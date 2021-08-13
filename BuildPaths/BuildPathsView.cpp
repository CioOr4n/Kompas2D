
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
	
	CClientDC aDC(this);
	CRect rcClient;
	GetClientRect(&rcClient);
	EndOfDoc.m_x = rcClient.right - 1;
	EndOfDoc.m_y = rcClient.bottom - 1;
	CBuildPathsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//вызов в цикле отрисовщика
	for (int i = 0; i < pDoc->Paths.size(); i++)
		pDoc->Paths[i].Draw(&aDC);

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

bool CBuildPathsView::CheckPos(CPoint* point )
{
	// получение документа
	CBuildPathsDoc* pDoc = GetDocument();
	// проверка на начало в области 10 пикселей
	if ((abs(point->x - 5) < 10) & (abs(point->y - 5) < 10))
	{
		Path path(EndOfDoc);
		pDoc->Paths.push_back(path);
		point->SetPoint(0, 0);
		return true;
	}
	else 
	//проверка на концы путей в области 10 пикселей и на не закончен ли данный путь
		for (int i = 0; i < pDoc->Paths.size(); i++)
		{
			
			Point temp = pDoc->Paths[i].GetEnd();
			if ((abs(point->x - temp.m_x) < 10) & (abs(point->y - temp.m_y) < 10) & !pDoc->Paths[i].IsEnd())
			{
				point->SetPoint(temp.m_x, temp.m_y);
				return true;
			}
		}
	
	return false;

}


// получение индекса в контейнере путей по концу пути
int CBuildPathsView::GetIndex(Point x)
{
	CBuildPathsDoc* pDoc = GetDocument();
	for (int i = 0; i < pDoc->Paths.size(); i++)
	{
		Point temp = pDoc->Paths[i].GetEnd();
		if ((x.m_x == temp.m_x) & (x.m_y == temp.m_y) )
			return i;
	}
	return -1;
}

// проверка на конец пути, если попали в область конца пути, то инициализурем точку координатами конца документа
Point CBuildPathsView::EndPoints(CPoint point)
{
	

	if ((abs(point.x - EndOfDoc.m_x) < 10) && (abs(point.y - EndOfDoc.m_y) < 10))
	{
		return EndOfDoc;
	}
	else
	{
		Point temp;
		temp.m_x = point.x;
		temp.m_y = point.y;
		return temp;
	}
}

Point s, e,m;

bool bs = false, bm = false;
// нажатие на левую кнопку мыши
void CBuildPathsView::OnLButtonDown(UINT nFlags, CPoint point)
{	
	// получение области рисования
	CClientDC aDC(this);
	CBuildPathsDoc* pDoc = GetDocument();
	// если не выбрана начальная точка и не попадает в начало или конец какого-то пути, то оповещение
	if (!bs)
		if (!CheckPos(&point))
		{
			AfxMessageBox(_T("Начинать или с конца пути или от начала"));
			return;
		}
	//свитч по выбору фигур
	switch (ElemType)
	{
	case TypeElem::line2p: // линия по 2 точкам
	{
		if (bs) // если стартовая точка есть
		{
			//инициализурем конечную точку
			e = EndPoints(point);
			//вызов контроллера
			LineController line(s, e);
			//получение индекса пути
			int index = GetIndex(s);
			//Добавление в контейнер путей
			line.AddToPath(&pDoc->Paths[index]);
			
			bs = !bs;
		}
		else
		{
			// инициализурем стартовую точку
			s.m_x = point.x;
			s.m_y = point.y;
			bs = !bs;
		}
		
	}
	break;
	case TypeElem::linela: // линия по точке длине и углу
	{
		int length = _ttoi(CMFCToolBarEditBoxButton::GetContentsAll(IDS_LENGTH)); // получение длины
		int angle = _ttoi(CMFCToolBarEditBoxButton::GetContentsAll(IDS_ANGLE)); //получение угла
		if (length == 0) // если длина равно 0 - оповестить
		{
			AfxMessageBox(_T("Длина не может равняться 0"));
				return;
		}
		else
		{
			//инициализуруем начальную точку
			s.m_x = point.x;
			s.m_y = point.y;
			//вызов контроллера
			LineController line( s, length, -angle);
			// получение индекса
			int index = GetIndex(s);
			//Добавление в контейнер путей
			line.AddToPath(&pDoc->Paths[index]);
			
		}
		
	}
	break;
	case TypeElem::arc3p: // дуга по 3 точкам
	{
		if (bs & bm) // если есть начальная и средняя точка
		{
			e = EndPoints(point); // инициализируем конечную точку
			ArcController arc( s, e, m); //вызов контроллера
			int index = GetIndex(s); // получение индекса пути
			arc.AddToPath(&pDoc->Paths[index]); // добавление в контейнер путей
			bs = bm = false;
			
		}
		else if (bs)
		{ //инициализация средней точки
			m.m_x = point.x;
			m.m_y = point.y;
			bm = !bm;
		}
		else
		{
			// иницализация начальной точки
			s.m_x = point.x;
			s.m_y = point.y;
			bs = !bs;
		}

	}
	break; 
	case TypeElem::arc2p: // дуга по 2 точкам
	{
		if (bs)
		{
			e = EndPoints(point); // инициализируем конечную точку
			bool clock = CMFCToolBarComboBoxButton::GetCurSelAll(IDS_COMBO); // получаем направление построения
			int rad = _ttoi(CMFCToolBarEditBoxButton::GetContentsAll(IDS_RAD)); //получаем радиус
			if (rad == 0) // проверка на радиус
			{
				bs = !bs;
				AfxMessageBox(_T("Радиус не может равняться 0"));
				return;
			}
			double l = sqrt(pow(e.m_x - s.m_x, 2) + pow(e.m_y - s.m_y, 2)); // проверка на существование окружности с заданным радиусом
			if (rad < l / 2)
			{
				bs = !bs;
				AfxMessageBox(_T("Радиус слишком мал"));
				return;
			}
			
			ArcController arc( s, e, rad, clock); //вызов контроллера
			int index = GetIndex(s); // получение индекса
			arc.AddToPath(&pDoc->Paths[index]); // добавление в путь
			bs = !bs;
		}
		else
		{
			//инициализация начальной точки
			s.m_x = point.x;
			s.m_y = point.y;
			bs = !bs;
		}
	}
	}
	OnDraw(&aDC); //вызов перерисовщик
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
	if (bs | bm)
		return;
	ElemType = TypeElem::line2p;
	
}


void CBuildPathsView::OnLinela()
{
	if (bs | bm)
		return;
	ElemType = TypeElem::linela;
	
}


void CBuildPathsView::OnArc3p()
{
	if (bs | bm)
		return;
	ElemType = TypeElem::arc3p;

}


void CBuildPathsView::OnArc2p()
{
	if (bs | bm)
		return;
	ElemType = TypeElem::arc2p;

}


void CBuildPathsView::OnUpdateLine2p(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(ElemType == TypeElem::line2p);
}


void CBuildPathsView::OnUpdateLinela(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(ElemType == TypeElem::linela);
}


void CBuildPathsView::OnUpdateArc3p(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(ElemType == TypeElem::arc3p);
}


void CBuildPathsView::OnUpdateArc2p(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(ElemType == TypeElem::arc2p);
}

