//=========================================================================================
//
// スポナー
// Author:日野澤匠泉	[spawner.cpp]
//
//=========================================================================================
#include "spawner.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "objectX.h"
#include "playerx.h"
#include "score.h"
#include "time.h"
#include "game.h"
#include "enemyX.h"
#include "effect.h"
#include "particle.h"
#include "boss.h"
#include "fastenemy.h"

//=========================================================================================
//静的メンバ変数
//=========================================================================================
int CSpawner::m_Currentalive = 0;

//=========================================================================================
//マクロ定義
//=========================================================================================
#define ROTATION	(1.2f)		//移動量
#define ENEMY_INTERVAL (100)
#define FAST_INTERVAL (400)
#define SPAWNER_LIFE (15)
#define NUM_ENEMY (60)

//=========================================================================================
//スポナーのコンストラクタ	
//=========================================================================================
CSpawner::CSpawner()
{
	m_nSpwanCtr = 0;
	m_nLife = SPAWNER_LIFE;
	m_nSpawnfast = 0;
	m_nEnemValue = 0;
}

//=========================================================================================
//スポナーのデストラクタ
//=========================================================================================
CSpawner::~CSpawner()
{

}

//=========================================================================================
//スポナーの初期化処理
//=========================================================================================
HRESULT CSpawner::Init(void)
{
	//オブジェクトの初期化処理
	CObjectX::Init("data\\MODEL\\spawner_00.x");

	//種類の設定
	SetType(TYPE_SPAWNER);

	//位置更新
	SetPosition(D3DXVECTOR3(0.0f, 500.0f, -200.0f));

	return S_OK;
}

//=========================================================================================
//スポナーの終了処理
//=========================================================================================
void CSpawner::Uninit(void)
{
	m_Currentalive--;

	//オブジェクトの終了処理
	CObjectX::Uninit();
}

//=========================================================================================
//スポナーの更新処理
//=========================================================================================
void CSpawner::Update(void)
{
	Spawn();

	//エネミー角度取得
	D3DXVECTOR3 EnemyRot = CObjectX::GetRot();

	// 毎フレーム、回転角度を増加
	EnemyRot.y += ROTATION * 0.016666f;

	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//向き更新
	SetRot(EnemyRot);

	//デバッグ情報取得
	CDebugProc* pDebug = CManager::GetManager()->GetDebugProc();

	//デバッグ表示
	pDebug->Print("[スポナー] ( X:%f Y:%f Z:%f )\n\n", EnemyRot.x, EnemyRot.y, EnemyRot.z);
}

//=========================================================================================
//スポナーの描画処理
//=========================================================================================
void CSpawner::Draw(void)
{
	//オブジェクトの描画処理
	CObjectX::Draw();
}

//=========================================================================================
//スポナーの生成処理
//=========================================================================================
CSpawner* CSpawner::Create(D3DXVECTOR3 pos)
{
	m_Currentalive++;

	//ポインタの変数を宣言
	CSpawner* pSpawner;

	//オブジェクト3Dの生成
	pSpawner = new CSpawner;

	if (pSpawner != nullptr)
	{//使用されているとき

		//初期化処理
		pSpawner->Init();
		pSpawner->SetPosition(pos);
	}

	//オブジェクト情報を返す
	return pSpawner;
}

//=========================================================================================
//スポナーのヒット処理
//=========================================================================================
void CSpawner::Hit(void)
{
	m_nLife--;

	CParticle::Create(GetPosition(), 0);

	//スコアの情報取得
	CScore* pScore = CGame::GetScore();

	if (m_nLife <= 0)
	{
		//終了処理
		CSpawner::Uninit();

		//ボスの体力減算
		CGame::GetBoss()->SumLife(40);

		//スコアの加算
		pScore->AddScore(1000);
	}
}

//=========================================================================================
//スポーンチャンク設定
//=========================================================================================
void CSpawner::Spawn(void)
{
	m_nSpwanCtr++;		//カウンターの加算
	m_nSpawnfast++;
	D3DXVECTOR3 pos = GetPosition();

	CEnemyX* enemy = nullptr;
	CFastEnemy* fastenemy = nullptr;

	//敵の総数
	m_nEnemValue = enemy->GetNumSpawn() + fastenemy->GetNumSpawn();

	if (m_nEnemValue <= NUM_ENEMY) {
		if (m_nSpwanCtr >= ENEMY_INTERVAL){
			//敵の生成
			enemy = CEnemyX::Create();
			enemy->SetPosition(pos);

			m_nSpwanCtr = 0;	//カウンター初期化
		}
		if (m_nSpawnfast >= FAST_INTERVAL){
			fastenemy = CFastEnemy::Create();
			fastenemy->SetPosition(pos);

			m_nSpawnfast = 0;
		}
	}
	else {
		return;
	}
}

//=========================================================================================
//スポナー設定
//=========================================================================================
int CSpawner::GetNumSpawner(void)
{
	return m_Currentalive;
}