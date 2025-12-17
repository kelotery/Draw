#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include "pch.h"
#include "framework.h"
#include "DrawingSystem.h"
#include "DrawingSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDrawingSystemDlg::CDrawingSystemDlg(CWnd* pParent)
    : CDialogEx(IDD_DRAWINGSYSTEM_DIALOG, pParent), LineWidth(5), m_LineType(0), m_text(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    LineColor = RGB(0, 0, 255);
    ShapeColor = RGB(255, 0, 0);
    Mode = LineMode;
    startdrawing = false;
    isfilled = false;
    LineType = false;
}

void CDrawingSystemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, LineWidth);
    DDX_Radio(pDX, IDC_RADIO1, m_LineType);
    DDX_Control(pDX, IDC_COMBO1, m_fill);
    DDX_Control(pDX, IDC_COMBO2, m_Mode);
    DDX_Text(pDX, IDC_EDIT2, m_text);
    DDX_Control(pDX, IDC_COMBO3, m_Language);
}

BEGIN_MESSAGE_MAP(CDrawingSystemDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_BN_CLICKED(IDC_BUTTON1, &CDrawingSystemDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CDrawingSystemDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CDrawingSystemDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CDrawingSystemDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CDrawingSystemDlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CDrawingSystemDlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CDrawingSystemDlg::OnBnClickedButton7)
    ON_BN_CLICKED(IDC_BUTTON8, &CDrawingSystemDlg::OnBnClickedButton8)
    ON_EN_CHANGE(IDC_EDIT1, &CDrawingSystemDlg::OnEnChangeEdit1)
    ON_BN_CLICKED(IDC_RADIO1, &CDrawingSystemDlg::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &CDrawingSystemDlg::OnBnClickedRadio2)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CDrawingSystemDlg::OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO2, &CDrawingSystemDlg::OnCbnSelchangeCombo2)
    ON_CBN_SELCHANGE(IDC_COMBO3, &CDrawingSystemDlg::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()

BOOL CDrawingSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    m_Language.AddString(L"中文");
    m_Language.AddString(L"English");
    m_Language.AddString(L"日本語");
    m_Language.SetCurSel(0);
    m_currentLang = APP_LANG_CHINESE;
    UpdateAllUIStrings();
    return TRUE;
}

BOOL CDrawingSystemDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        BOOL bCtrl = (::GetKeyState(VK_CONTROL) < 0);
        if (bCtrl && pMsg->wParam == 'Z') { OnBnClickedButton8(); return TRUE; }
        if (bCtrl && pMsg->wParam == 'S') { SaveCanvasAsImage(); return TRUE; }
    }
    return CDialogEx::PreTranslateMessage(pMsg);
}

