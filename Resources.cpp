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

#include "Resources.h"

#include "resources/greenR16.cpp"
#include "resources/redR16.cpp"
#include "resources/yellowR16.cpp"

#include "resources/connecting22.cpp"
#include "resources/locked22.cpp"
#include "resources/settings22.cpp"
#include "resources/tools22.cpp"
#include "resources/unlocked22.cpp"

#if defined ( __WXGTK__) || defined (__WXMSW__)
#include "resources/vcash.cpp"
#endif

using namespace wxGUI;

void Resources::init() {
    wxInitAllImageHandlers();

    redR = wxBITMAP_PNG_FROM_DATA(redR16);
    greenR = wxBITMAP_PNG_FROM_DATA(greenR16);
    yellowR = wxBITMAP_PNG_FROM_DATA(yellowR16);

    connecting = wxBITMAP_PNG_FROM_DATA(connecting22);
    locked = wxBITMAP_PNG_FROM_DATA(locked22);
    settings = wxBITMAP_PNG_FROM_DATA(settings22);
    tools = wxBITMAP_PNG_FROM_DATA(tools22);
    unlocked = wxBITMAP_PNG_FROM_DATA(unlocked22);

    wxBitmap bm = wxBITMAP_PNG_FROM_DATA(vcash);
    vcashIcon.CopyFromBitmap(bm);
}

wxBitmap Resources::redR;

wxBitmap Resources::greenR;

wxBitmap Resources::yellowR;

wxBitmap Resources::connecting;

wxBitmap Resources::locked;

wxBitmap Resources::settings;

wxBitmap Resources::tools;

wxBitmap Resources::unlocked;

wxIcon Resources::vcashIcon;
