# PyTorch 学习笔记预览（重写版）

我基于 `src` 目录下的 `ch1` 到 `ch16` 代码重写了这份预览版，同时完整覆盖 `note.md` 中已有内容与 `todo`。我写这份笔记的目标不是只做摘抄，而是把每一章里第一次出现的核心类、函数、对象、参数、调用方式、典型场景和注意点都整理清楚，便于后续回看代码时能直接对上。

## 0. 总体说明

- `note.md` 里提到的章节主题已经全部保留，没有删减。
- 我已经按“补充概念 + 参数解释 + 调用方式 + 使用场景 + 官方文档链接”的方式把 `todo` 展开。
- 除了 `note.md` 里已有的 `ch1` 到 `ch15`，我这里额外把 `src/ch16使用GPU训练2.py` 也纳入说明，因为它已经是我代码的一部分。
- 文中我会用“当前代码写法”和“我更推荐的写法”来区分：前者描述我现在的脚本，后者补充更稳妥、更规范的 PyTorch 用法。

## 1. 常用库、模块与函数来源

### 1.1 这些库分别负责什么

- `torch`
  - PyTorch 的核心库，负责张量创建、形状变换、自动求导、设备管理、序列化等。
  - 例如：`torch.tensor`、`torch.reshape`、`torch.argmax`、`torch.no_grad`、`torch.save`、`torch.load`、`torch.device`。
- `torch.nn`
  - 神经网络模块库，负责定义层、激活函数、损失函数和模型基类。
  - 例如：`nn.Module`、`nn.Conv2d`、`nn.Linear`、`nn.MaxPool2d`、`nn.ReLU`、`nn.CrossEntropyLoss`。
- `torch.nn.functional`
  - 无状态函数版网络操作，通常没有需要学习的参数。
  - 例如：`torch.nn.functional.conv2d`。
  - 可以理解为“直接做一次运算”，而不是“先构造一个层对象再反复调用”。
- `torch.optim`
  - 优化器模块，负责根据梯度更新参数。
  - 例如：`torch.optim.SGD`、`torch.optim.Adam`。
- `torch.utils.data`
  - 数据集与数据加载工具。
  - 例如：`Dataset`、`DataLoader`。
- `torch.utils.tensorboard`
  - 把标量、图片、模型图等写入 TensorBoard 日志。
  - 例如：`SummaryWriter`。
- `torchvision`
  - 视觉领域扩展库，包含数据集、图像变换、预训练模型等。
- `torchvision.datasets`
  - 现成数据集。
  - 例如：`torchvision.datasets.CIFAR10`。
- `torchvision.transforms`
  - 图像预处理与数据增强。
  - 例如：`ToTensor`、`Resize`、`Normalize`、`Compose`、`RandomCrop`。
- `torchvision.models`
  - 现成网络模型。
  - 例如：`torchvision.models.vgg16`。
- `PIL.Image`
  - 图像读取与显示，经常作为 `transforms` 的输入。
- `numpy`
  - 数组库，经常与图片可视化、格式转换一起出现。
- `cv2`
  - OpenCV 图像处理库，`cv2.imread` 返回 `numpy.ndarray`。
- `os`
  - Python 标准库，用来拼路径、列目录、判断文件是否存在。
- `time`
  - Python 标准库，用来统计训练耗时。
- `multiprocessing.freeze_support`
  - Windows 下多进程启动辅助函数，`DataLoader(num_workers>0)` 时经常会用到。

### 1.2 常见函数从哪个模块来

- `torch.tensor`、`torch.reshape`、`torch.argmax`、`torch.no_grad`、`torch.save`、`torch.load`、`torch.device` 来自 `torch`
- `nn.Module`、`nn.Conv2d`、`nn.MaxPool2d`、`nn.Flatten`、`nn.Linear`、`nn.Sequential`、`nn.ReLU`、`nn.Sigmoid`、`nn.L1Loss`、`nn.MSELoss`、`nn.CrossEntropyLoss` 来自 `torch.nn`
- `conv2d` 的函数式版本来自 `torch.nn.functional`
- `Dataset`、`DataLoader` 来自 `torch.utils.data`
- `SummaryWriter` 来自 `torch.utils.tensorboard`
- `CIFAR10` 来自 `torchvision.datasets`
- `ToTensor`、`Resize`、`Normalize`、`Compose`、`RandomCrop` 来自 `torchvision.transforms`
- `vgg16` 来自 `torchvision.models`

### 1.3 常见 Python 内置函数

- `print(...)`
  - 打印变量、形状、损失值和调试信息
- `len(obj)`
  - 获取长度，例如数据集大小、文件名列表长度
- `range(n)`
  - 生成整数序列，常用于 epoch 循环和重复实验
- `type(obj)`
  - 查看对象类型，例如判断当前是 `PIL.Image` 还是 `numpy.ndarray`
- `iter(obj)`
  - 把可迭代对象变成迭代器，例如 `iter(dataloader)`
- `next(it)`
  - 从迭代器中取下一个元素，例如拿到第一个 batch

这些函数不是 PyTorch 专属，但在我的代码里出现得非常频繁。我把它们单独分出来，是为了避免后面阅读训练代码时把“Python 基础语法”和“PyTorch API”混在一起。

### 1.4 `help()` 与 `??`

- `help(obj)` 是 Python 自带帮助系统，可以看类、函数、方法的文档字符串。
- `obj??` 常见于 IPython / Jupyter，用来快速查看对象说明或源代码。
- 我这套代码里常见可查询对象：

```python
help(torchvision.datasets.CIFAR10)
help(torchvision.transforms.Resize)
help(torch.nn.Conv2d)
```

## ch1pytorch加载数据.py

### 1. 这一章在做什么

这一章在自己实现一个最基础的 `Dataset`，让程序知道：

- 数据放在哪里
- 一条数据怎么取
- 整个数据集一共有多少条

同时也顺手演示了几种数据组织形式：

- 图片文件名本身就带类别信息
- 单独用 `txt` 文件保存标签

当前代码选择的是第二种：图片路径和标签文本文件分开存放。

### 2. `Dataset` 与 `DataLoader` 的分工

- `Dataset`
  - 定义“单条数据怎么取”。
  - 重点是 `__getitem__` 和 `__len__`。
- `DataLoader`
  - 定义“训练时一批数据怎么取”。
  - 重点是 `batch_size`、`shuffle`、`num_workers`、`drop_last`。

一句话概括：

- `Dataset` 处理样本级逻辑
- `DataLoader` 处理批量级逻辑

### 3. 当前代码里的自定义数据集类

```python
class Mydata(Dataset):
    def __init__(self, root_dir, img_dir, label_dir):
        ...

    def __getitem__(self, index):
        ...

    def __len__(self):
        ...
```

#### `__init__(self, root_dir, img_dir, label_dir)`

作用：

- 保存目录信息
- 生成图片目录和标签目录的完整路径
- 提前把文件名列表读出来，后面按索引取

参数：

- `root_dir`
  - 数据集根目录，例如 `../dataset_excersize/train`
- `img_dir`
  - 图片子目录，例如 `ants_image`
- `label_dir`
  - 标签子目录，例如 `ants_label`

当前代码里用到的函数：

- `os.path.join(a, b, ...)`
  - 作用：拼接路径，避免手写 `/` 或 `\\`
  - 场景：跨平台路径处理
- `os.listdir(path)`
  - 作用：列出目录下所有文件名
  - 场景：批量读取图片或标签文件名

#### `__getitem__(self, index)`

作用：

- 根据索引拿到一条样本

当前代码返回值：

```python
return img_path, label
```

也就是：

- 图片路径字符串
- 标签文本字符串

注意：

- 我这份代码没有直接返回 `PIL.Image` 或 `Tensor`
- 所以它更像是“先把路径和标签拿出来看懂”，不是直接喂模型的最终版本

更常见的训练版写法通常是：

```python
img = Image.open(img_path)
label = int(...)
return img, label
```

或者进一步：

```python
img = transform(Image.open(img_path))
return img, label
```

#### `__len__(self)`

作用：

