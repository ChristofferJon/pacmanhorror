
E:\Programmering\Github\pacmanhorror>@git.exe %*
#ifndef __GAMEENTITY__
#define __GAMEENTITY__

#include <D3DX10.h>
#include "Model.h"

class GameEntity
{
public:
	GameEntity();
	~GameEntity();

public:
	float mHealth;
	D3DXVECTOR3 mPosition;
	Model* mModel;
	D3DManager* md3dManager;
	ID3D10Device* md3dDevice;

public:
	virtual void Update(float _dt) = 0;
	virtual void Draw(float _dt) = 0;
	virtual void Initialize() = 0;
};

#endif
E:\Programmering\Github\pacmanhorror>@set ErrorLevel=%ErrorLevel%

E:\Programmering\Github\pacmanhorror>@rem Restore the original console codepage.

E:\Programmering\Github\pacmanhorror>@chcp %cp_oem% > nul < nul
