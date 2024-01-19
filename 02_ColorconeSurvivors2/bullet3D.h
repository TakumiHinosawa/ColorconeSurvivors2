//=========================================================================================
//
// 3D�p �e [bullet3D.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _BULLET3D_H_
#define _BULLET3D_H_

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//�N���X�錾
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
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`�����
	int m_nLife;			//�e�̎���
};

#endif
