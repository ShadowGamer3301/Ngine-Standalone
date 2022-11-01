#include "Window.hxx"
#include "Exception.hxx"

Ngine::Window::WindowClass Ngine::Window::WindowClass::wndClass;

#pragma region WindowClass

const char* Ngine::Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Ngine::Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

Ngine::Window::WindowClass::WindowClass() noexcept
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = Window::HandleMsgSetup;
	wcex.lpszClassName = WindowClass::GetName();
	wcex.hInstance = WindowClass::GetInstance();
	wcex.hIcon = nullptr;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hIconSm = nullptr;
	wcex.lpszMenuName = nullptr;

	RegisterClassEx(&wcex);
}

Ngine::Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

#pragma endregion

#pragma region Window
Ngine::Window::Window(unsigned int width, unsigned int height, char* name) : width(width), height(height)
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
		throw Exception(__LINE__, __FILE__, "AdjustWindowRect() failed");

	hWnd = CreateWindow(WindowClass::GetName(), name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), this);

	if(!hWnd)
		throw Exception(__LINE__, __FILE__, "Could not create window");

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Ngine::Window::~Window()
{
	DestroyWindow(hWnd);
}

std::optional<int> Ngine::Window::ProcessMessage() noexcept
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return (int)msg.wParam;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

LRESULT Ngine::Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE) {
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Ngine::Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to window instance
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window instance handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Ngine::Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

#pragma endregion