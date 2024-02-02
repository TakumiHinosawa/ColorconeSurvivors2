//=========================================================================================
//
// �v���C���[
// Author:�����V����	[playerX.cpp]
//
//=========================================================================================
#include "main.h"
#include "playerX.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "score.h"
#include "sound.h"
#include "game.h"
#include "bullet3D.h"
#include "explosion3D.h"

//=========================================================================================
//�}�N����`
//=========================================================================================
#define GRAVITY	(0.8f)			//�d��
#define MOVE_PLAYER	(0.8f)		//�ړ���
#define JUMPHEIGHT (16.0f)		//�W�����v��
#define AIRBORNE (20)			//���V����
#define ROTSPEED (0.7f)			//��]���x
#define TIMING	 (6)			//�e���˂̑��x
#define BULLETSPEED	(5.0f)		//�e��
#define HEIGHT		(10.0f)		//����
#define KNOCKBACK	(10.0f)

//=========================================================================================
//�v���C���[�̃R���X�g���N�^	
//=========================================================================================
CPlayerX::CPlayerX()
{
	m_VtxMax = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BuildingPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================================================================
//�v���C���[�̃f�X�g���N�^
//=========================================================================================
CPlayerX::~CPlayerX()
{

}

//=========================================================================================
//�v���C���[�̏���������
//=========================================================================================
HRESULT CPlayerX::Init(void)
{
	//�I�u�W�F�N�g�̏���������
	CObjectX::Init("data\\MODEL\\player_00.x");

	//��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	D3DXVECTOR3 pos = { 0.0f,0.0f,-200.0f };
	CObjectX::SetPosition(pos);

	return S_OK;
}

//=========================================================================================
//�v���C���[�̏I������
//=========================================================================================
void CPlayerX::Uninit(void)
{
	//�I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//=========================================================================================
//�v���C���[�̍X�V����
//=========================================================================================
void CPlayerX::Update(void)
{
	//�v���C���[���쏈��
	Controller(); 
}

//=========================================================================================
//�v���C���[�̕`�揈��
//=========================================================================================
void CPlayerX::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//=========================================================================================
//�v���C���[�̃R���g���[���[
//=========================================================================================
void CPlayerX::Controller(void)
{
	//�f�o�b�O���擾
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	//�J�������擾
	D3DXVECTOR3 RotCamera = CCamera::GetRotCamera();

	//�L�[�{�[�h�ւ̃|�C���^�擾
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//�R���g���[���[�ւ̃|�C���^�擾
	CInputController *pInputController = CManager::GetManager()->GetInputController();

	//�J�������擾
	D3DXVECTOR3 CameraRot = CCamera::GetRotCamera();

	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	//�����擾����
	D3DXVECTOR3 rot = CObjectX::GetRot();
	D3DXVECTOR3 move = CObjectX::GetMove();
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//���݂̈ʒu��ۑ�
	m_OldPos = pos;

	//�J�������擾
	float fRotMove = rot.y;		//���݂̌���
	float fRotDest = rot.y;		//�s����������
	float fRotDiff = fRotDest - fRotMove;	//�ړI�̕���
	bool bUse = false;
	
	//*********************************************************************
	//�@�ړ�
	//*********************************************************************
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputController->GetJoyStickLX(0) < 0)
	{//���������ꂽ�Ƃ�
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputController->GetJoyStickLY(0) > 0)
		{//��
			move.x += sinf(CameraRot.y - (D3DX_PI * 0.25f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (D3DX_PI * 0.25f)) * MOVE_PLAYER;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputController->GetJoyStickLY(0) < 0)
		{//��
			move.x += sinf(CameraRot.y - (D3DX_PI * 0.75f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (D3DX_PI * 0.75f)) * MOVE_PLAYER;
		}
		else
		{//��
			move.x += sinf(CameraRot.y - (D3DX_PI * 0.5f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (D3DX_PI * 0.5f)) * MOVE_PLAYER;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputController->GetJoyStickLX(0) > 0)
	{//���������ꂽ�Ƃ�
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputController->GetJoyStickLY(0) > 0)
		{//��
			move.x += sinf(CameraRot.y - (-D3DX_PI * 0.25f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (-D3DX_PI * 0.25f)) * MOVE_PLAYER;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputController->GetJoyStickLY(0) < 0)
		{//��
			move.x += sinf(CameraRot.y - (-D3DX_PI * 0.75f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (-D3DX_PI * 0.75f)) * MOVE_PLAYER;
		}
		else
		{//��
			move.x += sinf(CameraRot.y - (-D3DX_PI * 0.5f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (-D3DX_PI * 0.5f)) * MOVE_PLAYER;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputController->GetJoyStickLY(0) > 0)
	{//��ړ�
		move.x += sinf(CameraRot.y) * MOVE_PLAYER;
		move.z += cosf(CameraRot.y) * MOVE_PLAYER;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputController->GetJoyStickLY(0) < 0)
	{//���ړ�
		move.x -= sinf(CameraRot.y) * MOVE_PLAYER;
		move.z -= cosf(CameraRot.y) * MOVE_PLAYER;
	}

	//*********************************************************************
	//�@�ˌ�
	//*********************************************************************
	if (pInputKeyboard->GetPress(DIK_LEFT) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRX(0) < 0 && m_nTiming >= TIMING)
	{//���������ꂽ�Ƃ�
		if (pInputKeyboard->GetPress(DIK_UP) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) > 0 && m_nTiming >= TIMING)
		{
			//�e�̐���
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (D3DX_PI * 0.25f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (D3DX_PI * 0.25f)) * BULLETSPEED));

			//�T�E���h�̍Đ�
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//�J�E���^�[������
			m_nTiming = 0;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) < 0 && m_nTiming >= TIMING)
		{
			//�e�̐���
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(D3DXVECTOR3(sinf(CameraRot.y - (D3DX_PI * 0.75f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (D3DX_PI * 0.75f)) * BULLETSPEED)));

			//�T�E���h�̍Đ�
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//�J�E���^�[������
			m_nTiming = 0;
		}
		else
		{
			//�e�̐���
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (D3DX_PI * 0.5f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (D3DX_PI * 0.5f)) * BULLETSPEED));

			//�T�E���h�̍Đ�
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//�J�E���^�[������
			m_nTiming = 0;
		}
	}

	if (pInputKeyboard->GetPress(DIK_RIGHT) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRX(0) > 0 && m_nTiming >= TIMING)
	{//���������ꂽ�Ƃ�
		if (pInputKeyboard->GetPress(DIK_UP) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) > 0 && m_nTiming >= TIMING)
		{
			//�e�̐���
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (-D3DX_PI * 0.25f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (-D3DX_PI * 0.25f)) * BULLETSPEED));

			//�T�E���h�̍Đ�
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//�J�E���^�[������
			m_nTiming = 0;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) < 0 && m_nTiming >= TIMING)
		{
			//�e�̐���
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (-D3DX_PI * 0.75f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (-D3DX_PI * 0.75f)) * BULLETSPEED));

			//�T�E���h�̍Đ�
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//�J�E���^�[������
			m_nTiming = 0;
		}
		else
		{
			//�e�̐���
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (-D3DX_PI * 0.5f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (-D3DX_PI * 0.5f)) * BULLETSPEED));

			//�T�E���h�̍Đ�
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//�J�E���^�[������
			m_nTiming = 0;
		}
	}
	if (pInputKeyboard->GetPress(DIK_UP) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRY(0) > 0 && m_nTiming >= TIMING)
	{
		//�e�̐���
		CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
			D3DXVECTOR3(sinf(CameraRot.y) * BULLETSPEED, 0.0f, cosf(CameraRot.y) * BULLETSPEED));

		//�T�E���h�̍Đ�
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		//�J�E���^�[������
		m_nTiming = 0;
	}
	if (pInputKeyboard->GetPress(DIK_DOWN) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRY(0) < 0 && m_nTiming >= TIMING)
	{
		//�e�̐���
		CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
			D3DXVECTOR3(-sinf(CameraRot.y) * BULLETSPEED, 0.0f, -cosf(CameraRot.y) * BULLETSPEED));

		//�T�E���h�̍Đ�
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		//�J�E���^�[������
		m_nTiming = 0;
	}

	//�e�̃^�C�~���O���Z
	m_nTiming++;

	//�ړ��ʂ��X�V(����������)
	move.x += (0.0f - move.x) * 0.12f;
	move.z += (0.0f - move.z) * 0.12f;

	//�p�x�Z�o
	fRotDiff = fRotDest - fRotMove;		//�ڕW�̈ړ������܂ł̍���

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

	rot.y += fRotDiff * 0.1f;

	//�ړ������̕␳
	if (rot.y > D3DX_PI || rot.y < -D3DX_PI)
	{
		if (rot.y > D3DX_PI)
		{
			rot.y += -D3DX_PI * 2;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2;
		}
	}

	//�d��
	move.y -= GRAVITY;

	//�ړ��ʉ��Z
	pos += move;

	//�ʒu���X�V
	SetPosition(pos);

	//�ړ��ʍX�V
	SetMove(move);

	//�����Ƃ̓����蔻�菈��
	CollisionBuilding();

	//�f�o�b�O�\��
	pDebug->Print("\n�d�� : %f\n",move.y);
	pDebug->Print("�v���C���[�̍��W %f  %f  %f\n",pos.x,pos.y,pos.z);
}

