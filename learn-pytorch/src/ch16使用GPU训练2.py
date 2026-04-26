import torch 
import torchvision
import torch.nn as nn
import os
from torch.utils.tensorboard import SummaryWriter

train_dataset = torchvision.datasets.CIFAR10(root='../torch_dataset',
                                       download=True,transform=torchvision.transforms.ToTensor(),train=True)

test_dataset = torchvision.datasets.CIFAR10(root='../torch_dataset',
                                          download=True,transform=torchvision.transforms.ToTensor(),train=False)

device = torch.device('cuda:0')

train_size = len(train_dataset)
test_size = len(test_dataset)

train_dataloader = torch.utils.data.DataLoader(train_dataset,batch_size=64,drop_last=True)
test_dataloader = torch.utils.data.DataLoader(test_dataset,batch_size=64,drop_last=True)


class MyNetWork(nn.Module):
    def __init__(self,lr=0.001):
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
        self.Loss = nn.CrossEntropyLoss().to(device)
        self.optim = torch.optim.Adam(self.model.parameters(),lr=lr)

    def forward(self,input):
        return self.model(input)
    
    def loss(self,input,output):
        return self.Loss(input,output)
    

eporch = 30
writer = SummaryWriter('logs_loss')

if os.path.exists('../pretrained_model/ch14_model.pth'):
    mynet = torch.load('../pretrained_model/ch14_model.pth',weights_only=False)
    # 使用gpu
    mynet = mynet.to(device)
else:
    mynet = MyNetWork()
    mynet.train()
    for i in range(eporch):
        loss_result_train = 0
        loss_result_test = 0

        acurracy=0

        print(f"---------第{i}轮训练开始---------")
        for data in train_dataloader:
            imgs,target = data
            imgs = mynet(imgs)
            # 使用gpu
            imgs = imgs.to(device)
            target = target.to(device)

            acurracy += (imgs.argmax(1)==target).sum()
            result=mynet.loss(imgs,target)
            mynet.optim.zero_grad()
            result.backward()
            mynet.optim.step()
            loss_result_train+=result.item()
        print(f"本轮训练损失函数值总和为{loss_result_train},正确率为{1.0*acurracy/train_size}")
        writer.add_scalar('train_loss',loss_result_train,i)
        writer.add_scalar('train_accuracy',1.0*acurracy/train_size,i)

        mynet.eval()
        acurracy = 0
        with torch.no_grad():
            for data in test_dataloader:
                imgs,target = data
                imgs = mynet(imgs)
                 # 使用gpu
                imgs = imgs.to(device)
                target = target.to(device)

                acurracy += (imgs.argmax(1)==target).sum()
                result = mynet.loss(imgs,target)
                loss_result_test +=result.item()
        writer.add_scalar('test_loss',loss_result_test,i)
        writer.add_scalar('test_accuary',1.0*acurracy/test_size,i)
        print(f"本轮测试损失函数值总和为{loss_result_test},正确率为{1.0*acurracy/test_size}")

    torch.save(mynet,'../pretrained_model/ch14_model.pth')
    print("模型已经保存")
writer.close()


