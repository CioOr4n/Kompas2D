
// BuildPathsView.cpp: реализация класса CBuildPathsView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "BuildPaths.h"
#endif
#include "Figures.h"
#include <memory>
#include "BuildPathsDoc.h"
#include "BuildPathsView.h"
#include "PropertiesWnd.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBuildPathsView

IMPLEMENT_DYNCREATE(CBuildPathsView, CView)

BEGIN_MESSAGE_MAP(CBuildPathsView, CView)
	ON_WM_CONTEXTMENU()
	

	ON_WM_LBUTTONDOWN()

	ON_WM_MOUSEMOVE()

	ON_COMMAND(ID_LINE2P, &CBuildPathsView::OnLine2p)
	ON_COMMAND(ID_LINELA, &CBuildPathsView::OnLinela)
	ON_COMMAND(ID_ARC3P, &CBuildPathsView::OnArc3p)
	ON_COMMAND(ID_ARC2P, &CBuildPathsView::OnArc2p)
	ON_UPDATE_COMMAND_UI(ID_LINE2P, &CBuildPathsView::OnUpdateLine2p)
	ON_UPDATE_COMMAND_UI(ID_LINELA, &CBuildPathsView::OnUpdateLinela)
	ON_UPDATE_COMMAND_UI(ID_ARC3P, &CBuildPathsView::OnUpdateArc3p)
	ON_UPDATE_COMMAND_UI(ID_ARC2P, &CBuildPathsView::OnUpdateArc2p)
	ON_COMMAND(IDS_ENTER, &CBuildPathsView::EnterData)

	ON_COMMAND(ID_GDI, &CBuildPathsView::OnGdi)
END_MESSAGE_MAP()

// Создание или уничтожение CBuildPathsView

CBuildPathsView::CBuildPathsView() noexcept
{


}

CBuildPathsView::~CBuildPathsView()
{
}

BOOL CBuildPathsView::PreCreateWindow(CREATESTRUCT& cs)
{
	
	return CView::PreCreateWindow(cs);
}

// Рисование CBuildPathsView


void CBuildPathsView::OnDraw(CDC* pDC)
{

	m_drawer = std::make_unique<GDIDrawer>(pDC);
	CBuildPathsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	std::list<Path>& listOfPath = pDoc->GetPaths();
	//вызов в цикле отрисовщика
	std::list<Path>& listOfEndPath = pDoc->GetEndPaths();
	for (auto& path :listOfPath)
		path.Draw(*m_drawer);
	for (auto& path : listOfEndPath)
		path.Draw(*m_drawer);
	
	
}



void CBuildPathsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBuildPathsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CBuildPathsView

#ifdef _DEBUG
void CBuildPathsView::AssertValid() const
{
	CView::AssertValid();
}

void CBuildPathsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBuildPathsDoc* CBuildPathsView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBuildPathsDoc)));
	return (CBuildPathsDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CBuildPathsView






// нажатие на левую кнопку мыши
void CBuildPathsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (elemType > TypeElem::arc2p || elemType < TypeElem::line2p)
	{
		AfxMessageBox(_T("Выберите построение"));
		return;
	}
	// получение области рисования
	CClientDC aDC(this);
	CBuildPathsDoc* pDoc = GetDocument();
	Point temp;
	temp.m_x = point.x;
	temp.m_y = point.y;

	m_controller->AddPoint(temp);
	
	OnDraw(&aDC);
	 //вызов перерисовщик
	CView::OnLButtonDown(nFlags, point);
}


// отображение текущих координат
void CBuildPathsView::OnMouseMove(UINT nFlags, CPoint point)
 {
	CString pos; 
	pos.Format(_T("%d"), point.x);
	CMFCToolBarEditBoxButton::SetContentsAll(IDS_X, pos);
	pos.Format(_T("%d"), point.y);
	CMFCToolBarEditBoxButton::SetContentsAll(IDS_Y, pos);
	CView::OnMouseMove(nFlags, point);
}




void CBuildPathsView::OnLine2p()
{
	CBuildPathsDoc* pDoc = GetDocument();
	elemType = TypeElem::line2p;
	m_controller = std::make_unique<LineController>(elemType, pDoc);
	CMFCToolBarEditBoxButton* editRad = CMFCToolBarEditBoxButton::GetByCmd(IDS_RAD);
	editRad->EnableWindow(false);
	CMFCToolBarEditBoxButton* editLength = CMFCToolBarEditBoxButton::GetByCmd(IDS_LENGTH);
	editLength->EnableWindow(false);
	CMFCToolBarEditBoxButton* editAngle = CMFCToolBarEditBoxButton::GetByCmd(IDS_ANGLE);
	editAngle->EnableWindow(false);
	CMFCToolBarComboBoxButton* combo = CMFCToolBarComboBoxButton::GetByCmd(IDS_COMBO);
	combo->SetFlatMode(false);
}


