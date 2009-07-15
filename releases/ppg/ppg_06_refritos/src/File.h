//: src:File.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 9 August 2005  
// Declaration of CFile class

#ifndef FILE_H
#define FILE_H

#include <cstdio>
#include "Base.h"


class CFile {
public:
	CFile() { 
		m_hFile = NULL;
		if(isLittleEndian()) {
			m_littleEndian=true;
		} else {
			m_littleEndian = false;
		}
	} ;
	~CFile() { Close(); }
	bool        Open        (const char *pszFile);
    void        Close       ();
    //void        Flush       ();
	
	char	ReadChar();
	unsigned char ReadUChar();
	void	ReadCharArray(char* theArray, unsigned int num);
	short	ReadShort();
	ushort	ReadUshort();
	void	ReadShortArray(short* theArray, unsigned int num);
	unsigned ReadUnsigned();
	int		ReadInt();
	void	ReadIntArray(int* theArray, unsigned int num);
	float	ReadFloat();
	void	ReadFloatArray(float* theArray, unsigned int num);
	
	void setSourceLittleEndian(bool isLittleEndian);
	int isLittleEndian();
private:
		FILE *m_hFile;
	int m_iLength;
	
	bool m_littleEndian; // is this computer little endian?
	bool m_sourceLittleEndian; // is the source saved as little endian?
	
};

#endif