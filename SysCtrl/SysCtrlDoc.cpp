// SysCtrlDoc.cpp : implementation of the CSysCtrlDoc class
//

#include "stdafx.h"
#include "SysCtrl.h"

#include "SysCtrlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSysCtrlDoc

IMPLEMENT_DYNCREATE(CSysCtrlDoc, CDocument)

BEGIN_MESSAGE_MAP(CSysCtrlDoc, CDocument)
END_MESSAGE_MAP()


// CSysCtrlDoc construction/destruction

CSysCtrlDoc::CSysCtrlDoc()
{
	// TODO: add one-time construction code here

}

CSysCtrlDoc::~CSysCtrlDoc()
{
}

BOOL CSysCtrlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSysCtrlDoc serialization

void CSysCtrlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CSysCtrlDoc diagnostics

#ifdef _DEBUG
void CSysCtrlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSysCtrlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSysCtrlDoc commands
