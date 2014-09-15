// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
	float  angle : TRANSFORM0;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;

	const float angle = input.angle;

	float cosLength, sinLength;
	sincos(angle, sinLength, cosLength);

	float3x3 xAxisRotation = { 
		1.0, 0.0, 0.0,
		0.0, cosLength, -sinLength,
		0.0, sinLength, cosLength };

	float3 temporaryPos = mul(input.pos, xAxisRotation);

	float4 pos = float4(temporaryPos, 1.0f);

	// Transform the vertex position into projected space.
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// Pass the color through without modification.
	output.color = input.color;

	return output;
}
