#ifndef __RESOURCEHANDLER__
#define __RESOURCEHANDLER__

#include "VertexBuffer.h"
#include "Material.h"
#include "RenderPackage.h"
#include "Texture.h"
#include "Model.h"
#include "Sprite.h"
#include <string>
#include <vector>

#include "CFG.h"

#include "Dbg.h"

#include "D3DManager.h"

using std::string;
using std::vector;

struct spriteVertex
{
	float topLeft[2];
	float dimensions[2];
	float opacity;
};

struct basicVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 col;

	basicVertex( D3DXVECTOR3 _p, D3DXVECTOR4 _c )
	{
		pos = _p;
		col = _c;
	}
};

//struct spriteVertexA
//{
//	float topLeft[2];
//	float dimensions[2];
//};
//
//struct defMeshVertex
//{
//	D3DXVECTOR3 position;
//	D3DXVECTOR2 texCoord;
//};
//
//struct lMeshVertex
//{
//	D3DXVECTOR3 position;
//	D3DXVECTOR3 normal;
//	D3DXVECTOR2 texCoord;
//};

class ResourceHandler
{
public:
	ResourceHandler(D3DManager* _d3dManager);
	~ResourceHandler();

public:
	// low level
	vector<Texture*> mTextures;
	vector<Material> mMaterials;
	vector<VertexBuffer*> mBuffers;
	vector<RenderPackage> mRenderPackages;

	// high level
	vector<Model> mModels;
	vector<Sprite> mSprites;

	Texture* getTexture(int _id);
	Material* getMaterial(int _id);
	VertexBuffer* getBuffer(int _id);


	void addMaterial(string _file);
	void addTexture(string _file);
	void addBuffer(string _file);
	void addRenderPackage(int _index);

	CFG* mCfg;

public:
	Model* getModel(int _id);
	Sprite* getSprite(int _id);
	RenderPackage* getRenderPackage(int _id);

	int CreateModel(int _id, int _tex, int _buf, int _mat, int _ren);
	int CreateSprite(int _id, int _tex, int _buf);

	void CreateCube(int _width, int _height, int _length, VertexBuffer* _vBuffer);
	vector<D3DXVECTOR3> CreateQuad(int _width, int _height);

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