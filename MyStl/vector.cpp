#include<iostream>
#include<stdexcept>
namespace MyStl {
	template<typename T>
	class vector {
	private:
		T* data; // указатель на массив данных
		size_t capacity; // вместимость массива
		size_t size; // число элементов массива
		
		void resize() {
			capacity *= 2;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i) { // ++i не создает копию, i++ создает копию объекта
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}

	public:
		// базовый размер				 инициализируем вместимость и число элементов
		vector(size_t baseCapacity = 10) : capacity(baseCapacity), size(0) {
			data = new T[capacity];
		}
		~vector() {
			delete[] data;
		}
		// вставка назад
		void pushBack(const T& value) {
			if (size >= capacity) {
				resize();
			}
			data[size++] = value;
		}
		// удаление последнего элемента
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
