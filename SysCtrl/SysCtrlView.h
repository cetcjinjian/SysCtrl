// SysCtrlView.h : interface of the CSysCtrlView class
//


#pragma once

#include "MyDataGrid.h"
#include "TransData_Manager.h"
#include "ProtocolData_Manager.h"
#include "Buffer.h"

class CSysCtrlView : public CView
{
protected: // create from serialization only
	CSysCtrlView();
	DECLARE_DYNCREATE(CSysCtrlView)

// Attributes
public:
	CSysCtrlDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSysCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnChangeVisualManager(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	CMyDataGrid*	pGridCtrl;
	TransData_Manager* pTrans_Manager;
	ProtocolData_Manager* pProtocol_Manager;
	CBuffer* m_pBuffer_recv;
	CBuffer* m_pBuffer_send;



	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void AdjustLayout();
};

#ifndef _DEBUG  // debug version in SysCtrlView.cpp
inline CSysCtrlDoc* CSysCtrlView::GetDocument() const
   { return reinterpret_cast<CSysCtrlDoc*>(m_pDocument); }
#endif

