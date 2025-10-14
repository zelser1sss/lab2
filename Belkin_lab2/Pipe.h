#pragma once
#include <string>
#include <vector>
#include <map>
class CS;

class Pipe
{
private:

	std::string name;
	float length;
	int diameter;
	bool repair;

public:

	Pipe() = default;
	Pipe(const std::string& name, float length, int diameter, bool repair);

	std::string getName() const { return name; }
	float getLength() const { return length; }
	int getDiameter() const { return diameter; }
	bool getRepair() const { return repair; }

	void setName(const std::string& newName) { name = newName; }
	void setLength(float newLength) { length = newLength; }
	void setDiameter(int newDiameter) { diameter = newDiameter; }
	void setRepair(bool newRepair) { repair = newRepair; }

};

