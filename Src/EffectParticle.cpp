//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//
//		パーティクルの処理
//															EffectParticle.cpp
//=============================================================================
#include  "EffectParticle.h"

//------------------------------------------------------------------------
//
//	パーティクルプロシージャクラスのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEffectParticleProc::CEffectParticleProc()
{
	PARTICLEBASE pb = {};

	// ------------------------------------------------------------------------------------------
	// パーティクル構造体の設定

	// 0:火花パーティクル
	m_ParticleArray.push_back(pb);
	Load(_T("Data/Image/particle3.png"), &m_ParticleArray.back());// パーティクルテクスチャ
	m_ParticleArray.back().m_nNum = 100;             // 一つのオブジェクト中のパーティクル数。PARTICLE_NUM_MAX以下であること。
	m_ParticleArray.back().m_fDestSize = 0.1f;       // 表示サイズ(一つのパーティクルの大きさ)
	m_ParticleArray.back().m_FrameEnd = 60;          // パーティクルを表示している時間
	m_ParticleArray.back().m_fSpeed = 0.015f;        // パーティクルの移動スピード。ランダム
	m_ParticleArray.back().m_iBarthFrame = 20;       // パーティクルの開始までの最大待ち時間。ランダムで開始。０は待ち無し
	m_ParticleArray.back().m_ifBound = 0;            // 地面でバウンドさせるか（0:バウンドなし 1:地面でバウンド）
	m_ParticleArray.back().m_fAlpha = 0.9f;          // 透明度
	m_ParticleArray.back().m_nBlendFlag = 1;         // ブレンドステートフラグ(0:通常描画　1:加算合成色描画)
	SetSrc(&m_ParticleArray.back());                 // バーテックスバッファの作成

	// 1:火花パーティクル・大
	//m_ParticleArray.push_back(pb);
	//Load(_T("Data/Image/particle2.png"), &m_ParticleArray.back());// パーティクルテクスチャ
	//m_ParticleArray.back().m_nNum = 10;              // 一つのオブジェクト中のパーティクル数。PARTICLE_NUM_MAX以下であること。
	//m_ParticleArray.back().m_fDestSize = 0.5f;       // 表示サイズ(一つのパーティクルの大きさ)
	//m_ParticleArray.back().m_FrameEnd = 60;          // パーティクルを表示している時間
	//m_ParticleArray.back().m_fSpeed = 0.015f;        // パーティクルの移動スピード。ランダム
	//m_ParticleArray.back().m_iBarthFrame = 0;        // パーティクルの開始までの最大待ち時間。ランダムで開始。０は待ち無し
	//m_ParticleArray.back().m_ifBound = 0;            // 地面でバウンドさせるか（0:バウンドなし 1:地面でバウンド）
	//m_ParticleArray.back().m_fAlpha = 0.9f;          // 透明度
	//m_ParticleArray.back().m_nBlendFlag = 1;         // ブレンドステートフラグ(0:通常描画　1:加算合成色描画)
	//SetSrc(&m_ParticleArray.back());                 // バーテックスバッファの作成


	// ---------------------------------------------------------------------------------------------
	// オブジェクトの生成
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectParticleObj(this));  // m_pObjArrayにオブジェクトを生成する
	}

};
//------------------------------------------------------------------------
//
//	パーティクルプロシージャクラスのデストラクタ	
//
//------------------------------------------------------------------------
CEffectParticleProc::~CEffectParticleProc()
{
	for (int i = 0; i < m_ParticleArray.size(); i++)
	{
		SAFE_RELEASE(m_ParticleArray[i].m_pTexture);
		SAFE_RELEASE(m_ParticleArray[i].m_pVertexBuffer);
	}
};

//------------------------------------------------------------------------
//
//	パーティクル構造体配列のアドレスを返す	
//
//  idx  パーティクル構造体配列の要素番号
//
//	戻り値 PARTICLEBASE*　　配列のアドレス
//
//------------------------------------------------------------------------
PARTICLEBASE* CEffectParticleProc::GetPartArrayPtr(int idx)
{
	if (idx < 0 || idx >= m_ParticleArray.size())
	{
		MessageBox(nullptr, _T("■ GetPartArrayPtr( idx) ■"), _T("指定要素番号の配列がありません"), MB_OK);
		return nullptr;
	}
	return &m_ParticleArray[idx];
}

