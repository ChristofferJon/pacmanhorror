#pragma once

#include "Observer.h"
#include <vector>
#include <algorithm>

class Observer;

//-------------------
//Observee class
//-------------------
class Observee
{
public:
	virtual ~Observee();	//destructor

	bool AddObserver(Observer* observer);
	bool RemoveObserver(Observer* observer);
	bool NotifyObservers();
protected:
	//Constructor is protected because this class is abstract, it's only meant to be inherited!
	Observee();

private:
	std::vector<Observer*> m_ObserverVec;
	//---------------------------------------------------------------------
	// Disabling default copy constructor and default assignment operator
	//---------------------------------------------------------------------
	Observee(const Observee& yRef);
	Observee& operator=(const Observee& yRef);
};

/*
The Subject (‘Observee’ in the code example) does all the hard work. It keeps track of all observers and notifies them when necessary!
The three methods are fairly easy to understand, their name describes what they do.
They return a bool so you can check if the execution went as expected.
*/