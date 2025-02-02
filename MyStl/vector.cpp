#include<iostream>
#include<stdexcept>
namespace MyStl {
	template<typename T>
	class vector {
	private:
		T* data; // ��������� �� ������ ������
		size_t capacity; // ����������� �������
		size_t size; // ����� ��������� �������
		
		void resize() {
			capacity *= 2;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i) { // ++i �� ������� �����, i++ ������� ����� �������
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}

	public:
		// ������� ������				 �������������� ����������� � ����� ���������
		vector(size_t baseCapacity = 10) : capacity(baseCapacity), size(0) {
			data = new T[capacity];
		}
		~vector() {
			delete[] data;
		}
		// ������� �����
		void pushBack(const T& value) {
			if (size >= capacity) {
				resize();
			}
			data[size++] = value;
		}
		// �������� ���������� ��������
		void popBack() {
			if (size > 0) {
				--size;
			}
			else {
				throw std::out_of_range("Vector is empty");
			}
		}
		size_t getSize() const {
			return size;
		}
		T& operator[](size_t index) {
			if (index >= size) {
				throw std::out_of_range("Index out of range");
			}
			return data[index];
		}

	};
}
