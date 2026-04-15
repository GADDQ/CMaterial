# CMaterial

![C++20](https://img.shields.io/badge/C++-20-blue.svg?style=for-the-badge&logo=c%2B%2B)
![CMake](https://img.shields.io/badge/CMake-4.1+-success.svg?style=for-the-badge&logo=cmake)
![License](https://img.shields.io/badge/License-MIT-orange.svg?style=for-the-badge)

![Platform](https://img.shields.io/badge/Platform-Windows-blue.svg?style=for-the-badge&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCI+PHBhdGggZmlsbD0iIzAwNzhENiIgZD0iTTAgMy40NDlMOS43NSAyLjExMnY5LjQwNUgwek0xMC44NDkgMS45NjJMMjQgMHYxMS41MTdIMTAuODQ5ek0wIDEyLjQ4M2g5Ljc1djkuNDA1TDAgMjAuNTUxek0xMC44NDkgMTIuNDgzSDI0VjI0bC0xMy4xNTEtMS45NjJ6Ii8+PC9zdmc+)
![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg?style=for-the-badge&logo=linux)
![Platform](https://img.shields.io/badge/Platform-Macos-black.svg?style=for-the-badge&logo=apple)

> [!WARNING]
> **Actively under development! Documentation, screenshots, and examples are NOT yet available.**

A modern cross-platform GUI framework based on ImGui and GLFW, featuring Material Design 3 by default.

---

## Simple
Easy to use, yet powerful enough. The development experience is so logical and intuitive that it feels like second nature, while effortlessly handling incredibly complex workloads.

## High Performance
Fully powered by native C++ 20. It launches instantly on double-click, features a minimal memory footprint, and is extremely performance-friendly.

## Ultra Small
Outputs a **single executable file** by default via static linking—no need to bundle any dynamic libraries (DLLs/SOs). Built with the leanest possible dependencies, and Release binaries are compressed with [UPX](https://github.com/upx/upx) to achieve the absolute minimum footprint.

## Modern
A meticulously built top-level architecture designed for modern GUI software development. Out of the box, it fixes and natively supports IME (Input Method Editor).

## Highly Customizable
Design your own components however you wish using OpenGL 3.3 Core and ImGui APIs, then use them just like native ImGui widgets. It is ***stupidly easy and fast*** to build complex and beautiful UIs. Additionally, a visual UI editor is on the roadmap.

---

## Libraries
- **[GLFW](https://github.com/glfw/glfw)** : A lightweight, cross-platform API for creating windows, contexts, handling input and events.
- **[GLAD](https://github.com/dav1dde/glad)** : A multi-Language Vulkan/GL/GLES/EGL/GLX/WGL loader-generator based on the official specifications.
- **[tweeny](https://github.com/mobius3/tweeny)** : An inbetweening library designed for the creation of complex animations and beautiful interactive software.
- **[stb_image](https://github.com/nothings/stb)** : A highly renowned single-file public domain library for loading images in C/C++.

---

## Third-Party Toolchain
*(These tools are strictly for the development and build processes)*
- **[CLion](https://www.jetbrains.com/clion/)** : The recommended cross-platform C/C++ IDE for this project.
- **[UPX](https://github.com/upx/upx)** : The Ultimate Packer for eXecutables. ***Used strictly for compressing Release binaries.***
- **[CMake](https://cmake.org/)** : A powerful, industry-standard software build system.
- **[MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/)** : Microsoft Visual C++ Compiler, used for Windows builds.
- **[GCC](https://gcc.gnu.org/)** : The GNU Compiler Collection, used for Linux builds.