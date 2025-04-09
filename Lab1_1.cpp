#include <iostream>
#include <string>

class Character {
private:
    std::string name;  // Ïðèâàòíîå ïîëå: èìÿ ïåðñîíàæà
    int health;        // Ïðèâàòíîå ïîëå: óðîâåíü çäîðîâüÿ
    int attack;        // Ïðèâàòíîå ïîëå: óðîâåíü àòàêè
    int defense;       // Ïðèâàòíîå ïîëå: óðîâåíü çàùèòû

    int maxHealth;      // Ïðèâàòíîå ïîëå: Ïðåäåë î÷êîâ çäîðîâüÿ (èñïîëüçóåòñÿ â heal)

public:
    // Êîíñòðóêòîð äëÿ èíèöèàëèçàöèè äàííûõ
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), maxHealth(h), attack(a), defense(d) {
    }

    // Ìåòîä äëÿ ïîëó÷åíèÿ óðîâíÿ çäîðîâüÿ
    int getHealth() const {
        return health;
    }

    // Ìåòîä äëÿ âûâîäà èíôîðìàöèè î ïåðñîíàæå
    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    // Ìåòîä äëÿ àòàêè äðóãîãî ïåðñîíàæà
    void attackEnemy(Character& enemy) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.health -= damage;
            std::cout << name << " attacks " << enemy.name << " for " << damage << " damage!" << std::endl;
        }
        else {
            std::cout << name << " attacks " << enemy.name << ", but it has no effect!" << std::endl;
        }
    }

    // Ìåòîä äëÿ âîññòàíîâëåíèÿ çäîðîâüÿ
    void heal(int point) {
        health += point;
        if (health > maxHealth) {
            health = maxHealth;
            std::cout << name << " is restored to the limit of " << health << "health!" << std::endl;
        }
        else {
            std::cout << name << " is restored to " << point << " health!" << std::endl;
        }
    }

    // Ìåòîä äëÿ íåñìåðòåëüíîãî óðîíà
    void takeDamege(int point) {
        health -= point;
        if (health <= 0) {
            std::cout << name << " receives deadly damage, but survives!" << std::endl;
            health = 1;
        }
        else {
            std::cout << name << " receives " << point << " damage!"<<std::endl;
        }
    }
};

int main() {
    // Ñîçäàåì îáúåêòû ïåðñîíàæåé
    Character hero("Hero", 100, 20, 10);
    Character monster("Goblin", 50, 15, 5);

    // Âûâîäèì èíôîðìàöèþ î ïåðñîíàæàõ
    hero.displayInfo();
    monster.displayInfo();

    // Ãåðîé àòàêóåò ìîíñòðà
    hero.attackEnemy(monster);
    monster.displayInfo();

    // Ìîíñòð âîññòàíàâëèâàåòñÿ
    monster.heal(10);
    monster.displayInfo();

    //Ãåðîé ñïîòûêàåòñÿ
    hero.takeDamege(999);
    hero.displayInfo();
    return 0;
}