- 返回数据集长度

当前代码：

```python
length = len(self.img_list)
return length
```

这会告诉 PyTorch 这个数据集一共能取多少条。

### 4. 其他出现在本章的函数

- `Image.open(path)`
  - 作用：读取图片，返回 `PIL.Image`
  - 场景：图像文件读取
- `img.show()`
  - 作用：直接显示 `PIL.Image`
  - 注意：只适用于 `PIL.Image`，不适用于 `Tensor`
- `open(label_path, 'r')`
  - 作用：打开文本标签文件
- `f.read()`
  - 作用：读取整个文本内容
- `len(obj)`
  - 作用：获取列表、数据集等对象长度

### 5. 数据集相加

代码里有：

```python
train_data = bees_data + ants_data
```

这里不是简单的 Python 列表相加，而是 `Dataset` 的拼接。PyTorch 内部会返回一个 `ConcatDataset`，把两个数据集按顺序接在一起。

适用场景：

- 训练集由多个子数据集合并而成
- 想统一管理同结构但来源不同的数据

### 6. 图像的常见表示形式

- `PIL.Image`
  - 更适合读图、显示、传统图像处理
- `torch.Tensor`
  - 更适合送入神经网络计算

最常见转换链路：

```python
PIL.Image -> transforms.ToTensor() -> torch.Tensor
```

### 7. 官方文档

