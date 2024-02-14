//*****************************************************
//
// �t�F�[�h����[fade.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define FADE_SPEED			(0.05f)				//�t�F�[�h�̃X�s�[�h

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CFade *CFade::m_pFade = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CFade::CFade()
{
	m_fade = FADE_NONE;
	m_modeNext = CScene::MODE_TITLE;
	m_pVtxBuff = nullptr;
	m_col = { 0.0f,0.0f,0.0f,0.0f };
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CFade::~CFade()
{

}

//=====================================================
// ��������
//=====================================================
CFade *CFade::Create(CScene::MODE modeNext)
{
	if (m_pFade == nullptr)
	{
		m_pFade = new CFade;

		if (m_pFade != nullptr)
		{
			m_pFade->Init(modeNext);
		}
	}

	return m_pFade;
}

//=====================================================
// ����������
//=====================================================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	//���̐ݒ�
	m_fade = FADE_NONE;
	m_col = { 0.0f,0.0f,0.0f,0.0f };

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	if (m_pVtxBuff == nullptr)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL);
	}

	//���_���̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//��ʑJ��
	CManager::GetManager()->SetMode(m_modeNext);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CFade::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C�����
			m_col.a += FADE_SPEED;
			
			if (m_col.a >= 1.0f)
			{//�|���S�������S�ɕs�����ɂȂ�����
				m_col.a = 1.0f;
				m_fade = FADE_OUT;

				//��ʑJ��
				CManager::GetManager()->SetMode(m_modeNext);
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_col.a -= FADE_SPEED;

			if (m_col.a <= 0.0f)
			{//�|���S�������S�ɕs�����ɂȂ�����
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		//���_���̃|�C���^
		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================================
// �ݒ菈��
//=====================================================
void CFade::SetFade(CScene::MODE modeNext)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_IN;
		m_modeNext = modeNext;
		m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
	}
}

//=====================================================
// ���擾����
//=====================================================
CFade::FADE CFade::GetState(void)
{
	return m_fade;
}