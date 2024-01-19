//=========================================================================================
//
//[number.cpp]
//Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "object2d.h"

//*****************************************************************************************
//�ÓI�����o�ϐ�������
//*****************************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=========================================================================================
//�i���o�[�̃R���X�g���N�^
//=========================================================================================
CNumber::CNumber()
{
	m_pObject2D = NULL;
}

//=========================================================================================
//�i���o�[�̃f�X�g���N�^
//=========================================================================================
CNumber::~CNumber()
{

}

//=========================================================================================
//�i���o�[�̃e�N�X�`���ǂݍ���
//=========================================================================================
HRESULT CNumber::Load(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number2nd.png",
		&m_pTexture);

	return S_OK;
}

//=========================================================================================
//�i���o�[�̃e�N�X�`���j��
//=========================================================================================
void CNumber::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//=========================================================================================
//�i���o�[�̏���������
//=========================================================================================
HRESULT CNumber::Init(void)
{
	//�I�u�W�F�N�g����
	m_pObject2D = CObject2D::Create();

	return S_OK;
}

//=========================================================================================
//�i���o�[�̏I������
//=========================================================================================
void CNumber::Uninit(void)
{
	if (m_pObject2D != NULL)
	{//�g�p����Ă���Ƃ�

		//�g�p����Ă��Ȃ���Ԃɂ���
		m_pObject2D = NULL;
	}
}

//=========================================================================================
//�i���o�[�̍X�V����
//=========================================================================================
void CNumber::Update(void)
{
	////�I�u�W�F�N�g�̍X�V����
	//m_pObject2D->Update();
}

//=========================================================================================
//�i���o�[�̕`�揈��
//=========================================================================================
void CNumber::Draw(void)
{
	////�I�u�W�F�N�g�̕`�揈��
	//m_pObject2D->Draw();
}

//=========================================================================================
//�i���o�[�̐ݒ菈��
//=========================================================================================
CNumber *CNumber::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CNumber *pNumber;

	//�I�u�W�F�N�g2D�̐���
	pNumber = new CNumber;

	if (pNumber != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pNumber->Init();

		//�e�N�X�`���̊��蓖��
		pNumber->m_pObject2D->BindTexture(m_pTexture);
	}

	//�I�u�W�F�N�g����Ԃ�
	return pNumber;
}

//=========================================================================================
//�X�R�A�̐ݒ菈��
//=========================================================================================
void CNumber::SetScore(D3DXVECTOR3 pos,int nCnt,int aTexU)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pObject2D->GetVtx()->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu���X�V
	pVtx[0].pos = D3DXVECTOR3(pos.x - 25.0f + nCnt * 50.0f, pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 25.0f + nCnt * 50.0f, pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 25.0f + nCnt * 50.0f, pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 25.0f + nCnt * 50.0f, pos.y + 50.0f, 0.0f);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU * 0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pObject2D->GetVtx()->Unlock();
}

//=========================================================================================
//�X�R�A�̉��Z����
//=========================================================================================
void CNumber::AddScore(int nCnt, int aTexU)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pObject2D->GetVtx()->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu���X�V
	pVtx[0].pos = D3DXVECTOR3(100.0f + nCnt * 50.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(150.0f + nCnt * 50.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(100.0f + nCnt * 50.0f, 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(150.0f + nCnt * 50.0f, 50.0f, 0.0f);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU * 0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pObject2D->GetVtx()->Unlock();
}