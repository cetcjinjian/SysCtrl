// outputbar.cpp : implementation of the COutputBar class
//

#include "stdafx.h"
#include "SysCtrl.h"
#include "outputbar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

COutputBar::COutputBar()
{
	// TODO: add one-time construction code here
}

COutputBar::~COutputBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tabs window:
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_3D, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create list windows:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | LVS_REPORT;
	
	m_wndList1.m_bVisualManagerStyle = TRUE;

	//m_wndList1.ModifyStyle(NULL,WS_VSCROLL, 0);

	if (!m_wndList1.Create (dwViewStyle, rectDummy, &m_wndTabs, 2))
	{
		TRACE0("Failed to create output view\n");
		return -1;      // fail to create
	}

	// Attach list windows to tab:

	m_wndList1.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_wndTabs.AddTab (&m_wndList1, _T("指令回馈"), -1);

	m_wndList1.InsertColumn(1, _T("收发序号"), LVCFMT_CENTER, 350);
	m_wndList1.InsertColumn(2, _T("收发时间"), LVCFMT_CENTER, 350);
	m_wndList1.InsertColumn(3, _T("收发类型"), LVCFMT_CENTER, 350);
	m_wndList1.InsertColumn(4, _T("收发指令"), LVCFMT_CENTER, 350);

	

	
	SetMyFont();

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	CRect rectClient;
	GetClientRect(rectClient);
	int width = rectClient.right / 4;
	if (width < 100)
		width = 200;
	for (int i = 0; i < 4; ++i)
	{
		m_wndList1.SetColumnWidth(i,width);
	}
	//Invalidate();
	//this->SetRedraw();
	m_wndList1.ShowScrollBar(SB_HORZ, FALSE);
	m_wndList1.SetRedraw(true);
	

}


void COutputBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CBCGPDockingControlBar::OnPaint()

	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	//font = pFrame->m_wndRibbonBar.GetFont();
	//CFont m_font;
	//LOGFONT lf;
	//font->GetLogFont(&lf);
	//lf.lfHeight = 20;
	//lf.lfWeight = 700;
	//_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("宋体"));
	//m_font.CreateFontIndirect(&lf);
	//this->SetFont(&m_font);

}



void COutputBar::SetMyFont()
{
	LOGFONT logFont;
	logFont.lfHeight = 16;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = 700;
	logFont.lfItalic = 0;
	logFont.lfUnderline = 0;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = ANSI_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;

	_tcscpy_s(logFont.lfFaceName, LF_FACESIZE, _T("宋体"));
	m_font.CreateFontIndirect(&logFont);
	m_wndList1.SetFont(&m_font);
}