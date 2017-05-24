
#ifndef __xe_gfx_png_pluginpng_hpp__
#define __xe_gfx_png_pluginpng_hpp__

#include <memory>
#include <xe/Plugin.hpp>

namespace xe {
    class PluginPNG : public Plugin {
    public:
        PluginPNG();

        virtual ~PluginPNG();

        virtual PluginData getData() const override;

        virtual void start(Core *core) override;

        virtual void stop(Core *core) override;
        
    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif
