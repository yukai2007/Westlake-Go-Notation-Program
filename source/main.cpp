#include <wx/wx.h>
#include "frame.h"

class GoPlusPlusApp : public wxApp
{
private:
    wxLocale * locale;
public:
    bool OnInit() override;
};

bool GoPlusPlusApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);

    locale = new wxLocale(wxLANGUAGE_CHINESE_SIMPLIFIED);
    if (! locale->IsOk())
        wxMessageBox(wxT("不能加载本地化数据，因此一部分界面元素可能会显示为西文。"));
    locale->AddCatalog(wxT("GoPlusPlus"));

    auto f = new frame;
    f->Show();

    return true;
}

wxIMPLEMENT_APP(GoPlusPlusApp);
