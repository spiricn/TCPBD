#include "Exception.h"

#include <td/td.h>

#define TD_TRACE_TAG "Exception"

#include <stdarg.h>
#include <stdio.h>
#include <sstream>

Exception::Exception(const char* functionName, const char* fileName, long lineNumber, const char* descFmt, ...) throw()
	:  mLineNumber(lineNumber), mDesc(descFmt), mFile(fileName), mFunctionName(functionName), std::runtime_error(""){

	va_list argList;
	va_start(argList, descFmt);

	// Format the message
	char bfr[1024];
	vsnprintf(bfr, 1024, descFmt, argList);
	va_end(argList);

	mDesc = bfr;

	LOGE("%s", getFullDescription().c_str());

}

Exception::~Exception() throw(){

}

const std::string& Exception::getDescription() const{
	return mDesc;
}

const std::string Exception::getFullDescription() const{
	std::stringstream s;
	s	<< "----------------------------\n"
		<< ">> " << mDesc << " <<\n"
		<< mFunctionName << " @ " << mLineNumber << "\n"
		<< mFile << "\n"
		<< "----------------------------\n";

	return s.str();
}

const std::string& Exception::getFileName() const{
	return mFile;
}

long Exception::getLineNumber() const{
	return mLineNumber;
}


const std::string& Exception::getFunctionName() const{
	return mFunctionName;
}

