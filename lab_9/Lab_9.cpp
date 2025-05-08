#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <random>
#include <ctime>
#include <iomanip>

// Шаблонный класс Logger
template<typename T>
class Logger {
    std::ofstream logFile;
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile) {
            throw std::runtime_error("Cannot open log file");
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const T& message) {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        tm tm_buffer;
        localtime_s(&tm_buffer, &now_time);  // Безопасная версия для Windows
        logFile << "[" << std::put_time(&tm_buffer, "%Y-%m-%d %H:%M:%S") << "] "
            << message << std::endl;
    }
};

// Глобальный логгер для простоты использования
Logger<std::string> gameLogger("game_log.txt");

// Функция для получения случайного числа с использованием времени как seed
int getRandomByTime(int min, int max) {
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    static std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

class Character;
class Monster;

// Базовый класс для предметов
class Item {
protected:
    std::string name;
    std::string description;
public:
    Item(const std::string& n, const std::string& desc) : name(n), description(desc) {}
    virtual ~Item() = default;

    virtual void use(Character& character) = 0;
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
};

// Класс инвентаря
class Inventory {
    std::vector<std::unique_ptr<Item>> items;
public:
    void addItem(std::unique_ptr<Item> item) {
        items.push_back(std::move(item));
        gameLogger.log("Added item to inventory: " + item->getName());
    }

    void removeItem(const std::string& itemName) {
        items.erase(
            std::remove_if(items.begin(), items.end(),
                [&](const std::unique_ptr<Item>& item) {
                    return item->getName() == itemName;
                }),
            items.end());
        gameLogger.log("Removed item from inventory: " + itemName);
    }

    void display() const {
        std::cout << "Inventory:\n";
        for (const auto& item : items) {
            std::cout << "- " << item->getName() << ": "
                << item->getDescription() << "\n";
        }
    }

    bool hasItem(const std::string& itemName) const {
        return std::any_of(items.begin(), items.end(),
            [&](const std::unique_ptr<Item>& item) {
                return item->getName() == itemName;
            });
    }
};

// Базовый класс монстров
class Monster {
protected:
    std::string name;
    int HP;
    int ATK;
public:
    Monster(std::string n, int hp, int ap) : name(n), HP(hp), ATK(ap) {}
    virtual ~Monster() = default;

    virtual void attack(Character& player) = 0;

    void displayInfo() const {
        std::cout << "Name: " << name << "\tHealth: " << HP
            << "\tAttack: " << ATK << std::endl;
    }

    int getHP() const { return HP; }
    std::string getName() const { return name; }
    void setHP(int amount) {
        HP = amount;
        if (HP < 0) HP = 0;
    }

    bool isAlive() const { return HP > 0; }
};

// Производные классы монстров
class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 15, 3) {}

    void attack(Character& player) override;
};

class Skeleton : public Monster {
public:
    Skeleton() : Monster("Skeleton", 25, 4) {}

    void attack(Character& player) override;
};

class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 50, 8) {}

    void attack(Character& player) override;
};

// Класс персонажа
class Character {
    std::string name;
    int HP;
    int maxHP;
    int ATK;
    int DP;
    int LVL;
    int XP;
    Inventory inventory;
public:
    Character(std::string n, int hp, int ap, int dp, int lvl)
        : name(n), HP(hp), maxHP(hp), ATK(ap), DP(dp), LVL(lvl), XP(0) {
    }

