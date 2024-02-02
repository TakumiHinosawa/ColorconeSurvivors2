//=========================================================================================
//
// エフェクト処理[effect.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//エフェクト
//*****************************************************************************************
class CEffect : public CObjectBillboard
{
public:
	CEffect();
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect* Create(void);

private:
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif

