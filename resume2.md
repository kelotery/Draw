# MFC绘画板
MFC简单绘图系统
---

# 🎨 MFC Advanced Drawing System (高级绘图系统)

![C++](https://img.shields.io/badge/Language-C++17-blue.svg) ![Framework](https://img.shields.io/badge/Framework-MFC-orange.svg) ![Test](https://img.shields.io/badge/Unit%20Test-Google%20Test-brightgreen.svg)

基于 **Microsoft Foundation Classes (MFC)** 开发的 Windows 桌面绘图应用程序。该系统采用面向对象设计，利用 `std::vector` 存储图元数据，实现了矢量化的绘图管理，支持多语言切换、撤销操作及单元测试验证。

## ✨ 主要功能 (Features)

### 1. 绘图模式 (Drawing Modes)
系统支持多种图元绘制（代码对应 `Mode` 枚举）：
*   **基础图形**：点 (Point)、直线 (Line)、椭圆 (Ellipse)、矩形 (Rectangle)。
*   **自由绘制**：手写笔模式 (Free Draw/OwnerDrawingMode)，支持连续轨迹记录。
*   **文本插入**：在画布指定位置插入文字 (Text)。
*   **图片导入**：支持导入 PNG、JPG、BMP 格式图片并显示。

### 2. 属性设置 (Attributes)
*   **颜色控制**：
    *   画笔颜色 (Line Color)：通过 `CColorDialog` 自定义。
    *   填充颜色 (Fill Color)：支持实心填充。
*   **线条样式**：
    *   **线宽**：自定义数值（默认 5px）。
    *   **线型**：支持实线 (Solid) 和虚线 (Dash)。
        *   *注：代码已包含针对 Windows GDI 的特殊处理，当选择虚线时自动适配线宽，保证虚线可见。*
*   **填充模式**：可切换“有填充”或“无填充” (Transparent)。

### 3. 操作与交互 (Operations)
*   **撤销功能 (Undo)**：基于栈的撤销机制，移除最后绘制的图元 (快捷键 `Ctrl+Z`)。
*   **清空画布**：一键清除所有内容。
*   **保存作品**：将当前画布保存为 PNG 图片，文件名自动包含时间戳 (快捷键 `Ctrl+S`)。
*   **多语言支持**：实时切换界面语言，支持 **中文**、**English**、**日本語**。

## 🛠️ 技术架构 (Technical Architecture)

### 核心类：`CDrawingSystemDlg`
*   **数据结构**：使用 `std::vector<MyShape> m_shapes` 存储所有绘制对象。这意味着绘图是**重绘 (Redraw)** 机制，而非简单的位图操作，从而实现了“撤销”功能。
*   **绘图引擎**：在 `OnPaint` 中遍历 `m_shapes` 容器，使用 GDI (`CPen`, `CBrush`, `CDC`) 实时渲染。
*   **消息拦截**：重写 `PreTranslateMessage` 以拦截键盘消息，实现 `Ctrl+Z` 和 `Ctrl+S` 快捷键。

### 关键逻辑实现
*   **虚线修复**：在 `OnPaint` 中实现了逻辑判断，当 `s.isDash` 为真时，强制设置 `CPen` 宽度为 1，解决了 MFC 中宽线条无法显示虚线的 GDI 限制。
*   **自动化保存**：保存路径自动生成，利用 `CTime` 格式化当前时间，防止文件名冲突。

## 🧪 单元测试 (Unit Testing)

本项目引入 **Google Test (gtest)** 框架，对剥离出的核心业务逻辑进行验证，确保系统稳定性。

### 测试模块
为了进行测试，核心逻辑被封装在独立的逻辑类中（如 `DrawingLogic.h`）：

1.  **ShapeFactory 测试**
    *   **测试目的**：验证图形工厂能否正确创建 `MyShape` 对象。
    *   **验证点**：检查图形类型（直线/矩形）、坐标初始化、颜色赋值、以及虚线属性的正确传递。
    *   **示例**：`EXPECT_EQ(1, shape.type)` 确保工厂生成的确实是直线模式。

2.  **PathGenerator 测试**
    *   **测试目的**：验证文件保存路径生成逻辑的正确性。
    *   **验证点**：确保生成的文件名符合 `Draw_YYYYMMDD_HHMMSS.png` 格式，且路径拼接无误。
    *   **优势**：避免了在测试时产生真实的垃圾文件，仅测试字符串逻辑。

## 🚀 快速开始 (Getting Started)

### 环境要求
*   Visual Studio 2019 / 2022
*   工作负载：使用 C++ 的桌面开发 (MFC)

### 编译与运行
1.  打开 `DrawingSystem.sln`。
2.  **重要提示**：在运行前，请检查 `CDrawingSystemDlg.cpp` 中的 `SaveCanvasAsImage` 函数。
    *   默认保存路径硬编码为：`C:\\Users\\17663\\Desktop\\ai大作业\\保存图片`。
    *   **请务必将其修改为您电脑上存在的路径**，否则保存功能可能会失败或创建文件夹失败。
3.  按 `F5` 编译并运行。

### 运行单元测试
1.  在解决方案中找到测试项目（例如 `DrawingSystemTests`）。
2.  打开 **测试资源管理器 (Test Explorer)**。
3.  点击 **运行所有测试**。

## 📝 待办事项 / 已知限制
*   **保存路径**：目前路径是硬编码的，建议修改为从 `CFileDialog` 获取或保存到“我的文档”。
*   **图片大小**：导入的图片目前显示在固定位置 `(0,0)`，未来可添加拖拽移动图片功能。

---
**Author**: 17663 (Based on User Path)
**Course**: AI Homework Project
