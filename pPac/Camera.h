#ifndef CAMERA_H
#define CAMERA_H

#include <D3DX10.h>
#include "Dbg.h"

class Camera
{
public:
	Camera();
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

private:
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mRight;
	D3DXVECTOR3 mUp;
	D3DXVECTOR3 mLook;

	D3DXMATRIX mView;
	D3DXMATRIX mProj;

	float scroll, oldScroll; //trollmade
	Dbg*	dbg;
};

Camera& GetCamera();

#endif