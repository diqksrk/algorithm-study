#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

typedef struct {
	int position_x;
	int position_y;
	int dir;
}robot_cleaner;

enum ROBOT_DIR {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum ROBOT_DIR rd;

int new_dirx[4] = {0, 1, 0, -1};
int new_diry[4] = {-1, 0,1,0};

int depth, width, result;
int robot_x, robot_y, robot_dir;
int Map[50][50];
bool game_end;
queue<robot_cleaner> q;

void Input() {
	scanf("%d %d", &depth, &width);
	scanf("%d %d %d", &robot_y, &robot_x, &robot_dir);
	q.push({ robot_x, robot_y, robot_dir });
	for (int i = 0; i < depth; i++) {
		for (int j = 0; j < width; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
}

ROBOT_DIR turn_direction(ROBOT_DIR rd) {
	switch (rd)
	{
	case UP:
		return rd = LEFT;
	case RIGHT:
		return rd = UP;
	case DOWN:
		return rd = RIGHT;
	case LEFT:
		return rd = DOWN;
	default:
		break;
	}
}

ROBOT_DIR back_going(ROBOT_DIR rd) {
	switch (rd)
	{
	case UP:
		return rd = DOWN;
	case RIGHT:
		return rd = LEFT;
	case DOWN:
		return rd = UP;
	case LEFT:
		return rd = RIGHT;
	default:
		break;
	}
}

void search(int position_x, int position_y, ROBOT_DIR rd) {
	ROBOT_DIR next_directtion=rd;
	for (int i = 0; i < 4; i++) {
		 next_directtion= turn_direction(next_directtion);
		int next_positionx = position_x + new_dirx[next_directtion];
		int next_positiony = position_y + new_diry[next_directtion];
		if (next_positionx < 0 || next_positiony < 0 || next_positionx >= width || next_positiony >= depth) continue;
		if (Map[next_positiony][next_positionx] != 0) continue;
		game_end = false;
		q.push({ next_positionx, next_positiony, next_directtion});
		break;
	}
	
	if (game_end) {
		next_directtion = back_going(next_directtion);
		position_x = position_x + new_dirx[next_directtion];
		position_y = position_y + new_diry[next_directtion];
		if (Map[position_y][position_x] == 1 || position_x < 0 || position_y < 0|| position_x>=width || position_y>=depth) {
			printf("%d", result);
			return;
		}
		else {
			q.push({ position_x, position_y, rd});
		}
	}
}

void Calc() {
	while (!q.empty()) {
		int position_x = q.front().position_x;
		int position_y = q.front().position_y;
		int robot_dir = q.front().dir; 
		game_end = true;
		q.pop();
		if (Map[position_y][position_x] == 0) {
			Map[position_y][position_x] = 2;
			result++;
		}
		switch (robot_dir)
		{
		case UP:
			search(position_x, position_y,UP);
			break;
		case RIGHT:
			search(position_x, position_y,RIGHT);
			break;
		case DOWN:
			search(position_x, position_y,DOWN);
			break;
		case LEFT:
			search(position_x, position_y,LEFT);
			break;
		default:
			break;
		}
	}
}

void Solve() {
	Input();
	Calc();
}


int main(void) {
	Solve();
	return 0;
}