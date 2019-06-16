////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NVDShow ���b�p�[
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
	//  �f�t�H���g�R���X�g���N�^
	//
	//  SetCoreData() ���Ăяo���āA��{�N���X�Ƀf�[�^��ݒ肷��B

	VCOM_CLASSMETHOD
		~Class_NVDSWrap(void);
	//  �f�X�g���N�^
	//

	VCOM_CLASSMETHOD
		NVRESULT Create(LPCVOID lpvParam);
	//  �C���X�^���X�̏�����
	//
	//  �C���X�^���X�Ƀp�����[�^��^���āA�C���X�^���X�̃f�[�^��������(�쐬)����B
	//  vcd.bIsCreated �t���O�𗧂āA�������ς݂��`�F�b�N���s����悤�ɂ���B

	VCOM_CLASSMETHOD
		NVRESULT ResetData(void);
	//  �C���X�^���X�̃f�[�^�����Z�b�g
	//
	//  �C���X�^���X���ŗ��p�����������Ȃǂ�������ACreate() �Ăяo���O�̏�Ԃɖ߂��B
	//  vcd.bIsCreated �t���O�����Z�b�g���A�Ă� Create() ���s����悤�ɂ���B

	VCOM_CLASSMETHOD
		NVRESULT QueryInterface(DWORD dwFourCC, LPVOID* lpvInterface);
	//  �C���^�[�t�F�[�X�̎擾
	//
	//  DWORD dwFourCC			�擾�������C���^�[�t�F�[�X
	//  LPVOID *lpvInterface	�C���^�[�t�F�[�X���i�[����|�C���^
	//
	//  ���̃C���X�^���X�́AdwFourCC �Ŏw�肵���^�̃C���^�[�t�F�[�X���擾����B
	//  �擾�ł���C���^�[�t�F�[�X�́A�C���X�^���X�ɂ���ĈقȂ邪�A
	//  �C���X�^���X�N���X�̃X�[�p�[�N���X�ɂ�����N���X�̃C���^�[�t�F�[�X��
	//  �K���擾�ł���悤�Ɏ������Ȃ���΂Ȃ�Ȃ��B
	//  ���̊֐��ŕʂ̃C���^�[�t�F�[�X���擾����ƁA������ AddRef() ���s����̂ŁA
	//  �Â��C���^�[�t�F�[�X�ɑ΂��Ă�������� Release() ����K�v������B

	VCOM_CLASSMETHOD
		NVRESULT GetInfo(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);
	//  �t�H�[�}�b�g�Ǝ��̊g�������擾����
	//
	//  DWORD dwFourCC			���̌`���������N���X���ʎq
	//  LPVOID�@lpvInfo			�����󂯎��o�b�t�@
	//  LPDWORD�@lpdwSize		�o�b�t�@�̃T�C�Y
	//
	//  �t�H�[�}�b�g���Ƃɒ�߂�ꂽ�g������Ԃ��B
	//  lpvInfo �� NULL ��n���ƁA�K�v�ȃo�b�t�@�T�C�Y���Ԃ����B
	//  ��񂪎擾�����ƁAlpdwSize �Ɏ��ۂɊi�[���ꂽ�T�C�Y���Ԃ�B
	//  �o�b�t�@�T�C�Y������Ȃ��ꍇ�A�G���[���Ԃ�A���̂Ƃ� lpdwSize �ɕK�v�ȃT�C�Y���Ԃ����B
	//  NVAudioFile�C���^�[�t�F�[�X�W���̏��Ƃ��āA
	//  NVAudioFileInfo�`��������̂ŁA����ɂ͕K���Ή�����悤�ɂ���B

	VCOM_CLASSMETHOD
		NVRESULT GetComment(DWORD dwFourCC, LPVOID lpvInfo, LPDWORD lpdwSize);
	//  �Ȗ��Ȃǂ̃R�����g�����擾����
	//
	//  DWORD dwFourCC		�����󂯎��\���̂̎��ʎq
	//  LPVOID lpvInfo		�����󂯎��o�b�t�@(�\����)�̃|�C���^
	//  LPDWORD lpdwSize	�o�b�t�@�̃T�C�Y
	//
	//  lpvInfo �� NULL ��n���ƁA�K�v�ȃo�b�t�@�T�C�Y���Ԃ����B
	//  ��񂪎擾�����ƁAlpdwSize �Ɏ��ۂɊi�[���ꂽ�T�C�Y���Ԃ�B
	//  �o�b�t�@�T�C�Y������Ȃ��ꍇ�A�G���[���Ԃ�A���̂Ƃ� lpdwSize �ɕK�v�ȃT�C�Y���Ԃ����B
	//  �W���̌`���Ƃ��āANVAudioFileComment�`��������̂ŁA
	//  ����ɂ͕K���Ή�����悤�ɂ���B

	VCOM_CLASSMETHOD
		NVRESULT GetPCMWaveFormat(LPPCMWAVEFORMAT lppcmwf);
	//  �f�R�[�h�f�[�^�̃t�H�[�}�b�g���擾����
	//
	//  LPPCMWAVEFORMAT lppcmwf		�����󂯎��o�b�t�@
	//
	//  PCMWAVEFORMAT �`���ŁA�f�R�[�h����Ă���f�[�^�̌`�����擾����B
	//  PCMWAVEFORMAT::wf.wFormatTag�́AWAVE_FORMAT_PCM�܂���WAVE_FORMAT_IEEE_FLOAT�݂̂��T�|�[�g

	VCOM_CLASSMETHOD
		NVRESULT DecodeToPCMData(LPVOID lpBuffer, LONG lBufferSize, LPLONG lplResultSize);
	//  �f�[�^���f�R�[�h���A������󂯎��
	//
	//  LPVOID lpBuffer			�f�R�[�h���ꂽ�f�[�^���󂯎��o�b�t�@
	//  LONG lBufferSize		�擾�������f�[�^�̗�
	//  LPLONG lplResultSize	���ۂɎ擾���ꂽ�f�[�^�̗�
	//
	//  �f�[�^���f�R�[�h���āAPCM �`���Ŏ󂯎��B���̃t�H�[�}�b�g�́AGetPCMWaveFormat �Ŏ擾�ł���t�H�[�}�b�g�Ɋ�Â��Ă���B
	//  NV_OK ���Ԃ����ꍇ�́A�K���v�������T�C�Y�̃f�[�^���擾����Ă���B
	//  VAFERR_VALUE_ENDOFDATA �̏ꍇ�A���ۂɎ擾���ꂽ�f�[�^�̗ʂ́AlplResultSize �ɕԂ����B
	//  ����̌Ăяo���́A�K��VAFERR_VALUE_ENDOFDATA �ɂȂ�B
	//  �f�[�^���ɃG���[�����������̂́A�񕜂ł����ꍇ�ɂ́AVAFERR_VALUE_ERRORRECOVERED���Ԃ�B
	//	���̏ꍇ�́A�f�R�[�h�͂��̂܂ܑ��s�ł���B
	//  ����ȊO�̃G���[���Ԃ����ꍇ�́A�f�R�[�h�𑱂��邱�Ƃ͂ł��Ȃ��B
	//  �f�[�^�̈ꕔ�ł�����ɏ������ꂽ�ꍇ�́AlplResultSize �Ɏ��ۂɎ擾���ꂽ�f�[�^�̗ʂ��Ԃ��Ă���B

	VCOM_CLASSMETHOD
		NVRESULT Rewind(void);
	//  �f�[�^��擪�܂Ŋ����߂�
	//
	//  ���ʓI�ɂ�SetCurrentPosition(0, NVAUDIOFILE_SEEKBEGIN)�Ɠ��������A
	//  �t�H�[�}�b�g�ɂ���Ă͐擪�ւ̃V�[�N�͍����ɍs���邽�ߕʓr�p��
	//  �p�~���Ă��ǂ����ȁc�c�H

	VCOM_CLASSMETHOD
		NVRESULT FileInfoDialog(HWND hwnd);
	//  �t�@�C�����̃_�C�A���O��\��
	//
	//  HWND hwnd		�e�E�B���h�E�̃n���h��
	//
	//  �t�@�C���̏���R�����g�����������[�h���X�_�C�A���O��\������B
	//  ���ɍ쐬�ς݂̏ꍇ�ɂ́A�Q�d�ɕ\�����Ȃ��悤�ɒ���
	//  �܂��AAddRef() Release()���g���āA
	//  �\�����Ƀf�R�[�_���N���[�Y����Ă����v�Ȃ悤�ɂ��Ă����K�v����B
	//  �_�C�A���O�́ANVRegisterDialog()��NVUnRegisterDialog()�ŁA
	//  ���b�Z�[�W���[�v���ł����Ə��������悤�ɂ���K�v����B

	VCOM_CLASSMETHOD
		NVRESULT GetCurrentPosition(LPQWUNION lpquPosition, DWORD dwFlag);
	//  �t�@�C���̌��݈ʒu���o�C�g�P�ʂŎ擾
	//
	//  LPQWUNION lpquPosition	�擾���錻�݈ʒu�̃I�t�Z�b�g
	//  DWORD dwFlag			�I�t�Z�b�g�̊�ʒu

	VCOM_CLASSMETHOD
		NVRESULT SetCurrentPosition(QWUNION quPosition, DWORD dwFlag);
	//  �t�@�C���̌��݈ʒu���o�C�g�P�ʂŐݒ�
	//
	//  QWUNION quPosition	�ݒ肷�錻�݈ʒu�̃I�t�Z�b�g
	//  DWORD dwFlag		�I�t�Z�b�g�̊�ʒu
	//
	//  �\�Ȍ���o�C�g�P�ʂł̃V�[�N���s����悤�ɂ��ׂ������A
	//  ���݂�Lilith�ł́A�����̌덷�������Ă����v�Ȃ���ɂȂ��Ă���B
	//  ���b�p�[�v���O�C���ȂǁA���̃f�R�[�_���T���v���P�ʂ�ms�P�ʂł���
	//  �V�[�N���s���Ȃ����ɂ́A���̒P�ʂɊۂ߂Ă��\��Ȃ��B
	//  �������A���̂��Ƃ�t���h�L�������g���ɖ��L����̂�S�����邱�ƁB

	VCOM_CLASSMETHOD
		NVRESULT ReferenceTimeToSamples(QWUNION quReferenceTime, LPQWUNION lpquSamples);
	//  �Q�Ǝ���(�}�C�N���b�P��)����T���v�����֕ϊ�����
	//
	//  QWUNION quReferenceTime		�Q�Ǝ���(�}�C�N���b�P��)
	//  LPQWUNION lpquSamples		�T���v����
	VCOM_CLASSMETHOD
		NVRESULT SamplesToReferenceTime(QWUNION quSamples, LPQWUNION lpquReferenceTime);
	//  �T���v��������Q�Ǝ���(�}�C�N���b�P��)�֕ϊ�����
	//
	//  QWUNION quSamples			�T���v����
	//  LPQWUNION lpquReferenceTime	�Q�Ǝ���(�}�C�N���b�P��)
	VCOM_CLASSMETHOD
		NVRESULT GetReferenceTime(LPQWUNION lpquReferenceTime);
	//  ���݂̎Q�Ǝ���(�}�C�N���b�P��)���擾
	//
	//  LPQWUNION lpquReferenceTime		�Q�Ǝ���(�}�C�N���b�P��)

	VCOM_CLASSMETHOD
		NVRESULT GetTotalTime(LPQWUNION lpquTotalTime);
	//  �}�C�N���b�P�ʂőS�Đ����Ԃ��擾
	//
	//  LPQWUNION lpquTotalTime		�S�Đ�����(�}�C�N���b�P��)

