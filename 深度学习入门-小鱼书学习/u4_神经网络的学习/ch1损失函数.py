import os
import sys

import numpy as np

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from dataset.mnist import load_mnist


def cross_entropy_error(y, t):
    if y.ndim == 1:
        t = t.reshape(1, t.size)
        y = y.reshape(1, y.size)
    batch_size = y.shape[0]
    return -np.sum(t * np.log(y + 1e-7)) / batch_size


def false_cross_entropy_error(y, t):
    if y.ndim == 1:
        t = t.reshape(1, t.size)
        y = y.reshape(1, y.size)
    batch_size = y.shape[0]
    return -np.sum(np.log(y[np.arange(batch_size), t] + 1e-7)) / batch_size


if __name__ == '__main__':
    (x_train, t_train), _ = load_mnist(one_hot_label=True, normalize=True)
    print('训练数据的形状：', x_train.shape)
    print('训练标签的形状：', t_train.shape)

    train_size = x_train.shape[0]
    batch_size = 100
    batch_mask = np.random.choice(train_size, batch_size)
    x_batch = x_train[batch_mask]
    t_batch = t_train[batch_mask]

    print('选取的数据下标:', batch_mask)
    print('batch 数据形状：', x_batch.shape)
    print('batch 标签形状：', t_batch.shape)
