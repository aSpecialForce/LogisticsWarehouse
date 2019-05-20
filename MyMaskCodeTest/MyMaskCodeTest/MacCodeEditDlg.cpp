// MacCodeEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMaskCodeTest.h"
#include "MacCodeEditDlg.h"
#include "afxdialogex.h"
#include <stack>


// CMacCodeEditDlg dialog

IMPLEMENT_DYNAMIC(CMacCodeEditDlg, CDialogEx)


CMacCodeEditDlg::CMacCodeEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMacCodeEditDlg::IDD, pParent)
{
	m_kDecimalType = Decimal;
}

CMacCodeEditDlg::~CMacCodeEditDlg()
{
}

void CMacCodeEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CODEB1, m_codeB1Edit);
	DDX_Control(pDX, IDC_EDIT_CODEB2, m_codeB2Edit);
	DDX_Control(pDX, IDC_EDIT_CODEB3, m_codeB3Edit);
	DDX_Control(pDX, IDC_EDIT_CODEB4, m_codeB4Edit);
	DDX_Control(pDX, IDC_EDIT_CODEB5, m_codeB5Edit);
	DDX_Control(pDX, IDC_EDIT_CODEB6, m_codeB6Edit);
	DDX_Control(pDX, IDC_COMBO_DECIMALTYPE, m_decimalTypeCmb);

	m_decimalTypeCmb.InsertString(m_decimalTypeCmb.GetCount(),L"Decimal");
	m_decimalTypeCmb.InsertString(m_decimalTypeCmb.GetCount(),L"Binary");
	m_decimalTypeCmb.InsertString(m_decimalTypeCmb.GetCount(),L"Hex");
	m_decimalTypeCmb.SetCurSel(0);
	m_kDecimalType = Decimal;
}


BEGIN_MESSAGE_MAP(CMacCodeEditDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMacCodeEditDlg::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO_DECIMALTYPE, &CMacCodeEditDlg::OnCbnSelchangeComboDecimaltype)
END_MESSAGE_MAP()


// CMacCodeEditDlg message handlers


void CMacCodeEditDlg::OnBnClickedButtonClear()
{
	CString str = L"";
	m_codeB1Edit.SetWindowTextW(str);
	m_codeB2Edit.SetWindowTextW(str);
	m_codeB3Edit.SetWindowTextW(str);
	m_codeB4Edit.SetWindowTextW(str);
	m_codeB5Edit.SetWindowTextW(str);
	m_codeB6Edit.SetWindowTextW(str);
}

int CMacCodeEditDlg::GetCode1ByteValue()
{
	return GetCodeByteValue(m_codeB1Edit);
}

int CMacCodeEditDlg::GetCode2ByteValue()
{
	return GetCodeByteValue(m_codeB2Edit);
}

int CMacCodeEditDlg::GetCode3ByteValue()
{
	return GetCodeByteValue(m_codeB3Edit);
}

int CMacCodeEditDlg::GetCode4ByteValue()
{
	return GetCodeByteValue(m_codeB4Edit);
}

int CMacCodeEditDlg::GetCode5ByteValue()
{
	return GetCodeByteValue(m_codeB5Edit);
}

int CMacCodeEditDlg::GetCode6ByteValue()
{
	return GetCodeByteValue(m_codeB6Edit);
}

int CMacCodeEditDlg::GetCodeByteValue(const CEdit & codeByteEdit)
{
	int nResult = 0 ;
	CString str = L"";

	codeByteEdit.GetWindowTextW(str);

	if(!str.IsEmpty())
	{
		try
		{
			if (m_kDecimalType == Binary)
			{
				//nResult = std::stoi(str.GetBuffer(),0,2);
				nResult = Bianry2Decimal(str.GetBuffer());
			}
			else if (m_kDecimalType == Decimal)
			{
				nResult = _wtoi(str.GetBuffer());
			}
			else if (m_kDecimalType == Hexadecimal)
			{
				//nResult = std::stoi(str.GetBuffer(),0,16);
				nResult = Hex2Decimal(str.GetBuffer());
			}
		}
		catch (CException* e)
		{
			wchar_t   szError[1024];   
			e->GetErrorMessage(szError,1024);   //  e.GetErrorMessage(szError,1024); 
			::AfxMessageBox(szError); 
		}
	}
	return nResult;
}

std::wstring CMacCodeEditDlg::Decimal2Binary(int mask)
{
	std::wstring wstrResult = L"";
	unsigned int i;
	int nLength = sizeof(int)*8/2;
	for(i = 0; i < nLength; i++)
	{ 
		if(mask & (1 << (nLength - 1 - i)))
			wstrResult.append(L"1");
		else
			wstrResult.append(L"0");
	}
	
	int nTemp = _wtoi(wstrResult.c_str());
	wstrResult.clear();
	wchar_t strResultTemp[100] = {0};
	swprintf_s(strResultTemp,L"%d",nTemp);
	wstrResult = strResultTemp;
	return wstrResult;
}

