//=========================================================================================
//
// �G�l�~�[
// Author:�����V����	[enemyX.cpp]
//
//=========================================================================================
#include "main.h"
#include "enemyX.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "objectX.h"
#include "playerx.h"
#include "score.h"
#include "time.h"
#include "game.h"
#include "spawner.h"

//=========================================================================================
//�}�N����`
//=========================================================================================
#define ENEMYMOVE	(2.0f)		//�ړ���

//*****************************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************************
int CEnemyX::m_Count = 0;

//=========================================================================================
//�G�l�~�[�̃R���X�g���N�^	
//=========================================================================================
CEnemyX::CEnemyX()
{

}

//=========================================================================================
//�G�l�~�[�̃f�X�g���N�^
//=========================================================================================
CEnemyX::~CEnemyX()
{

}

//=========================================================================================
//�G�l�~�[�̏���������
//=========================================================================================
HRESULT CEnemyX::Init(void)
{
	//�I�u�W�F�N�g�̏���������
	CObjectX::Init("data\\MODEL\\enemy_00.x");

	//��ނ̐ݒ�
	SetType(TYPE_ENEMYX);

	return S_OK;
}

//=========================================================================================
//�G�l�~�[�̏I������
//=========================================================================================
void CEnemyX::Uninit(void)
{
	//�I�u�W�F�N�g�̏I������
	CObjectX::Uninit();

	//�J�E���^�[���Z
	m_Count++;
}

//=========================================================================================
//�G�l�~�[�̍X�V����
//=========================================================================================
void CEnemyX::Update(void)
{
	//�f�o�b�O���擾
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	//�ʒu���擾����
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//�ϐ��錾
	D3DXVECTOR3 Dest;
	float fRotMove, fRotDest, fRotDiff;

	//�G�l�~�[�ʒu�擾
	D3DXVECTOR3 EnemyPos = CObjectX::GetPosition();
	EnemyPos.y = 40.0f;

	//�G�l�~�[�p�x�擾
	D3DXVECTOR3 EnemyRot = CObjectX::GetRot();

	//�G�l�~�[�ړ��ʎ擾
	D3DXVECTOR3 EnemyMove = CObjectX::GetMove();

	//�v���C���[���擾
	CPlayerX *pPlayer = CGame::GetPlayer();
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
	EnemyMove.x = sinf(EnemyRot.y) * ENEMYMOVE;
	EnemyMove.z = cosf(EnemyRot.y) * ENEMYMOVE;

	//�ړ��ʉ��Z
	EnemyPos += EnemyMove;

	//�ʒu�X�V
	SetPosition(EnemyPos);

	//�����X�V
	SetRot(EnemyRot);

	//�f�o�b�O�\��
	pDebug->Print("[�G�l�~�[] ( X:%f Y:%f Z:%f )\n\n", pos.x, pos.y, pos.z);
}

//=========================================================================================
//�G�l�~�[�̕`�揈��
//=========================================================================================
void CEnemyX::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//=========================================================================================
//�G�l�~�[�̐�������
//=========================================================================================
CEnemyX *CEnemyX::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CEnemyX *pEnemyX;

	//�I�u�W�F�N�g3D�̐���
	pEnemyX = new CEnemyX;

	if (pEnemyX != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pEnemyX->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pEnemyX;
}

//=========================================================================================
//�G�l�~�[�̃q�b�g����
//=========================================================================================
void CEnemyX::Hit(void)
{
	//�X�R�A�̏��擾
	CScore *pScore = CGame::GetScore();

	//�X�R�A�̉��Z
	pScore->AddScore(100);

	//�I������
	CEnemyX::Uninit();
}

//=========================================================================================
//�G�l�~�[�̃L����
//=========================================================================================
int CEnemyX::GetKillCount(void)
{
	return m_Count;
}

//=========================================================================================
//�G�l�~�[�̃L����
//=========================================================================================
void CEnemyX::SetKillCount(int nNum)
{
	m_Count = nNum;
}