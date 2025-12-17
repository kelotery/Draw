#pragma once

// 必须包含这两个，否则 CTime 和 CImage 无法识别
#include <afxwin.h>   
#include <atltime.h> 
#include <atlimage.h>
#include <vector>
#include <memory>

// ---------------------------------------------------------
// 定义 MyShape
// (为了测试方便，我们在这里定义它。如果你的 Dlg.h 里也有，
// 在测试项目中只包含 DrawingLogic.h 即可，不要同时包含 Dlg.h)
// ---------------------------------------------------------
#ifndef MY_SHAPE_DEF
#define MY_SHAPE_DEF
struct MyShape {
    int type;
    CPoint start;
    CPoint end;
    std::vector<CPoint> freePoints;
    COLORREF lineColor;
    COLORREF fillColor;
    int width;
    bool isDash;
    bool filled;
    CString text;
    std::shared_ptr<CImage> pImage;
};
#endif

class ShapeFactory {
public:
    static MyShape CreateShape(int type, CPoint start, CPoint end, COLORREF color, int width, bool isDash, bool isFilled)
    {
        MyShape s;
        s.type = type;
        s.start = start;
        s.end = end;
        s.lineColor = color;
        s.width = width;
        s.isDash = isDash;
        s.filled = isFilled;
        s.fillColor = color;
        s.text = _T("");
        s.pImage = nullptr;
        return s;
    }
};

class PathGenerator {
public:
    static CString GenerateSavePath(CString baseFolder, CTime currentTime)
    {
        CString timeStr = currentTime.Format(_T("%Y%m%d_%H%M%S"));
        CString fullPath;
        fullPath.Format(_T("%s\\Draw_%s.png"), baseFolder, timeStr);
        return fullPath;
    }
};
