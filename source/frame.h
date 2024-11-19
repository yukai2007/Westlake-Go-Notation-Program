#pragma once
#include <wx/frame.h>
#include <wx/panel.h>
#include "canvas.h"

enum MenuID
{
    ID_Open = 1000,
    ID_Save,
    ID_SaveAs,
    ID_Exit,
    ID_Clear,
    ID_Undo,
    ID_Redo,
    ID_ModeFlipKeep,
    ID_ModeBlackWhite,
    ID_About
};

class frame : public wxFrame
{
private:
    int gameMode{0};
    // wxPanel* m_canvas;
    canvas can;
    int lastColour{game_board::White};
    wxMenu* menuEdit;

    std::stack<int> colours, colRedos;
    std::string file;
public:
    frame();

    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnPaint(wxPaintEvent& event);

    void OnLeftUp(wxMouseEvent& event);
    void OnRightUp(wxMouseEvent& event);

    void OnFlipKeep(wxCommandEvent& event);
    void OnBlackWhite(wxCommandEvent& event);

    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
};

//Build up the fraction