    void attack(Monster& enemy) {
        std::string msg = name + " attacks " + enemy.getName() + "!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);

        enemy.setHP(enemy.getHP() - ATK);

        msg = name + " inflicts " + std::to_string(ATK) + " damage!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }

    void Heal(int amount) {
        HP += amount;
        if (HP > maxHP) HP = maxHP;

        std::string msg = name + " heals for " + std::to_string(amount) + " HP!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }

    void getExp(int amount) {
        XP += amount;
        if (XP >= 100) {
            LVL++;
            XP -= 100;
            maxHP += 10;
            ATK += 2;
            DP += 1;
            HP = maxHP;

            std::string msg = name + " leveled up to level " + std::to_string(LVL) + "!";
            std::cout << msg << std::endl;
            gameLogger.log(msg);
        }
    }

    void displayInfo() const {
        std::cout << "Name: " << name << "\tLevel:" << LVL
            << "\nHealth: " << HP << "/" << maxHP
            << "\nAttack: " << ATK << "\nDefense: " << DP
            << "\nXP: " << XP << "/100" << std::endl;
    }

    Inventory& getInventory() { return inventory; }

    // Getters
    std::string getName() const { return name; }
    int getHP() const { return HP; }
    int getATK() const { return ATK; }
    int getDP() const { return DP; }
    int getLVL() const { return LVL; }
    int getXP() const { return XP; }

    // Setters
    void setHP(int value) {
        HP = value;
        if (HP < 0) HP = 0;
    }
};

// Реализации атак монстров
void Goblin::attack(Character& player) {
    std::string msg = name + " attacks with a rusty dagger!";
    std::cout << msg << std::endl;
    gameLogger.log(msg);

    int damage = ATK - player.getDP();
    if (damage > 0) {
        player.setHP(player.getHP() - damage);

        msg = name + " inflicts " + std::to_string(damage) + " damage!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }
    else {
        msg = "Attack has no effect!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }
}

void Skeleton::attack(Character& player) {
    std::string msg = name + " swings its bony arms!";
    std::cout << msg << std::endl;
    gameLogger.log(msg);

    int damage = ATK - player.getDP();
    if (damage > 0) {
        player.setHP(player.getHP() - damage);

        msg = name + " inflicts " + std::to_string(damage) + " damage!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }
    else {
        msg = "Attack has no effect!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }
}

void Dragon::attack(Character& player) {
    std::string msg = name + " breathes fire!";
    std::cout << msg << std::endl;
    gameLogger.log(msg);

    int damage = (ATK * 2) - player.getDP(); // Двойной урон
    if (damage > 0) {
        player.setHP(player.getHP() - damage);

        msg = name + " inflicts " + std::to_string(damage) + " damage!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }
    else {
        msg = "Attack has no effect!";
        std::cout << msg << std::endl;
        gameLogger.log(msg);
    }
}

// Класс игры
class Game {
    Character player;
    std::vector<std::unique_ptr<Monster>> monsters;
    bool gameRunning;

    void createMonsters() {
        monsters.push_back(std::make_unique<Goblin>());
        monsters.push_back(std::make_unique<Skeleton>());
        monsters.push_back(std::make_unique<Dragon>());
        gameLogger.log("Created monsters for the game");
    }

    void battle(Monster& monster) {
        gameLogger.log("Battle started with " + monster.getName());

        while (player.getHP() > 0 && monster.getHP() > 0) {
            player.displayInfo();
            monster.displayInfo();

            std::cout << "\n1. Attack\n2. Use Item\n3. Run\n";
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                player.attack(monster);
                if (monster.getHP() > 0) {
                    monster.attack(player);
                }
                break;
            case 2:
                // Реализация использования предмета
                std::cout << "Not implemented yet!\n";
                gameLogger.log("Player tried to use item (not implemented)");
                break;
            case 3:
                if (getRandomByTime(1, 100) > 50) { // 50% шанс убежать
                    std::cout << "You ran away!\n";
                    gameLogger.log("Player successfully ran away");
                    return;
                }
                else {
                    std::cout << "Failed to run away!\n";
                    gameLogger.log("Player failed to run away");
                    monster.attack(player);
                }
                break;
            default:
                std::cout << "Invalid choice!\n";
                gameLogger.log("Player made invalid choice in battle");
            }
        }

        if (player.getHP() > 0) {
            int xpReward = monster.getHP() * 2; // Награда за победу
            player.getExp(xpReward);

            std::string msg = "Player defeated the " + monster.getName() +
                " and gained " + std::to_string(xpReward) + " XP!";
            std::cout << msg << "\n";
            gameLogger.log(msg);
        }
        else {
            std::string msg = "Player was defeated by " + monster.getName() + "... Game Over!";
            std::cout << msg << "\n";
            gameLogger.log(msg);
            gameRunning = false;
        }
    }

public:
    Game() : player("Hero", 50, 5, 1, 1), gameRunning(true) {
        createMonsters();
        gameLogger.log("Game initialized");
    }

    void start() {
        std::cout << "Game started!\n";
        gameLogger.log("Game started");

        while (gameRunning) {
            std::cout << "\nChoose action:\n1. Battle\n2. Inventory\n3. Save\n4. Load\n5. Quit\n";
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1: {
                // Случайный выбор монстра с учетом времени
                int monsterIndex = getRandomByTime(0, monsters.size() - 1);
                battle(*monsters[monsterIndex]);
                break;
            }
            case 2:
                player.getInventory().display();
                gameLogger.log("Player viewed inventory");
                break;
            case 3:
                saveGame();
                break;
            case 4:
                loadGame();
                break;
            case 5:
                gameRunning = false;
                gameLogger.log("Player quit the game");
                break;
            default:
                std::cout << "Invalid choice!\n";
                gameLogger.log("Player made invalid main menu choice");
            }
        }
    }

    void saveGame() {
        std::ofstream file("savegame.txt");
        if (file) {
            file << player.getName() << "\n";
            file << player.getHP() << "\n";
            file << player.getATK() << "\n";
            file << player.getDP() << "\n";
            file << player.getLVL() << "\n";
            file << player.getXP() << "\n";
            std::cout << "Game saved!\n";
            gameLogger.log("Game saved successfully");
        }
        else {
            gameLogger.log("Failed to save game");
        }
    }

    void loadGame() {
        std::ifstream file("savegame.txt");
        if (file) {
            std::string name;
            int hp, atk, dp, lvl, xp;
            file >> name >> hp >> atk >> dp >> lvl >> xp;
            player = Character(name, hp, atk, dp, lvl);
            player.getExp(xp);
            std::cout << "Game loaded!\n";
            gameLogger.log("Game loaded successfully");
        }
        else {
            std::cout << "No save file found!\n";
            gameLogger.log("Failed to load game - no save file");
        }
    }
};

int main() {
    try {
        Game game;
        game.start();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        gameLogger.log(std::string("Fatal error: ") + e.what());
        return 1;
    }
    return 0;
}