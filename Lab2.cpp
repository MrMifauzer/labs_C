#include <iostream>
#include <string>

class Character {
private:
	std::string name;
	int health;
	int attack;
	int defense;

public:
	// Конструктор
	Character(const std::string& n, int h, int a, int d)
		: name(n), health(h), attack(a), defense(d) {
		std::cout << "Character " << name << " created!\n";
	}

	// Деструктор
	~Character() {
		std::cout << "Character " << name << " destroyed!\n";
	}

	void displayInfo() const {
		std::cout << "Name: " << name << ", HP: " << health
			<< ", Attack: " << attack << ", Defense: " << defense << std::endl;
	}
};

class Monster {
private:
	std::string name;
	int health;
	int attack;
	int defense;

public:
	// Конструктор
	Monster(const std::string& n, int h, int a, int d)
		: name(n), health(h), attack(a), defense(d) {
		std::cout << "Monster " << name << " created!\n";
	}

	// Деструктор
	~Monster() {
		std::cout << "Monster " << name << " destroyed!\n";
	}

	void displayInfo() const {
		std::cout << "Name: " << name << ", HP: " << health
			<< ", Attack: " << attack << ", Defense: " << defense << std::endl;
	}
};

// Класс Weapon
class Weapon {
	std::string name;
	int damage;
	int weight;
public:
	// Конструктор
	Weapon(const std::string& n, int d, int w) : name(n), damage(d), weight(w) { 
		std::cout << name << " Noticed! "<< std::endl;
	}
	// Вывод информации
	void displayInfo() {
		std::cout << "Name: " << name << "\nHP: " << damage
			<< "\nWeight: " << weight <<"\n" << std::endl;
	}
	// Деструктор
	~Weapon() { std::cout << name << " destroid!"<< std::endl; }
};

int main() {
	Weapon wp1("Goblin Knife", 5, 3);
	Weapon wp2("Great Sword", 70, 50);
	Weapon wp3("Holy Grail", 999, 999);
	std::cout<< std::endl;
	wp1.displayInfo();
	wp2.displayInfo();
	wp3.displayInfo();
	std::cout << std::endl;
}