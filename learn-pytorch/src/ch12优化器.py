import torch
import torchvision
import torch.nn as nn

dataset = torchvision.datasets.CIFAR10(root='../torch_dataset',train=False,
                                       download=True,transform=torchvision.transforms.ToTensor())
dataloader = torch.utils.data.DataLoader(dataset,batch_size=64,drop_last=False,shuffle=True)

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
        self.optimizor = torch.optim.Adam(self.model.parameters(),lr=0.01)
        self.loss = nn.CrossEntropyLoss()

    def forward(self,input):
        return self.model(input)
    
    def Loss(self,input,target):
        return self.loss(input,target)
    
mynet = MyNetWork()

for i in range(20):
    for data in dataloader:
        imgs,target = data
        imgs_result = mynet(imgs)
        loss_result = mynet.Loss(imgs_result,target)
        mynet.optimizor.zero_grad()
        loss_result.backward()
        mynet.optimizor.step()
        print(loss_result)