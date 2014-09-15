#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\MotionBlurRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace MotionBlur
{
	class MotionBlurMain : public DX::IDeviceNotify
	{
	public:
		MotionBlurMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~MotionBlurMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();
		void SetRotationSpeed(float degreesPerSecond);

		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		std::unique_ptr<MotionBlurRenderer> m_sceneRenderer;

		DX::StepTimer m_timer;
	};
}