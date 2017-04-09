#pragma once

// BackStagePageInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageInfo dialog

class CBackStagePageInfo : public CBCGPDialog
{
	DECLARE_DYNCREATE(CBackStagePageInfo)

// Construction
public:
	CBackStagePageInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_FORM_INFO };
	CBCGPButton	m_btnPreview;

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnPreview();
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	void OnDraw(CDC* pDC);
	void PreparePreviewBitmap();

	CString	m_strDocName;
	CString	m_strPath;
};
