import numpy as np
class ReluLayer:
    def __init__(self):
        self.mask = None
    def forward(self,x):
        self.mask = (x <= 0)
        out = x.copy()
        out[self.mask] = 0
        return out
    def backward(self, dout):
        dx=dout.copy()
        dx[self.mask] = 0
        return dx
    
class SigmoidLayer:
    def __init__(self):
        self.out=None
    def forward(self,x):
        self.out=1/(1+np.exp(-x))
        return self.out
    def backward(self,dout):
        dx = dout*(1.0-self.out)*self.out
        return dx