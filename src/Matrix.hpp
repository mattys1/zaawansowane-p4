#include <random>
#include <vector>

template <typename T>

class Matrix {
private:
	std::vector<T> data;
	int sideSize;
public:
	Matrix(void) {}

	Matrix(int n) : data(n * n), sideSize { n } {}

	Matrix(int n , int* t): data(n * n), sideSize { n } {
		std::copy(t, t + n * n, data.begin());
	} 

	Matrix(Matrix const& m) : data(m.data), sideSize { m.sideSize } {}

	Matrix& alokuj(int n){
		if(data.size() != n * n){
			data.resize(n * n);
			sideSize = n;
		}

		return *this;
	}

	int pokaz(int x, int y) const {
		return data[x * y];
	}

	Matrix& dowroc(void) {
		Matrix<T> temp(sideSize);

		for(int i = 0; i < sideSize; i++){
			for(int j = 0; j < sideSize; j++){
				temp.data[i * sideSize + j] = data[j * sideSize + i];
			}
		}

		*this = temp;
		return *this;
	}

	//wypełniamy cyframi od 0 do 9 wszystkie elementy 
	Matrix& losuj(void) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dis(0, 9);

		for(int i = 0; i < sideSize; i++){
			for(int j = 0; j < sideSize; j++){
				data[i * sideSize + j] = dis(gen);
			}
		}
	}

	Matrix& losuj(int x) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 9);

		for(int i = 0; i < x; i++){
			int a = dis(gen);
			int b = dis(gen);
			data[a * sideSize + b] = dis(gen);
		}
	}

	//po przekątnej są wpisane dane z tabeli, 
	/* a pozostałe elementy są równe 0,  */
	Matrix& diagonalna(int* t) {
		for(int i = 0; i < sideSize; i++){
			for(int j = 0; j < sideSize; j++){
				if(i == j){
					data[i * sideSize + j] = t[i];
				} else {
					data[i * sideSize + j] = 0;
				}
			}
		}
	}
};

