#include <iostream>
#include <ctime>
#include "barley_break.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	barley_break s;
	s.solvable_random_fill(70);
	s.print();
	cout << endl;
	unsigned int start = clock();
	s.ida_star();
	unsigned int end = clock();
	s.print_moves();
	cout << endl;
	s.print_res();
	cout << endl << endl << "Time: " << (float)(end - start) / CLOCKS_PER_SEC << endl;
}
