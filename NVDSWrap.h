////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow ���b�p�[
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
// Class_NVDSWrap�N���X
//

class Class_NVDSWrap;
typedef Class_NVDSWrap* INVDSWRAP;
typedef const Class_NVDSWrap* CINVDSWRAP;
typedef INVDSWRAP* LPINVDSWRAP;
typedef const INVDSWRAP* LPCINVDSWRAP;

class NVDSHOWWRAP_CLASS_EXPORT Class_NVDSWrap : virtual public Class_NVAudioFile
{
public:
	// �f�t�H���g�R���X�g���N�^
	Class_NVDSWrap(void);

	// �f�X�g���N�^
	VCOM_CLASSMETHOD
		~Class_NVDSWrap(void);

	// �C���X�^���X�̏�����
	VCOM_CLASSMETHOD
		NVRESULT Create(LPCVOID lpvParam);

	// �C���X�^���X�̃f�[�^�����Z�b�g
	VCOM_CLASSMETHOD
		NVRESULT ResetData(void);

	// �C���^�[�t�F�[�X�̎擾
	VCOM_CLASSMETHOD
		NVRESULT QueryInterface(DWORD dwFourCC, LPVOID* lpvInterface);

	// �t�H�[�}�b�g�Ǝ��̊g�������擾����
	VCOM_CLASSMETHOD
		NVRESULT GetInfo(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);

	// �Ȗ��Ȃǂ̃R�����g�����擾����
	VCOM_CLASSMETHOD
		NVRESULT GetComment(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);

	// �f�R�[�h�f�[�^�̃t�H�[�}�b�g���擾����
	VCOM_CLASSMETHOD
		NVRESULT GetPCMWaveFormat(LPPCMWAVEFORMAT lppcmwf);

	// �f�[�^���f�R�[�h���A������󂯎��
	VCOM_CLASSMETHOD
		NVRESULT DecodeToPCMData(LPVOID lpBuffer, LONG lBufferSize, LPLONG lplResultSize);

	// �f�[�^��擪�܂Ŋ����߂�
	VCOM_CLASSMETHOD
		NVRESULT Rewind(void);

	// �t�@�C�����̃_�C�A���O��\��
	VCOM_CLASSMETHOD
		NVRESULT FileInfoDialog(HWND hwnd);

	// �t�@�C���̌��݈ʒu���o�C�g�P�ʂŎ擾
	VCOM_CLASSMETHOD
		NVRESULT GetCurrentPosition(LPQWUNION lpquPosition, DWORD dwFlag);

	// �t�@�C���̌��݈ʒu���o�C�g�P�ʂŐݒ�
	VCOM_CLASSMETHOD
		NVRESULT SetCurrentPosition(QWUNION quPosition, DWORD dwFlag);

	// �Q�Ǝ���(�}�C�N���b�P��)����T���v�����֕ϊ�����
	VCOM_CLASSMETHOD
		NVRESULT ReferenceTimeToSamples(QWUNION quReferenceTime, LPQWUNION lpquSamples);

	// �T���v��������Q�Ǝ���(�}�C�N���b�P��)�֕ϊ�����
	VCOM_CLASSMETHOD
		NVRESULT SamplesToReferenceTime(QWUNION quSamples, LPQWUNION lpquReferenceTime);

	// ���݂̎Q�Ǝ���(�}�C�N���b�P��)���擾
	VCOM_CLASSMETHOD
		NVRESULT GetReferenceTime(LPQWUNION lpquReferenceTime);

	// �}�C�N���b�P�ʂőS�Đ����Ԃ��擾
	VCOM_CLASSMETHOD
		NVRESULT GetTotalTime(LPQWUNION lpquTotalTime);

protected:
	// �C���^�[�t�F�[�X���Q�ƃe�[�u���ɓo�^����
	VCOM_CLASSMETHOD
		NVRESULT AddInterface(DWORD dwFlag);

	// �C���^�[�t�F�[�X���Q�ƃe�[�u������폜����
	VCOM_CLASSMETHOD
		NVRESULT DeleteInterface(void);

	friend INT_PTR CALLBACK NVDSWrap_InfoDialogProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

protected:
	INVAUDIOFILE parent;
	HWND hwndInfo;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �O���[�o���֐�
//

NVRESULT NVDSHOWWRAP_EXPORT NVDSHOWWRAP_API CreateInstance_NVDSWrap(LPIVCOM lpivcom);

#pragma pack(pop)
EXTERN_C_END