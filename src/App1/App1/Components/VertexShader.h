
#pragma once

//	VertexShader.h: Encapsulating a vertex shader object and an input layout object

#include "pch.h"

#include "ShaderBase.h"
#include "..\Common\DirectXHelper.h"

namespace App1 {

	template <typename T>
	class VertexShader : public ShaderBase  {

	public:
		VertexShader() : _shader{ nullptr }, _layout{ nullptr } { }

		concurrency::task<void> CreateAsync(ID3D11Device1* device, const std::wstring& filename) override
		{
			DebugPrint("\t VertexShader<" + std::string(typeid(T).name()) + ">::CreateAsync() ...\n");

			return concurrency::create_task(DX::ReadDataAsync(filename)).then([this, device](const std::vector<byte> data)
			{
				DebugPrint("\t A Lambda: Creating a VS and an IL ... \n");

				DX::ThrowIfFailed(device->CreateVertexShader(&data[0], data.size(), nullptr, &_shader));

				DX::ThrowIfFailed(device->CreateInputLayout(T::_elements, T::_count, &data[0], data.size(), &_layout));
			});
		}

		virtual void Bind(ID3D11DeviceContext1* context, ID3D11ClassInstance *const *instances = nullptr, unsigned count = 0) override
		{
			//DebugPrint("\t VertexShader<" + std::string(typeid(T).name()) + ">::Bind() ...\n");

			context->VSSetShader(_shader.Get(), instances, count);
			context->IASetInputLayout(_layout.Get());
		}

		void Reset()
		{
			_shader.Reset();
			_layout.Reset();
		}

		virtual ~VertexShader() {}

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> _shader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> _layout;
	};

}
