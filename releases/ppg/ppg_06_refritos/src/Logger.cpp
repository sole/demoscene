#include "Logger.h"

CLogger::CLogger() {
	this->m_Logfile="log.txt";
	this->m_ofstream.open("log.txt", ofstream::out | ofstream::trunc); // TODO open not log.txt but the appropiate file
	this->os = &this->m_ofstream;
}

CLogger::CLogger(string _logfile) {
	this->m_Logfile = _logfile;
	this->m_ofstream.open(_logfile.c_str(), ofstream::out | ofstream::trunc); 	this->os = &this->m_ofstream;
}

CLogger::~CLogger() {
}