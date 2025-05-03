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
			throw std::out_of_range("������� ����� - �� ������� ������� �������");
		}
		elements.erase(elements.begin());
	}
	const T& front() const {
		if (elements.empty()) {
			throw std::out_of_range("������� ����� - �� ������� ������� �������");
		}
		return elements.front();
	}

	bool empty() const {
		return elements.empty();
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	std::cout << "=== �������� ������� ===" << std::endl;
	try
	{
		Queue<int> intQueue; // ������� ������� ��� ����� �����

		// ��������� �������� � �������
		intQueue.push(10);
		intQueue.push(20);
		intQueue.push(30);

		// ������� ������ �������
		std::cout << "������ �������: " << intQueue.front() << std::endl;

		// ������� ������ �������
		intQueue.pop();
		std::cout << "������ ������� ����� ��������: " << intQueue.front() << std::endl;

		// ������� ���������� ��������
		intQueue.pop();
		intQueue.pop();

		// ������� ������� �� ������ ������� - ������ ������� ����������
		intQueue.pop();
	}
	catch (const std::exception& e)
	{
		std::cerr << "������: " << e.what() << std::endl;
	}
	std::cout << "\n=== �������� ������� ����� ===" << std::endl;
	try
	{
		Queue<std::string> stringQueue; // ������� ������� ��� �����

		// ��������� �������� � �������
		stringQueue.push("������");
		stringQueue.push("���");
		stringQueue.push("!");

		// ������� ������ �������
		std::cout << "������ �������: " << stringQueue.front() << std::endl;

		// ������� ������ �������
		stringQueue.pop();
		std::cout << "������ ������� ����� ��������: " << stringQueue.front() << std::endl;

		// ������� ���������� ��������
		stringQueue.pop();
		stringQueue.pop();

		// ������� ������� �� ������ ������� - ������ ������� ����������
		stringQueue.pop();
	}
	catch (const std::exception& e)
	{
		std::cerr << "������: " << e.what() << std::endl;
	}
};