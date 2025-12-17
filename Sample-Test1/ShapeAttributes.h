#pragma once
// ShapeAttributes.h
#pragma once

#include <afxwin.h> // 包含 CPoint 和 COLORREF

// 模拟您的 DrawingMode 枚举
enum DrawingMode
{
    PointMode,
    LineMode,
    EllipseMode,
    RectangleMode,
    OwnerDrawingMode,
    TextMode,
    ImageMode
};

class CShapeAttributes
{
public:
    COLORREF m_lineColor;
    COLORREF m_shapeColor;
    int m_lineWidth;
    bool m_isDashed;     // 对应您的 LineType
    bool m_isFilled;     // 对应您的 isfilled
    DrawingMode m_currentMode;

    CShapeAttributes()
        : m_lineColor(RGB(0, 0, 0)), m_shapeColor(RGB(0, 0, 0)),
        m_lineWidth(1), m_isDashed(false), m_isFilled(false),
        m_currentMode(LineMode)
    {
    }

    // --- 核心逻辑函数：用于验证属性的有效性 ---

    // 检查线宽是否在有效范围内 (0到20)
    bool IsLineWidthValid() const
    {
        return (m_lineWidth >= 0 && m_lineWidth <= 20);
    }

    // 检查模式是否是“形状绘制”模式 (排除点、自由绘制、文字、图片)
    bool IsShapeMode() const
    {
        return (m_currentMode == EllipseMode || m_currentMode == RectangleMode);
    }
};