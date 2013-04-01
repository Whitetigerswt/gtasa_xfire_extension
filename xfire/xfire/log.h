#pragma once
#include <fstream>

using namespace std;

class Log {
  public:
    Log(char* filename);
    ~Log();
    void Write(char* logline);
	void Write(char* logline, int notime);
  private:
    ofstream m_stream;
};