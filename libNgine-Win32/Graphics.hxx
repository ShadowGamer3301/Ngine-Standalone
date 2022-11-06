#pragma once
#include "Macro.hxx"
#include "Window.hxx"

#include <d3d11.h>
#include <wrl.h>

namespace Ngine {
	namespace wrl = Microsoft::WRL;

	class NAPI Graphics {

	public:
		Graphics(Ngine::Window& wnd);
		~Graphics();

		void Render();

	private:
		//Private methods
		void InitializePipeline(Ngine::Window& wnd);
		IDXGIAdapter* FetchGraphicsAdapter();

		//Private components
		wrl::ComPtr<ID3D11Device> m_pDevice;
		wrl::ComPtr<ID3D11DeviceContext> m_pDeviceContext;
		wrl::ComPtr<IDXGISwapChain> m_pSwapChain;
		ID3D11RenderTargetView* m_pRenderTargetView;
		wrl::ComPtr<IDXGIFactory1> m_pFactory;
	};
}