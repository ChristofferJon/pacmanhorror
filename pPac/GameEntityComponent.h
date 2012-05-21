#ifndef __GAMEENTITYCOMPONENT__
#define __GAMEENTITYCOMPONENT__

class GameEntityComponent
{
public:
	GameEntityComponent();
	~GameEntityComponent();

public:
	virtual void Initialize(...) = 0;
	virtual void Update( float dt ) = 0;
};

#endif