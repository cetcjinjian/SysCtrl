// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SysCtrl.h"

#include "MainFrm.h"
#include "BackStagePageInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_REGISTERED_MESSAGE(BCGM_ON_BEFORE_RIBBON_BACKSTAGE_VIEW, OnBeforeShowRibbonBackstageView)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	//m_font;
	//font = this->GetFont();
	//LOGFONT lf;
	//font->GetLogFont(&lf);
	//lf.lfHeight = 600;
	//lf.lfWeight = 700;
	//_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("ËÎÌå"));
	//m_font.CreateFontIndirect(&lf);
	//this->SetFont(&m_font);

	//m_wndRibbonBar.SetFont(&m_font);

	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: add your status bar panes here:
	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE1, _T("Pane 1"), TRUE), _T("Pane 1"));
	m_wndStatusBar.AddExtendedElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE2, _T("Pane 2"), TRUE), _T("Pane 2"));

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());

	const int nPaneSize = globalUtils.ScaleByDPI(200);

	


	const int nOutputPaneSize = globalUtils.ScaleByDPI(150);

	if (!m_wndOutput.Create (_T("Ö¸Áî»ØÀ¡"), this, CSize (nOutputPaneSize, nOutputPaneSize),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}
	m_wndOutput.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);


	

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndOutput);
	








	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




BOOL CMainFrame::CreateRibbonBar ()
{
	m_wndRibbonBar.EnableCustomization();

	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	if (!m_wndRibbonBar.LoadFromXML (_T("IDR_BCGP_RIBBON_XML")))
	{
		return FALSE;
	}

	CBCGPRibbonCategory* pBackstageCategory = m_wndRibbonBar.GetBackstageCategory ();

	if (pBackstageCategory != NULL)
	{
		CBCGPRibbonBackstageViewPanel* pBackstagePanel = DYNAMIC_DOWNCAST (CBCGPRibbonBackstageViewPanel, pBackstageCategory->GetPanel (0));

		if (pBackstagePanel != NULL)
		{
			pBackstagePanel->AttachViewToItem (4, new CBCGPRibbonBackstageViewItemForm(IDD_FORM_INFO, RUNTIME_CLASS(CBackStagePageInfo)), FALSE);
			pBackstagePanel->AttachRecentViewToItem(5, BCGP_SHOW_FOLDERS_LIST | BCGP_SHOW_PINS, FALSE);
			pBackstagePanel->AttachPrintPreviewToItem(6, FALSE);
		}
	}







	
	return TRUE;
}

LRESULT CMainFrame::OnRibbonCustomize (WPARAM wp, LPARAM /*lp*/)
{
	ShowOptions (wp == 0 ? 1 : 0);
	return 1;
}

void CMainFrame::OnToolsOptions()
{
	ShowOptions (0);
}

void CMainFrame::ShowOptions (int nPage)
{
	// Create custom categories:
	
	// "Popular" items:
	
	CList<UINT, UINT> lstPopular;
	
	lstPopular.AddTail (ID_FILE_NEW);
	lstPopular.AddTail (ID_FILE_OPEN);
	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_FILE_PRINT_PREVIEW);
	lstPopular.AddTail (ID_FILE_PRINT_DIRECT);
	lstPopular.AddTail (ID_EDIT_UNDO);
	
	// Hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);
	
	// All commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);

	// Create "Customize QAT" page:
	CBCGPRibbonCustomizeQATPage pageCustomizeQAT(&m_wndRibbonBar);
	
	pageCustomizeQAT.AddCustomCategory (_T("Popular Commands"), lstPopular);
	pageCustomizeQAT.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);
	pageCustomizeQAT.AddCustomCategory (_T("All Commands"), lstAll);
	
	// Create "Customize Ribbon" page:
	CBCGPRibbonCustomizeRibbonPage pageCustomizeRibbon(&m_wndRibbonBar);
	
	pageCustomizeRibbon.AddCustomCategory (_T("Popular Commands"), lstPopular);
	pageCustomizeRibbon.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);
	pageCustomizeRibbon.AddCustomCategory (_T("All Commands"), lstAll);
	
	// Create property sheet:
	CBCGPPropertySheet propSheet(_T("Options"), this, nPage);
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	propSheet.EnableLayout(TRUE, NULL, TRUE);
	propSheet.EnableVisualManagerStyle(TRUE, TRUE);
	
	propSheet.SetLook(CBCGPPropertySheet::PropSheetLook_List, -1 /* Default list width */);
	
	propSheet.AddPage (&pageCustomizeRibbon);
	
	propSheet.AddPage (&pageCustomizeQAT);

	// TODO: add your option pages here:
	// COptionsPage1 pageOptions1;
	// propSheet.AddPage (&pageOptions1);
	//
	// COptionsPage1 pageOptions2;
	// propSheet.AddPage (&pageOptions2);
	
	if (propSheet.DoModal() != IDOK)
	{
		return;
	}
}


void CMainFrame::OnViewOutput() 
{
	ShowControlBar (&m_wndOutput,
					!(m_wndOutput.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndOutput.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());


	
}




LRESULT CMainFrame::OnBeforeShowRibbonBackstageView(WPARAM, LPARAM)
{
	theApp.CreateScreenshot(m_bmpAppPreview);
	return 0;
}

