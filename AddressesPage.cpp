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
 
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include <wx/clipbrd.h>
#include <wx/menu.h>
#include "wx/sizer.h"
#endif

#include "AddressesPage.h"
#include "ToolsFrame.h"
#include "VcashApp.h"

namespace wxGUI {
    int wxCALLBACK AddressesCmpFunct(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortDt) {
        AddressesPage::SortData *sortData = (AddressesPage::SortData *) sortDt;
        wxListCtrl *listCtrl = sortData->listCtrl;
        int col = static_cast<int>(sortData->column);

        long index1 = listCtrl->FindItem(0, item1);
        auto str1 = listCtrl->GetItemText(index1, col);

        long index2 = listCtrl->FindItem(0, item2);
        auto str2 = listCtrl->GetItemText(index2, col);

        int result = str1.Cmp(str2);
        if (result == 0) {
            col = (col + 1) % listCtrl->GetColumnCount();
            str1 = listCtrl->GetItemText(index1, col);
            str2 = listCtrl->GetItemText(index2, col);
        }
        return sortData->ascending ? str1.Cmp(str2) : str2.Cmp(str1);
    }
}

using namespace wxGUI;

AddressesPage::AddressesPage(VcashApp &vcashApp, wxWindow &parent)
        : wxPanel(&parent) {

    vcashApp.view.addressesPage = this;

    addresses = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                               wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_NONE);
    addresses->InsertColumn(Account, "Account", wxLIST_FORMAT_LEFT, 100);
    addresses->InsertColumn(Address, "Address", wxLIST_FORMAT_LEFT, 330);

    wxSizer *pageSizer = new wxBoxSizer(wxVERTICAL);
    pageSizer->Add(addresses, 1, wxALL | wxEXPAND, 5);

    SetSizerAndFit(pageSizer);

    addresses->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [this, &vcashApp](wxListEvent &event) {
        long index = event.GetIndex();

        enum PopupMenu {
            Copy, New, QR
        };
        wxMenu popupMenu;
        popupMenu.Append(Copy, wxT("&Copy"));
        popupMenu.Append(New, wxT("&New"));
        popupMenu.Append(QR, wxT("&QR Code"));

        auto select = GetPopupMenuSelectionFromUser(popupMenu);

        switch (select) {
            case Copy: {
                wxString address = addresses->GetItemText(index, Address);

                auto clipboard = wxTheClipboard;

                if (clipboard->Open()) {
                    clipboard->Clear();
                    clipboard->SetData(new wxTextDataObject(address));
                    clipboard->Flush();

                    clipboard->Close();
                }
                break;
            }
            case New: {
                wxString account = addresses->GetItemText(index, Account);
                vcashApp.controller.onConsoleCommandEntered("getnewaddress " + account.ToStdString());
                break;
            }
            case QR:
                //toDo: generate QR code
                break;
            default:
                break;
        }

        event.Skip();
    });

    sortData = {addresses, Account, true};

    addresses->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &ev) {
        sortData.column = static_cast<Column >(ev.GetColumn());
        sortData.ascending = !sortData.ascending;
        addresses->SortItems(AddressesCmpFunct, (wxIntPtr) &sortData);

    });
}

void AddressesPage::addAddress(const std::string &account, const std::string &address) {
    wxListItem item{};
    int id = addresses->GetItemCount();
    item.SetId(id);
    long index = addresses->InsertItem(item);

    addresses->SetItemPtrData(index, (wxUIntPtr) id);
    addresses->SetItem(index, Account, wxString(account));
    addresses->SetItem(index, Address, wxString(address));
    addresses->SortItems(AddressesCmpFunct, (wxIntPtr) &sortData);
}