void CDrawingSystemDlg::UpdateAllUIStrings()
{
    if (!::IsWindow(m_hWnd)) return;

    // 1. 备份下拉框当前选择项，防止重置后丢失
    int nModeIdx = m_Mode.GetCurSel();
    int nFillIdx = m_fill.GetCurSel();

    m_Mode.ResetContent();
    m_fill.ResetContent();

    if (m_currentLang == APP_LANG_CHINESE)
    {
        // 模式下拉框
        m_Mode.AddString(L"点"); m_Mode.AddString(L"直线"); m_Mode.AddString(L"椭圆");
        m_Mode.AddString(L"矩形"); m_Mode.AddString(L"自由画");
        // 填充下拉框
        m_fill.AddString(L"有填充"); m_fill.AddString(L"无填充");

        // 按钮文字 (IDC_BUTTON1 - 8)
        GetDlgItem(IDC_BUTTON1)->SetWindowText(L"画笔颜色");
        GetDlgItem(IDC_BUTTON2)->SetWindowText(L"填充颜色");
        GetDlgItem(IDC_BUTTON3)->SetWindowText(L"清空画板");
        GetDlgItem(IDC_BUTTON4)->SetWindowText(L"插入文字");
        GetDlgItem(IDC_BUTTON5)->SetWindowText(L"导入图片");
        GetDlgItem(IDC_BUTTON6)->SetWindowText(L"保存(Ctrl+S)");
        GetDlgItem(IDC_BUTTON7)->SetWindowText(L"查看文件夹");
        GetDlgItem(IDC_BUTTON8)->SetWindowText(L"撤销(Ctrl+Z)");

        // 单选框 (IDC_RADIO1 - 2)
        GetDlgItem(IDC_RADIO1)->SetWindowText(L"实线");
        GetDlgItem(IDC_RADIO2)->SetWindowText(L"虚线");

        this->SetWindowText(L"高级绘图系统 v2.0");
    }
    else if (m_currentLang == APP_LANG_JAPANESE)
    {
        m_Mode.AddString(L"ドット"); m_Mode.AddString(L"直線"); m_Mode.AddString(L"楕円");
        m_Mode.AddString(L"矩形"); m_Mode.AddString(L"自由描画");
        m_fill.AddString(L"塗りつぶし"); m_fill.AddString(L"なし");

        GetDlgItem(IDC_BUTTON1)->SetWindowText(L"線の色");
        GetDlgItem(IDC_BUTTON2)->SetWindowText(L"塗りの色");
        GetDlgItem(IDC_BUTTON3)->SetWindowText(L"クリア");
        GetDlgItem(IDC_BUTTON4)->SetWindowText(L"テキスト");
        GetDlgItem(IDC_BUTTON5)->SetWindowText(L"画像挿入");
        GetDlgItem(IDC_BUTTON6)->SetWindowText(L"保存(Ctrl+S)");
        GetDlgItem(IDC_BUTTON7)->SetWindowText(L"フォルダ");
        GetDlgItem(IDC_BUTTON8)->SetWindowText(L"元に戻す(Ctrl+Z)");

        GetDlgItem(IDC_RADIO1)->SetWindowText(L"実線");
        GetDlgItem(IDC_RADIO2)->SetWindowText(L"破線");


        this->SetWindowText(L"お絵かきシステム v2.0");
    }
    else // English
    {
        m_Mode.AddString(L"Point"); m_Mode.AddString(L"Line"); m_Mode.AddString(L"Ellipse");
        m_Mode.AddString(L"Rect"); m_Mode.AddString(L"Free Draw");
        m_fill.AddString(L"Filled"); m_fill.AddString(L"No Fill");

        GetDlgItem(IDC_BUTTON1)->SetWindowText(L"Pen Color");
        GetDlgItem(IDC_BUTTON2)->SetWindowText(L"Fill Color");
        GetDlgItem(IDC_BUTTON3)->SetWindowText(L"Clear");
        GetDlgItem(IDC_BUTTON4)->SetWindowText(L"Add Text");
        GetDlgItem(IDC_BUTTON5)->SetWindowText(L"Import");
        GetDlgItem(IDC_BUTTON6)->SetWindowText(L"Save(Ctrl+S)");
        GetDlgItem(IDC_BUTTON7)->SetWindowText(L"Folder");
        GetDlgItem(IDC_BUTTON8)->SetWindowText(L"Undo(Ctrl+Z)");

        GetDlgItem(IDC_RADIO1)->SetWindowText(L"Solid");
        GetDlgItem(IDC_RADIO2)->SetWindowText(L"Dash");

        this->SetWindowText(L"Drawing System v2.0");
    }

    // 2. 恢复选择项索引
    m_Mode.SetCurSel(nModeIdx == CB_ERR ? 1 : nModeIdx);
    m_fill.SetCurSel(nFillIdx == CB_ERR ? 1 : nFillIdx);
}

void CDrawingSystemDlg::OnPaint()
{
    CPaintDC dc(this);
    if (!IsIconic()) {
        for (const auto& s : m_shapes) {
            if (s.type == ImageMode && s.pImage) {
                s.pImage->Draw(dc.GetSafeHdc(), s.start.x, s.start.y);
                continue;
            }
            CPen pen(s.isDash ? PS_DASH : PS_SOLID, s.width, s.lineColor);
            CBrush brush(s.fillColor), trans; trans.CreateStockObject(NULL_BRUSH);
            CPen* pOldPen = dc.SelectObject(&pen);
            CBrush* pOldBrush = dc.SelectObject(s.filled ? &brush : &trans);

            if (s.type == LineMode) { dc.MoveTo(s.start); dc.LineTo(s.end); }
            else if (s.type == EllipseMode) dc.Ellipse(s.start.x, s.start.y, s.end.x, s.end.y);
            else if (s.type == RectangleMode) dc.Rectangle(s.start.x, s.start.y, s.end.x, s.end.y);
            else if (s.type == PointMode) dc.SetPixel(s.start.x, s.start.y, s.lineColor);
            else if (s.type == TextMode) dc.TextOut(s.start.x, s.start.y, s.text);
            else if (s.type == OwnerDrawingMode) {
                for (size_t i = 1; i < s.freePoints.size(); ++i) {
                    dc.MoveTo(s.freePoints[i - 1]); dc.LineTo(s.freePoints[i]);
                }
            }
            dc.SelectObject(pOldPen); dc.SelectObject(pOldBrush);
        }
    }
}

void CDrawingSystemDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    DownPoint = point;
    if (Mode == OwnerDrawingMode) {
        startdrawing = true;
        MyShape s; s.type = OwnerDrawingMode; s.lineColor = LineColor; s.width = LineWidth;
        s.freePoints.push_back(point); m_shapes.push_back(s);
    }
    else if (Mode == PointMode || Mode == TextMode) {
        UpdateData(TRUE);
        MyShape s; s.type = Mode; s.start = point; s.lineColor = LineColor; s.text = m_text;
        m_shapes.push_back(s); Invalidate();
    }
    CDialogEx::OnLButtonDown(nFlags, point);
}

void CDrawingSystemDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    if (Mode == OwnerDrawingMode && startdrawing) {
        m_shapes.back().freePoints.push_back(point); Invalidate(FALSE);
    }
    CDialogEx::OnMouseMove(nFlags, point);
}

void CDrawingSystemDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (Mode >= LineMode && Mode <= RectangleMode) {
        MyShape s; s.type = Mode; s.start = DownPoint; s.end = point;
        s.lineColor = LineColor; s.fillColor = ShapeColor; s.width = LineWidth;
        s.isDash = LineType; s.filled = isfilled; m_shapes.push_back(s);
    }
    startdrawing = false; Invalidate();
    CDialogEx::OnLButtonUp(nFlags, point);
}

void CDrawingSystemDlg::OnBnClickedButton1() // 线条颜色
{
    CColorDialog dlg(LineColor);
    if (dlg.DoModal() == IDOK) LineColor = dlg.GetColor();
}

void CDrawingSystemDlg::OnBnClickedButton2() // 填充颜色（修复链接错误的关键）
{
    CColorDialog dlg(ShapeColor);
    if (dlg.DoModal() == IDOK) ShapeColor = dlg.GetColor();
}

void CDrawingSystemDlg::OnBnClickedButton5() // 导入图片
{
    TCHAR szFilter[] = _T("Images(*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp||");
    CFileDialog dlg(TRUE, NULL, NULL, 0, szFilter, this);
    if (dlg.DoModal() == IDOK) {
        auto img = std::make_shared<CImage>();
        if (SUCCEEDED(img->Load(dlg.GetPathName()))) {
            MyShape s; s.type = ImageMode; s.start = CPoint(0, 0); s.pImage = img;
            m_shapes.push_back(s); Invalidate();
        }
    }
}

void CDrawingSystemDlg::SaveCanvasAsImage()
{
    CClientDC dc(this); CRect r; GetClientRect(&r);
    CImage img; img.Create(r.Width(), r.Height(), 32);
    BitBlt(img.GetDC(), 0, 0, r.Width(), r.Height(), dc, 0, 0, SRCCOPY);

    CString path = _T("C:\\Users\\17663\\Desktop\\ai大作业\\保存图片");
    if (GetFileAttributes(path) == INVALID_FILE_ATTRIBUTES) CreateDirectory(path, NULL);
    CString name = path + _T("\\Draw_") + CTime::GetCurrentTime().Format(_T("%Y%m%d_%H%M%S")) + _T(".png");

    img.Save(name);
    img.ReleaseDC();
    MessageBox(m_currentLang == APP_LANG_CHINESE ? L"保存成功！" : L"Saved Successfully!");
}

void CDrawingSystemDlg::OnBnClickedButton8() { if (!m_shapes.empty()) { m_shapes.pop_back(); Invalidate(); } }
void CDrawingSystemDlg::OnBnClickedButton3() { m_shapes.clear(); Invalidate(); }
void CDrawingSystemDlg::OnCbnSelchangeCombo2() { Mode = m_Mode.GetCurSel(); }
void CDrawingSystemDlg::OnCbnSelchangeCombo1() { isfilled = (m_fill.GetCurSel() == 0); }
void CDrawingSystemDlg::OnCbnSelchangeCombo3() { m_currentLang = (LanguageID)m_Language.GetCurSel(); UpdateAllUIStrings(); }
void CDrawingSystemDlg::OnBnClickedRadio1() { LineType = false; }
void CDrawingSystemDlg::OnBnClickedRadio2() { LineType = true; }
void CDrawingSystemDlg::OnBnClickedButton6() { SaveCanvasAsImage(); }
void CDrawingSystemDlg::OnBnClickedButton7() { ShellExecute(NULL, L"explore", L"C:\\Users\\17663\\Desktop\\ai大作业\\保存图片", NULL, NULL, SW_SHOW); }
void CDrawingSystemDlg::OnBnClickedButton4() { Mode = TextMode; }
void CDrawingSystemDlg::OnEnChangeEdit1() { UpdateData(TRUE); }
void CDrawingSystemDlg::OnSysCommand(UINT nID, LPARAM lParam) { CDialogEx::OnSysCommand(nID, lParam); }
HCURSOR CDrawingSystemDlg::OnQueryDragIcon() { return static_cast<HCURSOR>(m_hIcon); }