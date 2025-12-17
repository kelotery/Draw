#include "pch.h"
#include "gtest/gtest.h"

// 必须再次包含这个，确保测试环境加载 MFC
#include <afxwin.h> 

// 【关键修改】：请尝试使用绝对路径，或者确认 ../DrawingSystem 是正确的相对路径
// 如果你的测试项目文件夹和 DrawingSystem 文件夹是并列的，下面是对的：
#include "../DrawingSystem/DrawingLogic.h"

// 如果上面报错，请暂时用绝对路径代替，例如：
// #include "D:\\allworkTXT\\ai\\test1\\draw\\DrawingSystem\\DrawingLogic.h"

TEST(ShapeFactoryTest, CreateLineShape) {
    // 1. Arrange
    CPoint start(10, 10);
    CPoint end(100, 100);
    COLORREF red = RGB(255, 0, 0);
    int width = 5;

    // 2. Act
    MyShape shape = ShapeFactory::CreateShape(1, start, end, red, width, true, false);

    // 3. Assert
    EXPECT_EQ(1, shape.type);
    EXPECT_EQ(10, shape.start.x);
    EXPECT_EQ(100, shape.end.y);
    EXPECT_EQ(5, shape.width);
    EXPECT_TRUE(shape.isDash);

    // 【修复报错关键点 1】：COLORREF 是 unsigned long，不能直接和 int 比较
    // 我们强制转成 unsigned int 进行比较
    EXPECT_EQ((unsigned int)red, (unsigned int)shape.lineColor);
}

TEST(SerializerLogicTest, GenerateFileName) {
    // 1. Arrange
    CTime mockTime(2025, 12, 25, 14, 30, 0);
    CString folder = _T("D:\\TestFolder");

    // 2. Act
    CString result = PathGenerator::GenerateSavePath(folder, mockTime);
    CString expected = _T("D:\\TestFolder\\Draw_20251225_143000.png");

    // 【修复报错关键点 2】：CString 必须转换成 C风格字符串 才能被 GTest 比较
    // 使用 .GetString()
    EXPECT_STREQ(expected.GetString(), result.GetString());
}

TEST(ShapeFactoryTest, CheckDefaultInitialization) {
    CPoint p(0, 0);
    MyShape shape = ShapeFactory::CreateShape(0, p, p, 0, 1, false, false);

    // 验证 CString 是否为空，同样需要 GetString() 或者 IsEmpty()
    EXPECT_TRUE(shape.text.IsEmpty());

    // 指针可以直接比较
    EXPECT_EQ(nullptr, shape.pImage);
}
