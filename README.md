Celem projektu było zaimplementowanie kalkulatora działającego na podstawie algorytmu Odwrotnej notacji polskiej. 
Zabronione było korzystanie z bibliotek stl oraz string.
Projekt został wykonany w kwietniu 2024 roku w ramach przedmiotu Algorytmy i Struktury Danych.

Operacje w kolejności rosnącego priorytetu:

a + b, a - b, a * b, a / b - wszystkie operacje wykonywane są na liczbach całkowitych, stąd wynik dzielenia zaokrąglany jest w dół

IF(a, b, c) - jeśli a> 0 zwróć b, w przeciwnym razie c

N a - jednoargumentowa negacja, czyli -a

MIN( a1, a2, ... ) , MAX(a1, a2, ...) - funkcje MIN i MAX nie mają ograniczonej liczby parametrów

( ... ) - nawiasy

-------------

ENG

The goal of the project was to implement a calculator based on the Reverse Polish Notation (RPN) algorithm.
The use of STL libraries and the string class was prohibited.

The project was completed in April 2024 as part of the "Algorithms and Data Structures" course.

Operations in increasing order of priority:


a + b, a - b, a * b, a / b - All operations are performed on integers, so the result of division is rounded down.

IF(a, b, c) - if a > 0, return b; otherwise, return c.

N a - single-argument negation, equivalent to -a.

MIN(a1, a2, ...), MAX(a1, a2, ...) - the MIN and MAX functions have no limit on the number of parameters.

( ... ) - parentheses for grouping operations.

-------------

Wejście/Input:

4
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) .
2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .
N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .
IF ( ( 6 + 8 ) , ( 4 / 2 ) , MIN ( 8 , 2 , 1 , 0 , 3 ) ) * 2 * 6 / N ( 3 ) .

Wyjście/Output:

100  1  34  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6
MAX3 2 34 1 100
MIN4 77 35 36 66 80 34 100
MIN6 60 50 35 80 34 100
34

2  100  1  6  5  *  2  +  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6  3  *  +
* 5 6 1 100 2
+ 2 30 1 100 2
MAX3 2 32 1 100 2
MIN4 77 35 36 66 80 32 100 2
MIN6 60 50 35 80 32 100 2
* 3 32 2
+ 96 2
98

400  N  11  3  2  *  -  2  /  +  200  N  N  +
N 400
* 2 3 11 -400
- 6 11 -400
/ 2 5 -400
+ 2 -400
N 200 -398
N -200 -398
+ 200 -398
-198

6  8  +  4  2  /  8  2  1  0  3  MIN5  IF  2  *  6  *  3  N  /
+ 8 6
/ 2 4 14
MIN5 3 0 1 2 8 2 14
IF 0 2 14
* 2 2
* 6 4
N 3 24
/ -3 24
-8
