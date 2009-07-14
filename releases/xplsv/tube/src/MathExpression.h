#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

#include <string>
#include <map>

class MathExpression {
public:
	MathExpression(void);
	MathExpression(std::string expression);
	float value();
	float parse(std::string expression);
	void setExpression(std::string strExpression);
	void setVar(std::string strVariable, float value);
	enum {
		MATHEXP_EXP,
		MATHEXP_NUMBER,
		MATHEXP_OPERATOR,
		MATHEXP_VARIABLE,
		MATHEXP_UNKNOWN
	};
private:
		bool m_isUpdated;
		float m_fValue;
	std::string m_strExpression;
	std::map<std::string, float> m_Variables;
		std::string findToken(std::string expression, std::string *strRemaining);
		int findTokenType(std::string token);
		float findVariable(std::string strVariable);
};

#endif
