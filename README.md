# 程序运行说明

我们添加了Makefile用于测试:

当前目录下执行以下命令, 生成对应的可执行程序

```
make
```

当前目录下执行以下命令, 进行单元测试(需要确保已经编译安装了googletest)

```
make test-units 
```

当前目录下执行以下命令, 进行数独解决好坏样例测试

```
make test-solve-good
```

```
make test-solve-bad
```

## 用户手册

### 程序源码的 github 链接

[NK-MXD/ShuduSolution: 软件工程结对编程作业 (github.com)](https://github.com/NK-MXD/ShuduSolution)

### 数独游戏的介绍

数独游戏是一种逻辑数学游戏，旨在填充一个9x9的方格网格，使得每一行、每一列和每一个3x3的子网格中都包含1到9的数字，且每个数字只能在每行、每列和每个子网格中出现一次。游戏开始时，会给你一个已经填充了一部分数字的初始盘面，你需要根据已知数字和规则来推理和填写剩余的空格。通过观察已有的数字和规则，你可以进行推理和推断来确定每个空格的正确数字。填写数字时，需要保证每一行、每一列和每个子网格中的数字都符合规则，没有重复出现。解决数独谜题需要一定的逻辑推理和推断能力，而难度级别可以根据已知数字的数量和位置而有所变化。

### 程序概述

本程序实现的基本功能有：

1、对输入的命令进行判断，实现不同的功能，对非法输入进行报错；  
2、生成 n 种不重复的数独终局至文件；  
3、读取文件内的数独问题，求解并将结果输出到文件。

除此之外，我们在上述程序的基础功能之上添加了以下拓展功能提供给用户进行选择尝试:

1、生成不同数量的数独游戏至文件；  
2、设置生成数独游戏的难度等级；  
3、设置不同填充数字的数独游戏；  
4、设置生成唯一解的数独游戏；   
5、提供帮助参考列表；

### 程序运行说明

程序运行环境：Windows10 及以上，Linux 环境均可。

程序使用的参数列表如下：

| 命令参数              | 作用                         | 说明                                               |  范围限制       | 用法示例 |
| --------------------- | ---------------------------- | -------------------------------------------------- |--------------------- | ---------------------------- |
| -c, --count \<number>  | 指定生成终局数目             | Needs number of sudoku puzzles (1-1000000)         | 1-1000000      | 示例：sudoku.exe -c 20 [表示生成 20 个数独终盘]   |
| -s, --solve \<file>    | 指定数独游戏路径             | Needs path to sudoku puzzle file                   | 绝对或者相对路径       |示例：sudoku.exe -s game.txt [表示从 game.txt 读取若干个数独游戏，并给出其解答，生成到 sudoku.txt 中]                            |
| -n, --number \<number> | 指定生成数独游戏数目         | Needs number of games (1-10000)                    | 1-10000        |示例：sudoku.exe -n 1000 -r 30~40 [表示生成 1000 个数独游戏(需要和-r搭配使用否则会报错)]                                                                               |
| -m, --mode \<number>   | 指定生成游戏难度等级         | Generates game difficulty (1-3)                    | 1-3            | 示例：sudoku.exe -n 1000 -m 1 -r 30~40 [表示生成 1000 个简单数独游戏，只有 m 和 n 一起使用才认为参数无误，否则会报错]                     |
| -r, --range \<range>   | 指定生成游戏填充数字数目范围 | Generates game with number range (21~54)           | 21-54          | 示例：sudoku.exe -n 20 -r 21~54 [表示生成 20 个填充数字数目范围为 21 到 54 之间的数独游戏，只有 r 和 n 一起使用才认为参数无误，否则会报错] |
| -u, --unique \<bool>   | 指定生成具有唯一解的游戏个数 | Generates game with unique solution(default false) |                 | 示例：sudoku.exe -n 20 -u [表示生成 20 个解唯一的数独游戏，只有 u 和 n 一起使用才以为参数无误，否则会报错]                       |
| -h, --help            | 显示帮助信息                 | Displays this help information                     | | |

可以通过控制参数来达到不同的运行效果

### 程序运行方式

在命令行中选取不同的参数即可运行程序，例如：

![image.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202306302250626.png)

可以选择不同的参数进行运行程序

![image.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202306302253378.png)

可以看到已经生成了对应的终局在文件当中，终局生成格式为每个棋局顺序排列在文件的一行：

![image.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202306302255142.png)

### 程序运行示例

1. 生成 10 盘数独游戏终局到文件当中：

```shell
./shudu -c 10 
```

![1688140826757.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202307010000340.png)

![1688140865784.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202307010001673.png)

2. 生成 1 盘数独游戏到文件当中，设置填充数独游戏的洞的个数为 30~40，难度系数为 2，终局数唯一：

```shell
./shudu -n 1 -m 2 -r 30~40 -u
```

![1688140437645.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202306302354482.png)

在当前文件夹下的 gameBoard.txt 文件下可以找到当前棋盘对应的游戏文件:

![1688140469294.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202306302354122.png)

3. 上述游戏局面生成之后，从文件路径中找到该文件路径进行求解数独游戏：

```shell
./shudu -s ./gameBoard.txt
```

![1688140643093.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202306302357707.png)

对应的游戏结果保存在当前路径下的 solveBoard.txt 文件当中：

![1688140763717.png|500](https://image-1305894911.cos.ap-beijing.myqcloud.com/Obsidian/202306302359100.png)

