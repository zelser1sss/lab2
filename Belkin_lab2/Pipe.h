#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
class CS;

class Pipe
{
private:

	int id;
	std::string name;
	float length;
	int diameter;
	bool repair;

	static const std::vector<int> allowed_diameters;

public:

	Pipe() = default;
	Pipe(int id, const std::string& name, float length, int diameter, bool repair);

	int getId() const { return id; }
	std::string getName() const { return name; }
	float getLength() const { return length; }
	int getDiameter() const { return diameter; }
	bool getRepair() const { return repair; }

	void setId(int newId) { id = newId; }
	void setName(const std::string& newName) { name = newName; }
	void setLength(float newLength) { length = newLength; }
	bool setDiameter(int newDiameter);
	void setRepair(bool newRepair) { repair = newRepair; }

	static bool isValidDiameter(int diameter);
	static const std::vector<int>& getAllowedDiameters();

	friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
	friend std::istream& operator>>(std::istream& in, Pipe& pipe);
};

