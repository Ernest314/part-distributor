#include <vector>
#include <string>

class Piece {
public:

private:
	int partCount;
	bool hasSolo;
	std::vector<int> partPriority;	// lower index = more important
	// Functions dealing with this might be inefficient, but it shouldn't
	// matter since this should be modified very rarely (e.g. upon creation).
	std::string title;
	std::string composer;

public:
	Piece(
		int partCount,
		bool hasSolo = false,
		std::string title = "",
		std::string composer = ""
	);
	Piece(
		int partCount,
		std::vector<int> partPriority,
		bool hasSolo = false,
		std::string title = "",
		std::string composer = ""
	);

int get_partCount()			{ return partCount; }
bool get_hasSolo()			{ return hasSolo; }
int get_partPriority(int part);
std::vector<int> get_partPriority()	{ return partPriority; }
std::string get_title()		{ return title; }
std::string get_composer()	{ return composer; }

void set_partCount(int partCount)		{ this->partCount = partCount; }
void set_hasSolo(bool hasSolo)			{ this->hasSolo = hasSolo; }

private:
	~Piece();
}