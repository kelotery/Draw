#include "pch.h"
#include "gtest/gtest.h"
#include "ShapeAttributes.h" 

// ... TEST 宏和 main 函数 ...
// 1. 定义一个测试套件 (Test Fixture)
// 使用 TEST(TestSuiteName, TestName) 宏
TEST(ShapeAttributesTest, DefaultConstructorInitializesCorrectly)
{
    CShapeAttributes attrs;

    // 检查默认值是否符合预期
    // 假设默认线宽是 1, 默认模式是 LineMode
    EXPECT_EQ(attrs.m_lineWidth, 1);
    EXPECT_FALSE(attrs.m_isDashed);
    EXPECT_FALSE(attrs.m_isFilled);
    EXPECT_EQ(attrs.m_currentMode, LineMode);
    EXPECT_EQ(attrs.m_lineColor, RGB(0, 0, 0));
}

// 2. 测试 IsLineWidthValid 函数的边界条件
TEST(ShapeAttributesTest, LineWidthValidation)
{
    CShapeAttributes attrs;

    // a) 正常情况
    attrs.m_lineWidth = 10;
    EXPECT_TRUE(attrs.IsLineWidthValid());

    // b) 边界值：0
    attrs.m_lineWidth = 0;
    EXPECT_TRUE(attrs.IsLineWidthValid());

    // c) 边界值：20 (对应您的 DDV_MinMaxInt(pDX, LineWidth, 0, 20);)
    attrs.m_lineWidth = 20;
    EXPECT_TRUE(attrs.IsLineWidthValid());

    // d) 超出范围：21
    attrs.m_lineWidth = 21;
    EXPECT_FALSE(attrs.IsLineWidthValid());

    // e) 超出范围：-1
    attrs.m_lineWidth = -1;
    EXPECT_FALSE(attrs.IsLineWidthValid());
}

// 3. 测试 IsShapeMode 函数的逻辑
TEST(ShapeAttributesTest, ModeCheck)
{
    CShapeAttributes attrs;

    // a) 正确的形状模式
    attrs.m_currentMode = EllipseMode;
    EXPECT_TRUE(attrs.IsShapeMode());

    attrs.m_currentMode = RectangleMode;
    EXPECT_TRUE(attrs.IsShapeMode());

    // b) 非形状模式
    attrs.m_currentMode = LineMode;
    EXPECT_FALSE(attrs.IsShapeMode());

    attrs.m_currentMode = TextMode;
    EXPECT_FALSE(attrs.IsShapeMode());

    attrs.m_currentMode = PointMode;
    EXPECT_FALSE(attrs.IsShapeMode());
}

// GTest 入口点函数
int main(int argc, char** argv) {
    // 使用完整的命名空间路径
    ::testing::InitGoogleTest(&argc, argv);

    // RUN_ALL_TESTS 是一个宏，通常不需要命名空间前缀，但如果它找不到
    // 那么问题就是 GTest.h 文件没有被正确处理。
    return RUN_ALL_TESTS();
}