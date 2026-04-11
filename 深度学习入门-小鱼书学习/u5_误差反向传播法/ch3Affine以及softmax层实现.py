import numpy as np
import sys
import os

parent_dir = os.path.dirname(os.path.dirname(__file__))
chap4_dir = os.path.join(parent_dir, "u4_神经网络的学习")
sys.path.append(chap4_dir)
from ch4function import *
class AffineLayer:
    def __init__(self,W,b):
        self.W = W
        self.b = b
        self.x = None
        self.dW = None
        self.db = None
    def forward(self,x):
        out =np.dot(x,self.W)+self.b
        self.x = x
        return out
    def backward(self,dout):
        dx =np.dot(dout,self.W.T)
        self.dW = np.dot(self.x.T,dout )
        self.db=np.sum(dout,axis=0)
        return dx
    
class SoftmaxWithLoss:
    def __init__(self):
        self.loss = None
        self.y = None
        self.t = None
    def forward(self,x,t):
        self.t = t
        self.y = softmax(x)
        self.loss = cross_entropy_error(self.y, self.t)
        return self.loss
    def backward(self,dout,lamada_w=0.1,params=None):
        dx = dout*(self.y-self.t)/self.t.shape[0]
        grad = {}
        if params is not None:
            for i in range(1, len(params) // 2 + 1):
                grad['W' + str(i)] = params['W' + str(i)] * (lamada_w)
                grad['b' + str(i)] = 0
        return dx,grad