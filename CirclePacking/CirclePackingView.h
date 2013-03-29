// CirclePackingView.h : interface of the CCirclePackingView class
//


#pragma once

#include "CirclePackingDoc.h"
class CCirclePackingView : public CView
{
protected: // create from serialization only
	CCirclePackingView();
	DECLARE_DYNCREATE(CCirclePackingView)

// Attributes
public:
	CCirclePackingDoc* GetDocument() const;
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
	virtual ~CCirclePackingView();
	void OnPackingStart(char *msg);
	void OnPacking();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CirclePackingView.cpp
inline CCirclePackingDoc* CCirclePackingView::GetDocument() const
   { return reinterpret_cast<CCirclePackingDoc*>(m_pDocument); }
#endif

