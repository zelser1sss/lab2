#pragma once
#include <string>

class CS
{
private:

	std::string name;
	int k_cex;
	int k_cex_in_work;
	std::string type;

public:

	CS() = default;
	CS(const std::string& name, int k_cex, int k_cex_in_work, const std::string& type);

	std::string getName() const { return name; }
	int getKCex() const { return k_cex; }
	int getKCexInWork() const { return k_cex_in_work; }
	std::string getType() const { return type; }

	void setName(const std::string& newName) { name = newName; }
	void setKCex(int newKCex) { k_cex = newKCex; }
	void setKCexInWork(int newKCexInWork) { k_cex_in_work = newKCexInWork; }
	void setType(const std::string& newType) { type = newType; }

	float getUnusedPercent() const;
	bool startWorkshops(int count);
	bool stopWorkshops(int count);

};

