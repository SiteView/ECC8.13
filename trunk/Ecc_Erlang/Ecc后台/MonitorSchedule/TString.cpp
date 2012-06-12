#include ".\tstring.h"

TString::TString(void)
{
}

TString::~TString(void)
{
}

int TString::Format(const char * format,...)
{
	int chars=256;
	va_list args;
	va_start(args, format);
	while(true)
	{
    	init();
		resize(chars);

		char *ptr = getText();
		int n=vsnprintf(ptr, chars, format, args);
		if(n>-1)
			break;
		else
		{
			clear();
	    	chars+=256;
		}
	}
        setLength(strlen(getText()));
	va_end(args);


	return 0;
}

int TString::Format(int len,const char * format,...)
{
	int chars=len;
	init();
	resize(chars);

        va_list args;
        va_start(args, format);

        char *ptr = getText();
	vsnprintf(ptr, chars, format, args);
        setLength(strlen(getText()));
	va_end(args);

	return 0;

}

TString TString::Left(int nCount)
{
	if(nCount<=0)
		return "";

	if(nCount>=this->getLength())
		return *this;

	return this->substr(0,nCount);	

}

TString TString::Right(int nCount)
{
	if(nCount<=0)
		return "";

	if(nCount>=this->getLength())
		return *this;

	return substr(getLength()-nCount,nCount);

}

int TString::CompareNoCase(const char * str)
{
	return stricmp(this->getText(),str);
}
