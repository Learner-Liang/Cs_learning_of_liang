import numpy as np
import matplotlib.pyplot as plt
import sys,os
parent_dir = os.path.dirname(os.path.dirname(__file__))
sys.path.append(parent_dir)
chap4_dir = os.path.join(parent_dir, "u4_神经网络的学习")
sys.path.append(chap4_dir)
chap5_dir = os.path.join(parent_dir, "u5_误差反向传播法")
sys.path.append(chap5_dir)
from dataset.mnist import load_mnist
import ch4two_layer
from ch1参数更新 import Adam

def relu(x):
    return np.maximum(0, x)

if __name__ == '__main__':
    node_num = 100
    S= {"He": np.sqrt(2/node_num), "Xavier": np.sqrt(1/node_num), "std": 0.01}
    x = np.random.rand(100, node_num)
    layer_num = 5
    W = np.random.randn(layer_num, node_num, node_num)
    plt.figure(1, figsize=(12, 12))
    j = 0
    for key in S:
        a=x
        w = W * S[key]
        for i in range(layer_num):
            a = relu(np.dot(a, w[i]))
            plt.subplot(3, layer_num,j*5 + i + 1)
            plt.title(key + ' layer' + str(i + 1))
            plt.hist(a.flatten(), bins=40, range=(0, 1))
        j+=1
    plt.show()

    color={"std": "red", "Xavier": "blue", "He": "green"}
    plt.figure(2, figsize=(12, 6))
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True) 

    network = ch4two_layer.two_layer_net(input_size=784, hidden_size=100, output_size=10)
    optimizer = Adam()
    iters_num = 2000
    train_size = x_train.shape[0]
    batch_size = 100
    loss_list = {}
    plt.xlabel('iterations')
    plt.ylabel('loss')

    for key in S:
        loss_list[key] = []
        network.params['W1'] = np.random.randn(784, 100) * S[key]
        network.params['b1'] = np.zeros(100)
        network.params['W2'] = np.random.randn(100, 10) * S[key]
        network.params['b2'] = np.zeros(10)
        network.sync_layer_params()

        for i in range(iters_num):
            batch_mask = np.random.choice(train_size, batch_size)
            x_batch = x_train[batch_mask]
            t_batch = t_train[batch_mask]

            grad = network.gradient(x_batch, t_batch)
            optimizer.update(network.params, grad)
            loss = network.loss(x_batch, t_batch)
            if i % 100 == 0:
                print(f"{key} iteration {i}/{iters_num} loss: {loss}")
            loss_list[key].append(loss)
        plt.scatter((np.arange(iters_num))[::10], loss_list[key][::10], label=key, color=color[key])
        plt.legend()
    plt.show()