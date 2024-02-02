//=========================================================================================
//
// エネミーX [enemyX.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _ENEMYX_H_			//このマクロ定義がされなかったら
#define _ENEMYX_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "spawner.h"

//*****************************************************************************************
//オブジェクトXクラス
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


