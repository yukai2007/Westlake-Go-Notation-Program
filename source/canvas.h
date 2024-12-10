#pragma once
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/window.h>
#include <wx/bitmap.h>

#include <stack>
#include <iostream>

#include "game.h"

class canvas
{
protected:
    wxBitmap stone[2];
    wxBitmap palete;
    std::stack<game_board> board;
    std::stack<game_board> redos;
    //棋盘和初始界面
public:
    canvas();
    void realise(wxDC& target);
    game_board& get_board() { return board.top(); }

    bool can_place(int colour, int x, int y,int px,int py)
        { return board.top().can_place(colour, x, y,px,py); }
    void place(int colour, int x, int y)
    {
        game_board tmp{board.top()};
        tmp.place(colour, x, y);
        tmp.record_step(x, y);
        board.push(tmp);
        while (! redos.empty())
            redos.pop();
    }
    //应该是棋子的坐标，之后鼠标点击对应相应的坐标点
    void load(std::istream& input);
    void save(std::ostream& output);

    void clear()
    {
        while (! redos.empty())
            redos.pop();
        while (! board.empty())
            board.pop();
        board.push(game_board());
    }
    //清空棋盘，初始话界面

    bool can_undo() { return board.size() > 1; }
    void undo()
    {
        redos.push(board.top());
        board.pop();
    }
    //撤销操作(undo)
    bool can_redo() { return !redos.empty(); }
    void redo()
    {
        board.push(redos.top());
        redos.pop();
    }
    //重做操作(redo)
};
