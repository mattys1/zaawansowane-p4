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

	/**
 * @brief Wstawia wartość do macierzy na podaną pozycję.
 * @param x Indeks wiersza.
 * @param y Indeks kolumny.
 * @param wartosc Wartość, którą wstawiamy do macierzy.
 * @return Zwraca referencję do bieżącej macierzy (this).
 *
 * Metoda wstawia liczbę do macierzy w odpowiednie miejsce.
 * Dzięki temu można zmienić zawartość macierzy w dowolnym miejscu.
 */
	Matrix& wstaw(int x, int y, int wartosc) {
		data[x][y] = wartosc;
		return *this;
	}

	/**
	 * @brief Tworzy wzór szachownicy w macierzy.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 *
	 * Metoda ustawia w macierzy wzór podobny do szachownicy,
	 * gdzie pola naprzemiennie mają wartość 0 lub 1.
	 */
	Matrix& szachownica(void) {
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data.size(); j++) {
				data[i][j] = ((i + j) % 2 == 0) ? 0 : 1;
			}
		}
		return *this;
	}

	/**
	 * @brief Dodaje do macierzy inną macierz element po elemencie.
	 * @param m Druga macierz, którą dodajemy.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 *
	 * Dodaje wszystkie elementy macierzy m do bieżącej macierzy A.
	 * Jeśli rozmiary się nie zgadzają, nic nie robi.
	 */
	Matrix& operator+(Matrix const& m) {
		// Sprawdzenie wymiarów
		if (data.size() != m.data.size()) {
			return *this;
		}

		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data.size(); j++) {
				data[i][j] += m.data[i][j];
			}
		}
		return *this;
	}

	/**
	 * @brief Mnoży macierz przez inną macierz.
	 * @param m Macierz, przez którą mnożymy.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 *
	 * Wykonuje klasyczne mnożenie macierzy kwadratowych.
	 * Jeśli rozmiary się nie zgadzają, nic nie zmienia.
	 * Wynikiem jest A = A * m.
	 */
	Matrix& operator*(Matrix const& m) {
		int n = (int)data.size();
		if (n == 0 || n != (int)m.data.size()) {
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

	/**
	 * @brief Dodaje do każdego elementu macierzy liczbę całkowitą.
	 * @param a Liczba, którą dodajemy do elementów macierzy.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 */
	Matrix& operator+(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += a;
			}
		}
		return *this;
	}

	/**
	 * @brief Mnoży każdy element macierzy przez liczbę całkowitą.
	 * @param a Liczba, przez którą mnożymy elementy macierzy.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 */
	Matrix& operator*(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem *= a;
			}
		}
		return *this;
	}

	/**
	 * @brief Odejmuje od każdego elementu macierzy liczbę całkowitą.
	 * @param a Liczba, którą odejmujemy od elementów macierzy.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 */
	Matrix& operator-(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem -= a;
			}
		}
		return *this;
	}

	/**
	 * @brief Dodaje liczbę całkowitą do każdego elementu macierzy (postać a + m).
	 * @param a Liczba do dodania.
	 * @param m Macierz, do której dodajemy liczbę.
	 * @return Nowa macierz z dodaną liczbą a.
	 */
	friend Matrix operator+(int a, Matrix const& m) {
		Matrix result(m);
		for (auto& row : result.data) {
			for (auto& elem : row) {
				elem = a + elem;
			}
		}
		return result;
	}

	/**
	 * @brief Mnoży każdy element macierzy przez liczbę całkowitą (postać a * m).
	 * @param a Liczba przez którą mnożymy.
	 * @param m Macierz, której elementy mnożymy.
	 * @return Nowa macierz po pomnożeniu.
	 */
	friend Matrix operator*(int a, Matrix const& m) {
		Matrix result(m);
		for (auto& row : result.data) {
			for (auto& elem : row) {
				elem = a * elem;
			}
		}
		return result;
	}

	/**
	 * @brief Odejmuje każdy element macierzy od liczby a (postać a - m).
	 * @param a Liczba od której odejmujemy.
	 * @param m Macierz, której elementy odejmujemy.
	 * @return Nowa macierz po odjęciu.
	 */
	friend Matrix operator-(int a, Matrix const& m) {
		Matrix result(m);
		for (auto& row : result.data) {
			for (auto& elem : row) {
				elem = a - elem;
			}
		}
		return result;
	}

	/**
	 * @brief Operator postinkrementacji - zwiększa każdy element o 1.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 *
	 * Po wykonaniu A++ każdy element w A jest większy o 1.
	 */
	Matrix& operator++(int) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += 1;
			}
		}
		return *this;
	}

	/**
	 * @brief Operator postdekrementacji - zmniejsza każdy element o 1.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 *
	 * Po wykonaniu A-- każdy element w A jest mniejszy o 1.
	 */
	Matrix& operator--(int) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem -= 1;
			}
		}
		return *this;
	}

	/**
	 * @brief Dodaje liczbę całkowitą do każdego elementu macierzy (A += a).
	 * @param a Liczba do dodania.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 */
	Matrix& operator+=(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += a;
			}
		}
		return *this;
	}

	/**
	 * @brief Odejmuje od każdego elementu macierzy liczbę całkowitą (A -= a).
	 * @param a Liczba do odjęcia.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 */
	Matrix& operator-=(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem -= a;
			}
		}
		return *this;
	}

	/**
	 * @brief Mnoży każdy element macierzy przez liczbę całkowitą (A *= a).
	 * @param a Liczba przez którą mnożymy.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 */
	Matrix& operator*=(int a) {
		for (auto& row : data) {
			for (auto& elem : row) {
				elem *= a;
			}
		}
		return *this;
	}

	/**
	 * @brief Dodaje do każdego elementu macierzy część całkowitą z liczby a.
	 * @param a Liczba typu double, bierzemy floor(a) i dodajemy do każdego elementu.
	 * @return Zwraca referencję do bieżącej macierzy (this).
	 *
	 * Dla przykładu, jeśli a = 3.7 to floor(a) = 3 i dodajemy 3 do każdego elementu.
	 */
	Matrix& operator()(double a) {
		int val = (int)std::floor(a);
		for (auto& row : data) {
			for (auto& elem : row) {
				elem += val;
			}
		}
		return *this;
	}

	/**
	 * @brief Wypisuje macierz do strumienia wyjściowego.
	 * @param o Strumień wyjściowy.
	 * @param m Macierz do wypisania.
	 * @return Referencja do strumienia wyjściowego.
	 *
	 * Wypisuje elementy macierzy w postaci wierszy. Każdy element jest oddzielony spacją.
	 */
	friend std::ostream& operator<<(std::ostream& o, Matrix const& m) {
		for (const auto& row : m.data) {
			for (const auto& elem : row) {
				o << elem << " ";
			}
			o << "\n";
		}
		return o;
	}

	/**
	 * @brief Sprawdza, czy macierz jest równa innej macierzy.
	 * @param m Macierz do porównania.
	 * @return true jeśli są równe, false w przeciwnym razie.
	 *
	 * Porównuje elementy o tych samych indeksach.
	 */
	bool operator==(const Matrix& m) const {
		if (data.size() != m.data.size() || data[0].size() != m.data[0].size()) return false;
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data[i].size(); j++) {
				if (data[i][j] != m.data[i][j]) return false;
			}
		}
		return true;
	}

	/**
	 * @brief Sprawdza, czy każda wartość bieżącej macierzy jest większa niż w macierzy m.
	 * @param m Macierz do porównania.
	 * @return true jeśli wszystkie elementy A są większe od odpowiadających elementów m, w przeciwnym razie false.
	 */
	bool operator>(const Matrix& m) const {
		if (data.size() != m.data.size() || data[0].size() != m.data[0].size()) return false;
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data[i].size(); j++) {
				if (!(data[i][j] > m.data[i][j])) return false;
			}
		}
		return true;
	}

	/**
	 * @brief Sprawdza, czy każda wartość bieżącej macierzy jest mniejsza niż w macierzy m.
	 * @param m Macierz do porównania.
	 * @return true jeśli wszystkie elementy A są mniejsze od odpowiadających elementów m, w przeciwnym razie false.
	 */
	bool operator<(const Matrix& m) const {
		if (data.size() != m.data.size() || data[0].size() != m.data[0].size()) return false;
		for (int i = 0; i < (int)data.size(); i++) {
			for (int j = 0; j < (int)data[i].size(); j++) {
				if (!(data[i][j] < m.data[i][j])) return false;
			}
		}
		return true;
	}
};
