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
 
#ifndef STATUSBARIMAGE_H
#define STATUSBARIMAGE_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/icon.h>
#include <wx/event.h>
#include <wx/statbmp.h>
#include <wx/statusbr.h>
#endif

#include <functional>

namespace wxGUI {

    class StatusBarImage : public wxStaticBitmap {
    public:
		StatusBarImage(wxStatusBar &parent, wxBitmap &bitmap);

        StatusBarImage(wxStatusBar &parent, wxBitmap &bitmap, std::function<void(wxMouseEvent &)> onClickCode);

        void bindOnLeftClick(std::function<void(wxMouseEvent &)> onClickCode);
    };
}

#endif // STATUSBARIMAGE_H