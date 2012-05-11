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
	for ( int i = 0; i < mModels.size(); i++ )
		if ( _id == mModels[i].mId )
			return &mModels[i];

	return &mModels[0];
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
	for ( int i = 0; i < mRenderPackages.size(); i++ )
		if ( _id == mRenderPackages[i].mId )
			return &mRenderPackages[i];

	return &mRenderPackages[0];
}

void ResourceHandler::CreateCube(int _width, int _height, int _length, VertexBuffer* _vBuffer)
{
	vector<basicVertex> vert;
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

	D3DXVECTOR4 color = D3DXVECTOR4( 1, 1, 1, 1 );

	for (int i = 0; i < 36; i++)
		vert.push_back( basicVertex( quad[i], color ) );

	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &vert;

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( basicVertex ) * 36;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
		
	if ( FAILED( mD3DDevice->CreateBuffer( &bd, &initData, &_vBuffer->mBuffer ) ) )
		int i = 42;

	//	Set vertex buffer
	UINT stride = sizeof( basicVertex );
	UINT offset = 0;
	_vBuffer->stride = stride;
	_vBuffer->offset = offset;
	mD3DDevice->IASetVertexBuffers( 0, 1, &_vBuffer->mBuffer, &stride, &offset );
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

void ResourceHandler::InstanceSpriteBuffer(VertexBuffer* _vBuffer)
{
	spriteVertex vert;

	vert.topLeft[0] = convertPixelsToClipSpace(1200,0);
	vert.topLeft[1] = -convertPixelsToClipSpace(720,0);
	vert.dimensions[0] = convertPixelsToClipSpaceDistance(1200,1200);
	vert.dimensions[1] = convertPixelsToClipSpaceDistance(720,720);
	vert.opacity = 1;

	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &vert;

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( spriteVertex ) * 1;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
		
	if ( FAILED( mD3DDevice->CreateBuffer( &bd, &initData, &_vBuffer->mBuffer ) ) )
		int i = 42;

	//	Set vertex buffer
	UINT stride = sizeof( spriteVertex );
	UINT offset = 0;
	_vBuffer->stride = stride;
	_vBuffer->offset = offset;
	mD3DDevice->IASetVertexBuffers( 0, 1, &_vBuffer->mBuffer, &stride, &offset );
}

void ResourceHandler::InstanceSpriteBuffer( VertexBuffer* _vBuffer, float xDim, float yDim )
{
	spriteVertex vert;

	float XRU = 800;
	float YRU = 10;
	float XLU = 600;
	float YLU = 80;

	float XDIM = 160;
	float YDIM = 42;

	vert.topLeft[0] = convertPixelsToClipSpace( XRU, YRU );
	vert.topLeft[1] = -convertPixelsToClipSpace( XLU, YLU );
	vert.dimensions[0] = convertPixelsToClipSpaceDistance( XRU, xDim );
	vert.dimensions[1] = convertPixelsToClipSpaceDistance( XLU, yDim );
	vert.opacity = 1;

	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &vert;

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( spriteVertex ) * 1;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
		
	if ( FAILED( mD3DDevice->CreateBuffer( &bd, &initData, &_vBuffer->mBuffer ) ) )
		int i = 42;

	//	Set vertex buffer
	UINT stride = sizeof( spriteVertex );
	UINT offset = 0;
	mD3DDevice->IASetVertexBuffers( 0, 1, &_vBuffer->mBuffer, &stride, &offset );
}

void ResourceHandler::CreateVBuffer( string _file )
{
	DATA_CONTAINER* d = mCfg->getCFG()->GetContainer( _file );

	for each ( CFG_Link* l in d->links() )
	{
		int id = -1;
		for each ( CFG_Entry* e in l->entries() )
		{
			if ( e->key() == "FILE" )
			{
				id = mCfg->getCFG()->GetIntOfKey("ID", l->name() , d->name() );
				string directory = mCfg->getCFG()->GetStringOfKey( "FILE", l->name()  , d->name() );

				// push back
				mBuffers.push_back( new VertexBuffer( id ) );

				// instance depending on file reference
				if ( directory == "SB_FULL" ) // no file, cover the entire window
				{
					InstanceSpriteBuffer( getBuffer( id ) );
				}
				else if ( directory == "SB_DEF" ) // no file but x & y defined
				{
					CreateCube( 100, 100, 100, getBuffer( id ) );
				}
				else if ( directory == "SB_3DEF" ) // no file but x, y & z defined
				{
					// instance buffer ( id, x, y, z )
				}
				else	// obj file referensed
				{
					// load obj
					// instance buffer ( id, obj )
				}
			}
		}
	}
}

void ResourceHandler::Test()
{
	LoadLowLevel( "SpriteCollection" );
	LoadHighLevel( "SpriteCollection" );

	CreateModel( 800, 200, 101, 400, 902 );
}

void ResourceHandler::LoadHighLevel( string _file )
{
	DATA_CONTAINER* d = mCfg->getCFG()->GetContainer( _file );

	for each ( CFG_Link* l in d->links() )
	{
		int id = -1;
		int tId = -1;
		int bId = -1;

		for each ( CFG_Entry* e in l->entries() )
		{
			id = mCfg->getCFG()->GetIntOfKey("ID", l->name() , d->name() );
			tId = mCfg->getCFG()->GetIntOfKey("TEXTUREID", l->name(), d->name() );
			bId = mCfg->getCFG()->GetIntOfKey("BUFFERID", l->name(), d->name());
		}
		CreateSprite( id, tId , bId ); //id:textureId:bufferId
	}
}

void ResourceHandler::LoadLowLevel( string _file )
{
	// create dolan texture
	CreateTexture( "TextureCollection" );	

	CreateVBuffer( "BufferCollection" );

	CreateRenderPackage( "RenderCollection" );

	CreateMaterial( "MaterialCollection" );
}

// This will load all textures defined in the parameter file
void ResourceHandler::CreateTexture( string _file )
{
	// set up a temporary pointer to get access for all entries
	DATA_CONTAINER* d = mCfg->getCFG()->GetContainer( _file );

	for each ( CFG_Link* l in d->links() )
	{
		int id = -1;

		for each ( CFG_Entry* e in l->entries() )
		{
			// texture class is defined by an image FILE and an ID
			if ( e->key() == "ID" )
				id = mCfg->getCFG()->GetIntOfKey("ID", l->name(), d->name() );

			if ( e->key() == "FILE" )
			{
				string directory = mCfg->getCFG()->GetStringOfKey("FILE", l->name() , d->name() );

				mTextures.push_back( new Texture( id, directory, md3dManager ) );
			}
		}
	}
}

// there is a slight difference with setting up a renderpackage
// as we need to directly reference data from the d3dManager
// note: this make initialisation error prone so use carefully
void ResourceHandler::CreateRenderPackage( string _file )
{
	// set up a temporary pointer to get access for all entries
	DATA_CONTAINER* d = mCfg->getCFG()->GetContainer( _file );

	for each ( CFG_Link* l in d->links() )
	{
		int id = -1;

		for each ( CFG_Entry* e in l->entries() )
		{
			// texture class is defined by an image FILE and an ID
			if ( e->key() == "ID" )
				id = mCfg->getCFG()->GetIntOfKey("ID", l->name(), d->name() );

			if ( e->key() == "FILE" )
			{
				int index = mCfg->getCFG()->GetIntOfKey("FILE", l->name() , d->name() );

				mRenderPackages.push_back( RenderPackage( id, md3dManager->mEffects[index], md3dManager->mTechniques[index] ) );
			}
		}
	}
}

void ResourceHandler::CreateMaterial( string _file )
{
	// set up a temporary pointer to get access for all entries
	DATA_CONTAINER* d = mCfg->getCFG()->GetContainer( _file );

	for each ( CFG_Link* l in d->links() )
	{
		int id = -1;
		float amb = 0.0 ;
		float diff = 0.0f;
		float spec = 0.0f;
		float shin = 0.0f;

		for each ( CFG_Entry* e in l->entries() )
		{
			if ( e->key() == "ID" )
				id = mCfg->getCFG()->GetIntOfKey("ID", l->name(), d->name() );

			if ( e->key() == "AMBIENT" )
				amb = mCfg->getCFG()->GetFloatOfKey("AMBIENT", l->name() , d->name() );

			if ( e->key() == "DIFFUSE" )
				diff = mCfg->getCFG()->GetFloatOfKey("DIFFUSE", l->name() , d->name() );

			if ( e->key() == "SPECULAR" )
				spec = mCfg->getCFG()->GetFloatOfKey("SPECULAR", l->name() , d->name() );

			if ( e->key() == "SHINY" )
			{
				shin = mCfg->getCFG()->GetFloatOfKey("SHINY", l->name() , d->name() );

				// and we're done, add to list
				mMaterials.push_back( Material( id, amb, spec, diff, shin ) );
			}
		}
	}
}