- `Dataset` / `DataLoader`：[https://docs.pytorch.org/docs/stable/data.html](https://docs.pytorch.org/docs/stable/data.html)
- `PIL.Image`：[https://pillow.readthedocs.io/en/stable/reference/Image.html](https://pillow.readthedocs.io/en/stable/reference/Image.html)
- `os`：[https://docs.python.org/3/library/os.html](https://docs.python.org/3/library/os.html)
- `os.path.join`：[https://docs.python.org/3/library/os.path.html#os.path.join](https://docs.python.org/3/library/os.path.html#os.path.join)
- `os.listdir`：[https://docs.python.org/3/library/os.html#os.listdir](https://docs.python.org/3/library/os.html#os.listdir)
- `open`：[https://docs.python.org/3/library/functions.html#open](https://docs.python.org/3/library/functions.html#open)

## ch2TensorBoard.py

### 1. 这一章在做什么

这章主要学习如何把训练过程中的内容写进 TensorBoard，包括：

- 标量：`add_scalar`
- 图像：`add_image`
- 多图：后面章节的 `add_images`
- 模型图：后面章节的 `add_graph`

TensorBoard 启动命令：

```bash
tensorboard --logdir=日志目录 --port=6006
```

说明：

- `--logdir` 指向日志目录
- `--port` 可以自己改，防止和别人的端口冲突
- 默认常用端口是 `6006`

### 2. `SummaryWriter`

当前代码：

```python
writer = SummaryWriter("../logs")
```

作用：

- 创建一个日志写入器

常用参数：

- `log_dir`
  - 日志保存目录
- `comment`
  - 额外标记
- `flush_secs`
  - 多久强制刷新一次缓存

典型场景：

- 记录 loss 曲线
- 记录 accuracy 曲线
- 可视化图片和网络结构

### 3. `add_scalar`

当前代码：

```python
for i in range(10):
    writer.add_scalar("y=x", i, i)
```

调用格式：

```python
writer.add_scalar(tag, scalar_value, global_step)
```

参数：

- `tag`
  - 曲线名，例如 `train_loss`
- `scalar_value`
  - 数值
- `global_step`
  - 横轴步数，通常是 batch 或 epoch

场景：

- 训练损失
- 测试损失
- 学习率
- 正确率

### 4. `add_image`

当前代码：

```python
img = Image.open(image_path)
img_array = np.array(img)
writer.add_image("test", img_array, 1, dataformats="HWC")
```

调用格式：

```python
writer.add_image(tag, img_tensor, global_step, dataformats="CHW")
```

参数：

- `tag`
  - 图片名
- `img_tensor`
  - 图像数据，可以是 `numpy.ndarray` 或 `torch.Tensor`
- `global_step`
  - 步数
- `dataformats`
  - 数据格式，例如 `HWC`、`CHW`

这里为什么写 `HWC`：

- `np.array(img)` 后得到的是 NumPy 数组
- 其形状通常是 `(H, W, C)`

### 5. `H / W / C` 的含义

- `H`
  - Height，高度
- `W`
  - Width，宽度
- `C`
  - Channel，通道数

常见格式：

- `HWC`
  - 常见于 `numpy`、`PIL`、很多传统图像处理库
- `CHW`
  - 常见于 PyTorch Tensor 图像

![1776657004228](image/note/1776657004228.png)

### 6. `writer.close()`

作用：

- 关闭日志写入器
- 确保缓存内容被完整写入磁盘

### 7. 官方文档

- `SummaryWriter`、`add_scalar`、`add_image`、`add_images`、`add_graph`：[https://docs.pytorch.org/docs/stable/tensorboard.html](https://docs.pytorch.org/docs/stable/tensorboard.html)
- `numpy.array`：[https://numpy.org/doc/stable/reference/generated/numpy.array.html](https://numpy.org/doc/stable/reference/generated/numpy.array.html)
- TensorBoard：[https://www.tensorflow.org/tensorboard/get_started](https://www.tensorflow.org/tensorboard/get_started)

## ch3tranforms.py

### 1. transforms 的使用思路

这一章的主线就是：

```python
创建变换对象 -> 把图片传进去 -> 得到变换后的结果
```

也就是先“实例化一个工具”，再“调用这个工具”。

### 2. `transforms.ToTensor()`

当前代码：

```python
tensor_trans = transforms.ToTensor()
img_tensor = tensor_trans(img)
```

作用：

- 把图片转成 `torch.Tensor`

常见输入：

- `PIL.Image`
- `numpy.ndarray`

常见输出：

- `torch.Tensor`

重要特性：

- 输入若是 `PIL.Image` 或 `uint8` 的 `numpy.ndarray`
- 结果通常会从 `HWC` 变成 `CHW`
- 像素范围通常从 `0~255` 变成 `0.0~1.0`

当前代码演示了两种输入：

```python
img = Image.open(img_path)
img_tensor = tensor_trans(img)
```

```python
img_cv = cv2.imread(img_path)
img_cv_tensor = tensor_trans(img_cv)
```

### 3. `cv2.imread`

作用：

- 用 OpenCV 读取图片

返回值：

- `numpy.ndarray`

注意：

- OpenCV 默认通道顺序是 `BGR`
- `PIL` 常见顺序是 `RGB`
- 如果后面颜色看起来不对，首先检查是不是 `BGR/RGB` 混了

### 4. `writer.add_image("tensor_img", img_tensor)`

这里能直接写，是因为：

- `img_tensor` 已经是 `Tensor`
- 且形状通常是 `CHW`
- 这正是 `add_image` 常见的默认输入格式

### 5. 官方文档

- `ToTensor`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.ToTensor.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.ToTensor.html)
- `cv2.imread`：[https://docs.opencv.org/4.x/d4/da8/group__imgcodecs.html](https://docs.opencv.org/4.x/d4/da8/group__imgcodecs.html)

## ch4rransorms常用.py

### 1. transform 对象为什么能像函数一样调用

代码中有很多这种写法：

```python
img_tensor = tran_to_tensor(img)
img_resize = trans_resize(img)
```

原因是这些类内部实现了 `__call__`，所以“对象名(参数)”就等价于调用这个对象。

### 2. `Normalize`

当前代码：

```python
tensor_normal = transforms.Normalize([0.5, 0.5, 0.5], [0.5, 0.5, 0.5])
img_tensor_nor = tensor_normal(img_tensor)
```

作用：

- 对 Tensor 做按通道标准化

计算公式：

```python
output = (input - mean) / std
```

参数：

- `mean`
  - 每个通道的均值
- `std`
  - 每个通道的标准差

输入要求：

- 一般是图像 Tensor
- 通道数要和 `mean/std` 的长度对应

场景：

- 让输入分布更稳定
- 配合预训练模型时，使用该模型对应的均值和方差

### 3. `Resize`

当前代码：

```python
trans_resize = transforms.Resize((512, 512))
img_resize = trans_resize(img)
```

作用：

- 调整图片尺寸

`size` 的两种常见写法：

- `Resize((h, w))`
  - 明确指定高和宽
- `Resize(512)`
  - 把短边缩放到 `512`，长边按比例变化

当前代码还演示了：

```python
trans_resize2 = transforms.Resize(512)
```

这不是“只设高度 512”，而是“短边等于 512”。

### 4. `Compose`

当前代码：

```python
resize_composor = transforms.Compose([trans_resize2, tran_to_tensor])
img1 = resize_composor(img)
```

作用：

- 把多个变换按顺序串起来

参数：

- 一个列表
- 列表中的每一项都应是可调用对象

执行顺序：

```python
img
-> Resize(512)
-> ToTensor()
-> 输出 Tensor
```

场景：

- 训练前预处理
- 训练时数据增强
- 测试时统一输入尺寸

### 5. `RandomCrop`

当前代码：

```python
tran_randomcrop = transforms.RandomCrop((400, 500))
compose_randomcrop = transforms.Compose([tran_to_tensor, tran_randomcrop])
```

作用：

- 从原图中随机裁出一块指定大小的区域

参数：

- `size`
  - 整数：输出正方形
  - 元组 `(h, w)`：输出指定高宽
- `padding`
  - 裁剪前先补边
- `pad_if_needed`
  - 原图太小时自动补边
- `fill`
  - 常数填充值
- `padding_mode`
  - 补边模式，例如 `constant`、`reflect`

使用场景：

- 数据增强
- 提高模型对局部位置变化的鲁棒性

### 6. 官方文档

- `Normalize`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Normalize.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Normalize.html)
- `Resize`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Resize.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Resize.html)
- `Compose`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Compose.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Compose.html)
- `RandomCrop`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.RandomCrop.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.RandomCrop.html)

## ch5torchvision的数据集使用.py

### 1. `torchvision.datasets.CIFAR10`

当前代码：

```python
train_set = torchvision.datasets.CIFAR10(
    root="../torch_dataset",
    train=True,
    transform=composor,
    download=True
)
```

作用：

- 加载 CIFAR10 数据集

每一条样本的返回值是：

```python
(image, target)
```

其中：

- `image` 是图像
- `target` 是类别下标

### 2. 构造参数

- `root`
  - 数据集下载或读取的根目录
- `train`
  - `True` 表示训练集
  - `False` 表示测试集
- `transform`
  - 对图像做变换
- `target_transform`
  - 对标签做变换
- `download`
  - 若本地没有，则自动下载

### 3. `transform` 对返回值的影响

当前代码用了：

```python
composor = torchvision.transforms.Compose([
    torchvision.transforms.ToTensor()
])
```

所以：

- 不加 `transform` 时，`img` 常常是 `PIL.Image`
- 加了 `ToTensor()` 后，`img` 就会变成 `torch.Tensor`

这也是为什么当前代码里：

```python
img, label = train_set[0]
img.show()
```

这在严格意义上并不适合 Tensor。`show()` 是 `PIL.Image` 的方法，不是 Tensor 的方法。

### 4. `classes`

当前代码：

```python
print(train_set.classes)
print(train_set.classes[label])
```

作用：

- `train_set.classes` 返回类别名称列表
- `train_set.classes[label]` 可把数字标签映射回类别名

例如：

- `label = 3`
- `train_set.classes[3] = "cat"`

这也是从 `target` 看具体种类时最常用的方法。

### 5. `target` 到类别名的常用写法

如果 `target` 来自 `DataLoader` 的一个 batch：

```python
imgs, target = next(iter(loader))
```

则可以这样看类别名：

```python
loader.dataset.classes[target[0].item()]
```

说明：

- `DataLoader` 本身不负责保存语义标签名
- 真正保存类别名的是它内部的 `dataset`

### 6. 官方文档

- `CIFAR10`：[https://docs.pytorch.org/vision/main/generated/torchvision.datasets.CIFAR10.html](https://docs.pytorch.org/vision/main/generated/torchvision.datasets.CIFAR10.html)
- `Compose`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Compose.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Compose.html)
- `ToTensor`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.ToTensor.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.ToTensor.html)

## ch6dataloader.py

### 1. `DataLoader` 的作用

`DataLoader` 负责把 `Dataset` 变成“可以按 batch 取数据”的对象。

更常见写法：

```python
from torch.utils.data import DataLoader
loader = DataLoader(...)
```

当前代码写法：

```python
from torch.utils.data import dataloader
loader = dataloader.DataLoader(...)
```

也能用，只是不如直接导入 `DataLoader` 常见。

### 2. 常用参数

```python
DataLoader(
    dataset,
    batch_size=1,
    shuffle=False,
    num_workers=0,
    drop_last=False
)
```

- `dataset`
  - 要加载的数据集
- `batch_size`
  - 每批多少样本
- `shuffle`
  - 每轮开始前是否打乱
- `num_workers`
  - 使用几个子进程并行加载数据
- `drop_last`
  - 最后一批不满时是否丢弃

### 3. `drop_last`

假设：

- 总样本数是 `100`
- `batch_size=64`

则会分成：

- 第 1 批：64
- 第 2 批：36

这时：

- `drop_last=True`
  - 最后 36 条直接丢弃
- `drop_last=False`
  - 保留最后这 36 条

当前代码分别构造了两种 DataLoader 用来对比。

### 4. 遍历方式

当前代码：

```python
for data in Not_Droplast_test_data_loader:
    imgs, targets = data
```

说明：

- `DataLoader` 是可迭代对象
- 每次循环拿到的是一个 batch
- `imgs` 是批量图片
- `targets` 是批量标签

如果是 CIFAR10 且 `batch_size=64`，常见形状为：

```python
imgs.shape == [64, 3, 32, 32]
```

### 5. `add_images`

当前代码：

```python
writer.add_images("Not_Droplast", imgs, step)
```

作用：

- 一次写入一个 batch 的多张图片

输入形状通常要求：

```python
[N, C, H, W]
```

### 6. `num_workers` 的现实说明

- `num_workers=0`
  - 最稳定，调试时最省事
- `num_workers>0`
  - 可能加速数据加载
  - 但在 Windows 下必须配合：

```python
if __name__ == "__main__":
    ...
```

否则容易报多进程启动错误

### 7. 官方文档

- `DataLoader` / `Dataset`：[https://docs.pytorch.org/docs/stable/data.html](https://docs.pytorch.org/docs/stable/data.html)

![1776995151779](image/note/1776995151779.png)

## ch7神经网络的骨架.py

### 1. `nn.Module`

PyTorch 中几乎所有自定义模型都继承自：

```python
torch.nn.Module
```

它的职责是：

- 管理子层
- 管理参数
- 统一前向调用方式

### 2. `__init__` 与 `forward`

模型类的标准结构是：

```python
class MyModule(nn.Module):
    def __init__(self):
        super().__init__()
        ...

    def forward(self, input):
        ...
```

分工：

- `__init__`
  - 定义层对象
- `forward`
  - 定义数据如何从输入流向输出

调用时：

```python
output = model(x)
```

这会自动触发：

```python
model.forward(x)
```

### 3. `torch.nn.functional.conv2d` 与 `nn.Conv2d`

当前代码同时演示了两种写法：

```python
torch.nn.functional.conv2d(input, kernel, padding=0, stride=(1, 2))
```

和

```python
nn.Conv2d(in_channels=1, out_channels=1, kernel_size=3)
```

区别：

- `F.conv2d`
  - 直接做一次卷积运算
  - 权重 `kernel` 由我手动传进去
  - 常用于理解公式、写函数式网络、做特殊运算
- `nn.Conv2d`
  - 创建一个“卷积层对象”
  - 权重由模块内部维护并参与训练
  - 更适合真正搭建模型

### 4. `nn.Conv2d`

当前代码里的典型参数：

```python
nn.Conv2d(in_channels=3, out_channels=6, kernel_size=3, stride=1, padding=0)
```

参数说明：

- `in_channels`
  - 输入通道数，例如 RGB 图像通常是 `3`
- `out_channels`
  - 卷积核个数，也就是输出通道数
- `kernel_size`
  - 卷积核大小
- `stride`
  - 步长
- `padding`
  - 填充
- `dilation`
  - 空洞卷积间隔
- `bias`
  - 是否带偏置

场景：

- 提取局部空间特征
- 图像分类、检测、分割中的基础层

### 5. `nn.MaxPool2d`

当前代码：

```python
torch.nn.MaxPool2d(kernel_size=3, ceil_mode=True)
```

参数说明：

- `kernel_size`
  - 池化窗口大小
- `stride`
  - 步长，不写时通常默认为 `kernel_size`
- `padding`
  - 补边
- `ceil_mode`
  - 是否向上取整计算输出大小
- `dilation`
  - 池化窗口元素的间隔

作用：

- 下采样
- 减少特征图尺寸
- 保留局部最强响应

### 6. `torch.tensor` 与 `torch.reshape`

当前代码：

```python
input = torch.tensor(data, dtype=torch.float32)
input = torch.reshape(input, [1, 1, 5, 5])
```

作用：

- `torch.tensor`
  - 从 Python 列表创建 Tensor
- `torch.reshape`
  - 改变张量形状，但不改变元素总数

常见场景：

- 手工构造测试样本
- 把二维数据变成卷积层期望的四维输入

### 7. 可视化卷积和池化结果

当前代码把输出 reshape 成 3 通道后再写入 TensorBoard：

```python
output = torch.reshape(output, (-1, 3, output.shape[2], output.shape[3]))
writer.add_images("output", output, step)
```

这样做的目的是：

- 让 TensorBoard 能按图片批次显示特征图

### 8. 官方文档

- `nn.Module`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html)
- `Conv2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Conv2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Conv2d.html)
- `MaxPool2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.MaxPool2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.MaxPool2d.html)
- `torch.nn.functional.conv2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.functional.conv2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.functional.conv2d.html)
- `torch.tensor`：[https://docs.pytorch.org/docs/stable/generated/torch.tensor.html](https://docs.pytorch.org/docs/stable/generated/torch.tensor.html)
- `torch.reshape`：[https://docs.pytorch.org/docs/stable/generated/torch.reshape.html](https://docs.pytorch.org/docs/stable/generated/torch.reshape.html)

## ch8非线性激活.py

### 1. 为什么要有激活函数

如果网络里只有线性层，那么多个线性层叠起来本质上还是一个线性变换，表达能力有限。激活函数的作用就是引入非线性。

### 2. `nn.ReLU`

当前代码：

```python
self.Relu1 = torch.nn.ReLU()
```

定义：

- `ReLU(x) = max(0, x)`

参数：

- `inplace=False`
  - 是否原地修改输入张量

输入输出：

- 输入形状基本不受限
- 输出形状与输入相同

场景：

- 现代卷积网络最常见激活函数之一
- 计算简单，梯度传播效果通常不错

### 3. `nn.Sigmoid`

当前代码：

```python
self.sigmoid1 = torch.nn.Sigmoid()
```

定义：

- `sigmoid(x) = 1 / (1 + e^{-x})`

输出范围：

- `0 ~ 1`

场景：

- 二分类输出概率
- 门控结构

注意：

- 深层网络中较少作为隐藏层主激活函数，因为容易梯度饱和

### 4. 当前代码的写法

我这里把激活函数再包了一层自定义模块：

```python
class MyRelu(torch.nn.Module):
    ...
```

这样做的意义主要是熟悉“层对象放在 `__init__`、前向逻辑写在 `forward`”这一套模型书写方式。

### 5. 官方文档

- `ReLU`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.ReLU.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.ReLU.html)
- `Sigmoid`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Sigmoid.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Sigmoid.html)

## ch9神经网络-线性层及其他层.py

这一章在我的 `note.md` 里有明确 `todo`，所以我在这里把“线性层、卷积层、池化层、正则化层、归一化层”都完整说明，即使当前代码并没有全部用到。

### 1. `nn.Linear`

当前代码核心：

```python
self.linear1 = nn.Linear(..., 10, bias=1)
```

更规范的参数写法应写成：

```python
nn.Linear(in_features, out_features, bias=True)
```

参数：

- `in_features`
  - 输入最后一维大小
- `out_features`
  - 输出最后一维大小
- `bias`
  - 是否加偏置，推荐写 `True/False`，不要写 `1/0`

作用：

- 做仿射变换：`y = xW^T + b`

场景：

- 分类器最后几层
- 卷积特征 flatten 后接全连接

当前代码思路：

- 先从 `DataLoader` 里拿一个 batch 看形状
- 再把整批图片 reshape 成一条超长向量后送入线性层

注意：

- `Linear` 只要求输入最后一维等于 `in_features`
- 前面可以有任意批维度

### 2. 卷积层

- 代码已在 `ch7` 和 `ch10` 中实际使用 `nn.Conv2d`
- 主要作用：提取局部空间特征

### 3. 池化层

- 代码已在 `ch7` 和 `ch10` 中使用 `nn.MaxPool2d`
- 主要作用：下采样、减少尺寸、增强局部平移不变性

### 4. 正则化层：`nn.Dropout`

虽然当前代码没有直接用，但 `note.md` 里提到了“将一部分神经网络输出随机变为 0，防止过拟合”，这对应的就是 `Dropout`。

典型写法：

```python
nn.Dropout(p=0.5)
```

参数：

- `p`
  - 置零概率
- `inplace`
  - 是否原地操作

作用：

- 训练时随机屏蔽一部分特征
- 缓解过拟合

注意：

- 只在 `train()` 模式下生效
- `eval()` 时会自动关闭随机丢弃

### 5. 归一化层：`nn.BatchNorm2d`

虽然当前代码没有直接用，但 `note.md` 中“归一化层”应补全。

典型写法：

```python
nn.BatchNorm2d(num_features)
```

参数：

- `num_features`
  - 通道数
- `eps`
  - 防止除零的小常数
- `momentum`
  - 运行均值和方差的更新系数
- `affine`
  - 是否学习缩放和平移参数

作用：

- 稳定特征分布
- 常常帮助更快收敛

### 6. `iter()` 和 `next()`

当前代码：

```python
imgs = next(iter(dataloader))[0]
```

含义：

- `iter(dataloader)` 先创建迭代器
- `next(...)` 再取出第一个 batch

场景：

- 临时检查形状
- 手动看第一批数据

### 7. 官方文档

- `Linear`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Linear.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Linear.html)
- `Dropout`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Dropout.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Dropout.html)
- `BatchNorm2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.BatchNorm2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.BatchNorm2d.html)

## ch10sequential搭建神经网络.py

### 1. `nn.Sequential`

当前代码把多层网络写成：

```python
self.model = nn.Sequential(
    nn.Conv2d(...),
    nn.MaxPool2d(...),
    nn.Conv2d(...),
    nn.MaxPool2d(...),
    nn.Conv2d(...),
    nn.MaxPool2d(...),
    nn.Flatten(),
    nn.Linear(...),
    nn.Linear(...)
)
```

作用：

- 把一串按顺序执行的层打包成一个整体

适合场景：

- 结构简单、前向流程线性的网络

不太适合：

- 有分支
- 有跳连
- 前向逻辑需要条件判断

### 2. `nn.Flatten`

作用：

- 把多维特征图摊平成一维，通常用于卷积层接全连接层

当前代码里：

- 卷积和池化后得到 `[N, 64, 4, 4]`
- `Flatten()` 后变成 `[N, 64*4*4]`

### 3. 这份网络结构的流动过程

输入是 CIFAR10 图片：

```python
[N, 3, 32, 32]
```

经过三次卷积和池化后，空间尺寸被压缩，再接两层全连接，最终输出：

```python
[N, 10]
```

这 10 个值就是 10 个类别的 logits。

### 4. `writer.add_graph`

当前代码：

```python
writer.add_graph(Mynet, input)
```

作用：

- 将模型计算图写入 TensorBoard

参数：

- `model`
  - 模型对象
- `input_to_model`
  - 一组示例输入

场景：

- 检查网络结构是否符合预期
- 学习每层的连接关系

### 5. `named_parameters()`

`note.md` 里提到要介绍 `named_parameters()`。

作用：

- 迭代得到“参数名 + 参数值”

常见写法：

```python
for name, param in model.named_parameters():
    print(name, param.shape)
```

用途：

- 看每层权重名字
- 定位某一层参数
- 调试梯度和权重更新

和它对应的还有：

```python
model.parameters()
```

区别：

- `parameters()`
  - 只给参数值
- `named_parameters()`
  - 给“参数名 + 参数值”

### 6. 官方文档

- `Sequential`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Sequential.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Sequential.html)
- `Flatten`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Flatten.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Flatten.html)
- `Module.named_parameters`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html)

