// CDialog_DayDoctor.cpp: 实现文件
//

#include "pch.h"
#include "XEngine_GrabVotes.h"
#include "CDialog_DayDoctor.h"
#include "afxdialogex.h"


// CDialog_DayDoctor 对话框

IMPLEMENT_DYNAMIC(CDialog_DayDoctor, CDialogEx)

CDialog_DayDoctor::CDialog_DayDoctor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDialog_DayDoctor::~CDialog_DayDoctor()
{
}

void CDialog_DayDoctor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListDoctor);
	DDX_Control(pDX, IDC_EDIT1, m_EditName);
	DDX_Control(pDX, IDC_EDIT2, m_EditLevel);
	DDX_Control(pDX, IDC_EDIT3, m_EditCode);
	DDX_Control(pDX, IDC_EDIT4, m_EditGoodat);
	DDX_Control(pDX, IDC_EDIT5, m_EditTicket);
	DDX_Control(pDX, IDC_EDIT6, m_EditProName);
	DDX_Control(pDX, IDC_EDIT7, m_EditWXID);
	DDX_Control(pDX, IDC_EDIT8, m_EditProUserID);
	DDX_Control(pDX, IDC_BUTTON4, m_BtnGetVotes);
	DDX_Control(pDX, IDC_LIST2, m_ListInfo);
}


