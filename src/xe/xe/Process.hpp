
#pragma once

#ifndef __xe_process_hpp__
#define __xe_process_hpp__

#include <string>
#include <list>
#include <xe/PreDef.hpp>

namespace xe {

    /**
     * @brief Process execution status.
     */
    enum class ProcessStatus {
        Stopped,     //! The process has not begun, or has been terminated.
        Executing     //! The process is currently executing.
    }; 

    /**
     * @brief Flags passed during process creation
     */
    enum class ProcessFlags {
        Default,    //! Default proccess execution.
        Redirect    //! Redirection
    };

    inline bool operator& (ProcessFlags flags, ProcessFlags flag) {
        if (static_cast<int>(flags)&static_cast<int>(flag)) {
            return true;
        } else {
            return false;
        }
    }

    class XE_API Process {
    public:
        Process(ProcessFlags flags, const std::string &name, const std::list<std::string> &args = std::list<std::string>());

        ~Process();

        int getExitCode() const;

        ProcessStatus getStatus() const;

        void start();

        void terminate();

        void pause();

        void wait();

        std::string getOutput() const;

    private:
        struct Private;
        Private *m_impl;
    };
}

#endif
