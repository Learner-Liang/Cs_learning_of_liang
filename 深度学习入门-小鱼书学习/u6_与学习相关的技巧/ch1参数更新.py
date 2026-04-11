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


class SGD:
    def __init__(self,lr=0.01):
        self.lr = lr
    def update(self,params,grads):
        for key in params:
            params[key] -= self.lr * grads[key]
        return 

class Momentum:
    def __init__(self,lr=0.1,momentum=0.9):
        self.lr=lr
        self.momentum=momentum
        self.v=None
    def update(self,params,grad):
        if(self.v==None):
            self.v={}
            for key in params:
                self.v[key]=np.zeros_like(params[key])
        for key in params:
            self.v[key]=self.momentum*self.v[key]-self.lr*grad[key]
            params[key]+=self.v[key]
        return 

class AdaGrad:
    def __init__(self,lr=0.01):
        self.lr=lr
        self.h=None
    def update(self,params,grad):
        if self.h==None:
            self.h={}
            for key in params:
                self.h[key]=np.zeros_like(params[key])
        for key in params:
            self.h[key] += grad[key]*grad[key]
            params[key]-=self.lr*grad[key]/(np.sqrt(self.h[key])+np.exp(1e-7))
        return

class Adam:
    def __init__(self,lr=0.001,beta1=0.9,beta2=0.999):
        self.lr=lr
        self.beta1=beta1
        self.beta2=beta2
        self.m=None
        self.v=None
        self.iter=0
    def update(self,params,grad):
        if self.m ==None:
            self.m={}
            self.v={}
            for key in params:
                self.m[key]=np.zeros_like(params[key])
                self.v[key]=np.zeros_like(params[key])
        self.iter+=1
        for key in params:
            self.m[key] = self.beta1*self.m[key]+(1-self.beta1)*grad[key]
            self.v[key] = self.beta2*self.v[key]+(1-self.beta2)*grad[key]**2
            m_hat = self.m[key]/(1-self.beta1**self.iter)
            v_hat = self.v[key]/(1-self.beta2**self.iter)
            params[key] -= self.lr*m_hat/(np.sqrt(v_hat)+1e-7)
        return 
if __name__=="__main__":
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True)
    x_size = x_train.shape[0]
    loss_list={}
    iter_num=2000
    learning_rate=0.01
    batrch_size=100

    SGD_optimizer=SGD(lr=learning_rate)
    Momentum_optimizer=Momentum(lr=learning_rate,momentum=0.9)
    AdaGrad_optimizer=AdaGrad(lr=learning_rate)
    Adam_optimizer=Adam(lr=learning_rate,beta1=0.9,beta2=0.999)
    optimizers = {'SGD': SGD_optimizer, 'Momentum': Momentum_optimizer, 'AdaGrad': AdaGrad_optimizer, 'Adam': Adam_optimizer}
    net_layer = ch4two_layer.two_layer_net(input_size=784,hidden_size=100,output_size=10)

    color_list = {'SGD': 'red', 'Momentum': 'blue', 'AdaGrad': 'green', 'Adam': 'magenta'}
    line_type_list = {'SGD': '-', 'Momentum': '--', 'AdaGrad': '-.', 'Adam': ':'}
    plt.figure(figsize=(8, 6))
    plt.xlabel("iteration")
    plt.ylabel("loss")

    for key in optimizers.keys():
        
        loss_list[key]=[]
        optimizer = optimizers[key]
        for i in range(iter_num):
            mask = np.random.choice(x_size, batrch_size)
            x_batch = x_train[mask]
            t_batch = t_train[mask]
            loss_list[key].append(net_layer.loss(x_batch,t_batch))
            grads= net_layer.gradient(x_batch,t_batch)
            optimizer.update(net_layer.params,grads)
            if i%100==0:
                print(f"{key} : {i} / {iter_num} , loss : {loss_list[key][-1]}")
        plt.scatter((np.arange(iter_num))[::10], loss_list[key][::10], label=key,color=color_list[key],\
                 linestyle=line_type_list[key])
        plt.legend()
    plt.show()
