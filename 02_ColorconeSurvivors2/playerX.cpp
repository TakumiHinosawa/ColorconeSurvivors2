//=========================================================================================
//
// プレイヤー
// Author:日野澤匠泉	[playerX.cpp]
//
//=========================================================================================
#include "main.h"
#include "playerX.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "score.h"
#include "sound.h"
#include "game.h"
#include "bullet3D.h"
#include "explosion3D.h"

//=========================================================================================
//マクロ定義
//=========================================================================================
#define GRAVITY	(0.8f)			//重力
#define MOVE_PLAYER	(0.8f)		//移動量
#define JUMPHEIGHT (16.0f)		//ジャンプ力
#define AIRBORNE (20)			//浮遊時間
#define ROTSPEED (0.7f)			//回転速度
#define TIMING	 (6)			//弾発射の速度
#define BULLETSPEED	(5.0f)		//弾速
#define HEIGHT		(10.0f)		//高さ
#define KNOCKBACK	(10.0f)

//=========================================================================================
//プレイヤーのコンストラクタ	
//=========================================================================================
CPlayerX::CPlayerX()
{
	m_VtxMax = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BuildingPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================================================================
//プレイヤーのデストラクタ
//=========================================================================================
CPlayerX::~CPlayerX()
{

}

//=========================================================================================
//プレイヤーの初期化処理
//=========================================================================================
HRESULT CPlayerX::Init(void)
{
	//オブジェクトの初期化処理
	CObjectX::Init("data\\MODEL\\player_00.x");

	//種類の設定
	SetType(TYPE_PLAYER);

	D3DXVECTOR3 pos = { 0.0f,0.0f,-200.0f };
	CObjectX::SetPosition(pos);

	return S_OK;
}

//=========================================================================================
//プレイヤーの終了処理
//=========================================================================================
void CPlayerX::Uninit(void)
{
	//オブジェクトの終了処理
	CObjectX::Uninit();
}

//=========================================================================================
//プレイヤーの更新処理
//=========================================================================================
void CPlayerX::Update(void)
{
	//プレイヤー操作処理
	Controller(); 
}

//=========================================================================================
//プレイヤーの描画処理
//=========================================================================================
void CPlayerX::Draw(void)
{
	//オブジェクトの描画処理
	CObjectX::Draw();
}

//=========================================================================================
//プレイヤーのコントローラー
//=========================================================================================
void CPlayerX::Controller(void)
{
	//デバッグ情報取得
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	//カメラ情報取得
	D3DXVECTOR3 RotCamera = CCamera::GetRotCamera();

	//キーボードへのポインタ取得
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//コントローラーへのポインタ取得
	CInputController *pInputController = CManager::GetManager()->GetInputController();

	//カメラ情報取得
	D3DXVECTOR3 CameraRot = CCamera::GetRotCamera();

	//サウンド情報取得
	CSound *pSound = CManager::GetManager()->GetSound();

	//向き取得処理
	D3DXVECTOR3 rot = CObjectX::GetRot();
	D3DXVECTOR3 move = CObjectX::GetMove();
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//現在の位置を保存
	m_OldPos = pos;

	//カメラ情報取得
	float fRotMove = rot.y;		//現在の向き
	float fRotDest = rot.y;		//行きたい方向
	float fRotDiff = fRotDest - fRotMove;	//目的の方向
	bool bUse = false;
	
	//*********************************************************************
	//　移動
	//*********************************************************************
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputController->GetJoyStickLX(0) < 0)
	{//←が押されたとき
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputController->GetJoyStickLY(0) > 0)
		{//↑
			move.x += sinf(CameraRot.y - (D3DX_PI * 0.25f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (D3DX_PI * 0.25f)) * MOVE_PLAYER;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputController->GetJoyStickLY(0) < 0)
		{//↓
			move.x += sinf(CameraRot.y - (D3DX_PI * 0.75f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (D3DX_PI * 0.75f)) * MOVE_PLAYER;
		}
		else
		{//←
			move.x += sinf(CameraRot.y - (D3DX_PI * 0.5f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (D3DX_PI * 0.5f)) * MOVE_PLAYER;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputController->GetJoyStickLX(0) > 0)
	{//→が押されたとき
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputController->GetJoyStickLY(0) > 0)
		{//↑
			move.x += sinf(CameraRot.y - (-D3DX_PI * 0.25f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (-D3DX_PI * 0.25f)) * MOVE_PLAYER;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputController->GetJoyStickLY(0) < 0)
		{//↓
			move.x += sinf(CameraRot.y - (-D3DX_PI * 0.75f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (-D3DX_PI * 0.75f)) * MOVE_PLAYER;
		}
		else
		{//→
			move.x += sinf(CameraRot.y - (-D3DX_PI * 0.5f)) * MOVE_PLAYER;
			move.z += cosf(CameraRot.y - (-D3DX_PI * 0.5f)) * MOVE_PLAYER;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputController->GetJoyStickLY(0) > 0)
	{//上移動
		move.x += sinf(CameraRot.y) * MOVE_PLAYER;
		move.z += cosf(CameraRot.y) * MOVE_PLAYER;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputController->GetJoyStickLY(0) < 0)
	{//下移動
		move.x -= sinf(CameraRot.y) * MOVE_PLAYER;
		move.z -= cosf(CameraRot.y) * MOVE_PLAYER;
	}

	//*********************************************************************
	//　射撃
	//*********************************************************************
	if (pInputKeyboard->GetPress(DIK_LEFT) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRX(0) < 0 && m_nTiming >= TIMING)
	{//←が押されたとき
		if (pInputKeyboard->GetPress(DIK_UP) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) > 0 && m_nTiming >= TIMING)
		{
			//弾の生成
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (D3DX_PI * 0.25f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (D3DX_PI * 0.25f)) * BULLETSPEED));

			//サウンドの再生
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//カウンター初期化
			m_nTiming = 0;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) < 0 && m_nTiming >= TIMING)
		{
			//弾の生成
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(D3DXVECTOR3(sinf(CameraRot.y - (D3DX_PI * 0.75f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (D3DX_PI * 0.75f)) * BULLETSPEED)));

			//サウンドの再生
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//カウンター初期化
			m_nTiming = 0;
		}
		else
		{
			//弾の生成
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (D3DX_PI * 0.5f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (D3DX_PI * 0.5f)) * BULLETSPEED));

			//サウンドの再生
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//カウンター初期化
			m_nTiming = 0;
		}
	}

	if (pInputKeyboard->GetPress(DIK_RIGHT) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRX(0) > 0 && m_nTiming >= TIMING)
	{//→が押されたとき
		if (pInputKeyboard->GetPress(DIK_UP) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) > 0 && m_nTiming >= TIMING)
		{
			//弾の生成
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (-D3DX_PI * 0.25f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (-D3DX_PI * 0.25f)) * BULLETSPEED));

			//サウンドの再生
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//カウンター初期化
			m_nTiming = 0;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true && m_nTiming >= TIMING
			|| pInputController->GetJoyStickRY(0) < 0 && m_nTiming >= TIMING)
		{
			//弾の生成
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (-D3DX_PI * 0.75f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (-D3DX_PI * 0.75f)) * BULLETSPEED));

			//サウンドの再生
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//カウンター初期化
			m_nTiming = 0;
		}
		else
		{
			//弾の生成
			CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
				D3DXVECTOR3(sinf(CameraRot.y - (-D3DX_PI * 0.5f)) * BULLETSPEED, 0.0f,
					cosf(CameraRot.y - (-D3DX_PI * 0.5f)) * BULLETSPEED));

			//サウンドの再生
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			//カウンター初期化
			m_nTiming = 0;
		}
	}
	if (pInputKeyboard->GetPress(DIK_UP) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRY(0) > 0 && m_nTiming >= TIMING)
	{
		//弾の生成
		CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
			D3DXVECTOR3(sinf(CameraRot.y) * BULLETSPEED, 0.0f, cosf(CameraRot.y) * BULLETSPEED));

		//サウンドの再生
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		//カウンター初期化
		m_nTiming = 0;
	}
	if (pInputKeyboard->GetPress(DIK_DOWN) == true && m_nTiming >= TIMING
		|| pInputController->GetJoyStickRY(0) < 0 && m_nTiming >= TIMING)
	{
		//弾の生成
		CBullet3D::Create()->SetBullet(D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z),
			D3DXVECTOR3(-sinf(CameraRot.y) * BULLETSPEED, 0.0f, -cosf(CameraRot.y) * BULLETSPEED));

		//サウンドの再生
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		//カウンター初期化
		m_nTiming = 0;
	}

	//弾のタイミング加算
	m_nTiming++;

	//移動量を更新(減衰させる)
	move.x += (0.0f - move.x) * 0.12f;
	move.z += (0.0f - move.z) * 0.12f;

	//角度算出
	fRotDiff = fRotDest - fRotMove;		//目標の移動方向までの差分

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

	rot.y += fRotDiff * 0.1f;

	//移動方向の補正
	if (rot.y > D3DX_PI || rot.y < -D3DX_PI)
	{
		if (rot.y > D3DX_PI)
		{
			rot.y += -D3DX_PI * 2;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2;
		}
	}

	//重力
	move.y -= GRAVITY;

	//移動量加算
	pos += move;

	//位置情報更新
	SetPosition(pos);

	//移動量更新
	SetMove(move);

	//建物との当たり判定処理
	CollisionBuilding();

	//デバッグ表示
	pDebug->Print("\n重力 : %f\n",move.y);
	pDebug->Print("プレイヤーの座標 %f  %f  %f\n",pos.x,pos.y,pos.z);
}

