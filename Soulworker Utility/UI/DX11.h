#pragma once

#define DIRECTX11 DX11::getInstance()
struct Texture {
	ID3D11ShaderResourceView* ptr = nullptr;
	int xSize = 0;
	int ySize = 0;
};
class DX11 : public Singleton<DX11> {
private:
	ID3D11Device* _d3dDevice;
	ID3D11DeviceContext* _d3dDeviceContext;
	unsigned int _4xMsaaQuality;
	bool _enable4xMsaa;
	std::array<std::string, 11> charTexturesFiles = { "Unknown.png","Haru.png","Erwin.png","Lily.png","Jin.png","Stella.png","Iris.png","Chii.png","Ephnel.png","Nabi.png","Dhana.png" };
	std::array<ID3D11ShaderResourceView*, 11> charTextures;
	bool CreateDevice();
	void Check4XMSAA();
	void CleanDevice();

public:
	DX11();
	~DX11();

	bool Init();

	IDXGISwapChain* CreateSwapChain(HWND hWnd);
	ID3D11RenderTargetView* CreateRenderTarget(IDXGISwapChain* swapChain);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv);
	Texture getcharacterTexture(int jobid);
};