#pragma once
#include <ctime>
#include "Dxlib.h"

//	�萔�̐錾
#define WINDOW_W 1280	// ��ʃT�C�Y�@��
#define WINDOW_H 720	// ��ʃT�C�Y�@�c
#define COLOR_DEPTH 32	// �F�[�x

/// <summary>
/// Game�N���X�i�V���O���g���j
///  �Q�[���{�̂̎���
/// </summary>
class Game
{

protected:
	int title_frame = 0;
	int count;
	/// <summary>
	/// �V���O���g���I�u�W�F�N�g�ێ�
	/// </summary>
	static Game* s_self_ptr;

	/// <summary>
	/// �B���R���X�g���N�^�[
	/// </summary>
	Game() {}

	int matched_cnt;
    int trump_BG;
	int bgm_mp=0;
public:
	int mj_bg;
	int click_bg;
	int nGame_mode=0;
	enum Mode {
		GraphInit,
		Title,
		GameNow,
		Result,
		Ending,

	};
	// �}�E�X���W�p�̕ϐ�
	int mouse_x;
	int mouse_y;

	/// <summary>
	/// �I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g</returns>
	static Game* GetObject()
	{
		// �V���O���g���I�u�W�F�N�g�̑��݃`�F�b�N
		if (Game::s_self_ptr == nullptr)
		{
			// �I�u�W�F�N�g�𐶐�
			Game::s_self_ptr = new Game();
		}

		// �V���O���g���I�u�W�F�N�g�����^�[��
		return Game::s_self_ptr;
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Game()
	{
		// =======================================
		//  �I������
		// =======================================
		// DX���C�u�����g�p�̏I������
		DxLib_End();

		// �V���O���g���ێ��ϐ��̃��Z�b�g
		Game::s_self_ptr = nullptr;
		;
	}

	/// <summary>
	/// ���������\�b�h
	/// </summary>
	/// <returns>����</returns>
	bool Init()
	{
		// �I�u�W�F�N�g�`�F�b�N
		if (this == nullptr)
		{
			return false;
		}

		// =======================================
		//  ����������
		// =======================================
		// ���O�̏����o���𖳌���
		SetOutApplicationLogValidFlag(FALSE);	// ���O�̏����o���𖳌���

		// �E�B���h�E���[�h�̐ݒ�
		ChangeWindowMode(TRUE);					// �E�C���h�E���[�h��L����

		// �E�B���h�E�T�C�Y�ƃJ���[�r�b�g�̐ݒ�
		SetGraphMode(WINDOW_W, WINDOW_H, COLOR_DEPTH);

		// �E�B���h�E�̃^�C�g��
		SetMainWindowText("DxLib Template");

		// �w�i�F�̐ݒ�
		SetBackgroundColor(128, 128, 128);

		// �c�w���C�u��������������
		if (DxLib_Init() == -1)
		{
			return false;						// �������Ɏ��s�����ꍇ��false��Ԃ�
		}

		// �E�B���h�E�`�惂�[�h�ݒ�
		SetDrawScreen(DX_SCREEN_BACK);			// ����ʂɕ`�悷��

		return true;


	}
	/// <summary>
	/// Game���[�v���\�b�h
	/// </summary>
	void GameLoop() {

		// �I�u�W�F�N�g�`�F�b�N
		if (this == nullptr)
		{
			return;
		}

		// ------------------------------
		//  �Q�[�����[�v
		// ------------------------------
		while (ProcessMessage() == 0)
		{
			// ���t���b�V�����[�g��ݒ肷�邽�߂̏���
			clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;

			// �}�E�X�J�[�\���\���ݒ�
			SetMouseDispFlag(TRUE);

			// printfDx�̏�����
			clsDx();

			// ��ʏ�̕`����������i��ʂ������j
			ClearDrawScreen();

			//  ���͏���
			this->input();

			//  ��ʕ`�揈��
			this->update();

			//  �`�揈��
			this->render();


			// ���t���b�V�����[�g�����ɂȂ�܂ő҂���
			while (clock() < check_fps) {}

			// ����ʂ̕`���\�ɔ��f
			ScreenFlip();


			// ESC�L�[�Ń��[�v���甲����
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				break;
			}

		}
	}

protected:

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <returns>����</returns>
	int input();


	/// <summary>
	/// ��ʍX�V����
	/// </summary>
	/// <returns>����</returns>
	int update();


	/// <summary>
	/// �����Đ�����
	/// </summary>
	/// <returns>����</returns>
	int render();

};
