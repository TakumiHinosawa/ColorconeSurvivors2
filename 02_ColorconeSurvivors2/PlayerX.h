//=========================================================================================
//
// プレイヤーX [playerX.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _PLAYERX_H_			//このマクロ定義がされなかったら
#define _PLAYERX_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//オブジェクトXクラス
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