//------------------------------------------------------------------------
//
//	スプライトイメージの読み込み	
//
//  TCHAR* szFName            パーティクルのテクスチャファイル名
//  PARTICLEBASE* pPartBase   パーティクル	構造体アドレス
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CEffectParticleProc::Load(TCHAR* szFName, PARTICLEBASE* pPartBase)
{

	//テクスチャー読み込み	
	if (FAILED(GameDevice()->m_pD3D->CreateShaderResourceViewFromFile(szFName, &pPartBase->m_pTexture,
		pPartBase->m_dwImageWidth, pPartBase->m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("パーティクル　テクスチャーを読み込めません"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	パーティクルプロシージャのバーティクスバッファ作成	
//	（ジオメトリ関連を初期化．ここでは”点”用）	
//
//	PARTICLEBASE* pPartBase
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CEffectParticleProc::SetSrc(PARTICLEBASE* pPartBase)
{
	//バーテックス
	PARTICLE_VERTEX vertices[] =
	{
		VECTOR3(0.0f, 0.0f, 0.0f)
	};

	// ２度目以降に初期化されることの対策
	SAFE_RELEASE(pPartBase->m_pVertexBuffer);

	// バーテックスバッファー作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PARTICLE_VERTEX) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(GameDevice()->m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &pPartBase->m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;

}
//------------------------------------------------------------------------
//
//	パーティクルプロシージャクラスの開始	
//
//	・パーティクルオブジェクト配列の中から、空いているパーティクルを探して開始する
//　　パーティクル構造体配列の要素番号を０として開始する
// 
//  VECTOR3 vEmitPos          パーティクルの発生位置
//  VECTOR3 vNormal           パーティクルの発生面の法線（省略可）
//
//	戻り値 bool
//		true	= 正常
//		false	= 異常
//
//------------------------------------------------------------------------
bool CEffectParticleProc::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	return Start(0, vEmitPos, vNormal);
}
//------------------------------------------------------------------------
//
//	パーティクルプロシージャクラスの開始	
//
//	・パーティクルオブジェクト配列の中から、空いているパーティクルを探して開始する
//
//  int nPartIdx              パーティクル構造体配列の要素番号
//  VECTOR3 vEmitPos          パーティクルの発生位置
//  VECTOR3 vNormal           パーティクルの発生面の法線（省略可）
//
//	戻り値 bool
//		true	= 正常
//		false	= 異常
//
//------------------------------------------------------------------------
bool CEffectParticleProc::Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal)
{

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CEffectParticleObj*)m_pObjArray[i])->Start(nPartIdx, vEmitPos, vNormal);
			return true;
		}
	}
	return false;
};


// ============================================================================================


// ========================================================================================
//
//	パーティクルオブジェクトクラス
//（ポイントスプライトでパーティクルを実現）
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	パーティクルオブジェクトのコンストラクタ	
//
//  int MaxParticle          パーティクルの数
//
//------------------------------------------------------------------------
CEffectParticleObj::CEffectParticleObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_pD3D = GameDevice()->m_pD3D;
	m_pShader = GameDevice()->m_pShader;

	m_nPartIdx = 0;
	m_MaxParticle = 0;
	m_vEmitPos = VECTOR3(0, 0, 0);
	m_pPtArray = nullptr;
	m_Frame = 0;

	//	初期化
	Init();

}
//------------------------------------------------------------------------
//
//	パーティクルオブジェクトのデストラクタ	
//
//------------------------------------------------------------------------
CEffectParticleObj::~CEffectParticleObj()
{
	SAFE_DELETE_ARRAY(m_pPtArray);
}

