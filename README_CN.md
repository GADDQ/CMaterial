# CMaterial

![C++20](https://img.shields.io/badge/C++-20-blue.svg?style=for-the-badge&logo=c%2B%2B)
![CMake](https://img.shields.io/badge/CMake-4.1+-success.svg?style=for-the-badge&logo=cmake)
![License](https://img.shields.io/badge/License-MIT-orange.svg?style=for-the-badge)

![Platform](https://img.shields.io/badge/Platform-Windows-blue.svg?style=for-the-badge&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCI+PHBhdGggZmlsbD0iIzAwNzhENiIgZD0iTTAgMy40NDlMOS43NSAyLjExMnY5LjQwNUgwek0xMC44NDkgMS45NjJMMjQgMHYxMS41MTdIMTAuODQ5ek0wIDEyLjQ4M2g5Ljc1djkuNDA1TDAgMjAuNTUxek0xMC44NDkgMTIuNDgzSDI0VjI0bC0xMy4xNTEtMS45NjJ6Ii8+PC9zdmc+)
![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg?style=for-the-badge&logo=linux)
![Platform](https://img.shields.io/badge/Platform-Macos-black.svg?style=for-the-badge&logo=apple)

> [!WARNING]
> **仍在努力开发中！文档、截图、示例暂未就绪！**

基于 ImGui 和 GLFW 的现代跨平台 GUI 框架，使用 Material Design 3 设计语言实现默认附带组件。

---

## 简单
易于上手，足够强大。开发合理到令人觉得本该如此，却能轻松胜任复杂多倍的工作。

## 高性能
完全基于原生 C++ 20 驱动，双击即开，内存占用极小，性能及其友好。

## 极小体积
默认使用静态链接输出**单文件**，无需打包任何动态链接库，并尽量使用最精简的依赖库。Release 产物默认使用 [UPX](https://github.com/upx/upx) 进行压缩，以压缩至最小体积。

## 现代化
为现代 GUI 软件开发而精心构建的顶层架构。开箱即用，修复并原生支持 IME（输入法）。

## 高度定制化
利用 OpenGL 3.3 Core 与 ImGui API 随心所欲地设计你自己的组件，然后像原生 ImGui 控件一样调用它们。***无脑且极速的***构建复杂且精美的 UI。此外，一款可视化的 UI 编辑器在开发计划内。

---

## 依赖库
- **[GLFW](https://github.com/glfw/glfw)** : 一个轻量级、跨平台的 API，用于创建窗口、上下文、读取输入及处理事件。
- **[GLAD](https://github.com/dav1dde/glad)** : 基于官方规范的多语言 Vulkan/GL/GLES/EGL/GLX/WGL 加载器生成工具。
- **[tweeny](https://github.com/mobius3/tweeny)** : 一个专为游戏和其他精美交互式软件打造的复杂补间动画库。
- **[stb_image](https://github.com/nothings/stb)** : C/C++ 领域极具盛名的单头文件公共域图像加载库。

---

## 第三方工具链
*(以下工具仅用于项目开发与构建阶段)*
- **[CLion](https://www.jetbrains.com/clion/)** : 项目默认使用的 C/C++ 跨平台集成开发环境。
- **[UPX](https://github.com/upx/upx)** : 终极可执行文件压缩器。***仅用于压缩 Release 版本的二进制文件。***
- **[CMake](https://cmake.org/)** : 强大、工业标准的软件构建系统。
- **[MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/)** : 微软 Visual C++ 编译器，用于构建 Windows 版本。
- **[GCC](https://gcc.gnu.org/)** : GNU 编译器套件，用于构建 Linux 版本。