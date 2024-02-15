//=============================================================================
//
// title
// Author : Hinosawa Takumi
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#include "title.h"
#include "modeimage.h"
#include "input.h"
#include "PlayerX.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "building.h"
#include "sound.h"
#include "fade.h"
#include "titlelogo.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pCamera = nullptr;
	m_pModeImage = nullptr;
	m_pObjectX = nullptr;
	m_pLight = nullptr;
	m_nCtr = 0;
	m_nTrans = 0;
	bUse = false;
	bSound = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	//********************************************************
	//�J�����̐����E������
	//********************************************************
	m_pCamera = new CCamera;

	if (m_pCamera != nullptr)
	{//�g�p����Ă��Ȃ��Ƃ�

		//�J�����̏���������
		m_pCamera->Init();
	}

	//********************************************************
	//���C�g�̐����E������
	//********************************************************
	m_pLight = new CLight;

	if (m_pLight != nullptr)
	{//�g�p����Ă��Ȃ��Ƃ�

		//���C�g�̏���������
		m_pLight->Init();
	}

	//********************************************************
	//�I�u�W�F�N�g������
	//********************************************************
	m_pObjectX = CObjectX::Create("data\\MODEL\\player_00.x");
	m_pObjectX->SetPosition(D3DXVECTOR3(0.0f,70.0f, -200.0f));
	m_pObjectX->SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));

	//********************************************************
	//�e�N�X�`���ǂݍ���
	//********************************************************
	m_pModeImage->Load(0);
	CTitlelogo::Load();

	//�w�i����
	m_pModeImage = CModeImage::Create(0);
	CTitlelogo::Create();

	if (m_pModeImage != nullptr)
	{
		//������
		m_pModeImage = nullptr;
	}
	else
	{
		//����������
		m_pModeImage->Init(0);
	}

	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CTitle::Uninit(void)
{
	bUse = false;

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
	CTitlelogo::Unload();
	
	//********************************************************
	//�J�����̏I������
	//********************************************************
	if (m_pCamera != nullptr)
	{//�g�p����Ă���Ƃ�

		//�J�����̏���������
		m_pCamera->Uninit();
	}

	//********************************************************
	//���C�g�̏I������
	//********************************************************
	if (m_pLight != nullptr)
	{//�g�p����Ă���Ƃ�

		//�J�����̏���������
		m_pLight->Uninit();
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//�R���g���[���[�ւ̃|�C���^�擾
	CInputController* pInputController = CManager::GetManager()->GetInputController();

	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	m_nTrans++;

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && bSound == false ||
		pInputController->GetPress(pInputController->BUTTON_A, 0) == true && bSound == false)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
		bUse = true;
		bSound = true;
	}
	if (bUse == true)
	{
		m_nCtr++;
	}
	if (m_nCtr > 100)
	{
		//��ʑJ��
		CFade::GetInstance()->SetFade(CScene::MODE_GAME);

		m_nCtr = 0;		//�J�E���^�[������
	}

	//********************************************************
	//���C�g�̍X�V����
	//********************************************************
	if (m_pLight != nullptr)
	{//�g�p����Ă���Ƃ�

		//�J�����̏���������
		m_pLight->Update();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	//********************************************************
	//�J�����̐ݒ菈��
	//********************************************************
	if (m_pCamera != nullptr)
	{//�g�p����Ă���Ƃ�

		//�J�����̏���������
		m_pCamera->SetCamera();
	}
}

//=========================================================================================
//��������
//=========================================================================================
CTitle *CTitle::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CTitle *pTitle;

	//����
	pTitle = new CTitle;

	if (pTitle != nullptr)
	{//�g�p����Ă���Ƃ�

		//����������
		pTitle->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pTitle;
}
