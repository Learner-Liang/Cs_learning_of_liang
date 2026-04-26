import torch.nn as nn 
import torchvision
import torch 
from  torch.utils.tensorboard import SummaryWriter
dataset = torchvision.datasets.CIFAR10(root='../torch_dataset',train=False,
                                       transform=torchvision.transforms.ToTensor(),download=True)
dataloader = torch.utils.data.DataLoader(dataset,batch_size=64,shuffle=True)
class MyNetWork(nn.Module):
    def __init__(self):
        super(MyNetWork,self).__init__()
        self.conv1 = nn.Conv2d(in_channels=3,out_channels=32,padding=2,kernel_size=5)
        self.Maxpool1 = nn.MaxPool2d(kernel_size=2)
        self.conv2 = nn.Conv2d(in_channels=32,out_channels=32,padding=2,kernel_size=5)
        self.Maxpool2 = nn.MaxPool2d(kernel_size=2)
        self.conv3 = nn.Conv2d(in_channels=32,out_channels=64,padding=2,kernel_size=5)
        self.Maxpool3 = nn.MaxPool2d(kernel_size=2)
        self.Flatten = nn.Flatten()
        self.linear1 = nn.Linear(in_features=64*4*4,out_features=64,bias=True)
        self.linear2 = nn.Linear(in_features=64,out_features=10,bias=True)

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
        # 等于以下内容

        '''output = self.conv1(input)
        output = self.Maxpool1(output)
        output = self.conv2(output)
        output = self.Maxpool2(output)
        output = self.conv3(output)
        output = self.Maxpool3(output)
        output =self.Flatten(output)
        output = self.linear1(output)
        output = self.linear2(output)
        return output'''


Mynet = MyNetWork()

input = next(iter(dataloader))[0]
print(Mynet(input))

# 看神经网络图
writer = SummaryWriter('net_graph')
writer.add_graph(Mynet,input)
writer.close()

        