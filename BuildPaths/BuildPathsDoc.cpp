
// BuildPathsDoc.cpp: реализация класса CBuildPathsDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "BuildPaths.h"
#endif

#include "BuildPathsDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBuildPathsDoc

IMPLEMENT_DYNCREATE(CBuildPathsDoc, CDocument)

BEGIN_MESSAGE_MAP(CBuildPathsDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CBuildPathsDoc::OnFileSave)
END_MESSAGE_MAP()


// Создание или уничтожение CBuildPathsDoc

CBuildPathsDoc::CBuildPathsDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CBuildPathsDoc::~CBuildPathsDoc()
{
}

BOOL CBuildPathsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CBuildPathsDoc

void CBuildPathsDoc::Serialize(CArchive& ar)
{
	
	if (ar.IsStoring())
	{
		
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CBuildPathsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CBuildPathsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CBuildPathsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CBuildPathsDoc

#ifdef _DEBUG
void CBuildPathsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBuildPathsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CBuildPathsDoc


void CBuildPathsDoc::OnFileSave()
{

	CString File;
	//Проверка на наличие путей
	if (Paths.size() == 0)
	{
		AfxMessageBox(_T("Нечего сохранять"));
		return;
	}
	// создание экземпляра диалогоа
	CFileDialog fd(false,L"xml", L"Построение путей",NULL,L"XML Files (*.xml)");
	
	//вызов диалога и получение путей
	if (fd.DoModal() == IDOK)
	{
		File = fd.GetPathName();
	}
	//Приведение к CStringA
	CStringA FilePath(File);
	// создание экземпляра документа
	tinyxml2::XMLDocument doc;
	//добавление декларации
	XMLDeclaration* decl = doc.NewDeclaration();
	doc.InsertEndChild(decl);
	//создание элемента документа
	XMLElement* elem = doc.NewElement("Document");
	doc.InsertEndChild(elem);
	// создание стартовой точки документа
	XMLElement* StartPointDoc = doc.NewElement("StartPoint");
	elem->InsertFirstChild(StartPointDoc);
	//создание точки Startx
	XMLElement* xs = doc.NewElement("x");
	xs->SetText(0);
	StartPointDoc->InsertEndChild(xs);
	//создание точки Starty
	XMLElement* ys = doc.NewElement("y");
	ys->SetText(0);
	StartPointDoc->InsertEndChild(ys);
	// создание конечной точки документа
	XMLElement* FinishPointDoc = doc.NewElement("FinishPoint");
	elem->InsertEndChild(FinishPointDoc);
	//создание точки Finishx
	XMLElement* xf = doc.NewElement("x");
	xf->SetText(Paths[0].m_EndDoc.m_x);
	FinishPointDoc->InsertEndChild(xf);
	//создание точки Finishy
	XMLElement* yf = doc.NewElement("y");
	yf->SetText(Paths[0].m_EndDoc.m_y);
	FinishPointDoc->InsertEndChild(yf);
	// Создание в цикле количество путей и вызов метода преобразования
	for (int i = 0; i < Paths.size(); i++)
	{
		XMLElement* Objects = doc.NewElement("Objects");
		elem->InsertEndChild(Objects);
		Paths[i].ToXML(Objects, &doc);
	}

	
	//сохранения файла
	doc.SaveFile(FilePath);
	
}
