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
#include "particle.h"
#include "fade.h"

//=========================================================================================
//ボスのコンストラクタ	
//=========================================================================================
CBoss::CBoss()
{
	m_nLife = 300;
	m_nSpawnCtr = 0;
	m_framesToWait = 0;
	m_currentFrame = 0;
	m_pos = {};
	m_move = {};
	m_targetPos = {};
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
	m_pos = CObjectX::GetPosition();
	m_pos.y = -200.0f;
	m_move = D3DXVECTOR3(5.0f, 0.0f, 5.0f);

	if (m_framesToWait > 0) 
	{
		// 移動後の停滞中
		m_framesToWait--;
	}
	else
	{
		// 移動中
		D3DXVECTOR3 direction = m_targetPos - m_pos;
		D3DXVec3Normalize(&direction, &direction);

		m_pos.x += m_move.x * direction.x;
		m_pos.y += m_move.y * direction.y;
		m_pos.z += m_move.z * direction.z;

		m_currentFrame++;

		if (m_currentFrame >= 60) 
		{
			// 一定フレーム移動したら再びランダムな位置に移動
			MoveToRandomPosition();
		}
	}

	CSpawner* pSpawner = nullptr;

	if (m_nCtr >= 400 && pSpawner->GetNumSpawner() < NUM_SPAWNER)
	{
		float fRandX, fRandZ;
		fRandX = (float)(rand() % 801) - 400.0f;
		fRandZ = (float)(rand() % 801) - 400.0f;

		pSpawner = CSpawner::Create(D3DXVECTOR3(fRandX, -190.0f, fRandZ));

		m_nCtr = 0;
		m_nSpawnCtr++;
	}
	if (m_nLife <= 0)
	{
		//画面遷移
		CFade::GetInstance()->SetFade(CScene::MODE_GAME);
		return;
	}

	//移動設定
	SetMove(m_move);

	//位置更新
	SetPosition(m_pos);

	//デバッグ表示
	pDebug->Print("\n[ボス位置] ( X:%f Y:%f Z:%f )\n", pos.x, pos.y, pos.z);
	pDebug->Print("[ボス移動] ( X:%f Y:%f Z:%f )\n", m_move.x, m_move.y, m_move.z);
	pDebug->Print("[ボス 体力] ( %d )\n\n",m_nLife);
}

//=========================================================================================
//ボスの移動
//=========================================================================================
void CBoss::MoveToPosition(const D3DXVECTOR3& targetPosition)
{
	m_targetPos = targetPosition;
	m_targetPos.y = -200.0f;
	m_framesToWait = 0; // 移動後に一定フレーム停滞させる
	m_currentFrame = 0;
}

//=========================================================================================
//ボスのランダムな位置に移動
//=========================================================================================
void CBoss::MoveToRandomPosition()
{
	// ランダムな位置に移動する
	float randomX = static_cast<float>(rand() % 801) - 400.0f;
	float randomZ = static_cast<float>(rand() % 801) - 400.0f;

	D3DXVECTOR3 targetPosition(randomX, -200.0f, randomZ);

	// 移動させる
	MoveToPosition(targetPosition);
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

	CParticle::Create(GetPosition(), 0);
}

//=========================================================================================
//HP取得処理
//=========================================================================================
int CBoss::GetLife(void)
{
	return m_nLife;
}

//=========================================================================================
//HP減算処理
//=========================================================================================
void CBoss::SumLife(int nNum)
{
	m_nLife -= nNum;
}