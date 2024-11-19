# Westlake-Go-Notation-Program 项目

Westlake-Go-Notation-Program 是一个围棋游戏客户端，使用 C++ 和 wxWidgets 编写，支持 Windows 操作系统。

## 目录结构

- `source/`：包含源代码文件（C++ 代码和头文件）
- `art/`：包含资源文件（如图标和界面样式）
- `object/`：存放编译后的中间对象文件
- `binary/`：存放最终的可执行文件
- `Makefile`：用于构建项目的 Makefile

## 项目依赖

在使用和编译该项目之前，确保您的系统已安装以下依赖项：

- **C++ 编译器**：支持 C++17，推荐使用 `g++`（如 MinGW 或 MSYS2）
- **wxWidgets**：3.0 版本的 wxWidgets 库，用于图形界面构建
- **Windows 系统**：该项目仅支持 Windows 平台（适配了 `msw` 编译目标）

### 安装 wxWidgets

您需要安装 wxWidgets 3.0，您可以通过以下命令在 MSYS2 中安装它：

```
pacman -S mingw-w64-x86_64-wxwidgets
```

## 构建与运行

### 1. 编译项目

在项目根目录中，使用 `Makefile` 来构建项目。打开终端并输入以下命令：

```
make
```

这将执行编译流程，生成最终的可执行文件 `Westlake-Go-Notation-Program.exe`，位于 `binary/` 目录中。

### 2. 运行项目

构建完成后，可以通过以下命令运行项目：

```
make run
```

这将启动 `Westlake-Go-Notation-Program` 应用程序。

## 配置说明

在 `Makefile` 中，有几个重要的变量和设置：

- `CXXFLAGS`：C++ 编译器选项，如启用多线程支持、指定 Unicode 编码等。
- `LINKFLAGS`：链接器选项，包含静态链接、添加 wxWidgets 和 Windows 必需的库等。
- `CXX` 和 `LINK`：指定 C++ 编译器和链接器。
- `BIN_NAME`：指定生成的可执行文件名称（`Westlake-Go-Notation-Program`）。

## 常见问题

### 1. **如何解决库重复定义错误？**

如果在链接时遇到类似 `multiple definition` 的错误，可能是因为某些库被多次引用。尝试修改 `Makefile` 中 `LINKFLAGS` 的库链接顺序，或者检查是否重复链接了某些库。

### 2. **如何修改项目的外观或功能？**

- 您可以在 `source/` 目录下找到所有源代码文件进行修改。
- 界面资源文件存储在 `art/` 目录中，修改相关资源文件后，使用 `make refresh-art` 重新生成。
