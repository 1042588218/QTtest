#ifndef __SORTCONTROL_H__
#define __SORTCONTROL_H__
#include <vector>

#if _UNICODE
#define STRLEN wcslen
typedef std::wstring String;
#else
#define STRLEN strlen
typedef std::string String ;
#endif

struct SortDataStruct
{
	int    data;
	String str;
};

class Object;

class SortControl
{
public:
	SortControl(const SortDataStruct* parray, SIZE_T size)
	{
	}
private:
	std::vector<Object*> m_ControlContainer;
};
#endif