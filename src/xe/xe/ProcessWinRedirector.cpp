
#ifdef _WIN32

#include "ProcessWinRedirector.hpp"
#include <sstream>

namespace xe {
    static bool isWinNT() {
        OSVERSIONINFOW osv = {0};
        osv.dwOSVersionInfoSize = sizeof(osv);
        GetVersionExW(&osv);
        return (osv.dwPlatformId == VER_PLATFORM_WIN32_NT);
    }

    ProcessWinRedirector::ProcessWinRedirector(STARTUPINFO *si, PROCESS_INFORMATION *m_pi) {
        SECURITY_ATTRIBUTES sa = {0};
        SECURITY_DESCRIPTOR sd = {0};

        // initialize SECURITY_ATTRIBUTES
        if (isWinNT()) {
            InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
            SetSecurityDescriptorDacl(&sd, true, NULL, false);
            sa.lpSecurityDescriptor = &sd;
        } else {
            sa.lpSecurityDescriptor = NULL;
        }

        // enable process output redirection
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.lpSecurityDescriptor = &sd;
        sa.bInheritHandle = TRUE;

        HANDLE m_hStdIn = 0, m_hStdOut = 0;
        HANDLE m_hReadStdOut = 0, m_hWriteStdIn = 0;

        BOOL result;
        result = ::CreatePipe(&m_hStdIn, &m_hWriteStdIn, &sa, 0);
        result = ::CreatePipe(&m_hReadStdOut, &m_hStdOut, &sa, 0);

        si->dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        si->wShowWindow = SW_HIDE;
        si->hStdOutput = m_hStdOut;
        si->hStdError = m_hStdOut;
        si->hStdInput = m_hStdIn;

        m_hStdIn = m_hStdIn;
        m_hStdOut = m_hStdOut;
        m_hReadStdOut = m_hReadStdOut;
        m_hWriteStdIn = m_hWriteStdIn;

        m_pi = m_pi;
    }

    ProcessWinRedirector::~ProcessWinRedirector() {
        ::CloseHandle(m_hStdIn);
        ::CloseHandle(m_hStdOut);
        ::CloseHandle(m_hReadStdOut);
        ::CloseHandle(m_hWriteStdIn);
    }

    std::string ProcessWinRedirector::getOutput() {
        PROCESS_INFORMATION pi = *m_pi;

        std::stringstream ss;

        while (true) {
            // check for pending reads from stdout
            const int BUFFER_SIZE = 1024;
            char buff[BUFFER_SIZE] = {0};
            DWORD readed = 0;
            DWORD avail = 0;

            ::PeekNamedPipe(m_hReadStdOut, buff, BUFFER_SIZE-1, &readed, &avail, NULL);

            if (readed > 0) {
                ::ZeroMemory(buff, sizeof(buff));

                if (avail > BUFFER_SIZE-1) {
                    while (readed >= BUFFER_SIZE-1) {
                        ::ReadFile(m_hReadStdOut, buff, BUFFER_SIZE-1, &readed, NULL);
                        ss << buff;
                        ::ZeroMemory(buff, sizeof(buff));
                    }
                } else {
                    ::ReadFile(m_hReadStdOut, buff, BUFFER_SIZE-1, &readed, NULL);
                    ss << buff;
                }
            }

            // check if process is running
            unsigned long exitCode = 0;
            ::GetExitCodeProcess(pi.hProcess, &exitCode);

            if (exitCode != STILL_ACTIVE) {
                break;
            }
        }

        return ss.str();
    }
}

#endif
