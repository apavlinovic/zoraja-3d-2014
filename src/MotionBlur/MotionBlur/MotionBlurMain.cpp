#include "pch.h"
#include "MotionBlurMain.h"
#include "Common\DirectXHelper.h"

using namespace MotionBlur;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

MotionBlurMain::MotionBlurMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_deviceResources(deviceResources)
{
	m_deviceResources->RegisterDeviceNotify(this);

	m_sceneRenderer = std::unique_ptr<MotionBlurRenderer>(new MotionBlurRenderer(m_deviceResources));
}

MotionBlurMain::~MotionBlurMain()
{
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

void MotionBlurMain::CreateWindowSizeDependentResources() 
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

void MotionBlurMain::Update() 
{
	m_timer.Tick([&]()
	{
		m_sceneRenderer->Update(m_timer);
	});
}

bool MotionBlurMain::Render() 
{
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::Black);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_sceneRenderer->Render();

	return true;
}

void MotionBlurMain::SetRotationSpeed(float degreesPerSecond)
{
	m_sceneRenderer->SetRotationSpeed(degreesPerSecond);
}

void MotionBlurMain::OnDeviceLost()
{
	m_sceneRenderer->ReleaseDeviceDependentResources();
}

void MotionBlurMain::OnDeviceRestored()
{
	m_sceneRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}
