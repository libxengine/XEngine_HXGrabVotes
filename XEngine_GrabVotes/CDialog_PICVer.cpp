// CDialog_PICVer.cpp: 实现文件
//

#include "pch.h"
#include "XEngine_GrabVotes.h"
#include "CDialog_PICVer.h"
#include "afxdialogex.h"


// CDialog_PICVer 对话框

IMPLEMENT_DYNAMIC(CDialog_PICVer, CDialogEx)

CDialog_PICVer::CDialog_PICVer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CDialog_PICVer::~CDialog_PICVer()
{
}

void CDialog_PICVer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_StaticTips);
	DDX_Control(pDX, IDC_STATIC_PIC, m_StaticPIC);
}


BEGIN_MESSAGE_MAP(CDialog_PICVer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_PICVer::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_STATIC_PIC, &CDialog_PICVer::OnStnClickedStaticPic)
ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialog_PICVer 消息处理程序


void CDialog_PICVer::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	TCHAR tszHdrBuffer[4096];
	TCHAR tszBodyBuffer[1024];
	TCHAR tszItemText[64];
	CHAR* ptszMsgBuffer = NULL;
	CHAR* ptszGBKBuffer = (char*)malloc(1024000);

	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));
	memset(tszBodyBuffer, '\0', sizeof(tszBodyBuffer));
	memset(tszItemText, '\0', sizeof(tszItemText));

	((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_EditDistinctid.GetWindowText(m_StrDistinctID);

	LPCTSTR lpszUrl = _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=Register&a=submitReg");
	_stprintf_s(tszHdrBuffer, _T("Host: huaxi2.mobimedical.cn\r\n"
		"Accept: */*\r\n"
		"Origin: https://huaxi2.mobimedical.cn\r\n"
		"X-Requested-With: XMLHttpRequest\r\n"
		"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 NetType/WIFI MicroMessenger/7.0.20.1781(0x6700143B) WindowsWechat(0x63040026)\r\n"
		"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
		"Cookie: %s\r\n"
		"Sec-Fetch-Site: same-origin\r\n"
		"Sec-Fetch-Mode: cors\r\n"
		"Sec-Fetch-Dest: empty\r\n"
		"Referer: https://huaxi2.mobimedical.cn/index.php?g=Wap&m=WxView&d=registerAndAppoint&a=index\r\n"
		"Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
	), m_StrDistinctID.GetBuffer());

	CString m_StrSchedule;
	CString m_StrDoctorID;
	CString m_StrUserID;
	CString m_StrWXID;
	HTREEITEM hRoot = ((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TreeHospital.GetSelectedItem();
	if (NULL == hRoot)
	{
		AfxMessageBox(_T("没有选择部门,无法继续"));
		return;
	}
	XENGINE_DEPARTMENTINFO* pSt_Department = (XENGINE_DEPARTMENTINFO*)((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TreeHospital.GetItemData(hRoot);

	pm_DialogDoctor[((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetCurSel()].m_EditSchedule.GetWindowText(m_StrSchedule);
	pm_DialogDoctor[((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetCurSel()].m_EditCode.GetWindowText(m_StrDoctorID);
	pm_DialogDoctor[((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetCurSel()].m_EditProUserID.GetWindowText(m_StrUserID);
	pm_DialogDoctor[((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetCurSel()].m_EditWXID.GetWindowText(m_StrWXID);

	BOOL bFirst = TRUE;
	TCHAR tszMousePoint[MAX_PATH];
	memset(tszMousePoint, '\0', MAX_PATH);
	for (auto stl_ListIterator = stl_ListMouse.begin(); stl_ListIterator != stl_ListMouse.end(); stl_ListIterator++)
	{
		TCHAR tszPointer[128];
		memset(tszPointer, '\0', sizeof(tszPointer));

		_stprintf_s(tszPointer, _T("%d%%2C%d"), stl_ListIterator->x, stl_ListIterator->y);

		if (!bFirst)
		{
			_tcscat(tszMousePoint, "%3B");
		}
		_tcscat(tszMousePoint, tszPointer);
		bFirst = FALSE;
	}
	stl_ListMouse.clear();
	_stprintf_s(tszBodyBuffer, _T("tagArray=%s&schedulid=%s&deptId=%d&userid=%s&is_ai=&token=%s"), tszMousePoint, m_StrSchedule.GetBuffer(), pSt_Department->nDepId, m_StrUserID.GetBuffer(), m_StrWXID.GetBuffer());
	APIHelp_HttpRequest_Post(lpszUrl, tszBodyBuffer, &nResponseCode, &ptszMsgBuffer, &nMsgLen, tszHdrBuffer);
	BaseLib_OperatorString_UTFToAnsi(ptszMsgBuffer, ptszGBKBuffer, &nMsgLen);

	Json::Value st_JsonRoot;
	Json::CharReaderBuilder st_JsonBuild;
	JSONCPP_STRING st_JsonError;
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuild.newCharReader());
	//解析JSON
	if (!pSt_JsonReader->parse(ptszGBKBuffer, ptszGBKBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		AfxMessageBox(_T("解析数据失败,无法继续"));
		free(ptszGBKBuffer);
		return ;
	}
	AfxMessageBox(st_JsonRoot["errorMsg"].asCString());
	free(ptszGBKBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
}


BOOL CDialog_PICVer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	bInit = FALSE;
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog_PICVer::OnStnClickedStaticPic()
{
	// TODO: 在此添加控件通知处理程序代码
	CPoint m_Point;
	CString m_StrTips;
	TCHAR tszMsgBuffer[MAX_PATH];

	memset(tszMsgBuffer, '\0', MAX_PATH);

	CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC);
	GetCursorPos(&m_Point);
	CRect pRect;
	pWnd->GetClientRect(&pRect);
	pWnd->ScreenToClient(&m_Point);
	
	m_StaticTips.GetWindowText(m_StrTips);
	_stprintf_s(tszMsgBuffer, _T("%s 鼠标点击:X:%d Y:%d"), m_StrTips.GetBuffer(), m_Point.x, m_Point.y);
	m_StaticTips.SetWindowText(tszMsgBuffer);

	MOUSE_PICINFO st_PICMouse;
	st_PICMouse.x = m_Point.x;
	st_PICMouse.y = m_Point.y;
	stl_ListMouse.push_back(st_PICMouse);
}

void CDialog_PICVer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	if (!bInit)
	{
#ifdef _DEBUG
		LPCTSTR lpszFile = _T("D:\\XEngine_GrabVotes\\Debug\\1.jpg");
#else
		LPCTSTR lpszFile = _T("./1.jpg");
#endif
		CImage m_Image;
		m_Image.Load(lpszFile);

		//获取控件的矩形
		CRect rectControl;  //控件矩形对象
		CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC); //Picture Control的ID为IDC_IMAGE

		int nPICWidth = m_Image.GetWidth();
		int nPICHeight = m_Image.GetHeight();
		pWnd->MoveWindow(0, 0, nPICWidth, nPICHeight);    //固定Picture Control控件的大小 
		pWnd->GetClientRect(&rectControl);
		//以控件为画布，在其上画图
		CDC* pDc = GetDlgItem(IDC_STATIC_PIC)->GetDC();
		SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//绘图前必须调用此函数（设置缩放模式），否则失真严重

		//画图（以下两种方法都可）
		m_Image.StretchBlt(pDc->m_hDC, rectControl, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域
		//m_Image.Draw(pDc->m_hDC, rectControl);                //将图片绘制到Picture控件表示的矩形区域

		m_Image.Destroy();
		pWnd->ReleaseDC(pDc);
		bInit = TRUE;
	}
}
