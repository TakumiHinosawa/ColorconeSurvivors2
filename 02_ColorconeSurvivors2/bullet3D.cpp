//=========================================================================================
//
//[bullet.cpp]
//Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "bullet3D.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "explosion3D.h"
#include "enemyX.h"
#include "score.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define SIZE	(15.0f)		//�T�C�Y

//*****************************************************************************************
//�ÓI�����o�ϐ�������
//*****************************************************************************************
LPDIRECT3DTEXTURE9 CBullet3D::m_pTexture = NULL;

//=========================================================================================
//�e�̃R���X�g���N�^
//=========================================================================================
CBullet3D::CBullet3D()
{//�e�평����

	m_nLife = 50;
}

//=========================================================================================
//�e�̃f�X�g���N�^
//=========================================================================================
CBullet3D::~CBullet3D()
{

}

//=========================================================================================
//�e�̃e�N�X�`���ǂݍ���
//=========================================================================================
HRESULT CBullet3D::Load(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet.png",
		&m_pTexture);

	return S_OK;
}

//=========================================================================================
//�e�̃e�N�X�`���j��
//=========================================================================================
void CBullet3D::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=========================================================================================
//�e�̏���������
//=========================================================================================
HRESULT CBullet3D::Init(void)
{
	//�I�u�W�F�N�g�̏���������
	CObjectBillboard::Init();

	//��ނ̐ݒ�
	SetType(TYPE_BULLET);

	//�T�C�Y�ݒ菈��
	CObjectBillboard::SetSize(SIZE, SIZE);

	return S_OK;
}

//=========================================================================================
//�e�̏I������
//=========================================================================================
void CBullet3D::Uninit(void)
{
	//�I�u�W�F�N�g�̏I������
	CObjectBillboard::Uninit();
}

//=========================================================================================
//�e�̍X�V����
//=========================================================================================
void CBullet3D::Update(void)
{
	//�T�E���h�̎擾
	CSound* pSound = CManager::GetManager()->GetSound();

	//���������炷
	m_nLife--;

	//�ʒu���擾
	D3DXVECTOR3 pos = CObjectBillboard::GetPosition();

	//�ړ��ʎ擾����
	D3DXVECTOR3 move = CObjectBillboard::GetMove();

	//�ړ��ʉ��Z
	pos += move;

	//�ʒu���ݒ菈��
	CObjectBillboard::SetPos(pos);

	//�e�̐ݒ菈��
	CObjectBillboard::SetBullet(pos, move);

	if (CollisionEnemy() == true)
	{
		return;
	}
	else if (CollisionBoss() == true)
	{
		return;
	}
	else if (CollisionSpawner() == true)
	{
		return;
	}
	else
	{
		if (m_nLife <= 0)
		{// 0�ȉ��̎�

			//�����̐���
			CExplosion3D::Create(pos);

			//�I������
			Uninit();
		}
		return;
	}
}

//=========================================================================================
//�e�̕`�揈��
//=========================================================================================
void CBullet3D::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectBillboard::Draw();
}

//=========================================================================================
//�e�̐ݒ菈��
//=========================================================================================
void CBullet3D::SetPosotion(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	//�ʒu���擾
	D3DXVECTOR3 Bulletpos, Bulletmove;

	//�ʒu���擾
	Bulletpos = CObjectBillboard::GetPosition();

	//�ړ��ʎ擾
	Bulletmove = CObjectBillboard::GetRot();

	Bulletpos = pos;
	Bulletmove = move;
	m_nLife = nLife;
}

//=========================================================================================
//�e�̐ݒ菈��
//=========================================================================================
CBullet3D *CBullet3D::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CBullet3D *pBullet;

	//�I�u�W�F�N�g2D�̐���
	pBullet = new CBullet3D;

	if (pBullet != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pBullet->Init();

		//�e�N�X�`���̊��蓖��
		pBullet->BindTexture(m_pTexture);
	}

	//�I�u�W�F�N�g����Ԃ�
	return pBullet;
}