protected:
	VCOM_CLASSMETHOD
		NVRESULT AddInterface(DWORD dwFlag);
	//  �C���^�[�t�F�[�X���Q�ƃe�[�u���ɓo�^����
	//
	//  DWORD dwFlag	�N���X�C���X�^���X�̏ꍇ�P�A����ȊO�͂O
	//
	//  �R���X�g���N�^�̒��ŌĂ΂�A�C���^�[�t�F�[�X�|�C���^���e�[�u���ɓo�^���A
	//  VIsValidInterface() �ŃC���^�[�t�F�[�X�̗L���������؂ł���悤�ɂ���B

	VCOM_CLASSMETHOD
		NVRESULT DeleteInterface(void);
	//  �C���^�[�t�F�[�X���Q�ƃe�[�u������폜����
	//
	//  DeleteInstance() �̒��ŌĂ΂�A�C���^�[�t�F�[�X�|�C���^���e�[�u������폜����B

	friend INT_PTR CALLBACK NVDSWrap_InfoDialogProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

protected:
	INVAUDIOFILE parent;
	HWND hwndInfo;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ���C�u�����֐��̒�`
//

NVRESULT NVDSHOWWRAP_EXPORT NVDSHOWWRAP_API CreateInstance_NVDSWrap(LPIVCOM lpivcom);

#pragma pack(pop)
EXTERN_C_END