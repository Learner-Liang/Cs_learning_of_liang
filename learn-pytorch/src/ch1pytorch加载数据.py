from torch.utils.data import Dataset
from PIL import Image
import os
# help(Dataset)

class Mydata(Dataset):
    def __init__(self,root_dir,img_dir,label_dir):
        self.root_dir = root_dir
        self.img_dir=img_dir
        self.label_dir=label_dir

        # 路径相加
        self.img_path =  os.path.join(root_dir,img_dir)
        self.label_path = os.path.join(root_dir,label_dir)

         # 将文件夹下所有东西（名称）变成列表
        self.img_list = os.listdir(self.img_path)
        self.label_list = os.listdir(self.label_path)
    
    def __getitem__(self, index):
        img_path = os.path.join(self.img_path,self.img_list[index])
        label_path = os.path.join(self.label_path,self.label_list[index])
        with open(label_path,'r') as f:
            label = f.read()
        return img_path, label
    def __len__(self):
        length = len(self.img_list)
        return length

if __name__ == '__main__':
    # 输出图片
    img_path = '../dataset_excersize/train/ants_image/0013035.jpg'
    img = Image.open(img_path)
    img.show()

    # 将图片集文件地址
    dir_path = '../dataset_excersize/train/ants_image'

    # 将文件夹下所有东西（名称）变成列表
    dir_path_list = os.listdir(dir_path)

    # 因而，我们还需要他的文件夹地址，跟他组装，形成图片的地址
    root_dir = '../dataset_excersize/train'
    ants_img_dir = 'ants_image'
    bees_img_dir = "bees_image"
    
    ants_label_dir = 'ants_label'
    bees_label_dir = 'bees_label'

    ants_data =Mydata(root_dir,ants_img_dir,ants_label_dir)
    img = Image.open(ants_data.__getitem__(1)[0])
    img.show()
    
    print("图片数量为：",ants_data.__len__())

    # 可以直接用索引
    print(ants_data[1][0])
    print(ants_data[1][1])
    # len也一样
    print("图片数量为：",len(ants_data))

    bees_data = Mydata(root_dir,bees_img_dir,bees_label_dir)

    # 数据集拼接
    train_data = bees_data+ants_data
    print(train_data[0][0])
    print(train_data[0][1])
