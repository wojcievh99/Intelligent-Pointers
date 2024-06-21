// temp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

class Mountain {
public:
	int height;
	std::string name;
	bool climbable;
	std::shared_ptr<std::vector<std::string>> people;
	std::vector<std::string>* people2;
};

class Terrain {
	std::vector<std::weak_ptr<Mountain>> ms;
public:
	std::string name;
	Terrain(std::vector<std::weak_ptr<Mountain>> mountains, std::string namet)
		: ms(mountains), name(namet) {
		std::cout << namet << " : st. OK " << std::endl;
	}

	friend void showMountainsOnThisGround(std::shared_ptr<Terrain>);
};

void showMountainsOnThisGround(std::shared_ptr<Terrain> t) {
	std::cout << "Mountains in the terrain of " << t->name << ":\n";
	for (const auto& mountain : (t->ms)) {
		mountain.lock()
			? std::cout << "\t" << mountain.lock()->name << std::endl
			: std::cout << "\t" << "No match" << std::endl;
	}
}

int main()
{
	setlocale(0, "");

	// shared
	std::shared_ptr<Mountain> m1 = 
		std::make_shared<Mountain>(8848, "Everest", true, 
			std::make_shared<std::vector<std::string>>(), // people
			new std::vector<std::string>({ "LL", "WW" }) // people2
			);
	
	std::cout << m1->people2 << std::endl;
	m1->people->push_back("KK");
	m1->people->push_back("MD");
	m1->people->push_back("KGB");

	std::cout << "People who climbed the " << m1->name << ":\n";
	for (const auto& person : *(m1->people)) {
		std::cout << "\t" << person << std::endl;
	}

	std::cout << "People who didn't climbed the " << m1->name << ":\n";
	for (const auto& person : *(m1->people2)) {
		std::cout << "\t" << person << std::endl;
	}

	std::shared_ptr<Mountain> mt =
		std::make_shared<Mountain>(8586, "Kanczenczonga", true,
			std::make_shared<std::vector<std::string>>(), // people
			new std::vector<std::string>({ "XX", "YY" }) // people2
		);

	// weak

	std::weak_ptr<Mountain> m2 = m1;
	std::weak_ptr<Mountain> m3 = mt;

	std::vector<std::weak_ptr<Mountain>> vt = {m2, m3};

	std::shared_ptr<Terrain> Himalaje =
		std::make_shared<Terrain>(
			vt, "Himalaje"
		);
	
	showMountainsOnThisGround(Himalaje);

}
