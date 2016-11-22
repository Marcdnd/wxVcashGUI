Following Vcash dependencies are needed to build the GUI:

libcoin.a
libboost_system.a
libssl.a
libcrypto.a
libleveldb.a
libdb.a
libdb_cxx.a
libdatabase.a

Notice also the the following code in status_manager.cpp has to be disabled before compiling Vcash.

#if (defined __linux__ && !defined __ANDROID__)
    /**
     * Ignore status updates on linux (until there is a UI).
     */
#else
 ...