//------------------------------------------------------------------------
//	パーティクルオブジェクトの初期化関数
//
//  各種設定値の初期化
//
//
//  戻り値　　　なし
//------------------------------------------------------------------------
void CEffectParticleObj::Init()
{
	m_bActive = false;
	m_MaxParticle = EFFECT_NUM_MAX;           // 初期値としてパーティクル配列要素数を入れて置く
	m_pPtArray = new PART[EFFECT_NUM_MAX];    // 一つのオブジェクトの中のパーティクル配列の生成
}

//------------------------------------------------------------------------
//	パーティクルオブジェクトのパーティクル構造体配列のアドレスを返す関数
//
//  引数　　なし
//
//  戻り値　　　PARTICLEBASE*   配列のアドレス
//------------------------------------------------------------------------
PARTICLEBASE* CEffectParticleObj::GetPartArrayPtr()
{
	return  ((CEffectParticleProc*)m_pProc)->GetPartArrayPtr(m_nPartIdx);
}

//------------------------------------------------------------------------
//
//	パーティクルオブジェクトの開始	
//  ・パーティクルを指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
// 
//  int     nPartIdx          パーティクル構造体配列の要素番号
//  VECTOR3 vEmitPos          パーティクルの発生位置
//  VECTOR3 vNormal           パーティクルの発生面の法線（省略可）
//
//	戻り値 bool
//		true	= 正常
//		false	= 異常
//
//------------------------------------------------------------------------
bool CEffectParticleObj::Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return false;

	}
	else {
		// 開始処理
		m_bActive = true;
		m_nPartIdx = nPartIdx;
		m_MaxParticle = GetPartArrayPtr()->m_nNum;  // パーティクル構造体のパーティクル数を設定する
		if (m_MaxParticle > EFFECT_NUM_MAX) m_MaxParticle = EFFECT_NUM_MAX; // もしも要素数をオーバーしていたら要素数に訂正する
		m_vEmitPos = vEmitPos;
		m_Frame = 0;

		// 移動方向。法線方向を中心としてランダム方向に発生させる
		VECTOR3 vDist, vMin, vMax;
		vDist.x = (1.0f - fabsf(vNormal.x)) / 2;
		vDist.y = (1.0f - fabsf(vNormal.y)) / 2;
		vDist.z = (1.0f - fabsf(vNormal.z)) / 2;

		if (vNormal.x < 0)
		{
			vMin.x = vNormal.x - vDist.x;
			vMax.x = 0.0f + vDist.x;
		}
		else {
			vMin.x = 0.0f - vDist.x;
			vMax.x = vNormal.x + vDist.x;
		}
		if (vNormal.y < 0)
		{
			vMin.y = vNormal.y - vDist.y;
			vMax.y = 0.0f + vDist.y;
		}
		else {
			vMin.y = 0.0f - vDist.y;
			vMax.y = vNormal.y + vDist.y;
		}
		if (vNormal.z < 0)
		{
			vMin.z = vNormal.z - vDist.z;
			vMax.z = 0.0f + vDist.z;
		}
		else {
			vMin.z = 0.0f - vDist.z;
			vMax.z = vNormal.z + vDist.z;
		}

		// パーティクルの開始
		for (int i = 0; i < m_MaxParticle; i++)
		{
			m_pPtArray[i].Pos = m_vEmitPos;
			m_pPtArray[i].Dir.x = ((float)rand() / (float)RAND_MAX) * (vMax.x - vMin.x) + vMin.x;
			m_pPtArray[i].Dir.y = ((float)rand() / (float)RAND_MAX) * (vMax.y - vMin.y) + vMin.y;
			m_pPtArray[i].Dir.z = ((float)rand() / (float)RAND_MAX) * (vMax.z - vMin.z) + vMin.z;
			m_pPtArray[i].Dir = normalize(m_pPtArray[i].Dir);
			m_pPtArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * GetPartArrayPtr()->m_fSpeed;      // 移動スピード。ランダム
			m_pPtArray[i].BirthFrame = (int)(((float)rand() / RAND_MAX) * GetPartArrayPtr()->m_iBarthFrame);  // 開始までの待ち時間。ランダム
		}
		return true;
	}
}

