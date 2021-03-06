﻿////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow ラッパープラグイン
// NVDShowWrap.h
//
// Copyright (c) 2019 Ibemu
// Released under the MIT license.
// https://opensource.org/licenses/MIT
//

#pragma once
#define WINVER 0x0600
#define _WIN32_WINNT 0x0600

#include "../uLilithPluginSDK/NVLibCore/NVLibCore.h"
#include "../uLilithPluginSDK/NVAFLib/NVAFLib.h"

EXTERN_C_START
#pragma pack(push, 1)

#ifdef NVDSHOWWRAP_EXPORTS
#define NVDSHOWWRAP_API _stdcall
#define NVDSHOWWRAP_CLASS_EXPORT __declspec(dllexport)
#define NVDSHOWWRAP_EXPORT __declspec(dllexport)
#else
#define NVDSHOWWRAP_API _stdcall
#define NVDSHOWWRAP_CLASS_EXPORT __declspec(dllimport)
#define NVDSHOWWRAP_EXPORT __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// エラーナンバー
//

// 0xBE00は適当
#define NVDSWRAPERR_                        0xBE00
#define MAKE_NVDSWRAPERR(name, value, flag) MAKE_NVERR((name), (NVDSWRAPERR_ | (value)), (flag))
#define MAKE_NVDSWRAPERR_VALUE(value) MAKE_NVERR_VALUE(NVDSWRAPERR_ | (value))


// 0xBE01
#define NVDSWRAPERR_UNSUPPORTED                   MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_UNSUPPORTED"), 0x01, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_UNSUPPORTED             MAKE_NVDSWRAPERR_VALUE(0x01)

// 0xBE02
#define NVDSWRAPERR_ALREADYUSED                   MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_ALREADYUSED"), 0x02, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_ALREADYUSED             MAKE_NVDSWRAPERR_VALUE(0x02)

// 0xBE03
#define NVDSWRAPERR_INVALIDPARAMTYPE              MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_INVALIDPARAMTYPE"), 0x03, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_INVALIDPARAMTYPE        MAKE_NVDSWRAPERR_VALUE(0x03)

// 0xBE04
#define NVDSWRAPERR_INVALIDPARAMSIZE              MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_INVALIDPARAMSIZE"), 0x04, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_INVALIDPARAMSIZE        MAKE_NVDSWRAPERR_VALUE(0x04)

// 0xBE05
#define NVDSWRAPERR_INVALIDPARAM                  MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_INVALIDPARAM"), 0x05, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_INVALIDPARAM            MAKE_NVDSWRAPERR_VALUE(0x05)

// 0xBE06
#define NVDSWRAPERR_NOCREATE                      MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_NOCREATE"), 0x06, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_NOCREATE                MAKE_NVDSWRAPERR_VALUE(0x06)

// 0xBE07
#define NVDSWRAPERR_ENDOFDATA                     VAFERR_ENDOFDATA//MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_ENDOFDATA"), 0x07, NVERR_SAFE)
#define NVDSWRAPERR_VALUE_ENDOFDATA               VAFERR_VALUE_ENDOFDATA//MAKE_NVDSWRAPERR_VALUE(0x07)

// 0xBE08
#define NVDSWRAPERR_BUFFERTOOSMALL                MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_BUFFERTOOSMALL"), 0x08, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_BUFFERTOOSMALL          MAKE_NVDSWRAPERR_VALUE(0x08)

// 0xBE09
#define NVDSWRAPERR_FILEISBROKEN                  MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_FILEISBROKEN"), 0x09, NVERR_NORMAL)
#define NVDSWRAPERR_VALUE_FILEISBROKEN            MAKE_NVDSWRAPERR_VALUE(0x09)

// 0xBE0A
#define NVDSWRAPERR_UNSUPPORTEDFILE               MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_UNSUPPORTEDFILE"), 0x0A, NVERR_NORMAL)
#define NVDSWRAPERR_VALUE_UNSUPPORTEDFILE         MAKE_NVDSWRAPERR_VALUE(0x0A)

// 0xBE0B
#define NVDSWRAPERR_UNKNOWNFOURCC                 MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_UNKNOWNFOURCC"), 0x0B, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_UNKNOWNFOURCC           MAKE_NVDSWRAPERR_VALUE(0x0B)

// 0xBE0C
#define NVDSWRAPERR_CANTCREATEINFODIALOG          MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_CANTCREATEINFODIALOG"), 0x0C, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_CANTCREATEINFODIALOG    MAKE_NVDSWRAPERR_VALUE(0x0C)

// 0xBE0D
#define NVDSWRAPERR_DOWN_CAST_FAILED			  MAKE_NVDSWRAPERR(TEXT("NVDSWRAPERR_DOWN_CAST_FAILED"), 0x0D, NVERR_FATAL)
#define NVDSWRAPERR_VALUE_DOWN_CAST_FAILED		  MAKE_NVDSWRAPERR_VALUE(0x0D)

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow.vssを保持する構造体
//

struct LibraryFunctions
{
	HINSTANCE dllInstance;
	VSSDECINFO vssDecInfo;
};
extern LibraryFunctions NVDSWrap_Library;

#pragma pack(pop)
EXTERN_C_END