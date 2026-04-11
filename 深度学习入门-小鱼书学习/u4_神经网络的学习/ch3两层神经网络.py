import sys,os
sys.path.append(os.path.dirname(os.path.dirname(__file__)))
import numpy as np
import ch4function as function
from dataset.mnist import load_mnist
import matplotlib.pyplot as plt


if __name__=="__main__":
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True)
    train_loss_list = []
    train_acc_list = []
    iteration_num = 1500
    learning_rate = 0.1
    start_iter = 0


class two_layer_net:
    def __init__(self, input_size, hidden_size, output_size):
        self.params = {}
        self.params['W1'] = np.random.randn(input_size, hidden_size)
        self.params['b1'] = np.random.randn(hidden_size)
        self.params['W2'] = np.random.randn(hidden_size, output_size)
        self.params['b2'] = np.random.randn(output_size)

    def load_params(self, params):
        for key in ('W1', 'b1', 'W2', 'b2'):
            self.params[key] = params[key]

    def predict(self,x):
        a1=np.dot(x,self.params['W1'])+self.params['b1']
        z1=function.sigmoid(a1)
        a2=np.dot(z1,self.params['W2'])+self.params['b2']
        y=function.softmax(a2)
        return y
    
    def loss(self,x,t):
        y=self.predict(x)
        return function.cross_entropy_error(y,t)
    
    def accuracy(self,x,t):
        t=np.argmax(t,axis=1)
        y=np.argmax(self.predict(x),axis=1)
        ac_num=np.sum(y==t)
        return ac_num/float(x.shape[0])\
        
    def numerical_gradient(self,x,t):
        loss_W=lambda W:self.loss(x,t)
        grads = {}
        grads['W1'] = function.numerical_gradient(loss_W,self.params['W1'])
        grads['b1'] = function.numerical_gradient(loss_W,self.params['b1'])
        grads['W2'] = function.numerical_gradient(loss_W,self.params['W2'])
        grads['b2'] = function.numerical_gradient(loss_W,self.params['b2'])
        return grads

if __name__=="__main__":
    train_size=x_train.shape[0]
    batch_size=100
    network=two_layer_net(input_size=784,hidden_size=100,output_size=10)
    # 获取当前脚本所在目录（即“u4_神经网络的学习”文件夹）
    current_dir = os.path.dirname(__file__)
    model_path = os.path.join(current_dir, "model_two_layer.npz")

    # 恢复训练
    if os.path.exists(model_path):
        print("发现存档，正在恢复训练...")
        data = np.load(model_path)
        saved_params = {key: data[key] for key in ('W1', 'b1', 'W2', 'b2')}
        network.load_params(saved_params)
        start_iter = data['iteration'] + 1  # 从上次断点的下一次开始
        train_loss_list = data['loss_list'].tolist()  # 恢复画图用的列表

    for i in range(start_iter,iteration_num):
        mask=np.random.choice(train_size,batch_size)
        x_batch=x_train[mask]
        t_batch=t_train[mask]
        grads = network.numerical_gradient(x_batch,t_batch)
        for key in network.params:
            network.params[key] -= learning_rate * grads[key]
        if i%100==0:
            train_loss_list.append(network.loss(x_batch,t_batch))
            train_acc_list.append(network.accuracy(x_batch,t_batch))
            print("第"+str(i)+"次迭代，损失值为"+str(train_loss_list[-1])+",准确率为",f"{train_acc_list[-1]}")

            # 保存数据到当前脚本所在目录
            np.savez(model_path, 
                    W1=network.params['W1'], b1=network.params['b1'], 
                    W2=network.params['W2'], b2=network.params['b2'], 
                    iteration=i+1, 
                    loss_list=train_loss_list)

    print("训练完成！")
    test_acc=network.accuracy(x_test,t_test)
    test_loss=network.loss(x_test,t_test)
    print("测试数据的损失值为"+str(test_loss)+",测试数据的准确率为",f"{test_acc}")


    eporch = np.arange(len(train_loss_list))
    plt.figure(num=1,figsize=(10,5))
    plt.plot(eporch, train_loss_list, label="train_loss")
    plt.xlabel("eporch")
    plt.ylabel("loss")
    plt.legend()
    plt.show()

    plt.figure(num=2,figsize=(10,5))
    plt.plot(eporch, train_acc_list, label="train_acc")
    plt.xlabel("eporch")
    plt.ylabel("accuracy")
    plt.legend()
    plt.show()
