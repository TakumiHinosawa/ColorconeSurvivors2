//=========================================================================================
//
// �t�@�X�g�G�l�~�[ [fastenemy.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _FASTENEMY_H_			//���̃}�N����`������Ȃ�������
#define _FASTENEMY_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "spawner.h"

//*****************************************************************************************
//�I�u�W�F�N�gX�N���X
//*****************************************************************************************
class CFastEnemy : public CObjectX
{
public:
	CFastEnemy();
	~CFastEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	static int GetKillCount(void);
	static void SetKillCount(int nNum);
	void CollisionBuilding(void);
	static CFastEnemy* Create(void);
	int GetNumSpawn(void);

private:
	static int m_Count;
	static int m_nNumSpawn;
	int m_nLife;
	D3DXVECTOR3 m_OldPos;
	D3DXVECTOR3 m_VtxMax;
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_BuildingPos;

	void PushoutCollision(void);
};

#endif


