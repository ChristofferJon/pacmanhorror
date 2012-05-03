#include "Observee.h"



//------------------------
// Forward Declarations
//------------------------

class Notifier
{
public:
	Notifier(Observee* observee) : m_pObservee(observee)
	{}

	void operator()(Observer* observer)
	{
		observer->Notify(m_pObservee);
	}

private:
	Observee* m_pObservee;
};

//--------------------------
// Constructor & Destructor
//--------------------------

Observee::Observee()
{
	//Nothing to create
}

Observee::~Observee()
{
	// nothing to destroy
}


//this method adds an observer to the vector of observers
bool Observee::AddObserver( Observer* observer)
{
	std::vector<Observer*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
	//return false if the observer is already in the vector. This is not expected. But there is nothing really wrong either
	if(temp != m_ObserverVec.end() )
		return false;

	m_ObserverVec.push_back(observer);
	return true;
}

//This method removes an observer from the vector
bool Observee::RemoveObserver( Observer* observer)
{
	std::vector<Observer*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
	
	//return false if the observer could not be found (and evidently can't be removed)
	if(temp == m_ObserverVec.end() )
		return false;

	else
	{
		m_ObserverVec.erase(remove(m_ObserverVec.begin(), m_ObserverVec.end(), observer));
	}
	return true;
}

//This Method is very important, it triggers all Notify() methods of all observers.
//The specific code in each class that inherits from observer will be executed

bool Observee::NotifyObservers()
{
	for_each(m_ObserverVec.begin(), m_ObserverVec.end(), Notifier(this));
	//Return false if there are no observers in the vector
	return(m_ObserverVec.size() > 0);
}