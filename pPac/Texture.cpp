#include "Texture.h"

Texture::Texture(int _id, std::string _file, D3DManager* _D3DManager)	: mId(_id)
{
	pSRView = NULL;
	HRESULT hr = D3DX10CreateShaderResourceViewFromFile( _D3DManager->mD3DDevice, 
											_file.c_str(),
											NULL, NULL,
											&pSRView, NULL );

	if ( FAILED ( hr) )
		int i = 42;

	this->pSRView = pSRView;
}


Texture::~Texture()
{
	delete pSRView;
	pSRView = NULL;
}

ID3D10ShaderResourceView* Texture::getPSRView()const
{
	return pSRView;
}