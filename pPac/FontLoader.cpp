#include "FontLoader.h"

FontLoader::FontLoader()
{
	mFontSprite = NULL;
}


FontLoader::~FontLoader()
{
	mFont->Release();
	mFont = NULL;

	mFontSprite->Release();
	mFontSprite = NULL;
}

void FontLoader::CreateFont(string _fontType, ID3D10Device* _mD3DDevice)
{
	int size = 40;

	D3DX10CreateFont( _mD3DDevice, size, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT(_fontType.c_str()), &mFont);

	D3DX10CreateSprite( _mD3DDevice, 256, &mFontSprite);
}

ID3DX10Sprite* FontLoader::getSpriteFont()
{
	return mFontSprite;
}

LPD3DX10FONT* FontLoader::getFont()
{
	return &mFont;
}