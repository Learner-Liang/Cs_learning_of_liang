import numpy as np


def im2col(input_data,fh,fw,stride=1,pad=((0,0),(0,0)),constant_values=0):
    input_data = np.pad(input_data, ((0,0),(0,0),(pad[0][0],pad[0][1]) ,(pad[1][0],pad[1][1])), \
                        mode='constant',constant_values=constant_values)

    N,C,H,W = input_data.shape
    out_h = (H-fh)//stride + 1
    out_w = (W-fw)//stride + 1
    col = np.zeros((N*out_h*out_w, C*fh*fw))
    i=0
    for a in range(N):
        for h in range(0, out_h):
            h_temp = h*stride
            for w in range(0, out_w):
                col[i] = input_data[a,0:C,h_temp:h_temp+fh,w*stride:w*stride+fw].flatten()
                i+=1
    return col


def col2im(col, input_shape, fh, fw, stride=1, pad=((0,0),(0,0))):
    N, C, H, W = input_shape
    H_pad = H + pad[0][0] + pad[0][1]
    W_pad = W + pad[1][0] + pad[1][1]
    out_h = (H_pad - fh) // stride + 1
    out_w = (W_pad - fw) // stride + 1

    img = np.zeros((N, C, H_pad, W_pad))
    i = 0
    for a in range(N):
        for h in range(out_h):
            h_temp = h * stride
            for w in range(out_w):
                w_temp = w * stride
                img[a, :, h_temp:h_temp+fh, w_temp:w_temp+fw] += col[i].reshape(C, fh, fw)
                i += 1

    h_end = H_pad - pad[0][1] if pad[0][1] > 0 else H_pad
    w_end = W_pad - pad[1][1] if pad[1][1] > 0 else W_pad
    return img[:, :, pad[0][0]:h_end, pad[1][0]:w_end]
