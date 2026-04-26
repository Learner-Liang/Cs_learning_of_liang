import torchvision
from torch.utils.tensorboard import SummaryWriter

# 转化为tensor之后test_set[0]返回值不一样
composor = torchvision.transforms.Compose(
    [torchvision.transforms.ToTensor()
])

train_set = torchvision.datasets.CIFAR10(root="../torch_dataset",train=True,transform=composor,download=True)
test_set = torchvision.datasets.CIFAR10(root="../torch_dataset",train=False,transform=composor,download=True)

print(train_set[0])
img,label=train_set[0]
print("数据的种类为：",train_set.classes)
print(label)
print("下标为0对应的种类为:",train_set.classes[label])
img.show()


