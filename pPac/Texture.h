#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>
#include "D3DManager.h"

class Texture
{
public:
	Texture(int _id, std::string _file, D3DManager* _D3DManager);
	~Texture();

	const int mId;
	ID3D10ShaderResourceView* getPSRView()const;

public:
	ID3D10ShaderResourceView* pSRView;
};

#endif