////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow ラッパー
// NVDSWrap.cpp
//
// Copyright (c) 2019 Ibemu
// Released under the MIT license.
// https://opensource.org/licenses/MIT
//

#include "NVDSWrap.h"
#include "../uLilithPluginSDK/Resource/resource.h"

#include <string>
#include <sstream>
#include <ShObjIdl.h>
#include <propkey.h>
#include <propvarutil.h>

#pragma comment(lib,"NVLibCore.lib")
#pragma comment(lib,"NVAFLib.lib")
#pragma comment(lib,"Propsys.lib")

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// グローバル関数
//

NVRESULT NVDSHOWWRAP_EXPORT NVDSHOWWRAP_API CreateInstance_NVDSWrap(LPIVCOM lpivcom)
{
	// インスタンスの作成
	// vtable を初期化する必要があるので、new 演算子経由でメモリをアロケーションする。

	if (!lpivcom)
	{
		return NVERR_UNDEFINED;
	}

	*lpivcom = (IVCOM) new Class_NVDSWrap;
	if (*lpivcom)
	{
		return NV_OK;
	}
	else
	{
		return NVERR_UNDEFINED;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// メンバ関数
//

Class_NVDSWrap::Class_NVDSWrap(void)
{
	// デフォルトコンストラクタ
	// NVDShowインスタンス
	IVCOM p;
	VCOM_CREATEINSTANCEPROC createInstance = (VCOM_CREATEINSTANCEPROC)GetProcAddress(NVDSWrap_Library.dllInstance, "CreateInstance_NVDShow");
	NVDSWrap_Library.vssDecInfo.CreateInstance(NVDSHOW_FOURCC, &p);
	parent = dynamic_cast<INVAUDIOFILE>(p);
	hwndInfo = NULL;

	// 呼ぶ必要あり
	Class_VCOM::SetCoreData((LPVOID)this, (DWORD) sizeof(Class_NVDSWrap), NVDSWRAP_FOURCC);

	return;
}


Class_NVDSWrap::~Class_NVDSWrap(void)
{
	// デストラクタ
	// NVDShowインスタンス
	parent->Release();
	

	// Release済みか判定
	assert(!vcd.bIsCreated);
	return;
}

inline std::wstring Variant2WString(PROPVARIANT v)
{
	switch (v.vt)
	{
	case VT_I1:
		return std::to_wstring(v.cVal);
	case VT_I2:
		return std::to_wstring(v.iVal);
	case VT_I4:
		return std::to_wstring(v.lVal);

	case VT_UI1:
		return std::to_wstring(v.bVal);
	case VT_UI2:
		return std::to_wstring(v.uiVal);
	case VT_UI4:
		return std::to_wstring(v.ulVal);

	case VT_R4:
		return std::to_wstring(v.fltVal);
	case VT_R8:
		return std::to_wstring(v.dblVal);

	case VT_INT:
		return std::to_wstring(v.intVal);
	case VT_UINT:
		return std::to_wstring(v.uintVal);

	case VT_LPSTR:
	{
		int len = MultiByteToWideChar(CP_ACP, 0, v.pszVal, -1, NULL, 0);
		WCHAR* s = new WCHAR[len + 1ll];
		MultiByteToWideChar(CP_ACP, 0, v.pszVal, -1, s, len);
		std::wstring str(s);
		delete[] s;
		return str;
	}

	case VT_LPWSTR:
		return std::wstring(v.pwszVal);

	case VT_VECTOR | VT_LPWSTR:
	{
		// ベクターはPropVariantGetStringElemで取るといい？
		UINT32 size = v.ulVal;
		std::wostringstream oss;
		for (UINT32 i = 0; i < size; ++i)
		{
			if (i > 0) oss << ", ";
			PWSTR str;
			if (SUCCEEDED(PropVariantGetStringElem(v, i, &str)))
			{
				oss << str;
				CoTaskMemFree(str);
			}
		}
		return oss.str();
	}
	}

	// デフォルト
	return L"";
}


NVRESULT Class_NVDSWrap::Create(LPCVOID lpvParam)
{
	// インスタンスの初期化
	NVRESULT nvres = NV_OK;

	LPCNVAUDIOFILECREATE lpcnvafc = (LPCNVAUDIOFILECREATE)lpvParam;

	if (vcd.bIsCreated)
	{
		// 初期化済みの場合はエラー
		return NVDSWRAPERR_ALREADYUSED;
	}
	if (!parent)
	{
		// parentがNULLの場合もエラー
		return NVDSWRAPERR_DOWN_CAST_FAILED;
	}

	if (lpcnvafc->dwFourCC == NVDSWRAP_FOURCC)
	{
		// FourCCをNVDShowのものに差し替え
		LPNVAUDIOFILECREATE lpnvafc = const_cast<LPNVAUDIOFILECREATE>(lpcnvafc);
		lpnvafc->dwFourCC = NVDSHOW_FOURCC;
	}
	if ((lpcnvafc->dwFourCC == NVAUDIOFILE_FOURCC) || (lpcnvafc->dwFourCC == NVDSHOW_FOURCC) || (lpcnvafc->dwFourCC == NVDSWRAP_FOURCC))
	{
		nvres = parent->Create(lpcnvafc);

		if (nvres)
		{
			return nvres;
		}

		// プロパティを読み込み
		NVAUDIOFILEINFO afi;
		DWORD afisize = sizeof(afi);
		parent->GetInfo(NVAUDIOFILE_FOURCC, &afi, &afisize);
		IPropertyStore* store = NULL;
		SHGetPropertyStoreFromParsingName(afi.lpszDataName, NULL, GETPROPERTYSTOREFLAGS::GPS_DEFAULT, __uuidof(IPropertyStore), (void**)& store);
		if (store)
		{
			PROPVARIANT vArtist;
			PROPVARIANT vTitle;
			PROPVARIANT vAlbum;
			PROPVARIANT vYear;
			PROPVARIANT vTrackNumber;
			PROPVARIANT vGenre;
			PROPVARIANT vComment;

			store->GetValue(PKEY_Music_Artist, &vArtist);
			store->GetValue(PKEY_Title, &vTitle);
			store->GetValue(PKEY_Music_AlbumTitle, &vAlbum);
			store->GetValue(PKEY_Media_Year, &vYear);
			store->GetValue(PKEY_Music_TrackNumber, &vTrackNumber);
			store->GetValue(PKEY_Music_Genre, &vGenre);
			store->GetValue(PKEY_Comment, &vComment);

			nvafd.lpnvafcm = NVAFBuildComment(Variant2WString(vArtist).c_str(), Variant2WString(vTitle).c_str(),
				Variant2WString(vAlbum).c_str(), Variant2WString(vYear).c_str(), Variant2WString(vTrackNumber).c_str(),
				Variant2WString(vGenre).c_str(), Variant2WString(vComment).c_str());
		}
	}
	else
	{
		return NVDSWRAPERR_INVALIDPARAMTYPE;
	}

	if (nvres)
	{
		return nvres;
	}

	vcd.bIsCreated = TRUE;

	return NV_OK;
}


NVRESULT Class_NVDSWrap::ResetData(void)
{
	parent->ResetData();

	return Class_NVAudioFile::ResetData();
}


NVRESULT Class_NVDSWrap::QueryInterface(DWORD dwFourCC, LPVOID* lpvInterface)
{
	// インターフェースの取得

	if (dwFourCC == NVDSWRAP_FOURCC)
	{
		// このクラス
		*lpvInterface = (INVDSWRAP)this;
		AddRef();
		return NV_OK;
	}
	else if (dwFourCC == NVDSHOW_FOURCC)
	{
		// NVDShow
		return parent->QueryInterface(dwFourCC, lpvInterface);
	}
	else
	{
		return Class_NVAudioFile::QueryInterface(dwFourCC, lpvInterface);
	}
}


NVRESULT Class_NVDSWrap::AddInterface(DWORD dwFlag)
{
	VAddInterface(this, (IVCOM)this, NVDSWRAP_FOURCC, dwFlag);

	return Class_NVAudioFile::AddInterface(0);
}


NVRESULT Class_NVDSWrap::DeleteInterface(void)
{
	VDeleteInterface(this);

	return Class_NVAudioFile::DeleteInterface();
}


NVRESULT Class_NVDSWrap::GetInfo(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize)
{
	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}
	
	return parent->GetInfo(dwFourCC, lpvInfo, lpdwSize);
}


NVRESULT Class_NVDSWrap::GetComment(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize)
{
	// 曲名などのコメント情報を取得する
	// NVDShowのGetCommentではなく自前のものを使う

	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}

	if (dwFourCC == NVDSWRAP_FOURCC)
	{
		dwFourCC = NVAUDIOFILE_FOURCC;
	}

	return Class_NVAudioFile::GetComment(dwFourCC, lpvInfo, lpdwSize);

	//return parent->GetComment(dwFourCC, lpvInfo, lpdwSize);
}


