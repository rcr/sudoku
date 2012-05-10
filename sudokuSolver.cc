#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void printmx(int mx[81]){
	cout << "+-----------------------+\n";
	for(int i=0; i<81; i+=9){
		for(int j=0; j<9; j++){
			if(!(j%3)) cout << "| ";
			mx[i+j] ? cout << mx[i+j] << " " : cout << ". ";
		}
		cout << "|\n";
		if(i==18 || i==45){
			cout << "|-------+-------+-------|\n";
		}
	}
	cout << "+-----------------------+\n";
}
void solvemx(int mx[81]){
	bool hints[81] = {false};
	for(int i=0; i<81; i++){
		if(mx[i]){
			hints[i] =true;
		}
	}
	int current =0;
	bool backtracking =false;
	while(current < 81){
		if(current < 0){
			cout << "No solution\n";
			exit(1);
		}
		if(hints[current]){
			backtracking ? current-- : current++;
		} else {
			backtracking =false;
			if(++mx[current] ==10){
				mx[current--] =0;
				backtracking = true;	
			} else {
				int base = ((current%9)/3)*3 + (current/27)*27;
				for(int i=(current/9)*9; i<(current/9)*9+9; i++){
					if(i != current && mx[i] == mx[current]){
						goto noincrement;
					}
				}
				for(int i=current%9; i<81; i+=9){
					if(i != current && mx[i] == mx[current]){
						goto noincrement;
					}
				}
				for(int i=0; i<=18; i+=9){
					for(int j=0; j<3; j++){
						if((base+i+j) != current && mx[base+i+j] == mx[current]){
							goto noincrement;
						}
					}
				}
				current++;
				noincrement:;
			} 
		}
	}
	printmx(mx);
}

int main () {
	//"worst case": 691752849 increments, ~50 seconds
	int sudoku[81] ={
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,3,0,8,5,
		0,0,1,0,2,0,0,0,0,
		0,0,0,5,0,7,0,0,0,
		0,0,4,0,0,0,1,0,0,
		0,9,0,0,0,0,0,0,0,
		5,0,0,0,0,0,0,7,3,
		0,0,2,0,1,0,0,0,0,
		0,0,0,0,4,0,0,0,9};
	// easy: 364 increments, 0 seconds
	int sudoku1[81] ={
		0,3,0,0,2,0,0,0,0,
		2,0,0,0,0,1,0,0,8,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,7,0,0,0,
		0,4,0,0,0,0,0,0,6,
		0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,7,0,
		6,0,0,8,0,0,0,0,0};

		printmx(sudoku1);
		cout << endl << "Solving...\n\n";
		long start = time(0);
		solvemx(sudoku1);
		long end = time(0);
		cout << "Time taken: " << (end - start) << " seconds\n";
	return 0;
}
