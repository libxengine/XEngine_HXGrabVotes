#pragma once


// CDialog_PICVer 对话框
typedef struct  
{
	int x;
	int y;
}MOUSE_PICINFO;

class CDialog_PICVer : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_PICVer)

public:
	CDialog_PICVer(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_PICVer();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticPic();
	CStatic m_StaticTips;
	list<MOUSE_PICINFO> stl_ListMouse;
	CStatic m_StaticPIC;
	BOOL bInit;
	afx_msg void OnPaint();
};
