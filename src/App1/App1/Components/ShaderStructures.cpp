
//	ShaderStructures.cpp: GPU byte mapping information

#include "pch.h"

#include "..\Content\ShaderStructures.h"

using namespace App1;

const D3D11_INPUT_ELEMENT_DESC VertexPositionColor::_elements[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};