BEGIN_MESSAGE_MAP(CDialog_DayDoctor, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_DayDoctor::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog_DayDoctor::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDialog_DayDoctor::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog_DayDoctor::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDialog_DayDoctor 消息处理程序


BOOL CDialog_DayDoctor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListDoctor.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 40);
	m_ListDoctor.InsertColumn(1, _T("名字"), LVCFMT_CENTER, 50);
	m_ListDoctor.InsertColumn(2, _T("日期"), LVCFMT_CENTER, 50);
	m_ListDoctor.SetExtendedStyle(m_ListDoctor.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_ListInfo.InsertColumn(0, _T("余票"), LVCFMT_CENTER, 40);
	m_ListInfo.InsertColumn(1, _T("时间"), LVCFMT_CENTER, 50);
	m_ListInfo.InsertColumn(2, _T("日期"), LVCFMT_CENTER, 50);
	m_ListInfo.InsertColumn(3, _T("LabelId"), LVCFMT_CENTER, 75);
	m_ListInfo.InsertColumn(4, _T("ScheduleID"), LVCFMT_CENTER, 75);
	m_ListInfo.SetExtendedStyle(m_ListDoctor.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
BOOL CDialog_DayDoctor::Dialog_Doctor_GetInfo()
{
	POSITION pSt_PosItem = m_ListInfo.GetFirstSelectedItemPosition();
	if (NULL == pSt_PosItem)
	{
		AfxMessageBox(_T("没有选择医生排班"));
		return FALSE;
	}
	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	TCHAR tszHdrBuffer[4096];
	TCHAR tszMsgBuffer[2048];
	TCHAR tszItemText[64];
	CHAR* ptszMsgBuffer = NULL;
	CHAR* ptszGBKBuffer = (char*)malloc(1024000);

	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));
	memset(tszItemText, '\0', sizeof(tszItemText));

	((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_EditDistinctid.GetWindowText(m_StrDistinctID);

	LPCTSTR lpszUrl = _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=Card&a=cardList");
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

	CString m_StrDoctorID;
	CString m_StrLabelID;
	CString m_StrScheudleID;
	TCITEM st_TCItem;
	st_TCItem.pszText = tszItemText;
	st_TCItem.cchTextMax = sizeof(tszItemText);
	st_TCItem.mask = TCIF_TEXT;
	((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetItem(((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetCurSel(), &st_TCItem);
	m_EditCode.GetWindowText(m_StrDoctorID);

	int nSelect = m_ListInfo.GetNextSelectedItem(pSt_PosItem);
	m_StrLabelID = m_ListInfo.GetItemText(nSelect, 3);
	m_StrScheudleID = m_ListInfo.GetItemText(nSelect, 4);

	_stprintf_s(tszMsgBuffer, _T("doctorid=%s&date=%s&LabelId=%s&districtCode=%s"), m_StrDoctorID.GetBuffer(), tszItemText, m_StrLabelID.GetBuffer(), m_StrScheudleID.GetBuffer());
	USES_CONVERSION;
	APIClient_Http_Request("POST", W2A(lpszUrl), W2A(tszMsgBuffer), &nResponseCode, &ptszMsgBuffer, &nMsgLen, W2A(tszHdrBuffer));
	BaseLib_Charset_UTFToAnsi(ptszMsgBuffer, ptszGBKBuffer, &nMsgLen);

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
		if (1 != atoi(st_JsonRoot["state"].asCString()))
		{
			AfxMessageBox(A2W(st_JsonRoot["errorMsg"].asCString()));
			free(ptszGBKBuffer);
			return FALSE;
		}
	}
	else
	{
		if (1 != st_JsonRoot["state"].asInt())
		{
			AfxMessageBox(A2W(st_JsonRoot["errorMsg"].asCString()));
			free(ptszGBKBuffer);
			return FALSE;
		}
	}
	Json::Value st_JsonObejct = st_JsonRoot["data"];
	Json::Value st_JsonArray = st_JsonObejct["cardList"];

	m_EditProName.SetWindowText(A2W(st_JsonArray[0]["userName"].asCString()));
	m_EditProUserID.SetWindowText(A2W(st_JsonArray[0]["userid"].asCString()));

	free(ptszGBKBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return TRUE;
}

BOOL CDialog_DayDoctor::Dialog_Doctor_GetWXID()
{
	POSITION pSt_PosItem = m_ListInfo.GetFirstSelectedItemPosition();
	if (NULL == pSt_PosItem)
	{
		AfxMessageBox(_T("没有选择医生排班"));
		return FALSE;
	}
	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	CString m_StrSchudel;
	TCHAR tszHdrBuffer[4096];
	TCHAR tszUrlBuffer[1024];
	CHAR* ptszMsgBuffer = NULL;
	CHAR* ptszGBKBuffer = (char*)malloc(1024000);

	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));
	memset(tszUrlBuffer, '\0', sizeof(tszUrlBuffer));

	int nSelect = m_ListInfo.GetNextSelectedItem(pSt_PosItem);
	m_StrSchudel = m_ListInfo.GetItemText(nSelect, 4);
	((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_EditDistinctid.GetWindowText(m_StrDistinctID);

	_stprintf_s(tszUrlBuffer, _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=Register&a=getRegQueueStart&schedulid=%s"), m_StrSchudel.GetBuffer());
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
	
	USES_CONVERSION;
	APIClient_Http_Request(_X("GET"), W2A(tszUrlBuffer), NULL, &nResponseCode, &ptszMsgBuffer, &nMsgLen, W2A(tszHdrBuffer));
	BaseLib_Charset_UTFToAnsi(ptszMsgBuffer, ptszGBKBuffer, &nMsgLen);

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
		if (1 != atoi(st_JsonRoot["state"].asCString()))
		{
			AfxMessageBox(A2W(st_JsonRoot["errorMsg"].asCString()));
			free(ptszGBKBuffer);
			return FALSE;
		}
	}
	else
	{
		if (1 != st_JsonRoot["state"].asInt())
		{
			AfxMessageBox(A2W(st_JsonRoot["errorMsg"].asCString()));
			free(ptszGBKBuffer);
			return FALSE;
		}
	}
	m_EditWXID.SetWindowText(A2W(st_JsonRoot["data"]["tn"].asCString()));

	free(ptszGBKBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return TRUE;
}

void CDialog_DayDoctor::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pSt_PosItem = m_ListDoctor.GetFirstSelectedItemPosition();
	if (NULL == pSt_PosItem)
	{
		AfxMessageBox(_T("没有选择医生"));
		return;
	}
	if (!Dialog_Doctor_GetInfo())
	{
		return;
	}
	if (!Dialog_Doctor_GetWXID())
	{
		return;
	}
}

BOOL CDialog_DayDoctor::Dialog_Doctor_GetVer()
{
	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	TCHAR tszHdrBuffer[2048];
	CHAR* ptszMsgBuffer = NULL;
	CHAR* ptszGBKBuffer = (char*)malloc(1024000);

	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));
	memset(ptszGBKBuffer, '\0', 1024000);

	((CXEngineGrabVotesDlg*)AfxGetApp()->m_pMainWnd)->m_EditDistinctid.GetWindowText(m_StrDistinctID);

	LPCTSTR lpszUrl = _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=FeyVerify&a=createVerify&v=0.159669334659");
	_stprintf_s(tszHdrBuffer, _T("Host: huaxi2.mobimedical.cn\r\n"
		"Accept: image/webp,image/apng,image/*,*/*;q=0.8\r\n"
		"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 NetType/WIFI MicroMessenger/7.0.20.1781(0x6700143B) WindowsWechat(0x63040026)\r\n"
		"Cookie: %s\r\n"
		"Sec-Fetch-Site: same-origin\r\n"
		"Sec-Fetch-Mode: cors\r\n"
		"Sec-Fetch-Dest: image\r\n"
		"Referer: https://huaxi2.mobimedical.cn/index.php?g=Wap&m=WxView&d=registerAndAppoint&a=index\r\n"
		"Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
	), m_StrDistinctID.GetBuffer());
	USES_CONVERSION;
	APIClient_Http_Request(_X("GET"), W2A(lpszUrl), NULL, &nResponseCode, &ptszMsgBuffer, &nMsgLen, W2A(tszHdrBuffer));
	if (nMsgLen <= 0)
	{
		AfxMessageBox(_T("获取验证图片失败"));
		return FALSE;
	}
#ifdef _DEBUG
	LPCTSTR lpszFile = _T("D:\\XEngine_HXGrabVotes\\Debug\\1.jpg");
#else
	LPCTSTR lpszFile = _T("./1.jpg");
#endif
	FILE* pSt_File = _tfopen(lpszFile, _T("wb"));
	fwrite(ptszMsgBuffer, 1, nMsgLen, pSt_File);
	fclose(pSt_File);

	CDialog_PICVer m_DlgPICVer;
	if (IDOK == m_DlgPICVer.DoModal())
	{
		bRun = FALSE;
	}

	free(ptszGBKBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return TRUE;
}
void CDialog_DayDoctor::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_StrSchedule;
	POSITION pSt_PosItem = m_ListInfo.GetFirstSelectedItemPosition();
	if (NULL == pSt_PosItem)
	{
		return;
	}
	m_StrSchedule = m_ListInfo.GetItemText(m_ListInfo.GetNextSelectedItem(pSt_PosItem), 4);
	if (m_StrSchedule.IsEmpty())
	{
		AfxMessageBox(_T("请求失败,没有获取到个人信息"));
		return;
	}
	Dialog_Doctor_GetVer();
}


void CDialog_DayDoctor::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_EditName.SetWindowText(_T(""));
	m_EditLevel.SetWindowText(_T(""));
	m_EditCode.SetWindowText(_T(""));
	m_EditGoodat.SetWindowText(_T(""));
	m_EditTicket.SetWindowText(_T(""));

	POSITION pSt_PosItem = m_ListDoctor.GetFirstSelectedItemPosition();
	if (NULL == pSt_PosItem)
	{
		return;
	}
	XENGINE_DOCTORINFO* pSt_DoctorInfo = (XENGINE_DOCTORINFO*)m_ListDoctor.GetItemData(m_ListDoctor.GetNextSelectedItem(pSt_PosItem));
	if (NULL == pSt_DoctorInfo)
	{
		return;
	}

	m_EditName.SetWindowText(pSt_DoctorInfo->tszDoctorName);
	m_EditLevel.SetWindowText(pSt_DoctorInfo->tszDoctorType);
	m_EditCode.SetWindowText(pSt_DoctorInfo->tszDoctorID);
	m_EditGoodat.SetWindowText(pSt_DoctorInfo->tszDoctorGoodAt);
	m_EditTicket.SetWindowText(pSt_DoctorInfo->tszDoctorTicket);

	int nMsgLen = 0;
	int nResponseCode = 0;
	CString m_StrDistinctID;
	TCHAR tszHdrBuffer[4096];
	TCHAR tszMsgBuffer[2048];
	TCHAR tszItemText[64];
	CHAR* ptszMsgBuffer = NULL;
	CHAR* ptszGBKBuffer = (char*)malloc(1024000);

	memset(tszHdrBuffer, '\0', sizeof(tszHdrBuffer));
	memset(tszItemText, '\0', sizeof(tszItemText));

	((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_EditDistinctid.GetWindowText(m_StrDistinctID);

	LPCTSTR lpszUrl = _T("https://huaxi2.mobimedical.cn/index.php?g=WapApi&m=Register&a=getDoctorDetail");
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

	CString m_StrDoctorID;
	TCITEM st_TCItem;
	st_TCItem.pszText = tszItemText;
	st_TCItem.cchTextMax = sizeof(tszItemText);
	st_TCItem.mask = TCIF_TEXT;
	((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetItem(((CXEngineGrabVotesDlg*)AfxGetMainWnd())->m_TabDay.GetCurSel(), &st_TCItem);
	m_EditCode.GetWindowText(m_StrDoctorID);

	USES_CONVERSION;
	_stprintf_s(tszMsgBuffer, _T("doctorid=%s&date=%s&LabelId=0&districtCode=%d"), m_StrDoctorID.GetBuffer(), tszItemText, pSt_DoctorInfo->nDistrictCode);
	APIClient_Http_Request(_X("POST"), W2A(lpszUrl), W2A(tszMsgBuffer), &nResponseCode, &ptszMsgBuffer, &nMsgLen, W2A(tszHdrBuffer));
	BaseLib_Charset_UTFToAnsi(ptszMsgBuffer, ptszGBKBuffer, &nMsgLen);

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
	if (Json::stringValue == st_JsonRoot["state"].type())
	{
		if (1 != atoi(st_JsonRoot["state"].asCString()))
		{
			AfxMessageBox(A2W(st_JsonRoot["errorMsg"].asCString()));
			free(ptszGBKBuffer);
			return ;
		}
	}
	else
	{
		if (1 != st_JsonRoot["state"].asInt())
		{
			AfxMessageBox(A2W(st_JsonRoot["errorMsg"].asCString()));
			free(ptszGBKBuffer);
			return ;
		}
	}
	m_ListInfo.DeleteAllItems();
	CString m_StrDate = m_ListDoctor.GetItemText(m_ListDoctor.GetNextSelectedItem(pSt_PosItem), 2);
	Json::Value st_JsonArray = st_JsonRoot["data"]["schedul"];
	for (unsigned int i = 0; i < st_JsonArray.size(); i++)
	{
		if (Json::ValueType::stringValue == st_JsonArray[i]["SeqNoStrLast"].type())
		{
			m_ListInfo.InsertItem(i, A2W(st_JsonArray[i]["SeqNoStrLast"].asCString()));
		}
		else
		{
			TCHAR tszTmp[64];
			memset(tszTmp, '\0', sizeof(tszTmp));
			_stprintf(tszTmp, _T("%d"), st_JsonArray[i]["SeqNoStrLast"].asInt());
			m_ListInfo.InsertItem(i, tszTmp);
		}
		m_ListInfo.SetItemText(i, 1, A2W(st_JsonArray[i]["period"].asCString()));
		m_ListInfo.SetItemText(i, 2, A2W(st_JsonArray[i]["week"].asCString()));
		m_ListInfo.SetItemText(i, 3, A2W(st_JsonArray[i]["LabelId"].asCString()));
		m_ListInfo.SetItemText(i, 4, A2W(st_JsonArray[i]["schedulid"].asCString()));
	}
	free(ptszGBKBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	*pResult = 0;
}

DWORD WINAPI CDialog_DayDoctor::Dialog_Doctor_Thread(LPVOID lParam)
{
	CDialog_DayDoctor* pClass_This = (CDialog_DayDoctor*)lParam;
	while (pClass_This->bRun)
	{
		pClass_This->Dialog_Doctor_GetVer();
		Sleep(100);
	}
	return 0;
}

void CDialog_DayDoctor::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_StrBtnVotes;
	LPCTSTR lpszMsgBtn = _T("一键抢票");
	m_BtnGetVotes.GetWindowText(m_StrBtnVotes);

	if (0 == _tcsncmp(lpszMsgBtn, m_StrBtnVotes.GetBuffer(), _tcslen(lpszMsgBtn)))
	{
		POSITION pSt_PosItem = m_ListInfo.GetFirstSelectedItemPosition();
		if (NULL == pSt_PosItem)
		{
			AfxMessageBox(_T("没有选择医生"));
			return;
		}
		bRun = TRUE;
		hThread = CreateThread(NULL, 0, Dialog_Doctor_Thread, this, 0, NULL);
		m_BtnGetVotes.SetWindowText(_T("暂停抢票"));
	}
	else
	{
		bRun = FALSE;
		CloseHandle(hThread);

		m_BtnGetVotes.SetWindowText(_T("一键抢票"));
	}
}
