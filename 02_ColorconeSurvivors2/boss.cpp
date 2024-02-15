//=========================================================================================
//
// �{�X
// Author:�����V����	[boss.cpp]
//
//=========================================================================================
#include "boss.h"
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
#include "fade.h"

//=========================================================================================
//�{�X�̃R���X�g���N�^	
//=========================================================================================
CBoss::CBoss()
{
	m_nLife = 300;
	m_nSpawnCtr = 0;
	m_framesToWait = 0;
	m_currentFrame = 0;
	m_pos = {};
	m_move = {};
	m_targetPos = {};
}

//=========================================================================================
//�{�X�̃f�X�g���N�^
//=========================================================================================
CBoss::~CBoss()
{

}

//=========================================================================================
//�{�X�̏���������
//=========================================================================================
HRESULT CBoss::Init(void)
{
	//�I�u�W�F�N�g�̏���������
	CObjectX::Init("data\\MODEL\\boss_00.x");

	//��ނ̐ݒ�
	SetType(TYPE_BOSS);

	return S_OK;
}

//=========================================================================================
//�{�X�̏I������
//=========================================================================================
void CBoss::Uninit(void)
{
	//�I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//=========================================================================================
//�{�X�̍X�V����
//=========================================================================================
void CBoss::Update(void)
{
	m_nCtr++;

	//�f�o�b�O���擾
	CDebugProc* pDebug = CManager::GetManager()->GetDebugProc();

	//�ʒu���擾����
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//�{�X�̍��W�擾
	m_pos = CObjectX::GetPosition();
	m_pos.y = -200.0f;
	m_move = D3DXVECTOR3(5.0f, 0.0f, 5.0f);

	if (m_framesToWait > 0) 
	{
		// �ړ���̒�ؒ�
		m_framesToWait--;
	}
	else
	{
		// �ړ���
		D3DXVECTOR3 direction = m_targetPos - m_pos;
		D3DXVec3Normalize(&direction, &direction);

		m_pos.x += m_move.x * direction.x;
		m_pos.y += m_move.y * direction.y;
		m_pos.z += m_move.z * direction.z;

		m_currentFrame++;

		if (m_currentFrame >= 60) 
		{
			// ���t���[���ړ�������Ăу����_���Ȉʒu�Ɉړ�
			MoveToRandomPosition();
		}
	}

	CSpawner* pSpawner = nullptr;

	if (m_nCtr >= 400 && pSpawner->GetNumSpawner() < NUM_SPAWNER)
	{
		float fRandX, fRandZ;
		fRandX = (float)(rand() % 801) - 400.0f;
		fRandZ = (float)(rand() % 801) - 400.0f;

		pSpawner = CSpawner::Create(D3DXVECTOR3(fRandX, -190.0f, fRandZ));

		m_nCtr = 0;
		m_nSpawnCtr++;
	}
	if (m_nLife <= 0)
	{
		//��ʑJ��
		CFade::GetInstance()->SetFade(CScene::MODE_GAME);
		return;
	}

	//�ړ��ݒ�
	SetMove(m_move);

	//�ʒu�X�V
	SetPosition(m_pos);

	//�f�o�b�O�\��
	pDebug->Print("\n[�{�X�ʒu] ( X:%f Y:%f Z:%f )\n", pos.x, pos.y, pos.z);
	pDebug->Print("[�{�X�ړ�] ( X:%f Y:%f Z:%f )\n", m_move.x, m_move.y, m_move.z);
	pDebug->Print("[�{�X �̗�] ( %d )\n\n",m_nLife);
}

//=========================================================================================
//�{�X�̈ړ�
//=========================================================================================
void CBoss::MoveToPosition(const D3DXVECTOR3& targetPosition)
{
	m_targetPos = targetPosition;
	m_targetPos.y = -200.0f;
	m_framesToWait = 0; // �ړ���Ɉ��t���[����؂�����
	m_currentFrame = 0;
}

//=========================================================================================
//�{�X�̃����_���Ȉʒu�Ɉړ�
//=========================================================================================
void CBoss::MoveToRandomPosition()
{
	// �����_���Ȉʒu�Ɉړ�����
	float randomX = static_cast<float>(rand() % 801) - 400.0f;
	float randomZ = static_cast<float>(rand() % 801) - 400.0f;

	D3DXVECTOR3 targetPosition(randomX, -200.0f, randomZ);

	// �ړ�������
	MoveToPosition(targetPosition);
}

//=========================================================================================
//�{�X�̕`�揈��
//=========================================================================================
void CBoss::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//=========================================================================================
//�{�X�̐�������
//=========================================================================================
CBoss* CBoss::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CBoss* pBoss;

	//�I�u�W�F�N�g3D�̐���
	pBoss = new CBoss;

	if (pBoss != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pBoss->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pBoss;
}

//=========================================================================================
//�{�X�̃q�b�g����
//=========================================================================================
void CBoss::Hit(void)
{
	m_nLife--;

	CParticle::Create(GetPosition(), 0);
}

//=========================================================================================
//HP�擾����
//=========================================================================================
int CBoss::GetLife(void)
{
	return m_nLife;
}

//=========================================================================================
//HP���Z����
//=========================================================================================
void CBoss::SumLife(int nNum)
{
	m_nLife -= nNum;
}