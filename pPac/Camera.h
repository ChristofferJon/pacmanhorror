#ifndef CAMERA_H
#define CAMERA_H

#include <D3DX10.h>
#include "Dbg.h"
#include "D3DManager.h"

class Camera
{
public:
	Camera(D3DManager* _md3dManager);
	~Camera();

	D3DXVECTOR3& position();

	D3DXMATRIX view() const;
	D3DXMATRIX proj() const;

	void setLens(float foxY, float aspect, float zn, float zf);

	void strafe(float d);
	void walk(float d);

	void pitch(float angle);
	void rotateY(float angle);

	void rebuildView();

	void Scroll(float v);//trollmade
	void ReInit();//trollmade

public:
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mRight;
	D3DXVECTOR3 mUp;
	D3DXVECTOR3 mLook;

	D3DXMATRIX mView;
	D3DXMATRIX mProj;

	float scroll, oldScroll; //trollmade
	Dbg*	dbg;

	D3DManager*		md3dManager;
	ID3D10Device*	md3dDevice;
};

Camera& GetCamera();

#endif