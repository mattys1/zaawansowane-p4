#include <random>
#include <vector>
#include <print>
#include <cmath>
#include <iostream>

/**
 * @brief Klasa reprezentująca macierz.
 * 
 * @tparam T Typ danych przechowywanych w macierzy.
 */
template <typename T>
class Matrix {
private:
	std::vector<std::vector<T>> data;

public:
	/**
	 * @brief Konstruktor domyślny.
	 */
	Matrix(void) {}

	/**
	 * @brief Konstruktor tworzący macierz o rozmiarze n x n.
	 * 
	 * @param n Rozmiar macierzy.
	 */
	Matrix(int n) : data(n, std::vector<T>(n)) {}

	/**
	 * @brief Konstruktor tworzący macierz o rozmiarze n x n i wypełniający ją danymi z tablicy.
	 * 
	 * @param n Rozmiar macierzy.
	 * @param t Wskaźnik do tablicy z danymi.
	 */
	Matrix(int n, int* t) : data(n, std::vector<T>(n)) {
		for(auto& row : data){
			row = {t, t + n};
			t += n;
		}
	}

	/**
	 * @brief Konstruktor kopiujący.
	 * 
	 * @param m Obiekt macierzy do skopiowania.
	 */
	Matrix(Matrix const& m) : data(m.data) {}

	/**
	 * @brief Wypisuje zawartość macierzy.
	 */
	void wypisz(void) {
		for(const auto& row : data){
			for(const auto& elem : row) {
				std::print("{} ", elem);
			}
			std::println();
		}
	}

	/**
	 * @brief Alokuje pamięć dla macierzy o rozmiarze n x n.
	 * 
	 * @param n Rozmiar macierzy.
	 * @return Referencja do obiektu macierzy.
	 */
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

	/**
	 * @brief Zwraca wartość elementu macierzy na pozycji (x, y).
	 * 
	 * @param x Wiersz.
	 * @param y Kolumna.
	 * @return Wartość elementu macierzy.
	 */
	int pokaz(int x, int y) const {
		return data[x][y];
	}

	/**
	 * @brief Odwraca macierz (transpozycja).
	 * 
	 * @return Referencja do obiektu macierzy.
	 */
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

	/**
	 * @brief Wypełnia macierz losowymi wartościami od 0 do 9.
	 * 
	 * @return Referencja do obiektu macierzy.
	 */
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

	/**
	 * @brief Wypełnia x losowych elementów macierzy wartościami od 0 do 9.
	 * 
	 * @param x Liczba elementów do wypełnienia.
	 * @return Referencja do obiektu macierzy.
	 */
	Matrix& losuj(int x) {
		if (data.size() == 0) return *this;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 9);

