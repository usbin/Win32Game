
//--------------------------------------------------------------------------------------
// GLOBAL
//--------------------------------------------------------------------------------------
SamplerState samLinear;
Texture2D txDiffuse;
cbuffer ChangeOnResizeBuffer
{
    matrix projection;
};
cbuffer ChangeOnRenderBuffer
{
    float4 mesh_color : SV_TARGET;
    int use_texture;
};
//--------------------------------------------------------------------------------------
// Vertex Input Type
//--------------------------------------------------------------------------------------
struct VertexInputType
{
    float4 position : POSITION;
    float2 texture_position: TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Pixel Input Type
//--------------------------------------------------------------------------------------
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 texture_position: TEXCOORD;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PixelInputType VS( VertexInputType input )
{
    PixelInputType output = input;
    output.position = mul(output.position,projection);
    output.position.x = (-1.0 + output.position.x); //(-1, 1)의 x축을 (0, 1)로 변경
    output.position.y = (1.0 - output.position.y); //(1, -1)의 y축을 (0, 1)로 변경(x축 반전)
    output.texture_position = input.texture_position;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PixelInputType input) : SV_Target
{
    if(use_texture){
        return txDiffuse.Sample(samLinear, input.texture_position);
    }
    else{
        return mesh_color;
    }
}
