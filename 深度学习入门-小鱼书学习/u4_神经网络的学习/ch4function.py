import numpy as np
def numerical_derivative(f, x):
    h=1e-5
    return (f(x+h)-f(x-h)) / (2*h)

def numerical_gradient(f, x):
    h=1e-5
    grad = np.zeros(x.shape)
    it = np.nditer(x, flags=['multi_index'], op_flags=['readwrite'])
    
    while not it.finished:
        idx = it.multi_index
        tmp_val = x[idx]
        
        x[idx] = float(tmp_val) + h
        f1 = f(x) 
        
        x[idx] = float(tmp_val) - h
        f2 = f(x) 
        
        grad[idx] = (f1 - f2) / (2*h)
        
        x[idx] = tmp_val 
        
        it.iternext()
        
    return grad

def softmax(a):
    c=np.max(a,axis=1).reshape(-1,1)
    ex_p = np.exp(a-c)
    sum_ex_p = np.sum(ex_p,axis=1).reshape(-1,1)
    y = ex_p / sum_ex_p
    return y

def sigmoid(x):
    return 1/(1+np.exp(-x))

def cross_entropy_error(y,t):
    if(y.ndim == 1):
        t=t.reshape(1,t.size)
        y=y.reshape(1,y.size)   
    batch_size=y.shape[0]
    return -np.sum(t*np.log(y+1e-7))/batch_size

def false_cross_entropy_error(y,t):
    if y.ndim == 1:
        t = t.reshape(1, t.size)
        y = y.reshape(1, y.size)
    batch_size = y.shape[0]
    return -np.sum(np.log(y[np.arange(batch_size), t] + 1e-7)) / batch_size