//=========================================================================================
//
// �G�l�~�[X [enemyX.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _ENEMYX_H_			//���̃}�N����`������Ȃ�������
#define _ENEMYX_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//�I�u�W�F�N�gX�N���X
//*****************************************************************************************
class CEnemyX : public CObjectX
{
public:
	CEnemyX();
	~CEnemyX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	static int GetKillCount(void);
	static void SetKillCount(int nNum);
	static CEnemyX *Create(void);

private:
	static int m_Count;
};

#endif


