/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <stdexcept>
#include <xe/sys/LibraryPrivate.hpp>

#if defined (_WINDOWS)
#include <Windows.h>

namespace xe { namespace sys {

    static std::string getLastErrorStrWin32() {
        // error string formatting WinAPI call extracted from
        // http://www.paskov.biz/blog/clasterror/

        std::string msg;
        
        DWORD errorCode = ::GetLastError();

        const int errorTextLength = 1024;
        CHAR lpErrorText[1024];

        ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, errorCode, 0, lpErrorText, errorTextLength, 0 );
        msg = lpErrorText;
    
        return msg;
    }

    void Library::Private::load(const std::string &name) {
        if (name.empty() == true) {
            throw std::runtime_error("The library name must be non empty.");
        }

        HANDLE handle = ::LoadLibraryA(name.c_str()); 

        if (!handle) {
            std::string msg;

            msg += "Library::Private::load: Error during the load of the library ";
            msg += "'" + name + "': " + getLastErrorStrWin32();
            
            throw std::runtime_error(msg);
        }

        this->handle = handle;
    }

    void Library::Private::unload() {
        if (this->handle != NULL) {
            ::HMODULE handle = static_cast< ::HMODULE >(this->handle);
            ::FreeLibrary(handle);

            this->handle = NULL;
        }
    }

    FunctionPtr Library::Private::getFunctionPtr(const std::string &name) 
    {
        HMODULE handle = NULL;
        FARPROC procAddress = NULL;

        if (this->handle == NULL) {
            throw std::runtime_error("The library must be loaded first.");
        }

        if (name.empty() == true) {
            throw std::runtime_error("The function name must be non-empty.");
        }

        handle = static_cast<HMODULE>(this->handle);

        procAddress = ::GetProcAddress(handle, name.c_str());

        if (procAddress == NULL) {
            std::string msg;

            msg += "The function name must be non-empty ";
            msg += "(Windows specific error: '" +  getLastErrorStrWin32() + "').";

            throw std::runtime_error(msg);
        }

        return reinterpret_cast<FunctionPtr>(procAddress);
    }
}}

#endif
