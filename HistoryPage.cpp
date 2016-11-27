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
 
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/clipbrd.h>
#include <wx/sizer.h>
#include <wx/imaglist.h>
#include <wx/menu.h>
#endif

#include "HistoryPage.h"
#include "Resources.h"
#include "VcashApp.h"

namespace wxGUI {
    int cmpDatesFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData) {
        HistoryPage *historyPage = (HistoryPage *) sortData;
        std::string txid1 = *(std::string *) item1;
        std::string txid2 = *(std::string *) item2;
        std::time_t t1 = historyPage->transactions.find(txid1)->second.time;
        std::time_t t2 = historyPage->transactions.find(txid2)->second.time;
        if (t1 < t2)
            return 1;
        else if (t1 > t2)
            return -1;
        else
            return 0;
    }
}

using namespace wxGUI;

HistoryPage::HistoryPage(VcashApp &vcashApp, wxWindow &parent)
        : transactions(), wxPanel(&parent) {

    vcashApp.view.historyPage = this;

    listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                              wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_NONE);

    wxBitmap redR = Resources::redR;
    wxImage redL = redR.ConvertToImage().Rotate180();
    wxBitmap greenR = Resources::greenR;
    wxImage greenL = greenR.ConvertToImage().Rotate180();;
    wxBitmap yellowR = Resources::yellowR;
    wxImage yellowL = yellowR.ConvertToImage().Rotate180();;

    int dim = wxMax(redL.GetHeight(), redL.GetWidth());
    wxImageList *statusImages = new wxImageList(dim, dim, true);
    statusImages->Add(redL);
    statusImages->Add(greenL);
    statusImages->Add(yellowL);
    statusImages->Add(redR);
    statusImages->Add(greenR);
    statusImages->Add(yellowR);

    listCtrl->SetImageList(statusImages, wxIMAGE_LIST_SMALL);

    listCtrl->InsertColumn(Icon, wxT(""), wxLIST_FORMAT_CENTER, 24);
    listCtrl->InsertColumn(Date, wxT("Date"), wxLIST_FORMAT_LEFT, 133);
    listCtrl->InsertColumn(Status, wxT("Status"), wxLIST_FORMAT_LEFT, 120);
    listCtrl->InsertColumn(Amount, wxT("Amount"), wxLIST_FORMAT_LEFT, 125);

    wxSizer *pageSizer = new wxBoxSizer(wxHORIZONTAL);
    pageSizer->Add(listCtrl, 1, wxALL | wxEXPAND, 5);

    SetSizerAndFit(pageSizer);


    listCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [this, &vcashApp](wxListEvent &event) {
        long index = event.GetIndex();

        enum PopupMenu {
            BlockExplorer, Copy, Info, Lock
        };
        wxMenu popupMenu;
        popupMenu.Append(BlockExplorer, wxT("&Block explorer"));
        popupMenu.Append(Copy, wxT("&Copy"));
        popupMenu.Append(Info, wxT("&Information"));
        popupMenu.Append(Lock, wxT("&Lock"));

        auto select = GetPopupMenuSelectionFromUser(popupMenu);
        listCtrl->SetItemState(index, 0,
                               wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED);

        switch (select) {
            case BlockExplorer: {
                std::string txid = *((std::string *) listCtrl->GetItemData(index));
                std::string url = "https://www.blockexperts.com/xvc/tx/" + txid;
                wxLaunchDefaultBrowser(url);
                break;
            }

            case Copy: {
                std::string txid = *((std::string *) listCtrl->GetItemData(index));

                auto clipboard = wxTheClipboard;

                if (clipboard->Open()) {
                    clipboard->Clear();
                    clipboard->SetData(new wxTextDataObject(txid));
                    clipboard->Flush();

                    clipboard->Close();
                }
                break;
            }

            case Info: {
                std::string txid = *((std::string *) listCtrl->GetItemData(index));
                std::string cmd = "gettransaction " + txid;
                vcashApp.controller.onConsoleCommandEntered(cmd);
                break;
            }

            case Lock: {
                std::string txid = *((std::string *) listCtrl->GetItemData(index));
                vcashApp.controller.onZerotimeLockTransaction(txid);
                break;
            }

            default: {
                break;
            };
        }
    });
}

void HistoryPage::addTransaction(const std::string &txid, const std::time_t &time, const std::string &status,
                                 const std::string &amount) {
    long newItemIndex = transactions.size();
    TxData txData = { time };
    auto pair = transactions.insert(std::make_pair(txid, txData));

    long index;

    if (pair.second) {
        // Not in list. This is a new insertion
        wxListItem item{};
        item.SetId(newItemIndex);

        index = listCtrl->InsertItem(item);
        if (index >= 0) {
            listCtrl->SetItemPtrData(index, (wxUIntPtr) &(pair.first->first)); // set txid as item txData
        } else
            transactions.erase(pair.first); // was not inserted in listCtrl. Remove it from transactions map
    } else {
        // This is a replacement
        index = listCtrl->FindItem(-1, (wxUIntPtr) &(pair.first->first)); // search for item with this txid
    }

    if (index >= 0) {
        char formattedTime[256];
        std::strftime(formattedTime, sizeof(formattedTime), "%m/%d/%y %H:%M:%S", std::localtime(&time));

        listCtrl->SetItem(index, Icon, wxString(""), Yellow);
        listCtrl->SetItem(index, Date, wxString(formattedTime));
        listCtrl->SetItem(index, Status, wxString(status));
        listCtrl->SetItem(index, Amount, wxString(amount));
        listCtrl->SetItemState(index, 0, 0);
        // listCtrl->EnsureVisible(index);
    }

    listCtrl->SortItems(cmpDatesFunction, (wxIntPtr) this);
}

void HistoryPage::setColour(const std::string &txid, BulletColor color) {
    auto it = transactions.find(txid);
    if (it != transactions.end()) {
        long index = listCtrl->FindItem(-1,
                                        (wxUIntPtr) &(it->first));  // find index of item in listCtrl with this txid
        if (index >= 0) {
            bool isOut = listCtrl->GetItemText(index, Amount)[0] == '-';
            int numImages = listCtrl->GetImageList(wxIMAGE_LIST_SMALL)->GetImageCount();
            listCtrl->SetItem(index, Icon, wxString(""), isOut ? color : numImages / 2 + color);
        }
    }
}

void HistoryPage::setStatus(const std::string &txid, const std::string &status) {
    auto it = transactions.find(txid);
    if (it != transactions.end()) {
        long index = listCtrl->FindItem(-1,
                                        (wxUIntPtr) &(it->first));  // find index of item in listCtrl with this txid
        if (index >= 0) {
            listCtrl->SetItem(index, Status, wxString(status));
        }
    }
}
