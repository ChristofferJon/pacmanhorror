#ifndef __FONTLOADER__
#define __FONTLOADER__

#include <d3d10.h>
#include <D3DX10.h>
#include <string>

using std::string;

class FontLoader
{
public:
	FontLoader();
	~FontLoader();

private:
	LPD3DX10FONT mFont;
	ID3DX10Sprite* mFontSprite;
	D3DXCOLOR mColor;

public:
	void CreateFont(string _fontType, ID3D10Device* _mD3DDevice);
	ID3DX10Sprite* getSpriteFont();
	LPD3DX10FONT* getFont();
};

#endif