		int n = (int)data.size();
		for (int i = 0; i < x; i++) {
			int a = dis(gen) % n; // zabezpieczenie przed wyjściem poza zakres
			int b = dis(gen) % n; // j.w.
			data[a][b] = dis(gen);
		}
		return *this;
	}

	/**
	 * @brief Wypełnia przekątną macierzy wartościami z tablicy t, pozostałe elementy są równe 0.
	 * 
	 * @param t Wskaźnik do tablicy z wartościami.
	 * @return Referencja do obiektu macierzy.
	 */
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

	/**
	 * @brief Wypełnia przekątną macierzy wartościami z tablicy t, przesuniętą o k pozycji.
	 * 
	 * @param k Przesunięcie przekątnej.
	 * @param t Wskaźnik do tablicy z wartościami.
	 * @return Referencja do obiektu macierzy.
	 */
	Matrix& diagonalna_k(int k, const int* t) {
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

	/**
	 * @brief Wypełnia kolumnę x wartościami z tablicy t.
	 * 
	 * @param x Numer kolumny.
	 * @param t Wskaźnik do tablicy z wartościami.
	 * @return Referencja do obiektu macierzy.
	 */
	Matrix& kolumna(int x, const int* t) {
		for(int i = 0; i < data.size(); i++){
			data[i][x] = t[i];
		}
		return *this;
	}

	/**
	 * @brief Wypełnia wiersz x wartościami z tablicy t.
	 * 
	 * @param x Numer wiersza.
	 * @param t Wskaźnik do tablicy z wartościami.
	 * @return Referencja do obiektu macierzy.
	 */
	Matrix& wiersz(int x, const int* t) {
		for(int i = 0; i < data.size(); i++){
			data[x][i] = t[i];
		}
		return *this;
	}

	/**
	 * @brief Wypełnia macierz: 1 na przekątnej, 0 poza przekątną.
	 * 
	 * @return Referencja do obiektu macierzy.
	 */
	Matrix& przekatna(void) {
		for(int i = 0; i < data.size(); i++){
			for(int j = 0; j < data.size(); j++){
				if(i == j){
					data[i][j] = 1;
				} else {
					data[i][j] = 0;
				}
			}
		}
		return *this;
	}

	/**
	 * @brief Wypełnia macierz: 1 pod przekątną, 0 nad przekątną i na przekątnej.
	 * 
	 * @return Referencja do obiektu macierzy.
	 */
	Matrix& pod_przekatna(void) {
		for(int i = 0; i < data.size(); i++){
			for(int j = 0; j < data.size(); j++){
				if(i > j){
					data[i][j] = 1;
				} else {
					data[i][j] = 0;
				}
			}
		}
		return *this;
	}

	/**
	 * @brief Wypełnia macierz: 1 nad przekątną, 0 pod przekątną i na przekątnej.
	 * 
	 * @return Referencja do obiektu macierzy.
	 */
	Matrix& nad_przekatna(void) {
		for(int i = 0; i < data.size(); i++){
			for(int j = 0; j < data.size(); j++){
				if(i < j){
					data[i][j] = 1;
				} else {
					data[i][j] = 0;
				}
			}
		}
		return *this;
	}

	//..................................................................

	// wstaw(int x, int y, int wartosc)
	Matrix& wstaw(int x, int y, int wartosc) {
		data[x][y] = wartosc;
		return *this;
	}

	// szachownica()
	Matrix& szachownica(void) {
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data.size(); j++) {
				data[i][j] = ((i + j) % 2 == 0) ? 0 : 1;
			}
		}
		return *this;
	}

	// operator+(matrix& m) // A = A + m
	Matrix& operator+(Matrix const& m) {
		// Sprawdzenie wymiarów
		if (data.size() != m.data.size()) {
			// Nie zmieniamy nic jeśli wymiary nie pasują
			return *this;
		}

		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data.size(); j++) {
				data[i][j] += m.data[i][j];
			}
		}
		return *this;
	}

	// operator*(matrix& m) // A = A * m
	Matrix& operator*(Matrix const& m) {
		// Sprawdzenie czy można mnożyć: (n x n) * (n x n) -> OK jeżeli rozmiary są takie same
		int n = (int)data.size();
		if (n == 0 || n != (int)m.data.size()) {
			// Nie zmieniamy nic jeśli nie da się mnożyć
			return *this;
		}

		Matrix<T> result(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				T sum = 0;
				for (int k = 0; k < n; k++) {
					sum += data[i][k] * m.data[k][j];
				}
				result.data[i][j] = sum;
			}
		}
		*this = result;
		return *this;
	}

	// operator+(int a) // A = A + a
	Matrix& operator+(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += a;
			}
		}
		return *this;
	}

	// operator*(int a) // A = A * a
	Matrix& operator*(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem *= a;
			}
		}
		return *this;
	}

	// operator-(int a) // A = A - a
	Matrix& operator-(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem -= a;
			}
		}
		return *this;
	}

	// friend matrix operator+(int a, matrix& m)
	friend Matrix operator+(int a, Matrix const& m) {
		Matrix result(m);
		for (auto& row : result.data) {
			for (auto& elem : row) {
				elem = a + elem;
			}
		}
		return result;
	}

	// friend matrix operator*(int a, matrix& m)
	friend Matrix operator*(int a, Matrix const& m) {
		Matrix result(m);
		for (auto& row : result.data) {
			for (auto& elem : row) {
				elem = a * elem;
			}
		}
		return result;
	}

	// friend matrix operator-(int a, matrix& m)
	friend Matrix operator-(int a, Matrix const& m) {
		Matrix result(m);
		for (auto& row : result.data) {
			for (auto& elem : row) {
				elem = a - elem;
			}
		}
		return result;
	}

	// operator++(int) // A++ zwiększa wszystkie elementy o 1
	Matrix& operator++(int) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += 1;
			}
		}
		return *this;
	}

	// operator--(int) // A-- zmniejsza wszystkie elementy o 1
	Matrix& operator--(int) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem -= 1;
			}
		}
		return *this;
	}

	// operator+=(int a) // każdy element powiększamy o a
	Matrix& operator+=(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += a;
			}
		}
		return *this;
	}

	// operator-=(int a)
	Matrix& operator-=(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem -= a;
			}
		}
		return *this;
	}

	// operator*=(int a)
	Matrix& operator*=(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem *= a;
			}
		}
		return *this;
	}

	// operator()(double a) - interpretacja zadania operator(double)
	// "wszystkie cyfry są powiększone o część całkowitą z wpisanej cyfry"
	// Zakładamy więc, że floor(a) dodajemy do każdego elementu.
	Matrix& operator()(double a) {
		int val = (int)std::floor(a);
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += val;
			}
		}
		return *this;
	}

	// operator<<
	friend std::ostream& operator<<(std::ostream& o, Matrix const& m) {
		for (const auto& row : m.data) {
			for (const auto& elem : row) {
				o << elem << " ";
			}
			o << "\n";
		}
		return o;
	}

	// operator==
	bool operator==(const Matrix& m) const {
		if (data.size() != m.data.size()) return false;
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data.size(); j++) {
				if (data[i][j] != m.data[i][j]) return false;
			}
		}
		return true;
	}

	// operator>
	bool operator>(const Matrix& m) const {
		if (data.size() != m.data.size()) return false;
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data.size(); j++) {
				if (!(data[i][j] > m.data[i][j])) return false;
			}
		}
		return true;
	}

	// operator<
	bool operator<(const Matrix& m) const {
		if (data.size() != m.data.size()) return false;
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data.size(); j++) {
				if (!(data[i][j] < m.data[i][j])) return false;
			}
		}
		return true;
	}
};
