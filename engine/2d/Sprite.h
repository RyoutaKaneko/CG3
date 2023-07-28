#pragma once

#include <Windows.h>
#include <D3dx12.h>
#include <d3dcompiler.h>
#include <cassert>
#include <DirectXTex.h>
#include <wrl.h>
#include <array>
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"

#include "DirectXCommon.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;


struct VertexPosUv {
	Vector3 pos;
	Vector2 uv;
};

// パイプラインセット
struct PipelineSet {
	// パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
};

//スプライトの共通データ
struct SpriteCommon {

	//テクスチャの最大枚数
	static const int spriteSRVCount = 512;

	//パイプラインセット
	PipelineSet pipelineSet;

	// 射影行列
	Matrix4 matProjection{};

	//テクスチャ用デスクリプタヒープの生成
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//テクスチャソース(テクスチャバッファ)の配列
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];

};

class Sprite
{
public:
	/// <summary>
	/// スプライト生成
	/// </summary>
	void SpriteCreate(ID3D12Device* dev);

	/// <summary>
	/// スプライト共通データ生成
	/// </summary>
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev);

	/// <summary>
	/// スプライト共通グラフィックスコマンドのセット
	/// </summary>
	void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	/// <summary>
	/// スプライト単体描画
	/// </summary>
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon,
		ID3D12Device* dev);
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon,
		ID3D12Device* dev, float alpha_);
	void DrawC(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon,
		ID3D12Device* dev, Vector4 color_);

	/// <summary>
	/// スプライト単体更新
	/// </summary>
	void SpriteUpdate(const SpriteCommon& spriteCommon);

	/// <summary>
	/// スプライト共通テクスチャ読み込み
	/// </summary>
	void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);

	/// <summary>
	/// スプライト単体頂点バッファの転送
	/// </summary>
	void SpriteTransferVertexBuffer();

	void SetTexNumber(UINT texnumber) { this->texNumber = texnumber; }
	void SetPosition(Vector3 position) { this->position = position; }
	void SetScale(Vector2 scale) { this->scale = scale; }
	void SetRotation(float rotate) { this->rotation = rotation; }
	const Vector3& GetPosition() const { return position; }

	void Release();


	void SetAlpha(float alpha_);
	void SetColor(Vector4 color_);

	float GetRotation() { return rotation; }

public:
	void SetPiplineSet(PipelineSet piplineSet);

	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* device);

	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

protected:
	struct ConstBufferData {
		Vector4 color; // 色 (RGBA)
		Matrix4 mat; //座標
	};

	UINT texNumber = 0;

	DirectXCommon* dXCommon = nullptr;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	ComPtr<ID3D12Resource> constBuff;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	// ワールド行列
	Matrix4 matWorld;
	// 座標、大きさ 回転
	Vector3 position = { 0,0,0 };
	Vector2 scale = { 1,1 };
	Vector3 rotation_ = { 0.0f,0.0f,0.0f };

	// Z軸回りの回転
	float rotation = 0.0f;
};
