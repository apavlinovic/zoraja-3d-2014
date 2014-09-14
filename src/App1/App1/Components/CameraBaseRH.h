
#pragma once

//	CameraBase.h: Basic camera features are view and projection matrices

#include "pch.h"

#include "ConstantBuffer.h"

namespace App1 {

	class CameraBaseRH {

	public:
		struct Transfer {
			DirectX::XMFLOAT4X4 view;
			DirectX::XMFLOAT4X4 projection;
		};

		CameraBaseRH(_In_ ID3D11Device1* device) : _buffer{ device } { }

		void SetView(DirectX::FXMVECTOR eye, DirectX::FXMVECTOR at, DirectX::FXMVECTOR up) 
		{
			DirectX::XMStoreFloat4x4(&_transfer.view, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtRH(eye, at, up)));
		}

		void SetProjection(DirectX::CXMMATRIX orientation, float fov, float aspect, float zn, float zf)
		{
			DirectX::XMMATRIX perspective = DirectX::XMMatrixPerspectiveFovRH(fov, aspect, zn, zf);

			DirectX::XMStoreFloat4x4(&_transfer.projection, DirectX::XMMatrixTranspose(perspective * orientation));
		}

		void Update(_In_ ID3D11DeviceContext1* context)
		{
			_buffer.Update(context, _transfer);
		}

		ConstantBuffer<Transfer>* GetConstantBuffer() { return &_buffer; }

		void Reset() { _buffer.Reset(); }

		virtual ~CameraBaseRH() {}

	private:
		ConstantBuffer<Transfer> _buffer;
		struct Transfer _transfer;
	};

}