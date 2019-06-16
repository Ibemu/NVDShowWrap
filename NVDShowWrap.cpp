﻿////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow ラッパープラグイン
// NVDShowWrap.cpp
//
// by Ibemu
//

#include "NVDShowWrap.h"
#include "NVDSWrap.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// プロトタイプ
//

EXTERN_C_START

//  Generic
NVRESULT NVDSHOWWRAP_EXPORT NVDSHOWWRAP_API VSSGetPluginInfo(LPVSSPLUGININFO lpInfo);

//  VSS Category D
NVRESULT NVDSHOWWRAP_API VSSDecGetInfo(LPVSSDECINFO lpInfo);
NVRESULT NVDSHOWWRAP_API VSSDecIsSupported(INVSTREAM invst, DWORD dwFourCC);
NVRESULT NVDSHOWWRAP_API VSSDecCreateInstance(DWORD dwFourCC, LPIVCOM lpivcom);
HWND NVDSHOWWRAP_API VSSDecConfigDialog(DWORD dwFourCC, HINSTANCE hInstance, HWND hwndOwner);

EXTERN_C_END

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 定数
//

#define SUPPORT_COUNT 1

const static DWORD lpdwSupportFourCC[SUPPORT_COUNT] = { NVDSWRAP_FOURCC };
const static LPCTSTR lpcszSupportFileType[SUPPORT_COUNT] =
{
	TEXT("Direct Show File (Wrap)"),
};
const static VSSPLUGININFO vssInfo =
{
	0x3000, TEXT("NVDirectShow Wrapper"), TEXT("Ibemu"),
	TEXT("https://twitter.com/Ibemu231"), TEXT("DirectShow Reader/Decoder"),
	VSSDecGetInfo, NULL, NULL,
};

const static VSSDECINFO vssDecInfo =
{
	SUPPORT_COUNT, lpdwSupportFourCC, lpcszSupportFileType,
	VSSDecIsSupported, VSSDecCreateInstance, VSSDecConfigDialog,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 関数
//

NVRESULT NVDSHOWWRAP_EXPORT NVDSHOWWRAP_API VSSGetPluginInfo(LPVSSPLUGININFO lpInfo)
{
	if (!lpInfo)
	{
		return VAFERR_INVALIDPARAM;
	}

	CopyMemory(lpInfo, &vssInfo, sizeof(VSSPLUGININFO));
	return NV_OK;
}

NVRESULT NVDSHOWWRAP_API VSSDecGetInfo(LPVSSDECINFO lpInfo)
{
	if (!lpInfo)
	{
		return VAFERR_INVALIDPARAM;
	}

	CopyMemory(lpInfo, &vssDecInfo, sizeof(VSSDECINFO));
	return NV_OK;
}

NVRESULT NVDSHOWWRAP_API VSSDecIsSupported(INVSTREAM invst, DWORD dwFourCC)
{
	if (dwFourCC == NVDSWRAP_FOURCC) dwFourCC = NVDSHOW_FOURCC;

	return NVDSWrap_Library.vssDecInfo.IsSupported(invst, dwFourCC);
}

NVRESULT NVDSHOWWRAP_API VSSDecCreateInstance(DWORD dwFourCC, LPIVCOM lpivcom)
{
	switch (dwFourCC)
	{
	case NVDSWRAP_FOURCC:
	//case NVDSHOW_FOURCC:
	{
		return CreateInstance_NVDSWrap(lpivcom);
	}
	default:
		return VAFERR_UNSUPPORTED;
	}
}

HWND NVDSHOWWRAP_API VSSDecConfigDialog(DWORD dwFourCC, HINSTANCE hInstance, HWND hwndOwner)
{
	if (dwFourCC == NVDSWRAP_FOURCC) dwFourCC = NVDSHOW_FOURCC;
	return NVDSWrap_Library.vssDecInfo.ConfigDialog(dwFourCC, hInstance, hwndOwner);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// グローバル変数
//
HINSTANCE NVDSWrap_Instance;					//  DLL モジュールのインスタンスハンドル
LONG NVDSWrap_AttachedProcessCount = 0;			//  アタッチされたプロセスの数
LibraryFunctions NVDSWrap_Library;					//  externしたやつ

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// エントリーポイント
//

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//  アタッチされたプロセス数のカウント
		if (InterlockedIncrement(&NVDSWrap_AttachedProcessCount) == 1)
		{
			NVDSWrap_Instance = hModule;		//  インスタンスハンドルの保存

			NVDSWrap_Library.dllInstance = LoadLibrary(TEXT("Plugin\\NVDShow.vss.org"));
			VSSPLUGININFO info;
			VSSGETPLUGININFO getInfo = (VSSGETPLUGININFO)GetProcAddress(NVDSWrap_Library.dllInstance, "VSSGetPluginInfo");
			getInfo(&info);
			info.VSSDecGetInfo(&NVDSWrap_Library.vssDecInfo);

			//  スレッドのアタッチを通知しないようにする
			DisableThreadLibraryCalls(hModule);
		}
	}
	break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
	{
		//  アタッチされたプロセス数のカウント
		//  静的データの解放
		if (InterlockedDecrement(&NVDSWrap_AttachedProcessCount) == 0)
		{
			FreeLibrary(NVDSWrap_Library.dllInstance);
		}
	}
	break;
	}
	return TRUE;
}

