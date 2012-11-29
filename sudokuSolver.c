#include <stdio.h>
#include <stdlib.h>

#define SUDOKU 82

void solve(char *);
void print(int *);

int
main(int argc, char **argv)
{
	FILE *fp;
	if ((fp = fopen(argv[1], "r")) == NULL)
		return 1;
	
	int count;
	fscanf(fp, "%d\n", &count);

	char *buf;
	if ((buf = malloc(SUDOKU * count * sizeof(char))) == NULL)
		return 1;

	if ((fread(buf, sizeof(char), SUDOKU * count, fp)) != (SUDOKU * count))
		return 1;

	char *ptr;
	for (ptr = buf; count--; ptr+=SUDOKU)
		solve(ptr);

	free(buf);

	return 0;
}

void
solve(char *board)
{
	int i, j, ri, ci, bi, val, backtracking = 0, cell = 0;
	int hint[81], mx[81], row[9][9] = {0}, col[9][9] = {0}, box[9][9] = {0};

	for (i=0; i<81; i++){
		val = *board++ - '0';
		hint[i] = mx[i] = val;

		ri = i/9;
		ci = i%9;
		bi = ci/3 + (ri/3)*3;

		if (val--)
			row[ri][val] = col[ci][val] = box[bi][val] = 1;
	}

	while (cell < 81){
		if (cell < 0){
			puts("No solution");
			break;
		}
		if (hint[cell])
			backtracking ? cell-- : cell++;
		else {
			backtracking = 0;

			ri = cell/9;
			ci = cell%9;
			bi = ci/3 + (ri/3)*3;

			for (j=mx[cell]; j<9; j++)
				if (!row[ri][j] && !col[ci][j] && !box[bi][j])
					break;
			if (mx[cell]) {
				val = mx[cell] - 1;
				row[ri][val] = col[ci][val] = box[bi][val] = 0;
			}
			if (j == 9){
				backtracking = 1;
				mx[cell--] = 0;
				continue;
			}
			row[ri][j] = col[ci][j] = box[bi][j] = 1; 

			mx[cell++] = j+1;
		}
	}
	// print(mx);
}

void
print(int mx[81])
{
	int i, j;
	puts("+-----------------------+");
	for(i=0; i<9; i++){
		for(j=0; j<9; j++)
			printf("%s%c ", (!(j%3)) ? "| " : "", mx[i*9 + j] + '0');
		puts("|");
		if(i == 2 || i == 5)
			puts("|-------+-------+-------|");
	}
	puts("+-----------------------+");
}
