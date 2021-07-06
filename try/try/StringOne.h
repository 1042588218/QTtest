#include <cstring>
#include "String.h"

namespace MySpace
{
	String::String()
	{
		pString = NULL;
	}

	String::String(const char* str)
	{
		pString = NULL;

		if (str != NULL)
		{

		}


	}

	String::~String()
	{
		if (pString != NULL)
		{
			delete[] pString;
		}

	}
}