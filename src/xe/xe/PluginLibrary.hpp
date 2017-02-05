
#pragma once

#ifndef __xe_pluginlibrary_hpp__
#define __xe_pluginlibrary_hpp__

#include <string>
#include <memory>

#include <xe/Library.hpp>
#include <xe/Plugin.hpp>

namespace xe { 

    class XE_API Core;
    class XE_API Plugin;

    class XE_API PluginLibrary : public Plugin {
    public:
        explicit PluginLibrary(std::unique_ptr<Library> library);

        virtual ~PluginLibrary();
        
        virtual PluginData getData() const override;

        virtual void start(Core *core) override;

        virtual void stop(Core *core) override;

    private:
        struct Private;
        Private *m_impl;
    };
}

#endif 
