//=========================================================================================
//
// [modeimage.cpp]
// Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
// �C���N���[�h
//*****************************************************************************************
#include "modeimage.h"
#include "renderer.h"
#include "manager.h"
#include "object2D.h"
#include "input.h"
#include "sound.h"
#include "object.h"

//*****************************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************************
LPDIRECT3DTEXTURE9 CModeImage::m_pTexture = NULL;

//=========================================================================================
// ���[�h�C���[�W�̃R���X�g���N�^
//=========================================================================================
CModeImage::CModeImage()
{
	m_pModeImage = NULL;
}

//=========================================================================================
// ���[�h�C���[�W�̃f�X�g���N�^
//=========================================================================================
CModeImage::~CModeImage()
{

}

//=========================================================================================
// ���[�h�C���[�W�̃e�N�X�`���ǂݍ���
//=========================================================================================
HRESULT CModeImage::Load(int nType)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	switch (nType)
	{
	case 0:
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\title.png",
			&m_pTexture);
		break;

	case 1:
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\ranking.png",
			&m_pTexture);
		break;

	case 2:
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\tutorial.png",
			&m_pTexture);
		break;

	case 3:
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\tutorial.png",
			&m_pTexture);
		break;
	}
	return S_OK;
}

//=========================================================================================
// ���[�h�C���[�W�̃e�N�X�`���j��
//=========================================================================================
void CModeImage::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=========================================================================================
// ���[�h�C���[�W�̏���������
//=========================================================================================
HRESULT CModeImage::Init(int nType)
{
	if (m_pModeImage == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//����
		m_pModeImage = new CObject2D;
	}

	if (m_pModeImage != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		m_pModeImage->Init();

		//�e�N�X�`���̊��蓖��
		m_pModeImage->BindTexture(m_pTexture);
	}

	switch (nType)
	{
	case 0:
		//��ނ̐ݒ�
		SetType(TYPE_TITLE);
		break;

	case 1:
		//��ނ̐ݒ�
		SetType(TYPE_RANKING);
		break;

	case 2:
		//��ނ̐ݒ�
		SetType(TYPE_TUTORIAL);
		break;

	case 3:
		//��ނ̐ݒ�
		SetType(TYPE_RESULT);
		break;
	}

	//�摜�ݒ�
	m_pModeImage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 360.0f, 650.0f);

	return S_OK;
}

//=========================================================================================
// ���[�h�C���[�W�̏I������
//=========================================================================================
void CModeImage::Uninit(void)
{
	//�J��
	Release();
}

//=========================================================================================
// ���[�h�C���[�W�̍X�V����
//=========================================================================================
void CModeImage::Update(void)
{
	m_pModeImage->GetMove();
}

//=========================================================================================
// ���[�h�C���[�W�̕`�揈��
//=========================================================================================
void CModeImage::Draw(void)
{
	//�`�揈��
	m_pModeImage->Draw();
}

//=========================================================================================
// ���[�h�C���[�W�̐ݒ菈��
//=========================================================================================
CModeImage *CModeImage::Create(int nType)
{
	//�|�C���^�̕ϐ���錾
	CModeImage *pModeImage = NULL;

	//�I�u�W�F�N�g2D�̐���
	pModeImage = new CModeImage;

	if (pModeImage != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pModeImage->Init(nType);

		//�e�N�X�`���̊��蓖��
		pModeImage->BindTexture(m_pTexture);
	}

	//�I�u�W�F�N�g����Ԃ�
	return pModeImage;
}