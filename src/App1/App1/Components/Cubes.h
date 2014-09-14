
#pragma once

//	Cubes.h: Defining cubes 

#include "pch.h"

#include "Content\ShaderStructures.h"
#include "MeshBase.h"

namespace App1 {

	// The root template for all cube specializations
	template <typename T, typename U> class Cube : public MeshBase<T, U> { };

	template <>
	class Cube<VertexPositionColor, unsigned short> : public MeshBase<VertexPositionColor, unsigned short>{

	public:
		Cube() {}

		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device1* device) override
		{
			DebugPrint("\t Cube<VertexPositionColor, unsigned>::CreateAsync() ...\n");

			std::vector<VertexPositionColor> vertices = {
				VertexPositionColor{ DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f) },
				VertexPositionColor{ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) },
				VertexPositionColor{ DirectX::XMFLOAT3(-0.5f, 0.5f, -0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) },
				VertexPositionColor{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 1.0f) },
				VertexPositionColor{ DirectX::XMFLOAT3(0.5f, -0.5f, -0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) },
				VertexPositionColor{ DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f) },
				VertexPositionColor{ DirectX::XMFLOAT3(0.5f, 0.5f, -0.5f), DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f) },
				VertexPositionColor{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) },
			};

			std::vector<unsigned short> indices = {
				0, 2, 1, // -x
				1, 2, 3,

				4, 5, 6, // +x
				5, 7, 6,

				0, 1, 5, // -y
				0, 5, 4,

				2, 6, 7, // +y
				2, 7, 3,

				0, 4, 6, // -z
				0, 6, 2,

				1, 3, 7, // +z
				1, 7, 5,
			};

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device1* device, const std::wstring&) override
		{
			DebugPrint("\t Cube<VertexPositionColor, unsigned>::CreateAsync() ...\n");

			std::vector<VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Here, you can load your mesh from a file 

			return MeshBase::CreateAsync(device, vertices, indices);
		}

	};

}