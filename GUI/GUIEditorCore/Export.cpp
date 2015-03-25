#include <RfCore.h>
#include "EditorApp.h"

#define APIENTRY __stdcall

#pragma warning(disable:4996)	// freopen

using namespace RenderFish;

extern "C"
{
	__declspec(dllexport) void* APIENTRY Create(void* native_wnd)
	{
		// add console
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);

		// before others
		Debug::init();

		EditorApp* core = new EditorApp(static_cast<HWND>(native_wnd));
		if (!core->Init())
			return 0;
		return core;
	}

	__declspec(dllexport) void APIENTRY Destroy(EditorApp* core)
	{
		if (core != nullptr)
		{
			delete core;
			core = nullptr;
		}
	}

	__declspec(dllexport) void APIENTRY Refresh(EditorApp* core)
	{
		core->DrawScene();
	}

	__declspec(dllexport) void APIENTRY Resize(EditorApp* core, unsigned int width, unsigned int height)
	{
		core->OnResize(width, height);
	}
}