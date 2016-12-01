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
#include "wx/sizer.h"
#endif

#include "ConsolePage.h"
#include "VcashApp.h"

using namespace wxGUI;

ConsolePage::ConsolePage(VcashApp &vcashApp, wxWindow &parent) : wxPanel(&parent) {
    vcashApp.view.consolePage = this;

    int cols = 1, vgap = 10, hgap = 15;
    wxFlexGridSizer *fgs = new wxFlexGridSizer(cols, vgap, hgap);

    output = new wxRichTextCtrl(
            this, wxID_ANY, wxEmptyString, wxDefaultPosition,
            wxDefaultSize, wxVSCROLL | wxBORDER_NONE | wxWANTS_CHARS);


    wxFont fixedFont = wxFont(11, wxFIXED, wxNORMAL, wxNORMAL);
    output->SetFont(fixedFont);

    command = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    output->SetToolTip(wxT("Results of invoked RPC commands"));
    command->SetToolTip(wxT("RPC command to invoke"));

    fgs->Add(output, 1, wxEXPAND);
    fgs->Add(command, 1, wxEXPAND);

    fgs->AddGrowableRow(0, 1);
    fgs->AddGrowableCol(0, 1);

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(fgs, 1, wxALL | wxEXPAND, 10);
    SetSizerAndFit(hbox);
    Centre();

    command->Bind(wxEVT_TEXT_ENTER, [this, &vcashApp](wxCommandEvent &) {
        std::string cmd = command->GetValue().ToStdString();
        vcashApp.controller.onConsoleCommandEntered(cmd);
    });

    output->Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent &) {
        command->SetFocus();
    });
}

void ConsolePage::appendToConsole(const std::string &text, bool bold) {
    //output->SetEditable(true);
    if(bold) {
        output->BeginBold();
        output->BeginFontSize(output->GetFont().GetPointSize()+2);
        output->BeginStandardBullet("X",0,30);
    }
    output->WriteText(wxString(text));
    output->Newline();
    if(bold) {
        output->EndFont();
        output->EndBold();
        output->EndStandardBullet();
    }

    output->ShowPosition(output->GetLastPosition());
    //output->SetValue(text);
    //output->ScrollPages(100); //   ScrollIntoView(output->GetCaretPosition(), WXK_PAGEDOWN);
    //output-ScrollLines(-1);
}
