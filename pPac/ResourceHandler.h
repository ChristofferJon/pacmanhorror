#ifndef __RESOURCEHANDLER__
#define __RESOURCEHANDLER__

#include "GFX_Asset_Collection.h"
#include "Vertex_Collection.h"
#include "StandardCalls.h"

#include "CFG.h"
#include "D3DManager.h"


struct spriteVertex
{
	float topLeft[2];
	float dimensions[2];
	float opacity;
};

class ResourceHandler
{
public:
	ResourceHandler(D3DManager* _d3dManager);
	~ResourceHandler();

public:
	// low level
	vector<Texture*>		mTextures;
	vector<Material*>		mMaterials;
	vector<VertexBuffer*>	mBuffers;
	vector<RenderPackage*>	mRenderPackages;

	// high level
	vector<Model>			mModels;
	vector<Sprite>			mSprites;

	Texture*				getTexture(int _id);
	Material*				getMaterial(int _id);
	VertexBuffer*			getBuffer(int _id);


	void					addMaterial(string _file);
	void					addTexture(string _file);
	void					addBuffer(string _file);
	void					addRenderPackage(int _index);

	CFG* mCfg;

public:
	Model*					getModel(int _id);
	Sprite*					getSprite(int _id);
	RenderPackage*			getRenderPackage(int _id);

	int CreateModel(int _id, int _tex, int _buf, int _mat, int _ren);
	int CreateSprite(int _id, int _tex, int _buf);

	vector<D3DXVECTOR3> CreateCube(int _width, int _height, int _length );
	vector<D3DXVECTOR3> CreateQuad(int _x, int _y, int _z );
	vector<D3DXVECTOR2> SimpleSkin(int numVerts);

	void InstancePTVertexBuffer( vector<D3DXVECTOR3> _position, vector<D3DXVECTOR2> _uv, VertexBuffer* _vBuffer );
	void InstancePCVertexBuffer( vector<D3DXVECTOR3> _position, D3DXVECTOR4 _color, VertexBuffer* _vBuffer );

	void InstanceSpriteBuffer(VertexBuffer* _vBuffer);
	void InstanceSpriteBuffer(VertexBuffer* _vBuffer, float xDim, float yDim);

	void Test();

	ID3D10Device* mD3DDevice;
	D3DManager* md3dManager;

	Dbg* mDbg;

	void LoadLowLevel(string _file);
	void LoadHighLevel( string _file );

	void CreateTexture( string _file );
	void CreateVBuffer( string _file );
	void CreateRenderPackage( string _file );
	void CreateMaterial( string _file );
};

#endif