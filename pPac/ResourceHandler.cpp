#include "ResourceHandler.h"

ResourceHandler* instance = NULL;


ResourceHandler::ResourceHandler(D3DManager* _d3dManager)
{
	md3dManager = _d3dManager;
	mD3DDevice = _d3dManager->mD3DDevice;
	Test();
}

ResourceHandler::~ResourceHandler()
{
	for each (Model m in mModels)
		m.~Model();
	for each (Sprite s in mSprites)
		s.~Sprite();
	for each (Texture* t in mTextures)
		t->~Texture();
	for each (Material m in mMaterials)
		m.~Material();
	for each (VertexBuffer* b in mBuffers)
		b->~VertexBuffer();
	for each (RenderPackage r in mRenderPackages)
		r.~RenderPackage();
}

// assign the temp a default model in case we cant
// find a matching id, return a pointer
Model* ResourceHandler::getModel(int _id)
{
	Model* temp = &mModels[0];
	for each (Model m in mModels)
		if (_id == m.mId)
			temp = &m;

	return temp;
}

Sprite* ResourceHandler::getSprite(int _id)
{
	for ( int i = 0; i < mSprites.size(); i++)
		if ( _id == mSprites[i].mId )
			return &mSprites[i];

	return &mSprites[0];
}

// we need to do multiple safety checks here to make sure
// there are corresponding id's to our parameters. If not
// we should revert to a default asset.
int ResourceHandler::CreateModel(int _id, int _tex, int _buf, int _mat, int _ren)
{
	Texture* tex = getTexture(_tex);
	VertexBuffer* buf = getBuffer(_buf);
	Material* mat = getMaterial(_mat);
	RenderPackage* ren = getRenderPackage(_ren);

	mModels.push_back( Model( _id, tex, buf, mat, ren ) );

	return _id;
}

int ResourceHandler::CreateSprite(int _id, int _tex, int _buf)
{
	Texture* tex = getTexture(_tex);
	VertexBuffer* buf = getBuffer(_buf);

	mSprites.push_back( Sprite( _id, tex, buf ) );

	return _id;
}

Texture* ResourceHandler::getTexture(int _id)
{
	Texture* temp = mTextures[0];
	for each (Texture* t in mTextures)
		if (_id == t->mId)
		{
			temp = t;
			break;
		}

	return temp;
}

Material* ResourceHandler::getMaterial(int _id)
{
	Material* temp = &mMaterials[0];
	for each (Material m in mMaterials)
		if (_id == m.mId)
		{
			temp = &m;
			break;
		}

	return temp;
}

VertexBuffer* ResourceHandler::getBuffer(int _id)
{
	VertexBuffer* temp = mBuffers[0];
	for each (VertexBuffer* b in mBuffers)
		if (_id == b->mId)
		{
			temp = b;
			break;
		}

	return temp;
}

RenderPackage* ResourceHandler::getRenderPackage(int _id)
{
	RenderPackage* temp = &mRenderPackages[0];
	for each (RenderPackage r in mRenderPackages)
		if (_id == r.mId)
		{
			temp = &r;
			break;
		}

	return temp;
}

vector<D3DXVECTOR3>& ResourceHandler::CreateCube(int _width, int _height, int _length)
{
	//define all points in the quad
	D3DXVECTOR3 p[8] =
	{
		D3DXVECTOR3(-_width, -_height, -_length),	//BLU 0
		D3DXVECTOR3(-_width, _height, -_length),	//BLD 1
		D3DXVECTOR3(_width, _height, -_length),		//BRD 2
		D3DXVECTOR3(_width, -_height, -_length),	//BRU 3
		D3DXVECTOR3(-_width, -_height, _length),	//FLU 4
		D3DXVECTOR3(-_width, _height, _length),		//FLD 5
		D3DXVECTOR3(_width, _height, _length),		//FRD 6
		D3DXVECTOR3(_width, -_height, _length)		//FRU 7
	};

	D3DXVECTOR3 quad[36] =
	{
		p[0], p[1], p[2], p[0], p[2], p[3], //back
		p[4], p[5], p[6], p[4], p[6], p[7], //front
		p[4], p[5], p[1], p[4], p[1], p[0], //left
		p[7], p[6], p[2], p[7], p[2], p[3], //right
		p[0], p[4], p[7], p[0], p[7], p[3], //bottom
		p[1], p[5], p[6], p[1], p[6], p[2]  //top
	};

	vector<D3DXVECTOR3> temp;

	for (int i = 0; i < 36; i++)
		temp.push_back(quad[i]);

	return temp;
}

vector<D3DXVECTOR3> ResourceHandler::CreateQuad(int _width, int _height)
{
	D3DXVECTOR3 p[4] =
	{
		D3DXVECTOR3(-_width, -_height, 0),		//LU 4
		D3DXVECTOR3(-_width, _height, 0),		//LD 5
		D3DXVECTOR3(_width, _height, 0),		//RD 6
		D3DXVECTOR3(_width, -_height, 0)		//RU 7
	};

	D3DXVECTOR3 quad[6] =
	{
		p[0], p[1], p[2], p[0], p[2], p[3]
	};

	vector<D3DXVECTOR3> temp;

	for (int i = 0; i < 36; i++)
		temp.push_back(quad[i]);

	return temp;
}

inline float convertPixelsToClipSpace( const int pixelDimension, const int pixels )
{
	return (float)pixels/pixelDimension*2 -1;
}

inline float convertPixelsToClipSpaceDistance( const int pixelDimension, const int pixels )
{
	return (float)pixels/pixelDimension*2;
}

void ResourceHandler::InstanceBuffer(ID3D10Buffer* _buffer)
{
		spriteVertex vert;

	vert.topLeft[0] = convertPixelsToClipSpace(1200,0);
	vert.topLeft[1] = -convertPixelsToClipSpace(720,0);
	vert.dimensions[0] = convertPixelsToClipSpaceDistance(1200,1200);
	vert.dimensions[1] = convertPixelsToClipSpaceDistance(1200,1200);
	vert.opacity = 1;

	D3D10_SUBRESOURCE_DATA initData;
initData.pSysMem = &vert;

D3D10_BUFFER_DESC bd;
bd.Usage = D3D10_USAGE_DEFAULT;
bd.ByteWidth = sizeof( spriteVertex ) * 1;
bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
bd.CPUAccessFlags = 0;
bd.MiscFlags = 0;
		
if ( FAILED( mD3DDevice->CreateBuffer( &bd, &initData, &_buffer ) ) )
	int i = 42;

	// Set vertex buffer
	UINT stride = sizeof( spriteVertex );
	UINT offset = 0;
	mD3DDevice->IASetVertexBuffers( 0, 1, &_buffer, &stride, &offset );

	mBuffers[0]->setBuffer(*_buffer);
}

void ResourceHandler::Test()
{
	mBuffers.push_back( new VertexBuffer( 110 ) );

	mTextures.push_back( new Texture( 110, ".\\Resources\\GFX\\Textures\\Assets\\button2.png", md3dManager ) );
	mSprites.push_back( Sprite( 110, mTextures[0], mBuffers[0] ) );
	InstanceBuffer( mBuffers[0]->mBuffer );
}