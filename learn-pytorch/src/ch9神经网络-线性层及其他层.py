import torch.nn as nn
import torchvision
import torch

dataset = torchvision.datasets.CIFAR10(root='../torch_dataset',transform=torchvision.transforms.ToTensor(),
                                       train=False,download=True)
dataloader = torch.utils.data.DataLoader(dataset,batch_size=64,shuffle=True,num_workers=0
                                         ,drop_last=True)
class MyNetWork(nn.Module):
    def __init__(self):
        super(MyNetWork,self).__init__()
        imgs = next(iter(dataloader))[0]
        self.linear1 = nn.Linear(imgs.shape[0]*imgs.shape[1]*imgs.shape[2]*imgs.shape[3],10,bias=1)
    def forward(self,input):
        return self.linear1(input)

mynet = MyNetWork()
for data in dataloader:
    imgs,target = data
    imgs= torch.reshape(imgs,[1,1,1,-1])
    print(mynet(imgs))
