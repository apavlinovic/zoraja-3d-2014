
#pragma once

//	ShaderBase.h: A base class for shader objects

#include "pch.h"

namespace App1 {

	class ShaderBase  {

	public:
		enum ProgrammableStages : byte { VertexShaderStage, HullShaderStage, DomainShaderStage, GeometryShaderStage, PixelShaderStage, ComputeShaderStage, NumShadersStages };

		ShaderBase() {}

		virtual concurrency::task<void> CreateAsync(ID3D11Device1* device, const std::wstring& filename) = 0;

		virtual void Bind(ID3D11DeviceContext1* context, ID3D11ClassInstance* const* instances, unsigned count) = 0;

		virtual void Reset() = 0;

		virtual ~ShaderBase() {}
	};

}