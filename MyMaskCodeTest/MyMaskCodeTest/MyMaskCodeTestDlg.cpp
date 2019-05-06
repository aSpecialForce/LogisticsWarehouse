
// MyMaskCodeTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMaskCodeTest.h"
#include "MyMaskCodeTestDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyMaskCodeTestDlg dialog




CMyMaskCodeTestDlg::CMyMaskCodeTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyMaskCodeTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMaskCodeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MACADDR, m_macAddrTab);
	DDX_Control(pDX, IDC_TAB_MACMASKADDR, m_macMaskTab);
	DDX_Control(pDX, IDC_TAB_RESULTADDR, m_resultAddrTab);

	m_macAddrEditDlg.Create(IDD_DIALOG_MACCODE,&m_macAddrTab);
	m_maskAddrEditDlg.Create(IDD_DIALOG_MACCODE,&m_macMaskTab);
	m_resultAddrEditDlg.Create(IDD_DIALOG_MACCODE,&m_resultAddrTab);

	CRect rect;
	m_macAddrTab.GetClientRect(&rect);
	::MoveWindow(m_macAddrEditDlg.m_hWnd, rect.TopLeft().x, rect.TopLeft().y, rect.Width(), rect.Height(), TRUE);
	::ShowWindow(m_macAddrEditDlg.m_hWnd, SW_SHOW);

	m_macMaskTab.GetClientRect(&rect);
	::MoveWindow(m_maskAddrEditDlg.m_hWnd, rect.TopLeft().x, rect.TopLeft().y, rect.Width(), rect.Height(), TRUE);
	::ShowWindow(m_maskAddrEditDlg.m_hWnd, SW_SHOW);

	m_resultAddrTab.GetClientRect(&rect);
	::MoveWindow(m_resultAddrEditDlg.m_hWnd, rect.TopLeft().x, rect.TopLeft().y, rect.Width(), rect.Height(), TRUE);
	::ShowWindow(m_resultAddrEditDlg.m_hWnd, SW_SHOW);
}

BEGIN_MESSAGE_MAP(CMyMaskCodeTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CALMACRESULT, &CMyMaskCodeTestDlg::OnBnClickedButtonCalmacresult)
	ON_BN_CLICKED(IDC_BUTTON_DELETEDATA, &CMyMaskCodeTestDlg::OnBnClickedButtonDeletedata)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MACMASKADDR, &CMyMaskCodeTestDlg::OnTcnSelchangeTabMacmaskaddr)
END_MESSAGE_MAP()


// CMyMaskCodeTestDlg message handlers

BOOL CMyMaskCodeTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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


	SetWindowText(L"ÑÚÂë¼ÆËãÆ÷");
	//ShowWindow(SW_MAXIMIZE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyMaskCodeTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyMaskCodeTestDlg::OnPaint()
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
HCURSOR CMyMaskCodeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyMaskCodeTestDlg::OnBnClickedButtonCalmacresult()
{
	int nMacByte1 = 0;
	int nMacByte2 = 0;
	int nMacByte3 = 0;
	int nMacByte4 = 0;
	int nMacByte5 = 0;
	int nMacByte6 = 0;

	int nMaskByte1 = 0;
	int nMaskByte2 = 0;
	int nMaskByte3 = 0;
	int nMaskByte4 = 0;
	int nMaskByte5 = 0;
	int nMaskByte6 = 0;

	int nResultByte1 = 0;
	int nResultByte2 = 0;
	int nResultByte3 = 0;
	int nResultByte4 = 0;
	int nResultByte5 = 0;
	int nResultByte6 = 0;

	 nMacByte1 = m_macAddrEditDlg.GetCode1ByteValue();
	 nMacByte2 = m_macAddrEditDlg.GetCode2ByteValue();
	 nMacByte3 = m_macAddrEditDlg.GetCode3ByteValue();
	 nMacByte4 = m_macAddrEditDlg.GetCode4ByteValue();
	 nMacByte5 = m_macAddrEditDlg.GetCode5ByteValue();
	 nMacByte6 = m_macAddrEditDlg.GetCode6ByteValue();

	 nMaskByte1 = m_maskAddrEditDlg.GetCode1ByteValue();
	 nMaskByte2 = m_maskAddrEditDlg.GetCode2ByteValue();
	 nMaskByte3 = m_maskAddrEditDlg.GetCode3ByteValue();
	 nMaskByte4 = m_maskAddrEditDlg.GetCode4ByteValue();
	 nMaskByte5 = m_maskAddrEditDlg.GetCode5ByteValue();
	 nMaskByte6 = m_maskAddrEditDlg.GetCode6ByteValue();


	 nResultByte1 = nMacByte1 & nMaskByte1;
	 nResultByte2 = nMacByte2 & nMaskByte2;
	 nResultByte3 = nMacByte3 & nMaskByte3;
	 nResultByte4 = nMacByte4 & nMaskByte4;
	 nResultByte5 = nMacByte5 & nMaskByte5;
	 nResultByte6 = nMacByte6 & nMaskByte6;

	 m_resultAddrEditDlg.SetCode1Byte(nResultByte1);
	 m_resultAddrEditDlg.SetCode2Byte(nResultByte2);
	 m_resultAddrEditDlg.SetCode3Byte(nResultByte3);
	 m_resultAddrEditDlg.SetCode4Byte(nResultByte4);
	 m_resultAddrEditDlg.SetCode5Byte(nResultByte5);
	 m_resultAddrEditDlg.SetCode6Byte(nResultByte6);
}


void CMyMaskCodeTestDlg::OnBnClickedButtonDeletedata()
{
	m_macAddrEditDlg.OnBnClickedButtonClear();
	m_maskAddrEditDlg.OnBnClickedButtonClear();
	m_resultAddrEditDlg.OnBnClickedButtonClear();
}


void CMyMaskCodeTestDlg::OnTcnSelchangeTabMacmaskaddr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
