#pragma once
#include "afxwin.h"
#include "CDataModule.h"
#include <string>


// CMacCodeEditDlg dialog

class CMacCodeEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMacCodeEditDlg)

public:
	CMacCodeEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMacCodeEditDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_MACCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_codeB1Edit;
	CEdit m_codeB2Edit;
	CEdit m_codeB3Edit;
	CEdit m_codeB4Edit;
	CEdit m_codeB5Edit;
	CEdit m_codeB6Edit;

private:
	std::wstring GetValueStr(int nValue);
	int GetCodeByteValue(const CEdit & codeByteEdit);
public:
	int GetCode1ByteValue();
	int GetCode2ByteValue();
	int GetCode3ByteValue();
	int GetCode4ByteValue();
	int GetCode5ByteValue();
	int GetCode6ByteValue();

	void SetCode1Byte(int nValue);
	void SetCode2Byte(int nValue);
	void SetCode3Byte(int nValue);
	void SetCode4Byte(int nValue);
	void SetCode5Byte(int nValue);
	void SetCode6Byte(int nValue);

	std::wstring Decimal2Binary(int mask);
	int Bianry2Decimal(std::wstring wstrBinary);
	int Hex2Decimal(std::wstring wstrHex);
private:
	CComboBox m_decimalTypeCmb;

	CDecimalType m_kDecimalType;
public:
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnCbnSelchangeComboDecimaltype();
};
