import matplotlib.pyplot as plt
import numpy as np


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


if __name__ == '__main__':
    x = np.random.randn(1000, 100)
    layer_num = 5
    activation = {}
    a = x
    plt.figure(1, figsize=(12, 8))
    W = np.random.randn(layer_num, 100, 100)
    for i in range(layer_num):
        a = sigmoid(np.dot(a, W[i]))
        activation[i] = a
        plt.subplot(2, layer_num, i + 1)
        plt.title('layer' + str(i + 1))
        plt.hist(a.flatten(), bins=40, range=(0, 1))

    a = x
    W = 0.01 * W
    for i in range(layer_num):
        a = sigmoid(np.dot(a, W[i]))
        activation[i] = a
        plt.subplot(2, layer_num, i + 1 + layer_num)
        plt.title('layer' + str(i + 1))
        plt.hist(a.flatten(), bins=40, range=(0, 1))

    plt.show()

    plt.figure(2, figsize=(12, 6))
    W = W / np.sqrt(100)
    a = x
    for i in range(layer_num):
        a = sigmoid(np.dot(a, W[i]))
        activation[i] = a
        plt.subplot(2, layer_num, i + 1)
        plt.title('layer' + str(i + 1))
        plt.hist(a.flatten(), bins=40, range=(0, 1))
    plt.show()
