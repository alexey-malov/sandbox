

#include "GenericWindow.h"

bool CGenericWindow::m_registered = false;;

const WCHAR CGenericWindow::m_wndClassName[] = L"CGenericWindowClassName";

CGenericWindow::CGenericWindow(HINSTANCE hInstance, LPCWSTR windowTitle, int x, int y, int w, int h, HWND hParent)
	:m_hInstance(hInstance)
{
	Create(windowTitle, x, y, w, h, hParent);
}


void CGenericWindow::DoOnDestroy(const std::function<void()> & onDestroy)
{
	m_onDestroy = onDestroy;
}

CGenericWindow::~CGenericWindow()
{
}

void CGenericWindow::Create(LPCWSTR windowTitle, int x, int y, int w, int h, HWND hParent)
{
	RegisterWndClass(m_hInstance);

	m_hWnd = CreateWindow(m_wndClassName, windowTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE, x, y, w, h, hParent, NULL, m_hInstance, this);

}

void CGenericWindow::RegisterWndClass(HINSTANCE hInstance)
{
	if (m_registered)
		return;

	WNDCLASSEX wcex = {0};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//#TODO: add icon if needed
	wcex.hIcon = nullptr; 
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //background_brush;
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCE(IDC_CEFCLIENT);
	wcex.lpszClassName = m_wndClassName; // TODO
	//#TODO: add icon if needed
	wcex.hIconSm = nullptr; //

	
	m_registered = RegisterClassEx(&wcex) != 0;
}

LRESULT CALLBACK CGenericWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE)
	{
		SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams));
	}
	auto self = reinterpret_cast<CGenericWindow*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
	if (self)
	{
		switch (message)
		{
		case WM_DESTROY:
			if (self->m_onDestroy)
			{
				self->m_onDestroy();
			}
			return 0;
		default:
			break;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


