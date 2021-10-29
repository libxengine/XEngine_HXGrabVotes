
// XEngine_GrabVotesDlg.h: 头文件
//

#pragma once

// CXEngineGrabVotesDlg 对话框
class CXEngineGrabVotesDlg : public CDialogEx
{
// 构造
public:
	CXEngineGrabVotesDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XENGINE_GRABVOTES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL XEngine_GrabVotes_Post(int nSelected);
public:
	CEdit m_EditDistinctid;
	afx_msg void OnBnClickedButton1();
	CTreeCtrl m_TreeHospital;
	CTabCtrl m_TabDay;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CButton m_BtnHospital;
};
