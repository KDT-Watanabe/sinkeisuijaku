#include "Game.h"		// Game�N���X�w�b�_


// ------------------------------
//  WinMain
// ------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	// �Q�[���I�u�W�F�N�g����
	Game* game_ptr = Game::GetObject();

	// �Q�Ƃ��쐬
	Game& game = *game_ptr;


	// �Q�[��������
	if (!game.Init()) {
		return -1;				// DxLib�̏������Ɏ��s�����璼���ɏI��
	}

	// �Q�Ƃ��g���ăQ�[�����[�v�N��
	game.GameLoop();

	// �Q�[���I�u�W�F�N�g�j��
	if (game_ptr != nullptr)
	{
		// �I�u�W�F�N�g�̔j��
		delete game_ptr;
		// �|�C���^�[�ϐ��̏�����
		game_ptr = nullptr;
	}


	// ======================================
	//
	//  ����m�F
	// 
	// ======================================

	//
	// �j�������I�u�W�F�N�g���Q�Ƃ��Ă݂�
	//

	//game_ptr->Init();			// �|�C���^�[�͏���������Ă���̂�nullptr�`�F�b�N�Ɋ|����B

	//game.Init();				// �Q�Ƃ͂��̂܂܂Ȃ̂�nullptr�`�F�b�N�Ɋ|����Ȃ��B�i�I�u�W�F�N�g�͂��łɔj������Ă���̂œ���͕s��j



	// �\�t�g�̏I��
	return 0;
}