// PASS_0 ============================================================================

float4 gUV;
float Brush_Radius;
float Spray_Radius;
float Density;
float Tex1Density;
float Tex2Density;
float Tex3Density;


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
    float TEX1_DEN = Tex1Density;
    float TEX2_DEN = Tex2Density;
    float TEX3_DEN = Tex3Density;


    //float UVDensity = Density;
	//float4 Tex0 = tex2D(TexSampler0, UV);

    float2 UV = Input.uv;
    UV.x *= TEX1_DEN;
    UV.y *= TEX1_DEN;
	float4 Tex1 = tex2D(TexSampler1, UV);

    UV = Input.uv;
    UV.x *= TEX2_DEN;
    UV.y *= TEX2_DEN;
	float4 Tex2 = tex2D(TexSampler2, UV);
    UV = Input.uv;
    UV.x *= TEX3_DEN;
    UV.y *= TEX3_DEN;
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
		brush = float4(Density * 0.1f, Density * 0.1f, Density * 0.1f, Density);
	}
	if (l > r && l < sr)
	{
		float dV = (sr - l) / (sr - r);
		dV *= Density * 0.1f;
		brush = float4(dV, dV, dV, 1);

        if ( l + 0.002f > sr )
            brush = float4(2.5f, 2.5f, 2.5f, 1);

	}

	return (Tex1 * Alpha.r * Rd + Tex2 * Alpha.g * Gd + Tex3 * Alpha.b * Bd + brush * 0.4f);
};

// PASS_1 =========================================================================================================

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;

float4 gWorldLightPosition;
float4 gWorldCameraPosition : ViewPosition;

float gTime : Time0_X;
float gWaveHeight;
float gSpeed;
float gWaveFrequency;
float gUVSpeed;
float gTransparent;

struct VS1_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;
   float2 mUV: TEXCOORD0;
};

struct VS1_OUTPUT 
{
   float4 mPosition : POSITION;
   float2 mUV: TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 mReflection: TEXCOORD3;
};

VS1_OUTPUT WaveShader_Pass_1_Vertex_Shader_vs_main( VS2_INPUT Input )
{
   VS2_OUTPUT Output;
   
   float cosTime = gWaveHeight * cos(gTime * gSpeed + Input.mUV.x * gWaveFrequency);
   float cosTime2 = gWaveHeight * cos(gTime * gSpeed + Input.mUV.y * gWaveFrequency);

   Input.mPosition.y += cosTime + cosTime2;
   

   Output.mPosition = mul( Input.mPosition, gWorldMatrix );

   float3 lightDir = Output.mPosition.xyz - gWorldLightPosition.xyz;
   lightDir = normalize(lightDir);
   
   //float3 d = float(3)

   float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;
   
   Output.mPosition = mul( Output.mPosition, gViewMatrix );
   Output.mPosition = mul( Output.mPosition, gProjectionMatrix );
   
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   worldNormal = normalize(worldNormal);

   Output.mDiffuse = dot(-lightDir, worldNormal);
   Output.mReflection = reflect(lightDir, worldNormal);

   Output.mUV = Input.mUV + float2(gTime * gUVSpeed, 0);
   
   return Output;
}

struct PS1_INPUT
{
   float2 mUV : TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 mReflection: TEXCOORD3;
};

texture DiffuseMap_Tex;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};
texture SpecularMap_Tex;
sampler2D SpecularSampler = sampler_state
{
   Texture = (SpecularMap_Tex);
};

float3 gLightColor;
float4 WaveShader_Pass_1_Pixel_Shader_ps_main(PS1_INPUT Input) : COLOR
{
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   float3 diffuse = gLightColor * albedo.rgb * saturate(Input.mDiffuse);
   
   float3 reflection = normalize(Input.mReflection);
   float3 viewDir = normalize(Input.mViewDir); 
   float3 specular = 0;
   if ( diffuse.x > 0 )
   {
      specular = saturate(dot(reflection, -viewDir ));
      specular = pow(specular, 20.0f);
      
      float4 specularIntensity  = tex2D(SpecularSampler, Input.mUV);
      specular *= specularIntensity.rgb * gLightColor;
   }

   float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo;
   
   return float4(ambient + diffuse + specular, gTransparent);
}





technique Shader
{
	pass Pass_0
	{
		PixelShader = compile ps_2_0 main_0();
	}
};