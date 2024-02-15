//=========================================================================================
//
//[titlelogo.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _TITLELOGO_H_			//���̃}�N����`������Ȃ�������
#define _TITLELOGO_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "object2D.h"

//*****************************************************************************************
//���[�h�C���[�W�N���X
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
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`�����
	CObject2D* m_pTitlelogo;
};
#endif