//=========================================================================================
//�v���C���[�̐�������
//=========================================================================================
CPlayerX *CPlayerX::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CPlayerX *pPlayerX;

	//�I�u�W�F�N�g3D�̐���
	pPlayerX = new CPlayerX;

	if (pPlayerX != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pPlayerX->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pPlayerX;
}

//=========================================================================================
//�v���C���[�ƌ����̓����蔻��
//=========================================================================================
void CPlayerX::CollisionBuilding(void)
{
	//�f�o�b�O���擾
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	CObject *pObj;

	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPos = GetPosition();

	//�v���C���[�̈ړ����擾
	D3DXVECTOR3 PlayerMove = GetMove();

	//�v���C���[�̃T�C�Y�ۊǗp�ϐ�
	D3DXVECTOR3 vtxMin, vtxMax;

	//�v���C���[�̃T�C�Y�擾
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

				//�G�̈ʒu�擾
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//�����̃T�C�Y���擾
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				// ******************************		�����蔻��		******************************* //

				//------------------------------------------------------------------------
				//	���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= PlayerPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= PlayerPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//���̔���
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > PlayerPos.z + vtxMin.z)
					{
						PlayerPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < PlayerPos.z + vtxMax.z)
					{
						PlayerPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= PlayerPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= PlayerPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < PlayerPos.x + vtxMax.x)
					{
						PlayerPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > PlayerPos.x + vtxMin.x)
					{
						PlayerPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}

				//------------------------------------------------------------------------
				//�c�̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= PlayerPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= PlayerPos.x + vtxMin.x
					&& BuildingPosition.z + BuildingVtxMin.z <= PlayerPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= PlayerPos.z + vtxMin.z)
				{
					if (BuildingPosition.y + BuildingVtxMin.y >= m_OldPos.y + vtxMax.y
						&& BuildingPosition.y + BuildingVtxMin.y < PlayerPos.y + vtxMax.y)
					{//�@���̔���

						//�ʒu�X�V
						PlayerPos.y = BuildingPosition.y + BuildingVtxMin.y - vtxMax.y;
					}
					if (BuildingPosition.y + BuildingVtxMax.y <= m_OldPos.y + vtxMin.y
						&& BuildingPosition.y + BuildingVtxMax.y > PlayerPos.y + vtxMin.y)
					{//�@��̔���
						
						//�ʒu�X�V
						PlayerPos.y = BuildingPosition.y + BuildingVtxMax.y - vtxMin.y + 0.001f;

						//�d�͏�����
						PlayerMove.y = 0.0f;

						pDebug->Print("\n����Ă��锻�� \n\n");
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
	SetPosition(PlayerPos);

	//�ړ����X�V
	SetMove(PlayerMove);

	CollideBoss();
	CollideEnemy();

	//�f�o�b�O�\��
	pDebug->Print("[�����@���W] ( X:%f Y:%f Z:%f )\n", m_BuildingPos.x, m_BuildingPos.y, m_BuildingPos.z);
	pDebug->Print("[�����@�ő�T�C�Y] ( X:%f Y:%f Z:%f )\n", m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);
	pDebug->Print("[�����@�ŏ��T�C�Y] ( X:%f Y:%f Z:%f )\n\n", m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
	pDebug->Print("[�v���C���[�@���W] ( X:%f Y:%f Z:%f )\n", PlayerPos.x, PlayerPos.y, PlayerPos.z);
	pDebug->Print("[�v���C���[ ���݂̍��W] ( X:%f Y:%f Z:%f )\n\n", m_OldPos.x, m_OldPos.y, m_OldPos.z);
}

//=========================================================================================
//�v���C���[�ƃ{�X�̓����蔻��
//=========================================================================================
void CPlayerX::CollideBoss(void)
{
	CObject* pObj;

	//�T�E���h���擾
	//CSound* pSound = CManager::GetSound();

	//�ʒu���擾
	D3DXVECTOR3 PlayerPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//���f���T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

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

				if (PlayerPos.x >= EnemyPos.x + vtxMin.x
					&& PlayerPos.x <= EnemyPos.x + vtxMax.x
					&& PlayerPos.z >= EnemyPos.z + vtxMin.z
					&& PlayerPos.z <= EnemyPos.z + vtxMax.z)
				{//�����蔻��

					//�����̐���
					CExplosion3D::Create(EnemyPos);

					//�T�E���h�̍Đ�
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//�G�Ɏ���������������
					//pObj->Uninit();

					//�X�R�A�̏��擾
					CScore* pScore = CGame::GetScore();

					//�X�R�A�̉��Z
					pScore->SubScore(100);
				}
			}
		}
	}
}

