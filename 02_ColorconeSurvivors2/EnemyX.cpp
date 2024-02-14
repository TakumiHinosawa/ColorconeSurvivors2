//=========================================================================================
//
// エネミー
// Author:日野澤匠泉	[enemyX.cpp]
//
//=========================================================================================
#include "main.h"
#include "enemyX.h"
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
#include "point.h"

//=========================================================================================
//マクロ定義
//=========================================================================================
#define ENEMYMOVE	(2.0f)		//移動量
#define GRAVITY	(0.8f)			//重力

//*****************************************************************************************
//静的メンバ変数
//*****************************************************************************************
int CEnemyX::m_Count = 0;

//=========================================================================================
//エネミーのコンストラクタ	
//=========================================================================================
CEnemyX::CEnemyX()
{
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BuildingPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================================================================
//エネミーのデストラクタ
//=========================================================================================
CEnemyX::~CEnemyX()
{

}

//=========================================================================================
//エネミーの初期化処理
//=========================================================================================
HRESULT CEnemyX::Init(void)
{
	//オブジェクトの初期化処理
	CObjectX::Init("data\\MODEL\\enemy_00.x");

	//種類の設定
	SetType(TYPE_ENEMYX);

	return S_OK;
}

//=========================================================================================
//エネミーの終了処理
//=========================================================================================
void CEnemyX::Uninit(void)
{
	//オブジェクトの終了処理
	CObjectX::Uninit();

	//カウンター加算
	m_Count++;
}

//=========================================================================================
//エネミーの更新処理
//=========================================================================================
void CEnemyX::Update(void)
{
	//位置情報取得処理
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//変数宣言
	D3DXVECTOR3 Dest;
	float fRotMove, fRotDest, fRotDiff;

	//エネミー位置取得
	D3DXVECTOR3 EnemyPos = CObjectX::GetPosition();
	m_OldPos = EnemyPos;

	//エネミー角度取得
	D3DXVECTOR3 EnemyRot = CObjectX::GetRot();

	//エネミー移動量取得
	D3DXVECTOR3 EnemyMove = CObjectX::GetMove();

	//プレイヤー情報取得
	CPlayerX *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	Dest = PlayerPos - EnemyPos;			//目標の向き
	fRotMove = EnemyRot.y;					//現在の移動方向(角度)
	fRotDest = atan2f(Dest.x, Dest.z);		//目標の移動方向(角度)
	fRotDiff = fRotDest - fRotMove;			//目標の移動方向までの差分

	//移動方向の補正
	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += -D3DX_PI * 2;
		}
		else if (fRotDiff < -D3DX_PI)
		{
			fRotDiff += D3DX_PI * 2;
		}
	}

	//移動方向(角度)の補正
	EnemyRot.y += fRotDiff * 0.05f;

	//移動方向の補正
	if (EnemyRot.y > D3DX_PI || EnemyRot.y < -D3DX_PI)
	{
		if (EnemyRot.y > D3DX_PI)
		{
			EnemyRot.y += -D3DX_PI * 2;
		}
		else if (EnemyRot.y < -D3DX_PI)
		{
			EnemyRot.y += D3DX_PI * 2;
		}
	}

	//移動量補正
	EnemyMove.x = sinf(EnemyRot.y) * ENEMYMOVE;
	EnemyMove.z = cosf(EnemyRot.y) * ENEMYMOVE;

	EnemyMove.y -= GRAVITY;

	//移動量加算
	EnemyPos += EnemyMove;

	if (EnemyPos.y <= -800.0f)
	{
		Uninit();
		return;
	}

	//位置更新
	SetPosition(EnemyPos);

	//移動量更新
	SetMove(EnemyMove);

	//向き更新
	SetRot(EnemyRot);

	//当たり判定
	CollisionBuilding();
	PushoutCollision();
}

//=========================================================================================
//エネミーの描画処理
//=========================================================================================
void CEnemyX::Draw(void)
{
	//オブジェクトの描画処理
	CObjectX::Draw();
}

//=========================================================================================
//エネミーの生成処理
//=========================================================================================
CEnemyX *CEnemyX::Create(void)
{
	//ポインタの変数を宣言
	CEnemyX *pEnemyX;

	//オブジェクト3Dの生成
	pEnemyX = new CEnemyX;

	if (pEnemyX != NULL)
	{//使用されているとき

		//初期化処理
		pEnemyX->Init();
	}

	//オブジェクト情報を返す
	return pEnemyX;
}

