//=========================================================================================
//
//[title.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _TITLE_H_			//���̃}�N����`������Ȃ�������
#define _TITLE_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�O���錾
//*****************************************************************************************
class CModeImage;
class CCamera;
class CObjectX;
class CLight;

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "manager.h"

//*****************************************************************************************
//�N���X��`
//*****************************************************************************************
class CTitle : public CScene
{
public:

	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTitle *Create(void);

private:
	CModeImage *m_pModeImage;
	CCamera *m_pCamera;
	CObjectX *m_pObjectX;
	CLight *m_pLight;
	int m_nCtr;
	int m_nTrans;
	bool bUse;
	bool bSound;
};

#endif