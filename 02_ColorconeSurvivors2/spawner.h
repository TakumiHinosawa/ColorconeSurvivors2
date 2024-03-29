//=========================================================================================
//
// スポナー [spawner.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _SPAWNER_H_			//このマクロ定義がされなかったら
#define _SPAWNER_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//スポナークラス
//*****************************************************************************************
class CSpawner : public CObjectX
{
public:
	CSpawner();
	~CSpawner();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Spawn(void);

	void Hit(void);
	int GetNumSpawner(void);

	static CSpawner* Create(D3DXVECTOR3 pos);

private:
	int m_nSpwanCtr;
	int m_nLife;
	int m_nSpawnfast;
	int m_nEnemValue;
	static int m_Currentalive;
};

#endif
