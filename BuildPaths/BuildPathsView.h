
// BuildPathsView.h: интерфейс класса CBuildPathsView
//

#pragma once
#include "Figures.h"
#include "BuildPathsController.h"

class CBuildPathsView : public CView
{
protected: // создать только из сериализации
	CBuildPathsView() noexcept;
	DECLARE_DYNCREATE(CBuildPathsView)

// Атрибуты
public:
	
	CBuildPathsDoc* GetDocument() const;
	

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

// Реализация
public:
	virtual ~CBuildPathsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	bool CheckPos(CPoint* point);
	int GetIndex(Point x);
	Point EndPoints(CPoint point);
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	TypeElem ElemType;
	Type Elem;
	Point EndOfDoc;
public:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnLine2p();
	afx_msg void OnLinela();
	afx_msg void OnArc3p();
	afx_msg void OnArc2p();
	afx_msg void OnUpdateLine2p(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLinela(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArc3p(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArc2p(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // версия отладки в BuildPathsView.cpp
inline CBuildPathsDoc* CBuildPathsView::GetDocument() const
   { return reinterpret_cast<CBuildPathsDoc*>(m_pDocument); }
#endif

