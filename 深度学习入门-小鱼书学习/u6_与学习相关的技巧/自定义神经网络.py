import numpy as np
import matplotlib.pyplot as plt
import sys, os

parent_dir = os.path.dirname(os.path.dirname(__file__))
sys.path.append(parent_dir)
chap4_dir = os.path.join(parent_dir, "u4_神经网络的学习")
sys.path.append(chap4_dir)
chap5_dir = os.path.join(parent_dir, "u5_误差反向传播法")
sys.path.append(chap5_dir)

from dataset.mnist import load_mnist
import ch4two_layer
from ch1参数更新 import Adam
from ch2激活层 import ReluLayer
from ch3Affine以及softmax层实现 import AffineLayer, SoftmaxWithLoss


class MultiLayernNet:
    def __init__(self, input_size, hidden_size_list, out_size, weight, optimizer=None):
        if optimizer is None:
            self.optimizer = Adam()
        else :
            self.optimizer = optimizer
        self.params = {}
        self.layers = {}
        self.params['W1'] = np.random.randn(input_size, hidden_size_list[0]) * weight
        self.params['b1'] = np.zeros(hidden_size_list[0])

        self.hidden_size = len(hidden_size_list)

        self.layers['Affine1'] = AffineLayer(self.params['W1'], self.params['b1'])
        self.layers['Relu1'] = ReluLayer()

        for i in range(1, len(hidden_size_list)):
            self.params['W' + str(i + 1)] = np.random.randn(hidden_size_list[i - 1], hidden_size_list[i]) * weight
            self.params['b' + str(i + 1)] = np.zeros(hidden_size_list[i])
            self.layers['Affine' + str(i + 1)] = AffineLayer(self.params['W' + str(i + 1)], self.params['b' + str(i + 1)])
            self.layers['Relu' + str(i + 1)] = ReluLayer()

        
        self.params['W' + str(len(hidden_size_list) + 1)] = np.random.randn\
            (hidden_size_list[-1], out_size) * weight
        self.params['b' + str(len(hidden_size_list) + 1)] = np.zeros(out_size)
        self.layers['Affine' + str(len(hidden_size_list) + 1)] = \
            AffineLayer(self.params['W' + str(len(hidden_size_list) + 1)], \
                        self.params['b' + str(len(hidden_size_list) + 1)])

        self.last_layer = SoftmaxWithLoss()

    def init(self):
        self.params['W1'] = np.random.randn(784, 100) * np.sqrt(2/100)
        self.params['b1'] = np.zeros(100)
        self.layers['Affine1'].W = self.params['W1']
        self.layers['Affine1'].b = self.params['b1']
        for i in range(2, self.hidden_size + 1):
            self.params['W' + str(i)] = np.random.randn(100, 100) * np.sqrt(2/100)
            self.params['b' + str(i)] = np.zeros(100)
            self.layers['Affine' + str(i)].W = self.params['W' + str(i)]
            self.layers['Affine' + str(i)].b = self.params['b' + str(i)]
        self.params['W' + str(self.hidden_size + 1)] = np.random.randn(100, 10) * np.sqrt(2/100)
        self.params['b' + str(self.hidden_size + 1)] = np.zeros(10)
        self.layers['Affine' + str(self.hidden_size + 1)].W = self.params['W' + str(self.hidden_size + 1)]
        self.layers['Affine' + str(self.hidden_size + 1)].b = self.params['b' + str(self.hidden_size + 1)]
        

    def predict(self, x):
        for layer in self.layers.values():
            x = layer.forward(x)
        return x

    def loss(self, x, t):
        y = self.predict(x)
        return self.last_layer.forward(y, t)
    

    def loss_w_r(self,x,t,lamada_w):
        y = self.predict(x)
        loss = self.last_layer.forward(y, t)
        for i in range(1, self.hidden_size + 2):
            loss += 0.5 * lamada_w * np.sum(self.params['W' + str(i)] ** 2)
        return loss
    

    def accuracy(self, x, t,prams=None):
        y = self.predict(x)
        y = y.argmax(axis=1)
        if t.ndim != 1:
            t = t.argmax(axis=1)
        accuracy = np.sum(y == t) / float(x.shape[0])
        return accuracy

    def gradient(self, x, t,_params=None,lamada_w=0.1):
        self.loss(x, t)
        dout = 1
        dout, grad = self.last_layer.backward(dout,params=_params,lamada_w=lamada_w)
        layers = list(self.layers.values())
        layers.reverse()

        for layer in layers:
            dout = layer.backward(dout)
        for i in range(1, self.hidden_size + 2):
            if _params is not None:
                grad['W' + str(i)] += self.layers['Affine' + str(i)].dW
                grad['b' + str(i)] += self.layers['Affine' + str(i)].db
            else :
                grad['W' + str(i)] = self.layers['Affine' + str(i)].dW
                grad['b' + str(i)] = self.layers['Affine' + str(i)].db
        return grad
