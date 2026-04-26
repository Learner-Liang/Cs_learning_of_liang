from PIL import Image
from torch.utils.tensorboard import SummaryWriter
from torchvision import transforms

img_path = "../dataset_excersize/train/ants_image/0013035.jpg"
img = Image.open(img_path)

writer = SummaryWriter('../logs')

# totensor
tran_to_tensor = transforms.ToTensor()
img_tensor = tran_to_tensor(img)

writer.add_image("img_tensor",img_tensor,0)

# Normalize
tensor_normal = transforms.Normalize([0.5,0.5,0.5],[0.5,0.5,0.5])
img_tensor_nor = tensor_normal(img_tensor)
writer.add_image("img_tensor",img_tensor_nor,1)

tensor_normal = transforms.Normalize([1,2,3],[1,2,3])
img_tensor_nor = tensor_normal(img_tensor)
writer.add_image("img_tensor",img_tensor_nor,2)


# resize
trans_resize = transforms.Resize((512,512))
img_resize = trans_resize(img)
print("Resize的返回类型为:",type(img_resize))
img_resize_tensor = tran_to_tensor(img_resize)
writer.add_image("resize_img",img_resize_tensor,0)


# compose
trans_resize2 = transforms.Resize(512)
resize_composor = transforms.Compose([trans_resize2,tran_to_tensor])
img1 = resize_composor(img)
writer.add_image("compose",img1,0)


# randomcrop
tran_randomcrop = transforms.RandomCrop((400,500))
compose_randomcrop = transforms.Compose([tran_to_tensor,tran_randomcrop])
for i in range(10):
    temp = compose_randomcrop(img)
    writer.add_image('Compose',temp,i)


writer.close()

