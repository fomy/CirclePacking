// CirclePackingDoc.cpp : implementation of the CCirclePackingDoc class
//

#include "stdafx.h"
#include "CirclePacking.h"

#include "CirclePackingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCirclePackingDoc

IMPLEMENT_DYNCREATE(CCirclePackingDoc, CDocument)

BEGIN_MESSAGE_MAP(CCirclePackingDoc, CDocument)
END_MESSAGE_MAP()


// CCirclePackingDoc construction/destruction

CCirclePackingDoc::CCirclePackingDoc()
{
	// TODO: add one-time construction code here

}

CCirclePackingDoc::~CCirclePackingDoc()
{
}

BOOL CCirclePackingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCirclePackingDoc serialization

void CCirclePackingDoc::Serialize(CArchive& ar)
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


// CCirclePackingDoc diagnostics

#ifdef _DEBUG
void CCirclePackingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCirclePackingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCirclePackingDoc commands