//=========================================================================================
//プレイヤーの生成処理
//=========================================================================================
CPlayerX *CPlayerX::Create(void)
{
	//ポインタの変数を宣言
	CPlayerX *pPlayerX;

	//オブジェクト3Dの生成
	pPlayerX = new CPlayerX;

	if (pPlayerX != NULL)
	{//使用されているとき

		//初期化処理
		pPlayerX->Init();
	}

	//オブジェクト情報を返す
	return pPlayerX;
}

//=========================================================================================
//プレイヤーと建物の当たり判定
//=========================================================================================
void CPlayerX::CollisionBuilding(void)
{
	//デバッグ情報取得
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	CObject *pObj;

	//サウンド情報取得
	CSound *pSound = CManager::GetManager()->GetSound();

	//プレイヤーの位置情報取得
	D3DXVECTOR3 PlayerPos = GetPosition();

	//プレイヤーの移動情報取得
	D3DXVECTOR3 PlayerMove = GetMove();

	//プレイヤーのサイズ保管用変数
	D3DXVECTOR3 vtxMin, vtxMax;

	//プレイヤーのサイズ取得
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

				//敵の位置取得
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//建物のサイズを取得
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				// ******************************		当たり判定		******************************* //

				//------------------------------------------------------------------------
				//	幅の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= PlayerPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= PlayerPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//幅の判定
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > PlayerPos.z + vtxMin.z)
					{
						PlayerPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < PlayerPos.z + vtxMax.z)
					{
						PlayerPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//横の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= PlayerPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= PlayerPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < PlayerPos.x + vtxMax.x)
					{
						PlayerPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > PlayerPos.x + vtxMin.x)
					{
						PlayerPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}

				//------------------------------------------------------------------------
				//縦の判定
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= PlayerPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= PlayerPos.x + vtxMin.x
					&& BuildingPosition.z + BuildingVtxMin.z <= PlayerPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= PlayerPos.z + vtxMin.z)
				{
					if (BuildingPosition.y + BuildingVtxMin.y >= m_OldPos.y + vtxMax.y
						&& BuildingPosition.y + BuildingVtxMin.y < PlayerPos.y + vtxMax.y)
					{//　下の判定

						//位置更新
						PlayerPos.y = BuildingPosition.y + BuildingVtxMin.y - vtxMax.y;
					}
					if (BuildingPosition.y + BuildingVtxMax.y <= m_OldPos.y + vtxMin.y
						&& BuildingPosition.y + BuildingVtxMax.y > PlayerPos.y + vtxMin.y)
					{//　上の判定
						
						//位置更新
						PlayerPos.y = BuildingPosition.y + BuildingVtxMax.y - vtxMin.y + 0.001f;

						//重力初期化
						PlayerMove.y = 0.0f;

						pDebug->Print("\n乗っている判定 \n\n");
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
	SetPosition(PlayerPos);

	//移動情報更新
	SetMove(PlayerMove);

	CollideBoss();
	CollideEnemy();

	//デバッグ表示
	pDebug->Print("[建物　座標] ( X:%f Y:%f Z:%f )\n", m_BuildingPos.x, m_BuildingPos.y, m_BuildingPos.z);
	pDebug->Print("[建物　最大サイズ] ( X:%f Y:%f Z:%f )\n", m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);
	pDebug->Print("[建物　最小サイズ] ( X:%f Y:%f Z:%f )\n\n", m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
	pDebug->Print("[プレイヤー　座標] ( X:%f Y:%f Z:%f )\n", PlayerPos.x, PlayerPos.y, PlayerPos.z);
	pDebug->Print("[プレイヤー 現在の座標] ( X:%f Y:%f Z:%f )\n\n", m_OldPos.x, m_OldPos.y, m_OldPos.z);
}

//=========================================================================================
//プレイヤーとボスの当たり判定
//=========================================================================================
void CPlayerX::CollideBoss(void)
{
	CObject* pObj;

	//サウンド情報取得
	//CSound* pSound = CManager::GetSound();

	//位置情報取得
	D3DXVECTOR3 PlayerPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//モデルサイズ取得
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//オブジェクト情報取得
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//使用されているとき

			if (pObj->GetType() == TYPE_BOSS)
			{//敵の時

				//敵の位置取得
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//頂点座標取得
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (PlayerPos.x >= EnemyPos.x + vtxMin.x
					&& PlayerPos.x <= EnemyPos.x + vtxMax.x
					&& PlayerPos.z >= EnemyPos.z + vtxMin.z
					&& PlayerPos.z <= EnemyPos.z + vtxMax.z)
				{//当たり判定

					//爆発の生成
					CExplosion3D::Create(EnemyPos);

					//サウンドの再生
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//敵に自分が当たった時
					//pObj->Uninit();

					//スコアの情報取得
					CScore* pScore = CGame::GetScore();

					//スコアの加算
					pScore->SubScore(100);
				}
			}
		}
	}
}

