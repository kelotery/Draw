#pragma once
#include <vector>
#include <memory>
#include <atlimage.h>

// 图形数据结构
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

// 枚举定义
enum DrawingMode { PointMode = 0, LineMode, EllipseMode, RectangleMode, OwnerDrawingMode, TextMode, ImageMode };
enum LanguageID { APP_LANG_CHINESE = 0, APP_LANG_ENGLISH = 1, APP_LANG_JAPANESE = 2 };

class CDrawingSystemDlg : public CDialogEx
{
public:
    CDrawingSystemDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DRAWINGSYSTEM_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    HICON m_hIcon;
    DECLARE_MESSAGE_MAP()

public:
    COLORREF LineColor;
    COLORREF ShapeColor;
    bool LineType;
    bool isfilled;
    int LineWidth;
    int m_LineType;
    int Mode;
    bool startdrawing;
    CPoint DownPoint;
    CString m_text;

    CComboBox m_Language, m_fill, m_Mode;
    LanguageID m_currentLang;

    std::vector<MyShape> m_shapes;

    void UpdateAllUIStrings();
    void SaveCanvasAsImage();

    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedButton1(); // 线色
    afx_msg void OnBnClickedButton2(); // 填充色
    afx_msg void OnBnClickedButton3(); // 清空
    afx_msg void OnBnClickedButton4(); // 文字模式
    afx_msg void OnBnClickedButton5(); // 导入图片
    afx_msg void OnBnClickedButton6(); // 保存
    afx_msg void OnBnClickedButton7(); // 查看文件夹
    afx_msg void OnBnClickedButton8(); // 撤销
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnCbnSelchangeCombo1();
    afx_msg void OnCbnSelchangeCombo2();
    afx_msg void OnCbnSelchangeCombo3();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg HCURSOR OnQueryDragIcon();
};