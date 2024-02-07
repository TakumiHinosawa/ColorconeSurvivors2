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

//=========================================================================================
//�{�X�̃R���X�g���N�^	
//=========================================================================================
CBoss::CBoss()
{
	m_nLife = 100;
	m_nSpawnCtr = 0;
	m_pos = {};
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
	D3DXVECTOR3 BossPos = CObjectX::GetPosition();
	BossPos = D3DXVECTOR3(0.0f,-200.0f,300.0f);
	m_pos = BossPos;

	D3DXVECTOR3 BossMove = CObjectX::GetMove();
	BossMove = D3DXVECTOR3(0.0f, 0.0f, 300.0f);

	float fRandX, fRandZ;
	fRandX = (float)(rand() % 801) - 400.0f;
	fRandZ = (float)(rand() % 801) - 400.0f;

	// �����_���Ȉʒu�Ɉړ�����
	float randomX = static_cast<float>(rand() % 801) - 400.0f;
	float randomZ = static_cast<float>(rand() % 801) - 400.0f;

	D3DXVECTOR3 targetPosition(randomX, 0.0f, randomZ);

	//�ړ�������
	MoveToPosition(targetPosition);

	//�ړ��ݒ�
	SetMove(m_pos);

	//�ʒu�X�V
	SetPosition(BossPos);

	if (m_nCtr >= 380 && m_nSpawnCtr < NUM_SPAWNER)
	{
		CSpawner* pSpawner = CSpawner::Create(D3DXVECTOR3(fRandX,-190.0f, fRandZ));

		m_nCtr = 0;
		m_nSpawnCtr++;
	}

	//�f�o�b�O�\��
	pDebug->Print("[�{�X] ( X:%f Y:%f Z:%f )\n\n", pos.x, pos.y, pos.z);
	pDebug->Print("[�{�X �̗�] ( %d )\n\n",m_nLife);
}

//=========================================================================================
//�{�X�̈ړ�
//=========================================================================================
void CBoss::MoveToPosition(const D3DXVECTOR3& targetPosition)
{
	// �������ƈړ����鏈��
	float distance = D3DXVec3Length(&(targetPosition - m_pos));
	float t = distance / 2.0f;

	// �ړ���܂ł̈ʒu���������ƍX�V
	m_pos += (targetPosition - m_pos) / t;
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

	if (m_nLife <= 0)
	{
		Uninit();
	}
}