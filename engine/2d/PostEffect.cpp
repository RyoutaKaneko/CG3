#include "PostEffect.h"
#include "WinApp.h"

const float PostEffect::clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

void PostEffect::Initialize(ID3D12Device* dev)
{
	HRESULT result;

	spriteCommon = SpriteCommonCreate(dev);
	SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/white1x1.png", dev);
	SpriteCreate(dev);

	//�e�N�X�`�����\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		WinApp::window_width, (UINT)WinApp::window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);
	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapPropsTex = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	CD3DX12_CLEAR_VALUE valTex = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor);

	//�e�N�X�`���o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&heapPropsTex, D3D12_HEAP_FLAG_NONE,
		&texresDesc, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&valTex, IID_PPV_ARGS(&texBuff));
	assert(SUCCEEDED(result));

	const UINT pixelCount = WinApp::window_width * WinApp::window_height;
	const UINT rowPitch = sizeof(UINT) * WinApp::window_width;
	const UINT depthPitch = rowPitch * WinApp::window_height;
	//�摜�C���[�W
	UINT* img = new UINT[pixelCount];
	for (int i = 0; i < pixelCount; i++) {
		img[i] = 0xff0000ff;
	}
	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = texBuff->WriteToSubresource(0, nullptr, img, rowPitch, depthPitch);
	assert(SUCCEEDED(result));
	delete[] img;
	//SRV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 1;
	//SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = dev->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result));
	//SRV�̐ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//�f�X�N���v�^�q�[�v��SRV�쐬
	dev->CreateShaderResourceView(texBuff.Get(), &srvDesc, descHeapSRV->GetCPUDescriptorHandleForHeapStart());
	
	//RTV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	//RTV�p�f�X�N���v�^�[�q�[�v�𐶐�
	result = dev->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));
	//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
	//�V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	//�f�X�N���v�^�[�q�[�v��RTV���쐬
	dev->CreateRenderTargetView(texBuff.Get(), &renderTargetViewDesc, descHeapRTV->GetCPUDescriptorHandleForHeapStart());

	//�[�x�o�b�t�@���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT, WinApp::window_width, WinApp::window_height,
			1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);

	CD3DX12_CLEAR_VALUE valDepth = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	//�[�x�o�b�t�@�̐���
	CD3DX12_HEAP_PROPERTIES heapPropsDepth = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	result = dev->CreateCommittedResource(&heapPropsDepth, D3D12_HEAP_FLAG_NONE,
		&depthResDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&valDepth,
		IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));

	//DSV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;

	//DSV�p�f�X�N���v�^�q�[�v���쐬
	result = dev->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	//�f�X�N���v�^�q�[�v��DSV�쐬
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
	 
	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(spriteCommon.pipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(spriteCommon.pipelineSet.rootsignature.Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // �O�p�`���X�g

	//�e�N�X�`���p�ŃX�N���v�^�q�[�v�̐ݒ�
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// ���_�o�b�t�@�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	// �萔�o�b�t�@(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());

	//�V�F�[�_�[���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(
		1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());

	//�|���S���̕`��
	cmdList->DrawInstanced(4, 1, 0, 0);
}

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList_)
{
	CD3DX12_RESOURCE_BARRIER rb = CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_RENDER_TARGET);
	cmdList_->ResourceBarrier(1, &rb);

	//�����_�[�^�[�Q�b�g�r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//�[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//�����_�[�^�[�Q�b�g���Z�b�g
	cmdList_->OMSetRenderTargets(1, &rtvH, false, &dsvH);
	//�r���[�|�[�g�̐ݒ�
	CD3DX12_VIEWPORT vp = CD3DX12_VIEWPORT(0.0f, 0.0f, WinApp::window_width, WinApp::window_height);
	cmdList_->RSSetViewports(1, &vp);
	//�S��ʃN���A
	cmdList_->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	cmdList_->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList_)
{
	//���\�[�X�o���A��ύX(�`��\->�V�F�[�_�[���\�[�X)
	CD3DX12_RESOURCE_BARRIER rb = CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	cmdList_->ResourceBarrier(1, &rb);
}
