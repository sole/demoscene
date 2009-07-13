class Event {
private:
	float start, length, power;
public:
	Event();
	Event(float _start, float _length, float _power);
	~Event();

	void setStart(float _start);
	void setLength(float _length);
	void setPower(float _power);
};