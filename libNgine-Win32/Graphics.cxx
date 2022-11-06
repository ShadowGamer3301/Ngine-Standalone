#include "Graphics.hxx"
#include "Exception.hxx"
#include <vector>
#include <spdlog/spdlog.h>

Ngine::Graphics::Graphics(Ngine::Window& wnd)
{
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&m_pFactory));
	if (FAILED(hr))
		throw Ngine::Exception(__LINE__, __FILE__, "Failed to create DXGI factory");

	InitializePipeline(wnd);
}

Ngine::Graphics::~Graphics()
{

}

void Ngine::Graphics::Render()
{
	float ClearColor[4] = { 0.0, 0.4, 0.6, 1.0 };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

	m_pSwapChain->Present(0, 0);
}

void Ngine::Graphics::InitializePipeline(Ngine::Window& wnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = wnd.width;
	sd.BufferDesc.Height = wnd.height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.OutputWindow = wnd.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	D3D_FEATURE_LEVEL featurelevellist[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	D3D_FEATURE_LEVEL fLevel = D3D_FEATURE_LEVEL_11_0;
	UINT fLevelListSize = ARRAYSIZE(featurelevellist);

	//Retrieve default graphics adapter
	IDXGIAdapter* default_adapter = FetchGraphicsAdapter();

	//Initialize device and swapchain
	HRESULT hr = D3D11CreateDeviceAndSwapChain(default_adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, 0, featurelevellist, fLevelListSize, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);
	if (FAILED(hr))
		throw Ngine::Exception(__LINE__, __FILE__, "Failed to create D3D11 device and/or swapchain");

	//Create back buffer
	ID3D11Texture2D* pBB;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBB);
	if (FAILED(hr))
		throw Ngine::Exception(__LINE__, __FILE__, "Failed to retrieve buffer");

	//Create RTV
	hr = m_pDevice->CreateRenderTargetView(pBB, NULL, &m_pRenderTargetView);
	pBB->Release();
	if (FAILED(hr))
		throw Ngine::Exception(__LINE__, __FILE__, "Failed to create D3D11 render target view");

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	//Set viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)wnd.width;
	vp.Height = (FLOAT)wnd.height;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.MinDepth = 0.0f;
	m_pDeviceContext->RSSetViewports(1, &vp);
}

IDXGIAdapter* Ngine::Graphics::FetchGraphicsAdapter()
{
	//List all avaliable adapters
	UINT i = 0;
	IDXGIAdapter* adapter;
	std::vector<IDXGIAdapter*> adapterlist;
	for (i = 0; m_pFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++)
	{
		DXGI_ADAPTER_DESC dsc;
		adapter->GetDesc(&dsc);

		std::wstring wdevname = dsc.Description;
		std::string devname(wdevname.begin(), wdevname.end());

		spdlog::info("Adapter found: {}", devname);
		adapterlist.push_back(adapter);
	}

	//Print to console the name of adapter
	DXGI_ADAPTER_DESC dsc;
	adapterlist[0]->GetDesc(&dsc);
	std::wstring wdevname = dsc.Description;
	std::string devname(wdevname.begin(), wdevname.end());
	spdlog::info("Selected adapter: {}", devname);

	//For now just return the first adapter that was found
	//Some better sorting will be added later
	return adapterlist[0];
}
