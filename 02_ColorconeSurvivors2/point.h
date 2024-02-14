//=========================================================================================
//
// �|�C���g����[epoint.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _POINT_H_
#define _POINT_H_

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectbillboard.h"

//*****************************************************************************************
//�|�C���g
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
