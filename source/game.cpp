#include "game.h"
#include "math.h"

game_board::game_board() {
	// 初始化棋盘
	for (int i = 0; i < 21; ++ i)
		board[0][i] = board[i][0] = board[20][i] = board[i][20] = 42;
	for (int i = 1; i <= 19; ++ i)
		for (int j = 1; j <= 19; ++ j)
			record[i][j] = board[i][j] = flags[i][j] = 0;
}

void game_board::remove_dead(int colour) {
	clear_flags();
	for (int i = 1; i <= 19; ++ i)
		for (int j = 1; j <= 19; ++ j) {
			clear_lib_flags();
			// 不是当前颜色，或者已经访问过
			if (board[i][j] != colour || flags[i][j] != 0)
				continue;
			// 访问当前交叉点上的一块棋
			visit(colour, i, j);
			++ count;
			// 如果没有气，就提子
			if (liberties == 0)
				remove(colour, i, j);
		}
}
//判断是否需要提子

void game_board::visit(int colour, int x, int y) {
	static constexpr int dx[] {-1, 0, 1, 0};
	static constexpr int dy[] {0, -1, 0, 1};
	// 已经访问过
	if (flags[x][y] != 0 || lib_flags[x][y] != 0)
		return;
	// 空白格子
	if (board[x][y] == Blank) {
		lib_flags[x][y] = colour;
		++ liberties;
		return;
	}
	// 非己方棋子（禁下）
	if (board[x][y] != colour)
		return;
	// 标记当前这个点
	flags[x][y] = count;
	// 访问四个方向的四个交叉点
	for (int i = 0; i < 4; ++ i)
		visit(colour, x + dx[i], y + dy[i]);
}
//判断是否可以落子到该位置

void game_board::clear_flags() {
	count = 1;
	for (int i = 1; i <= 19; ++ i)
		for (int j = 1; j <= 19; ++ j)
			flags[i][j] = 0;
}

void game_board::clear_lib_flags() {
	liberties = 0;
	for (int i = 1; i <= 19; ++ i)
		for (int j = 1; j <= 19; ++ j)
			lib_flags[i][j] = 0;
}

void game_board::remove(int colour, int x, int y) {
	static constexpr int dx[] {-1, 0, 1, 0};
	static constexpr int dy[] {0, -1, 0, 1};
	// 不是当前颜色
	if (board[x][y] != colour)
		return;
	// 提起当前这个子
	board[x][y] = Blank;
	// 四个方向的四个交叉点都提子
	for (int i = 0; i < 4; ++ i)
		remove(colour, x + dx[i], y + dy[i]);
}

void game_board::place(int colour, int x, int y) {
	clear_flags();
	board[x][y] = colour;
	remove_dead(-colour);
}

#define ll long long
bool game_board::can_place(int colour, int x, int y, int px, int py) {
    static constexpr int dx[] {-1, 0, 1, 0};
    static constexpr int dy[] {0, -1, 0, 1};
	if (board[x][y] != Blank)
		return false;
	// 测试禁着点（禁下点）
	game_board temp {*this};

    if(abs(px-x)+abs(py-y)==1){
        ll cur=1;
        for(ll i=0;i<4;i++){
            ll cx=px+dx[i],cy=py+dy[i];
            if(cx==x&&cy==y)continue;
            if(temp.board[cx][cy]==Blank||temp.board[cx][cy]==-colour)cur=0;
        }
        for(ll i=0;i<4;i++){
            ll cx=x+dx[i],cy=y+dy[i];
            if(cx==px&&cy==py)continue;
            if(temp.board[cx][cy]==Blank||temp.board[cx][cy]==colour)cur=0;
        }
		if(cur)return false;
    }

	temp.place(colour, x, y);

	temp.clear_flags();
	for (int i = 1; i <= 19; ++ i)
		for (int j = 1; j <= 19; ++ j) {
			clear_lib_flags();
			// 不是当前颜色，或者已经访问过
			if (temp.board[i][j] != colour || temp.flags[i][j] != 0)
				continue;
			// 访问当前交叉点上的一块棋
			temp.visit(colour, i, j);
			++ temp.count;
			// 如果没有气，就提子
			if (temp.liberties == 0)
				return false;
		}
	return true;
}
