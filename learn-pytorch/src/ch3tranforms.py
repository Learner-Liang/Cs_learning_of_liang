from torchvision import transforms
from PIL import Image
import cv2
from torch.utils.tensorboard import SummaryWriter

# transforms结构以及用法
img_path = "../dataset_excersize/train/ants_image/0013035.jpg"
img = Image.open(img_path)

## 两种参数
# 1.PIL图片
tensor_trans = transforms.ToTensor()
img_tensor = tensor_trans(img)
# print(img_tensor)
print(type(img))
 
# 2.opencv的img
img_cv = cv2.imread(img_path)
img_cv_tensor = tensor_trans(img_cv)
# print(img_cv_tensor)
print(type(img_cv))

# 传送tensor
writer = SummaryWriter("../logs")
writer.add_image("tensor_img",img_tensor)
writer.close()
