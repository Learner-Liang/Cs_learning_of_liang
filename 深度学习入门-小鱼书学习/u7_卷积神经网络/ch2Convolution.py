import numpy as np
import ch1im2col 


class Convolution:
    def __init__(self,W,b,stride=1,pad=((0,0),(0,0))):
        self.W = W
        self.b = b
        self.stride = stride
        self.pad = pad

        self.x = None
        self.col = None
        self.col_W = None
        self.dW = None
        self.db = None

    def forward(self,x):
        FN,C,FH,FW = self.W.shape
        N,_,H,W = x.shape
        out_h = (H + self.pad[0][0] + self.pad[0][1] - FH) // self.stride + 1
        out_w = (W + self.pad[1][0] + self.pad[1][1] - FW) // self.stride + 1

        col = ch1im2col.im2col(x,FH,FW,stride=self.stride,pad=self.pad)
        col_W = self.W.reshape(FN,-1).T
        out = np.dot(col,col_W) + self.b
        out = out.reshape(N,out_h,out_w,FN).transpose(0,3,1,2)

        self.x = x
        self.col = col
        self.col_W = col_W
        return out

    def backward(self,dout):
        FN,C,FH,FW = self.W.shape
        dout = dout.transpose(0,2,3,1).reshape(-1,FN)

        self.db = np.sum(dout, axis=0)
        self.dW = np.dot(self.col.T, dout).T.reshape(FN, C, FH, FW)

        dcol = np.dot(dout, self.col_W.T)
        dx = ch1im2col.col2im(dcol, self.x.shape, FH, FW, stride=self.stride, pad=self.pad)
        return dx
