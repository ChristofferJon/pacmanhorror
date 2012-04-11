#ifndef __D3DManager__
#define __D3DManager__

#include "D3DLibs.h"

class D3DManager
{
public:
	D3DManager(UINT _width, UINT _height);
	~D3DManager();

public:
	
	ID3D10Device*				mD3DDevice;
	IDXGISwapChain*				mSwapChain;
	ID3D10RenderTargetView*		mRenderTargetView;
	D3D10_VIEWPORT				mViewPort;

	bool						Initialize(HWND* _hWnd);

	//effect variable pointers
	ID3D10EffectMatrixVariable*		mViewMatrixEffectVariable;
	ID3D10EffectMatrixVariable*		mProjectionMatrixEffectVariable;
	ID3D10EffectMatrixVariable*		mWorldMatrixEffectVariable;

private:
	ID3D10RasterizerState*			pRS;
	D3D10_RASTERIZER_DESC			pRasterizerState;
	void	SetGFX();
	const	UINT mWidth;
	const	UINT mHeight;
	bool	fullScreen;
};

#endif