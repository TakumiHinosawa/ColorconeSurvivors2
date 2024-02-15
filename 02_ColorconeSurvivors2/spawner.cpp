//=========================================================================================
//
// �X�|�i�[
// Author:�����V����	[spawner.cpp]
//
//=========================================================================================
#include "spawner.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "objectX.h"
#include "playerx.h"
#include "score.h"
#include "time.h"
#include "game.h"
#include "enemyX.h"
#include "effect.h"
#include "particle.h"
#include "boss.h"
#include "fastenemy.h"

//=========================================================================================
//�ÓI�����o�ϐ�
//=========================================================================================
int CSpawner::m_Currentalive = 0;

//=========================================================================================
//�}�N����`
//=========================================================================================
#define ROTATION	(1.2f)		//�ړ���
#define ENEMY_INTERVAL (100)
#define FAST_INTERVAL (400)
#define SPAWNER_LIFE (15)
#define NUM_ENEMY (60)

//=========================================================================================
//�X�|�i�[�̃R���X�g���N�^	
//=========================================================================================
CSpawner::CSpawner()
{
	m_nSpwanCtr = 0;
	m_nLife = SPAWNER_LIFE;
	m_nSpawnfast = 0;
	m_nEnemValue = 0;
}

//=========================================================================================
//�X�|�i�[�̃f�X�g���N�^
//=========================================================================================
CSpawner::~CSpawner()
{

}

//=========================================================================================
//�X�|�i�[�̏���������
//=========================================================================================
HRESULT CSpawner::Init(void)
{
	//�I�u�W�F�N�g�̏���������
	CObjectX::Init("data\\MODEL\\spawner_00.x");

	//��ނ̐ݒ�
	SetType(TYPE_SPAWNER);

	//�ʒu�X�V
	SetPosition(D3DXVECTOR3(0.0f, 500.0f, -200.0f));

	return S_OK;
}

//=========================================================================================
//�X�|�i�[�̏I������
//=========================================================================================
void CSpawner::Uninit(void)
{
	m_Currentalive--;

	//�I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//=========================================================================================
//�X�|�i�[�̍X�V����
//=========================================================================================
void CSpawner::Update(void)
{
	Spawn();

	//�G�l�~�[�p�x�擾
	D3DXVECTOR3 EnemyRot = CObjectX::GetRot();

	// ���t���[���A��]�p�x�𑝉�
	EnemyRot.y += ROTATION * 0.016666f;

	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//�����X�V
	SetRot(EnemyRot);

	//�f�o�b�O���擾
	CDebugProc* pDebug = CManager::GetManager()->GetDebugProc();

	//�f�o�b�O�\��
	pDebug->Print("[�X�|�i�[] ( X:%f Y:%f Z:%f )\n\n", EnemyRot.x, EnemyRot.y, EnemyRot.z);
}

//=========================================================================================
//�X�|�i�[�̕`�揈��
//=========================================================================================
void CSpawner::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//=========================================================================================
//�X�|�i�[�̐�������
//=========================================================================================
CSpawner* CSpawner::Create(D3DXVECTOR3 pos)
{
	m_Currentalive++;

	//�|�C���^�̕ϐ���錾
	CSpawner* pSpawner;

	//�I�u�W�F�N�g3D�̐���
	pSpawner = new CSpawner;

	if (pSpawner != nullptr)
	{//�g�p����Ă���Ƃ�

		//����������
		pSpawner->Init();
		pSpawner->SetPosition(pos);
	}

	//�I�u�W�F�N�g����Ԃ�
	return pSpawner;
}

//=========================================================================================
//�X�|�i�[�̃q�b�g����
//=========================================================================================
void CSpawner::Hit(void)
{
	m_nLife--;

	CParticle::Create(GetPosition(), 0);

	//�X�R�A�̏��擾
	CScore* pScore = CGame::GetScore();

	if (m_nLife <= 0)
	{
		//�I������
		CSpawner::Uninit();

		//�{�X�̗̑͌��Z
		CGame::GetBoss()->SumLife(40);

		//�X�R�A�̉��Z
		pScore->AddScore(1000);
	}
}

//=========================================================================================
//�X�|�[���`�����N�ݒ�
//=========================================================================================
void CSpawner::Spawn(void)
{
	m_nSpwanCtr++;		//�J�E���^�[�̉��Z
	m_nSpawnfast++;
	D3DXVECTOR3 pos = GetPosition();

	CEnemyX* enemy = nullptr;
	CFastEnemy* fastenemy = nullptr;

	//�G�̑���
	m_nEnemValue = enemy->GetNumSpawn() + fastenemy->GetNumSpawn();

	if (m_nEnemValue <= NUM_ENEMY) {
		if (m_nSpwanCtr >= ENEMY_INTERVAL){
			//�G�̐���
			enemy = CEnemyX::Create();
			enemy->SetPosition(pos);

			m_nSpwanCtr = 0;	//�J�E���^�[������
		}
		if (m_nSpawnfast >= FAST_INTERVAL){
			fastenemy = CFastEnemy::Create();
			fastenemy->SetPosition(pos);

			m_nSpawnfast = 0;
		}
	}
	else {
		return;
	}
}

//=========================================================================================
//�X�|�i�[�ݒ�
//=========================================================================================
int CSpawner::GetNumSpawner(void)
{
	return m_Currentalive;
}