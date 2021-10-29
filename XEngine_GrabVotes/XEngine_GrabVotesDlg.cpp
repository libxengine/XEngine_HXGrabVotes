
// XEngine_GrabVotesDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "XEngine_GrabVotes.h"
#include "XEngine_GrabVotesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXEngineGrabVotesDlg 对话框
CDialog_DayDoctor* pm_DialogDoctor = NULL;


CXEngineGrabVotesDlg::CXEngineGrabVotesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XENGINE_GRABVOTES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXEngineGrabVotesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditDistinctid);
	DDX_Control(pDX, IDC_TREE1, m_TreeHospital);
	DDX_Control(pDX, IDC_TAB1, m_TabDay);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnHospital);
}

BEGIN_MESSAGE_MAP(CXEngineGrabVotesDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CXEngineGrabVotesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CXEngineGrabVotesDlg::OnBnClickedButton2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CXEngineGrabVotesDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CXEngineGrabVotesDlg 消息处理程序

BOOL CXEngineGrabVotesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
#ifdef _DEBUG
	LPCTSTR lpszFile = _T("D:\\XEngine_HXGrabVotes\\Debug\\Votes.ini");
#else
	LPCTSTR lpszFile = _T("./Votes.ini");
#endif
	TCHAR tszMsgBuffer[1024];
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	GetPrivateProfileString("Info", "cookie", NULL, tszMsgBuffer, sizeof(tszMsgBuffer), lpszFile);
	m_EditDistinctid.SetWindowText(tszMsgBuffer);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CXEngineGrabVotesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CXEngineGrabVotesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXEngineGrabVotesDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	TCHAR tszHdrBuffer[4096];
	CHAR* ptszMsgBuffer = NULL;

	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));

	m_EditDistinctid.GetWindowText(m_StrDistinctID);

	LPCTSTR lpszUrl = _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=Register&a=dutyDeptList");
	_stprintf_s(tszHdrBuffer, _T("Accept: */*\r\n"
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

	CHAR* ptszGBKBuffer = (char*)malloc(1024000);
	if (NULL == ptszGBKBuffer)
	{
		return;
	}
	memset(ptszGBKBuffer, '\0', 1024000);
	APIHelp_HttpRequest_Get(lpszUrl, &ptszMsgBuffer, &nMsgLen, &nResponseCode, tszHdrBuffer);
	BaseLib_OperatorString_UTFToAnsi(ptszMsgBuffer, ptszGBKBuffer, &nMsgLen);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	Json::Value st_JsonRoot;
	Json::CharReaderBuilder st_JsonBuild;
	JSONCPP_STRING st_JsonError;
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuild.newCharReader());
	//解析JSON
	if (!pSt_JsonReader->parse(ptszGBKBuffer, ptszGBKBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		AfxMessageBox(_T("解析数据失败,无法继续"));
		free(ptszGBKBuffer);
		return;
	}

	if (Json::stringValue == st_JsonRoot["state"].type())
	{
		if (1 != _ttoi(st_JsonRoot["state"].asCString()))
		{
			AfxMessageBox(st_JsonRoot["errorMsg"].asCString());
			free(ptszGBKBuffer);
			return;
		}
	}
	else
	{
		if (1 != st_JsonRoot["state"].asInt())
		{
			AfxMessageBox(st_JsonRoot["errorMsg"].asCString());
			free(ptszGBKBuffer);
			return;
		}
	}
	//医院
	Json::Value::Members st_JsonRootMember = st_JsonRoot["data"].getMemberNames();
	Json::Value::Members::iterator stl_HospitalIterator = st_JsonRootMember.begin();
	for (unsigned int i = 0; stl_HospitalIterator != st_JsonRootMember.end(); stl_HospitalIterator++, i++)
	{
		Json::Value st_JsonArray = st_JsonRoot["data"][stl_HospitalIterator->c_str()];
		HTREEITEM hRoot = m_TreeHospital.InsertItem(stl_HospitalIterator->c_str(), 1, 0, TVI_ROOT);

		Json::Value::Members st_JsonSubMember = st_JsonArray.getMemberNames();
		Json::Value::Members::iterator stl_DepartmentIterator = st_JsonSubMember.begin();
		for (unsigned int j = 0; stl_DepartmentIterator != st_JsonSubMember.end(); stl_DepartmentIterator++, j++)
		{
			Json::Value st_JsonDepartment = st_JsonArray[stl_DepartmentIterator->c_str()];
			HTREEITEM hDepartment = m_TreeHospital.InsertItem(st_JsonDepartment["deptName"].asCString(), 1, 0, hRoot);

			Json::Value::Members st_JsonNodeMember = st_JsonDepartment["tree"].getMemberNames();
			Json::Value::Members::iterator stl_NodeIterator = st_JsonNodeMember.begin();
			for (unsigned int k = 0; stl_NodeIterator != st_JsonNodeMember.end(); stl_NodeIterator++, k++)
			{
				Json::Value st_JsonNode = st_JsonDepartment["tree"][stl_NodeIterator->c_str()];
				HTREEITEM hNode = m_TreeHospital.InsertItem(st_JsonNode["deptName"].asCString(), 1, 0, hDepartment);

				XENGINE_DEPARTMENTINFO* pSt_DepartmentInfo = new XENGINE_DEPARTMENTINFO;
				memset(pSt_DepartmentInfo, '\0', sizeof(XENGINE_DEPARTMENTINFO));

				if (!st_JsonNode["deptName"].isNull())
				{
					_tcscpy(pSt_DepartmentInfo->tszDepName, st_JsonNode["deptName"].asCString());
				}
				if (!st_JsonNode["deptId"].isNull())
				{
					pSt_DepartmentInfo->nDepId = _ttoi(st_JsonNode["deptId"].asCString());
				}
				if (!st_JsonNode["LabelId"].isNull())
				{
					pSt_DepartmentInfo->nLabelId = _ttoi(st_JsonNode["LabelId"].asCString());
				}
				if (!st_JsonNode["districtCode"].isNull())
				{
					pSt_DepartmentInfo->nDistrictCode = _ttoi(st_JsonNode["districtCode"].asCString());
				}

				m_TreeHospital.SetItemData(hNode, (DWORD_PTR)pSt_DepartmentInfo);
			}
		}
	}
	free(ptszGBKBuffer);
	m_BtnHospital.EnableWindow(FALSE);
}


void CXEngineGrabVotesDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	TCHAR tszHdrBuffer[4096];
	CHAR* ptszMsgBuffer = NULL;
	XENGINE_LIBTIMER st_LibTime;

	if (NULL != pm_DialogDoctor)
	{
		for (int i = 0; i < m_TabDay.GetItemCount(); i++)
		{
			for (int j = 0; j < pm_DialogDoctor[i].m_ListDoctor.GetItemCount(); j++)
			{
				XENGINE_DOCTORINFO *pSt_DoctorInfo = (XENGINE_DOCTORINFO *)pm_DialogDoctor[i].m_ListDoctor.GetItemData(j);
				delete pSt_DoctorInfo;
				pSt_DoctorInfo = NULL;
			}
		}
		m_TabDay.DeleteAllItems();
		delete[]pm_DialogDoctor;
		pm_DialogDoctor = NULL;
	}
	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));
	memset(&st_LibTime, '\0', sizeof(XENGINE_LIBTIMER));

	m_EditDistinctid.GetWindowText(m_StrDistinctID);

	BaseLib_OperatorTime_GetSysTime(&st_LibTime);

	LPCTSTR lpszUrl = _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=Register&a=getRegistDate");
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

	CHAR* ptszGBKBuffer = (char*)malloc(1024000);
	if (NULL == ptszGBKBuffer)
	{
		return;
	}
	memset(ptszGBKBuffer, '\0', 1024000);
	APIHelp_HttpRequest_Get(lpszUrl, &ptszMsgBuffer, &nMsgLen, &nResponseCode, tszHdrBuffer);
	BaseLib_OperatorString_UTFToAnsi(ptszMsgBuffer, ptszGBKBuffer, &nMsgLen);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	Json::Value st_JsonRoot;
	Json::CharReaderBuilder st_JsonBuild;
	JSONCPP_STRING st_JsonError;
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuild.newCharReader());
	//解析JSON
	if (!pSt_JsonReader->parse(ptszGBKBuffer, ptszGBKBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		AfxMessageBox(_T("解析数据失败,无法继续"));
		free(ptszGBKBuffer);
		return;
	}
	if (Json::stringValue == st_JsonRoot["state"].type())
	{
		if (1 != _ttoi(st_JsonRoot["state"].asCString()))
		{
			AfxMessageBox(st_JsonRoot["errorMsg"].asCString());
			free(ptszGBKBuffer);
			return;
		}
	}
	else
	{
		if (1 != st_JsonRoot["state"].asInt())
		{
			AfxMessageBox(st_JsonRoot["errorMsg"].asCString());
			free(ptszGBKBuffer);
			return;
		}
	}
	Json::Value st_JsonArray = st_JsonRoot["data"];
	pm_DialogDoctor = new CDialog_DayDoctor[st_JsonArray.size()];

	for (unsigned int i = 0; i < st_JsonArray.size(); i++)
	{
		m_TabDay.InsertItem(i, st_JsonArray[i]["date"].asCString());
		pm_DialogDoctor[i].Create(IDD_DIALOG1, &m_TabDay);

		CRect st_Rect;
		m_TabDay.GetClientRect(&st_Rect);
		st_Rect.top += 20;
		st_Rect.bottom -= 0;
		st_Rect.left += 0;
		st_Rect.right -= 0;
		pm_DialogDoctor[i].MoveWindow(&st_Rect);
		pm_DialogDoctor[i].ShowWindow(SW_HIDE);
	}
	pm_DialogDoctor[0].ShowWindow(SW_SHOW);
	m_TabDay.SetCurSel(0);
	free(ptszGBKBuffer);

	XEngine_GrabVotes_Post(0);
	return;
}