NVRESULT Class_NVDSWrap::GetPCMWaveFormat(LPPCMWAVEFORMAT lppcmwf)
{
	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}

	return parent->GetPCMWaveFormat(lppcmwf);
}


NVRESULT Class_NVDSWrap::DecodeToPCMData(LPVOID lpBuffer, LONG lBufferSize, LPLONG lplResultSize)
{
	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}

	return parent->DecodeToPCMData(lpBuffer, lBufferSize, lplResultSize);
}


NVRESULT Class_NVDSWrap::Rewind(void)
{
	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}

	return parent->Rewind();
}

INT_PTR CALLBACK NVDSWrap_InfoDialogProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_INITDIALOG:
	{
		SetProp(hwnd, TEXT("invdswrap"), (HANDLE)lParam);
		SetFocus(GetDlgItem(hwnd, IDC_AUDIOFILE_FILENAME));

		// NVAUDIOFILEINFOはNVDShowが持ってるのでGetInfoを呼ぶしかない
		TCHAR lpszBuf[1024];
		NVAUDIOFILEINFO afi;
		DWORD afisize = sizeof(NVAUDIOFILEINFO);
		if (SUCCEEDED(((INVDSWRAP)lParam)->GetInfo(NVAUDIOFILE_FOURCC, &afi, &afisize)))
		{
			QWORD qwPlayTime = afi.quPlayTime.qw / 1000;

			SetDlgItemText(hwnd, IDC_AUDIOFILE_FILENAME, afi.lpszDataName);
			_stprintf_s(lpszBuf, 1024, TEXT("FileType = \n %s\nFileSize = %I64u bytes\nPlaySize = %I64u bytes\nPlayTime = %2I64u:%02I64u.%03I64u\n")
				TEXT("Bitrate = %d kbps (%s)\nBitsPerSample = %d bits\nSampleRate = %d Hz\nMode = %s"),
				afi.lpszFormatString, afi.quDataSize.qw, afi.quDecodedSize.qw, qwPlayTime / 60, qwPlayTime % 60, afi.quPlayTime.qw % 1000,
				afi.dwBitrate, (afi.dwFlag & NVAUDIOFILE_FLAG_VBR) ? TEXT("VBR") : TEXT("CBR"), afi.dwBitsPerSample, afi.dwSamplerate, afi.lpszModeString);
			SetDlgItemText(hwnd, IDC_AUDIOFILE_INFO, lpszBuf);
		}

		LPNVAUDIOFILECOMMENT lpnvafcm = (((INVDSWRAP)lParam)->nvafd.lpnvafcm);
		if (lpnvafcm)
		{
			SetDlgItemText(hwnd, IDC_AUDIOFILE_TITLE, &lpnvafcm->szString[lpnvafcm->lOffsetTitle]);
			SetDlgItemText(hwnd, IDC_AUDIOFILE_ARTIST, &lpnvafcm->szString[lpnvafcm->lOffsetArtist]);
			SetDlgItemText(hwnd, IDC_AUDIOFILE_ALBUM, &lpnvafcm->szString[lpnvafcm->lOffsetAlbum]);
			SetDlgItemText(hwnd, IDC_AUDIOFILE_DATE, &lpnvafcm->szString[lpnvafcm->lOffsetDate]);
			SetDlgItemText(hwnd, IDC_AUDIOFILE_TRACK, &lpnvafcm->szString[lpnvafcm->lOffsetTrackNumber]);
			SetDlgItemText(hwnd, IDC_AUDIOFILE_GENRE, &lpnvafcm->szString[lpnvafcm->lOffsetGenre]);
			SetDlgItemText(hwnd, IDC_AUDIOFILE_COMMENT, &lpnvafcm->szString[lpnvafcm->lOffsetComment]);
		}
		NVClipWindowPos(hwnd);
	}
	return FALSE;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
		{
			DestroyWindow(hwnd);
		}
		return TRUE;
		}
	}
	break;
	case WM_DESTROY:
	{
		INVDSWRAP invdswrap;

		invdswrap = (INVDSWRAP)GetProp(hwnd, TEXT("invdswrap"));
		if (invdswrap)
		{
			RemoveProp(hwnd, TEXT("invdswrap"));
			NVUnRegisterDialog(invdswrap->hwndInfo);
			invdswrap->hwndInfo = NULL;
			invdswrap->Release();
		}
	}
	break;
	}

	return FALSE;
}

