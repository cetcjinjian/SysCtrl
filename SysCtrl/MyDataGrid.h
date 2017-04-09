#pragma once
#include <BCGPGridCtrl.h>


class CMyDataGrid : public CBCGPGridCtrl
{
public:

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	
	void SetRowHeight();
	void SetMyFont();

private:
	CFont m_font;
	CFont *font;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};