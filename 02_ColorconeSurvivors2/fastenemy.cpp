//=========================================================================================
//
// �t�@�X�g�G�l�~�[
// Author:�����V����	[enemyX.cpp]
//
//=========================================================================================
#include "main.h"
#include "fastenemy.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "objectX.h"
#include "playerx.h"
#include "score.h"
#include "time.h"
#include "game.h"
#include "spawner.h"
#include "particle.h"
#include "point.h"

//=========================================================================================
//�}�N����`
//=========================================================================================
#define ENEMY_FASTSPEED (4.0f)

//*****************************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************************
int CFastEnemy::m_Count = 0;
int CFastEnemy::m_nNumSpawn = 0;

//=========================================================================================
//�G�l�~�[�̃R���X�g���N�^	
//=========================================================================================
CFastEnemy::CFastEnemy()
{
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BuildingPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//=========================================================================================
//�G�l�~�[�̃f�X�g���N�^
//=========================================================================================
CFastEnemy::~CFastEnemy()
{

}

//=========================================================================================
//�G�l�~�[�̏���������
//=========================================================================================
HRESULT CFastEnemy::Init(void)
{
	m_nLife = 5;

	//�I�u�W�F�N�g�̏���������
	CObjectX::Init("data\\MODEL\\enemy_01.x");

	//��ނ̐ݒ�
	SetType(TYPE_FASTENEMY);

	return S_OK;
}

//=========================================================================================
//�G�l�~�[�̏I������
//=========================================================================================
void CFastEnemy::Uninit(void)
{
	//�J�E���^�[���Z
	m_Count++;
	m_nNumSpawn--;

	//�I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//=========================================================================================
//�G�l�~�[�̍X�V����
//=========================================================================================
void CFastEnemy::Update(void)
{
	if (m_nLife <= 0) {
		Uninit();
		return;
	}

	//�ʒu���擾����
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//�ϐ��錾
	D3DXVECTOR3 Dest;
	float fRotMove, fRotDest, fRotDiff;

	//�G�l�~�[�ʒu�擾
	D3DXVECTOR3 EnemyPos = CObjectX::GetPosition();
	m_OldPos = EnemyPos;

	//�G�l�~�[�p�x�擾
	D3DXVECTOR3 EnemyRot = CObjectX::GetRot();

	//�G�l�~�[�ړ��ʎ擾
	D3DXVECTOR3 EnemyMove = CObjectX::GetMove();

	//�v���C���[���擾
	CPlayerX* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	Dest = PlayerPos - EnemyPos;			//�ڕW�̌���
	fRotMove = EnemyRot.y;					//���݂̈ړ�����(�p�x)
	fRotDest = atan2f(Dest.x, Dest.z);		//�ڕW�̈ړ�����(�p�x)
	fRotDiff = fRotDest - fRotMove;			//�ڕW�̈ړ������܂ł̍���

	//�ړ������̕␳
	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += -D3DX_PI * 2;
		}
		else if (fRotDiff < -D3DX_PI)
		{
			fRotDiff += D3DX_PI * 2;
		}
	}

	//�ړ�����(�p�x)�̕␳
	EnemyRot.y += fRotDiff * 0.05f;

	//�ړ������̕␳
	if (EnemyRot.y > D3DX_PI || EnemyRot.y < -D3DX_PI)
	{
		if (EnemyRot.y > D3DX_PI)
		{
			EnemyRot.y += -D3DX_PI * 2;
		}
		else if (EnemyRot.y < -D3DX_PI)
		{
			EnemyRot.y += D3DX_PI * 2;
		}
	}

	//�ړ��ʕ␳
	EnemyMove.x = sinf(EnemyRot.y) * ENEMY_FASTSPEED;
	EnemyMove.z = cosf(EnemyRot.y) * ENEMY_FASTSPEED;

	EnemyMove.y -= 2.0f;

	//�ړ��ʉ��Z
	EnemyPos += EnemyMove;

	if (EnemyPos.y <= -800.0f)
	{
		Uninit();
		return;
	}

	//�ʒu�X�V
	SetPosition(EnemyPos);

	//�ړ��ʍX�V
	SetMove(EnemyMove);

	//�����X�V
	SetRot(EnemyRot);

	//�����蔻��
	CollisionBuilding();
	PushoutCollision();
}

//=========================================================================================
//�G�l�~�[�̕`�揈��
//=========================================================================================
void CFastEnemy::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//=========================================================================================
//�G�l�~�[�̐�������
//=========================================================================================
CFastEnemy* CFastEnemy::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CFastEnemy* pEnemyX;

	//�I�u�W�F�N�g3D�̐���
	pEnemyX = new CFastEnemy;

	if (pEnemyX != nullptr)
	{//�g�p����Ă���Ƃ�

		//����������
		pEnemyX->Init();
		m_nNumSpawn++;
	}

	//�I�u�W�F�N�g����Ԃ�
	return pEnemyX;
}

//=========================================================================================
//�G�l�~�[�̃q�b�g����
//=========================================================================================
void CFastEnemy::Hit(void)
{
	m_nLife--;

	//�X�R�A�̏��擾
	CScore* pScore = CGame::GetScore();

	//�X�R�A�̉��Z
	pScore->AddScore(100);

	CParticle::Create(GetPosition(), 0);

	CPoint::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y + 50.0f, GetPosition().z));
}

