#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

typedef struct {
	int position_x;
	int position_y;
}desease;

int Map[8][8];
int copy_map[8][8];
int x, y;
int Max_count = 0;
int result = 0;
int dirx[4] = { -1,1,0,0 };
int diry[4] = { 0,0,-1,1 };
queue<desease> initial_q;

void Input() {
	scanf("%d %d", &y, &x);
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] == 2) initial_q.push({ j,i });
		}
	}
}

void Copy_one_Map(){
	for (int l = 0; l < y; l++) {
		for (int c = 0; c < x; c++) {
			copy_map[l][c] = Map[l][c];
		}
	}
}

void q_process() {
	queue<desease> q(initial_q);
	while (!q.empty()) {
		int q_x = q.front().position_x;
		int q_y = q.front().position_y;
		q.pop();
		for (int h = 0; h < 4; h++) {
			int next_x = q_x + dirx[h];
			int next_y = q_y + diry[h];
			if (copy_map[next_y][next_x] != 0 || next_x < 0 || next_y < 0 || next_x >= x || next_y >= y) continue;
			copy_map[next_y][next_x] = 2;
			q.push({ next_x, next_y });
		}
	}
}

void calc_result() {
	for (int t = 0; t < y; t++) {
		for (int b = 0; b < x; b++) {
			if (copy_map[t][b] == 0) result++;
		}
	}
}

void print_map() {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			printf("%d ", copy_map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Copy_Map() {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			copy_map[i][j] = Map[i][j];
		}
	}
}

void Calc() {
	int length = x * y;
	for (int i = 0; i < length; i++) {
		/*Copy_one_Map();*/
		if (Map[i / x][i%x] != 0) continue;
		Map[i / x][i%x] = 1;
		for (int j = i; j < length; j++) {
			if (Map[j / x][j%x] != 0) continue;
			Map[j / x][j%x] = 1;
			for (int k = j; k < length; k++) {
				result = 0;
				if (Map[k / x][k%x] != 0) continue;
				Map[k / x][k%x] = 1;
				Copy_Map();
				/*printf("copy\n");*/
				/*print_map();*/
				q_process();
				calc_result();
				/*printf("i , j , k : %d %d %d \n", i, j, k);*/
				/*print_map();*/
				
				Map[k / x][k%x] = 0;
				if (result > Max_count) Max_count = result;
			}
			Map[j / x][j%x] = 0;
		}
		Map[i / x][i%x] = 0;
	}

	printf("%d", Max_count);
}


int main(void) {
	Input();
	Calc();
	/*Copy_Map();
	q_process();*/
	return 0;
}