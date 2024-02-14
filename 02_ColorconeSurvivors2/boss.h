//=========================================================================================
//
// ボス [boss.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _BOSS_H_			//このマクロ定義がされなかったら
#define _BOSS_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//ボスクラス
//*****************************************************************************************
class CBoss : public CObjectX
{
public:
	CBoss();
	~CBoss();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	int GetLife(void);
	void SumLife(int nNum);
	void MoveToRandomPosition();
	static CBoss* Create(void);

private:
	static const int NUM_SPAWNER = 7;

	void MoveToPosition(const D3DXVECTOR3& targetPosition);

	int m_framesToWait;
	int m_currentFrame;
	int m_nLife;
	int m_nCtr;
	int m_nSpawnCtr;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_targetPos;
};

#endif


