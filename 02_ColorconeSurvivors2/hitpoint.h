//=========================================================================================
//
//�@�q�b�g�|�C���g[hitpoint.h]
//�@Author:�����V����
//
//=========================================================================================
#ifndef _HITPOINT_H_			//���̃}�N����`������Ȃ�������
#define _HITPOINT_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "object2D.h"

//*****************************************************************************************
//�q�b�g�|�C���g�N���X
//*****************************************************************************************
class CHitpoint : public CObject2D
{
public:
	CHitpoint();
	~CHitpoint();

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CHitpoint* Create(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif

