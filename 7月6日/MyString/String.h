#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>

#ifndef NULL
#define NULL 0
#endif

namespace MySpace
{
	class String
	{
	public:
		String();
		String(const char* str);
		String(const String& str);
		~String();
		String& operator= (const String& str);
		const char* GetString()const;
	private:
		char* pString;
	};

	std::ostream&  operator<< (std::ostream& out, const String& str);
	std::istream&  operator>>(std::istream& in, String& str);
}

#endif
