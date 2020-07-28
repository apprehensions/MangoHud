#include "kiero.h"
#include "windows.h"
#include <iostream>

#if KIERO_INCLUDE_D3D9
# include "d3d9_impl.h"
#endif

#if KIERO_INCLUDE_D3D10
# include "impl/d3d10_impl.h"
#endif

#if KIERO_INCLUDE_D3D11
# include "d3d11_impl.h"
#endif

#if KIERO_INCLUDE_D3D12
# include "d3d12_impl.h"
#endif

#if KIERO_INCLUDE_OPENGL
#endif

#if KIERO_INCLUDE_VULKAN
#endif

#if !KIERO_USE_MINHOOK
# error "The example requires that minhook be enabled!"
#endif

#include <windows.h>

void ConsoleSetup()
{
	// With this trick we'll be able to print content to the console, and if we have luck we could get information printed by the game.
	AllocConsole();
	SetConsoleTitle("MangoHud");
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
}

int kieroExampleThread()
{
    ConsoleSetup();
    if (kiero::init(kiero::RenderType::Auto) == kiero::Status::Success)
    {
        switch (kiero::getRenderType())
        {
#if KIERO_INCLUDE_D3D9
        case kiero::RenderType::D3D9:
            impl::d3d9::init();
            break;
#endif
#if KIERO_INCLUDE_D3D10
        case kiero::RenderType::D3D10:
            impl::d3d10::init();
            break;
#endif
#if KIERO_INCLUDE_D3D11
        case kiero::RenderType::D3D11:
            impl::d3d11::init();
            break;
#endif
#if KIERO_INCLUDE_D3D12
        case kiero::RenderType::D3D12:
            impl::d3d12::init();
            break;
#endif
        case kiero::RenderType::OpenGL:
            // TODO: OpenGL implementation?
            break;
        case kiero::RenderType::Vulkan:
            // TODO: Vulcan implementation?
            break;
        }

        return 1;
    }
	return 0;
}

void kieroShutdownThread()
{
    switch (kiero::getRenderType())
    {
#if KIERO_INCLUDE_D3D9
    case kiero::RenderType::D3D9:
        //impl::d3d9::uninit();
        break;
#endif
#if KIERO_INCLUDE_D3D10
    case kiero::RenderType::D3D10:
        impl::d3d10::uninit();
        break;
#endif
#if KIERO_INCLUDE_D3D11
    case kiero::RenderType::D3D11:
        //impl::d3d11::uninit();
        break;
#endif
#if KIERO_INCLUDE_D3D12
    case kiero::RenderType::D3D12:
        impl::d3d12::uninit();
        break;
#endif
    case kiero::RenderType::OpenGL:
        // TODO: OpenGL implementation?
        break;
    case kiero::RenderType::Vulkan:
        // TODO: Vulcan implementation?
        break;
    }
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
    
    DisableThreadLibraryCalls(hInstance);

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)kieroExampleThread, NULL, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        kieroShutdownThread();
        break;
    }

    return TRUE;
}
