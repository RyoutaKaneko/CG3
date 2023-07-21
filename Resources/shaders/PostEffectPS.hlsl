#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    //float4 texcolor0 = tex0.Sample(smp, input.uv);
    //float4 texcolor1 = 1 - tex1.Sample(smp, input.uv);
    
    
    
    float u_ = 5.0f / 1280.0f;
    float v_ = 5.0f / 720.0f;
    float4 colorWeight0 = { 0, 0, 0, 0 };
    float4 colorWeight1 = { 0, 0, 0, 0 };
    
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x - u_, input.uv.y - v_));
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x, input.uv.y - v_));
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x + u_, input.uv.y - v_));
    
    colorWeight1 += 1 - tex1.Sample(smp, float2(input.uv.x - u_, input.uv.y - v_));
    colorWeight1 += 1 - tex1.Sample(smp, float2(input.uv.x, input.uv.y - v_));
    colorWeight1 += 1 - tex1.Sample(smp, float2(input.uv.x + u_, input.uv.y - v_));
    
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x - u_, input.uv.y));
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x, input.uv.y));
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x + u_, input.uv.y));
    
    colorWeight1 += tex1.Sample(smp, float2(input.uv.x - u_, input.uv.y));
    colorWeight1 += tex1.Sample(smp, float2(input.uv.x, input.uv.y));
    colorWeight1 += tex1.Sample(smp, float2(input.uv.x + u_, input.uv.y));
    
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x - u_, input.uv.y + v_));
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x, input.uv.y + v_));
    colorWeight0 += tex0.Sample(smp, float2(input.uv.x + u_, input.uv.y + v_));
    
    colorWeight1 += 1 - tex1.Sample(smp, float2(input.uv.x - u_, input.uv.y + v_));
    colorWeight1 += 1 - tex1.Sample(smp, float2(input.uv.x, input.uv.y + v_));
    colorWeight1 += 1 - tex1.Sample(smp, float2(input.uv.x + u_, input.uv.y + v_));
    
    //return float4((colorWeight.rgb / 9), 1);
    
    float4 color = colorWeight0;
    if (fmod(input.uv.y, 0.1f) > 0.05f)
    {
        color = colorWeight1;
    }
    
    return float4((color.rgb / 9), 1);
}