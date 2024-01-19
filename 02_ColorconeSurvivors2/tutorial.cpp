//=============================================================================
//
// tutorial
// Author : Hinosawa Takumi
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#include "tutorial.h"
#include "modeimage.h"
#include "input.h"
#include "sound.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_nCtr = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//********************************************************
	//�e�N�X�`���ǂݍ���
	//********************************************************
	m_pModeImage->Load(2);

	//�w�i����
	m_pModeImage = CModeImage::Create(2);

	if (m_pModeImage != nullptr)
	{
		//������
		m_pModeImage = nullptr;
	}
	else
	{
		//����������
		m_pModeImage->Init(2);
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CTutorial::Uninit(void)
{
	if (m_pModeImage != nullptr)
	{
		//�I������
		m_pModeImage->Uninit();

		//������
		m_pModeImage = nullptr;
	}

	//********************************************************
	//�e�N�X�`���j��
	//********************************************************
	m_pModeImage->Unload();
}

//=============================================================================
//�X�V����
//=============================================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h�ւ̃|�C���^�擾
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//��ʑJ��
		CManager::GetManager()->SetMode(CScene::MODE_GAME);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_TRANSITION);
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}

//=========================================================================================
//��������
//=========================================================================================
CTutorial *CTutorial::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CTutorial *pTutorial;

	//����
	pTutorial = new CTutorial;

	if (pTutorial != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pTutorial->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pTutorial;
}