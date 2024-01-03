# Metoda eliminacji Gaussa

Program wykonuje eliminację Gaussa w celu rozwiązania układu równań liniowych Ax = b, gdzie A to macierz współczynników, x to wektor niewiadomych, a b to wektor prawych stron.

## Struktura plików wejściowych

Program przyjmuje dwa pliki wejściowe: `A.txt` oraz `b.txt`.

### A.txt

Plik `A.txt` zawiera macierz współczynników układu równań. Pierwsza linia określa rozmiary macierzy, a następnie podane są elementy macierzy.

Przykład `A.txt`:

3 3  // Rozmiar macierzy: 3 wiersze, 3 kolumny;
1 3 5
1 2 2
1 1 4


### b.txt

Plik `b.txt` zawiera wektor prawych stron układu równań. Pierwsza linia określa rozmiar wektora, a następnie podane są elementy wektora.

Przykład `b.txt`:

3 1  // Rozmiar wektora: 3 wiersze, 1 kolumna;
3
4
1


## Uruchamianie programu

Program można uruchomić z linii poleceń, podając pliki wejściowe jako argumenty. Przykład:

```bash
../my_program A.txt b.txt

