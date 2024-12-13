#include <random>
#include <vector>
#include <print>

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
};
