import torchvision
from torch.utils.tensorboard import SummaryWriter
from torch.utils.data import dataloader

composor = torchvision.transforms.Compose([
    torchvision.transforms.ToTensor()
])

train_set = torchvision.datasets.CIFAR10(root='../torch_dataset',transform=composor,train=True,download=True)
test_set = torchvision.datasets.CIFAR10(root='../torch_dataset',transform=composor,train=False,download=True)
writer = SummaryWriter('../logs')

Not_Droplast_test_data_loader = dataloader.DataLoader(test_set,batch_size=64,shuffle=True,num_workers=0,drop_last=True)
print("单张图片：",train_set[0][0].shape)

step=0
for data in Not_Droplast_test_data_loader:
    imgs,targets= data
    writer.add_images("Not_Droplast",imgs,step)
    step+=1

Droplast_test_data_loader = dataloader.DataLoader(test_set,batch_size=64,shuffle=True,num_workers=0,drop_last=False)
step=0

for data in Droplast_test_data_loader:
    imgs,targets= data
    writer.add_images("Droplast",imgs,step)
    step+=1

writer.close()
