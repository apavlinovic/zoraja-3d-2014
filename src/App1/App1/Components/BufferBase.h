
#pragma once

//	BufferBase.h: A base class for buffers

#include "pch.h"

namespace App1 {

	class BufferBase {

	public:
		BufferBase(unsigned size) : _buffer{ nullptr }, _size{ size } {}

		ID3D11Buffer* GetBuffer() { return _buffer.Get(); }

		void Reset() { _buffer.Reset(); }

		~BufferBase() {}

	protected:
		unsigned _size;
		Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
	};

}