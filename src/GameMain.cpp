#include "WinMain.h"
#include "Base.h"
#include "Hit.h"
#include "Title.h"
#include "ModeSelectScene.h"
#include "EasyPlay.h"
#include "NormalPlay.h"
#include "HardPlay.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Endscene.h"
// =====================================================
//	�O���[�o���ϐ�
//	�����̊֐��ŋ��ʂ��Ďg�������ϐ��͂����ɏ���
// =====================================================

int scene_change = 0;

enum  Scene // �e�V�[��
{
	TITLE_SCENE = 0, // �^�C�g���V�[��
	GAMEMAIN_SCENE,  // �Q�[�����C���V�[��
	END_SCENE,       // �G���h�V�[��

	CLEAN,           // �N���[��
};

// �I�u�W�F�N�g�̐錾
// -------------------------
Base base;             //Base �^�C�g���V�[���̐؂�ւ������邽��
PlayScene playscene;     // �v���C�V�[��
Title title;           // �^�C�g��
EndScene endscene;     // �G���f�B���O�V�[��

// -------------------------
 

// �X�^�[�g��ʂɖ߂邽�߂̕ϐ�
int start_count ;
int count = 10;

// =====================================================
//		������
//	�Q�[���J�n����ɍŏ���1�񂾂����s�����֐�
//	�ŏ��̒l��ϐ��ɓ��ꂽ���Ƃ��Ɏg��
// =====================================================
void GameInit()
{
	title.Init();
	playscene.Init();
	endscene.Init();

}

// =====================================================
//		�X�V
//	�Q�[�����I�������܂Ŏ��s�����֐�
//	1�b�Ԃɖ�60��Ă΂��
//	1�t���[���ōs�������������ɏ���
// =====================================================
void GameUpdate()
{

	switch (scene_change)
	{
	case TITLE_SCENE:
		start_count = 600;
		count = 10;
		title.Update();
		if (title.IsChange()) {
			scene_change = 1;
		}
		break;
	case GAMEMAIN_SCENE:
		playscene.Update();
		if (playscene.IsChange()) {
			scene_change = 2;
		}
		break;
	case END_SCENE:
		endscene.Update();
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			scene_change = 3;
		}
		break;
	case CLEAN:
		start_count--;
		if (start_count % 60 == 0) {
			count--;
		}
		
		if (start_count < 0) {
			GameExit();
			GameInit();
			
			scene_change = 0;
			
		}
		break;
	}
	// 

}
// =====================================================
//		�`��
//	�Q�[�����I�������܂Ŏ��s�����֐�
//	1�b�Ԃɖ�60��Ă΂��
//	GameUpdate�֐������s���ꂽ��Ɏ��s�����֐�
// =====================================================
void GameDraw()
{
	switch (scene_change)
	{
	case TITLE_SCENE:
		title.Draw();
		break;

	case GAMEMAIN_SCENE:
		playscene.Draw();
		break;

	case END_SCENE:
		endscene.Draw();
		DrawString(20, 425, "SKIP >> SPACE", GetColor(255, 255, 255));
		break;
	case CLEAN:
		DrawFormatString(310, 230,  GetColor(255, 255, 255), "START << %d", count);
	default:
		break;
	}


}
// =====================================================
//		�I��
//	�Q�[�����I������O��1�񂾂����s�����֐�
//	�����Ō�Ɍ�Еt�����s���Ƃ��Ɏg��
// =====================================================
void GameExit()
{
	// �e�N���X�̏I������
	title.Exit();
	playscene.Exit();
	endscene.Exit();
}
