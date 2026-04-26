import torch.nn as nn
import torch 
from torch.utils.data import dataloader
import torchvision
from torch.utils.tensorboard import SummaryWriter

test_set = torchvision.datasets.CIFAR10(root='../torch_dataset',download=True,train=True,transform=torchvision.transforms.ToTensor())

dataloader = dataloader.DataLoader(test_set,shuffle=True,num_workers=0,batch_size=64,drop_last=True)

# 两层卷积层
class Module(nn.Module):
    def __init__(self):
        super(Module,self).__init__()
        # 卷积核 in_channels*kernel[0]*kernel[1]，有out_channels个卷积核
        # 输出为三个通道时候，当作RGB，1个时候为灰度图，因而如果通道数不一样需要reshape
        self.conv1 = nn.Conv2d(in_channels=3,out_channels=6,kernel_size=3,stride=1,padding=0)
        # 现在为[64,6,x,x]->[xx,3,x,x]
        self.conv2 = nn.Conv2d(in_channels=6,out_channels=6,kernel_size=3,stride=1,padding=0)

    def forward(self,input):
        output=self.conv1(input)
        output=self.conv2(output)
        return output
    
# 一层池化层
class MaxPollModule(nn.Module):
    def __init__(self):
        super(MaxPollModule,self).__init__()
        self.Maxpool1 = torch.nn.MaxPool2d(kernel_size=3,ceil_mode=True)
    def forward(self,input):
        return self.Maxpool1(input)


input = torch.tensor([
            [3, 0, 5, 1, 4],
            [2, 5, 1, 0, 3],
            [4, 2, 0, 5, 1],
            [1, 4, 3, 2, 0],
            [5, 1, 4, 3, 2]
        ],dtype=torch.float32)

kernel = torch.tensor([[
    [1, 1, 1], [1, 2, 1], [3, 1, 1]]
    ],dtype=torch.float32)

input = torch.reshape(input,[1,1,5,5])
kernel = torch.reshape(kernel,[1,1,3,3])

# 卷积层
# nn.functional 
conv = torch.nn.functional.conv2d(input,kernel,padding=0,stride=(1,2))
print(conv)

# nn
conv_nn = torch.nn.Conv2d(in_channels=1,out_channels=1,kernel_size=3)
print(conv_nn(input))

# 池化层
maxpool = torch.nn.MaxPool2d(kernel_size=3,ceil_mode=True)
print(maxpool(input))

# 测试数据
myModule= Module()
mypoolModule = MaxPollModule()
writer = SummaryWriter('../logs')
step=0
for data in dataloader:
    imgs,target = data
    writer.add_images("input",imgs,step)

    # 卷积层
    output = myModule(imgs)
    # add_img输出通道数只能为1/3
    output = torch.reshape(output,(-1,3,output.shape[2],output.shape[3]))
    writer.add_images('output',output,step)

    # 池化层
    output = mypoolModule(output)
    writer.add_images('pool',output,step)
    step+=1


writer.close()