NVRESULT Class_NVDSWrap::FileInfoDialog(HWND hwnd)
{
	// ファイル情報のダイアログを表示
	// 自分で作る
	// フィルタの設定ボタンは未実装

	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}

	if (hwndInfo)
	{
		SetFocus(hwndInfo);
		return NV_OK;
	}

	AddRef();

	hwndInfo = CreateDialogParam(NVGetResourceDLL(), MAKEINTRESOURCE(IDD_AUDIOFILE_INFO), hwnd, NVDSWrap_InfoDialogProc, (LPARAM)this);
	if (!hwndInfo)
	{
		Release();
		return NVDSWRAPERR_CANTCREATEINFODIALOG;
	}
	NVRegisterDialog(hwndInfo);

	return NV_OK;
	//return parent->FileInfoDialog(hwnd);
}

NVRESULT Class_NVDSWrap::GetCurrentPosition(LPQWUNION lpquPosition, DWORD dwFlag)
{
	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}

	return parent->GetCurrentPosition(lpquPosition, dwFlag);
}


NVRESULT Class_NVDSWrap::SetCurrentPosition(QWUNION quPosition, DWORD dwFlag)
{
	if (!vcd.bIsCreated)
	{
		return NVDSWRAPERR_NOCREATE;
	}

	return parent->SetCurrentPosition(quPosition, dwFlag);
}

NVRESULT Class_NVDSWrap::ReferenceTimeToSamples(QWUNION quReferenceTime, LPQWUNION lpquSamples)
{
	if (!vcd.bIsCreated)
	{
		return VAFERR_NOCREATE;
	}

	return parent->ReferenceTimeToSamples(quReferenceTime, lpquSamples);
}

NVRESULT Class_NVDSWrap::SamplesToReferenceTime(QWUNION quSamples, LPQWUNION lpquReferenceTime)
{
	if (!vcd.bIsCreated)
	{
		return VAFERR_NOCREATE;
	}

	return parent->SamplesToReferenceTime(quSamples, lpquReferenceTime);
}

NVRESULT Class_NVDSWrap::GetReferenceTime(LPQWUNION lpquReferenceTime)
{
	if (!vcd.bIsCreated)
	{
		return VAFERR_NOCREATE;
	}

	return parent->GetReferenceTime(lpquReferenceTime);
}

NVRESULT Class_NVDSWrap::GetTotalTime(LPQWUNION lpquTotalTime)
{
	if (!vcd.bIsCreated)
	{
		return VAFERR_NOCREATE;
	}

	return parent->GetTotalTime(lpquTotalTime);
}
