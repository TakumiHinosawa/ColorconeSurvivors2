//=========================================================================================
//
// �G�t�F�N�g����[effect.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//�G�t�F�N�g
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

