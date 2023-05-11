cbuffer cbuff0 : register(b0) {
	matrix viewproj;
	matrix world;
	float3 cameraPos;
};

//頂点バッファの入力
struct VSInput {
	float4 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

//頂点シェーダーからピクセルシェーダーへのやり取りに使うやつ
struct VSOutput {
	float4 svpos : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};