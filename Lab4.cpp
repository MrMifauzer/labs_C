#include <iostream>
#include <memory>
#include <string>

class Inventory {
private:
    std::unique_ptr<std::string[]> items;  // ������������ ������ �����
    size_t capacity;                       // ������� �����������
    size_t size;                           // ������� ���������� ���������

    // ����������� ����������� ������� ��� �������������
    void resize() {
        capacity *= 2;  // ��������� �����������
        auto newItems = std::make_unique<std::string[]>(capacity);

        // �������� ������ ��������
        for (size_t i = 0; i < size; ++i) {
            newItems[i] = items[i];
        }

        items = std::move(newItems);  // ���������� ����� ������
    }

public:
    // �����������
    Inventory() : capacity(5), size(0) {
        items = std::make_unique<std::string[]>(capacity);
    }

    // ���������� ��������
    void addItem(const std::string& item) {
        if (size >= capacity) {
            resize();  // ����������� ������, ���� �� ��������
        }
        items[size++] = item;  // ��������� �������
    }

    // ����� ���������
    void displayInventory() const {
        if (size == 0) {
            std::cout << "��������� ����.\n";
            return;
        }

        std::cout << "=== ��������� ===\n";
        for (size_t i = 0; i < size; ++i) {
            std::cout << "- " << items[i] << "\n";
        }
        std::cout << "=================\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Inventory inv;

    // ��������� ��������
    inv.addItem("���");
    inv.addItem("���");
    inv.addItem("����� ��������");
    inv.addItem("���");
    inv.addItem("������");
    inv.addItem("������ ����");  // ������� resize()

    // ������� ���������
    inv.displayInventory();

    return 0;
}