#include <iostream>

template <typename T>
class My_vector {
protected:
	T* arr;
	unsigned size;
public:
	My_vector() {
		arr = nullptr;
		size = 0;
	}
	My_vector(unsigned _size) {
		size = _size;
		arr = new T[size];
	}
	My_vector(unsigned _size, T value = T()) {
		size = _size;
		arr = new T[size];
		for (unsigned int i = 0; i < size; i++) {
			arr[i] = value;
		}
	}
	My_vector(const My_vector <T>& other) {
		size = other.size;
		arr = new T[other.size];
		for (int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
	}
	My_vector<T>& operator = (const My_vector<T>& other) {
		size = other.size;
		arr = new T[other.size];
		for (int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
		return (*this);
	}

	int GetSize() {
		return size;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] << ' ';
		}
		std::cout << std::endl;
	}
	T& operator [] (int index) {
		if (index < size && index >= 0) {
			return arr[index];
		}
	}

	unsigned get_size() {
		return size;
	}
	void set_size(unsigned _size) {
		size = _size;
	}
	void set_el(T el, int index) {
		arr[index] = el;
	}
	void swap(int a, int b) {
		T tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
	}
	~My_vector() {
		delete[] arr;
		arr = nullptr;
		size = 0;
	}
};

template <typename T>
class Matrix :public My_vector <My_vector<T>> {
protected:
public:
	Matrix(int _n) :
		My_vector<My_vector<T>>(_n, My_vector<T>(_n, 0)) { this->size = _n; };
	Matrix(int _n, T a) :
		My_vector<My_vector<T>>(_n, My_vector<T>(_n, a)) { this->size = _n; };
	
	~Matrix() {}

	void print() {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				std::cout << this->arr[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	My_vector<T>& operator [] (int i) {
		if (i < this->size && i >= 0) {
			return this->arr[i];
		}
	}
	void swap(int a, int b) {
		My_vector<T> tmp = this->arr[a];
		this->arr[a] = this->arr[b];
		this->arr[b] = tmp;
	}
};

template <typename T>
class SLAU: public Matrix<T> {
private:
public:
	SLAU (int _n) : Matrix<T>(_n) {};
	SLAU (int _n, T a) : Matrix<T>(_n, a) {};
	~SLAU() {};
	My_vector<T> Gauss(My_vector<T> a) {
		if (this->size == 0) {
			throw "Error: Matrix's size = 0";
		}
		My_vector<T> answer = a;
		for (int i = 0; i < this->size; i++) {
			for (int i = 0; i < this->size; i++) {
				int f = 0;
				for (int j = 0; j < this->size; j++) {
					if (this->arr[i][j] != 0) {
						f = 1;
						break;
					}
				}
				if (f == 0) {
					throw "infinitely many solutions";
				}
			}
			if (this->arr[i][i] == 0) {
				for (int l = 0; l < this->size - 1; l++) {
					if (this->arr[l][i] != 0) {
						this->swap(i, l);
						answer.swap(i, l);
						i--;
						break;
					}
				}
			}
			for (int j = 0; j < this->size; j++) {
				if (i != j) {
					double k = this->arr[j][i] / this->arr[i][i];
					for (int h = 0; h < this->size; h++) {
						this->arr[j][h] -= k * this->arr[i][h];
					}
					answer[j] -= k * answer[i];
				}
			}
		}
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (i == j) {
					answer[j] = answer[j] / this->arr[i][i];
					this->arr[i][i] = 1;
				}
			}
		}
		return answer;
	}
};

int main() {
	std::cout << "enter size of matrix\n";
	int n;
	std::cin >> n;
	SLAU<double> m(n);
	std::cout << "enter matrix elements\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> m[i][j];
		}
	}
	m.print();
	std::cout << "enter the right part of system\n";
	My_vector<double> v(n, 1);
	for (int i = 0; i < n; i++) {
		std::cin >> v[i];
	}
	try {
		My_vector<double> ans = m.Gauss(v);
		std::cout << "answer: ";
		ans.print();
	}
	catch (const char* error_mess) {
		std::cout << error_mess << "\n";
	}
}
