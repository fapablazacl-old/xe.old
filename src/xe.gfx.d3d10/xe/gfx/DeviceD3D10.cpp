
#include "DeviceD3D10.hpp"

namespace xe { namespace gfx {

    DeviceD3D10::DeviceD3D10(const std::string &class_) 
    {
        const int DefaultWidth = 800;
        const int DefaultHeight = 600;

        // create the window
        m_hWnd = ::CreateWindow (
            class_.c_str(), 
            "test", 
            WS_OVERLAPPEDWINDOW, 
            CW_USEDEFAULT, CW_USEDEFAULT, 
            DefaultWidth, DefaultHeight, 
            NULL, NULL, 
            ::GetModuleHandle(NULL), 
            NULL
        );

        assert(m_hWnd);

        // create the Direct3D device 
        DXGI_SWAP_CHAIN_DESC scd = {};

        // back buffer properties
        scd.BufferCount = 1;
        scd.BufferDesc.Width = DefaultWidth;
        scd.BufferDesc.Height = DefaultHeight;
        scd.BufferDesc.RefreshRate.Numerator = 60;
        scd.BufferDesc.RefreshRate.Denominator = 1;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        // number of samples 
        scd.SampleDesc.Count = 1;
        scd.SampleDesc.Quality = 0;

        // render to
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

        // wich window render to
        scd.OutputWindow = m_hWnd;

        // most efficient render
        scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        scd.Flags = 0;

        // create device and the swapchain
        ::D3D10CreateDeviceAndSwapChain(0, D3D10_DRIVER_TYPE_HARDWARE, 0, 0, D3D10_SDK_VERSION, &scd, &m_swapChain, &m_device);

        // create a RenderTargetView for the Device
        ID3D10Texture2D *backBuffer = nullptr;
        m_swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&backBuffer);
        m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
        backBuffer->Release();

        m_device->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

        // setup viewport
        D3D10_VIEWPORT vp = {};

        vp.TopLeftX = vp.TopLeftY = 0;
        vp.Width = DefaultWidth;
        vp.Height = DefaultHeight;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        m_device->RSSetViewports(1, &vp);
    }

    DeviceD3D10::~DeviceD3D10()
    {
        m_renderTargetView->Release();
        m_swapChain->Release();
        m_device->Release();

        ::DestroyWindow(m_hWnd);
    }

    xe::input::InputManager* DeviceD3D10::getInputManager() 
    {
        return nullptr;
    }

    const xe::input::InputManager* DeviceD3D10::getInputManager() const 
    {
        return nullptr;
    }

    SubsetPtr DeviceD3D10::createSubset(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer) 
    {
        return SubsetPtr();
    }
        
    BufferPtr DeviceD3D10::createBuffer(const BufferType type, const std::size_t size, const void *data) 
    {
        return BufferPtr();
    }

    TexturePtr DeviceD3D10::createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData) 
    {
        return TexturePtr();
    }

    ProgramPtr DeviceD3D10::createProgram(const std::list<ShaderSource> &sources) 
    {
        assert(sources.size() > 0);
        
        return ProgramPtr();
    }

    void DeviceD3D10::setProgram(Program *program) 
    {
        assert(program);
    }

    Program* DeviceD3D10::getProgram() 
    {
        return nullptr;
    }
        
    void DeviceD3D10::setMaterial(Material *material) 
    {
        assert(material);
    }

    void DeviceD3D10::setMesh(Subset *mesh) 
    {
        assert(mesh);
    }

    void DeviceD3D10::draw(Primitive primitive, size_t start, size_t count) 
    {
        assert(start >= 0);
        assert(count > 0);
    }

    void DeviceD3D10::beginFrame(const ClearFlags flags, const ClearParams &params) 
    {
        assert(m_swapChain);

        m_device->ClearRenderTargetView(m_renderTargetView, params.color.values);

    }

    void DeviceD3D10::endFrame() 
    {
        assert(m_swapChain);

        m_swapChain->Present(0, 0);
    }

    void DeviceD3D10::setUniformMatrix(int location, int total, bool transpose, float *values) 
    {
        assert(location);
        assert(values);

    }

    void DeviceD3D10::setUniform(const UniformDescriptor &desc, const void* uniform) 
    {
        assert(uniform);
    }
}}
