from torch.utils.tensorboard import SummaryWriter
from PIL import Image
import numpy as np


writer = SummaryWriter("../logs")
for i in range(10):
    writer.add_scalar('y=x', i, i)


image_path = "../dataset_excersize/train/ants_image/0013035.jpg"
# image_path = "../dataset_excersize/train/ants_image/5650366_e22b7e1065.jpg"
img = Image.open(image_path)
img_array = np.array(img)
print(img_array.shape)
writer.add_image('test', img_array, 1, dataformats='HWC')
writer.close()
