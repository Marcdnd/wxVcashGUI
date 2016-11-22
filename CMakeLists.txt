cmake_minimum_required(VERSION 3.5)

project(vcash)

include_directories(./include /usr/local/include/wx-3.0  /usr/local/lib/wx/include/gtk3-unicode-static-3.0 .)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}  -std=c++11 -D_UNICODE -D_FILE_OFFSET_BITS=64  -D__WXGTK__   ")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES AccountPage.cpp AddressesPage.cpp ConsolePage.cpp Controller.cpp EncryptWalletDlg.cpp
        HistoryPage.cpp MiningPage.cpp  Resources.cpp StatisticsPage.cpp StatusBarImage.cpp
        StatusBarWallet.cpp ToolsFrame.cpp ToolsPanel.cpp TransferPage.cpp VcashApp.cpp MainFrame.cpp
        MainPanel.cpp StatusBar.cpp View.cpp OnPairsEvent.cpp)

add_executable(vcash ${SOURCE_FILES})

LINK_DIRECTORIES(/usr/local/lib /usr/lib/x86_64-linux-gnu)

TARGET_LINK_LIBRARIES(vcash
        ${CMAKE_SOURCE_DIR}/lib/libcoin.a
        ${CMAKE_SOURCE_DIR}/lib/libboost_system.a
        ${CMAKE_SOURCE_DIR}/lib/libssl.a
        ${CMAKE_SOURCE_DIR}/lib/libcrypto.a
        ${CMAKE_SOURCE_DIR}/lib/libleveldb.a
        ${CMAKE_SOURCE_DIR}/lib/libdb.a
        ${CMAKE_SOURCE_DIR}/lib/libdb_cxx.a
        ${CMAKE_SOURCE_DIR}/lib/libdatabase.a
        pthread
        wx_gtk3u_core-3.0 wx_baseu-3.0 wx_gtk3u_adv-3.0 gthread-2.0 -pthread gtk-3 gdk-3 X11 SM pangocairo-1.0 pango-1.0 gdk_pixbuf-2.0 cairo-gobject cairo  gio-2.0 gobject-2.0 glib-2.0 png wxregexu-3.0 wxtiff-3.0 wxjpeg-3.0 z dl m)