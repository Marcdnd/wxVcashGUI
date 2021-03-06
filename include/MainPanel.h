/******************************************************************************
 * wxVcashGUI: a GUI for Vcash, the decentralized currency 
 *             for the internet (https://v.cash/).
 *
 * Copyright (c) kryptRichards (krypt.Richards@gmail.com)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 ******************************************************************************/
 
#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/panel.h>
#include <wx/window.h>
#endif

namespace wxGUI {

    class VcashApp;

    class MainPanel : public wxPanel {
    public:
        MainPanel(VcashApp &vcashApp, wxWindow &parent);
    };
}

#endif // MAINPANEL_H