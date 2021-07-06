#ifndef __STRING_H__
#define __STRING_H__

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
		~String();
	private:
		char* pString;
	};
}

#endif