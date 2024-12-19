#include <iostream>
#include "Matrix.hpp"
#include <fstream>

int main(int argc, char *argv[]) {
    // Wczytanie rozmiaru i danych z pliku
    std::ifstream fin("dane.txt");
    if(!fin.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku dane.txt!" << std::endl;
        return 1;
    }

    int n;
    fin >> n;

    // Alokujemy tablicê pomocnicz¹
    int* tab = new int[n*n];
    for(int i = 0; i < n*n; i++) {
        fin >> tab[i];
    }
    fin.close();

    // Tworzymy macierz z wczytanych danych
    Matrix<int> A(n, tab);
    delete[] tab;

    std::cout << "Macierz A (wczytana z pliku):\n";
    std::cout << A;

    // Testy metod
    // Tworzymy inn¹ macierz o tym samym rozmiarze i j¹ wype³nimy losowo
    Matrix<int> B(n);
    B.losuj();
    std::cout << "\nMacierz B (losowa):\n" << B;

    // SprawdŸmy operacje dodawania macierzy (A + B)
    // Zwracamy uwagê, ¿e operator+ zosta³ zdefiniowany jako modyfikuj¹cy obiekt,
    // wiêc dla testów zrobimy kopiê macierzy A.
    Matrix<int> A_copy(A);
    A_copy + B;
    std::cout << "\nA + B:\n" << A_copy;

    // Sprawdzamy mno¿enie macierzy A * B
    // Mno¿enie mo¿liwe, jeœli rozmiary siê zgadzaj¹.
    // Gdyby rozmiary siê nie zgadza³y, nie wykonujemy mno¿enia.
    // Tutaj rozmiar jest taki sam, wiêc mno¿enie jest poprawne.
    Matrix<int> A_copy2(A);
    A_copy2 * B;
    std::cout << "\nA * B:\n" << A_copy2;

    // Testy dodawania liczby
    Matrix<int> A_copy3(A);
    A_copy3 + 10;
    std::cout << "\nA + 10:\n" << A_copy3;

    // Testy mno¿enia przez liczbê
    Matrix<int> A_copy4(A);
    A_copy4 * 2;
    std::cout << "\nA * 2:\n" << A_copy4;

    // Testy odejmowania liczby
    Matrix<int> A_copy5(A);
    A_copy5 - 5;
    std::cout << "\nA - 5:\n" << A_copy5;

    // Testy operatorów friend: int + A
    std::cout << "\n10 + A:\n" << (10 + A);

    // 10 * A
    std::cout << "\n10 * A:\n" << (10 * A);

    // 10 - A
    std::cout << "\n10 - A:\n" << (10 - A);

    // Test operatorów inkrementacji i dekrementacji
    Matrix<int> A_copy6(A);
    A_copy6++;
    std::cout << "\nA++:\n" << A_copy6;

    A_copy6--;
    std::cout << "\nA-- (po A++):\n" << A_copy6;

    // Test operatorów +=, -=, *=
    A_copy6 += 5;
    std::cout << "\nA += 5:\n" << A_copy6;
    A_copy6 -= 5;
    std::cout << "\nA -= 5:\n" << A_copy6;
    A_copy6 *= 3;
    std::cout << "\nA *= 3:\n" << A_copy6;

    // Test operator()(double)
    A_copy6(3.7); // Dodaje floor(3.7)=3 do ka¿dego elementu
    std::cout << "\nA_copy6(3.7):\n" << A_copy6;

    // Testy porównañ
    // Sprawdzimy czy A == A (powinno byæ true)
    std::cout << "\nA == A? " << (A == A ? "TAK" : "NIE") << "\n";
    // Sprawdzimy A > B i A < B (raczej nie, bo losowe)
    std::cout << "A > B? " << (A > B ? "TAK" : "NIE") << "\n";
    std::cout << "A < B? " << (A < B ? "TAK" : "NIE") << "\n";

    // Test wstawiania wartoœci w konkretne miejsce
    A.wstaw(0,0,999);
    std::cout << "\nA po wstawieniu 999 do [0,0]:\n" << A;

    // Test przek¹tnej
    Matrix<int> C(n);
    C.przekatna();
    std::cout << "\nC - przekatna:\n" << C;

    // Test pod_przekatna
    C.pod_przekatna();
    std::cout << "\nC - pod_przekatna:\n" << C;

    // Test nad_przekatna
    C.nad_przekatna();
    std::cout << "\nC - nad_przekatna:\n" << C;

    // Test szachownica
    C.szachownica();
    std::cout << "\nC - szachownica:\n" << C;

    // Test diagonalna
    // Utworzymy tablicê do wpisania po przek¹tnej
    int* diag_tab = new int[n];
    for(int i = 0; i < n; i++) diag_tab[i] = i+1;
    C.diagonalna(diag_tab);
    std::cout << "\nC - diagonalna:\n" << C;

    // Test diagonalna_k (przesuniêcie przek¹tnej)
    C.diagonalna_k(1, diag_tab);
    std::cout << "\nC - diagonalna_k(1):\n" << C;

    // Test kolumna
    // Wpiszmy kolumnê nr 0 danymi z diag_tab
    C.kolumna(0, diag_tab);
    std::cout << "\nC - kolumna(0):\n" << C;

    // Test wiersz
    // Wpiszmy wiersz nr 1 danymi z diag_tab
    C.wiersz(1, diag_tab);
    std::cout << "\nC - wiersz(1):\n" << C;

    delete[] diag_tab;

    // Test losuj(x) - wstawmy losowo kilka elementów
    C.losuj(10);
    std::cout << "\nC - losuj(10):\n" << C;

    // Test dowroc (transpozycja)
    C.dowroc();
    std::cout << "\nC - dowroc (transpozycja):\n" << C;

    // Test alokuj
    Matrix<int> D;
    D.alokuj(n); // alokujemy n x n
    D.przekatna();
    std::cout << "\nD - alokuj(n) i przekatna:\n" << D;

    // Test gdy nie mo¿na mno¿yæ macierzy (np. D jest n x n, zróbmy E 2n x 2n)
    Matrix<int> E(2*n);
    E.losuj();
    std::cout << "\nE (2n x 2n):\n";
    // Nie wypisujemy ca³ej, bo du¿a, ale powiedzmy tylko, ¿e istnieje.
    std::cout << "Macierz E o rozmiarze " << 2*n << "x" << 2*n << " utworzona.\n";

    // Próba mno¿enia D * E - powinno byæ zabronione (lub nic nie zrobiæ)
    int oldVal = D.pokaz(0,0);
    D * E;
    if(D.pokaz(0,0) == oldVal) {
        std::cout << "\nProba mnozenia D * E (rozne rozmiary) - niezmieniona macierz D, OK.\n";
    } else {
        std::cout << "\nProba mnozenia D * E (rozne rozmiary) - powinna byc zabezpieczona!\n";
    }

    std::cout << "\nTesty zakonczone.\n";

    return 0;
}