//=========================================================================================
//�G�l�~�[�̃L����
//=========================================================================================
int CFastEnemy::GetKillCount(void)
{
	return m_Count;
}

//=========================================================================================
//�G�l�~�[�̃L����
//=========================================================================================
void CFastEnemy::SetKillCount(int nNum)
{
	m_Count = nNum;
}

//=========================================================================================
//�v���C���[�ƌ����̓����蔻��
//=========================================================================================
void CFastEnemy::CollisionBuilding(void)
{
	CObject* pObj;

	//�T�E���h���擾
	CSound* pSound = CManager::GetManager()->GetSound();

	//�G�l�~�[�̈ʒu���擾
	D3DXVECTOR3 EnemyPos = GetPosition();

	//�G�l�~�[�̈ړ����擾
	D3DXVECTOR3 EnemyMove = GetMove();

	//�G�l�~�[�̃T�C�Y�ۊǗp�ϐ�
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�G�l�~�[�̃T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//�g�p����Ă���Ƃ�

			if (pObj->GetType() == TYPE_BUILDING)
			{//�����̎�

				//�����̈ʒu�擾
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//�����̃T�C�Y���擾
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				// ******************************		�����蔻��		******************************* //

				//------------------------------------------------------------------------
				//	���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= EnemyPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= EnemyPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//���̔���
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > EnemyPos.z + vtxMin.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < EnemyPos.z + vtxMax.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= EnemyPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= EnemyPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < EnemyPos.x + vtxMax.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > EnemyPos.x + vtxMin.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}

				//------------------------------------------------------------------------
				//�c�̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= EnemyPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= EnemyPos.x + vtxMin.x
					&& BuildingPosition.z + BuildingVtxMin.z <= EnemyPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= EnemyPos.z + vtxMin.z)
				{
					if (BuildingPosition.y + BuildingVtxMin.y >= m_OldPos.y + vtxMax.y
						&& BuildingPosition.y + BuildingVtxMin.y < EnemyPos.y + vtxMax.y)
					{//�@���̔���

						//�ʒu�X�V
						EnemyPos.y = BuildingPosition.y + BuildingVtxMin.y - vtxMax.y;
					}
					if (BuildingPosition.y + BuildingVtxMax.y <= m_OldPos.y + vtxMin.y
						&& BuildingPosition.y + BuildingVtxMax.y > EnemyPos.y + vtxMin.y)
					{//�@��̔���

						//�ʒu�X�V
						EnemyPos.y = BuildingPosition.y + BuildingVtxMax.y - vtxMin.y + 0.001f;

						//�d�͏�����
						EnemyMove.y = 0.0f;
					}
				}
				//���݂̃T�C�Y�̍��W��ۑ�����
				m_VtxMax = BuildingVtxMax;
				m_VtxMin = BuildingVtxMin;

				//�ʒu����ۑ�
				m_BuildingPos = BuildingPosition;
			}
		}
	}

	//�ʒu���X�V
	SetPosition(EnemyPos);

	//�ړ����X�V
	SetMove(EnemyMove);
}

//=========================================================================================
//�G���m�̓����蔻�菈��
//=========================================================================================
void CFastEnemy::PushoutCollision(void)
{
	CObject* pObj;

	//�T�E���h���擾
	CSound* pSound = CManager::GetManager()->GetSound();

	//�G�l�~�[�̈ʒu���擾
	D3DXVECTOR3 EnemyPos = GetPosition();

	//�G�l�~�[�̈ړ����擾
	D3DXVECTOR3 EnemyMove = GetMove();

	//�G�l�~�[�̃T�C�Y�ۊǗp�ϐ�
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�G�l�~�[�̃T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//�g�p����Ă���Ƃ�

			if (pObj->GetType() == TYPE_ENEMYX)
			{//�����̎�

				//�����̈ʒu�擾
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//�����̃T�C�Y���擾
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				//------------------------------------------------------------------------
				//	���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= EnemyPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= EnemyPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//���̔���
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > EnemyPos.z + vtxMin.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < EnemyPos.z + vtxMax.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= EnemyPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= EnemyPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < EnemyPos.x + vtxMax.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > EnemyPos.x + vtxMin.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}

				//���݂̃T�C�Y�̍��W��ۑ�����
				m_VtxMax = BuildingVtxMax;
				m_VtxMin = BuildingVtxMin;

				//�ʒu����ۑ�
				m_BuildingPos = BuildingPosition;
			}
			else if (pObj->GetType() == TYPE_FASTENEMY)
			{//�����̎�

				//�����̈ʒu�擾
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//�����̃T�C�Y���擾
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				//------------------------------------------------------------------------
				//	���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= EnemyPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= EnemyPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//���̔���
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > EnemyPos.z + vtxMin.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < EnemyPos.z + vtxMax.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= EnemyPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= EnemyPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < EnemyPos.x + vtxMax.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > EnemyPos.x + vtxMin.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}
			}
		}
	}

	//�ʒu���X�V
	SetPosition(EnemyPos);

	//�ړ����X�V
	SetMove(EnemyMove);
}

//=========================================================================================
//�G�����擾����
//=========================================================================================
int CFastEnemy::GetNumSpawn(void)
{
	return m_nNumSpawn;
}