//------------------------------------------------------------------------
//
//	パーティクルオブジェクトの移動・更新処理	
//  ・パーティクルを更新する
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CEffectParticleObj::Update()
{
	if (m_bActive)
	{
		m_Frame++;	// フレームを進める
		for (int i = 0; i < m_MaxParticle; i++)
		{
			if (m_Frame > m_pPtArray[i].BirthFrame) // 一個のパーティクルが表示開始時間になったとき
			{
				// 移動
				m_pPtArray[i].Pos = m_pPtArray[i].Pos + m_pPtArray[i].Dir * m_pPtArray[i].Speed;

				// 重力の計算
				m_pPtArray[i].Dir = m_pPtArray[i].Dir + VECTOR3(0, -0.049f, 0);

				// 地面でのバウンド
				if (GetPartArrayPtr()->m_ifBound == 1)
				{
					if (m_pPtArray[i].Pos.y < 0)
					{
						m_pPtArray[i].Dir.y = -m_pPtArray[i].Dir.y;
						m_pPtArray[i].Speed /= 1.8f;
					}
				}
			}
		}

		if (m_Frame >= GetPartArrayPtr()->m_FrameEnd) // 表示時間終了か
		{
			m_bActive = false;
		}

	}
}

//------------------------------------------------------------------------
//
//	パーティクルオブジェクトを画面にレンダリング	
//  ・パーティクルを表示する
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CEffectParticleObj::Draw()
{
	// 表示状態でないとき
	if (!m_bActive)  return;

	//使用するシェーダーのセット
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_POINT, nullptr, 0);
	m_pD3D->m_pDeviceContext->GSSetShader(m_pShader->m_pEffect3D_GS_POINT, nullptr, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, nullptr, 0);

	//バーテックスバッファーをセット
	UINT stride = sizeof(PARTICLE_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &GetPartArrayPtr()->m_pVertexBuffer, &stride, &offset);

	// 加算合成色のブレンディングを設定
	UINT mask = 0xffffffff;
	if (GetPartArrayPtr()->m_nBlendFlag == 1)   // 加算合成色指定
	{
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, nullptr, mask);
	}

	// パーティクル１粒を１枚ポイントスプライトとしてm_MaxParticle枚描画
	for (int i = 0; i < m_MaxParticle; i++)
	{
		// 描画開始前のものと描画フレームアウトのものは描画しない
		if (GetPartArrayPtr()->m_FrameEnd < m_Frame + (GetPartArrayPtr()->m_iBarthFrame - m_pPtArray[i].BirthFrame)) continue;

		//個々のパーティクルの、視点を向くワールドトランスフォームを求める
		MATRIX4X4 mWorld = GetLookatMatrix(m_pPtArray[i].Pos, GameDevice()->m_vEyePt);

		RenderParticle(mWorld, GameDevice()->m_mView, GameDevice()->m_mProj);  // パーティクルをレンダリング
	}

	if (GetPartArrayPtr()->m_nBlendFlag == 1)   // 加算合成色指定
	{
		// 通常のブレンディングに戻す
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, nullptr, mask);
	}

	//ジオメトリシェーダーのリセット
	m_pD3D->m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);

	return;
}
//------------------------------------------------------------------------
//
//	パーティクルをレンダリングする	
//
//  MATRIX4X4    W    ワールドマトリックス
//  MATRIX4X4    V    ビューマトリックス
//  MATRIX4X4    P    プロジェクションマトリックス
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CEffectParticleObj::RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P)
{

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列を渡す // -- 2017.8.25
		cb.mW = XMMatrixTranspose(W);
		cb.mV = XMMatrixTranspose(V);
		cb.mP = XMMatrixTranspose(P);

		cb.fAlpha = GetPartArrayPtr()->m_fAlpha;            // パーティクルの透明度
		cb.fSize = GetPartArrayPtr()->m_fDestSize;          // パーティクルのサイズ 
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout);
	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//テクスチャーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &GetPartArrayPtr()->m_pTexture);
	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(1, 0);

}

