#pragma once

namespace App1
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
	};

	struct ViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	struct VertexPositionColor {

		VertexPositionColor() { }

		VertexPositionColor(DirectX::XMFLOAT3 const& position, DirectX::XMFLOAT3 const& color)
			: _position{ position }, _color{ color }
		{ }

		VertexPositionColor(DirectX::FXMVECTOR position, DirectX::FXMVECTOR color)
		{
			DirectX::XMStoreFloat3(&_position, position);
			DirectX::XMStoreFloat3(&_color, color);
		}

		DirectX::XMFLOAT3 _position;
		DirectX::XMFLOAT3 _color;

		static const int _count = 2;
		static const D3D11_INPUT_ELEMENT_DESC _elements[_count];
	};
}