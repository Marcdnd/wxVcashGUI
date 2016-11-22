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
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#endif

#include "EncryptWalletDlg.h"
#include "Resources.h"
#include "StatusBarWallet.h"
#include "VcashApp.h"

using namespace wxGUI;

StatusBarWallet::StatusBarWallet(VcashApp &vcashApp, wxStatusBar &parent)
        : walletStatus(Unknown)
        , bitmapLocked(Resources::locked)
        , bitmapUnlocked(Resources::unlocked)
        , bitmapUnknown (Resources::connecting)
        , StatusBarImage(parent, *new wxBitmap(), [this, &parent, &vcashApp](wxMouseEvent &ev) {
              switch (walletStatus) {
                  case Locked: {
                      bool retry = true;
                      while (retry) {
                          wxPasswordEntryDialog getPasswordDlg(&parent, wxT("Password:"), wxT("Unlock wallet"));
                          auto result = getPasswordDlg.ShowModal();
                          switch (result) {
                              case wxID_CANCEL: {
                                  retry = false;
                                  break;
                              }
                              case wxID_OK: {
                                  std::string password = getPasswordDlg.GetValue().ToStdString();
                                  if (vcashApp.controller.onWalletWantUnlock(password)) {
                                      setWalletStatus(Unlocked);
                                      retry = false;
                                  }
                                  break;
                              }
                              default:
                                  break;
                          }
                      }
                      break;
                  }

                  case Unlocked: {
                      vcashApp.controller.onWalletLock();
                      setWalletStatus(Locked);
                      break;
                  }

                  case Unencrypted: {
                      int result = wxMessageBox(
                              wxT("Encrypting your wallet keeps it safe in case it is lost or stolen."),
                              wxT("Encrypt wallet"), wxYES_NO | wxICON_QUESTION | wxYES_DEFAULT, &parent);
                      if (result == wxYES) {
                          EncryptWalletDlg *encryptWalletDlg = new EncryptWalletDlg(parent, wxT("Encrypt wallet"));
                          auto result = encryptWalletDlg->ShowModal();
                          encryptWalletDlg->Destroy();

                          switch (result) {
                              case wxID_CANCEL:
                                  break;
                              case wxID_OK:
                                  if (vcashApp.controller.onWalletWantEncrypt(
                                          encryptWalletDlg->getPassword())) {
                                      setWalletStatus(Locked);
                                  } else {
                                      wxMessageBox(wxT("Wallet could not be encrypted."), wxT("Encrypt wallet"),
                                                   wxOK | wxICON_EXCLAMATION, &parent);
                                  }
                                  break;
                              default:
                                  break;
                          }
                      }
                      break;
                  }

                  case Unknown: {
                      break;
                  }

              }
          }) {
    setWalletStatus(walletStatus);
};

WalletStatus StatusBarWallet::getWalletStatus() {
    return walletStatus;
}

void StatusBarWallet::setWalletStatus(WalletStatus st) {
    walletStatus = st;
    switch (walletStatus) {
        case Locked:
            SetBitmap(bitmapLocked);
            break;
        case Unlocked:
        case Unencrypted:
            SetBitmap(bitmapUnlocked);
            break;
        case Unknown:
            SetBitmap(bitmapUnknown);
            break;
    }
}