//=========================================================================================
//�v���C���[�ƓG�̓����蔻��
//=========================================================================================
void CPlayerX::CollideEnemy(void)
{
	CObject* pObj;

	//�T�E���h���擾
	//CSound* pSound = CManager::GetSound();

	//�ʒu���擾
	D3DXVECTOR3 PlayerPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//���f���T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCnt);

		if (pObj != nullptr)
		{//�g�p����Ă���Ƃ�

			if (pObj->GetType() == TYPE_ENEMYX)
			{//�G�̎�

				//�G�̈ʒu�擾
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//���_���W�擾
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (PlayerPos.x >= EnemyPos.x + vtxMin.x
					&& PlayerPos.x <= EnemyPos.x + vtxMax.x
					&& PlayerPos.z >= EnemyPos.z + vtxMin.z
					&& PlayerPos.z <= EnemyPos.z + vtxMax.z)
				{//�����蔻��

					D3DXVECTOR3 rot = pObj->GetRot();

					//�m�b�N�o�b�N
					Knockback(KNOCKBACK, atan2f(GetPosition().x - pObj->GetPosition().x, GetPosition().z - pObj->GetPosition().z));
					
					//�����̐���
					CExplosion3D::Create(EnemyPos);

					//�T�E���h�̍Đ�
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//�G�Ɏ���������������
					pObj->Uninit();

					//�X�R�A�̏��擾
					CScore* pScore = CGame::GetScore();

					//�X�R�A�̉��Z
					pScore->SubScore(100);
				}
			}
		}
	}
}

//=========================================================================================
//�m�b�N�o�b�N����
//=========================================================================================
void CPlayerX::Knockback(float knockbackForce, float angle)
{
	D3DXVECTOR3 Velocity = GetMove();
	D3DXVECTOR3 Pos = GetPosition();

	// �p�x�����W�A���ɕϊ�
	float radians = angle;

	// �m�b�N�o�b�N�̑��x���v�Z
	float knockbackX = knockbackForce * cosf(radians);
	float knockbackZ = knockbackForce * sinf(radians);

	// ���x���X�V���ăm�b�N�o�b�N��K�p
	Velocity.x += knockbackX;
	Velocity.z += knockbackZ;

	Pos += Velocity;
	SetMove(Velocity);
	SetPosition(Pos);
}