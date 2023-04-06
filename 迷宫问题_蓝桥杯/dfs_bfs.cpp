//蓝桥杯：https://www.lanqiao.cn/problems/602/learning/?first_category_id=1&sort=students_count&second_category_id=3
#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include <cstdio>
#define ROWS 30
#define COLS 50

class Move
{
public:
	Move(int x = 0, int y = 0)
	{
		row = x;
		col = y;
	}
	Move(const Move& m)
	{
		row = m.row;
		col = m.col;
	}
	int row, col;
};

char maze[ROWS + 2][COLS + 2] = {
	"01010101001011001001010110010110100100001000101010",
	"00001000100000101010010000100000001001100110100101",
	"01111011010010001000001101001011100011000000010000",
	"01000000001010100011010000101000001010101011001011",
	"00011111000000101000010010100010100000101100000000",
	"11001000110101000010101100011010011010101011110111",
	"00011011010101001001001010000001000101001110000000",
	"10100000101000100110101010111110011000010000111010",
	"00111000001010100001100010000001000101001100001001",
	"11000110100001110010001001010101010101010001101000",
	"00010000100100000101001010101110100010101010000101",
	"11100100101001001000010000010101010100100100010100",
	"00000010000000101011001111010001100000101010100011",
	"10101010011100001000011000010110011110110100001000",
	"10101010100001101010100101000010100000111011101001",
	"10000000101100010000101100101101001011100000000100",
	"10101001000000010100100001000100000100011110101001",
	"00101001010101101001010100011010101101110000110101",
	"11001010000100001100000010100101000001000111000010",
	"00001000110000110101101000000100101001001000011101",
	"10100101000101000000001110110010110101101010100001",
	"00101000010000110101010000100010001001000100010101",
	"10100001000110010001000010101001010101011111010010",
	"00000100101000000110010100101001000001000000000010",
	"11010000001001110111001001000011101001011011101000",
	"00000110100010001000100000001000011101000000110011",
	"10101000101000100010001111100010101001010000001000",
	"10000010100101001010110000000100101010001011101000",
	"00111100001000010000000110111000000001000000001011",
	"10000001100111010111010001000110111010101101111000"
};

int visited[ROWS + 2][COLS + 2];

using namespace std;

bool Isok(int row, int col)
{
	if (row<0 || row>ROWS - 1 ||
		col<0 || col>COLS - 1 ||
		visited[row][col] ||
		maze[row][col] == '1')
		return false;
	return true;
}

bool rightway(int row, int col)
{
	if (row<0 || row>ROWS - 1 ||
		col<0 || col>COLS - 1 ||
		maze[row][col] == '1')
		return false;
	return true;
}

int main()
{
	string ways;
	queue<Move> move;
	move.push(Move());




	//求出每一个点到原点的步数
	while (!move.empty())
	{
		Move cur = move.front();move.pop();
		if (cur.row == ROWS - 1 && cur.col == COLS - 1) break;

		//下D
		if (Isok(cur.row + 1, cur.col)) {
			move.push(Move(cur.row + 1, cur.col));
			visited[cur.row + 1][cur.col] = visited[cur.row][cur.col] + 1;
		}
		//左L
		if (Isok(cur.row, cur.col - 1)) {
			move.push(Move(cur.row, cur.col - 1));
			visited[cur.row][cur.col - 1] = visited[cur.row][cur.col] + 1;
		}
		//右R
		if (Isok(cur.row, cur.col + 1)
			) {
			move.push(Move(cur.row, cur.col + 1));
			visited[cur.row][cur.col + 1] = visited[cur.row][cur.col] + 1;
		}
		//下D
		if (Isok(cur.row - 1, cur.col)) {
			move.push(Move(cur.row - 1, cur.col));
			visited[cur.row - 1][cur.col] = visited[cur.row][cur.col] + 1;
		}

	}
	visited[0][0] = 0;
	for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0;j < COLS;j++)
		{
			printf("%-4d", visited[i][j]);
		}
		cout << endl;
	}

	//通过步数找打最短路径
	int row = ROWS - 1, col = COLS - 1;
	while (row != 0 || col != 0)
	{
		//下D
		if (rightway(row - 1, col)) {
			if (visited[row - 1][col] + 1 == visited[row][col]) {
				ways += 'D';row = row - 1;maze[row][col] = '#';continue;
			}
		}
		//左L
		if (rightway(row, col + 1)) {
			if (visited[row][col + 1] + 1 == visited[row][col]) {
				ways += 'L';col = col + 1;maze[row][col] = '#';continue;
			}
		}
		//右R
		if (rightway(row, col - 1)) {
			if (visited[row][col - 1] + 1 == visited[row][col]) {
				ways += 'R';col = col - 1;maze[row][col] = '#';continue;
			}
		}
		//上U
		if (rightway(row + 1, col)) {
			if (visited[row + 1][col] + 1 == visited[row][col]) {
				ways += 'U';row = row + 1;maze[row][col] = '#';continue;
			}
		}
	}


	for (int i = 0;i < ROWS;i++)
	{
		printf("%s\n", maze[i]);
	}

	for (int i = ways.size() - 1;i >= 0;i--)
		cout << ways[i];
	getchar();
	return 0;
}