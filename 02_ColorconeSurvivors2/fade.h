//*****************************************************
//
// �t�F�[�h����[fade.h]
// Author:�����V����
//
//*****************************************************

#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object2D.h"
#include "manager.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFade
{
public:
	typedef enum
	{//�t�F�[�h�̏��
		FADE_NONE = 0,				//�������Ă��Ȃ����
		FADE_IN,					//�t�F�[�h�C�����
		FADE_OUT,					//�t�F�[�h�A�E�g���
		FADE_MAX
	}FADE;

	CFade();	// �R���X�g���N�^
	~CFade();	// �f�X�g���N�^
	
	static CFade *Create(CScene::MODE modeNext);
	HRESULT Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CScene::MODE modeNext);
	FADE GetState(void);
	static CFade *GetInstance(void) { return m_pFade; }

private:
	//�O���[�o���ϐ��錾
	FADE m_fade;									//�t�F�[�h�̏��
	CScene::MODE m_modeNext;								//���̉��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXCOLOR m_col;	// �F
	static CFade *m_pFade;	// ���g�̃|�C���^
};
#endif
