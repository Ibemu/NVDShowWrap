////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow ラッパー
// NVDSWrap.h
//
// Copyright (c) 2019 Ibemu
// Released under the MIT license.
// https://opensource.org/licenses/MIT
//

#pragma once

#include "NVDShowWrap.h"

EXTERN_C_START
#pragma pack(push, 1)

#define NVDSWRAP_FOURCC MAKEFOURCC('W', 'D', 'S', 'W')
#define NVDSHOW_FOURCC MAKEFOURCC('V', 'D', 'S', 'W')

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Class_NVDSWrapクラス
//

class Class_NVDSWrap;
typedef Class_NVDSWrap* INVDSWRAP;
typedef const Class_NVDSWrap* CINVDSWRAP;
typedef INVDSWRAP* LPINVDSWRAP;
typedef const INVDSWRAP* LPCINVDSWRAP;

class NVDSHOWWRAP_CLASS_EXPORT Class_NVDSWrap : virtual public Class_NVAudioFile
{
public:
	// デフォルトコンストラクタ
	Class_NVDSWrap(void);

	// デストラクタ
	VCOM_CLASSMETHOD
		~Class_NVDSWrap(void);

	// インスタンスの初期化
	VCOM_CLASSMETHOD
		NVRESULT Create(LPCVOID lpvParam);

	// インスタンスのデータをリセット
	VCOM_CLASSMETHOD
		NVRESULT ResetData(void);

	// インターフェースの取得
	VCOM_CLASSMETHOD
		NVRESULT QueryInterface(DWORD dwFourCC, LPVOID* lpvInterface);

	// フォーマット独自の拡張情報を取得する
	VCOM_CLASSMETHOD
		NVRESULT GetInfo(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);

	// 曲名などのコメント情報を取得する
	VCOM_CLASSMETHOD
		NVRESULT GetComment(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);

	// デコードデータのフォーマットを取得する
	VCOM_CLASSMETHOD
		NVRESULT GetPCMWaveFormat(LPPCMWAVEFORMAT lppcmwf);

	// データをデコードし、それを受け取る
	VCOM_CLASSMETHOD
		NVRESULT DecodeToPCMData(LPVOID lpBuffer, LONG lBufferSize, LPLONG lplResultSize);

	// データを先頭まで巻き戻す
	VCOM_CLASSMETHOD
		NVRESULT Rewind(void);

	// ファイル情報のダイアログを表示
	VCOM_CLASSMETHOD
		NVRESULT FileInfoDialog(HWND hwnd);

	// ファイルの現在位置をバイト単位で取得
	VCOM_CLASSMETHOD
		NVRESULT GetCurrentPosition(LPQWUNION lpquPosition, DWORD dwFlag);

	// ファイルの現在位置をバイト単位で設定
	VCOM_CLASSMETHOD
		NVRESULT SetCurrentPosition(QWUNION quPosition, DWORD dwFlag);

	// 参照時間(マイクロ秒単位)からサンプル数へ変換する
	VCOM_CLASSMETHOD
		NVRESULT ReferenceTimeToSamples(QWUNION quReferenceTime, LPQWUNION lpquSamples);

	// サンプル数から参照時間(マイクロ秒単位)へ変換する
	VCOM_CLASSMETHOD
		NVRESULT SamplesToReferenceTime(QWUNION quSamples, LPQWUNION lpquReferenceTime);

	// 現在の参照時間(マイクロ秒単位)を取得
	VCOM_CLASSMETHOD
		NVRESULT GetReferenceTime(LPQWUNION lpquReferenceTime);

	// マイクロ秒単位で全再生時間を取得
	VCOM_CLASSMETHOD
		NVRESULT GetTotalTime(LPQWUNION lpquTotalTime);

protected:
	// インターフェースを参照テーブルに登録する
	VCOM_CLASSMETHOD
		NVRESULT AddInterface(DWORD dwFlag);

	// インターフェースを参照テーブルから削除する
	VCOM_CLASSMETHOD
		NVRESULT DeleteInterface(void);

	friend INT_PTR CALLBACK NVDSWrap_InfoDialogProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

protected:
	INVAUDIOFILE parent;
	HWND hwndInfo;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// グローバル関数
//

NVRESULT NVDSHOWWRAP_EXPORT NVDSHOWWRAP_API CreateInstance_NVDSWrap(LPIVCOM lpivcom);

#pragma pack(pop)
EXTERN_C_END