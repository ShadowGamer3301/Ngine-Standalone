#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <optional>
#include <memory>
#include "Macro.hxx"

namespace Ngine {
	class NAPI Window {
	friend class Graphics;

	private:
		class NAPI WindowClass {
		public:
			static const wchar_t* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const wchar_t* wndClassName = L"Ngine Window";
			static WindowClass wndClass;
			HINSTANCE hInst;
		};
	
	public:
		Window(unsigned int width, unsigned int height, wchar_t* name);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		static std::optional<int> ProcessMessage() noexcept;
		inline HWND GetWindowHandler() const noexcept { return hWnd; }

	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

		int width;
		int height;
		HWND hWnd;
	};
}