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
	for each (Material* m in mMaterials)
		m->~Material();
	for each (VertexBuffer* b in mBuffers)
		b->~VertexBuffer();
	for each (RenderPackage* r in mRenderPackages)
		r->~RenderPackage();
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
	for ( int i = 0; i < mTextures.size(); i++ )
		if ( _id == mTextures[i]->mId )
			return mTextures[i];

	return mTextures[0];
}

Material* ResourceHandler::getMaterial(int _id)
{
	for ( int i = 0; i < mMaterials.size(); i++ )
		if ( _id == mMaterials[i]->mId )
			return mMaterials[i];

	return mMaterials[0];
}

VertexBuffer* ResourceHandler::getBuffer(int _id)
{
	for ( int i = 0; i < mBuffers.size(); i++ )
		if ( _id == mBuffers[i]->mId )
			return mBuffers[i];

	return mBuffers[0];
}

RenderPackage* ResourceHandler::getRenderPackage(int _id)
{
	for ( int i = 0; i < mRenderPackages.size(); i++ )
		if ( _id == mRenderPackages[i]->mId )
			return mRenderPackages[i];

	return mRenderPackages[0];
}

void ResourceHandler::InstancePCVertexBuffer( vector<D3DXVECTOR3> _position, D3DXVECTOR4 _color, VertexBuffer* _vBuffer )
{
	vector<PCVertex> vert;

	for ( int i = 0; i < _position.size(); i++)
		vert.push_back( PCVertex( _position[i], _color ) );

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof( PCVertex ) * vert.size();
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &vert[0];
		
	if ( FAILED( mD3DDevice->CreateBuffer( &bd, &initData, &_vBuffer->mBuffer ) ) )
		int i = 42;

	//	Set vertex buffer
	UINT stride = sizeof( PCVertex );
	UINT offset = 0;
	_vBuffer->stride = stride;
	_vBuffer->offset = offset;
	_vBuffer->numVertices = vert.size();
	mD3DDevice->IASetVertexBuffers( 0, 1, &_vBuffer->mBuffer, &stride, &offset );
}

void ResourceHandler::InstancePTVertexBuffer( vector<D3DXVECTOR3> _position, vector<D3DXVECTOR2> _uv, VertexBuffer* _vBuffer )
{
	vector<PTVertex> vert;

	for ( int i = 0; i < _position.size(); i++)
		vert.push_back( PTVertex( _position[i], _uv[i % 6] ) );

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof( PTVertex ) * vert.size();
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &vert[0];
		
	if ( FAILED( mD3DDevice->CreateBuffer( &bd, &initData, &_vBuffer->mBuffer ) ) )
		int i = 42;

	//	Set vertex buffer
	UINT stride = sizeof( PTVertex );
	UINT offset = 0;
	_vBuffer->stride = stride;
	_vBuffer->offset = offset;
	_vBuffer->numVertices = vert.size();
	mD3DDevice->IASetVertexBuffers( 0, 1, &_vBuffer->mBuffer, &stride, &offset );
}

vector<D3DXVECTOR3> ResourceHandler::CreateCube( int _width, int _height, int _length )
{
	vector<D3DXVECTOR3> vert;

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

	int quad[36] =
	{
		1, 0, 2, 2, 0, 3, //back
		4, 5, 6, 4, 6, 7, //front
		5, 4, 1, 1, 4, 0, //left
		7, 6, 2, 7, 2, 3, //right
		0, 4, 7, 0, 7, 3, //bottom
		5, 1, 6, 6, 1, 2  //top
	};

	for (int i = 0; i < 36; i++)
		vert.push_back(p[quad[i]] );

	return vert;
}

vector<D3DXVECTOR3> ResourceHandler::CreateQuad( int _x, int _y, int _z )
{
	vector<D3DXVECTOR3> vert;

	D3DXVECTOR3 p[4] =
	{
		D3DXVECTOR3( -_x,	-_y,	-_z),		//LU 4
		D3DXVECTOR3( -_x,	_y,		_z),		//LD 5
		D3DXVECTOR3( _x, 	_y,		_z),		//RD 6
		D3DXVECTOR3( _x, 	-_y,	-_z)		//RU 7
	};

	int quad[6] =
	{
		1, 0, 2, 2, 0, 3
	};

	for (int i = 0; i < 6; i++)
		vert.push_back( p[quad[i]] );

	return vert;
}

