#include "DxLib.h"
#include "set_60hz.h"
#include "key.h"
#include "mng.h"

/*
�`�`�`�`�`�R���p�C��������@�`�`�`�`�`

���m�@�P�@�܂�����E���܂�
���m�@�Q�@��ɂ���v���W�F�N�g�J���܂�
���m�@�R�@totomi�̃v���p�e�B�J���܂�
���m�@�S�@�����ɂ���@�\���v���p�e�B�@�N���b�N
���m�@�T�@����ɂ���@�\��(C): ���@�A�N�e�B�u(Debug)�@����@���ׂĂ̍\���@�ɕύX
���m�@�U�@�����ɂ���@�\���v���p�e�B��C/C++���S�ʂƐi�݂܂�
���m�@�V�@�E�ɂ���@�ǉ��̃C���N���[�h�f�B���N�g���@�Ɂ@�uDxLib_VC�t�H���_�v�̒��ɂ���u�v���W�F�N�g�ɒǉ����ׂ��t�@�C��_VC�p�v�@�̃p�X�������
���m�@�W�@�����ɂ���@�\���v���p�e�B�������J���S�ʂƐi�݂܂�
���m�@�X�@�E�ɂ���@�ǉ��̃��C�u�����f�B���N�g���@�Ɂ@�������Ɠ����p�X�������
���m�P�O�@�������܂�
���m�P�P�@���𒅂܂��傤

������ˁI�I�R���p�C���ł����I�I�����I�I

�p �ł��Ȃ��񂾂��ǁE�E�E
�`�D�Ăւ؂��

�C�܂���ŉ摜�̎�荞�݂��΃p�X�ł���Ă��܂������ߕ\������Ȃ��摜���������Ă��܂�
�Ăւ؂��

*/

/*
�@�@�@�@�������A���܂���

�@�@�@�@�@�@�@�@(߄t� )
�@�@�@�@�@�@�@�@(|�@y |)


�@�@�@�@���܂��炪�Љ�Ő����Ă����̂ɕK�v�Ȃ̂͂��ꂾ�B

�@�@�@�@�@�@�@�@( ߄t�)�@ ���
�@�@�@�@�@�@�@�@(�_�^�_�^


�@�@�@�@�����J���Ƃ������Ƃ́E�E�E

�@�@�@�@�@���܁@ ( ߄t�)�@�@����
�@�@�@�@�@�@�@�_�^|�@y |�_�^


�@�@�@�@�܂�A�����������Ƃ��B

�@�@�@�@�@�@�@�@(߄t� )
�@�@�@�@�@�@�@�@(|�@y |)

*/

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
	int mode = 0;

	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 16);
	SetBackgroundColor(40, 40, 120);
	SetWindowText("�u�^�T��������݃A�N�V�����Q�[(��)");
	SetOutApplicationLogValidFlag(FALSE);
	if(DxLib_Init() == -1){
		return -1;
	}
	
	SetDrawScreen(DX_SCREEN_BACK);

	// ���C�����[�v
	while(ProcessMessage() == 0 && mode != -1){
		ClearDrawScreen();

		set_60hz();
		key_update();
		mng(&mode);
	
		ScreenFlip();

		 //WaitTimer(60); 
	}

	DxLib_End();
	return 0;
}

/*
	�ϐ�mode�ŃQ�[���̏�Ԃ��Ǘ��Amode�̒l��(-1)�ɂȂ�����Q�[���I��
*/
