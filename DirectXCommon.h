#pragma once

#include <cstdlib>
#include<chrono>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"

class DirectXCommon
{
public:
	//������
	void Initialize(WinApp*winApp);

	//�f�o�C�X�̏�����
	void InitializeDevice();

	//�R�}���h�֘A�̏�����
	void InitializeCommand();

	//�X���b�v�`�F�[���̏�����
	void InitializeSwapChain();

	//�����_�[�^�[�Q�b�g�r���[�̏�����
	void InitializeRendeTargetView();

	//�[�x�o�b�t�@�r���[�̏�����
	void InitializeDepthBuffer();

	//�t�F���X�̏�����
	void InitializeFence();

	//�`��O����
	void PreDraw();

	//�`��㏈��
	void PostDraw();

	//�f�o�C�X�擾
	ID3D12Device* GetDevice() const { return device_.Get(); }

	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList_.Get(); }

private: //�����o�֐�
	//FPS�Œ菉����
	void InitializeFixFPS();
	//FPS�Œ�X�V
	void UpdateFixFPS();

private:
	//WindowsAPI
	WinApp* winApp = nullptr;
	//DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	//DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	//�R�}���h���X�g
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	//�R�}���h�A���P�[�^
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator_;
	//�X���b�v�`�F�[��
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_;
	//�R�}���h�L���[
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer_;
	//�����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//�[�x�o�b�t�@�r���[
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff_;
	// ���\�[�X�o���A
	D3D12_RESOURCE_BARRIER barrierDesc_;
	//�t�F���X
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
	UINT64 fenceVal_ = 0;
	// ���ʊm�F
	HRESULT result;

	//�L�^����(FPS�Œ�p)
	std::chrono::steady_clock::time_point reference_;
};

