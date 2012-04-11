#include "D3DManager.h"


D3DManager::D3DManager(UINT _width, UINT _height)	:	mWidth(_width),
														mHeight(_height),
														mD3DDevice(NULL),
														mSwapChain(NULL),
														mRenderTargetView(NULL),
														pRS(0)
{
}


D3DManager::~D3DManager()
{
	if ( mRenderTargetView) mRenderTargetView->Release();
	if ( mSwapChain )		mSwapChain->SetFullscreenState(FALSE, NULL);
	if ( mSwapChain )		mSwapChain->Release();
	if ( mD3DDevice )		mD3DDevice->Release();
	if ( pRS )				pRS->Release();
}
