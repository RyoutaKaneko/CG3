#include "PostEffect.h"
#include "WinApp.h"

const float PostEffect::clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

void PostEffect::Initialize(ID3D12Device* dev)
{
	HRESULT result;

	spriteCommon = SpriteCommonCreate(dev);
	SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/white1x1.png", dev);
	SpriteCreate(dev);

	//テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		WinApp::window_width, (UINT)WinApp::window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);
	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapPropsTex = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	CD3DX12_CLEAR_VALUE valTex = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor);

	//テクスチャバッファの生成
	result = dev->CreateCommittedResource(
		&heapPropsTex, D3D12_HEAP_FLAG_NONE,
		&texresDesc, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&valTex, IID_PPV_ARGS(&texBuff));
	assert(SUCCEEDED(result));

	const UINT pixelCount = WinApp::window_width * WinApp::window_height;
	const UINT rowPitch = sizeof(UINT) * WinApp::window_width;
	const UINT depthPitch = rowPitch * WinApp::window_height;
	//画像イメージ
	UINT* img = new UINT[pixelCount];
	for (int i = 0; i < pixelCount; i++) {
		img[i] = 0xff0000ff;
	}
	//テクスチャバッファにデータ転送
	result = texBuff->WriteToSubresource(0, nullptr, img, rowPitch, depthPitch);
	assert(SUCCEEDED(result));
	delete[] img;
	//SRV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 1;
	//SRV用デスクリプタヒープを生成
	result = dev->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result));
	//SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//デスクリプタヒープにSRV作成
	dev->CreateShaderResourceView(texBuff.Get(), &srvDesc, descHeapSRV->GetCPUDescriptorHandleForHeapStart());
	
	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	//RTV用デスクリプターヒープを生成
	result = dev->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));
	//レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
	//シェーダーの計算結果をSRGBに変換して書き込む
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	//デスクリプターヒープにRTVを作成
	dev->CreateRenderTargetView(texBuff.Get(), &renderTargetViewDesc, descHeapRTV->GetCPUDescriptorHandleForHeapStart());

	//深度バッファリソース設定
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT, WinApp::window_width, WinApp::window_height,
			1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);

	CD3DX12_CLEAR_VALUE valDepth = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	//深度バッファの生成
	CD3DX12_HEAP_PROPERTIES heapPropsDepth = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	result = dev->CreateCommittedResource(&heapPropsDepth, D3D12_HEAP_FLAG_NONE,
		&depthResDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&valDepth,
		IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));

	//DSV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;

	//DSV用デスクリプタヒープを作成
	result = dev->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	//デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dev->CreateDepthStencilView(depthBuff.Get(), &dsvDesc, descHeapDSV->GetCPUDescriptorHandleForHeapStart());
	
	//
	SetScale(Vector2(512, 512));
	SpriteUpdate(spriteCommon);
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList_,ID3D12Device* dev)
{
	this->cmdList = cmdList_;
	 
	// パイプラインステートとルートシグネチャの設定コマンド
	cmdList->SetPipelineState(spriteCommon.pipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(spriteCommon.pipelineSet.rootsignature.Get());

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // 三角形リスト

	//テクスチャ用でスクリプタヒープの設定
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// 頂点バッファの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	// 定数バッファ(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());

	//シェーダーリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(
		1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());

	//ポリゴンの描画
	cmdList->DrawInstanced(4, 1, 0, 0);
}

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList_)
{
	CD3DX12_RESOURCE_BARRIER rb = CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_RENDER_TARGET);
	cmdList_->ResourceBarrier(1, &rb);

	//レンダーターゲットビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//レンダーターゲットをセット
	cmdList_->OMSetRenderTargets(1, &rtvH, false, &dsvH);
	//ビューポートの設定
	CD3DX12_VIEWPORT vp = CD3DX12_VIEWPORT(0.0f, 0.0f, WinApp::window_width, WinApp::window_height);
	cmdList_->RSSetViewports(1, &vp);
	//全画面クリア
	cmdList_->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	cmdList_->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList_)
{
	//リソースバリアを変更(描画可能->シェーダーリソース)
	CD3DX12_RESOURCE_BARRIER rb = CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	cmdList_->ResourceBarrier(1, &rb);
}
