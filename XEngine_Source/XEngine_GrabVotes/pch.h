// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H
#include <json/json.h>
#include <list>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>
using namespace std;
#include "CDialog_DayDoctor.h"
#include "CDialog_PICVer.h"
#include "XEngine_GrabVotesDlg.h"

typedef struct
{
	TCHAR tszDepName[256];
	int nDistrictCode;
	int nLabelId;
	int nDepId;
}XENGINE_DEPARTMENTINFO;
typedef struct
{
	TCHAR tszDoctorName[256];
	TCHAR tszDoctorID[256];
	TCHAR tszDoctorGoodAt[256];
	TCHAR tszDoctorType[256];
	TCHAR tszDoctorTicket[64];

	int nDistrictCode;
	int nLabelId;
}XENGINE_DOCTORINFO;

extern CDialog_DayDoctor* pm_DialogDoctor;


#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp")
#ifdef _DEBUG
#pragma comment(lib,"../Debug/jsoncpp")
#else
#pragma comment(lib,"../Release/jsoncpp")
#endif