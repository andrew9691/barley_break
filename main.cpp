#include <iostream>
#include <ctime>
#include "barley_break.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	//barley_break s;
	//s.solvable_random_fill(50);
	//vector<vector<int>> m = { { 7, 5, 10, 11 },{ 2, 12, 4, 1 },{ 6, 13, 3, 8 },{ 9, 15, 0, 14 } }; check
	vector<vector<int>> m = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 0 },{ 13, 14, 15, 12 } };
	barley_break s = barley_break(m);
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
