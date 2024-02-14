//*****************************************************
//
// フェード処理[fade.h]
// Author:日野澤匠泉
//
//*****************************************************

#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "object2D.h"
#include "manager.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CFade
{
public:
	typedef enum
	{//フェードの状態
		FADE_NONE = 0,				//何もしていない状態
		FADE_IN,					//フェードイン状態
		FADE_OUT,					//フェードアウト状態
		FADE_MAX
	}FADE;

	CFade();	// コンストラクタ
	~CFade();	// デストラクタ
	
	static CFade *Create(CScene::MODE modeNext);
	HRESULT Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CScene::MODE modeNext);
	FADE GetState(void);
	static CFade *GetInstance(void) { return m_pFade; }

private:
	//グローバル変数宣言
	FADE m_fade;									//フェードの状態
	CScene::MODE m_modeNext;								//次の画面
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	D3DXCOLOR m_col;	// 色
	static CFade *m_pFade;	// 自身のポインタ
};
#endif
