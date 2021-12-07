# Visual Studio Code 中 CMake 插件的基本使用

CMake 是一个构建管理工具。它可以根据用户编写的脚本生成适用于不同平台、不同工具链的构建文件。

## 安装 CMake

访问 [CMake 官网](https://cmake.org/) 进入 [CMake 下载页面](https://cmake.org/download/)，找到“[Latest Release](https://cmake.org/download/#latest)”，下载最新的发行版。

64 位 Windows 可以选择 Windows x64 Installer 下载即可。安装时，可以选择添加到 PATH 环境变量（Add to PATH）。

> 在 Visual Studio 中安装“C++ 桌面开发”的工作负载时，默认会安装 CMake。可以尝试从“Develop PowerShell for VS”中启动 Visual Studio Code。这样启动的 Code 中就会具有 Visual Studio 安装相关的环境变量。
>
> ![在开始菜单的“所有程序”下的“Visual Studio”目录中可以找到“Develop PowerShell for VS”的启动方式](https://img-blog.csdnimg.cn/495f174b99e942b3a7d7a6f1ca4c777b.png)
>
> 在“‘开始’菜单”的“所有程序”下的“Visual Studio”目录中可以找到“Develop PowerShell for VS”的启动方式。

## Visual Studio Code 中的使用

使用 Visual Studio Code 打开一个工作目录，这里以“CMakeDemo”为例。

<figure>
<img alt="使用 Visual Studio Code 打开一个工作目录" src="https://img-blog.csdnimg.cn/1b2ec19e282349708c86e8ef6ff82ae2.png" style="border-radius: 5px; outline: 1px solid gray; outline-offset: -1px;">
<figcaption>使用 Visual Studio Code 打开一个工作目录</figcaption>
</figure>


在插件市场中搜索“CMake”关键字，安装 Microsoft 提供的“[CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)”插件（会自动安装另一个依赖的插件）。

<figure>
<img alt="安装 Microsoft 提供的 CMake Tools 插件" src="https://img-blog.csdnimg.cn/a2e63443e1784f5a83465a44519da5b4.png" style="border-radius: 5px; outline: 1px solid gray; outline-offset: -1px;">
<figcaption>安装 Microsoft 提供的 CMake Tools 插件</figcaption>
</figure>

在目录下新建这些文件：

CMakeLists.txt

```cmake
project(CMake-Demo)

add_executable(demo "main.cpp" "foo.cpp" "foo.h")
```

> `add_executable` 命令用来告诉 CMake 添加一个“生成可执行程序”的目标。

foo.h

```cpp
#ifndef FOO_H
#define FOO_H

int some_function(int a, int b);

#endif
```

foo.cpp

```cpp
#include "foo.h"

int some_function(int a, int b) {
    return 2 * a + 3 * b;
}
```

main.cpp

```cpp
#include "foo.h"
#include <iostream>

int main() {
    std::cout << some_function(1,2);
}
```

文件创建并编写完成后，可以按 <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd> 打开命令面板，输入“configure”检索并执行“CMake: Configure”命令。也可以关闭窗口并重新打开，CMake 插件也会自动检测到当前文件夹下的这个 CMake 项目。

<figure>
<img src="https://img-blog.csdnimg.cn/38b5387a1b8947779b325da1ea3e88f0.png" style="border-radius: 5px; outline: 1px solid gray; outline-offset: -1px;">
<figcaption>Configure CMake 项目</figcaption>
</figure>

执行 Configure 操作时，CMake 插件会提示我们选择一个 Kit，根据需要选择自己需要使用的 Kit 即可。

<figure>
<img src="https://img-blog.csdnimg.cn/e56e6248ffbf4e62badd8d6dafcaf905.png" style="border-radius: 5px; outline: 1px solid gray; outline-offset: -1px;">
<figcaption>选择要使用的 Kit</figcaption>
</figure>

如果没有问题，CMake 插件将会有类似如下的输出：

<figure>
<img src="https://img-blog.csdnimg.cn/db135ff7441b42b6a398beed73b8688a.png" style="border-radius: 5px; outline: 1px solid gray; outline-offset: -1px;">
<figcaption>Configure 完成的输出</figcaption>
</figure>

> 如果出现问题，可以尝试显式指定 CMake 使用的 Generator。

CMake 插件默认在 Visual Studio 窗口的底端提供了一些按钮：

<kbd>⚙ Build</kbd> 按钮旁的是要构建的目标，默认为 all，也就是所有的目标。

<figure>
<img src="https://img-blog.csdnimg.cn/a5a88e480ed84a99b2f6b2979d8f8d93.png" style="border-radius: 5px; outline: 1px solid gray; outline-offset: -1px;">
<figcaption>选择要 Build 的目标</figcaption>
</figure>

点击 <kbd>⚙ Build</kbd> 按钮即可开始构建指定的项目。

CMake 插件默认的构建目录为工作目录下的 `build` 目录。CMake 生成的文件，以及构建产生的结果，都会在这个目录下。

> 这种方式称为“out-of-source build（在源代码之外构建）”，即构建相关的文件与源代码是分离开的，不会污染代码树。

<kbd>🐞</kbd> 和 <kbd>▶</kbd> 按钮分别为“调试运行”与“运行”；使用它们旁边的按钮可以选择要调试/运行的项目。

<figure>
<img src="https://img-blog.csdnimg.cn/c396b38eae5849368b5ad2a1850d5319.png" style="border-radius: 5px; outline: 1px solid gray; outline-offset: -1px;">
<figcaption>选择要调试/运行的项目</figcaption>
</figure>

## 子项目

一个含有 CMakeLists.txt 文件的目录就可以视作一个项目。假如一个目录中下有多个 CMake 项目，也可以使用 `add_subdirectory` 命令将它们添加进来。
