//=========================================================================================
//
//[bullet.cpp]
//Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "bullet3D.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "explosion3D.h"
#include "enemyX.h"
#include "score.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define SIZE	(15.0f)		//サイズ

//*****************************************************************************************
//静的メンバ変数初期化
//*****************************************************************************************
LPDIRECT3DTEXTURE9 CBullet3D::m_pTexture = NULL;

//=========================================================================================
//弾のコンストラクタ
//=========================================================================================
CBullet3D::CBullet3D()
{//各種初期化

	m_nLife = 50;
}

//=========================================================================================
//弾のデストラクタ
//=========================================================================================
CBullet3D::~CBullet3D()
{

}

//=========================================================================================
//弾のテクスチャ読み込み
//=========================================================================================
HRESULT CBullet3D::Load(void)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet.png",
		&m_pTexture);

	return S_OK;
}

//=========================================================================================
//弾のテクスチャ破棄
//=========================================================================================
void CBullet3D::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=========================================================================================
//弾の初期化処理
//=========================================================================================
HRESULT CBullet3D::Init(void)
{
	//オブジェクトの初期化処理
	CObjectBillboard::Init();

	//種類の設定
	SetType(TYPE_BULLET);

	//サイズ設定処理
	CObjectBillboard::SetSize(SIZE, SIZE);

	return S_OK;
}

//=========================================================================================
//弾の終了処理
//=========================================================================================
void CBullet3D::Uninit(void)
{
	//オブジェクトの終了処理
	CObjectBillboard::Uninit();
}

//=========================================================================================
//弾の更新処理
//=========================================================================================
void CBullet3D::Update(void)
{
	//サウンドの取得
	CSound* pSound = CManager::GetManager()->GetSound();

	//寿命を減らす
	m_nLife--;

	//位置情報取得
	D3DXVECTOR3 pos = CObjectBillboard::GetPosition();

	//移動量取得処理
	D3DXVECTOR3 move = CObjectBillboard::GetMove();

	//移動量加算
	pos += move;

	//位置情報設定処理
	CObjectBillboard::SetPos(pos);

	//弾の設定処理
	CObjectBillboard::SetBullet(pos, move);

	if (CollisionEnemy() == true)
	{
		return;
	}
	else if (CollisionBoss() == true)
	{
		return;
	}
	else if (CollisionSpawner() == true)
	{
		return;
	}
	else
	{
		if (m_nLife <= 0)
		{// 0以下の時

			//爆発の生成
			CExplosion3D::Create(pos);

			//終了処理
			Uninit();
		}
		return;
	}
}

//=========================================================================================
//弾の描画処理
//=========================================================================================
void CBullet3D::Draw(void)
{
	//オブジェクトの描画処理
	CObjectBillboard::Draw();
}

//=========================================================================================
//弾の設定処理
//=========================================================================================
void CBullet3D::SetPosotion(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	//位置情報取得
	D3DXVECTOR3 Bulletpos, Bulletmove;

	//位置情報取得
	Bulletpos = CObjectBillboard::GetPosition();

	//移動量取得
	Bulletmove = CObjectBillboard::GetRot();

	Bulletpos = pos;
	Bulletmove = move;
	m_nLife = nLife;
}

//=========================================================================================
//弾の設定処理
//=========================================================================================
CBullet3D *CBullet3D::Create(void)
{
	//ポインタの変数を宣言
	CBullet3D *pBullet;

	//オブジェクト2Dの生成
	pBullet = new CBullet3D;

	if (pBullet != NULL)
	{//使用されているとき

		//初期化処理
		pBullet->Init();

		//テクスチャの割り当て
		pBullet->BindTexture(m_pTexture);
	}

	//オブジェクト情報を返す
	return pBullet;
}

