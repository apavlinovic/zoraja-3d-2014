
#pragma once

//	Index Buffer.h: Encapsulating an index buffer object

#include "pch.h"

#include "BufferBase.h"

namespace App1 {

	template <typename T>
	class IndexBuffer : public BufferBase {

	public:
		explicit IndexBuffer(_In_ ID3D11Device1 *device, void* indices, int count,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			unsigned access = 0,
			unsigned flags = 0,
			unsigned stride = 0) : _indexsize{ sizeof (T) }, BufferBase{ sizeof (T) * count }
		{
			DebugPrint("\t IndexBuffer<" + std::string(typeid(T).name()) + ">::Ctor ...\n");
			DebugPrint("\t\t Index Size: " + std::to_string(sizeof(T)) + "\n");
			DebugPrint("\t\t Index Count: " + std::to_string(count) + "\n");
			DebugPrint("\t\t Buffer Size: " + std::to_string(_size) + "\n");

			CD3D11_BUFFER_DESC desc(_size, D3D11_BIND_INDEX_BUFFER, usage, access, flags, stride);

			D3D11_SUBRESOURCE_DATA data = { 0 };
			data.pSysMem = indices;

			DX::ThrowIfFailed(device->CreateBuffer(&desc, &data, _buffer.ReleaseAndGetAddressOf()));
		}

		void Bind(_In_ ID3D11DeviceContext1* context, DXGI_FORMAT format = DXGI_FORMAT_R16_UINT, unsigned offset = 0)
		{
			//DebugPrint("\t IndexBuffer<" + std::string(typeid(T).name()) + ">::Bind() ...\n");
			context->IASetIndexBuffer(_buffer.Get(), format, offset);
		}

	private:
		unsigned _indexsize;
	};
}
