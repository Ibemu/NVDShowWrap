////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow ラッパー
// NVDSWrap.h
//
// by Ibemu
//

#pragma once

#include "NVDShowWrap.h"

EXTERN_C_START
#pragma pack(push, 1)

#define NVDSWRAP_FOURCC MAKEFOURCC('W', 'D', 'S', 'W')
#define NVDSHOW_FOURCC MAKEFOURCC('V', 'D', 'S', 'W')

class Class_NVDSWrap;
typedef Class_NVDSWrap* INVDSWRAP;
typedef const Class_NVDSWrap* CINVDSWRAP;
typedef INVDSWRAP* LPINVDSWRAP;
typedef const INVDSWRAP* LPCINVDSWRAP;

class NVDSHOWWRAP_CLASS_EXPORT Class_NVDSWrap : virtual public Class_NVAudioFile
{
public:
	Class_NVDSWrap(void);
	//  デフォルトコンストラクタ
	//
	//  SetCoreData() を呼び出して、基本クラスにデータを設定する。

	VCOM_CLASSMETHOD
		~Class_NVDSWrap(void);
	//  デストラクタ
	//

	VCOM_CLASSMETHOD
		NVRESULT Create(LPCVOID lpvParam);
	//  インスタンスの初期化
	//
	//  インスタンスにパラメータを与えて、インスタンスのデータを初期化(作成)する。
	//  vcd.bIsCreated フラグを立て、初期化済みかチェックを行えるようにする。

	VCOM_CLASSMETHOD
		NVRESULT ResetData(void);
	//  インスタンスのデータをリセット
	//
	//  インスタンス内で利用したメモリなどを解放し、Create() 呼び出し前の状態に戻す。
	//  vcd.bIsCreated フラグをリセットし、再び Create() が行えるようにする。

	VCOM_CLASSMETHOD
		NVRESULT QueryInterface(DWORD dwFourCC, LPVOID* lpvInterface);
	//  インターフェースの取得
	//
	//  DWORD dwFourCC			取得したいインターフェース
	//  LPVOID *lpvInterface	インターフェースを格納するポインタ
	//
	//  このインスタンスの、dwFourCC で指定した型のインターフェースを取得する。
	//  取得できるインターフェースは、インスタンスによって異なるが、
	//  インスタンスクラスのスーパークラスにあたるクラスのインターフェースは
	//  必ず取得できるように実装しなければならない。
	//  この関数で別のインターフェースを取得すると、内部で AddRef() が行われるので、
	//  古いインターフェースに対してもきちんと Release() する必要がある。

	VCOM_CLASSMETHOD
		NVRESULT GetInfo(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);
	//  フォーマット独自の拡張情報を取得する
	//
	//  DWORD dwFourCC			情報の形式を示すクラス識別子
	//  LPVOID　lpvInfo			情報を受け取るバッファ
	//  LPDWORD　lpdwSize		バッファのサイズ
	//
	//  フォーマットごとに定められた拡張情報を返す。
	//  lpvInfo に NULL を渡すと、必要なバッファサイズが返される。
	//  情報が取得されると、lpdwSize に実際に格納されたサイズが返る。
	//  バッファサイズが足りない場合、エラーが返り、そのとき lpdwSize に必要なサイズが返される。
	//  NVAudioFileインターフェース標準の情報として、
	//  NVAudioFileInfo形式があるので、それには必ず対応するようにする。

	VCOM_CLASSMETHOD
		NVRESULT GetComment(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);
	//  曲名などのコメント情報を取得する
	//
	//  DWORD dwFourCC		情報を受け取る構造体の識別子
	//  LPVOID lpvInfo		情報を受け取るバッファ(構造体)のポインタ
	//  LPDWORD lpdwSize	バッファのサイズ
	//
	//  lpvInfo に NULL を渡すと、必要なバッファサイズが返される。
	//  情報が取得されると、lpdwSize に実際に格納されたサイズが返る。
	//  バッファサイズが足りない場合、エラーが返り、そのとき lpdwSize に必要なサイズが返される。
	//  標準の形式として、NVAudioFileComment形式があるので、
	//  それには必ず対応するようにする。

	VCOM_CLASSMETHOD
		NVRESULT GetPCMWaveFormat(LPPCMWAVEFORMAT lppcmwf);
	//  デコードデータのフォーマットを取得する
	//
	//  LPPCMWAVEFORMAT lppcmwf		情報を受け取るバッファ
	//
	//  PCMWAVEFORMAT 形式で、デコードされてくるデータの形式を取得する。
	//  PCMWAVEFORMAT::wf.wFormatTagは、WAVE_FORMAT_PCMまたはWAVE_FORMAT_IEEE_FLOATのみをサポート

