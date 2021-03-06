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
 
#ifndef VIEW_H
#define VIEW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/app.h>
#include <wx/checkbox.h>
#include "wx/listctrl.h"
#include <wx/stattext.h>
#include <wx/statusbr.h>
#endif

#include "HistoryPage.h"
#include "StatisticsPage.h"
#include "StatusBarWallet.h"

namespace wxGUI {

    class AddressesPage;
    class AccountPage;
    class ConsolePage;
    class MainFrame;
    class MiningPage;
    class StatusBarWallet;
    class StatusBar;
    class ToolsFrame;
    class ToolsPanel;

    class View {
    public:
        // Status bar
        void setWalletStatus(WalletStatus walletStatus);

        WalletStatus getWalletStatus();

        void setStatusBarMessage(const std::string &msg);

        // Account
        void setBalance(const std::string &balance);

        void setUnconfirmed(const std::string &unconfirmed);

        void setStake(const std::string &stake);

        void setImmature(const std::string &immature);

        // History of transactions
        void addTransaction(const std::string &txid, const std::time_t &date, const std::string &status,
                            const std::string &amount);

        void setColour(const std::string &txid, BulletColor color);

        void setStatus(const std::string &txid, const std::string &status);

        // Statistics
        void setTCP(const std::string &tcp);

        void setUDP(const std::string &udp);

        void setEstimated(const std::string &estimated);

        void setTotal(const std::string &total);

        void setDifficulty(const std::string &difficulty);

        void setSupply(const std::string &supply);

        // Mining
        void setMining(bool mining);

        bool getMining();

        // Console
        void appendToConsole(const std::string &text, bool bold = false);

        // Address book
        void addAddress(const std::string &account, const std::string &address);

        // Messages and notifications
        void MessageBox(const std::string &msg, const std::string &title, long style);

        void NotificationBox(const std::string &msg, const std::string &title);

        MainFrame *mainFrame;
        ToolsFrame *toolsFrame;
        StatusBar *statusBar;
        ToolsPanel *toolsPanel;
        StatusBarWallet *walletLock;

        AddressesPage *addressesPage;
        AccountPage *accountPage;
        ConsolePage *consolePage;
        HistoryPage *historyPage;
        MiningPage *miningPage;
        StatisticsPage *statisticsPage;
    };
}

#endif // VIEW_H
