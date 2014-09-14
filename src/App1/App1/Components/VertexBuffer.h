
#pragma once

//	VertexBuffer.h: Encapsulating a vertex buffer object

#include "pch.h"

#include "BufferBase.h"

namespace App1 {

	template <typename T>
	class VertexBuffer : public BufferBase {

	public:
		explicit VertexBuffer(_In_ ID3D11Device1* device, const T* vertices, int count,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			unsigned access = 0,
			unsigned flags = 0,
			unsigned stride = 0) : _vertexsize{ sizeof (T) }, BufferBase{ sizeof (T) * count }
		{
			DebugPrint("\t VertexBuffer<" + std::string(typeid(T).name()) + ">::Ctor ...\n");
			DebugPrint("\t\t Vertex Size: " + std::to_string(_vertexsize) + "\n");
			DebugPrint("\t\t Vertex Count: " + std::to_string(count) + "\n");
			DebugPrint("\t\t Buffer Size: " + std::to_string(_size) + "\n");

			CD3D11_BUFFER_DESC desc(_size, D3D11_BIND_VERTEX_BUFFER, usage, access, flags, stride);

			D3D11_SUBRESOURCE_DATA data = { 0 };
			data.pSysMem = vertices;

			DX::ThrowIfFailed(device->CreateBuffer(&desc, &data, &_buffer));
		}

		void Bind(_In_ ID3D11DeviceContext1* context, unsigned slot = 0, unsigned count = 1, const unsigned offset = 0)
		{
			//DebugPrint("\t VertexBuffer<" + std::string(typeid(T).name()) + ">::Bind() ...\n");
			context->IASetVertexBuffers(slot, count, _buffer.GetAddressOf(), &_vertexsize, &offset);
		}

	private:
		unsigned _vertexsize;
	};
}
