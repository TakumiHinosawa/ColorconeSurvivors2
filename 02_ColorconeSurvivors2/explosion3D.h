//=========================================================================================
//
// 3D�p ���� [explosion3D.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _EXPLOSION3D_H_
#define _EXPLOSION3D_H_

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//�N���X�錾
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
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`�����
	int m_nCounterAnim;			//�J�E���^�[�A�j���[�V����
	int m_nPatternAnim;			//�p�^�[���A�j���[�V����
};

#endif