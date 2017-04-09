// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "OutputBar.h"


class CMainFrame : public CBCGPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

	CBitmap& GetAppPreview() { return m_bmpAppPreview; }

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public :  // control bar embedded members
	CBCGPRibbonStatusBar	m_wndStatusBar;
	CBCGPRibbonBar			m_wndRibbonBar;
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	COutputBar				m_wndOutput;
	
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg void OnToolsOptions();
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);

	afx_msg LRESULT OnBeforeShowRibbonBackstageView(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	BOOL CreateRibbonBar ();
	void ShowOptions (int nPage);

	CBitmap m_bmpAppPreview;

public:
	//CFont m_font;
	//CFont* font;
};
