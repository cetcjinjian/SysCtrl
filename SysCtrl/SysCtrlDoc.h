// SysCtrlDoc.h : interface of the CSysCtrlDoc class
//


#pragma once


class CSysCtrlDoc : public CDocument
{
protected: // create from serialization only
	CSysCtrlDoc();
	DECLARE_DYNCREATE(CSysCtrlDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CSysCtrlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


