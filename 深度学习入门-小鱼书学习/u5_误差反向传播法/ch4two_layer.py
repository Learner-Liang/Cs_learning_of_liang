import os
import sys

import matplotlib.pyplot as plt
import numpy as np

parent_dir = os.path.dirname(os.path.dirname(__file__))
sys.path.append(parent_dir)
chap4_dir = os.path.join(parent_dir, 'u4_神经网络的学习')
sys.path.append(chap4_dir)

from ch4function import *
from ch1简单乘加法层 import *
from ch2激活层 import *
from ch3Affine以及softmax层实现 import *
from dataset.mnist import load_mnist


class two_layer_net:
    def __init__(self, input_size, hidden_size, output_size):
        weight_init_std = 0.01
        self.params = {}
        self.params['W1'] = weight_init_std * np.random.randn(input_size, hidden_size)
        self.params['b1'] = np.zeros(hidden_size)
        self.params['W2'] = weight_init_std * np.random.randn(hidden_size, output_size)
        self.params['b2'] = np.zeros(output_size)

        self.layers = {}
        self.layers['Affine1'] = AffineLayer(self.params['W1'], self.params['b1'])
        self.layers['Relu1'] = ReluLayer()
        self.layers['Affine2'] = AffineLayer(self.params['W2'], self.params['b2'])
        self.last_layer = SoftmaxWithLoss()

    def sync_layer_params(self):
        self.layers['Affine1'].W = self.params['W1']
        self.layers['Affine1'].b = self.params['b1']
        self.layers['Affine2'].W = self.params['W2']
        self.layers['Affine2'].b = self.params['b2']

    def load_params(self, params):
        for key in ('W1', 'b1', 'W2', 'b2'):
            self.params[key] = params[key]
        self.sync_layer_params()

    def predict(self, x):
        for layer in self.layers.values():
            x = layer.forward(x)
        return x

    def loss(self, x, t):
        y = self.predict(x)
        return self.last_layer.forward(y, t)

    def accuracy(self, x, t):
        y = self.predict(x)
        y = np.argmax(y, axis=1)
        if t.ndim != 1:
            t = np.argmax(t, axis=1)
        right_num = np.sum(y == t)
        return float(right_num) / x.shape[0]

    def numerical_gradient(self, x, t):
        loss_w = lambda _: self.loss(x, t)
        grads = {}
        grads['W1'] = numerical_gradient(loss_w, self.params['W1'])
        grads['b1'] = numerical_gradient(loss_w, self.params['b1'])
        grads['W2'] = numerical_gradient(loss_w, self.params['W2'])
        grads['b2'] = numerical_gradient(loss_w, self.params['b2'])
        return grads

    def gradient(self, x, t):
        self.loss(x, t)
        dout = self.last_layer.backward(1)[0]
        layers = list(self.layers.values())
        layers.reverse()
        for layer in layers:
            dout = layer.backward(dout)

        grads = {}
        grads['W1'] = self.layers['Affine1'].dW
        grads['b1'] = self.layers['Affine1'].db
        grads['W2'] = self.layers['Affine2'].dW
        grads['b2'] = self.layers['Affine2'].db
        return grads


def test(layer_net, x_train, t_train):
    x_batch = x_train[0:3]
    t_batch = t_train[0:3]
    grads_num = layer_net.numerical_gradient(x_batch, t_batch)
    grads_bp = layer_net.gradient(x_batch, t_batch)
    a = np.average(np.abs(grads_num['W1'] - grads_bp['W1']))
    b = np.average(np.abs(grads_num['b1'] - grads_bp['b1']))
    c = np.average(np.abs(grads_num['W2'] - grads_bp['W2']))
    d = np.average(np.abs(grads_num['b2'] - grads_bp['b2']))
    if a < 1e-6 and b < 1e-6 and c < 1e-6 and d < 1e-6:
        print('数值微分与反向传播的结果相近！')
    else:
        print('数值微分与反向传播的结果不相近！')
        raise SystemExit(1)


if __name__ == '__main__':
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True)
    train_loss_list = []
    train_acc_list = []
    iteration_num = 50000
    learning_rate = 0.01
    start_iter = 0

    layer_net = two_layer_net(input_size=784, hidden_size=100, output_size=10)
    current_dir = os.path.dirname(__file__)
    model_path = os.path.join(current_dir, 'model_two_layer.npz')

    if os.path.exists(model_path):
        print('发现存档，正在恢复训练...')
        data = np.load(model_path)
        saved_params = {key: data[key] for key in ('W1', 'b1', 'W2', 'b2')}
        layer_net.load_params(saved_params)
        start_iter = data['iteration'] + 1
        train_loss_list = data['loss_list'].tolist()
        if 'acc_list' in data:
            train_acc_list = data['acc_list'].tolist()
    else:
        test(layer_net, x_train, t_train)

    train_batch_size = 100
    train_size = x_train.shape[0]
    for i in np.arange(start_iter, iteration_num):
        mask = np.random.choice(train_size, train_batch_size)
        x_batch = x_train[mask]
        t_batch = t_train[mask]
        grads = layer_net.gradient(x_batch, t_batch)
        for key in layer_net.params:
            layer_net.params[key] -= learning_rate * grads[key]
        if i % 100 == 0:
            loss = layer_net.loss(x_batch, t_batch)
            train_loss_list.append(loss)
            acc = layer_net.accuracy(x_batch, t_batch)
            train_acc_list.append(acc)
            print('第' + str(i) + '次迭代，损失值为' + str(loss) + ',准确率为', f'{acc}')

            np.savez(
                model_path,
                W1=layer_net.params['W1'],
                b1=layer_net.params['b1'],
                W2=layer_net.params['W2'],
                b2=layer_net.params['b2'],
                iteration=i,
                loss_list=train_loss_list,
                acc_list=train_acc_list,
            )

    print('训练完成！')
    test_loss = layer_net.loss(x_test, t_test)
    test_acc = layer_net.accuracy(x_test, t_test)
    print('测试数据的损失值为' + str(test_loss) + ',测试数据的准确率为', f'{test_acc}')
