import torch 

data = [
    [1.2, -0.7, 2.5, -1.1],
    [-2.3, 0.4, 1.8, 2.9],
    [0.0, -1.6, 0.9, 1.3],
]
input = torch.tensor(data, dtype=torch.float32)
input = torch.reshape(input,[-1,1,input.shape[0],input.shape[1]])

class MyRelu(torch.nn.Module):
    def __init__(self):
        super(MyRelu,self).__init__()
        self.Relu1= torch.nn.ReLU()
    def forward(self,input):
        return self.Relu1(input)
    
class Mysigmoid(torch.nn.Module):
    def __init__(self):
        super(Mysigmoid,self).__init__()
        self.sigmoid1= torch.nn.Sigmoid()
    def forward(self,input):
        return self.sigmoid1(input)
    
myrelu=MyRelu()
mysigmoid=Mysigmoid()
print("ReLu:")
print(myrelu(input))
print("sigmoid:")
print(mysigmoid(input))