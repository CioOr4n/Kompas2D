
// MainFrm.h: интерфейс класса CMainFrame
//

#pragma once
#include "PropertiesWnd.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // создать только из сериализации
	CMainFrame() noexcept;
	 DECLARE_DYNCREATE(CMainFrame)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);

// Реализация
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // встроенные члены панели элементов управления
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CPropertiesWnd    m_wndProperties;
	CMFCCaptionBar    m_wndCaptionBar;
	CMFCToolBarComboBoxButton* m_wndComboBox;
	CMFCToolBarEditBoxButton* m_wndEdit1;
	CMFCToolBarEditBoxButton* m_wndEdit2;
	CMFCToolBarEditBoxButton* m_wndEdit3;
	CMFCToolBarEditBoxButton* m_wndEdit4;
	CMFCToolBarEditBoxButton* m_wndEdit5;


// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg LRESULT OnToolbarReset(WPARAM, LPARAM);
	afx_msg void OnSelChangeClick();
	afx_msg void OnClickComboBox();
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateCaptionBar();
};


