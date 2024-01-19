//=========================================================================================
//
//�X�R�A�\������[score.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _SCORE_H_	//���̒�`������Ă��Ȃ�������
#define _SCORE_H_	//��d�C���N���[�h�h�~�̃}�N����`������

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include"main.h"

//*****************************************************************************************
//�O���錾
//*****************************************************************************************
class CNumber;

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define NUM_PLACE		(5)		//�X�R�A�̌���

//*****************************************************************************************
//�N���X��`
//*****************************************************************************************
class CScore
{
public:
	CScore();
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore *Create(void);

	void SetScore(void);
	void SetScoreRanking(int nNum);
	void AddScore(int nValue);
	void SubScore(int nValue);
	int GetScore(void);
	void SaveScore(void);
	void LoadScore(void);
	void SetPosition(D3DXVECTOR3 pos);

private:
	int m_nScore;						//�X�R�A
	int m_nValue;						//�X�R�A�̑���
	int m_nCtr;							//�J�E���^�[
	D3DXVECTOR3 m_pos;					//�ʒu���
	CNumber *m_apNumber[NUM_PLACE];		//�������
	int m_Dist;
};

#endif
