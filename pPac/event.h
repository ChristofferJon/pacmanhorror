// http://www.astahost.com/info/tttcmp-basic-event-handler-class-familiar-handlers-mimic.html

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <algorithm> // For the remove listener function so we can use std::remove_if

template<class Data> class Event
{
protected: //protected so that subclasses can inherit the data
	typedef void (*fptr)(Data);
	typename std::vector<fptr> listeners;

public:
	void changed(Data& eventData)
	{
		for( typename std::vector<fptr>::iterator iter = listeners.begin(); iter!=listeners.end(); ++iter)
		{
			(*iter)(eventData);
		}
	}

	Event& add(fptr func)
	{
		for(typename std::vector<fptr>::iterator iter = listeners.begin(); iter != listeners.end(); ++iter)
		{
			//we must dereference the pointer-to-pointer-to-function to get the pointer-to-function so that we can compare it
			if(*iter == func)
			{
				//case was true, the fucntion has already been added so we return and don't add it again
				return *this;
			}

		}
		//Ok, func has not yet been added (or added then removed) so we can add it
		listeners.push_back(func);
		return *this;
	}

	bool evt_equal(fptr func1, fptr func2) //needs to be redone to only need one argument
	{
		return(func1 == func2);
	}
	Event& sub(fptr func)
	{
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(), evt_equal), listeners.end());
		return *this;
		
	}

	//Operators
	Event& operator += (fptr func)
	{
		return add(func);
	}
	Event& operator -= (fptr func)
	{
		return sub(func);
	}
	void operator()(Data& eventData)
	{
		changed(eventData);
	}
};

#endif