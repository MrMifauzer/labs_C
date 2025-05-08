#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <string>

class Character {
public:
    std::string name;
    int health;
    int attack;

    Character(std::string name, int health, int attack)
        : name(name), health(health), attack(attack) {
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    bool isAlive() const {
        return health > 0;
    }
    void SaveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file) {
            file << name << std::endl;
            file << health << std::endl;
            file << attack << std::endl;
            file.close();
        }
    };
    void loadFromFile(const std::string& filename) {
        std::ifstream in(filename);
        if (in) {
            std::getline(in, name);
            in >> health >> attack;
            in.close();
        }
    };
    void displayInfo() {
        std::cout << "Name: " << name << "\nhealth" << health << "\nAttack:" << attack << std::endl;
    }


};
std::mutex fightMutex;

void fight(Character& hero, Character& monster) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock(fightMutex);

        if (!hero.isAlive() || !monster.isAlive()) break;

        monster.takeDamage(hero.attack);
        std::cout << hero.name << " attacks " << monster.name << "! "
            << monster.name << " HP: " << monster.health << std::endl;

        if (!monster.isAlive()) break;

        hero.takeDamage(monster.attack);
        std::cout << monster.name << " attacks " << hero.name << "! "
            << hero.name << " HP: " << hero.health << std::endl;
    }

    std::cout << "\nBattle ended!" << std::endl;
    if (hero.isAlive())
        std::cout << hero.name << " won!\n";
    else
        std::cout << monster.name << " won!\n";
}

int main() {
    
    Character hero("Hero", 100, 15);
    Character monster("Goblin", 70, 10);
    hero.SaveToFile("Hero.txt");
    monster.SaveToFile("Monster.txt");
    std::thread fightThread(fight, std::ref(hero), std::ref(monster));
    fightThread.join();
    Character Bob("", 1, 1);
    Bob.loadFromFile("Bob.txt");
    Bob.displayInfo();
}
