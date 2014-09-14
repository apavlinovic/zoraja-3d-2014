
#pragma once

//	PixelShader.h: Encapsualting a pixel shader object

#include "pch.h"

#include "ShaderBase.h"
#include "..\Common\DirectXHelper.h"

namespace App1 {

	class PixelShader : public ShaderBase  {

	public:
		PixelShader() : _shader{ nullptr } { }

		concurrency::task<void> CreateAsync(ID3D11Device1* device, const std::wstring& filename) override
		{
			DebugPrint("\t PixelShader::CreateAsync() ...\n");

			return concurrency::create_task(DX::ReadDataAsync(filename)).then([this, device](const std::vector<byte> data) {

				DebugPrint("\t A Lambda: Creating a PS ... \n");

				DX::ThrowIfFailed(device->CreatePixelShader(&data[0], data.size(), nullptr, &_shader));
			});
		}

		virtual void Bind(ID3D11DeviceContext1* context, ID3D11ClassInstance *const *instances = nullptr, unsigned count = 0) override
		{
			//DebugPrint("\t PixelShader::Bind() ...\n");

			context->PSSetShader(_shader.Get(), instances, count);
		}

		void Reset() { _shader.Reset(); }

		virtual ~PixelShader() {}

	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _shader;
	};
}