vector<D3DXVECTOR2> ResourceHandler::SimpleSkin( int numVerts )
{
	vector<D3DXVECTOR2> uv;

	D3DXVECTOR2 p[4] =
	{
		D3DXVECTOR2( 0, 1 ),
		D3DXVECTOR2( 0, 0 ),
		D3DXVECTOR2( 1, 0 ),
		D3DXVECTOR2( 1, 1 )
	};

	int q[6] =
	{
		1, 0, 2, 2, 0, 3, //back
	};

	for ( int i = 0; i < numVerts; i++ )
		uv.push_back( p[ q[ i % 6 ] ] );

	return uv;
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
				string vType = mCfg->getCFG()->GetStringOfKey( "TYPE", l->name()  , d->name() );
				string directory = mCfg->getCFG()->GetStringOfKey( "FILE", l->name()  , d->name() );

				// push back
				mBuffers.push_back( new VertexBuffer( id ) );

				// instance depending on file reference
				if ( directory == "SB_FULL" ) // no file, cover the entire window
				{
					InstanceSpriteBuffer( getBuffer( id ) );
				}
				else if ( directory == "CUBE" ) // no file but x & y defined
				{
					if ( vType == "PCVERTEX" )
						InstancePCVertexBuffer( CreateCube( 100, 100, 100 ), D3DXVECTOR4( 0.5, 0.1, 0.35, 1.0 ), getBuffer( id ) );
					else if ( vType == "PTVERTEX" )
						InstancePTVertexBuffer( CreateCube( 100, 100, 100 ), SimpleSkin( 36 ), getBuffer( id ) );
				}
				else if ( directory == "DQUAD" ) // no file but x, y & z defined
				{
					if ( vType == "PCVERTEX" )
						InstancePCVertexBuffer( CreateQuad( 100, 0, 100 ), D3DXVECTOR4( 0.75, 0.5, 0.25, 1.0 ), getBuffer( id ) );
					else if ( vType == "PTVERTEX" )
						InstancePTVertexBuffer( CreateQuad( 100, 0, 100 ), SimpleSkin( 6 ), getBuffer( id ) );
				}
				else if ( directory == "UQUAD" )
				{
					if ( vType == "PCVERTEX" )
						InstancePCVertexBuffer( CreateQuad( 25, 25, 0 ), D3DXVECTOR4( 0.25, 0.5, 0.75, 1.0 ), getBuffer( id ) );
					else if ( vType == "PTVERTEX" )
						InstancePTVertexBuffer( CreateQuad( 25, 25, 0 ), SimpleSkin( 6 ), getBuffer( id ) );
				}
				else	// obj file referensed
				{
					// load obj
					int i = 42;
				}
			}
		}
	}
}

void ResourceHandler::Test()
{
	LoadLowLevel( "SpriteCollection" );
	LoadHighLevel( "SpriteCollection" );

	DATA_CONTAINER* d = mCfg->getCFG()->GetContainer( "ModelCollection" );

	for each ( CFG_Link* l in d->links() )
	{
		int id = -1;
		int tId = -1;
		int bId = -1;
		int mId = -1;
		int rId = -1;

		for each ( CFG_Entry* e in l->entries() )
		{
			id = mCfg->getCFG()->GetIntOfKey("ID", l->name() , d->name() );
			tId = mCfg->getCFG()->GetIntOfKey("TEXTUREID", l->name() , d->name() );
			bId = mCfg->getCFG()->GetIntOfKey("BUFFERID", l->name() , d->name() );
			mId = mCfg->getCFG()->GetIntOfKey("MATERIALID", l->name() , d->name() );
			rId = mCfg->getCFG()->GetIntOfKey("RENDERID", l->name() , d->name() );
		}

		CreateModel( id, tId, bId, mId, rId );
	}
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

				mRenderPackages.push_back( new RenderPackage( id, md3dManager->mEffects[index], md3dManager->mTechniques[index] ) );
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
				mMaterials.push_back( new Material( id, amb, spec, diff, shin ) );
			}
		}
	}
}