//=========================================================================================
//�e�̓G�̓����蔻��
//=========================================================================================
bool CBullet3D::CollisionEnemy(void)
{
	CObject *pObj;

	//�ʒu���擾
	D3DXVECTOR3 BulletPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//���f���T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//�g�p����Ă���Ƃ�

			if (pObj->GetType() == TYPE_ENEMYX )
			{//�G�̎�

				//�G�̈ʒu�擾
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//���_���W�擾
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (BulletPos.x >= EnemyPos.x + vtxMin.x
					&& BulletPos.x <= EnemyPos.x + vtxMax.x
					&& BulletPos.z >= EnemyPos.z + vtxMin.z
					&& BulletPos.z <= EnemyPos.z + vtxMax.z)
				{//�����蔻��

					//�T�E���h�̐���
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//�����̐���
					CExplosion3D::Create(EnemyPos);

					//�e�̏I������
					Uninit();

					//�q�b�g����
					pObj->Hit();

					//�X�R�A�̏��擾
					CScore *pScore = CGame::GetScore();

					//�X�R�A�̉��Z
					pScore->AddScore(10);

					//���������ꍇ��true��Ԃ�
					return true;
				}
			}
		}
	}

	//�������Ă��Ȃ��Ƃ�false�ɂ�Ԃ�
	return false;
}

//=========================================================================================
//�e�̓G�̓����蔻��
//=========================================================================================
bool CBullet3D::CollisionBoss(void)
{
	CObject* pObj;

	//�ʒu���擾
	D3DXVECTOR3 BulletPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//���f���T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	//�T�E���h���擾
	CSound* pSound = CManager::GetManager()->GetSound();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//�g�p����Ă���Ƃ�

			if (pObj->GetType() == TYPE_BOSS)
			{//�G�̎�

				//�G�̈ʒu�擾
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//���_���W�擾
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (BulletPos.x >= EnemyPos.x + vtxMin.x
					&& BulletPos.x <= EnemyPos.x + vtxMax.x
					&& BulletPos.z >= EnemyPos.z + vtxMin.z
					&& BulletPos.z <= EnemyPos.z + vtxMax.z)
				{//�����蔻��

					//�T�E���h�̐���
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//�����̐���
					CExplosion3D::Create(EnemyPos);

					//�e�̏I������
					Uninit();

					//�q�b�g����
					pObj->Hit();

					//�X�R�A�̏��擾
					CScore* pScore = CGame::GetScore();

					//�X�R�A�̉��Z
					pScore->AddScore(10);

					//���������ꍇ��true��Ԃ�
					return true;
				}
			}
		}
	}

	//�������Ă��Ȃ��Ƃ�false�ɂ�Ԃ�
	return false;
}

//=========================================================================================
//�e�̓G�̓����蔻��
//=========================================================================================
bool CBullet3D::CollisionSpawner(void)
{
	CObject* pObj;

	//�ʒu���擾
	D3DXVECTOR3 BulletPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//���f���T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	//�T�E���h���擾
	CSound* pSound = CManager::GetManager()->GetSound();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//�g�p����Ă���Ƃ�

			if (pObj->GetType() == TYPE_SPAWNER)
			{//�G�̎�

				//�G�̈ʒu�擾
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//���_���W�擾
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (BulletPos.x >= EnemyPos.x + vtxMin.x
					&& BulletPos.x <= EnemyPos.x + vtxMax.x
					&& BulletPos.z >= EnemyPos.z + vtxMin.z
					&& BulletPos.z <= EnemyPos.z + vtxMax.z)
				{//�����蔻��

					//�T�E���h�̐���
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//�����̐���
					CExplosion3D::Create(EnemyPos);

					//�e�̏I������
					Uninit();

					//�q�b�g����
					pObj->Hit();

					//�X�R�A�̏��擾
					CScore* pScore = CGame::GetScore();

					//�X�R�A�̉��Z
					pScore->AddScore(10);

					//���������ꍇ��true��Ԃ�
					return true;
				}
			}
		}
	}
	//�������Ă��Ȃ��Ƃ�false�ɂ�Ԃ�
	return false;
}