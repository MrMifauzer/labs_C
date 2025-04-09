#include <iostream>
#include <string>

class Character {
private:
    std::string name;  // Приватное поле: имя персонажа
    int health;        // Приватное поле: уровень здоровья
    int attack;        // Приватное поле: уровень атаки
    int defense;       // Приватное поле: уровень защиты

    int maxHealth;      // Приватное поле: Предел очков здоровья (используется в heal)

public:
    // Конструктор для инициализации данных
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), maxHealth(h), attack(a), defense(d) {
    }

    // Метод для получения уровня здоровья
    int getHealth() const {
        return health;
    }

    // Метод для вывода информации о персонаже
    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    // Метод для атаки другого персонажа
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

    // Метод для восстановления здоровья
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

    // Метод для несмертельного урона
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
    // Создаем объекты персонажей
    Character hero("Hero", 100, 20, 10);
    Character monster("Goblin", 50, 15, 5);

    // Выводим информацию о персонажах
    hero.displayInfo();
    monster.displayInfo();

    // Герой атакует монстра
    hero.attackEnemy(monster);
    monster.displayInfo();

    // Монстр восстанавливается
    monster.heal(10);
    monster.displayInfo();

    //Герой спотыкается
    hero.takeDamege(999);
    hero.displayInfo();
    return 0;
}
