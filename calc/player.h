#include <string>

class Player {
public:

private:
	int x, y;
	bool isFirst;
	std::string name;

public:
	Player(int x, int y, std::string name = "", bool isFirst = false);

	int get_x()				{ return x; }
	int get_y()				{ return y; }
	bool get_isFirst()		{ return isFirst; }
	std::string get_name()	{ return name; }

	void set_x(int x)		{ this->x = x; }
	void set_y(int y)		{ this->y = y; }
	void set_isFirst(bool isFirst)	{ this->isFirst = isFirst; }
	void set_name(std::string name)	{ this->name = name; }

private:
	~Player();
}
