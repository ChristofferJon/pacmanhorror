#include "D3DManager.h"

D3DManager::D3DManager()	:	mD3DDevice(NULL),
								mSwapChain(NULL),
								mRenderTargetView(NULL),
								pRS(0),
								mMenuEffect(NULL),
								mMenuLayout(0),
								mColorMap(NULL)
{
	mWidth = cfg->getCFG()->GetIntOfKey("RESX", "GFX", "Setup");
	mHeight = cfg->getCFG()->GetIntOfKey("RESY", "GFX", "Setup");
	
}


D3DManager::~D3DManager()
{
	if ( mRenderTargetView != NULL )
	{
		mRenderTargetView->Release();
		mRenderTargetView = NULL;
	}
	if ( mSwapChain != NULL )
	{
		mSwapChain->SetFullscreenState(FALSE, NULL);
		mSwapChain->Release();
		mSwapChain = NULL;
	}
	if ( mD3DDevice )		mD3DDevice->Release();
	if ( pRS )				
	{
		pRS->Release();
		pRS = NULL;
	}
}

bool D3DManager::Initialize(HWND* _hWnd, HINSTANCE _hInstance)
{
	// get window handle
	hWnd = _hWnd;
	hInstance = _hInstance;

	// set dimensions
	RECT rc;
	GetClientRect(*hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	// create device and swapchain
	if ( FAILED( CreateSwapChain( width, height ) ) )
		return dbg->getDbg()->fatalError(*hWnd, "Fatal error, shutting down");
	else dbg->getDbg()->print("D3D: %s\n", "Device succesfully created");

	// create shaders and effect pointers
	mMenuEffect = CreateFX("menuEffect.fx", mMenuEffect);
	if ( mMenuEffect == NULL)
		return dbg->getDbg()->fatalError(*hWnd, "Fatal error, shutting down");
	else dbg->getDbg()->print("D3D: %s\n", "Shaders succesfully created");

	mEffects.push_back( mMenuEffect );

	mMenuTechnique = mMenuEffect->GetTechniqueByName("SPRITE_RENDER");

	mTechniques.push_back( mMenuTechnique );

	// input layouts
	if ( FAILED ( CreateLayouts() ) )
		return dbg->getDbg()->fatalError(*hWnd, "Fatal error, shutting down");
	else dbg->getDbg()->print("D3D: %s\n", "Input Layout succesfully created");

	// render target views
	if ( FAILED ( CreateRenderTarget( mRenderTargetView ) ) )
		return dbg->getDbg()->fatalError(*hWnd, "Fatal error, shutting down");
	else dbg->getDbg()->print("D3D: %s\n", "RenderTargetView succesfully created");

	// depth stencils
	if ( FAILED( CreateDepthStencil( width, height, mRenderTargetView ) ) )
		return dbg->getDbg()->fatalError(*hWnd, "Fatal error, shutting down");
	else dbg->getDbg()->print("D3D: %s\n", "Depth Stencil succesfully created");

	// viewports
	CreateViewPorts(width, height, mViewPort);

	// rasterizerstate
	SetRasterizerState();

	//sprite test
	mColorMap = mMenuEffect->GetVariableByName( "colorMap" )->AsShaderResource();

	return true;
}

bool D3DManager::CreateSwapChain(UINT _width, UINT _height)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory( &swapChainDesc, sizeof(swapChainDesc) );

	// set up buffer
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = _width;
	swapChainDesc.BufferDesc.Height = _height;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// refresh rate
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// sampling setting
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;

	// output window handle
	swapChainDesc.OutputWindow = *hWnd;

	if ( FAILED ( isFullScreen = cfg->getCFG()->GetBoolOfKey("SCREENMODE", "GFX", "Setup") ) )
		return dbg->getDbg()->fatalError(*hWnd, "Setup.dat corrupt");

	swapChainDesc.Windowed = isFullScreen;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if ( FAILED( D3D10CreateDeviceAndSwapChain(	NULL,
												D3D10_DRIVER_TYPE_HARDWARE,
												NULL,
												0,
												D3D10_SDK_VERSION,
												&swapChainDesc,
												&mSwapChain,
												&mD3DDevice ) ) )
												return dbg->getDbg()->fatalError(*hWnd, "D3Ddevice creation failed");

	return true;
}

bool D3DManager::CreateShaders()
{


	return true;
}

