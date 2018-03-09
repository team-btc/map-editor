//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// TextureMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
texture Heightmap_Tex;
texture Normalmap_Tex;

sampler2D HeightSampler = sampler_state
{
   Texture = (Heightmap_Tex);
};

sampler2D NormalSampler = sampler_state
{
    Texture = (Normalmap_Tex);
};

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;
//float4x4 gDirLightMatrix;

struct VS_INPUT
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0;
   //float3 mNormal : NORMAL;
   //float3 mTangent : TANGENT;
   //float3 mBinormal : BINORMAL;
};

struct VS_OUTPUT
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0;
   //float3 mLightDir : TEXCOORD1;
   //float3 mViewDir : TEXCOORD2;
   //float3 T : TEXCOORD3;
   //float3 B : TEXCOORD4;
   //float3 N : TEXCOORD5;
};


VS_OUTPUT TextureMapping_Pass_0_Vertex_Shader_vs_main(VS_INPUT Input)
{
   VS_OUTPUT Output;
   float4 h = tex2Dlod(HeightSampler, float4(Input.mTexCoord.x, Input.mTexCoord.y, 0, 0));
   Output.mPosition = mul(Input.mPosition, gWorldMatrix);
   Output.mPosition.y += (h.r + h.g + h.b) / 3.0f * 255.0f - 128.0f;
   Output.mPosition = mul(Output.mPosition, gViewMatrix);
   Output.mPosition = mul(Output.mPosition, gProjectionMatrix);
   Output.mTexCoord = Input.mTexCoord;

   //float4 worldPosition = mul( Input.mPosition, gWorldMatrix );
   //float3 lightDir = worldPosition.xyz - gWorldLightPosition.xyz;
   //Output.mLightDir = normalize(lightDir);
   //
   //float3 viewDir = normalize(worldPosition.xyz - gWorldCameraPosition.xyz);
   //Output.mViewDir = viewDir;
   //
   //float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   //Output.N = normalize(worldNormal);
   //
   //float3 worldTangent = mul(Input.mTangent, (float3x3)gWorldMatrix );
   //Output.T = normalize(worldTangent);
   //
   //float3 worldBinormal = mul(Input.mBinormal, (float3x3)gWorldMatrix );
   //Output.B = normalize(worldBinormal);
   
   return Output;
}
texture DiffuseMap_Tex
<
   string ResourceName = ".\\Earth.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

sampler2D TextureMapping_Pass_0_Pixel_Shader_HeightSampler;
struct PS_INPUT
{
   float2 mTexCoord : TEXCOORD0;
};

float4 TextureMapping_Pass_0_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR
{
   float4 albedo = tex2D(DiffuseSampler, Input.mTexCoord);
   return albedo.rgba;

   //float3 tangentNormal = tex2D(NormalSampler, Input.mUV).xyz;
   //tangentNormal = normalize(tangentNormal * 2 - 1);
   //
   //float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   //TBN = transpose(TBN);
   //float3 wolrdNormal = mul(TBN, tangentNormal);
   //
   //float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   //float3 lightDir = normalize(Input.mLightDir);
   //float3 diffuse = saturate(dot(wolrdNormal, -lightDir));
   //diffuse = gLightColor * albedo.rgb * diffuse;
   //
   //float3 specular = 0;
   //if ( diffuse.x > 0 )
   //{
   //   float3 reflection = reflect(lightDir, wolrdNormal);
   //   float3 viewDir = normalize(Input.mViewDir); 

   //   specular = saturate(dot(reflection, -viewDir ));
   //   specular = pow(specular, 20.0f);
   //   
   //   float4 specularIntensity  = tex2D(SpecularSampler, Input.mUV);
   //   specular *= specularIntensity.rgb * gLightColor;
   //}

   //float3 ambient = float3(0.1f, 0.1f, 0.1f);
   //
   //return float4(ambient + diffuse + specular, 1);
}

//--------------------------------------------------------------//
// Technique Section for TextureMapping
//--------------------------------------------------------------//
technique TextureMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 TextureMapping_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 TextureMapping_Pass_0_Pixel_Shader_ps_main();
   }

}

