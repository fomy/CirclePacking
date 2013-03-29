// CirclePackingView.cpp : implementation of the CCirclePackingView class
//

#include "stdafx.h"
#include "CirclePacking.h"

#include "CirclePackingDoc.h"
#include "CirclePackingView.h"
#include "Packing.h"
#include "InputDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCirclePackingView
CCirclePackingView *pView;

IMPLEMENT_DYNCREATE(CCirclePackingView, CView)

BEGIN_MESSAGE_MAP(CCirclePackingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCirclePackingView construction/destruction

CCirclePackingView::CCirclePackingView()
{
	// TODO: add construction code here

}

CCirclePackingView::~CCirclePackingView()
{
}

BOOL CCirclePackingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	pView=this;
	return CView::PreCreateWindow(cs);
}

// CCirclePackingView drawing

void CCirclePackingView::OnDraw(CDC* /*pDC*/)
{
	CCirclePackingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCirclePackingView printing

BOOL CCirclePackingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCirclePackingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCirclePackingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCirclePackingView diagnostics

#ifdef _DEBUG
void CCirclePackingView::AssertValid() const
{
	CView::AssertValid();
}

void CCirclePackingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCirclePackingDoc* CCirclePackingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCirclePackingDoc)));
	return (CCirclePackingDoc*)m_pDocument;
}
#endif //_DEBUG


// CCirclePackingView message handlers
void DrawCircle(Circle circle)
{
	CClientDC   dc(pView); 
	CPoint   point(MULTI*circle.x+CENTREX,MULTI*circle.y+CENTREY);
	int r=MULTI*circle.radius;
	dc.Arc(point.x-r,point.y-r,point.x+r,point.y+r \
		,point.x-r,point.y \
		,point.x-r,point.y);
}
// CCyclePackingView message handlers
void DrawPattern(Pattern pattern)
{
	CClientDC   dc(pView); 
	pView->Invalidate();
	pView->UpdateWindow();
	DrawCircle(*pattern.container);
	for(int i=0;i<pattern.N;++i)
	{
		Circle *circle=pattern.circles[i];
		double r=circle->radius;
		DrawCircle(*circle);
	}
}

void CCirclePackingView::OnPacking()
{
	CInputDlg inputDlg;
	inputDlg.DoModal();
}
void CCirclePackingView::OnPackingStart(char *msg)
{
	/*
	* 协议： 容器的半径\0小圆个数\0小圆1的半径\0小圆2的半径\0
	*/
	time_t start=time(NULL);

	int ret=PackingMain(2, &msg);
	
	time_t end=time(NULL);
	time_t time=end-start;
	if(ret==0)
	{
		char *message=(char*)malloc(100*sizeof(char));
		sprintf(message, "已找到最优解，运行时间为：%d秒", time);
		AfxMessageBox(message);
		free(message);
	}
	/*还未实现*/
	else
	{
		char *message=(char*)malloc(100*sizeof(char));
		sprintf(message, "未找到最优解，运行时间为：%d秒", time);
		AfxMessageBox(message);
		free(message);
	}
}