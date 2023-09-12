#include "MyGame.h"
#include "SceneFactory.h"

void MyGame::Initialize()
{
	//���N���X�̏�����
	Framework::Initialize();

	// �^�C�g���摜�ǂݍ���
	if (!Image2d::LoadTexture(Image2d::ImgNumber::title, "title"))
	{
		assert(0);
	}
	// �w�i�摜�ǂݍ���
	if (!Image2d::LoadTexture(Image2d::ImgNumber::back_1, "backGround_1"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::back_2, "backGround_2"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::people, "people"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::hukidasi, "hukidasi"))
	{
		assert(0);
	}
	// ���U���g�摜�ǂݍ���
	if (!Image2d::LoadTexture(Image2d::ImgNumber::result, "result"))
	{
		assert(0);
	}
	// �C���T�[�g�摜�ǂݍ���
	if (!Image2d::LoadTexture(Image2d::ImgNumber::door_right, "door_right"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::door_left, "door_left"))
	{
		assert(0);
	}
	// �`���[�g���A���p�摜�̓ǂݍ���
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouse, "mouse"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouseLeft, "mouse_left"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouseRight, "mouse_right"))
	{
		assert(0);
	}
	// ���i�摜�̓ǂݍ���
	if (!Image2d::LoadTexture(Image2d::ImgNumber::kome_oke, "kome_oke"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::shari, "shari"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::sushi_geta, "sushi_geta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::maguro, "maguro"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::samon, "samon"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ebi, "ebi"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::tamago, "tamago"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ika, "ika"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::maguro_neta, "maguro_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::samon_neta, "samon_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ebi_neta, "ebi_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::tamago_neta, "tamago_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ika_neta, "ika_neta"))
	{
		assert(0);
	}

	// �V�[���t�@�N�g���[�𐶐����A�}�l�[�W���[�ɃZ�b�g
	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);
	SceneManager::GetInstance()->ChangeScene("Title");

	//���ݎ������}�C�N���b�Ŏ擾
	currentTimeMicro = []()
	{
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
	};
	//60fps�œ��삳����
	fps = 60;

	//���ݎ������擾
	end = currentTimeMicro();

	//���̍X�V���Ԃ��v�Z
	next = end + (1000 * 1000 / fps);
}

void MyGame::Finalize()
{
	// ���N���X�̏I��
	Framework::Finalize();
}

void MyGame::Update()
{
	//�ł��邾��60fps�ɂȂ�悤�ɃX���b�h�ҋ@
	end = currentTimeMicro();
	if (end < next)
	{
		//�X�V���Ԃ܂őҋ@
		std::this_thread::sleep_for(std::chrono::microseconds(next - end));
		//���̍X�V���Ԃ��v�Z�i1�b/�t���[�����[�g���Z�j
		next += (1000 * 1000 / fps);
	}
	else
	{
		//�X�V���Ԃ��߂����ꍇ�͌��ݎ������玟�̍X�V���Ԃ��v�Z
		next = end + (1000 * 1000 / fps);
	}

	//���N���X�̃A�b�v�f�[�g
	Framework::Update();
}

void MyGame::Draw()
{
	//���N���X�̃A�b�v�f�[�g
	Framework::Draw();
}
