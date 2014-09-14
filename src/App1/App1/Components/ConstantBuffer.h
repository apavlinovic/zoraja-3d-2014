
#pragma once

//	ConstantBuffer.h: Encapsulating a constant buffer. Its size is multiple of 16 bytes

#include "pch.h"

#include "BufferBase.h"

namespace App1 {

	template <typename T>
	class ConstantBuffer : public BufferBase {

	public:
		explicit ConstantBuffer(_In_ ID3D11Device1* device,
			T* data = nullptr,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			unsigned access = 0,
			unsigned flags = 0,
			unsigned stride = 0) : BufferBase(16 * ((sizeof(T) +15) / 16))
		{
			DebugPrint("\t ConstantBuffer<" + std::string(typeid(T).name()) + ">::Ctor ...\n");
			DebugPrint("\t Buffer Size: " + std::to_string(_size) + "\n");

			data = nullptr;

			CD3D11_BUFFER_DESC desc(_size, D3D11_BIND_CONSTANT_BUFFER, usage, access, flags, stride);

			DX::ThrowIfFailed(device->CreateBuffer(&desc, nullptr, &_buffer));
		}

		void Bind(_In_ ID3D11DeviceContext1* context, unsigned shader, unsigned slot = 0, unsigned count = 1)
		{
			//DebugPrint("\t ConstantBuffer<" + std::string(typeid(T).name()) + ">::Bind() ...\n");

			//	A constant buffer can be bound to 6 pipeline locations
			if (shader == ShaderBase::VertexShaderStage) {
				context->VSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else if (shader == ShaderBase::PixelShaderStage) {
				context->PSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else
				return;
		}

		void Update(_In_ ID3D11DeviceContext1* context, const T& data, unsigned subresource = 0, const D3D11_BOX* box = nullptr, unsigned rawpitch = 0, unsigned depthpitch = 0)
		{
			//DebugPrint("\t ConstantBuffer<" + std::string(typeid(T).name()) + ">::Update() ...\n");
			context->UpdateSubresource(_buffer.Get(), subresource, box, &data, rawpitch, depthpitch);
		}
	};

}