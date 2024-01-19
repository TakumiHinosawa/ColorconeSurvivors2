//=========================================================================================
//
// 3D用 弾 [bullet3D.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _BULLET3D_H_
#define _BULLET3D_H_

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//クラス宣言
//*****************************************************************************************
class CBullet3D : public CObjectBillboard
{
public:
	CBullet3D();
	~CBullet3D();

	static HRESULT Load(void);
	static void Unload(void);
	static CBullet3D *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosotion(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);
	bool CollisionEnemy(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ情報
	int m_nLife;			//弾の寿命
};

#endif
