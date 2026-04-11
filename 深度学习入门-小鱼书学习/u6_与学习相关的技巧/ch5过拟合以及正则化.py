import 自定义神经网络 as nn
import numpy as np
import matplotlib.pyplot as plt
if __name__ == '__main__':
    (x_train, t_train), (x_test, t_test) = nn.load_mnist(normalize=True, one_hot_label=True) 

    optimizer = nn.Adam()
    network = nn.MultiLayernNet(input_size=784, hidden_size_list=[100, 100, 100,100,100], \
                                out_size=10, weight=nn.np.sqrt(2/100), optimizer=optimizer)
    iters_num = 200
    train_size = x_train.shape[0]
    batch_size = 100
    loss_list = []
    accuracy_list = []
    test_acc_list = []

    x_train = x_train[:300]
    t_train = t_train[:300]
    train_size = x_train.shape[0]

    plt.xlabel('epoch')
    plt.ylabel('accuracy')
    plt.xticks(np.arange(0, iters_num // batch_size, 50))
    plt.yticks(np.arange(0, 1.1, 0.1))

    for i in range(iters_num):
        batch_mask = np.random.choice(train_size, batch_size)
        x_batch = x_train[batch_mask]
        t_batch = t_train[batch_mask]

        grad = network.gradient(x_batch, t_batch)
        optimizer.update(network.params, grad)
        loss = network.loss(x_batch, t_batch)
        if i % 100 == 0:
            print(f"iteration {i}/{iters_num} loss: {loss}")
            loss_list.append(loss)
        accuracy_list.append(network.accuracy(x_batch, t_batch))
        test_acc_list.append(network.accuracy(x_test, t_test))

    plt.plot(np.arange(len(accuracy_list)), accuracy_list, 
             label='train', color='blue', linestyle='-')
    plt.plot(np.arange(len(accuracy_list)), test_acc_list, 
             label='test', color='red', linestyle='-')
    network.init()
    # 正则化
    loss_list = []
    accuracy_list= []
    test_acc_list = []
    optimizer = nn.Adam()
    for i in range(iters_num):
        mask = np.random.choice(train_size, batch_size)
        x_batch = x_train[mask]
        t_batch = t_train[mask]
        grad = network.gradient(x_batch, t_batch,lamada_w=0.01, _params=network.params)
        optimizer.update(network.params, grad)
        loss = network.loss_w_r(x_batch, t_batch,lamada_w=0.01)
        if i % 100 == 0:
            print(f"iteration {i}/{iters_num} loss: {loss}")
            loss_list.append(loss)
        accuracy_list.append(network.accuracy(x_batch, t_batch))
        test_acc_list.append(network.accuracy(x_test, t_test))
    plt.plot(np.arange(len(accuracy_list)), accuracy_list, 
             label='train_regularized', color='blue', linestyle='--')
    plt.plot(np.arange(len(accuracy_list)), test_acc_list, 
             label='test_regularized', color='red', linestyle='--')
    
    plt.legend()
    
    plt.show()