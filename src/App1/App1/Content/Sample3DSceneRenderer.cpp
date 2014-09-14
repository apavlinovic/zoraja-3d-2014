#include "pch.h"
#include "Sample3DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"

#include "..\Components\Cubes.h"

using namespace App1;

using namespace DirectX;
using namespace Windows::Foundation;

using namespace std;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_degreesPerSecond(45),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	DebugPrint("\t Sample3DSceneRenderer::Ctor() ... \n");

	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	DebugPrint("\t Sample3DSceneRenderer::CreateWindowSizeDependentResources() ... \n");

	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	if (aspectRatio < 1.0f) { fovAngleY *= 2.0f; }

	_camera = make_shared<FixedCameraRH>(m_deviceResources->GetD3DDevice());

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	_camera->SetProjection(orientationMatrix, fovAngleY, aspectRatio, 0.01f, 100.0f);

	static const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	_camera->SetView(eye, at, up);
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		Rotate(radians);
	}
}

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
	// Prepare to pass the updated model matrix to the shader
	_actor->RotateY(radians);
}

void Sample3DSceneRenderer::StartTracking()
{
	DebugPrint("\t Sample3DSceneRenderer::StartTrecking() ... \n");

	m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
	}
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	_vertexshader->Bind(context);
	_pixelshader->Bind(context);

	_actor->Update(context);
	_actor->GetConstantBuffer()->Bind(context, ShaderBase::VertexShaderStage, 0);
	_actor->GetMesh()->BindVertexBuffer(context);
	_actor->GetMesh()->BindIndexBuffer(context);

	_camera->Update(context);
	_camera->GetConstantBuffer()->Bind(context, ShaderBase::VertexShaderStage, 1);

	_actor->GetMesh()->DrawIndexed(context);
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
{
	DebugPrint("\t Sample3DSceneRenderer::CreateDeviceDependentResources() ... \n");

	auto device = m_deviceResources->GetD3DDevice();

	_vertexshader = make_shared<VertexShader<VertexPositionColor>>();
	_pixelshader = make_shared<PixelShader>();

	auto vstask = _vertexshader->CreateAsync(device, L"SampleVertexShader.cso");

	auto pstask = _pixelshader->CreateAsync(device, L"SamplePixelShader.cso");

	std::shared_ptr<Cube<VertexPositionColor, unsigned short>> mesh = make_shared<Cube<VertexPositionColor, unsigned short>>();
	auto meshtask = mesh->CreateAsync(device);

	(vstask && pstask && meshtask).then([this] () {
		m_loadingComplete = true;
		DebugPrint("\t A Lambda: Loading is complete! \n");
	});

	_actor = make_shared<Actor<VertexPositionColor, unsigned short>>(device, mesh);
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;

	_vertexshader->Reset();
	_pixelshader->Reset();
	_actor->Reset();
	_camera->Reset();
}