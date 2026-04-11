import 自定义神经网络 as nn
import numpy as np
import matplotlib.pyplot as plt

class DropoutLayer:
    def __init__(self,droupout_ratio=0.5):
        self.dropout_ratio = droupout_ratio
        self.mask = None
    def forward(self,x,train_flg=True):
        if train_flg:
            self.mask = np.random.rand(*x.shape) > self.dropout_ratio
            return x*self.mask
        else:
            return x*(1-self.dropout_ratio)
    def backward(self,dout):
        return dout*self.mask
