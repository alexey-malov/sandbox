#pragma once

#include <windows.h>
#include <functional>

class CGenericWindow
{
public:
	CGenericWindow(HINSTANCE hInstance, LPCWSTR windowTitle, int x, int y, int w, int h, HWND hParent = nullptr);
	~CGenericWindow();
	CGenericWindow(const CGenericWindow&) = delete;
	CGenericWindow& operator=(const CGenericWindow&) = delete;
	void DoOnDestroy(const std::function<void()> & onDestroy);
private:
	void Create(LPCWSTR windowTitle, int x, int y, int w, int h, HWND hParent);
	static void RegisterWndClass(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
		LPARAM lParam);
	static bool m_registered;

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	static const WCHAR m_wndClassName[];

	std::function<void()> m_onDestroy;
};

