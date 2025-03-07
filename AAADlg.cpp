
// AAADlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "AAA.h"
#include "AAADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAAADlg dialog



CAAADlg::CAAADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AAA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAAADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_STATIC_TREE, m_Static_tree);
}

BEGIN_MESSAGE_MAP(CAAADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SIZING()
	ON_WM_MOVE()
	ON_COMMAND(ID_FILE_EXIT, &CAAADlg::OnFileExit)
	ON_WM_SIZE()
END_MESSAGE_MAP()

UINT indicators1[] =
{
	ID_SEPARATOR,           // индикатор строки состояния
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // индикатор строки состояния
	ID_INDICATOR_CAPS,
};

// CAAADlg message handlers
RECT rcWorkArea;
CImageList imageList;
BOOL CAAADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//ShowWindow(SW_MAXIMIZE);
	//RECT rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	//MoveWindow(&rcWorkArea);

	 // Получение текущего размера и положения окна
	CRect rect;
	GetWindowRect(&rect);

	// Изменение ширины окна, оставив положение и высоту неизменными
	SetWindowPos(NULL, 0, 0, rcWorkArea.right - rcWorkArea.left, rcWorkArea.bottom - rcWorkArea.top/*1080-40*/, SWP_NOMOVE | SWP_NOZORDER);

	/*0
	//init tool bar
	m_TBar = new CToolBar;
	m_TBar->CreateEx(this, TBSTYLE_FLAT | CBRS_TOOLTIPS, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_TBar->LoadToolBar(IDR_TOOLBAR_AAA);
	m_TBar->LoadBitmap(IDB_BITMAP1);
	*/

	//m_TBar.LoadImages(IDB_BITMAP1, NULL);

	// Создание панели инструментов
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR3))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}

	// Загрузка изображений
	//CImageList imageList;
	imageList.Create(32, 32, ILC_COLOR32, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_FOLD); // IDB_BITMAP1 - идентификатор вашего изображения
	imageList.Add(&bitmap, RGB(255, 0, 0)); // RGB(255, 0, 0) - цвет прозрачности

	// Установка изображений на кнопки
	m_wndToolBar.GetToolBarCtrl().SetImageList(&imageList);

	// Установите панель инструментов
	m_wndToolBar.SetWindowText(_T("Main Toolbar"));
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);
	CPoint ptOffset(rcClientNow.left - rcClientStart.left, rcClientNow.top - rcClientStart.top);

	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();


	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	//m_TBar->SetButtonStyle(0, TBBS_BUTTON);


	//init status bar
#define IDC_STATUS_BAR 222222

	CRect mainRect;
	this->GetWindowRect(&mainRect);
	m_SBar.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_SIZEGRIP, CRect(0, 0, 0, 0), this, IDC_STATUS_BAR);
	const int nParts = 8;
	CRect sbrect;
	m_SBar.GetClientRect(&sbrect);
	int widths[nParts] =
	{ sbrect.left,sbrect.left + 150, sbrect.left + 500,
		sbrect.left + 800,sbrect.left + 920,sbrect.left + 1150,sbrect.left + 1200 };
	VERIFY(m_SBar.SetParts(6, widths));
	m_SBar.SetSimple(FALSE);
	m_SBar.RedrawWindow();
	m_SBar.GetWindowRect(&mainRect);
	m_SBar.MoveWindow(mainRect.left, mainRect.top, mainRect.Width(), mainRect.Height() + 1);
	m_SBar.RedrawWindow();

	//int screenWidth = 0;
	//int screenHeight = 0;
	//::GetScreenResolution(screenWidth, screenHeight);

	//MoveWindow(0,0, 1920, 1000);
	//ResizeDialogWidth(500);

	/*
	// Создаем статический разделитель
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	// Объявляем и инициализируем CCreateContext
	CCreateContext* pContext = new CCreateContext;
	pContext->m_pNewViewClass = RUNTIME_CLASS(CTreeCtrl);
	pContext->m_pCurrentDoc = NULL;
	pContext->m_pNewDocTemplate = NULL;
	pContext->m_pLastView = NULL;
	pContext->m_pCurrentFrame = NULL;

	// Создаем левую часть разделителя для дерева иерархии
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTreeCtrl), CSize(200, 100), pContext))
	{
		TRACE0("Failed to create tree view pane\n");
		return FALSE;
	}
	*/

	// Измените стиль элемента для отображения границы
	m_Static_tree.ModifyStyle(0, WS_BORDER);

	// Установите текст или другое содержимое
	m_Static_tree.SetWindowText(_T("tree panel"));

	// Получаем размеры диалогового окна
	CRect rectClient;
	GetClientRect(&rectClient);

	// Получаем размеры и положение панели инструментов
	CRect rectToolbar;
	GetDlgItem(AFX_IDW_TOOLBAR)->GetWindowRect(&rectToolbar);
	ScreenToClient(&rectToolbar);

	// Получаем размеры и положение статусной строки
	CRect rectStatusBar;
	//GetDlgItem(AFX_IDW_STATUS_BAR)->GetWindowRect(&rectStatusBar);
	//ScreenToClient(&rectStatusBar);
	m_SBar.GetRect(0, &rectStatusBar);

	// Рассчитываем размеры и положение для статического элемента
	int staticWidth = rectClient.Width() / 4;
	int staticHeight = rectClient.Height() - rectToolbar.Height() - rectStatusBar.Height();
	int staticX = rectClient.left;// rectClient.Width() / 8;  // Позиционируем на 1/4 ширины
	int staticY = rectToolbar.Height();  // Позиционируем между панелью инструментов и статусной строкой

	m_Static_tree.MoveWindow(staticX, staticY, staticWidth, staticHeight);
	
	/*
	// Объявляем и инициализируем CCreateContext
	CCreateContext* pContext = new CCreateContext;
	pContext->m_pNewViewClass = RUNTIME_CLASS(CTreeCtrl);
	pContext->m_pCurrentDoc = NULL;
	pContext->m_pNewDocTemplate = NULL;
	pContext->m_pLastView = NULL;
	pContext->m_pCurrentFrame = NULL;


	// Создаем статический разделитель
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	// Создаем левую часть разделителя для статического элемента
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CStatic), CSize(200, 100), pContext))
	{
		TRACE0("Failed to create static view pane\n");
		return FALSE;
	}

	// Создаем правую часть разделителя для пустой области или другой вид
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CView), CSize(300, 100), pContext))
	{
		TRACE0("Failed to create right view pane\n");
		return FALSE;

	}
*/












	ShowWindow(SW_MAXIMIZE);

	initdlg = true;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAAADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAAADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAAADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CAAADlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}

int CAAADlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	//CMenu menu;
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);
	initdlg = false;
	return 0;
}


void CAAADlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here

	//move status bar
	CRect mainRect;
	this->GetWindowRect(&mainRect);
	CRect sbrect;
	m_SBar.GetClientRect(&sbrect);
	m_SBar.GetWindowRect(&mainRect);
	m_SBar.MoveWindow(mainRect.left, mainRect.top, mainRect.Width(), mainRect.Height() + 1);
	m_SBar.RedrawWindow();

}


void CAAADlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here

}


void CAAADlg::OnFileExit()
{
	// TODO: Add your command handler code here
	m_SBar.SetText(L"Журнал событий: ЗАГРУЖЕН", 3, 0);
}


void CAAADlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if ((nType == SIZE_MAXIMIZED) || (nType == SIZE_RESTORED))
	{
		//RECT rcWorkArea;
		//SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
		// Получение текущего размера и положения окна
		//CRect rect;
		//GetWindowRect(&rect);
		if (m_SBar.m_hWnd != NULL)
		{

			// Изменение ширины окна, оставив положение и высоту неизменными
			//SetWindowPos(NULL, 0, 0, rcWorkArea.right - rcWorkArea.left, rcWorkArea.bottom - rcWorkArea.top/*1080-40*/, SWP_NOMOVE | SWP_NOZORDER);

			CRect mainRect;
			this->GetWindowRect(&mainRect);
			m_SBar.MoveWindow(mainRect.left, mainRect.top, mainRect.Width(), mainRect.Height() + 1);
			m_SBar.RedrawWindow();
		}

		SetPosTreePanel();
	}
	else
	{
		//CDialogEx::OnSize(nType, cx, cy);
	}


}

void CAAADlg::SetPosTreePanel(void)
{
	
	if (initdlg != true) return;

	// Измените стиль элемента для отображения границы
	m_Static_tree.ModifyStyle(0, WS_BORDER);

	// Установите текст или другое содержимое
	m_Static_tree.SetWindowText(_T("tree panel"));

	// Получаем размеры диалогового окна
	CRect rectClient;
	GetClientRect(&rectClient);

	// Получаем размеры и положение панели инструментов
	CRect rectToolbar;
	GetDlgItem(AFX_IDW_TOOLBAR)->GetWindowRect(&rectToolbar);
	ScreenToClient(&rectToolbar);

	// Получаем размеры и положение статусной строки
	CRect rectStatusBar;
	//GetDlgItem(AFX_IDW_STATUS_BAR)->GetWindowRect(&rectStatusBar);
	//ScreenToClient(&rectStatusBar);
	m_SBar.GetRect(0, &rectStatusBar);

	// Рассчитываем размеры и положение для статического элемента
	int staticWidth = rectClient.Width() / 4;
	int staticHeight = rectClient.Height() - rectToolbar.Height() - rectStatusBar.Height();
	int staticX = rectClient.left;// rectClient.Width() / 8;  // Позиционируем на 1/4 ширины
	int staticY = rectToolbar.Height();  // Позиционируем между панелью инструментов и статусной строкой

	m_Static_tree.MoveWindow(staticX, staticY, staticWidth, staticHeight);

}