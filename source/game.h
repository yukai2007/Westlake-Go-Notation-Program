#pragma once

constexpr int gridSize = 40;
constexpr int gridCount = 18;
constexpr int sizeTotal = gridSize * (gridCount + 2);

constexpr int initial = gridSize;
constexpr int length = gridSize * gridCount;

const int stars[]{4 * gridSize, 10 * gridSize, 16 * gridSize};

class game_board
{
private:
    int board[21][21];  // 存储棋局的状态
    int flags[21][21];  // 搜索算法中的标记
    int lib_flags[21][21];  // 数气算法中的标记
    int count{1};       // 当前有几块棋
    int liberties{0};   // 当前处理的棋的气数

    int step{0};
protected:
    void remove_dead(int colour);
    void visit(int colour, int x, int y);
    void remove(int colour, int x, int y);
    void clear_flags();
    void clear_lib_flags();
public:
    int record[21][21];
    static constexpr int White = -1;
    static constexpr int Black = 1;
    static constexpr int Blank = 0;

    game_board();

    int* operator[](int x) { return board[x]; }

    bool can_place(int colour, int x, int y,int px,int py);
    void place(int colour, int x, int y);

    void record_step(int x, int y)
        { record[x][y] = ++step; }
};
