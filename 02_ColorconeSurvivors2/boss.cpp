//=========================================================================================
//
// ボス
// Author:日野澤匠泉	[boss.cpp]
//
//=========================================================================================
#include "boss.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "objectX.h"
#include "playerx.h"
#include "score.h"
#include "time.h"
#include "game.h"
#include "spawner.h"

//=========================================================================================
//ボスのコンストラクタ	
//=========================================================================================
CBoss::CBoss()
{
	m_nLife = 100;
	m_nSpawnCtr = 0;
	m_pos = {};
}

//=========================================================================================
//ボスのデストラクタ
//=========================================================================================
CBoss::~CBoss()
{

}

//=========================================================================================
//ボスの初期化処理
//=========================================================================================
HRESULT CBoss::Init(void)
{
	//オブジェクトの初期化処理
	CObjectX::Init("data\\MODEL\\boss_00.x");

	//種類の設定
	SetType(TYPE_BOSS);

	return S_OK;
}

//=========================================================================================
//ボスの終了処理
//=========================================================================================
void CBoss::Uninit(void)
{
	//オブジェクトの終了処理
	CObjectX::Uninit();
}

//=========================================================================================
//ボスの更新処理
//=========================================================================================
void CBoss::Update(void)
{
	m_nCtr++;

	//デバッグ情報取得
	CDebugProc* pDebug = CManager::GetManager()->GetDebugProc();

	//位置情報取得処理
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//ボスの座標取得
	D3DXVECTOR3 BossPos = CObjectX::GetPosition();
	BossPos = D3DXVECTOR3(0.0f,-200.0f,300.0f);
	m_pos = BossPos;

	D3DXVECTOR3 BossMove = CObjectX::GetMove();
	BossMove = D3DXVECTOR3(0.0f, 0.0f, 300.0f);

	float fRandX, fRandZ;
	fRandX = (float)(rand() % 801) - 400.0f;
	fRandZ = (float)(rand() % 801) - 400.0f;

	// ランダムな位置に移動する
	float randomX = static_cast<float>(rand() % 801) - 400.0f;
	float randomZ = static_cast<float>(rand() % 801) - 400.0f;

	D3DXVECTOR3 targetPosition(randomX, 0.0f, randomZ);

	//移動させる
	MoveToPosition(targetPosition);

	//移動設定
	SetMove(m_pos);

	//位置更新
	SetPosition(BossPos);

	if (m_nCtr >= 380 && m_nSpawnCtr < NUM_SPAWNER)
	{
		CSpawner* pSpawner = CSpawner::Create(D3DXVECTOR3(fRandX,-190.0f, fRandZ));

		m_nCtr = 0;
		m_nSpawnCtr++;
	}

	//デバッグ表示
	pDebug->Print("[ボス] ( X:%f Y:%f Z:%f )\n\n", pos.x, pos.y, pos.z);
	pDebug->Print("[ボス 体力] ( %d )\n\n",m_nLife);
}

//=========================================================================================
//ボスの移動
//=========================================================================================
void CBoss::MoveToPosition(const D3DXVECTOR3& targetPosition)
{
	// ゆっくりと移動する処理
	float distance = D3DXVec3Length(&(targetPosition - m_pos));
	float t = distance / 2.0f;

	// 移動先までの位置をゆっくりと更新
	m_pos += (targetPosition - m_pos) / t;
}

//=========================================================================================
//ボスの描画処理
//=========================================================================================
void CBoss::Draw(void)
{
	//オブジェクトの描画処理
	CObjectX::Draw();
}

//=========================================================================================
//ボスの生成処理
//=========================================================================================
CBoss* CBoss::Create(void)
{
	//ポインタの変数を宣言
	CBoss* pBoss;

	//オブジェクト3Dの生成
	pBoss = new CBoss;

	if (pBoss != NULL)
	{//使用されているとき

		//初期化処理
		pBoss->Init();
	}

	//オブジェクト情報を返す
	return pBoss;
}

//=========================================================================================
//ボスのヒット処理
//=========================================================================================
void CBoss::Hit(void)
{
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
	}
}