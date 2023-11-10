#include"multiFunctions.h"

bool isInBoard(Position position) {
	return (position.first >= 0 && position.first <= 7 && position.second >= 0 && position.second <= 7);
}

int pgcm(short int a, short int b) {
	while (b != 0) {
		int reste = a % b;
		a = b;
		b = reste;
	}
	return a == 0 ? 1 : abs(a);
}

Position coordoneeToPosition(const short int& row, const short int& col) {
	Position position;
	position.first = row;
	position.second = col;
	return position;
}

bool isEven(int number) {
	return number % 2 == 0;
}
