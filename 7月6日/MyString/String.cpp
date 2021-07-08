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
			size_t len = strlen(str);
			pString = new char[len + 1];
			if (pString != NULL)
			{
				strcpy_s(pString, len+1,str);
			}
		}
	

	}

	String::String(const String& str)
	{
		pString = NULL;
		if (str.pString != NULL)
		{
			size_t len = strlen(str.pString);
			pString = new char[len + 1];
			if (pString != NULL)
			{
				strcpy_s(pString, len + 1,str.pString);
			}
		}
	}

	String::~String()
	{
		if (pString != NULL)
		{
			delete [] pString;
		}
			
	}

	String& String::operator= (const String& str)
	{
		if (this != &str)
		{
			size_t len = strlen(str.pString);
			char *tmp = new char[len + 1];
			if (tmp != NULL)
			{
				strcpy_s(tmp, len + 1, str.pString);
				if (pString != NULL)
					delete[] pString;
				pString = tmp;
			}
		}
		return *this;
	}

	const char* String::GetString()const
	{
		return pString;
	}

	std::ostream&  operator<< (std::ostream& out, const String& str)
	{
		out << str.GetString();
		return out;
	}

	std::istream&  operator>>(std::istream& in, String& str)
	{
		char buffer[128];
		in >> buffer;
		str = buffer;
		return in;
	}
}