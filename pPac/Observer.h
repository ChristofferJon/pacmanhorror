#pragma once

#include <vector>
using namespace std;

class Observee;

//--------------------------
//Observer Class
//--------------------------
class Observer
{
public:
	virtual ~Observer();	//Destructor
	virtual void Notify(Observee* observee){};

protected:
	//constructor is protected because this class is abstract, it's only meant to be inherited!
	Observer();

private:
	//------------------------------------------------------------------------
	//Disabling default copy constructor and default assignemnt operator
	//------------------------------------------------------------------------
	Observer(const Observer& yRef);
	Observer& operator=(const Observer& yRef);
};

/*
	The class that inherits Observer needs to implement the virtual Notify(Observee* observee) method. 
	It will be called by the subject when necessary, in the case of our example when the jewel is removed from its place.
*/