BOOL CXEngineGrabVotesDlg::XEngine_GrabVotes_Post(int nSelected)
{
	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	TCHAR tszHdrBuffer[4096];
	TCHAR tszBodyBuffer[1024];
	TCHAR tszMsgBuffer[2048];
	TCHAR tszItemText[64];
	CHAR* ptszMsgBuffer = NULL;
	CHAR* ptszGBKBuffer = (char*)malloc(1024000);
	XENGINE_LIBTIMER st_LibTime;

	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));
	memset(tszBodyBuffer, '\0', sizeof(tszBodyBuffer));
	memset(tszItemText, '\0', sizeof(tszItemText));
	memset(&st_LibTime, '\0', sizeof(XENGINE_LIBTIMER));

	m_EditDistinctid.GetWindowText(m_StrDistinctID);

	BaseLib_OperatorTime_GetSysTime(&st_LibTime);

	LPCTSTR lpszUrl = _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=Register&a=getDoctorList");
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

	HTREEITEM hRoot = m_TreeHospital.GetSelectedItem();
	if (NULL == hRoot)
	{
		AfxMessageBox(_T("没有选择部门,无法继续"));
		return FALSE;
	}
	XENGINE_DEPARTMENTINFO* pSt_Department = (XENGINE_DEPARTMENTINFO*)m_TreeHospital.GetItemData(hRoot);

	TCITEM st_TCItem;
	st_TCItem.pszText = tszItemText;
	st_TCItem.cchTextMax = sizeof(tszItemText);
	st_TCItem.mask = TCIF_TEXT;
	m_TabDay.GetItem(nSelected, &st_TCItem);
	_stprintf_s(tszMsgBuffer, _T("deptId=%d&date=%s&SessionType=&LabelId=%d&districtCode=%d"), pSt_Department->nDepId, tszItemText, pSt_Department->nLabelId, pSt_Department->nDistrictCode);
	APIHelp_HttpRequest_Post(lpszUrl, tszMsgBuffer, &nResponseCode, &ptszMsgBuffer, &nMsgLen, tszHdrBuffer);
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
		return FALSE;
	}
	if (Json::stringValue == st_JsonRoot["state"].type())
	{
		if (1 != _ttoi(st_JsonRoot["state"].asCString()))
		{
			AfxMessageBox(st_JsonRoot["errorMsg"].asCString());
			free(ptszGBKBuffer);
			return FALSE;
		}
	}
	else
	{
		if (1 != st_JsonRoot["state"].asInt())
		{
			AfxMessageBox(st_JsonRoot["errorMsg"].asCString());
			free(ptszGBKBuffer);
			return FALSE;
		}
	}
	Json::Value st_JsonArray = st_JsonRoot["data"];
	for (unsigned int i = 0; i < st_JsonArray.size(); i++)
	{
		XENGINE_DOCTORINFO* pSt_DoctorInfo = new XENGINE_DOCTORINFO;
		memset(pSt_DoctorInfo, '\0', sizeof(XENGINE_DOCTORINFO));

		if (!st_JsonArray[i]["docName"].isNull())
		{
			_tcscpy(pSt_DoctorInfo->tszDoctorName, st_JsonArray[i]["docName"].asCString());
		}

		if (Json::ValueType::stringValue == st_JsonArray[i]["districtCode"].type())
		{
			pSt_DoctorInfo->nDistrictCode = _ttoi(st_JsonArray[i]["districtCode"].asCString());
		}
		else
		{
			pSt_DoctorInfo->nDistrictCode = st_JsonArray[i]["districtCode"].asInt();
		}

		if (Json::ValueType::stringValue == st_JsonArray[i]["doctorid"].type())
		{
			_tcscpy(pSt_DoctorInfo->tszDoctorID, st_JsonArray[i]["doctorid"].asCString());
		}
		else
		{
			_stprintf(pSt_DoctorInfo->tszDoctorID, _T("%d"), st_JsonArray[i]["doctorid"].asInt());
		}

		if (!st_JsonArray[i]["begoodat"].isNull())
		{
			_tcscpy(pSt_DoctorInfo->tszDoctorGoodAt, st_JsonArray[i]["begoodat"].asCString());
		}
		if (!st_JsonArray[i]["SessionType"].isNull())
		{
			_tcscpy(pSt_DoctorInfo->tszDoctorType, st_JsonArray[i]["SessionType"].asCString());
		}

		if (Json::ValueType::stringValue == st_JsonArray[i]["SeqNoStrLast"].type())
		{
			_tcscpy(pSt_DoctorInfo->tszDoctorTicket, st_JsonArray[i]["SeqNoStrLast"].asCString());
		}
		else
		{
			_stprintf(pSt_DoctorInfo->tszDoctorTicket, _T("%d"), st_JsonArray[i]["SeqNoStrLast"].asInt());
		}

		TCHAR tszItemBuffer[MAX_PATH];
		memset(tszItemBuffer, '\0', MAX_PATH);

		_stprintf_s(tszItemBuffer, _T("%d"), i);
		pm_DialogDoctor[m_TabDay.GetCurSel()].m_ListDoctor.InsertItem(i, tszItemBuffer);
		pm_DialogDoctor[m_TabDay.GetCurSel()].m_ListDoctor.SetItemText(i, 1, pSt_DoctorInfo->tszDoctorName);
		pm_DialogDoctor[m_TabDay.GetCurSel()].m_ListDoctor.SetItemText(i, 2, st_JsonArray[i]["period"].asCString());
		pm_DialogDoctor[m_TabDay.GetCurSel()].m_ListDoctor.SetItemData(i, (DWORD_PTR)pSt_DoctorInfo);
	}
	free(ptszGBKBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return TRUE;
}
void CXEngineGrabVotesDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_TabDay.GetItemCount(); i++)
	{
		if (i == m_TabDay.GetCurSel())
		{
			pm_DialogDoctor[i].ShowWindow(TRUE);
		}
		else
		{
			pm_DialogDoctor[i].ShowWindow(FALSE);
		}
	}

	if (pm_DialogDoctor[m_TabDay.GetCurSel()].m_ListDoctor.GetItemCount() <= 0)
	{
		XEngine_GrabVotes_Post(m_TabDay.GetCurSel());
	}
	*pResult = 0;
}