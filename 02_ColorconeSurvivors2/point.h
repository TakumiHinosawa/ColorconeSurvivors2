//=========================================================================================
//
// ポイント処理[epoint.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _POINT_H_
#define _POINT_H_

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//ポイント
//*****************************************************************************************
class CPoint : public CObjectBillboard
{
public:
	CPoint();
	~CPoint();

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPoint* Create(D3DXVECTOR3 targetpos);

private:
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
