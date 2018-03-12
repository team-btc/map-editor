
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

struct VS2_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;
   float2 mUV: TEXCOORD0;
};

struct VS2_OUTPUT 
{
   float4 mPosition : POSITION;
   float2 mUV: TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 mReflection: TEXCOORD3;
};

VS2_OUTPUT WaveShader_Pass_1_Vertex_Shader_vs_main( VS2_INPUT Input )
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




struct PS2_INPUT
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

float3 gLightColor
<
   string UIName = "gLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 0.70, 0.70, 1.00 );

float4 WaveShader_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
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

//--------------------------------------------------------------//
// Technique Section for WaveShader
//--------------------------------------------------------------//
technique WaveShader
{
   pass Pass_0
   {
      ALPHABLENDENABLE = TRUE;
      BLENDOP = ADD;
      DESTBLEND = INVSRCALPHA;
      SRCBLEND = BOTHINVSRCALPHA;
      // ZWRITEENABLE = TRUE;
      // CULLMODE = CW;
      // ZWRITEENABLE = FALSE;
      VertexShader = compile vs_2_0 WaveShader_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 WaveShader_Pass_0_Pixel_Shader_ps_main();
   }

}