//=========================================================================================
//エネミーのヒット処理
//=========================================================================================
void CEnemyX::Hit(void)
{
	//スコアの情報取得
	CScore *pScore = CGame::GetScore();

	//スコアの加算
	pScore->AddScore(100);

	CParticle::Create(GetPosition(), 0);

	CPoint::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y + 50.0f, GetPosition().z));

	//終了処理
	CEnemyX::Uninit();
}

//=========================================================================================
//エネミーのキル数
//=========================================================================================
int CEnemyX::GetKillCount(void)
{
	return m_Count;
}

//=========================================================================================
//エネミーのキル数
//=========================================================================================
void CEnemyX::SetKillCount(int nNum)
{
	m_Count = nNum;
}

//=========================================================================================
//プレイヤーと建物の当たり判定
//=========================================================================================
void CEnemyX::CollisionBuilding(void)
{
	CObject* pObj;

	//サウンド情報取得
	CSound* pSound = CManager::GetManager()->GetSound();

	//エネミーの位置情報取得
	D3DXVECTOR3 EnemyPos = GetPosition();

	//エネミーの移動情報取得
	D3DXVECTOR3 EnemyMove = GetMove();

	//エネミーのサイズ保管用変数
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//エネミーのサイズ取得
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//オブジェクト情報取得
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//使用されているとき

			if (pObj->GetType() == TYPE_BUILDING)
			{//建物の時

				//建物の位置取得
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//建物のサイズを取得
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				// ******************************		当たり判定		******************************* //

				//------------------------------------------------------------------------
				//	幅の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= EnemyPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= EnemyPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//幅の判定
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > EnemyPos.z + vtxMin.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < EnemyPos.z + vtxMax.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//横の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= EnemyPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= EnemyPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < EnemyPos.x + vtxMax.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > EnemyPos.x + vtxMin.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}

				//------------------------------------------------------------------------
				//縦の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= EnemyPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= EnemyPos.x + vtxMin.x
					&& BuildingPosition.z + BuildingVtxMin.z <= EnemyPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= EnemyPos.z + vtxMin.z)
				{
					if (BuildingPosition.y + BuildingVtxMin.y >= m_OldPos.y + vtxMax.y
						&& BuildingPosition.y + BuildingVtxMin.y < EnemyPos.y + vtxMax.y)
					{//　下の判定

						//位置更新
						EnemyPos.y = BuildingPosition.y + BuildingVtxMin.y - vtxMax.y;
					}
					if (BuildingPosition.y + BuildingVtxMax.y <= m_OldPos.y + vtxMin.y
						&& BuildingPosition.y + BuildingVtxMax.y > EnemyPos.y + vtxMin.y)
					{//　上の判定

						//位置更新
						EnemyPos.y = BuildingPosition.y + BuildingVtxMax.y - vtxMin.y + 0.001f;

						//重力初期化
						EnemyMove.y = 0.0f;
					}
				}
				//現在のサイズの座標を保存する
				m_VtxMax = BuildingVtxMax;
				m_VtxMin = BuildingVtxMin;

				//位置情報を保存
				m_BuildingPos = BuildingPosition;
			}
		}
	}

	//位置情報更新
	SetPosition(EnemyPos);

	//移動情報更新
	SetMove(EnemyMove);
}

//=========================================================================================
//敵同士の当たり判定処理
//=========================================================================================
void CEnemyX::PushoutCollision(void)
{
	CObject* pObj;

	//サウンド情報取得
	CSound* pSound = CManager::GetManager()->GetSound();

	//エネミーの位置情報取得
	D3DXVECTOR3 EnemyPos = GetPosition();

	//エネミーの移動情報取得
	D3DXVECTOR3 EnemyMove = GetMove();

	//エネミーのサイズ保管用変数
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//エネミーのサイズ取得
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//オブジェクト情報取得
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//使用されているとき

			if (pObj->GetType() == TYPE_ENEMYX)
			{//建物の時

				//建物の位置取得
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//建物のサイズを取得
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				//------------------------------------------------------------------------
				//	幅の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= EnemyPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= EnemyPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//幅の判定
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > EnemyPos.z + vtxMin.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < EnemyPos.z + vtxMax.z)
					{
						EnemyPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//横の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= EnemyPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= EnemyPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < EnemyPos.x + vtxMax.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > EnemyPos.x + vtxMin.x)
					{
						EnemyPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}

				//現在のサイズの座標を保存する
				m_VtxMax = BuildingVtxMax;
				m_VtxMin = BuildingVtxMin;

				//位置情報を保存
				m_BuildingPos = BuildingPosition;
			}
		}
	}

	//位置情報更新
	SetPosition(EnemyPos);

	//移動情報更新
	SetMove(EnemyMove);
}