
#pragma once 

#ifndef __demo_application_hpp__
#define __demo_application_hpp__

#include <memory>
#include <xe/Core.hpp>

namespace demo {
    class DemoApp : public xe::Core {
    public:
        DemoApp();

        ~DemoApp();

        int run();

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif
