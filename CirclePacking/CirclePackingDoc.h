// CirclePackingDoc.h : interface of the CCirclePackingDoc class
//


#pragma once


class CCirclePackingDoc : public CDocument
{
protected: // create from serialization only
	CCirclePackingDoc();
	DECLARE_DYNCREATE(CCirclePackingDoc)

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
	virtual ~CCirclePackingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


