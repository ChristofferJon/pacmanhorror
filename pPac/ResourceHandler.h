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

class ResourceHandler
{
public:
	ResourceHandler(D3DManager* _d3dManager);
	~ResourceHandler();

private:
	vector<Texture*> mTextures;
	vector<Material> mMaterials;
	vector<VertexBuffer*> mBuffers;
	vector<RenderPackage> mRenderPackages;
	vector<Model> mModels;
	vector<Sprite> mSprites;

	Texture* getTexture(int _id);
	Material* getMaterial(int _id);
	VertexBuffer* getBuffer(int _id);
	RenderPackage* getRenderPackage(int _id);

	void addMaterial(string _file);
	void addTexture(string _file);
	void addBuffer(string _file);
	void addRenderPackage(int _index);

	CFG* mCfg;

public:
	Model* getModel(int _id);
	Sprite* getSprite(int _id);

	int CreateModel(int _id, int _tex, int _buf, int _mat, int _ren);
	int CreateSprite(int _id, int _tex, int _buf);

	vector<D3DXVECTOR3>& CreateCube(int _width, int _height, int _length);
	vector<D3DXVECTOR3> CreateQuad(int _width, int _height);

	void InstanceBuffer(ID3D10Buffer* _buffer);

	void Test();

	ID3D10Device* mD3DDevice;
	D3DManager* md3dManager;

	Dbg* mDbg;
};

#endif