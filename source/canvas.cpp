#include "canvas.h"

canvas::canvas() :
    stone{
        {wxT("BLACK"), wxBITMAP_TYPE_PNG_RESOURCE},
        {wxT("WHITE"), wxBITMAP_TYPE_PNG_RESOURCE}},
    palete{sizeTotal, sizeTotal}
    // palete{wxT("BKG"), wxBITMAP_TYPE_PNG_RESOURCE} 
    //图片导入，具体看图片名
{
    wxMemoryDC memDC{palete};
    memDC.Clear();
    /* 绘制棋盘背景图片 */{
        wxBitmap bkg{wxT("BKG"), wxBITMAP_TYPE_PNG_RESOURCE};
        wxMemoryDC bkgDC{bkg};
        memDC.StretchBlit(wxPoint{0,0}, wxSize{sizeTotal, sizeTotal}, &bkgDC, wxPoint{0,0}, bkg.GetSize());
        bkgDC.SelectObject(wxNullBitmap);
        // memDC.DrawBitmap(bkg, wxPoint{0, 0});
    }
    memDC.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));

    // 初始化棋盘格子（空棋盘）
    int x{initial}, y{initial};
    for (int i = 0; i <= gridCount; ++ i, y += gridSize)
    {
        memDC.DrawLine(x, y, x + length, y);
        memDC.DrawLine(y, x, y, x + length);
    }
    memDC.SetBrush(*wxBLACK_BRUSH);
    for (int i = 0; i < 3; ++ i)
    for (int j = 0; j < 3; ++ j)
        memDC.DrawCircle(wxPoint{stars[i], stars[j]}, 3);

    memDC.SelectObject(wxNullBitmap);

    // 准备记录棋局
    board.push(game_board());
}

void canvas::realise(wxDC& target)
{
    // 画棋盘背景
    target.DrawBitmap(palete, wxPoint{0, 0});
    // 棋子的设备上下文
    wxMemoryDC stoneDC[]{{stone[0]}, {stone[1]}};
    const wxSize sz = stone[0].GetSize();

    // 准备字体大小
    target.SetFont(wxFont{wxFontInfo{14}.Bold().FaceName("Microsoft JhengHei")});
    // 画棋子（把棋子的图片放到对应位置）
    for (int i = 1; i <= 19; ++ i)
    for (int j = 1; j <= 19; ++ j)
    {
        const int x{i * gridSize - gridSize / 2}, y{j * gridSize - gridSize / 2};
        // 设置当前的棋子上下文
        wxMemoryDC* curStone;
        if (board.top()[i][j] == game_board::Black)
        {
            curStone = stoneDC;
            target.SetTextForeground(*wxWHITE);
        }
        else if (board.top()[i][j] == game_board::White)
        {
            curStone = stoneDC + 1;
            target.SetTextForeground(*wxBLACK);
        }
        // 如果当前位置有棋子
        if (board.top()[i][j] != game_board::Blank)
        {
            target.StretchBlit(wxPoint{x,y}, wxSize{gridSize, gridSize}, curStone, wxPoint{0,0}, sz);
            // 棋子序数标号
            int cnt = board.top().record[i][j];
            if (cnt != 0)
            {
                wxString label = wxString::Format("%d", cnt);
                wxSize sz = target.GetTextExtent(label);
                wxPoint pos{i * gridSize - sz.x / 2, j * gridSize - sz.y / 2};
                // 绘制标签
                target.DrawText(label, pos);
            }
        }
    }
    // 设置为空字体，防止析构失败
    target.SetFont(wxNullFont);
}

void canvas::load(std::istream& input)
{
    clear();
    for (int i = 1; i <= 19; ++ i)
    for (int j = 1; j <= 19; ++ j)
        input >> board.top()[i][j];
}

void canvas::save(std::ostream& output)
{
    for (int i = 1; i <= 19; ++ i)
    {
        output << board.top()[i][1];
        for (int j = 2; j <= 19; ++ j)
            output << ' ' << board.top()[i][j];
        output << std::endl;
    }
}
//图片导入用的是CMake，我这里没有环境。#include "canvas