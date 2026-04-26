# 小土堆 PyTorch 学习环境配置教程

本文记录在 Windows 电脑上使用 Anaconda 配置 PyTorch 学习环境的完整流程，适合跟着小土堆 PyTorch 教程学习使用。

## 1. 当前电脑环境

本机配置情况：

- 系统：Windows
- 显卡：NVIDIA GeForce RTX 4060 Laptop GPU
- NVIDIA 驱动：566.07
- `nvidia-smi` 显示 CUDA 支持上限：12.7
- Anaconda 安装目录：`D:\ANACONDA`
- 项目目录：`E:\my_github\Cs_learning_of_liang\learn-pytorch`

由于当前显卡驱动支持 CUDA 12.7，安装 PyTorch 时推荐选择 CUDA 12.6 版本，也就是 `cu126`。

## 2. 打开 Anaconda Prompt

在 Windows 开始菜单中搜索并打开：

```text
Anaconda Prompt
```

打开后先检查 conda 是否可用：

```powershell
conda --version
```

如果能看到类似下面的输出，说明 Anaconda 可以正常使用：

```text
conda 25.5.1
```

## 3. 创建 PyTorch 专用环境

建议不要直接在 `base` 环境中安装 PyTorch，而是单独创建一个学习环境，方便后续管理依赖。

```powershell
conda create -n learn-pytorch python=3.10 -y
```

创建完成后激活环境：

```powershell
conda activate learn-pytorch
```

如果命令行前面出现：

```text
(learn-pytorch)
```

说明环境已经激活成功。

## 4. 安装 GPU 版 PyTorch

在已经激活的 `(learn-pytorch)` 环境中执行：

```powershell
pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu126
```

说明：

- `torch` 是 PyTorch 核心库。
- `torchvision` 用于图像数据集、图像变换和经典视觉模型。
- `torchaudio` 用于音频相关任务。
- `cu126` 表示安装 CUDA 12.6 对应的 PyTorch 版本。
- 学习 PyTorch 时通常不需要单独安装 CUDA Toolkit，PyTorch 安装包已经包含运行所需的 CUDA 组件。

## 5. 安装课程常用依赖

继续在 `(learn-pytorch)` 环境中安装小土堆课程常用库：

```powershell
pip install matplotlib pandas pillow opencv-python tqdm tensorboard jupyter ipykernel
```

这些包的用途：

- `matplotlib`：绘图与图片显示。
- `pandas`：表格数据处理。
- `pillow`：图片读取和处理，常用导入名是 `PIL`。
- `opencv-python`：OpenCV 图像处理，常用导入名是 `cv2`。
- `tqdm`：训练进度条。
- `tensorboard`：训练过程可视化。
- `jupyter`：运行 Notebook。
- `ipykernel`：让 Jupyter 使用当前 conda 环境。

## 6. 验证 PyTorch 是否安装成功

执行下面的命令：

```powershell
python -c "import torch; print(torch.__version__); print(torch.version.cuda); print(torch.cuda.is_available()); print(torch.cuda.get_device_name(0) if torch.cuda.is_available() else 'CPU only')"
```

如果安装成功，并且 GPU 可以被 PyTorch 调用，输出中应该包含：

```text
True
NVIDIA GeForce RTX 4060 Laptop GPU
```

其中最重要的是：

```text
torch.cuda.is_available()
```

结果为 `True`，说明 PyTorch 可以使用显卡。

## 7. 配置 VS Code 解释器

打开 VS Code 后，进入项目目录：

```text
E:\my_github\Cs_learning_of_liang\learn-pytorch
```

然后选择 Python 解释器：

1. 按 `Ctrl + Shift + P`
2. 输入并选择 `Python: Select Interpreter`
3. 选择下面这个解释器：

```text
D:\anaconda3\envs\learn-pytorch\python.exe
```

如果列表中找不到该解释器，可以在 Anaconda Prompt 中执行：

```powershell
conda activate learn-pytorch
where python
```

然后把输出的 Python 路径手动填入 VS Code。

## 8. 创建测试脚本

在项目目录中新建文件：

```text
test_env.py
```

写入下面的代码：

```python
import torch

print("PyTorch version:", torch.__version__)
print("CUDA version:", torch.version.cuda)
print("CUDA available:", torch.cuda.is_available())

x = torch.rand(3, 4)
print("CPU tensor:")
print(x)

if torch.cuda.is_available():
    x = x.cuda()
    print("GPU tensor:")
    print(x)
    print("GPU name:", torch.cuda.get_device_name(0))
```

在 Anaconda Prompt 中运行：

```powershell
cd /d E:\my_github\Cs_learning_of_liang\learn-pytorch
conda activate learn-pytorch
python test_env.py
```

如果能正常输出随机张量，并且显示 RTX 4060 Laptop GPU，说明环境配置完成。

## 9. 在普通 PowerShell 中使用 conda

如果希望在 VS Code 终端或普通 PowerShell 中直接使用 `conda activate learn-pytorch`，可以在 Anaconda Prompt 中执行：

```powershell
conda init powershell
```

然后关闭所有 PowerShell 窗口，重新打开。

如果 PowerShell 提示脚本执行权限问题，执行：

```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

之后重新打开 PowerShell，再执行：

```powershell
conda activate learn-pytorch
```

## 10. 常见问题

### 10.1 `conda` 不是内部或外部命令

原因通常是普通 PowerShell 没有初始化 conda。

优先使用 Anaconda Prompt，或者在 Anaconda Prompt 中执行：

```powershell
conda init powershell
```

### 10.2 `torch.cuda.is_available()` 是 `False`

可以按顺序检查：

1. 是否安装的是 GPU 版 PyTorch，而不是 CPU 版。
2. 安装命令中是否包含 `--index-url https://download.pytorch.org/whl/cu126`。
3. NVIDIA 驱动是否正常，执行：

```powershell
nvidia-smi
```

如果 `nvidia-smi` 可以显示显卡信息，说明驱动基本正常。

### 10.3 VS Code 运行时找不到 torch

通常是 VS Code 选错了解释器。

重新选择：

```text
D:\anaconda3\envs\learn-pytorch\python.exe
```

或者在 VS Code 终端中确认：

```powershell
where python
python -c "import torch; print(torch.__version__)"
```

## 11. 后续学习建议

环境配置完成后，可以按照小土堆 PyTorch 教程的顺序学习：

1. Python 基础和常用包导入。
2. PyTorch 基本数据类型和 Tensor 操作。
3. `Dataset` 和 `DataLoader`。
4. `torchvision` 数据集和图片变换。
5. 神经网络模型搭建。
6. 损失函数和优化器。
7. 模型训练流程。
8. GPU 训练。
9. TensorBoard 可视化。
10. 模型保存与加载。

本仓库可以按照章节逐步添加代码文件，建议每一节单独建立一个 Python 文件，方便回顾和调试。
