
#include "PluginD3D10.hpp"

#include <cassert>

namespace xe { namespace gfx {
    PluginD3D10::PluginD3D10() 
        : m_hInstance(::GetModuleHandle(NULL)),  m_class("xe::gfx::DeviceD3D10") {}

    PluginD3D10::~PluginD3D10() {}

    PluginData PluginD3D10::getData() const {
        return {
            "Direct3D 10 Graphics Device", 
            "Direct3D 10 Graphics Device Implementation.", 
            {1, 0}
        };
    }

    void PluginD3D10::start(Core *core) {
        assert(core);
        assert(!m_factory);

        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.hInstance = m_hInstance;
        wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = ::LoadCursor(NULL, IDI_APPLICATION);
        wc.lpfnWndProc = DefWindowProc;
        wc.hbrBackground = (HBRUSH) COLOR_BTNFACE;
        wc.lpszClassName = m_class.c_str();

        ::RegisterClassEx(&wc);

        m_factory = std::make_unique<FactoryD3D10>(m_class);

        core->getGraphicsManager()->registerFactory(m_factory.get());
    }

    void PluginD3D10::stop(Core *core) {
        assert(core);
        assert(m_factory);

        core->getGraphicsManager()->unregisterFactory(m_factory.get());

        m_factory.reset(nullptr);

        ::UnregisterClass(m_class.c_str(), m_hInstance);
    }
}}

XE_EXPORT_PLUGIN(xe::Core, xe::gfx::PluginD3D10)
