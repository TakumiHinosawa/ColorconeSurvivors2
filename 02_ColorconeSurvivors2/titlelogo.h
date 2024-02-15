//=========================================================================================
//
//[titlelogo.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _TITLELOGO_H_			//このマクロ定義がされなかったら
#define _TITLELOGO_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "object2D.h"

//*****************************************************************************************
//モードイメージクラス
//*****************************************************************************************
class CTitlelogo : public CObject2D
{
public:
	CTitlelogo();
	~CTitlelogo();

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTitlelogo* Create(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ情報
	CObject2D* m_pTitlelogo;
};
#endif