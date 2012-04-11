#ifndef __SCREEN__
#define __SCREEN__

class Screen
{
public:
	Screen();
	~Screen();

protected:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Initialize() = 0;
	virtual void CheckForInput() = 0;
};

#endif