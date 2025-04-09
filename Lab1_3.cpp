#include <iostream>
#include <string>

class Entity {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Entity(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
    }


    virtual void attackEnemy(Entity& target) {
        int damage = attack - target.defense;
        if (damage > 0) {
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }

  
    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    virtual void heal(Entity& target ,int point) { //для лечения была добавлена цель
        target.setHp(point);
        std::cout << name << " restores " << point << " heals " << target.getName() << std::endl;
    }
    //Методы доступа
    int getDef()
    {
        return(defense);
    }

    int getAtk()
    {
        return(attack);
    }

    int getHp()
    {
        return(health);
    }
    void setHp(int point)
    {
        health += point;
    }
    std::string getName() 
    { 
        return(name);
    }
    
    virtual ~Entity() {}
};
class Character : public Entity {
public:
    Character(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {
    }

    // Переопределение метода attack
    void attackEnemy(Entity& target) override {
        int damage = attack - target.getDef();
        if (damage > 0) {
            // Шанс на критический удар (20%)
            if (rand() % 100 < 20) {
                damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.setHp(-damage);
            std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }


    void displayInfo() const override {
        std::cout << "Character: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
    void heal(Entity& target, int point) override { // Переопределение исцеления
        target.setHp(point*2); // Герой лечится в 2 раза лучше
        std::cout<< "Holy " << name << " restores " << point*2 << " heals " << target.getName() << std::endl;
    }
};

class Monster : public Entity {
public:
    Monster(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {
    }


    void attackEnemy(Entity& target) override {
        int damage = attack - target.getDef();
        if (damage > 0) {
            // Шанс на ядовитую атаку (30%)
            if (rand() % 100 < 30) {
                damage += 5; // Дополнительный урон от яда
                std::cout << "Poisonous attack! ";
            }
            target.setHp(-damage);
            std::cout << name << " attacks " << target.getName()<< " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        std::cout << "Monster: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

//Класс Boss
class Boss : public Monster {
public:
    Boss(const std::string& n, int h, int a, int d)
        : Monster(n, h, a, d) {
    }
    void attackEnemy(Entity& target) override {
        int damage = attack - target.getDef() / 2; //Боссы подавляют врага, ему сложнее защищаться
        if (damage > 0) {
            // Шанс на испепеление (90% для наглядности)
            if (rand() % 100 < 90) {
                damage = target.getHp(); //Урон равен здороью цели
                std::cout << "BREEDING! ";
            }
            target.setHp(-damage);// И этот урон не уменьшается броней
            std::cout << name << " bites " << target.getName() << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " bites " << target.getName() << ", but it has no effect!\n";
        }
    }
    void displayInfo() const override {
        std::cout << "Monster: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense 
            << "\n Special ability: 90% chance to incinerate the enemy." << std::endl;
    }
};


int main() {
    srand(static_cast<unsigned>(time(0)));

  
    Character hero("Hero", 100, 20, 10);
    Monster goblin("Goblin", 50, 15, 5);
    Boss dragon("Dragon", 150, 25, 20); //  Дракон переквалифицирован в босса

 
    Entity* entities[] = { &hero, &goblin, &dragon };

    for (auto& entity : entities) {
        entity->displayInfo(); 
    }

  
    hero.attackEnemy(dragon);
    goblin.attackEnemy(hero);
    hero.heal(hero, 10);
    for (auto& entity : entities) {
        entity->displayInfo();
    }
    dragon.attackEnemy(hero);

    return 0;
}
