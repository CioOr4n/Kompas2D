
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
	CRect rc;
	POSITION sd = GetFirstViewPosition();
	GetNextView(sd)->GetClientRect(&rc);
	

	m_endOfDoc.m_x = rc.right - 1;
	m_endOfDoc.m_y = rc.bottom - 1;


	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}
Point CBuildPathsDoc::GetEndDoc()
{
	return m_endOfDoc;
}

std::list<Path>& CBuildPathsDoc::GetPaths()
{
	return m_paths.GetPaths();
}

std::list<Path>& CBuildPathsDoc::GetEndPaths()
{
	return m_paths.GetEndPaths();
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
	std::list<Path>& paths = m_paths.GetEndPaths();
	//Проверка на наличие путей
	if (paths.size() == 0)
	{
		AfxMessageBox(_T("Нечего сохранять"));
		return;
	}
	else 
		for (auto& path : paths)
		{
			if (path.IsEnd())
				continue;
			else
			{
				int result = AfxMessageBox(_T("Есть не законченные пути.\nХотите продолжить?"), MB_OKCANCEL);
				if (result == IDCANCEL)
					return;
				else break;
			}
		}
	// создание экземпляра диалогоа
	CFileDialog fd(false,L"xml", L"Построение путей",NULL,L"XML Files (*.xml)|*.xml||");
	
	//вызов диалога и получение путей
	if (fd.DoModal() == IDOK)
	{
		File = fd.GetPathName();
	}
	else return;
	//Приведение к CStringA
	CStringA FilePath(File);
	// создание экземпляра документа
	tinyxml2::XMLDocument doc;
	//добавление декларации
	tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
	doc.InsertEndChild(decl);
	//создание элемента документа
	tinyxml2::XMLElement* elem = doc.NewElement("Document");
	doc.InsertEndChild(elem);
	tinyxml2::XMLElement* docsize = doc.NewElement("Windowsize");
	elem->InsertEndChild(docsize);
	// создание стартовой точки документа
	tinyxml2::XMLElement* StartPointDoc = doc.NewElement("StartPoint");
	docsize->InsertFirstChild(StartPointDoc);
	//создание точки Startx
	tinyxml2::XMLElement* xs = doc.NewElement("x");
	xs->SetText(0);
	StartPointDoc->InsertEndChild(xs);
	//создание точки Starty
	tinyxml2::XMLElement* ys = doc.NewElement("y");
	ys->SetText(0);
	StartPointDoc->InsertEndChild(ys);
	// создание конечной точки документа
	tinyxml2::XMLElement* FinishPointDoc = doc.NewElement("FinishPoint");
	docsize->InsertEndChild(FinishPointDoc);
	//создание точки Finishx
	tinyxml2::XMLElement* xf = doc.NewElement("x");
	xf->SetText(m_endOfDoc.m_x);
	FinishPointDoc->InsertEndChild(xf);
	//создание точки Finishy
	tinyxml2::XMLElement* yf = doc.NewElement("y");
	yf->SetText(m_endOfDoc.m_y);
	FinishPointDoc->InsertEndChild(yf);
	// Создание в цикле количество путей и вызов метода преобразования
	for (auto& path : paths)
	{
		tinyxml2::XMLElement* Objects = doc.NewElement("Objects");
		elem->InsertEndChild(Objects);
		path.ToXML(Objects, &doc);
	}
	//сохранения файла
	doc.SaveFile(FilePath);
	doc.Clear();
	doc.~XMLDocument();
}
