//=========================================================================================
//
// ファストエネミー [fastenemy.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _FASTENEMY_H_			//このマクロ定義がされなかったら
#define _FASTENEMY_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "spawner.h"

//*****************************************************************************************
//オブジェクトXクラス
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


