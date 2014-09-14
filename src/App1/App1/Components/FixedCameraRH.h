
#pragma once

//	Fixed Camera.h: Defining a fixed camera in the scene

#include "pch.h"

#include "CameraBaseRH.h"

namespace App1 {

	class FixedCameraRH : public CameraBaseRH {

	public:
		FixedCameraRH(_In_ ID3D11Device1* device) : CameraBaseRH{ device } { DebugPrint("\t FixedCamera::Ctor ...\n"); }

		virtual ~FixedCameraRH() {}
	};

}