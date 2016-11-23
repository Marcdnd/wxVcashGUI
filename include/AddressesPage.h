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
 
#ifndef ADDRESSESPAGE_H
#define ADDRESSESPAGE_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/window.h>
#endif

namespace wxGUI {

    class VcashApp;

    class AddressesPage : public wxPanel {
    public:
        AddressesPage(VcashApp &vcashApp, wxWindow &parent);

        void addAddress(const std::string &account, const std::string &address);

    private:
        wxListCtrl *addresses;
        enum Column { Account, Address };

        struct SortData {
            wxListCtrl *listCtrl;
            Column column;
            bool ascending;
        };

        SortData sortData;

        friend int wxCALLBACK AddressesCmpFunct(long item1, long item2, wxIntPtr sortDt);
    };
}

#endif // ADDRESSESPAGE_H