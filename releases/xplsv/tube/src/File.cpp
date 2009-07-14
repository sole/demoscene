#include "File.h"

int CFile::isLittleEndian() {
	union{ int a; char b; } u;
	u.a = 1;
	return u.b;
}

void CFile::setSourceLittleEndian(bool isLittleEndian) {
	this->m_littleEndian = isLittleEndian;
}

bool CFile::Open(const char *pszFile)
{
	m_hFile = fopen(pszFile, "rb");
	if (!m_hFile)
	{
		
		return false;
	}
	
	return (true);
}

void CFile::Close()
{
	if (m_hFile)
	{
		fclose(m_hFile);
		m_hFile = NULL;
	}
}

char CFile::ReadChar() {
	// No endianness fixing for char values
	if(m_hFile) {
		char buffer;
		fread(&buffer, sizeof(char), 1, m_hFile);
		return buffer;
	}
	return -1;
}

unsigned char CFile::ReadUChar() {
	// No endianness fixing for char values
	if(m_hFile) {
		unsigned char buffer;
		fread(&buffer, sizeof(unsigned char), 1, m_hFile);
		return buffer;
	}
	return 0;
}

void CFile::ReadCharArray(char* theArray, unsigned int num) {
	int i;
	for(i=0; i<num; i++) {
		theArray[i] = this->ReadChar();
	}
}

short CFile::ReadShort() {
	// a "short" is a short int which has size = 2 then we have to fix the endianness
	if(m_hFile) {
		short buffer, x;
		fread(&x, sizeof(short), 1, m_hFile);
		/*if((m_sourceLittleEndian==true) 
			&&
			(m_littleEndian==false))*/
		if(m_sourceLittleEndian!=m_littleEndian) {
			// needs fixing
			union {
				short s;
				char b[2];
			} dat1, dat2;
			dat1.s = x;
			dat2.b[0] = dat1.b[1];
			dat2.b[1] = dat1.b[0];
			buffer = dat2.s;
			//buffer = ((x<<8)|(x>>8));
		} else {
			buffer = x;
		}
		
		return buffer;
	}
	return -1;
}

void CFile::ReadShortArray(short* theArray, unsigned int num) {
	int i;
	for(i=0; i<num; i++) {
		theArray[i] = this->ReadShort();
	}
}

ushort CFile::ReadUshort() {
	// a "ushort" is a unsigned short int which has size = 2 then we have to fix the endianness
	if(m_hFile) {
		ushort buffer, x;
		fread(&x, sizeof(ushort), 1, m_hFile);
		if(m_sourceLittleEndian!=m_littleEndian) {
			// needs fixing
			buffer = ((x<<8)|(x>>8));
		} else {
			buffer = x;
		}
		
		return buffer;
	}
	return -1;
}


unsigned CFile::ReadUnsigned() {
	// an "unsigned" is an unsigned int which has size = 4 then we have to fix the endianness
	if(m_hFile) {
		unsigned buffer, x;
		fread(&x, sizeof(unsigned), 1, m_hFile);
		if(m_sourceLittleEndian!=m_littleEndian) {
			// needs fixing
			buffer = (x<<24)|((x<<8)&0x00FF0000)|((x>>8)&0x0000FF00)|(x>>24);
		} else {
			buffer = x;
		}
		
		return buffer;
	}
	return 0;
}

int CFile::ReadInt() {
	// Endianness must be fixed
	if(m_hFile) {
		int buffer, x;
		fread(&x, sizeof(int), 1, m_hFile);
		if(m_sourceLittleEndian!=m_littleEndian) {
			// needs fixing
			buffer = ((x<<24)|((x<<8)&0x00FF0000)|((x>>8)&0x0000FF00)|(x>>24));
		} else {
			buffer = x;
		}
		return buffer;
	}
	return -1;
}

void CFile::ReadIntArray(int* theArray, unsigned int num) {
	int i;
	for(i=0; i<num; i++) {
		theArray[i] = this->ReadInt();
	}
}

float CFile::ReadFloat() {
	// Endianness must be fixed
	if(m_hFile) {
		float buffer, x;
		fread(&x, sizeof(int), 1, m_hFile);
		if(m_sourceLittleEndian!=m_littleEndian) {
			// needs fixing
			union {
				float f;
				char b[4];
			} dat1, dat2;
			dat1.f = x;
			dat2.b[0] = dat1.b[3];
			dat2.b[1] = dat1.b[2];
			dat2.b[2] = dat1.b[1];
			dat2.b[3] = dat1.b[0];
			buffer = dat2.f;
		} else {
			buffer = x;
		}
		return buffer;
	}
	return -1;
}

void CFile::ReadFloatArray(float* theArray, unsigned int num) {
	int i;
	for(i=0; i<num; i++) {
		theArray[i] = this->ReadFloat();
	}
}
