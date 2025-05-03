#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Queue {
private:

	std::vector<T> elements;

public:
	void push(const T& item) {
		elements.push_back(item);
	};
	void pop() {
		if (elements.empty()) {
			throw std::out_of_range("Очередь пуста - не удалось удалить элемент");
		}
		elements.erase(elements.begin());
	}
	const T& front() const {
		if (elements.empty()) {
			throw std::out_of_range("Очередь пуста - не удалось вывести элемент");
		}
		return elements.front();
	}

	bool empty() const {
		return elements.empty();
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	std::cout << "=== Тестовая очередь ===" << std::endl;
	try
	{
		Queue<int> intQueue; // Создаем очередь для целых чисел

		// Добавляем элементы в очередь
		intQueue.push(10);
		intQueue.push(20);
		intQueue.push(30);

		// Выводим первый элемент
		std::cout << "Первый элемент: " << intQueue.front() << std::endl;

		// Удаляем первый элемент
		intQueue.pop();
		std::cout << "Первый элемент после удаления: " << intQueue.front() << std::endl;

		// Удаляем оставшиеся элементы
		intQueue.pop();
		intQueue.pop();

		// Попытка удалить из пустой очереди - должно вызвать исключение
		intQueue.pop();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Ошибка: " << e.what() << std::endl;
	}
	std::cout << "\n=== Тестовая осередь строк ===" << std::endl;
	try
	{
		Queue<std::string> stringQueue; // Создаем очередь для строк

		// Добавляем элементы в очередь
		stringQueue.push("Привет");
		stringQueue.push("Мир");
		stringQueue.push("!");

		// Выводим первый элемент
		std::cout << "Первый элемент: " << stringQueue.front() << std::endl;

		// Удаляем первый элемент
		stringQueue.pop();
		std::cout << "Первый элемент после удаления: " << stringQueue.front() << std::endl;

		// Удаляем оставшиеся элементы
		stringQueue.pop();
		stringQueue.pop();

		// Попытка удалить из пустой очереди - должно вызвать исключение
		stringQueue.pop();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Ошибка: " << e.what() << std::endl;
	}
};