float4 gUV;
float Brush_Radius;
float Spray_Radius;
float Density;

texture texture0;
texture texture1;
texture texture2;
texture texture3;
texture AlphaMap;



sampler2D TexSampler0 = sampler_state
{
   Texture = (texture0);
};
sampler2D TexSampler1 = sampler_state
{
   Texture = (texture1);
};
sampler2D TexSampler2 = sampler_state
{
   Texture = (texture2);
};
sampler2D TexSampler3 = sampler_state
{
   Texture = (texture3);
};
sampler2D TexAlpha = sampler_state
{
   Texture = (AlphaMap);
};

struct PS_INPUT
{	
	float2 uv : TEXCOORD;
};

float4 main_0(PS_INPUT Input) : COLOR
{
    float UVDensity = Density;
    float2 UV = Input.uv;
    UV.x *= UVDensity;
    UV.y *= UVDensity;

	float4 Tex0 = tex2D(TexSampler0, UV);
	float4 Tex1 = tex2D(TexSampler1, UV);
	float4 Tex2 = tex2D(TexSampler2, UV);
	float4 Tex3 = tex2D(TexSampler3, UV);
	float4 Alpha = tex2D(TexAlpha, Input.uv);
    

	float4 brush = float4(0,0,0,1);
	float r = Brush_Radius;
	float sr = Spray_Radius;
    float d = Alpha.r + Alpha.g + Alpha.b;
    float Rd = Alpha.r / d;
    float Gd = Alpha.g / d;
    float Bd = Alpha.b / d;


	float l;
	float3 vPick = (float3)gUV;
	float3 vPixel = float3(Input.uv.x , 0, Input.uv.y);
	float3 vLen = vPick - vPixel;
	l = length(vLen);
	if (l < r)
	{
		brush = float4(1, 1, 1, 1);
	}
	if (l > r && l < sr)
	{
		float dV = (sr - l) / (sr - r);
		dV *= Density;
		brush = float4(dV, dV, dV, 1);
	}

	return (Tex1 * Alpha.r * Rd + Tex2 * Alpha.g * Gd + Tex3 * Alpha.b * Bd + brush * 0.35f);
};

technique Shader
{
	pass Pass_0
	{
		PixelShader = compile ps_2_0 main_0();
	}
};