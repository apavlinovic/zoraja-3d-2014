
#pragma once

//	MeshBase.h: Defining an abstract representation of triangle lists 

#include "pch.h"

#include "..\Components\VertexBuffer.h"
#include "..\Components\IndexBuffer.h"

#include "..\Common\DirectXHelper.h"

namespace App1 {

	template <typename T, typename U> class MeshBase {

	public:
		MeshBase() : _vertexbuffer{ nullptr }, _indexbuffer{ nullptr }, _indexed{ false } { }

		concurrency::task<void> CreateAsync(_In_ ID3D11Device1* device, std::vector<T>& vertices, std::vector<U>& indices,
			D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		{
			DebugPrint("\t MeshBase<" + std::string(typeid(T).name()) + "," + std::string(typeid(U).name()) + ">::CreateAsync() ...\n");
			DebugPrint("\t\t Primitive Topology: " + ToString(topology) + "\n");

			_topology = topology;
			_vertexcount = (unsigned) vertices.size();

			return concurrency::create_task([this, device, vertices, indices]()
			{
				DebugPrint("---- A Lambda:: Creating a VB and an IB ...\n");

				_vertexbuffer = std::make_shared<VertexBuffer<T>>(device, &vertices[0], _vertexcount);

				if (!indices.empty()) {
					_indexed = true;

					_indexcount = (unsigned) indices.size();
					_indexbuffer = std::make_shared<IndexBuffer<U>>(device, (void*) (&indices[0]), _indexcount);

					if (typeid(U) == typeid (unsigned)) _format = DXGI_FORMAT_R32_UINT;
					else _format = DXGI_FORMAT_R16_UINT;
				}
			});
		}

		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device1* device) = 0;

		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device1* device, const std::wstring& filename) = 0;

		virtual void BindVertexBuffer(_In_ ID3D11DeviceContext1* context, int slot = 0, unsigned count = 1, unsigned offset = 0)
		{
			//DebugPrint("\t MeshBase<" + string(typeid(T).name()) + "," + string(typeid(U).name()) + ">::BindVertexBuffer() ...\n");

			_vertexbuffer->Bind(context, slot, count, offset);
			context->IASetPrimitiveTopology(_topology);
		}

		virtual void BindIndexBuffer(_In_ ID3D11DeviceContext1* context, unsigned offset = 0)
		{
			//DebugPrint("\t MeshBase<" + string(typeid(T).name()) + "," + string(typeid(U).name()) + ">::BindIndexBuffer() ...\n");

			if (_indexed) _indexbuffer->Bind(context, _format, offset);
		}

		virtual void Draw(_In_ ID3D11DeviceContext1* context, unsigned start = 0)
		{
			context->Draw(_vertexcount, start);
		}

		virtual void DrawIndexed(_In_ ID3D11DeviceContext1* context, unsigned startindex = 0, unsigned startvertex = 0)
		{
			if (_indexed) context->DrawIndexed(_indexcount, startindex, startvertex);
		}

		void Reset()
		{
			_vertexbuffer->Reset();
			_indexbuffer->Reset();
		}

	protected:
		unsigned _vertexcount;
		std::shared_ptr<VertexBuffer<T>> _vertexbuffer;

		bool _indexed;
		unsigned _indexcount;
		std::shared_ptr<IndexBuffer<U> > _indexbuffer;
		DXGI_FORMAT _format;

		D3D11_PRIMITIVE_TOPOLOGY _topology;
	};

	inline std::string ToString(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		switch (topology) {

		default: return "What a #%@$";

		case D3D_PRIMITIVE_TOPOLOGY_UNDEFINED: return "D3D_PRIMITIVE_TOPOLOGY_UNDEFINED";

		case D3D_PRIMITIVE_TOPOLOGY_POINTLIST: return "D3D_PRIMITIVE_TOPOLOGY_POINTLIST";
		case D3D_PRIMITIVE_TOPOLOGY_LINELIST: return "D3D_PRIMITIVE_TOPOLOGY_LINELIST";
		case D3D_PRIMITIVE_TOPOLOGY_LINESTRIP: return "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP";

		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST: return "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST";
		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP: return "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP";

			// Add the rest ...  

		}
	}

}