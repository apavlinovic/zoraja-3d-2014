#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

#include "..\Components\VertexShader.h"
#include "..\Components\PixelShader.h"
#include "..\Components\Actor.h"
#include "..\Components\FixedCameraRH.h"

namespace App1
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }

	private:
		void Rotate(float radians);

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		std::shared_ptr<VertexShader<VertexPositionColor>> _vertexshader;
		std::shared_ptr<PixelShader> _pixelshader;

		std::shared_ptr<Actor<VertexPositionColor, unsigned short>> _actor;
		std::shared_ptr<FixedCameraRH> _camera;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;
	};
}

