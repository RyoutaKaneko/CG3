cbuffer cbuff0 : register(b0)
{
	matrix matWorld; // �R�c�ϊ��s��
};

cbuffer cbuff1 : register(b1)
{
	matrix view;       // ���[���h �� �r���[�ϊ��s��
	matrix projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
	vector cameraPos;  // �J�������W�i���[���h���W�j
};

cbuffer cbuff2:register(b2)
{
	float3 m_ambient:packoffset(c0);  // �A���r�G���g�W��
	float3 m_diffuse:packoffset(c1);  // �f�B�ӂ��[���W��
	float3 m_specular:packoffset(c2); // �X�y�L�����[�W��
	float m_alpha : packoffset(c2.w); // �A���t�@
}

static const int MAX_BONES = 32;

cbuffer skinning:register(b3)
{
	matrix matSkinning[MAX_BONES];
}

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
	float4 svpos : SV_POSITION; // �V�X�e���p���_���W
	float3 normal :NORMAL;      // �@���x�N�g��
	float2 uv  :TEXCOORD;       // uv�l
};
struct VSInput
{
	float4 pos : POSITION; // �V�X�e���p���_���W
	float3 normal :NORMAL;      // �@���x�N�g��
	float2 uv  :TEXCOORD;       // uv�l
	uint4 boneIndices : BONEINDICES;//�{�[���̔ԍ�
	float4 boneWeights : BONEWEIGHTS;//�{�[���̃X�L���ԍ�
};