//=========================================================================================
//弾の敵の当たり判定
//=========================================================================================
bool CBullet3D::CollisionEnemy(void)
{
	CObject *pObj;

	//位置情報取得
	D3DXVECTOR3 BulletPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//モデルサイズ取得
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	//サウンド情報取得
	CSound *pSound = CManager::GetManager()->GetSound();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//オブジェクト情報取得
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//使用されているとき

			if (pObj->GetType() == TYPE_ENEMYX )
			{//敵の時

				//敵の位置取得
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//頂点座標取得
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (BulletPos.x >= EnemyPos.x + vtxMin.x
					&& BulletPos.x <= EnemyPos.x + vtxMax.x
					&& BulletPos.z >= EnemyPos.z + vtxMin.z
					&& BulletPos.z <= EnemyPos.z + vtxMax.z)
				{//当たり判定

					//サウンドの生成
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//爆発の生成
					CExplosion3D::Create(EnemyPos);

					//弾の終了処理
					Uninit();

					//ヒット処理
					pObj->Hit();

					//スコアの情報取得
					CScore *pScore = CGame::GetScore();

					//スコアの加算
					pScore->AddScore(10);

					//当たった場合はtrueを返す
					return true;
				}
			}
		}
	}

	//当たっていないときfalseにを返す
	return false;
}

//=========================================================================================
//弾の敵の当たり判定
//=========================================================================================
bool CBullet3D::CollisionBoss(void)
{
	CObject* pObj;

	//位置情報取得
	D3DXVECTOR3 BulletPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//モデルサイズ取得
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	//サウンド情報取得
	CSound* pSound = CManager::GetManager()->GetSound();

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

				if (BulletPos.x >= EnemyPos.x + vtxMin.x
					&& BulletPos.x <= EnemyPos.x + vtxMax.x
					&& BulletPos.z >= EnemyPos.z + vtxMin.z
					&& BulletPos.z <= EnemyPos.z + vtxMax.z)
				{//当たり判定

					//サウンドの生成
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//爆発の生成
					CExplosion3D::Create(EnemyPos);

					//弾の終了処理
					Uninit();

					//ヒット処理
					pObj->Hit();

					//スコアの情報取得
					CScore* pScore = CGame::GetScore();

					//スコアの加算
					pScore->AddScore(10);

					//当たった場合はtrueを返す
					return true;
				}
			}
		}
	}

	//当たっていないときfalseにを返す
	return false;
}

//=========================================================================================
//弾の敵の当たり判定
//=========================================================================================
bool CBullet3D::CollisionSpawner(void)
{
	CObject* pObj;

	//位置情報取得
	D3DXVECTOR3 BulletPos = GetPosition();
	D3DXVECTOR3 vtxMin, vtxMax;

	//モデルサイズ取得
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	//サウンド情報取得
	CSound* pSound = CManager::GetManager()->GetSound();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//オブジェクト情報取得
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//使用されているとき

			if (pObj->GetType() == TYPE_SPAWNER)
			{//敵の時

				//敵の位置取得
				D3DXVECTOR3 EnemyPos = pObj->GetPosition();

				//頂点座標取得
				vtxMax = pObj->GetVtxMax();
				vtxMin = pObj->GetVtxMin();

				if (BulletPos.x >= EnemyPos.x + vtxMin.x
					&& BulletPos.x <= EnemyPos.x + vtxMax.x
					&& BulletPos.z >= EnemyPos.z + vtxMin.z
					&& BulletPos.z <= EnemyPos.z + vtxMax.z)
				{//当たり判定

					//サウンドの生成
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

					//爆発の生成
					CExplosion3D::Create(EnemyPos);

					//弾の終了処理
					Uninit();

					//ヒット処理
					pObj->Hit();

					//スコアの情報取得
					CScore* pScore = CGame::GetScore();

					//スコアの加算
					pScore->AddScore(10);

					//当たった場合はtrueを返す
					return true;
				}
			}
		}
	}
	//当たっていないときfalseにを返す
	return false;
}