int CMacCodeEditDlg::Bianry2Decimal(std::wstring wstrBinary)
{
	int nResult = 0;
	const wchar_t* str = wstrBinary.c_str();
	int nLength = wcslen(str);
	for (unsigned int i = 0 ;i < nLength; ++i)
	{
		if (str[i] == '1')
		{
			nResult = nResult|(1<<(nLength - 1 - i ));
		}
	}

	return nResult;
}

int CMacCodeEditDlg::Hex2Decimal(std::wstring wstrHex)
{
	int nResult = 0;
	const wchar_t* str = wstrHex.c_str();
	int nLength = wcslen(str);
	for (unsigned int i = 0 ;i < nLength; ++i)
	{
		 if (str[i] >= '0' && str[i] <= '9')
		 {
			  nResult = nResult|((str[i] - '0')<<((nLength-1 - i)*4)); 
		 }
		 else if ((str[i] >= 'a' && str[i] <= 'f'))
		 {
			 nResult = nResult|(((7&(str[i] - 87))+8)<<((nLength-1 - i)*4)); 
		 }
		 else if((str[i] >= 'A' && str[i] <= 'F') )
		 {
			 nResult = nResult|(((7&(str[i] - 55))+8)<<((nLength-1 - i)*4));
		 }
	}

	return nResult;
}

void CMacCodeEditDlg::SetCode1Byte(int nValue)
{
	m_codeB1Edit.SetWindowTextW(GetValueStr(nValue).c_str());
}

void CMacCodeEditDlg::SetCode2Byte(int nValue)
{
	m_codeB2Edit.SetWindowTextW(GetValueStr(nValue).c_str());
}

void CMacCodeEditDlg::SetCode3Byte(int nValue)
{
	m_codeB3Edit.SetWindowTextW(GetValueStr(nValue).c_str());
}

void CMacCodeEditDlg::SetCode4Byte(int nValue)
{
	m_codeB4Edit.SetWindowTextW(GetValueStr(nValue).c_str());
}

void CMacCodeEditDlg::SetCode5Byte(int nValue)
{
	m_codeB5Edit.SetWindowTextW(GetValueStr(nValue).c_str());
}

void CMacCodeEditDlg::SetCode6Byte(int nValue)
{
	m_codeB6Edit.SetWindowTextW(GetValueStr(nValue).c_str());
}

std::wstring CMacCodeEditDlg::GetValueStr(int nValue)
{
	std::wstring wstrResult = L"";
	wchar_t strResult[100] = {0};
	if (m_kDecimalType == Binary)
	{			

		std::wstring wstrTemp = Decimal2Binary(nValue);

		std::stack<int> stackBinary;
		while(nValue!=0)
		{
			stackBinary.push(nValue % 2);
			nValue /= 2;
		}

		while(!stackBinary.empty())
		{
			std::wstring wstrDecimal = L"%d";
			swprintf_s(strResult,wstrDecimal.c_str(),stackBinary.top());
			wstrResult.append(strResult);
			stackBinary.pop();
		}
	}
	else if (m_kDecimalType == Decimal)
	{
		std::wstring wstrDecimal = L"%d";
		swprintf_s(strResult,wstrDecimal.c_str(),nValue);
		wstrResult = strResult;
	}
	else if (m_kDecimalType == Hexadecimal)
	{
		std::wstring wstrDecimal = L"%x";
		swprintf_s(strResult,wstrDecimal.c_str(),nValue);
		wstrResult = strResult;
	}

	return wstrResult;
}

void CMacCodeEditDlg::OnCbnSelchangeComboDecimaltype()
{
	CString str = L"";
	m_decimalTypeCmb.GetWindowTextW(str);

	int nByte1 = GetCode1ByteValue();
	int nByte2 = GetCode2ByteValue();
	int nByte3 = GetCode3ByteValue();
	int nByte4 = GetCode4ByteValue();
	int nByte5 = GetCode5ByteValue();
	int nByte6 = GetCode6ByteValue();

	if (str.CompareNoCase(L"Decimal") == 0)
	{
		m_kDecimalType = Decimal;
	}
	else if (str.CompareNoCase(L"Binary") == 0)
	{
		m_kDecimalType = Binary;
	}
	else if (str.CompareNoCase(L"Hex") == 0)
	{
		m_kDecimalType = Hexadecimal;
	}

	SetCode1Byte(nByte1);
	SetCode2Byte(nByte2);
	SetCode3Byte(nByte3);
	SetCode4Byte(nByte4);
	SetCode5Byte(nByte5);
	SetCode6Byte(nByte6);
}