	VCOM_CLASSMETHOD
		NVRESULT DecodeToPCMData(LPVOID lpBuffer, LONG lBufferSize, LPLONG lplResultSize);
	//  データをデコードし、それを受け取る
	//
	//  LPVOID lpBuffer			デコードされたデータを受け取るバッファ
	//  LONG lBufferSize		取得したいデータの量
	//  LPLONG lplResultSize	実際に取得されたデータの量
	//
	//  データをデコードして、PCM 形式で受け取る。そのフォーマットは、GetPCMWaveFormat で取得できるフォーマットに基づいている。
	//  NV_OK が返った場合は、必ず要求したサイズのデータが取得されている。
	//  VAFERR_VALUE_ENDOFDATA の場合、実際に取得されたデータの量は、lplResultSize に返される。
	//  今後の呼び出しは、必ずVAFERR_VALUE_ENDOFDATA になる。
	//  データ中にエラーがあったものの、回復できた場合には、VAFERR_VALUE_ERRORRECOVEREDが返る。
	//	この場合は、デコードはそのまま続行できる。
	//  それ以外のエラーが返った場合は、デコードを続けることはできない。
	//  データの一部でも正常に処理された場合は、lplResultSize に実際に取得されたデータの量が返っている。

	VCOM_CLASSMETHOD
		NVRESULT Rewind(void);
	//  データを先頭まで巻き戻す
	//
	//  結果的にはSetCurrentPosition(0, NVAUDIOFILE_SEEKBEGIN)と同じだが、
	//  フォーマットによっては先頭へのシークは高速に行えるため別途用意
	//  廃止しても良いかな……？

	VCOM_CLASSMETHOD
		NVRESULT FileInfoDialog(HWND hwnd);
	//  ファイル情報のダイアログを表示
	//
	//  HWND hwnd		親ウィンドウのハンドル
	//
	//  ファイルの情報やコメント情報を示すモードレスダイアログを表示する。
	//  既に作成済みの場合には、２重に表示しないように注意
	//  また、AddRef() Release()を使って、
	//  表示中にデコーダがクローズされても大丈夫なようにしておく必要あり。
	//  ダイアログは、NVRegisterDialog()とNVUnRegisterDialog()で、
	//  メッセージループ中でちゃんと処理されるようにする必要あり。

	VCOM_CLASSMETHOD
		NVRESULT GetCurrentPosition(LPQWUNION lpquPosition, DWORD dwFlag);
	//  ファイルの現在位置をバイト単位で取得
	//
	//  LPQWUNION lpquPosition	取得する現在位置のオフセット
	//  DWORD dwFlag			オフセットの基準位置

	VCOM_CLASSMETHOD
		NVRESULT SetCurrentPosition(QWUNION quPosition, DWORD dwFlag);
	//  ファイルの現在位置をバイト単位で設定
	//
	//  QWUNION quPosition	設定する現在位置のオフセット
	//  DWORD dwFlag		オフセットの基準位置
	//
	//  可能な限りバイト単位でのシークを行えるようにすべきだが、
	//  現在のLilithでは、多少の誤差があっても大丈夫なつくりになっている。
	//  ラッパープラグインなど、元のデコーダがサンプル単位やms単位でしか
	//  シーク等行えない時には、その単位に丸めても構わない。
	//  ただし、そのことを付属ドキュメント中に明記するのを心がけること。

	VCOM_CLASSMETHOD
		NVRESULT ReferenceTimeToSamples(QWUNION quReferenceTime, LPQWUNION lpquSamples);
	//  参照時間(マイクロ秒単位)からサンプル数へ変換する
	//
	//  QWUNION quReferenceTime		参照時間(マイクロ秒単位)
	//  LPQWUNION lpquSamples		サンプル数
	VCOM_CLASSMETHOD
		NVRESULT SamplesToReferenceTime(QWUNION quSamples, LPQWUNION lpquReferenceTime);
	//  サンプル数から参照時間(マイクロ秒単位)へ変換する
	//
	//  QWUNION quSamples			サンプル数
	//  LPQWUNION lpquReferenceTime	参照時間(マイクロ秒単位)
	VCOM_CLASSMETHOD
		NVRESULT GetReferenceTime(LPQWUNION lpquReferenceTime);
	//  現在の参照時間(マイクロ秒単位)を取得
	//
	//  LPQWUNION lpquReferenceTime		参照時間(マイクロ秒単位)

	VCOM_CLASSMETHOD
		NVRESULT GetTotalTime(LPQWUNION lpquTotalTime);
	//  マイクロ秒単位で全再生時間を取得
	//
	//  LPQWUNION lpquTotalTime		全再生時間(マイクロ秒単位)

protected:
	VCOM_CLASSMETHOD
		NVRESULT AddInterface(DWORD dwFlag);
	//  インターフェースを参照テーブルに登録する
	//
	//  DWORD dwFlag	クラスインスタンスの場合１、それ以外は０
	//
	//  コンストラクタの中で呼ばれ、インターフェースポインタをテーブルに登録し、
	//  VIsValidInterface() でインターフェースの有効性を検証できるようにする。

	VCOM_CLASSMETHOD
		NVRESULT DeleteInterface(void);
	//  インターフェースを参照テーブルから削除する
	//
	//  DeleteInstance() の中で呼ばれ、インターフェースポインタをテーブルから削除する。

	friend INT_PTR CALLBACK NVDSWrap_InfoDialogProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

protected:
	INVAUDIOFILE parent;
	HWND hwndInfo;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ライブラリ関数の定義
//

NVRESULT NVDSHOWWRAP_EXPORT NVDSHOWWRAP_API CreateInstance_NVDSWrap(LPIVCOM lpivcom);

#pragma pack(pop)
EXTERN_C_END