import torch

data1 = [[1, 2, 3],
         [4, 5, 6]]

data2 = [[7, 8, 9],
         [10, 11, 12]]

tensor1 = torch.tensor(data1,dtype=torch.float32)
tensor2 = torch.tensor(data2,dtype=torch.float32)

tensor1 =torch.reshape(tensor1,[1,1,2,3])
tensor2 =torch.reshape(tensor2,[1,1,2,3])

loss = torch.nn.L1Loss()
print(loss(tensor1,tensor2))

loss_MSE = torch.nn.MSELoss()
print(loss_MSE(tensor1,tensor2))

tensor3 = torch.tensor([[0,1,0],[1,0,0]],dtype=torch.float32)


loss_cross = torch.nn.CrossEntropyLoss()
print(loss_cross(torch.tensor(data1,dtype=torch.float32),tensor3))

# 神经网络的反向传播与loss
import torch.nn as nn 
import torchvision
from  torch.utils.tensorboard import SummaryWriter
dataset = torchvision.datasets.CIFAR10(root='../torch_dataset',train=False,
                                       transform=torchvision.transforms.ToTensor(),download=True)
dataloader = torch.utils.data.DataLoader(dataset,batch_size=64,shuffle=True)
class MyNetWork(nn.Module):
    def __init__(self):
        super(MyNetWork,self).__init__()
        self.model = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=32, padding=2, kernel_size=5),
            nn.MaxPool2d(kernel_size=2),
            nn.Conv2d(in_channels=32, out_channels=32, padding=2, kernel_size=5),
            nn.MaxPool2d(kernel_size=2),
            nn.Conv2d(in_channels=32, out_channels=64, padding=2, kernel_size=5),
            nn.MaxPool2d(kernel_size=2),
            nn.Flatten(),
            nn.Linear(in_features=64 * 4 * 4, out_features=64, bias=True),
            nn.Linear(in_features=64, out_features=10, bias=True)
        )

    def forward(self,input):
        return self.model(input)

mynet =MyNetWork()
for data in dataloader:
    imgs,target=data
    imgs = mynet(imgs)
    result_loss=loss_cross(imgs,target)
    print(result_loss)
    result_loss.backward()
    
    