void CBuildPathsView::OnLinela()
{
	CBuildPathsDoc* pDoc = GetDocument();
	elemType = TypeElem::linela;
	m_controller = std::make_unique<LineController>(elemType, pDoc);
	CMFCToolBarEditBoxButton* editRad = CMFCToolBarEditBoxButton::GetByCmd(IDS_RAD);
	editRad->EnableWindow(false);
	CMFCToolBarEditBoxButton* editLength = CMFCToolBarEditBoxButton::GetByCmd(IDS_LENGTH);
	editLength->EnableWindow(true);
	CMFCToolBarEditBoxButton* editAngle = CMFCToolBarEditBoxButton::GetByCmd(IDS_ANGLE);
	editAngle->EnableWindow(true);
	CMFCToolBarComboBoxButton* combo = CMFCToolBarComboBoxButton::GetByCmd(IDS_COMBO);
	combo->SetFlatMode(false);
}


void CBuildPathsView::OnArc3p()
{
	CBuildPathsDoc* pDoc = GetDocument();
	elemType = TypeElem::arc3p;
	m_controller = std::make_unique<ArcController>(elemType, pDoc);
	CMFCToolBarEditBoxButton* editLength = CMFCToolBarEditBoxButton::GetByCmd(IDS_LENGTH);
	editLength->EnableWindow(false);
	CMFCToolBarEditBoxButton* editAngle = CMFCToolBarEditBoxButton::GetByCmd(IDS_ANGLE);
	editAngle->EnableWindow(false);
	CMFCToolBarEditBoxButton* editRad = CMFCToolBarEditBoxButton::GetByCmd(IDS_RAD);
	editRad->EnableWindow(false);
	CMFCToolBarComboBoxButton* combo = CMFCToolBarComboBoxButton::GetByCmd(IDS_COMBO);
	combo->SetFlatMode(false);

}


void CBuildPathsView::OnArc2p()
{
	CBuildPathsDoc* pDoc = GetDocument();
	elemType = TypeElem::arc2p;
	m_controller = std::make_unique<ArcController>(elemType, pDoc);
	CMFCToolBarEditBoxButton* editLength = CMFCToolBarEditBoxButton::GetByCmd(IDS_LENGTH);
	editLength->EnableWindow(false);
	CMFCToolBarEditBoxButton* editAngle = CMFCToolBarEditBoxButton::GetByCmd(IDS_ANGLE);
	editAngle->EnableWindow(false);
	CMFCToolBarEditBoxButton* editRad = CMFCToolBarEditBoxButton::GetByCmd(IDS_RAD);
	editRad->EnableWindow(true);
	CMFCToolBarComboBoxButton* combo = CMFCToolBarComboBoxButton::GetByCmd(IDS_COMBO);
	combo->SetFlatMode(true);
}


void CBuildPathsView::OnUpdateLine2p(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(elemType == TypeElem::line2p);
	
}


void CBuildPathsView::OnUpdateLinela(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(elemType == TypeElem::linela);
}


void CBuildPathsView::OnUpdateArc3p(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(elemType == TypeElem::arc3p);
}


void CBuildPathsView::OnUpdateArc2p(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(elemType == TypeElem::arc2p);
}

void CBuildPathsView::EnterData()
{
	switch (elemType)
	{
	case TypeElem::linela:
	{
		CString temp = CMFCToolBarEditBoxButton::GetContentsAll(IDS_LENGTH);
		if (temp != "")
		{
			int length = _ttoi(temp);
			if (length <= 0)
			{
				AfxMessageBox(_T("Длина не может быть меньше или равен 0"));
				break;
			}
			else
			{
				m_controller->InputValue(TypeOfData::length, length);
				CMFCToolBarEditBoxButton::SetContentsAll(IDS_LENGTH, _T(""));
			}
		}
		temp = CMFCToolBarEditBoxButton::GetContentsAll(IDS_ANGLE); 
		if (temp != "")
		{
			int angle = _ttoi(temp);
				m_controller->InputValue(TypeOfData::angle, angle);
				CMFCToolBarEditBoxButton::SetContentsAll(IDS_ANGLE, _T(""));
		}
	}
	break;
	case TypeElem::arc2p:
	{
		CString temp = CMFCToolBarEditBoxButton::GetContentsAll(IDS_RAD);
		if (temp != "")
		{
			int rad = _ttoi(temp);
			if (rad <= 0)
			{
				AfxMessageBox(_T("Радиус не может быть меньше или равен 0"));
				break;
			}
			else
			{
				m_controller->InputValue(TypeOfData::rad, rad);
				CMFCToolBarEditBoxButton::SetContentsAll(IDS_LENGTH, _T(""));
			}
		}
		int index = CMFCToolBarComboBoxButton::GetCurSelAll(IDS_COMBO);
		m_controller->InputValue(TypeOfData::clock, index);
		
	}
	break;
	}
	CClientDC aDC(this);
	OnDraw(&aDC);
}



void CBuildPathsView::OnGdi()
{
	
}