ID3D10Effect* D3DManager::CreateFX(string _fileName, ID3D10Effect* _effect)
{
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
	string directory = ( ".\\shaders\\" + _fileName );

	if ( FAILED( D3DX10CreateEffectFromFile(	directory.c_str(), 
												NULL, NULL, 
												"fx_4_0", 
												shaderFlags, 
												0, 
												mD3DDevice, 
												NULL, NULL, 
												&_effect, 
												NULL, NULL ) ) )
	{
		string errorMsg = ("Failed to create " + _fileName);
		dbg->getDbg()->fatalError( *hWnd, errorMsg.c_str() );
	}

	return _effect;
}

bool D3DManager::CreateLayouts()
{
	// Menu layout
	D3D10_PASS_DESC menuPassDesc;

	D3D10_INPUT_ELEMENT_DESC menuDesc[] =
	{
		{ "ANCHOR",		0,	DXGI_FORMAT_R32G32_FLOAT,	0,	0,									D3D10_INPUT_PER_VERTEX_DATA,	0 },
		{ "DIMENSIONS",	0,	DXGI_FORMAT_R32G32_FLOAT,	0,	D3D10_APPEND_ALIGNED_ELEMENT,		D3D10_INPUT_PER_VERTEX_DATA,	0 },
		{ "OPACITY",	0,	DXGI_FORMAT_R32_FLOAT,		0,	D3D10_APPEND_ALIGNED_ELEMENT,		D3D10_INPUT_PER_VERTEX_DATA,	0 }
	};
	UINT numElements = 3;

	mMenuTechnique->GetPassByIndex( 0 )->GetDesc( &menuPassDesc );

	if ( FAILED( mD3DDevice->CreateInputLayout(	menuDesc, 
												numElements,
												menuPassDesc.pIAInputSignature,
												menuPassDesc.IAInputSignatureSize,
												&mMenuLayout ) ) )
												return dbg->fatalError(*hWnd, "Could not create menuLayout");

	mD3DDevice->IASetInputLayout( mMenuLayout );

	return true;
}

// note, parameter does not work, reverted to mRenderTargetView
bool D3DManager::CreateRenderTarget(ID3D10RenderTargetView* _renderTargetView)
{
	ID3D10Texture2D* backBuffer;

	if ( FAILED(	mSwapChain->GetBuffer(	0,	__uuidof( ID3D10Texture2D ),
											(LPVOID*) &backBuffer ) ) )
											return dbg->getDbg()->fatalError(*hWnd, "Could not get backbuffer");

	if ( FAILED(	mD3DDevice->CreateRenderTargetView(	backBuffer,
														NULL,
														&mRenderTargetView ) ) )
														return dbg->getDbg()->fatalError(*hWnd, "Could not create renderTarget");

	mD3DDevice->OMSetRenderTargets(1, &mRenderTargetView, NULL);
	backBuffer->Release();

	return true;
}

//note if we want to be able to initialize several depthstencils and views they need to be
//added as parameters
bool D3DManager::CreateDepthStencil(UINT _width, UINT _height, ID3D10RenderTargetView* _renderTargetView)
{
	D3D10_TEXTURE2D_DESC descDepth;

	descDepth.Width = _width;
	descDepth.Height = _height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	if ( FAILED( mD3DDevice->CreateTexture2D(	&descDepth,
												NULL,
												&mDepthStencil ) ) )
												return dbg->getDbg()->fatalError(*hWnd, "Failed to create depth stencil texture");

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	if ( FAILED( mD3DDevice->CreateDepthStencilView(	mDepthStencil,
														&descDSV,
														&mDepthStencilView ) ) )
														return dbg->getDbg()->fatalError(*hWnd, "Failed to create depth stencil view");

	mD3DDevice->OMSetRenderTargets(1, &_renderTargetView, mDepthStencilView);
	mDepthStencil->Release();

	return true;
}

void D3DManager::CreateViewPorts(UINT _width, UINT _height, D3D10_VIEWPORT _viewPort)
{
	_viewPort.Width = _width;
	_viewPort.Height = _height;
	_viewPort.MinDepth = 0.0f;
	_viewPort.MaxDepth = 1.0f;
	_viewPort.TopLeftX = 0;
	_viewPort.TopLeftY = 0;

	mD3DDevice->RSSetViewports( 1, &_viewPort );
}

void D3DManager::SetRasterizerState()
{
	rasterizerState.CullMode = D3D10_CULL_NONE;
	rasterizerState.FillMode = D3D10_FILL_SOLID;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = true;

	mD3DDevice->CreateRasterizerState( &rasterizerState, &pRS );
	mD3DDevice->RSSetState( pRS );
}

void D3DManager::SetGFX()
{

}