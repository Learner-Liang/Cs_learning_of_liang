import numpy as np


class BatchNormalization:
    def __init__(self, gamma, beta, momentum=0.9, eps=1e-7):
        self.gamma = gamma
        self.beta = beta
        self.momentum = momentum
        self.running_mean = None
        self.running_var = None
        self.eps = eps

        self.xc = None
        self.xn = None
        self.s = None
        self.sigma = None

        self.dgamma = None
        self.dbeta = None

    def forward(self, x):
        if self.running_mean is None:
            D = x.shape[1]
            self.running_mean = np.zeros(D)
            self.running_var = np.zeros(D)
        
        x_mean = x.mean(axis=0)
        self.xc = x - x_mean
        self.s = np.mean(self.xc**2, axis=0)
        self.sigma = np.sqrt(self.s + self.eps)
        self.xn = (x - x_mean) / self.sigma
        out = self.gamma * self.xn + self.beta
        self.running_mean = self.momentum * self.running_mean + (1 - self.momentum) * x_mean
        self.running_var = self.momentum * self.running_var + (1 - self.momentum) * self.s
        return out
    
    def test_forward(self, x):
        xc = x - self.running_mean
        xn = xc / np.sqrt(self.running_var + self.eps)
        out = self.gamma * xn + self.beta
        return out

    def backward(self, dout):
        self.dbeta = dout.sum(axis=0)
        self.dgamma = np.sum(self.xn * dout, axis=0)
        dx = self.gamma/self.sigma * (dout - dout.mean(axis=0) - self.xn * (dout * self.xn).mean(axis=0))
        return dx
