
// MyMaskCodeTestDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "MacCodeEditDlg.h"
#include "afxwin.h"


// CMyMaskCodeTestDlg dialog
class CMyMaskCodeTestDlg : public CDialogEx
{
// Construction
public:
	CMyMaskCodeTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYMASKCODETEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CMacCodeEditDlg m_macAddrEditDlg;
	CMacCodeEditDlg m_maskAddrEditDlg;
	CMacCodeEditDlg m_resultAddrEditDlg;
	CTabCtrl m_macAddrTab;
	CTabCtrl m_macMaskTab;
	CTabCtrl m_resultAddrTab;
public:
	afx_msg void OnBnClickedButtonCalmacresult();
	afx_msg void OnBnClickedButtonDeletedata();

public:
	afx_msg void OnTcnSelchangeTabMacmaskaddr(NMHDR *pNMHDR, LRESULT *pResult);
};
