import numpy as np
import matplotlib.pyplot as plt
import sys, os

current_dir = os.path.dirname(__file__)
sys.path.append(current_dir)
parent_dir = os.path.dirname(os.path.dirname(__file__))
sys.path.append(parent_dir)
chap4_dir = os.path.join(parent_dir, "u4_神经网络的学习")
sys.path.append(chap4_dir)
chap5_dir = os.path.join(parent_dir, "u5_误差反向传播法")
sys.path.append(chap5_dir)
chap6_dir = os.path.join(parent_dir, "u6_与学习相关的技巧")
sys.path.append(chap6_dir)

from dataset.mnist import load_mnist
import ch4two_layer
from ch1参数更新 import Adam
from ch2激活层 import ReluLayer
from ch3Affine以及softmax层实现 import AffineLayer, SoftmaxWithLoss

import ch1im2col
import ch2Convolution
import ch3pooling


class Flatten:
    def __init__(self):
        self.original_x_shape = None

    def forward(self, x):
        self.original_x_shape = x.shape
        return x.reshape(x.shape[0], -1)

    def backward(self, dout):
        return dout.reshape(self.original_x_shape)


class MultiLayernNet:
    def __init__(self, input_size=(1,28,28),
                 conv_size={"filter_num":30,"filter_size": 5,"pad":0,"stride":1},\
                  hidden_size=100, out_size=10, weight_init_std=0.01, optimizer=None):
        self.params = {}
        self.optimizer = optimizer if optimizer is not None else Adam()

        self.params['W1'] = weight_init_std * \
            np.random.randn\
        (conv_size["filter_num"], input_size[0], conv_size["filter_size"], conv_size["filter_size"])
        self.params['b1'] = np.zeros(conv_size["filter_num"])

        conv_output_h = (input_size[1] - conv_size["filter_size"] + 2 * conv_size["pad"]) // conv_size["stride"] + 1
        conv_output_w = (input_size[2] - conv_size["filter_size"] + 2 * conv_size["pad"]) // conv_size["stride"] + 1
        pool_output_h = (conv_output_h - 2) // 2 + 1
        pool_output_w = (conv_output_w - 2) // 2 + 1
        affine_input_size = conv_size["filter_num"] * pool_output_h * pool_output_w

        self.params['W2'] = weight_init_std * \
            np.random.randn(affine_input_size, hidden_size)
        self.params['b2'] = np.zeros(hidden_size)
        self.params['W3'] = weight_init_std * np.random.randn(hidden_size, out_size)
        self.params['b3'] = np.zeros(out_size)
        
        self.layers = {}
        self.layers['Conv1'] = ch2Convolution.Convolution\
            (self.params['W1'], self.params['b1'], conv_size["stride"], \
             ((conv_size["pad"], conv_size["pad"]), (conv_size["pad"], conv_size["pad"])))
        self.layers['Relu1'] = ReluLayer()
        self.layers['pool1'] = ch3pooling.Pooling(2, 2, stride=2)
        self.layers['Flatten'] = Flatten()
        self.layers['Affine1'] = AffineLayer(self.params['W2'], self.params['b2'])
        self.layers['Relu2'] = ReluLayer()
        self.layers['Affine2'] = AffineLayer(self.params['W3'], self.params['b3'])
        self.lastLayer = SoftmaxWithLoss()
    def predict(self, x):
        for layer in self.layers.values():
            x = layer.forward(x)
        return x
    def loss(self, x, t):
        y = self.predict(x)
        return self.lastLayer.forward(y, t)
    
    def accuracy(self, x, t):
        y = self.predict(x)
        y = np.argmax(y, axis=1)
        if t.ndim != 1 :
            t = np.argmax(t, axis=1)
        accuracy = np.sum(y == t) / float(x.shape[0])
        return accuracy 
    def gradient(self, x, t):
        self.loss(x, t)
        dout = 1
        dout = self.lastLayer.backward(dout)
        if isinstance(dout, tuple):
            dout = dout[0]
        layers = list(self.layers.values())
        layers.reverse()
        for layer in layers:
            dout = layer.backward(dout)
        grads = {}
        grads['W1'] = self.layers['Conv1'].dW
        
        grads['b1'] = self.layers['Conv1'].db
        grads['W2'] = self.layers['Affine1'].dW
        grads['b2'] = self.layers['Affine1'].db
        grads['W3'] = self.layers['Affine2'].dW
        grads['b3'] = self.layers['Affine2'].db
        return grads
    
