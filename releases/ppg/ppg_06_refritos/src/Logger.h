//: src:Logger.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 29 july 2005  
// Declaration of CLogger class

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CLogger {
public:
	CLogger();
	CLogger(string _logfile);
	~CLogger();
	ofstream *os;
private:
	string m_Logfile;
	ofstream m_ofstream;
};

#endif