## ch11反向传播与损失函数.py

### 1. 三个常见损失函数

#### `nn.L1Loss`

当前代码：

```python
loss = torch.nn.L1Loss()
print(loss(tensor1, tensor2))
```

含义：

- 平均绝对误差

公式：

```text
L = mean(|x - y|)
```

常用参数：

- `reduction`
  - `'mean'`、`'sum'`、`'none'`

适用场景：

- 对离群值相对更稳健

#### `nn.MSELoss`

当前代码：

```python
loss_MSE = torch.nn.MSELoss()
```

含义：

- 均方误差

公式：

```text
L = mean((x - y)^2)
```

适用场景：

- 回归问题

#### `nn.CrossEntropyLoss`

当前代码：

```python
loss_cross = torch.nn.CrossEntropyLoss()
```

作用：

- 多分类最常用损失函数之一

输入输出要求：

- 输入通常是 logits，形状 `[N, C]`
- 标签通常是类别下标，形状 `[N]`

当前代码里还出现了：

```python
loss_cross(torch.tensor(data1, dtype=torch.float32), tensor3)
```

这里 `tensor3` 是浮点张量，属于“软标签 / 概率分布”形式。现代 PyTorch 支持这种情况，但入门阶段更常见的是整数类别标签。

注意：

- `CrossEntropyLoss` 内部已经包含 `log_softmax`
- 所以一般不要在前面手动再做一次 `softmax`

