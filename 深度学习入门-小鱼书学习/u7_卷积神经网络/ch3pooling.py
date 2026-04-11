import ch1im2col
import numpy as np
class Pooling:
    def __init__(self,ph,pw,stride=1,pad=((0,0),(0,0))):
        self.ph = ph
        self.pw = pw
        self.stride = stride
        self.pad = pad
        self.x = None
        self.arg_max = None
        self.col_shape = None

    def forward(self,x,constant_values=0):
        N,C,H,W = x.shape
        out_h = (H + self.pad[0][0] + self.pad[0][1] - self.ph)//self.stride + 1
        out_w = (W + self.pad[1][0] + self.pad[1][1] - self.pw)//self.stride + 1

        col = ch1im2col.im2col(x,self.ph,self.pw,self.stride,self.pad,constant_values)
        self.x = x
        self.col_shape = col.shape
        col = col.reshape(-1,self.ph*self.pw)
        self.arg_max = np.argmax(col, axis=1)

        out = np.max(col,axis=1)
        out= out.reshape(N,out_h,out_w,C).transpose(0,3,1,2)
        return out

    def backward(self,dout):
        pool_size = self.ph*self.pw
        dout = dout.transpose(0,2,3,1)

        dmax = np.zeros((dout.size, pool_size))
        dmax[np.arange(self.arg_max.size), self.arg_max] = dout.flatten()
        dcol = dmax.reshape(self.col_shape)
        dx = ch1im2col.col2im(dcol, self.x.shape, self.ph, self.pw, self.stride, self.pad)
        return dx

        
