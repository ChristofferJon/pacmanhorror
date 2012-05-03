#include <string>
#include <iostream>
#include "event.h"
using namespace std;

void onEvent(string data)
{
	cout << "Handler function called with: " << data << endl;
}

void onEvent2(string data)
{
	cout << "Handler function number 2 called with: " << data << endl;
}

int main()
{

	cout<<"\n"<<endl;
	Event<string> handler; //Create an instance of Event, passing the string type as "Data" in the class
	handler.add(onEvent); //Pass the onEvent function to the Event class, telling it to notify the function when something changes.
							//Also the same as handler += onEvent;

	string msg = "My handler works!"; //make a message
	handler.changed(msg); //tell the event class that something changed, including the data - update all the listener functions!
							//also same as handler(msg)

	handler += onEvent2; //same as handler.add(onEvent2);

	msg += " (revisited!)"; //add new data
	handler(msg); //same as handler.changed(msg);

	//handler -= onEvent; Remove currently doesn't work

	msg = "Only handler 2 should say this!";
	handler(msg);
	cout << "\n\n" <<endl;

	system("pause");
	return 0;
}