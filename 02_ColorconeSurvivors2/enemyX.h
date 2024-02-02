//=========================================================================================
//
// �G�l�~�[X [enemyX.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _ENEMYX_H_			//���̃}�N����`������Ȃ�������
#define _ENEMYX_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "spawner.h"

//*****************************************************************************************
//�I�u�W�F�N�gX�N���X
//*****************************************************************************************
class CEnemyX : public CObjectX
{
public:
	CEnemyX();
	~CEnemyX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	static int GetKillCount(void);
	static void SetKillCount(int nNum);
	void CollisionBuilding(void);
	static CEnemyX *Create(void);

private:
	static int m_Count;
	D3DXVECTOR3 m_OldPos;
	D3DXVECTOR3 m_VtxMax;
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_BuildingPos;

	void PushoutCollision(void);
};

#endif


