
#pragma once

//	Actor.h: Defining a basic actor in the scene encapsulating a mesh and a world matrix

#include "pch.h"

#include "ConstantBuffer.h"
#include "MeshBase.h"
#include "ShaderBase.h"

namespace App1 {

	template <typename T, typename U> class Actor {

	public:
		struct Transfer {
			DirectX::XMFLOAT4X4 world;
		};

	public:
		Actor(_In_ ID3D11Device1* device, const std::shared_ptr<MeshBase <T, U>>& mesh) : _mesh{ mesh }, _buffer{ device }
		{
			DebugPrint("\t Actor<" + std::string(typeid(T).name()) + ", " + std::string(typeid(U).name()) + ">::Ctor ...\n");
		}

		DirectX::XMFLOAT4X4 GetWorld() const { return _transfer.world; }

		void RotateY(float radians)
		{
			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(radians)));
		}

		MeshBase<T, U>* GetMesh() const { return _mesh.get(); }

		ConstantBuffer<Transfer>* GetConstantBuffer() { return &_buffer; }

		void Update(_In_ ID3D11DeviceContext1* context)
		{
			//DebugPrint("\t Actor<" + std::string(typeid(T).name()) + ", " + std::string(typeid(U).name()) + ">::Update() ...\n");

			_buffer.Update(context, _transfer);
		}

		void Reset()
		{
			_mesh->Reset();
			_buffer.Reset();
		}

	private:
		std::shared_ptr<MeshBase <T, U>> _mesh;

		ConstantBuffer<Transfer> _buffer;
		struct Transfer _transfer;
	};

}