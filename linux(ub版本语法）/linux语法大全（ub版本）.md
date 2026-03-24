# linux语法大全（ub版本）  

## 用户相关命令  

对于高权限的长命令：sudo sh -c

创建用户：sudo adduser tt  

删除用户：sudo deluser --remove-home tt(不加--remove-home则表示删除用户但是不删除文件，后续强制删除文件sudo rm -rf /home/tt)  

su 用户名：切换身份         su - 用户名  彻底切换，相当于重新登录系统  

whoami：显示登录用户  

exit：**切了用户,** `exit` = 变回原来的自己;**连接了远端服务器**，`exit` = 断开连接，回本机，最后还有一个关闭终端。整体上与ctrl+c  类似。 

在ub中，使用root需要先设置他的密码，sudo passwd root，在设置之后就可以切换root   

### 使用root  

创建用户要用root，实在不行借用sudo命令  

passwd name:给指定用户设置密码   

deluser name：删除用户数据，但是不删除对应目录,deluser --remove-home name：删除用户及其数据还有目录   

adduser  --home  目录名称 name :创建一个自定义目录名臣的用户，由于ub不接受段参数，必须用--home，不能用-d  

查询用户信息：id 用户名称  

查询详细信息： who am i (没有空格表示查询当前登录的名称)   

## linux组 

### 用户组

创建组：groupadd name，创建用户指定组：adduser --ingroup 组名称 name  

删除组：groupdel name  

改变用户的组：usermod -g 新组名 name  

---

### 改变文件的组以及所属用户

改变文件所属用户：chown name 文件名   

改变文件所属组 ：chgrp 组名 文件名  

---

### linux的权限问题  

修改文件权限：

* chmod  chmod u=xxx,g=xxx,o=xxx 文件名，注意，此处只需要表明有的权限，额没有的权限不需要也不能用-表示，默认没有， 
* 用+ -表示 -表示去除权限，+表示加上权限 chmod u-x,g+w,o+w name，若不需要修改的部分的则不需要展示出  
* 全部加上某个权限 ：chmod a+/- x name         a表示all  
* 用数字表示 r=4,w=2,x=1,用二进位制表示  chmod u=7,g=5,o=1 name  

---



查询地址：ip addr,ens33表示虚拟网卡， inet 192.168.163.128表示地址，ifconfig也一样，不过已经太老了，被删除了  

查看当前文件所在目录 ：pwd  

软件安装包格式：deb，安装命令：**`apt`** (或者 `apt-get`)，用这个替代cenos中yum

检查镜像源：cat /etc/apt/sources.list或者apt-cache policy（最推荐），sudo apt update可以查看镜像源报错，比如过期等。

## 下载文件  

1. 本地与远程服务器  

远程传输文件：\# 例如：把服务器上的 error.log 下载到我当前的桌面 scp root@192.168.1.10:/home/logs/error.log .  最后这个点表示当前位置，通用格式： scp root@192.168.1.10:/home/logs/error.log  "地址"*(注：如果本地路径有空格，建议加上双引号)*

\# 例如：把本地的 demo.py 传到服务器 scp -Pxxxx  demo.py root @192.168.1.10:/home/project/（上传整个文件夹（记得加 -r）)    

注意名字，root为名称



`rsync` —— 最专业，增量同步 (推荐 ⭐)

-a: 归档模式(保留所有属性)  -v: 显示过程  -z: 压缩传输(省流量)  -P: 显示进度条(Progress)  

rsync -avzP 本地文件夹/ root@192.168.1.10:/远程目录/  

2. 服务器 <-> 互联网 (下载资源)： 

下载文件：wget https://example.com/file.zip  

下载文件保存为其他名字：wget -O new_name.zip https://example.com/file.zip（后台下载 (加 `-b`)） 

-O (大写): 使用远程文件名保存

curl -O https://example.com/file.zip

-o (小写): 指定名字保存

curl -o my_code.zip https://example.com/file.zip  

---

## 服务器相关  

在本地安装服务器：sudo apt update     sudo apt install openssh-server  

查看端口：grep Port /etc/ssh/sshd_config  

修改端口：先修改配置文件：sudo nano /etc/ssh/sshd_config，在文件中找到#Port 22改为 port xxxx,按 `Ctrl+O` 保存，`Ctrl+X` 退出,修改配置后不会立即生效，必须重启服务：sudo systemctl restart ssh，如果安装了防火墙，在重启服务前，最好先放行新端口：sudo ufw allow xxxx/tcp  

由于新特性：# 1. 停止并禁用 systemd 的 socket 监听（让 systemd 让路）
sudo systemctl stop ssh.socket  sudo systemctl disable ssh.socket   之后， 重新加载 systemd 守护进程（让系统知道我们改了底层逻辑） sudo systemctl daemon-reload，重新启动传统的 ssh 服务（这时它才会去读你的配置文件）  sudo systemctl enable ssh.service        sudo systemctl start ssh.service  

总结 放行端口->修改配置->以上操作->检查->重启

检查监听端口：sudo ss -tulnp | grep ssh，查看端口是配置文件的结果，但是这个监听端口才是实际运行的  

## vi编辑器  

创建文件：vim name, 点击i，o,a从正常变插入,保存：先按esc，再shift+冒号，切换到底行模式，输入wq保存，q则直接推出，！q表示不保存推出。

## 关机重启  

1. shutdown  ：shutdown -h now 表示立即关机   shutdown -h 1:表示一分钟后关机    shutdown -r now :立即重启  
2. halt： 就是直接使用，效果等同于关机  
3. sync 把内存的数据同步到磁盘，保存内存中的数据   
4. reboot 就是重启系统

 不管是重启系统还是关闭系统，首先要运行sync命令，把内存中的数据写入到磁盘中，目前的shutdown、reboot、halt命令在关机前都进行了sync，因而不需要再手动sync。 

## 文件操作  

显示当前目录的绝对路径：pwd  

切换到用户所在目录：cd ~       切换到根目录：cd /      cd ..：回到当前目录上一级  cd /home/ttt：切换到指定目录   

cd - 切换到上一条命令所在目录    

### 创建目录

在一个文件夹中创建目录：mkdir name    

创建多级文件夹：mkdir -p n1/n2  

### 删除目录  

删除目录（删除空的） rmdir name  

删除非空的文件：rm name（也可以用于删除文件夹）  参数-r：递归删除，先删除子文件，之后删除整个文件夹，用于删除非空文件夹   -f：不询问直接删除  

rm -rf /*：删除所有  

---

创建空的文件 ：touch name，与vim不同，创建的同时不能编辑   

---

拷贝文件：cp 被拷贝文件  目录  

拷贝目录：cp 参数  aaa   目录，拷贝内容-r  

---

mv：移动文件 剪切或者重命名，在同一个目录操作就是重命名，在不同目录就是剪切  

mv oldname  （目录/）newname，不加目录默认当前目录  

---

浏览文件 ：cat name | more ，|表示将当前命令执行结果交给下一个指令处理，more表示分页展示，enter表示行，空格表示页，q表示退出，-n表示显示行号，具体在文件中找，|less表示分屏浏览  

more file_name：作用一样  

输出到终端：echo，相当于printf；在某个文件中修改内容：echo 输入内容 > 指定文件之中，>>表示追加内容，>会覆盖掉内容  

输出指定文件（头部内容）前m行：head -m（-n m)  file  

输出文件尾部内容后m行：tail -m file        监控文件变化：tail -f name，开多个终端，之后执行了这一行命令的终端会进入监控状态  

软连接（创建快捷方式）：ln -s /被连接的目录  快捷方式名字  

查看历史命令：history，history 10表示最近的十条指令    

----

## 时间指令  

date（功能描述：显示当前时间）   

date +%Y（功能描述：显示当前年份） 

date +%m（功能描述：显示当前月份） 

date +%d（功能描述：显示当前是哪一天） 

date "+%Y-%m-%d %H:%M:%S"（功能描述：显示年月日时分秒） 

设置时间  date -s 字符串时间： date -s "2022-8-28 15:48:50"  

输出日历：cal   输出某年的全年日历：cal +n  

## 搜索指令  

**find ** 指令：递归遍历指定目录找到目标文件  

* 按照文件名称搜索：-name  find / -name test.txt，在某个指定的文件夹中搜，在-name之前加上一个目录路径      

* 搜索指定用户文件：-user   find /opt -user 'root'  

* 按照文件的大小搜索：-size   find / -size +200M ，查询大于200M的文件，-表示小于200的，不加表示等于200mb 

  ---

**locate**指令：利用事先建立好的系统中所有文件名 称及路径的locate数据库实现快速定位给定的文件，查询速度块  

由于locate指令基于数据库进行查询。所以第一次查询运行前，必须使用`updatedb`指令创建locate数 据库。  

locate name  

---

**witch**指令：可以查看某个指令在哪个目录下  

---

**grep**指令：grep过滤查找，管道符，”|“,表示前一个指令的处理结果输出传递给后面的指令处理。一般我们将 | 和  grep一起结合起来使用。 

基本语法：grep [选项] 查找内容 源文件    -n显示行号  -i忽略自动写大写   

## 压缩/解压指令  

* .gz文件   gunzip  解压   gzip  压缩，解压和压缩会自动删除文件，压缩解压到指定文件夹 gzip/gunzip -c 源文件 > /tmp/test.txt.gz，但是建议先压缩再移动    
* .zip文件  unzip  解压，-d表示解压到指定目录  ，  zip   压缩 ：-r  递归遍历文件目录压缩：zip -r  压缩后名称  被压缩目录   
* .tar.zip文件：tar 命令可以解压也可以压缩，-c  产生tar打包文件     -v  显示详细信息    -f   指定压缩后的文件名          -z打包同时压缩      -x     解压tar包文件，压缩文件：tar -zcvf  压缩文件的名称  被压缩目录    解压文件的命令：tar -zxvf 压缩文件名称  -C 指定目录 

---

## 任务调度指令  

ps -ef :查询所有运行的进程信息    

1. **crontab** :    -e：编辑定时任务     -l：查询定时任务       -r：删除所有定时任务  

* 定时调用指令：*/1 * * * * ls -l /etc/ > /tmp/etc.txt    ：开头的1表示每隔1分钟，ls -l /ets/ 表示命令，一共是五个\*，从左到右依次表示：一个小时中第几分钟，一天当中第几个小时，一个月中第几天，一年中地几个月，一周当中星期几，\*表示所有，任意一个的含义，','表示不连续时间，-表示连续时间，\*/n表示每隔n分钟  
* 定时执行脚本，要确保脚本具有可执行权限，\*\*\*\*\*  脚本位置  

2. **at**：一次性定期执行  

   systemctl start atd    # 启动服务
   systemctl enable atd   # 设置开机自动启动（防止重启后又挂了）

   时间格式如下：  

![image-20260203103428109](https://cdn.jsdelivr.net/gh/Learner-Liang/image-bed@main/images/image-20260203103428109.png) 

参数格式： 

![image-20260203103920792](https://cdn.jsdelivr.net/gh/Learner-Liang/image-bed@main/images/image-20260203103920792.png)  语法格式： at 选项 时间

输入 指令之后不要按回车，按两次 ctrl+d

查询待执行的一次性任务指令：`atq`  

 删除任务：`atrm+任务编号`  

---

## 磁盘  

* 查看磁盘分区：`lsblk`  
* 分区 ：`fdisk /目录`  ，目录在/dev/中  ，使用前格式化，`mkfs -t ext4 目录`  ，之后挂在对应的目录，先创建一个目录，之后挂在`sudo mount /dev/sdb2 /newdisk/` ,但是这是临时的，重启后失效，应该`vim /etc/fstab`，最后在其中编辑·`/dev/sdb2（磁盘名） / newdisk（目录）   ext4 defaults 0 1`。
* 查看磁盘分区使用情况展示：`df - h`  ，查看自定目录也有，参考linux文件，`du + 选项`。
* 统计目录中文件个数：`wc 选项`,
* 用树状图展示目录 ：`tree 目录`.

---

## 网络配置  

ipaddr 在linux查看ip地址  

ifconﬁg 在linux查看ip地址  

ping 是否ping通指定的ip地址
ipconﬁg 在windows操作系统里面查看网络的ip地址  

ub中网络配置文件为：/etc/netplan/，cenos中为：/etc/sysconfig/network-scripts/  

设置静态ip，用手动配置的方法：首先在ub中输入：`ip route`，网关就是via后面数字，子网掩码一般直接填：255.255.255.0，dns国内填 **`114.114.114.114`**，谷歌填8.8.8.8，最后重启有线网络连接开关，可以用ping www.baidu.com检验。  

查询主机名称：cat /etc/hostname   or hostname  

---

## 进程相关指令介绍  

### 展示进程  

展示进程：ps 参数  。

参数类型：

* ps -a:显示终端所用的进程信息
* ps-u:以用户的格式显示进程的信息
* ps-x:显示后台程序运行的参数
* -e 所有进程，-f全格式显示进程
* ps -ef：使用全格式查看所有进程信息

用grep可以进行筛选，grep bash 表示查询终端信息    

用grep查询时候，grep本身也会成为一个进程，用这样子：ps -ef | grep flameshot | grep -v grep更好或者pgrep flameshot

---

### 中止进程  

`kill 进程号`          kill -all杀死当前进程与子进程   如果sssh被杀死，则远程无法登录，若服务器可以登录但是远程不行，则检查一下sssh是否开启：`/bin/systemctl start sshd.service`    

中止终端：以上方法可能不管用，改成kill -9 进程号  

## 查看进程信息  

树状查看进程信息：`pstree [选项]`，-p:显示进程的PID，-u:显示进程的所属用户。

## 服务管理  

### service  

* 查看指令服务（被service管理）：cd /etc/init.d/   + ll
* 查看服务的状态：service 服务名 status  
* 停止/启动服务：service 服务名 start/stop    启动/关闭开机自启：systemctl enable/disable 服务名

### checkconfig(在ub中取消，详细查找pdf)  

* 查看指令服务（被checkconfig管理）：`chkconfig --list`  

### systemctl  指令  

* 查看指令服务：cd /usr/lib/systemd/system  +  ll  
* 查看被其管理的服务名称：systemctl list-unit-files（systemctl list-unit-files --type=service），配合grep使用可以查看特定的 
* 看“哪些服务是开机自启等特定状态的”：systemctl list-unit-files --type=service --state=enabled（**enabled**: ✅ 开机自启 **disabled**: ❌ 开机不自启  **static**: 🔗 被依赖项（自己不主动启动，但别的服务喊它时它会起）**masked**: 🚫 被彻底屏蔽（无法启动）
* 服务启动/停止/重启/重载/查看状态： systemctl [start | stop | restart | status] 服务名  
* 查看某一服务是否自启动：`systemctl is-enabled 服务名`  
* 设置服务自启动：systemctl enabled 服务名  
* 设置服务禁用自启动：`systemctl disable 服务名`   

以前的 Linux 有 0-6 个“运行级别” (Runlevel)。 但在 Ubuntu (Systemd) 中，这个概念被简化了。现在只有**“开” (enabled)** 和 **“关” (disabled)** 两种主要状态。

---

## 防火墙  

**打开端口/允许协议**： `sudo ufw allow 端口号/协议` *(例如：`sudo ufw allow 80/tcp`)*

**关闭端口/禁用协议**（其实是删除刚才那条允许规则）： `sudo ufw delete allow 端口号/协议` *(例如：`sudo ufw delete allow 80/tcp`)*

**查询端口/协议是否开启**（UFW 没有直接的 query 命令，我们用筛选的方式）： `sudo ufw status | grep 端口号` *(如果有输出就是开启，没输出就是关闭)*

**查询防火墙所有开放的端口/协议配置**： `sudo ufw status`

**重载防火墙**（通常改了配置文件才需要，普通加端口不需要）： `sudo ufw reload`  

**打开/关闭总开关**： `sudo ufw enable/disable`  

安装程序后，如果想开放外部访问窗口权限，必须开放对应的端口  

---

### 查找程序对应端口  

确保安装了需要的工具：sudo apt install net-tools  

查询所有监听窗口：sudo netstat -tulpn，可以用grep指令来查询特定的    

**参数：**

* **-t**: TCP (最常用的协议)
* **-u**: UDP (另一种协议)
* **-l**: Listening (只看正在监听的，不看正在通信的)
* **-p**: **Program** (最重要！显示由于哪个程序占用了端口)
* **-n**: Numeric (直接显示数字端口号，别给我显示 'ssh' 这种别名)  

**怎么看结果？** 你在一堆输出里，看 **“Local Address”** (本地地址) 和 **“PID/Program name”** (程序名) 这两列。

* `0.0.0.0:80`  ---> 说明 **80** 端口正在被占用。
* 对应右边写着 `1234/nginx` ---> 说明是 **nginx** 程序在用它

有时候防火墙报错说“8080端口被占用”，你想知道是谁这么大胆占了你的坑？

**命令格式：** `sudo lsof -i :端口号`

---

### 动态监控指令  

top与ps命令一样，它们都用来显示正在执行的进程。top与ps最大的不同之处，在于top在执行一段时
间可以更新正在运行的进程。

top [选项]  

![image-20260207170805855](https://cdn.jsdelivr.net/gh/Learner-Liang/image-bed@main/images/image-20260207170805855.png)

* 在输入top后，shift + 字母修改  

![image-20260207171703684](https://cdn.jsdelivr.net/gh/Learner-Liang/image-bed@main/images/image-20260207171703684.png)

* 监控特定用户进程  u + name  
* 终止指定的进程       
* top:输入此命令，然后回车，查看执行的进程，k：然后输入要结束的进程ID号 回车之后输入9 强制删除。

### 监控网络状态  

基本语法： netstat [选项]           选项说明 -an 按照一定的属性排列输出        -p 显示哪个进程在调用，新版用ss -anp替代了

**-t**: 只看 **TCP**

**-u**: 只看 **UDP**

**-l**: 只看 **监听中 (Listening)** 的（也就是开了端口等别人连的）

**-p**: 显示 **进程名**

**-n**: 显示 **数字端口** (不显示别名)  

不加 l 默认只显示 **“正在通话中” (Established)** 的连接。 也就是说，如果你的电脑现在没有正在下载文件，也没有正在跟别的电脑传数据，那屏幕就是空的。

## dpkg(rpm)

| **你的动作**     | **CentOS (rpm)**      | **Ubuntu (dpkg)**        | **备注**                         |
| ---------------- | --------------------- | ------------------------ | -------------------------------- |
| **安装本地包**   | `rpm -ivh 文件名.rpm` | **`dpkg -i 文件名.deb`** | `-i` = install                   |
| **卸载软件**     | `rpm -e 包名`         | **`dpkg -r 包名`**       | `-r` = remove (保留配置)         |
| **彻底卸载**     | (rpm通常不直接支持)   | **`dpkg -P 包名`**       | `-P` = purge (连配置文件一起删)  |
| **列出所有软件** | `rpm -qa`             | **`dpkg -l`**            | `-l` = list                      |
| **查看软件详情** | `rpm -qi 包名`        | **`dpkg -s 包名`**       | `-s` = status (显示版本、描述)   |
| **查文件去哪了** | `rpm -ql 包名`        | **`dpkg -L 包名`**       | `-L` = List files (列出安装路径) |
| **查文件是谁的** | `rpm -qf /bin/ls`     | **`dpkg -S /bin/ls`**    | `-S` = Search (反查文件归属)     |

 查询xxx是否通过rpm安装：rpm -q xxx：能显示则表明通过rpm方式安装  

有时候安装再Snap包中，所以需要sudo snap remove 指令追杀，查找他是否再：snap list firefox

## apt(yum)

| **你的目的 (Action)**   | **Ubuntu 指令 (apt)**                 | **CentOS 对照 (yum)**  | **老师的备注 (Tips)**                                        |
| ----------------------- | ------------------------------------- | ---------------------- | ------------------------------------------------------------ |
| **刷新软件源**          | **`sudo apt update`**                 | `yum makecache`        | **最重要！** 装软件前必做。它只下载菜单，不更新软件。        |
| **升级所有软件**        | **`sudo apt upgrade`**                | `yum update`           | **注意区别：** 它才是真正去下载新版软件并安装的步骤。        |
| **安装软件**            | **`sudo apt install <包名>`**         | `yum install <包名>`   | 自动解决依赖。                                               |
| **安装本地包**          | **`sudo apt install ./<文件名>.deb`** | `yum localinstall ...` | **神技！** 替代 `dpkg -i`，能自动补全依赖。(注意路径 `./` 不能少) |
| **卸载 (保留配置)**     | **`sudo apt remove <包名>`**          | `yum remove <包名>`    | 软件删了，但 `/etc` 下的配置文件还在。适合“以后可能还装回来”的情况。 |
| **彻底卸载 (连根拔起)** | **`sudo apt purge <包名>`**           | (无直接对应)           | **慎用！** 软件和配置文件统统删掉。                          |
| **搜索软件**            | `apt search <关键词>`                 | `yum search <关键词>`  | 比如 `apt search mysql`。                                    |
| **查看软件详情**        | `apt show <包名>`                     | `yum info <包名>`      | 查看版本、大小、依赖关系。                                   |
| **列出已安装软件**      | `apt list --installed`                | `yum list installed`   | 建议配合 `| grep` 使用。                                     |
| **清理无用依赖**        | **`sudo apt autoremove`**             | `yum autoremove`       | **强迫症必备！** 自动删除那些“为了装A而装B，现在A删了，B也没用了”的孤儿包。 |
| **清理缓存包**          | `sudo apt clean`                      | `yum clean all`        | 清空 `/var/cache/apt/archives/` 里的 `.deb` 文件，释放硬盘。 |
| **修复破损依赖**        | `sudo apt --fix-broken install`       | (复杂)                 | **救命指令！** 当安装报错说“依赖关系不满足”时，运行它能自动修好。 |

* 更新所有包：sudo apt update
  sudo apt upgrade -y

## 查看显卡  

nvidia-smi：检查显卡运行状况  

## 小问题解决  

* 小屏幕的问题：下载软件增强工具  sudo apt update   sudo apt install open-vm-tools-desktop -y  sudo reboot  

* 下载vscode ：sudo snap install --classic code    **安装核心构建工具包：** `sudo apt install build-essential`               检验安装：gcc --version` `make --version

* 查看自己的vscode配置：code --list-extensions

* 我的vscode配置：这个是脚本，直接复制运行即可

* extensions=(
      cweijan.vscode-office
      damiankoper.gdb-debug
      dbaeumer.vscode-eslint
      donjayamanne.githistory
      eamodio.gitlens
      exodiusstudios.comment-anchors
      formulahendry.code-runner
      github.copilot-chat
      github.remotehub
      mhutchie.git-graph
      ms-azuretools.vscode-containers
      ms-ceintl.vscode-language-pack-zh-hans
      ms-python.debugpy
      ms-python.python
      ms-python.vscode-pylance
      ms-python.vscode-python-envs
      ms-toolsai.jupyter
      ms-toolsai.jupyter-keymap
      ms-toolsai.jupyter-renderers
      ms-toolsai.vscode-jupyter-cell-tags
      ms-toolsai.vscode-jupyter-slideshow
      ms-vscode-remote.remote-containers
      ms-vscode-remote.remote-ssh
      ms-vscode-remote.remote-ssh-edit
      ms-vscode.azure-repos
      ms-vscode.cmake-tools
      ms-vscode.cpp-devtools
      ms-vscode.cpptools
      ms-vscode.cpptools-extension-pack
      ms-vscode.cpptools-themes
      ms-vscode.remote-explorer
      ms-vscode.remote-repositories
      shd101wyy.markdown-preview-enhanced
      spades.vs-picgo
      streetsidesoftware.code-spell-checker
      tintinweb.graphviz-interactive-preview
      twxs.cmake
      usernamehw.errorlens
      yzhang.markdown-all-in-one
  )

  for ext in "${extensions[@]}"; do
    code --install-extension "$ext"
  done
  
* 安装anaconda: wget -c https://repo.anaconda.com/archive/Anaconda3-2024.10-1-Linux-x86_64.sh -O ~/anaconda3.sh     执行安装：bash ~/anaconda3.sh    检验：+

* 配置linux网络，访问全球网络：

  以下操作存在写死问题，得注意 ，最好clash开tun模式，之后如果不行直接重新启动相关服务，比如下面的解决方案。

  查询自己ipv4地址：1. cmd  2. ipconfig 3. 查VMware Network Adapter VMnet8后面  

  1. 终端与日常命令层 (`~/.bashrc`)   这保障了 `wget`, `curl` 以及后续利用 Python 包管理器下载依赖时能够顺利联网。

  * echo 'export http_proxy="http://192.168.163.1:7897"' >> ~/.bashrc
    echo 'export https_proxy="http://192.168.163.1:7897"' >> ~/.bashrc
    source ~/.bashrc
  * 192等在自己的win上查询，7897这个在clash上看

  2. 系统核心包管理器层 (`apt`)

  `sudo` 提权操作默认会剥离普通用户的环境变量。这步配置保障了 `sudo apt update` 和安装底层 C/C++ 构建工具时，系统能获取到最高权限的网络通道。

  sudo bash -c 'echo "Acquire::http::Proxy \"http://192.168.163.1:7897\";" > /etc/apt/apt.conf.d/proxy.conf'
  sudo bash -c 'echo "Acquire::https::Proxy \"http://192.168.163.1:7897\";" >> /etc/apt/apt.conf.d/proxy.conf'

  192等在自己的win上查询，7897这个在clash上看

  3. Git 专属配置层 (`~/.gitconfig`)

  Git 作为独立的版本控制工具，有自己的一套配置逻辑。通过注入全局代理，无论你是通过 `git clone` 抓取开源项目，还是管理自己 `init` 的本地仓库并与远程仓库 (Remote) 进行频繁的数据推送与同步，流量都不会被防火墙拦截。

  git config --global http.proxy http://192.168.163.1:7897
  git config --global https.proxy http://192.168.163.1:7897

## 碰到的linux问题的解决方案

* ping失败：win+r ->services.msc->找到 **`VMware NAT Service`**，右键点击它，选择 **“重新启动” (Restart)**->找到 **`VMware DHCP Service`**，同样右键点击它，选择 **“重新启动” (Restart)**。

* 

  





  



