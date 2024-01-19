//=========================================================================================
//
//タイマー処理 [time.cpp]
//Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "time.h"
#include "number.h"
#include "object2d.h"
#include "manager.h"

//=========================================================================================
//コンストラクタ
//=========================================================================================
CTime::CTime()
{
	m_nTime = 60;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PLACE_TIME; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
}

//=========================================================================================
//デストラクタ
//=========================================================================================
CTime::~CTime()
{

}

//=========================================================================================
//タイマーの初期化処理
//=========================================================================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE_TIME; nCnt++)
	{
		//オブジェクト生成
		m_apNumber[nCnt] = CNumber::Create();
	}

	return S_OK;
}

//=========================================================================================
//タイマーの終了処理
//=========================================================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE_TIME; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{//使用されているとき

			//オブジェクト終了処理
			m_apNumber[nCnt]->Uninit();

			//オブジェクトを破棄
			delete m_apNumber[nCnt];

			//オブジェクト初期化
			m_apNumber[nCnt] = NULL;
		}
	}
}

//=========================================================================================
//タイマーの更新処理
//=========================================================================================
void CTime::Update(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE_TIME; nCnt++)
	{
		//オブジェクト更新処理
		m_apNumber[nCnt]->Update();
	}

	SetTime();

	if (m_nTime <= 0)
	{// 0以下

		// リザルトへ遷移
		CManager::GetManager()->SetMode(CScene::MODE_RESULT);
	}
}

//=========================================================================================
//タイマーの描画処理
//=========================================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE_TIME; nCnt++)
	{
		//オブジェクト描画処理
		m_apNumber[nCnt]->Draw();
	}
}

//=========================================================================================
//タイマーの設定処理
//=========================================================================================
CTime *CTime::Create(void)
{
	//ポインタの変数を宣言
	CTime *pTime;

	//オブジェクト2Dの生成
	pTime = new CTime;

	if (pTime != NULL)
	{//使用されているとき

		//初期化処理
		pTime->Init();
	}

	//オブジェクト情報を返す
	return pTime;
}

//=========================================================================================
//タイマーの設定処理
//=========================================================================================
void CTime::SetTime(void)
{
	int aTexU[NUM_PLACE_TIME];		//各桁の数値を格納

	aTexU[0] = m_nTime % 1000 / 100;
	aTexU[1] = m_nTime % 100 / 10;
	aTexU[2] = m_nTime % 10;

	for (int nCnt = 0; nCnt < NUM_PLACE_TIME; nCnt++)
	{
		//スコアの設定処理
		m_apNumber[nCnt]->SetScore(D3DXVECTOR3(200.0f, 10.0f, 0.0f), nCnt, aTexU[nCnt]);
	}
}

//=========================================================================================
//タイマーの加算処理
//=========================================================================================
void CTime::AddTime(int nValue)
{
	int aTexU[NUM_PLACE_TIME];		//各桁の数値を格納

	m_nTime -= nValue;

	aTexU[0] = m_nTime % 1000 / 100;
	aTexU[1] = m_nTime % 100 / 10;
	aTexU[2] = m_nTime % 10;
}

//=========================================================================================
//タイマーの取得
//=========================================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

