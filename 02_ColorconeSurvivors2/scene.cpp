////*****************************************************
////
//// �V�[������[scene.cpp]
//// Author:���R����
////
////*****************************************************
//
////*****************************************************
//// �C���N���[�h
////*****************************************************
//#include "scene.h"
//#include "select.h"
//#include "tutorial.h"
//#include "game.h"
//#include "title.h"
//#include "ranking.h"
//#include "manager.h"
//#include "renderer.h"
//
////=====================================================
//// �R���X�g���N�^
////=====================================================
//CScene::CScene()
//{
//	m_nTimerTrans = 0;
//}
//
////=====================================================
//// �f�X�g���N�^
////=====================================================
//CScene::~CScene()
//{
//
//}
//
////=====================================================
//// ����������
////=====================================================
//HRESULT CScene::Init(void)
//{
//	return S_OK;
//}
//
////=====================================================
//// �I������
////=====================================================
//void CScene::Uninit(void)
//{
//
//}
//
////=====================================================
//// �X�V����
////=====================================================
//void CScene::Update(void)
//{
//	// �����_���[�̎擾
//	CRenderer *pRenderer = CRenderer::GetInstance();
//
//	if (pRenderer != nullptr)
//	{
//		// �����_���[�̍X�V
//		pRenderer->Update();
//	}
//}
//
////=====================================================
//// �`�揈��
////=====================================================
//void CScene::Draw(void)
//{
//
//}
//
////=====================================================
//// �V�[���̐�������
////=====================================================
//CScene *CScene::Create(MODE mode)
//{
//	CScene *pScene = nullptr;
//
//	switch (mode)
//	{
//	case CScene::MODE_TITLE:
//
//		pScene = new CTitle;
//
//		break;
//	case CScene::MODE_SELECT:
//
//		pScene = new CSelect;
//
//		break;
//	case CScene::MODE_TUTORIAL:
//
//		pScene = new CTutorial;
//
//		break;
//	case CScene::MODE_GAME:
//
//		pScene = new CGame;
//
//		break;
//	case CScene::MODE_RANKING:
//
//		pScene = new CRanking;
//
//		break;
//	default:
//
//		pScene = new CGame;
//
//		break;
//	}
//
//	if (pScene != nullptr)
//	{// �V�[������
//		pScene->Init();
//	}
//
//	return pScene;
//}