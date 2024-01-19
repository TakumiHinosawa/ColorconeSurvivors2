//=========================================================================================
//
// 3D用 爆発 [explosion3D.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _EXPLOSION3D_H_
#define _EXPLOSION3D_H_

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//クラス宣言
//*****************************************************************************************
class CExplosion3D : public CObjectBillboard
{
public:
	CExplosion3D();
	~CExplosion3D();

	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion3D *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosotion(D3DXVECTOR3 pos, D3DXVECTOR3 move);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ情報
	int m_nCounterAnim;			//カウンターアニメーション
	int m_nPatternAnim;			//パターンアニメーション
};

#endif