#ifndef RFOBJECT_H
#define RFOBJECT_H

#include <string>

class RFObject
{
public:
	bool hideFlags;
	std::string name;

	RFObject()
	{

	}
	virtual ~RFObject()
	{

	}

	virtual std::string ToString()
	{
		return name;
	}

	static void Destroy()
	{

	}
};


#endif	//RFOBJECT_H