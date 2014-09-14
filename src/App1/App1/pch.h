#pragma once

#include <wrl.h>
#include <wrl/client.h>
#include <d3d11_2.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include <concrt.h>

#include <ppltasks.h>

#include <string>

#if defined (_DEBUG)

template<typename... Args>
inline void DebugPrint(Platform::String^ text, Args... args)
{
	auto data = std::wstring(text->Data());
	OutputDebugStringW(data.c_str());
}

template<typename... Args>
inline void DebugPrint(const std::wstring& text, Args... args)
{
	OutputDebugStringW(text.c_str());
}

template<typename... Args>
inline void DebugPrint(const std::string& text, Args... args)
{
	OutputDebugStringA(text.c_str());
}

#else

#define DebugPrint(x);

#endif