//=========================================================================================
//プレイヤーと敵の当たり判定
//=========================================================================================
void CPlayerX::CollideEnemy(void)
{
	CObject* pObj;

	//サウンド情報取得
	//CSound* pSound = CManager::GetSound();

	//位置情報取得
	D3DXVECTOR3 PlayerPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//モデルサイズ取得
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//オブジェクト情報取得
		pObj = CObject::GetObject(nCnt);

		if (pObj != nullptr)
		{//使用されているとき

			if (pObj->GetType() == TYPE_ENEMYX)
			{//敵の時

				//敵の位置取得
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//頂点座標取得
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (PlayerPos.x >= EnemyPos.x + vtxMin.x
					&& PlayerPos.x <= EnemyPos.x + vtxMax.x
					&& PlayerPos.z >= EnemyPos.z + vtxMin.z
					&& PlayerPos.z <= EnemyPos.z + vtxMax.z)
				{//当たり判定

					D3DXVECTOR3 rot = pObj->GetRot();

					//ノックバック
					Knockback(KNOCKBACK, atan2f(GetPosition().x - pObj->GetPosition().x, GetPosition().z - pObj->GetPosition().z));
					
					//爆発の生成
					CExplosion3D::Create(EnemyPos);

					//サウンドの再生
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//敵に自分が当たった時
					pObj->Uninit();

					//スコアの情報取得
					CScore* pScore = CGame::GetScore();

					//スコアの加算
					pScore->SubScore(100);
				}
			}
		}
	}
}

//=========================================================================================
//ノックバック処理
//=========================================================================================
void CPlayerX::Knockback(float knockbackForce, float angle)
{
	D3DXVECTOR3 Velocity = GetMove();
	D3DXVECTOR3 Pos = GetPosition();

	// 角度をラジアンに変換
	float radians = angle;

	// ノックバックの速度を計算
	float knockbackX = knockbackForce * cosf(radians);
	float knockbackZ = knockbackForce * sinf(radians);

	// 速度を更新してノックバックを適用
	Velocity.x += knockbackX;
	Velocity.z += knockbackZ;

	Pos += Velocity;
	SetMove(Velocity);
	SetPosition(Pos);
}