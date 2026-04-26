import torch
import torchvision

vgg16_false = torchvision.models.vgg16(pretrained=False)
vgg16_true = torchvision.models.vgg16(pretrained=True)

print(vgg16_true)
# 由于输出为1000个类，需要自己加一层什么的进行修改

# 增加一层
vgg16_true.add_module(name='add_linear',module=torch.nn.Linear(1000,10))
print(vgg16_true)

# 直接修改
vgg16_false.classifier[6]=torch.nn.Linear(4096,10)

# 模型保存与模型加载
# 1
torch.save(vgg16_true,'../pretrained_model/vgg16_true1.pth')
print(torch.load('../pretrained_model/vgg16_true1.pth',weights_only=False))

# 2（推荐，小一些）
torch.save(vgg16_false.state_dict(),'../pretrained_model/vgg16_false.pth')
# 可以看到以下输出为字典
print(torch.load('../pretrained_model/vgg16_false.pth'))

vgg16_load = torchvision.models.vgg16(pretrained=False)
vgg16_load.classifier[6]=torch.nn.Linear(4096,10)
vgg16_load.load_state_dict(torch.load('../pretrained_model/vgg16_false.pth'))
print(vgg16_load)

