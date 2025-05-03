#include <iostream>
#include <memory>
#include <string>

class Inventory {
private:
    std::unique_ptr<std::string[]> items;  // Динамический массив строк
    size_t capacity;                       // Текущая вместимость
    size_t size;                           // Текущее количество предметов

    // Увеличивает вместимость массива при необходимости
    void resize() {
        capacity *= 2;  // Удваиваем вместимость
        auto newItems = std::make_unique<std::string[]>(capacity);

        // Копируем старые элементы
        for (size_t i = 0; i < size; ++i) {
            newItems[i] = items[i];
        }

        items = std::move(newItems);  // Перемещаем новый массив
    }

public:
    // Конструктор
    Inventory() : capacity(5), size(0) {
        items = std::make_unique<std::string[]>(capacity);
    }

    // Добавление предмета
    void addItem(const std::string& item) {
        if (size >= capacity) {
            resize();  // Увеличиваем массив, если он заполнен
        }
        items[size++] = item;  // Добавляем предмет
    }

    // Вывод инвентаря
    void displayInventory() const {
        if (size == 0) {
            std::cout << "Инвентарь пуст.\n";
            return;
        }

        std::cout << "=== Инвентарь ===\n";
        for (size_t i = 0; i < size; ++i) {
            std::cout << "- " << items[i] << "\n";
        }
        std::cout << "=================\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Inventory inv;

    // Добавляем предметы
    inv.addItem("Меч");
    inv.addItem("Щит");
    inv.addItem("Зелье здоровья");
    inv.addItem("Лук");
    inv.addItem("Стрелы");
    inv.addItem("Кольцо маны");  // Вызовет resize()

    // Выводим инвентарь
    inv.displayInventory();

    return 0;
}