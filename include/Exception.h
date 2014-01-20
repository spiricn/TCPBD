#ifndef WT_EXCEPTION_H
#define WT_EXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>

class Exception : public std::runtime_error{
private:
	long mLineNumber;
	std::string mDesc;
	std::string mFunctionName;
	std::string mFile;

public:
	Exception(const char* functionName,
			const char* fileName, long lineNumber, const char* descFmt, ...) throw();

	virtual ~Exception() throw();
	
	const std::string& getDescription() const;

	const std::string getFullDescription() const;

	const std::string& getFileName() const;

	long getLineNumber() const;

	const std::string& getFunctionName() const;

}; // </Exception>

#define WT_THROW(fmt, ...) do{ throw Exception(__FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__); }while(0)

#define WT_ABORT(fmt, ...) do{ LOGE(fmt, ##__VA_ARGS__); abort(); }while(0)

#define WT_ASSERT(val, fmt, ...) do{ if(!(val)){ WT_THROW(fmt, __VA_ARGS__);} }while(0)

#endif
