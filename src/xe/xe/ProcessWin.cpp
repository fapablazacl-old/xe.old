
#ifdef _WIN32

#include "Process.hpp"
#include "ProcessWinRedirector.hpp"

#include <memory>
#include <cassert>

namespace xe {

    struct Process::Private {
        std::unique_ptr<ProcessWinRedirector> redirector;
        PROCESS_INFORMATION processInfo;
    };

    Process::Process(ProcessFlags flags, const std::string &name, const std::list<std::string> &args) 
        : m_impl(new Process::Private()) {

        assert(m_impl);

        std::string cmdLine = name + " " + boost::join(args, " ");
        char* lpCmdLine = const_cast<char*>(cmdLine.c_str());

        STARTUPINFO si = {0};
        si.cb = sizeof(STARTUPINFO);

        PROCESS_INFORMATION pi = {0};

        std::unique_ptr<ProcessWinRedirector> redirector;

        if (flags&ProcessFlags::Redirect) {
            redirector = std::make_unique<ProcessWinRedirector>(&si, &m_impl->processInfo);
        }

        // invoke process
        BOOL result = ::CreateProcess (
            nullptr, lpCmdLine,
            NULL, NULL, TRUE,
            CREATE_SUSPENDED, NULL, NULL,
            &si, &pi
        );

        if (result == FALSE) {
            throw std::runtime_error(std::to_string(::GetLastError()));
        }

        m_impl->processInfo = pi;
        m_impl->redirector = std::move(redirector);
    }

    Process::~Process() {
        ::CloseHandle(m_impl->processInfo.hProcess);
        ::CloseHandle(m_impl->processInfo.hThread);

        PROCESS_INFORMATION pi = { 0 };
        m_impl->processInfo = pi;

        delete m_impl;
    }

    int Process::getExitCode() const {
        DWORD exitCode = 0;

        if (!::GetExitCodeProcess(m_impl->processInfo.hProcess, &exitCode)) {
            throw std::runtime_error(std::to_string(::GetLastError()));
        } else {
            return static_cast<int>(exitCode);
        }
    }

    ProcessStatus Process::getStatus() const {
        return ProcessStatus::Executing;
    }

    void Process::start() {
        if (::ResumeThread(m_impl->processInfo.hThread) == FALSE) {
            throw std::runtime_error(std::to_string(::GetLastError()));
        }    
    }

    void Process::terminate() {
        if (::TerminateProcess(m_impl->processInfo.hProcess, -1) == FALSE) {
            throw std::runtime_error(std::to_string(::GetLastError()));
        }
    }

    void Process::pause() {
        throw std::runtime_error("");
    }

    void Process::wait() {
        if (::WaitForSingleObject(m_impl->processInfo.hProcess, INFINITE) == WAIT_FAILED) {
            throw std::runtime_error(std::to_string(::GetLastError()));
        }
    }

    std::string Process::getOutput() const {
        if (!m_impl->redirector) {
            throw std::runtime_error("Process::getOutput: The process wasn't created with a valid redirector.");
        }

        return m_impl->redirector->getOutput();
    }
}

#endif
