#pragma once


// CDialog_DayDoctor 对话框

class CDialog_DayDoctor : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_DayDoctor)

public:
	CDialog_DayDoctor(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_DayDoctor();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL Dialog_Doctor_PostInfo();
	BOOL Dialog_Doctor_GetInfo();
	BOOL Dialog_Doctor_GetWXID();
	BOOL Dialog_Doctor_GetRegister(LPCTSTR lpszScheduleID);
	BOOL Dialog_Doctor_GetVer();
	BOOL Dialog_Doctor_PostVer();
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListDoctor;
	CEdit m_EditName;
	CEdit m_EditLevel;
	CEdit m_EditCode;
	CEdit m_EditGoodat;
	afx_msg void OnBnClickedButton2();
	CEdit m_EditTicket;
	CEdit m_EditSchedule;
	CEdit m_EditProName;
	CEdit m_EditWXID;
	CEdit m_EditProUserID;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
};
