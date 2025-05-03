#include <iostream>
#include <string>

class Weapon {
private:
	std::string Name;
	int Damage;
	int Weight;
public:
	Weapon(const std::string& n, int d, int w) : Name(n), Damage(d), Weight(w) {}
	//Перегрузка +
	Weapon operator+(const Weapon& other) const {
		return Weapon(Name + " + " + other.Name, Damage + other.Damage, Weight + other.Weight);
	}
	// Перегрузка оператора <<
	friend std::ostream& operator<<(std::ostream& os, const Weapon& Weapon) {
		os << "Weapon: " << Weapon.Name << ", Damage: " << Weapon.Damage
			<< ", Weight: " << Weapon.Weight;
		return os;
	}
	//Перегрузка операторов сравнения
	bool operator>(const Weapon& other) const {
		return Damage > other.Damage;
	}
	bool operator<(const Weapon& other) const {
		return Damage < other.Damage;
	}
};

int main() {
	Weapon Sword("Sword", 10, 10);
	Weapon Bow("Bow", 15, 5);
	std::cout << Bow << std::endl;
	std::cout << Sword << std::endl;
	std::cout << Sword + Bow << std::endl;

	if (Sword > Bow) {
		std::cout << "Sword has more damage";
	}
	else { std::cout << "Bow has more damage" << std::endl; }
	if (Sword+Bow > Bow) {
		std::cout << "Sword+Bow has more damage";
	}
	else { std::cout << "Bow has more damage"<< std::endl; }

}