### 2. 反向传播：`loss.backward()`

当前代码：

```python
result_loss.backward()
```

作用：

- 根据损失值对网络参数求梯度
- 梯度会累计到每个参数的 `.grad` 中

重要说明：

- `backward()` 只负责算梯度
- 不负责更新参数
- 真正更新参数要交给优化器的 `step()`

### 3. `loss.item()`

后续章节出现了：

```python
result.item()
```

作用：

- 把只包含一个元素的 Tensor 取成普通 Python 数字

场景：

- 打印日志
- 累加 epoch 损失

### 4. 自动求导图

`note.md` 里写到“损失结果也是张量，会自动保存计算图，便于反向传播”，这点理解成下面这句话最准确：

- 只要张量参与了需要梯度的计算，PyTorch 就会记录这条计算链
- `backward()` 时就能沿这条链把梯度传回去

### 5. 官方文档

- `L1Loss`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.L1Loss.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.L1Loss.html)
- `MSELoss`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.MSELoss.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.MSELoss.html)
- `CrossEntropyLoss`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.CrossEntropyLoss.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.CrossEntropyLoss.html)
- `Tensor.backward`：[https://docs.pytorch.org/docs/stable/generated/torch.Tensor.backward.html](https://docs.pytorch.org/docs/stable/generated/torch.Tensor.backward.html)
- `Tensor.item`：[https://docs.pytorch.org/docs/stable/generated/torch.Tensor.item.html](https://docs.pytorch.org/docs/stable/generated/torch.Tensor.item.html)

## ch12优化器.py

### 1. 训练时的标准三步

当前代码已经体现出 PyTorch 训练的经典顺序：

```python
optimizer.zero_grad()
loss.backward()
optimizer.step()
```

含义：

1. 清空旧梯度
2. 计算新梯度
3. 按优化器规则更新参数

### 2. `model.parameters()`

当前代码：

```python
torch.optim.Adam(self.model.parameters(), lr=0.01)
```

作用：

- 把模型里所有可训练参数交给优化器

如果只想看参数名和值：

```python
for name, param in model.named_parameters():
    ...
```

### 3. 如何看权重、偏置与梯度

`note.md` 里要求补充 `.weight.data`、`.weight.grad`、`.bias` 等内容，这里统一说明：

- `layer.weight`
  - 权重参数对象
- `layer.weight.data`
  - 权重当前数值
- `layer.weight.grad`
  - 权重梯度
- `layer.bias`
  - 偏置参数对象
- `layer.bias.data`
  - 偏置当前数值
- `layer.bias.grad`
  - 偏置梯度

示例：

```python
print(model.linear1.weight.data.shape)
print(model.linear1.weight.grad)
print(model.linear1.bias.data)
```

对于 `nn.Sequential`，也可以像数组一样索引：

```python
print(model.model[0].weight.data.shape)
```

### 4. `torch.optim.SGD`

常见写法：

```python
torch.optim.SGD(params, lr=0.01, momentum=0.9)
```

常见参数：

- `params`
  - 待优化参数
- `lr`
  - 学习率
- `momentum`
  - 动量
- `weight_decay`
  - 权重衰减
- `nesterov`
  - 是否使用 Nesterov 动量

适用场景：

- 结构简单
- 想更可控地调学习率和泛化

### 5. `torch.optim.Adam`

当前代码使用：

```python
torch.optim.Adam(self.model.parameters(), lr=lr)
```

常见参数：

- `params`
  - 待优化参数
- `lr`
  - 学习率
- `betas`
  - 一阶、二阶动量系数
- `eps`
  - 数值稳定项
- `weight_decay`
  - 权重衰减

适用场景：

- 入门阶段最常用
- 收敛通常比较快
- 对超参数通常不那么敏感

### 6. SGD 与 Adam 的区别

- `SGD`
  - 更新规则简单
  - 常需要更仔细调学习率
  - 泛化能力很多时候表现不错
- `Adam`
  - 自适应学习率
  - 收敛更快，开箱即用性强
  - 深度学习入门和快速实验很常见

### 7. `zero_grad()` 为什么必须有

因为 PyTorch 默认是“梯度累加”：

- 第一次 `backward()` 后，梯度存在 `.grad`
- 第二次再 `backward()`，默认会在原来基础上继续加

所以每轮更新前通常都要：

```python
optimizer.zero_grad()
```

### 8. 官方文档

- `SGD`：[https://docs.pytorch.org/docs/stable/generated/torch.optim.SGD.html](https://docs.pytorch.org/docs/stable/generated/torch.optim.SGD.html)
- `Adam`：[https://docs.pytorch.org/docs/stable/generated/torch.optim.Adam.html](https://docs.pytorch.org/docs/stable/generated/torch.optim.Adam.html)
- `torch.optim`：[https://docs.pytorch.org/docs/stable/optim.html](https://docs.pytorch.org/docs/stable/optim.html)

## ch13网络模型.py

### 1. `torchvision.models.vgg16`

当前代码使用旧写法：

```python
torchvision.models.vgg16(pretrained=True)
```

这能表达我的学习目标，但当前官方文档里我更倾向于使用下面这种新版写法：

```python
torchvision.models.vgg16(weights="DEFAULT")
```

当前官方参数核心是：

- `weights`
  - 预训练权重
- `progress`
  - 是否显示下载进度条

我笔记里的 `pretrained`、`prosess`，整理后应理解为：

- 旧版常写 `pretrained=True/False`
- 当前我更推荐写 `weights=...`
- `progress=True` 表示显示下载进度

### 2. `add_module`

当前代码：

```python
vgg16_true.add_module(name="add_linear", module=torch.nn.Linear(1000, 10))
```

作用：

- 在模块末尾手动追加一个子模块

参数：

- `name`
  - 子模块名字
- `module`
  - 要加进去的层对象

场景：

- 研究模型结构
- 手动在模型尾部挂层

### 3. 直接修改分类头

当前代码：

```python
vgg16_false.classifier[6] = torch.nn.Linear(4096, 10)
```

这比 `add_module()` 更符合“改分类头”的实际需求，因为：

- VGG16 的最后一层本来就是 `classifier[6]`
- 直接替换就能把 `1000` 类改成 `10` 类

### 4. 保存与加载模型：两种方式

#### 方式 1：保存整个模型对象

```python
torch.save(vgg16_true, "../pretrained_model/vgg16_true1.pth")
model = torch.load("../pretrained_model/vgg16_true1.pth", weights_only=False)
```

优点：

- 简单直接

缺点：

- 依赖原始类结构
- 跨环境、跨版本兼容性相对差

#### 方式 2：只保存参数字典

```python
torch.save(vgg16_false.state_dict(), "../pretrained_model/vgg16_false.pth")
```

再加载：

```python
vgg16_load = torchvision.models.vgg16(pretrained=False)
vgg16_load.classifier[6] = torch.nn.Linear(4096, 10)
vgg16_load.load_state_dict(torch.load("../pretrained_model/vgg16_false.pth"))
```

优点：

- 我更推荐
- 更稳健
- 更适合项目开发

注意：

- 必须先构造出同结构模型
- `load_state_dict()` 只负责填参数，不负责创建层结构

### 5. `state_dict()`

作用：

- 返回一个字典，里面保存模型所有可学习参数和缓冲区

场景：

- 保存模型参数
- 迁移学习
- 断点续训

### 6. `argmax`

`note.md` 中提到“Argmax 找到最大值下标”，这在分类里非常常见：

```python
pred = logits.argmax(dim=1)
```

作用：

- 在类别维上取最大值所在位置
- 这个位置就是预测类别编号

### 7. `train()` 与 `eval()`

- `model.train()`
  - 训练模式
- `model.eval()`
  - 推理 / 测试模式

区别尤其体现在：

- `Dropout`
- `BatchNorm`

这两个层在训练和测试阶段行为不同，所以训练前最好 `train()`，测试前最好 `eval()`。

### 8. 官方文档

- `vgg16`：[https://docs.pytorch.org/vision/main/models/generated/torchvision.models.vgg16.html](https://docs.pytorch.org/vision/main/models/generated/torchvision.models.vgg16.html)
- `torch.save`：[https://docs.pytorch.org/docs/stable/generated/torch.save.html](https://docs.pytorch.org/docs/stable/generated/torch.save.html)
- `torch.load`：[https://docs.pytorch.org/docs/stable/generated/torch.load.html](https://docs.pytorch.org/docs/stable/generated/torch.load.html)
- `Module.state_dict` / `load_state_dict`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html)
- `torch.argmax`：[https://docs.pytorch.org/docs/stable/generated/torch.argmax.html](https://docs.pytorch.org/docs/stable/generated/torch.argmax.html)

## ch14完整的模型训练套路.py

### 1. 这章的意义

这一章把前面分散的内容串成了完整训练流程：

- 准备训练集和测试集
- 建立 `DataLoader`
- 定义模型
- 定义损失函数和优化器
- 训练
- 测试
- 记录 TensorBoard
- 保存模型

### 2. 模型类 `MyNetWork`

当前代码在 `__init__` 里定义了三部分：

- `self.model`
  - 网络本体，`nn.Sequential(...)`
- `self.Loss`
  - 损失函数对象，`nn.CrossEntropyLoss()`
- `self.optim`
  - 优化器对象，`torch.optim.Adam(...)`

这种写法的好处是：

- 把“模型 + 损失 + 优化器”集中到一个类里，便于演示

但从工程角度看，我通常更倾向于这样写：

- 模型单独一个类
- 损失函数和优化器在训练脚本里创建

### 3. `os.path.exists`

当前代码：

```python
if os.path.exists("../pretrained_model/ch14_model.pth"):
    mynet = torch.load(...)
```

作用：

- 检查模型文件是否已存在

场景：

- 断点续训
- 避免重复训练

### 4. 训练阶段

当前代码核心：

```python
for data in train_dataloader:
    imgs, target = data
    imgs = mynet(imgs)
    result = mynet.loss(imgs, target)
    mynet.optim.zero_grad()
    result.backward()
    mynet.optim.step()
```

流程：

1. 取一个 batch
2. 前向传播
3. 计算损失
4. 清梯度
5. 反向传播
6. 更新参数

### 5. 正确率计算

当前代码：

```python
acurracy += (imgs.argmax(1) == target).sum()
```

解释：

- `imgs.argmax(1)`
  - 对类别维取最大值下标
- `== target`
  - 与真实标签比较
- `.sum()`
  - 统计预测正确的样本数

### 6. 测试阶段与 `torch.no_grad()`

当前代码：

```python
mynet.eval()
with torch.no_grad():
    ...
```

作用：

- `eval()`
  - 切换到测试模式
- `torch.no_grad()`
  - 关闭梯度记录，节省显存和计算

### 7. TensorBoard 记录

当前代码：

```python
writer.add_scalar("train_loss", loss_result_train, i)
writer.add_scalar("train_accuracy", ..., i)
writer.add_scalar("test_loss", loss_result_test, i)
writer.add_scalar("test_accuary", ..., i)
```

这能在每个 epoch 记录训练和测试的损失、正确率。

### 8. 我这份代码里的一个细节

当前 `DataLoader` 使用了：

```python
drop_last=True
```

但正确率分母仍然使用：

```python
train_size = len(train_dataset)
test_size = len(test_dataset)
```

这意味着：

- 最后一批被丢掉了
- 分母却还是全数据集大小

因此算出的正确率会略微偏低。更严谨的做法是记录实际参与计算的样本数。

### 9. 过拟合说明

我在 `note.md` 中已经写到“训练数据过小，存在过拟合”，这和图中现象一致：

- 训练集表现持续变好
- 测试集指标不跟着同步改善

这就是典型的过拟合信号。

![1777188446740](image/note/1777188446740.png)
![1777188764506](image/note/1777188764506.png)
![1777188818210](image/note/1777188818210.png)
![1777188833423](image/note/1777188833423.png)
![1777188853266](image/note/1777188853266.png)
![1777188864510](image/note/1777188864510.png)

### 10. 官方文档

- `torch.no_grad`：[https://docs.pytorch.org/docs/stable/generated/torch.no_grad.html](https://docs.pytorch.org/docs/stable/generated/torch.no_grad.html)
- `Adam`：[https://docs.pytorch.org/docs/stable/generated/torch.optim.Adam.html](https://docs.pytorch.org/docs/stable/generated/torch.optim.Adam.html)
- `CrossEntropyLoss`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.CrossEntropyLoss.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.CrossEntropyLoss.html)

## ch15使用GPU训练1.py

### 1. GPU 训练的核心思想

我笔记里的主线写成：

```text
网络模型 -> 数据 -> 损失函数 -> .cuda()
```

更准确地说，是把“会参与 GPU 计算的张量或模块”移动到同一个设备上。

包括：

- 模型
- 输入数据 `imgs`
- 标签 `target`
- 损失函数内部需要参与设备计算的部分

不包括：

- `DataLoader` 本体
- 优化器对象本体

### 2. `.cuda()`

当前代码有：

```python
mynet.cuda()
imgs = imgs.cuda()
target = target.cuda()
self.Loss = nn.CrossEntropyLoss().cuda()
```

作用：

- 把模块或 Tensor 移到当前 CUDA 设备

适用对象：

- `Tensor`
- `nn.Module`

限制：

- 只适用于 CUDA
- 如果我以后想写 CPU/GPU 通用代码，我会更倾向于 `.to(device)`

### 3. `num_workers` 与速度

我的笔记里提到“4060 训练时间可以通过 `num_workers` 改变”，这个方向对，但还需要补一句现实情况：

- `num_workers` 影响的是数据加载速度
- 不是直接让模型计算变快
- 对 CIFAR10 这种小图和小模型，`num_workers` 不一定明显提速
- Windows 下 `num_workers>0` 还要处理多进程入口问题

所以：

- `num_workers` 是“可能有帮助”的调参项
- 不是 GPU 训练提速的唯一来源

### 4. `freeze_support()` 与 Windows 多进程

当前 `ch15` 新版代码里已经加了：

```python
from multiprocessing import freeze_support

if __name__ == "__main__":
    freeze_support()
    main()
```

这是因为在 Windows 下，`DataLoader(num_workers>0)` 需要主入口保护，否则容易出现“启动子进程前主进程还没完成初始化”的报错。

### 5. `time.time()`

当前代码用它来统计总耗时：

```python
start_time = time.time()
...
end_time = time.time()
```

结果：

```python
end_time - start_time
```

就是总训练时长。

### 6. 加载 GPU 训练好的模型到 CPU

我笔记里提到：

```python
torch.load(root, map_location=torch.device("cpu"))
```

这是对的。

作用：

- 当模型保存时来自 GPU
- 但当前机器只想在 CPU 上加载

就需要用 `map_location` 显式映射设备。

### 7. 官方文档

- `Tensor.cuda`：[https://docs.pytorch.org/docs/stable/generated/torch.Tensor.cuda.html](https://docs.pytorch.org/docs/stable/generated/torch.Tensor.cuda.html)
- `torch.load`：[https://docs.pytorch.org/docs/stable/generated/torch.load.html](https://docs.pytorch.org/docs/stable/generated/torch.load.html)
- `time.time`：[https://docs.python.org/3/library/time.html#time.time](https://docs.python.org/3/library/time.html#time.time)
- `multiprocessing.freeze_support`：[https://docs.python.org/3/library/multiprocessing.html#multiprocessing.freeze_support](https://docs.python.org/3/library/multiprocessing.html#multiprocessing.freeze_support)

![1777190638483](image/note/1777190638483.png)

## ch16使用GPU训练2.py

### 1. `torch.device`

当前代码：

```python
device = torch.device("cuda:0")
```

常见写法：

- `torch.device("cpu")`
- `torch.device("cuda")`
- `torch.device("cuda:0")`

说明：

- `"cpu"`：强制放 CPU
- `"cuda"`：当前默认 GPU
- `"cuda:0"`：第 0 块 GPU

### 2. `.to(device)`

我这份当前代码想表达的核心是：

```python
tensor = tensor.to(device)
model = model.to(device)
```

作用：

- 把 Tensor 或模块移动到指定设备

优点：

- CPU / GPU 通用
- 多卡写法统一

比 `.cuda()` 更通用。

### 3. 我更常用的 GPU 通用模板

当前 `ch16` 的思路是对的，但训练时我更倾向于这样写：

```python
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
model = MyNetWork().to(device)

for imgs, target in train_dataloader:
    imgs = imgs.to(device)
    target = target.to(device)
    outputs = model(imgs)
    loss = criterion(outputs, target)
```

推荐原因：

- 先把模型放到设备上
- 再把输入和标签放到同一设备
- 最后才前向传播

这比“先前向，再 `.to(device)`”更正确。

### 4. `.cuda()` 与 `.to(device)` 的区别

- `.cuda()`
  - 只面向 CUDA
  - 写法简单
- `.to(device)`
  - 更通用
  - 同时适合 CPU、单卡 GPU、多卡环境

在工程代码里，我通常更倾向于使用 `.to(device)`。

### 5. 官方文档

- `torch.device`：[https://docs.pytorch.org/docs/stable/tensor_attributes.html#torch-device](https://docs.pytorch.org/docs/stable/tensor_attributes.html#torch-device)
- `Tensor.to`：[https://docs.pytorch.org/docs/stable/generated/torch.Tensor.to.html](https://docs.pytorch.org/docs/stable/generated/torch.Tensor.to.html)API 官方文档速查表

## 补充：命令行训练脚本 `train.py`

这一节不是来自我当前仓库里的现成文件，而是我补充的一种常见训练脚本写法。虽然我现在没有真正写 `train.py`，但以后看别人的项目时，经常会遇到这种命令行入口，所以我单独把它记下来。

### 1. 一个常见的训练命令

最基础的形式经常写成：

```bash
python train.py --dataroot ./data --name exp1 --model cnn
```

如果再补充一些常见训练参数，通常会变成：

```bash
python train.py --dataroot ./data --name exp1 --model cnn --batch_size 64 --lr 0.001 --epochs 30
```

### 2. 这些参数分别是什么意思

#### `python train.py`

作用：

- 用 Python 运行训练脚本 `train.py`

这个文件通常是整个项目的训练入口。运行之后，程序一般会继续做这些事：

- 解析命令行参数
- 构造数据集和 `DataLoader`
- 创建模型
- 创建损失函数和优化器
- 执行训练循环
- 保存日志和模型权重

#### `--dataroot`

示例：

```bash
--dataroot ./data
```

作用：

- 指定数据集根目录

我一般把它理解成：

- “去哪个目录里找训练数据和测试数据”

常见场景：

- 数据目录不写死在代码里，而是在启动训练时手动指定
- 同一份代码可以训练不同位置的数据

#### `--name`

示例：

```bash
--name exp1
```

作用：

- 给这次实验起一个名字

这个名字经常会被用在：

- 日志目录
- 模型保存目录
- TensorBoard 运行目录
- 输出结果目录

例如：

- `runs/exp1`
- `checkpoints/exp1`

我通常把它理解成：

- “这次训练任务的代号”

#### `--model`

示例：

```bash
--model cnn
```

作用：

- 指定要训练哪个模型

常见写法：

- `--model cnn`
- `--model resnet18`
- `--model vgg16`
- `--model unet`

这个参数通常会影响：

- 程序实例化哪个网络类
- 是否加载对应预训练权重
- 分类头或输出层是否需要调整

我通常把它理解成：

- “这次训练到底用哪种网络结构”

#### 其他经常一起出现的参数

- `--batch_size 64`
  - 每个 batch 的样本数
- `--lr 0.001`
  - 学习率
- `--epochs 30`
  - 训练轮数
- `--gpu_ids 0`
  - 使用哪块 GPU
- `--save_freq 5`
  - 每隔多少轮保存一次模型

### 3. 这些参数在代码里通常怎么被接收

这种命令行参数最常见的来源是 Python 标准库 `argparse`。

一个最小示例通常会这样写：

```python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--dataroot", type=str, required=True, help="数据集根目录")
parser.add_argument("--name", type=str, default="exp1", help="实验名称")
parser.add_argument("--model", type=str, default="cnn", help="模型名称")
parser.add_argument("--batch_size", type=int, default=64, help="批大小")
parser.add_argument("--lr", type=float, default=0.001, help="学习率")
parser.add_argument("--epochs", type=int, default=30, help="训练轮数")

args = parser.parse_args()
```

上面这些 `add_argument(...)` 里，除了参数名本身，最常见的几个附加参数就是 `type`、`required`、`default`、`help`。

#### `required`

例如：

```python
parser.add_argument("--dataroot", type=str, required=True, help="数据集根目录")
```

作用：

- 表示这个参数是必填的

含义：

- 如果我运行训练脚本时没有写 `--dataroot ...`
- 程序就会直接报错，不会正常开始训练

适用场景：

- 数据路径
- 必须显式指定的配置项

#### `help`

例如：

```python
parser.add_argument("--dataroot", type=str, required=True, help="数据集根目录")
```

作用：

- 给这个参数写帮助说明

它主要给谁看：

- 给运行脚本的人看

最常见的触发方式：

```bash
python train.py --help
```

这时终端通常会显示类似：

```bash
--dataroot DATAROOT   数据集根目录
```

也就是说，`help` 不是给训练逻辑用的，而是给命令行说明文字用的。

#### `default`

我这里顺手补充一下这个参数。

例如：

```python
parser.add_argument("--name", type=str, default="exp1", help="实验名称")
parser.add_argument("--batch_size", type=int, default=64, help="批大小")
```

作用：

- 给这个参数设置默认值

含义：

- 如果我运行脚本时没有手动写这个参数
- 程序就自动使用这里设定的值

例如：

```bash
python train.py --dataroot ./data
```

如果命令里没有写：

- `--name`
- `--batch_size`

那么程序内部通常会自动得到：

- `args.name == "exp1"`
- `args.batch_size == 64`

适用场景：

- 大多数情况下都有一个常用值
- 参数可以省略，但仍然需要有合理默认行为

#### `required` 和 `default` 的区别

- `required=True`
  - 不传就报错
- `default=...`
  - 不传就使用默认值

通常来说：

- 很关键、不能省略的参数适合用 `required=True`
- 有常见默认配置的参数适合用 `default=...`

运行后：

- `args.dataroot` 对应 `--dataroot`
- `args.name` 对应 `--name`
- `args.model` 对应 `--model`
- `args.batch_size` 对应 `--batch_size`
- `args.lr` 对应 `--lr`

### 4. 这些参数“之后”通常会发生什么

如果我执行：

```bash
python train.py --dataroot ./data --name exp1 --model cnn
```

程序内部通常会按下面的顺序继续：

1. 读取 `args.dataroot`
   - 去 `./data` 找训练集和测试集
2. 读取 `args.model`
   - 根据字符串 `cnn` 创建对应模型
3. 读取 `args.name`
   - 建立本次实验的输出目录，例如 `checkpoints/exp1`
4. 开始训练
   - 记录 loss、accuracy、日志和模型参数

也就是说，这些参数本质上是在“启动训练之前，把训练配置从命令行传进程序”。

```bash
python train.py --dataroot ./dataset --name run1 --model resnet18
```

### 5. 如何查看一个项目到底支持哪些命令行参数

最直接的办法是：

```bash
python train.py --help
```

它通常会打印出这个训练脚本支持的全部参数、默认值和说明。

如果项目里没有写帮助信息，也可以直接在代码里找：

- `argparse.ArgumentParser`
- `parser.add_argument(...)`

### 6. 官方文档

- `argparse`：[https://docs.python.org/3/library/argparse.html](https://docs.python.org/3/library/argparse.html)

### PyTorch 核心

- `torch` 总览：[https://docs.pytorch.org/docs/stable/torch.html](https://docs.pytorch.org/docs/stable/torch.html)
- `torch.tensor`：[https://docs.pytorch.org/docs/stable/generated/torch.tensor.html](https://docs.pytorch.org/docs/stable/generated/torch.tensor.html)
- `torch.reshape`：[https://docs.pytorch.org/docs/stable/generated/torch.reshape.html](https://docs.pytorch.org/docs/stable/generated/torch.reshape.html)
- `torch.argmax`：[https://docs.pytorch.org/docs/stable/generated/torch.argmax.html](https://docs.pytorch.org/docs/stable/generated/torch.argmax.html)
- `torch.no_grad`：[https://docs.pytorch.org/docs/stable/generated/torch.no_grad.html](https://docs.pytorch.org/docs/stable/generated/torch.no_grad.html)
- `torch.save`：[https://docs.pytorch.org/docs/stable/generated/torch.save.html](https://docs.pytorch.org/docs/stable/generated/torch.save.html)
- `torch.load`：[https://docs.pytorch.org/docs/stable/generated/torch.load.html](https://docs.pytorch.org/docs/stable/generated/torch.load.html)
- `torch.device`：[https://docs.pytorch.org/docs/stable/tensor_attributes.html#torch-device](https://docs.pytorch.org/docs/stable/tensor_attributes.html#torch-device)
- `torch.Tensor.to`：[https://docs.pytorch.org/docs/stable/generated/torch.Tensor.to.html](https://docs.pytorch.org/docs/stable/generated/torch.Tensor.to.html)
- `torch.Tensor.cuda`：[https://docs.pytorch.org/docs/stable/generated/torch.Tensor.cuda.html](https://docs.pytorch.org/docs/stable/generated/torch.Tensor.cuda.html)

### `torch.nn`

- `nn.Module`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html)
- `nn.Conv2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Conv2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Conv2d.html)
- `nn.MaxPool2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.MaxPool2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.MaxPool2d.html)
- `nn.Linear`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Linear.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Linear.html)
- `nn.Flatten`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Flatten.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Flatten.html)
- `nn.Sequential`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Sequential.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Sequential.html)
- `nn.ReLU`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.ReLU.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.ReLU.html)
- `nn.Sigmoid`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Sigmoid.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Sigmoid.html)
- `nn.Dropout`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.Dropout.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.Dropout.html)
- `nn.BatchNorm2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.BatchNorm2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.BatchNorm2d.html)
- `nn.L1Loss`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.L1Loss.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.L1Loss.html)
- `nn.MSELoss`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.MSELoss.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.MSELoss.html)
- `nn.CrossEntropyLoss`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.CrossEntropyLoss.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.CrossEntropyLoss.html)

### `torch.nn.functional`

- `torch.nn.functional.conv2d`：[https://docs.pytorch.org/docs/stable/generated/torch.nn.functional.conv2d.html](https://docs.pytorch.org/docs/stable/generated/torch.nn.functional.conv2d.html)

### `torch.optim`

- `torch.optim` 总览：[https://docs.pytorch.org/docs/stable/optim.html](https://docs.pytorch.org/docs/stable/optim.html)
- `torch.optim.SGD`：[https://docs.pytorch.org/docs/stable/generated/torch.optim.SGD.html](https://docs.pytorch.org/docs/stable/generated/torch.optim.SGD.html)
- `torch.optim.Adam`：[https://docs.pytorch.org/docs/stable/generated/torch.optim.Adam.html](https://docs.pytorch.org/docs/stable/generated/torch.optim.Adam.html)

### 数据

- `Dataset` / `DataLoader`：[https://docs.pytorch.org/docs/stable/data.html](https://docs.pytorch.org/docs/stable/data.html)
- `CIFAR10`：[https://docs.pytorch.org/vision/main/generated/torchvision.datasets.CIFAR10.html](https://docs.pytorch.org/vision/main/generated/torchvision.datasets.CIFAR10.html)

### `torchvision.transforms`

- `ToTensor`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.ToTensor.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.ToTensor.html)
- `Resize`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Resize.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Resize.html)
- `Normalize`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Normalize.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Normalize.html)
- `Compose`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Compose.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.Compose.html)
- `RandomCrop`：[https://docs.pytorch.org/vision/main/generated/torchvision.transforms.RandomCrop.html](https://docs.pytorch.org/vision/main/generated/torchvision.transforms.RandomCrop.html)

### TensorBoard

- `SummaryWriter` / `add_scalar` / `add_image` / `add_images` / `add_graph`：[https://docs.pytorch.org/docs/stable/tensorboard.html](https://docs.pytorch.org/docs/stable/tensorboard.html)

### `torchvision.models`

- `vgg16`：[https://docs.pytorch.org/vision/main/models/generated/torchvision.models.vgg16.html](https://docs.pytorch.org/vision/main/models/generated/torchvision.models.vgg16.html)

### Python / Pillow / NumPy / OpenCV

- `os`：[https://docs.python.org/3/library/os.html](https://docs.python.org/3/library/os.html)
- `time`：[https://docs.python.org/3/library/time.html](https://docs.python.org/3/library/time.html)
- `multiprocessing.freeze_support`：[https://docs.python.org/3/library/multiprocessing.html#multiprocessing.freeze_support](https://docs.python.org/3/library/multiprocessing.html#multiprocessing.freeze_support)
- `PIL.Image`：[https://pillow.readthedocs.io/en/stable/reference/Image.html](https://pillow.readthedocs.io/en/stable/reference/Image.html)
- `numpy.array`：[https://numpy.org/doc/stable/reference/generated/numpy.array.html](https://numpy.org/doc/stable/reference/generated/numpy.array.html)
- `cv2.imread`：[https://docs.opencv.org/4.x/d4/da8/group__imgcodecs.html](https://docs.opencv.org/4.x/d4/da8/group__imgcodecs.html)
