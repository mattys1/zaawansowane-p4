#include <random>
#include <vector>
#include <print>

template <typename T>

// replace sideSize with data.size()

class Matrix {
private:
	std::vector<std::vector<T>> data;
public:
	Matrix(void) {}

	Matrix(int n) : data(
		n, std::vector<T>(n)
	) {}

	Matrix(int n , int* t): data(
		n, std::vector<T>(n)
	) {
		for(auto& row : data){
			row = {t, t + n};
			t += n;
		}
	} 

	Matrix(Matrix const& m) : data(m.data) {}

	void wypisz(void) {
		for(const auto& row : data){
			for(const auto& elem : row) {
				std::print("{} ", elem);
			}
			
			std::println();
		}
	}

	Matrix& alokuj(int n){
		if(data.size() == 0){
			data.resize(n, std::vector<T>(n));
		} else {
			if(data.size() < n){
				data.resize(n, std::vector<T>(n));
			}
		}

		return *this;
	}

	int pokaz(int x, int y) const {
		return data[x][y];
	}

	Matrix& dowroc(void) {
		Matrix<T> temp(data.size());

		for(int i = 0; i < data.size(); i++){
			for(int j = 0; j < data.size(); j++){
				temp.data[i][j] = data[j][i];
			}
		}

		*this = temp;
		return *this;
	}

	Matrix& losuj(void) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dis(0, 9);

		for(int i = 0; i < data.size(); i++){
			for(int j = 0; j < data.size(); j++){
				data[i][j] = dis(gen);
			}
		}
		return *this;
	}

	Matrix& losuj(int x) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 9);

		for(int i = 0; i < x; i++){
			int a = dis(gen);
			int b = dis(gen);
			data[a][b] = dis(gen);
		}
		return *this;
	}

	Matrix& diagonalna(const int* t) {
		for(int i = 0; i < data.size(); i++){
			for(int j = 0; j < data.size(); j++){
				if(i == j){
					data[i][j] = t[i];
				} else {
					data[i][j] = 0;
				}
			}
		}

		return *this;
	}

	// po przekątnej są wpisane dane z tabeli, 
	/* a pozostałe elementy są równe 0. Parametr k może oznaczać: 0 - przekątna  */
	/* przechodząca przez środek (czyli tak jak metoda diagonalna), cyfra dodatnia przesuwa  */
	/* diagonalną do góry macierzy o podaną cyfrę, cyfra ujemna przesuwa diagonalną  */
	/* w dół o podaną cyfrę,  */
	Matrix& diagonalna_k(int k, int* t) {
		for(int i = 0; i < data.size(); i++){
			for(int j = 0; j < data.size(); j++){
				if(i == j + k){
					data[i][j] = t[j];
				} else {
					data[i][j] = 0;
				}
			}
		}

		return *this;
	}

	Matrix& kolumna(int x, int* t) {
		for(int i = 0; i < data.size(); i++){
			data[i][x] = t[i];
		}

		return *this;
	}

	Matrix& wiersz(int x, int* t) {
		for(int i = 0; i < data.size(); i++){
			data[x][i] = t[i];
		}

		return *this;
	}
};
