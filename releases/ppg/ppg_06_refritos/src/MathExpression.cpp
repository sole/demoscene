#include "MathExpression.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MathExpression::MathExpression(void) {
	m_isUpdated = false;
}

MathExpression::MathExpression(std::string expression) {
	m_strExpression = expression;
	MathExpression();
}

float MathExpression::value() {
	if(m_isUpdated) {
		return m_fValue;
	} else {
		m_fValue = parse(m_strExpression);
		m_isUpdated = true;
		return m_fValue;
	}
}

float MathExpression::parse(std::string expression) {
	float fResult = 0;
	float fLeft, fRight;
	bool isReady = false;
	string strToken;
	string strRemaining;
	
	// Obtener token --------------------------------------------------
	unsigned int iTokenType;
	strToken = findToken(expression, &strRemaining);
	
	
	iTokenType = findTokenType(strToken);
	
	switch(iTokenType) {
		case MATHEXP_VARIABLE:
			fResult = this->findVariable(strToken);
			break;
		case MATHEXP_NUMBER:
			fResult = atof(strToken.c_str());
			break;
	}
	
	return fResult;
}

void MathExpression::setExpression(std::string strExpression) {
	this->m_strExpression = strExpression;
	m_isUpdated = false;
}

void MathExpression::setVar(std::string strVariable, float value) {
	// TODO
	m_isUpdated = false;
	this->m_Variables[strVariable] = value;
}

std::string MathExpression::findToken(std::string expression, std::string *strRemaining) {
	std:string token;
	unsigned int nextSpace = expression.find_first_of(" ");
	if(nextSpace > expression.length()) {
		token = expression;
		*strRemaining = "";
	} else {
		token = expression.substr(0, nextSpace);
	}
	
	return token;
}
int MathExpression::findTokenType(std::string token) {
	unsigned int i, iTokenLength = token.length();
	int tokenType = -1;
	char c;
	/*
	 MATHEXP_EXP,
	 MATHEXP_NUMBER,
	 MATHEXP_OPERATOR,
	 MATHEXP_VARIABLE,
	 MATHEXP_UNKNOWN
	 */
	
	i=0;
	while(i<iTokenLength) {
		c = token.at(i);
		if( c>='0' && c<='9') {
			if( (tokenType!=MATHEXP_VARIABLE) && (tokenType!=MATHEXP_EXP) ) 
				tokenType = MATHEXP_NUMBER;
		} else  if(c>='A' && c<='z') {
			if(tokenType == MATHEXP_NUMBER)
				tokenType = MATHEXP_UNKNOWN;
			else if (tokenType==-1)
				tokenType = MATHEXP_VARIABLE;
		} else {
		}
		i++;
	}
	
	
	return tokenType;
}

float MathExpression::findVariable(std::string strVariable) {
	for(map<string, float>::iterator i = m_Variables.begin();
		i != m_Variables.end();
		i++) {
		if(strVariable == i->first) {
			return i->second;
		}
	}
	return 0;
}
