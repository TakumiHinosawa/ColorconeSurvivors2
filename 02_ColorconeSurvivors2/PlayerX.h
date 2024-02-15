//=========================================================================================
//
// �v���C���[X [playerX.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _PLAYERX_H_			//���̃}�N����`������Ȃ�������
#define _PLAYERX_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//�I�u�W�F�N�gX�N���X
//*****************************************************************************************
class CPlayerX : public CObjectX
{
public:

	CPlayerX();
	~CPlayerX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Controller(void);
	static CPlayerX *Create(void);
	void CollisionBuilding(void);
	void CollideBoss(void);
	void CollideEnemy(void);
	void Knockback(float knockbackForce, float angle);
	void Pushout(void);

private:
	D3DXVECTOR3 m_OldPos;
	D3DXVECTOR3 m_VtxMax;
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_BuildingPos;
	int m_nTiming;
	int m_nCtr;
};

#endif


