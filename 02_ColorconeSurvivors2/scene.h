////*****************************************************
////
//// �V�[������[scene.h]
//// Author:���R����
////
////*****************************************************
//#ifndef _SCENE_H_
//#define _SCENE_H_
//
////*****************************************************
//// �C���N���[�h
////*****************************************************
//#include "main.h"
//
////*****************************************************
//// �O���錾
////*****************************************************
//class CPlayer;
//class CMeshField;
//
////*****************************************************
//// �N���X�̒�`
////*****************************************************
//class CScene
//{
//public:
//	enum MODE
//	{
//		MODE_TITLE = 0,
//		MODE_SELECT,
//		MODE_TUTORIAL,
//		MODE_GAME,
//		MODE_RANKING,
//		MODE_MAX
//	};
//
//	CScene();	// �R���X�g���N�^
//	~CScene();	// �f�X�g���N�^
//
//	virtual HRESULT Init(void);
//	virtual void Uninit(void);
//	virtual void Update();
//	virtual void Draw();
//	static CScene *Create(MODE mode);
//	int GetTimer(void) { return m_nTimerTrans; }
//	void SetTimer(int nTime) { m_nTimerTrans = nTime; }
//
//private:
//	int m_nTimerTrans;	// �J�ڃ^�C�}�[
//};
//
//#endif