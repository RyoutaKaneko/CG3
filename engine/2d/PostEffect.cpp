#include "PostEffect.h"

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, ID3D12Device* dev)
{
	this->cmdList = cmdList_;

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(spriteCommon.pipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(spriteCommon.pipelineSet.rootsignature.Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // �O�p�`���X�g

	//�e�N�X�`���p�ŃX�N���v�^�q�[�v�̐ݒ�
	ID3D12DescriptorHeap* ppHeaps[] = { spriteCommon.descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// ���_�o�b�t�@�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	// �萔�o�b�t�@(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());

	//�V�F�[�_�[���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(
		1, CD3DX12_GPU_DESCRIPTOR_HANDLE(spriteCommon.descHeap->GetGPUDescriptorHandleForHeapStart(),
			texNumber, dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	//�|���S���̕`��
	cmdList->DrawInstanced(4, 1, 0, 0);
}
