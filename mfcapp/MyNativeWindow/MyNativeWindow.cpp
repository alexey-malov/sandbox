#include "GenericWindow.h"
#include <memory>

using namespace std;

// Program entry point function.
int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       /*nCmdShow*/) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	auto wnd = make_unique<CGenericWindow>(hInstance, L"Hello", 0, 0, 1024, 768);
	wnd->DoOnDestroy([]{
		PostQuitMessage(0);
	});

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}