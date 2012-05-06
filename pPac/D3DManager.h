#ifndef __D3DManager__
#define __D3DManager__

#include "D3DLibs.h"
#include "CFG.h"
#include "Dbg.h"
#include <vector>

using std::vector;
using std::string;

class D3DManager
{
public:
	D3DManager();
	~D3DManager();
	D3DManager* getInstance();

public:
	HWND*	hWnd;
	HINSTANCE hInstance;

	ID3D10Device*				mD3DDevice;
	IDXGISwapChain*				mSwapChain;
	ID3D10RenderTargetView*		mRenderTargetView;
	D3D10_VIEWPORT				mViewPort;
	D3D10_RASTERIZER_DESC		rasterizerState;

	ID3D10Texture2D*			mDepthStencil;
	ID3D10DepthStencilView*		mDepthStencilView;

	bool						Initialize(HWND* _hWnd, HINSTANCE _hInstance);

	//effect variable pointers
	ID3D10EffectMatrixVariable*		mViewMatrixEffectVariable;
	ID3D10EffectMatrixVariable*		mProjectionMatrixEffectVariable;
	ID3D10EffectMatrixVariable*		mWorldMatrixEffectVariable;

	//effects & techniques

	// menues
	ID3D10Effect*						mMenuEffect;
	ID3D10EffectTechnique*				mMenuTechnique;
	ID3D10InputLayout*					mMenuLayout;
	//ID3D10EffectShaderResourceVariable* mColorMap;

	ID3D10EffectMatrixVariable*		mMenuView;
	ID3D10EffectMatrixVariable*		mMenuProjection;
	ID3D10EffectMatrixVariable*		mMenuWorld;


public:
	ID3D10RasterizerState*			pRS;
	D3D10_RASTERIZER_DESC			pRasterizerState;

	void	SetGFX();
	UINT	mWidth;
	UINT	mHeight;
	bool	isFullScreen;

	CFG*	cfg;
	Dbg*	dbg;

	bool	CreateSwapChain(UINT _width, UINT _height);
	bool	CreateShaders();

	ID3D10Effect*	CreateFX(string _fileName, ID3D10Effect* _effect);

	bool	CreateLayouts();
	bool	CreateRenderTarget(ID3D10RenderTargetView* _renderTargetView);
	bool	CreateDepthStencil(UINT _width, UINT _height, ID3D10RenderTargetView* _renderTargetView);
	void	CreateViewPorts(UINT _width, UINT _height, D3D10_VIEWPORT _viewPort);
	void	SetRasterizerState();

public:
	//sprite test
	ID3D10EffectShaderResourceVariable* mColorMap;
	vector<ID3D10Effect*> mEffects;
	vector<ID3D10EffectTechnique*> mTechniques;
};

#endif