#include "stdafx.h"
#include "log.h"
#include <ctime>

Log::Log(char* filename) {
  m_stream.open(filename);
}

void Log::Write(char* logline){
	time_t now = time(0);
    struct tm* tm = localtime(&now);    
	m_stream << "[" << tm->tm_year << '/' << tm->tm_mon << '/' << tm->tm_mday
         << ' ' << tm->tm_hour << ':' << tm->tm_min << ':' << tm->tm_sec << "]: ";
    m_stream << logline << endl;
}

void Log::Write(char* logline, int notime){
	if(notime == 0) {
		m_stream << logline;
	} else {
		time_t now = time(0);
		struct tm* tm = localtime(&now);    
		m_stream << "[" << tm->tm_year << '/' << tm->tm_mon << '/' << tm->tm_mday
			 << ' ' << tm->tm_hour << ':' << tm->tm_min << ':' << tm->tm_sec << "]: ";
		m_stream << logline << endl;
	}
}

Log::~Log(){
  m_stream.close();
}