
// BuildPathsDoc.h: интерфейс класса CBuildPathsDoc 
//
#pragma once

#include "Figures.h"
#include "Path.h"
#include "SortPath.h"

#include <list>
#include <vector>


class CBuildPathsDoc : public CDocument
{
protected: // создать только из сериализации
	CBuildPathsDoc() noexcept;
	DECLARE_DYNCREATE(CBuildPathsDoc)
private:
	Point m_endOfDoc;
	SortPath m_paths;

// Атрибуты

	
	
	
// Операции	
public:

// Переопределение
public:
	
	virtual BOOL OnNewDocument();
	Point GetEndDoc();
	ListPath& GetPaths();
	ListPath& GetEndPaths();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CBuildPathsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileSave();
};
