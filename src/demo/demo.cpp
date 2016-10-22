
#include <iostream>
#include <xe/Core.hpp>
#include <xe/PluginManager.hpp>
#include <xe/gfx/Manager.hpp>
#include <xe/gfx/Device.hpp>
#include <xe/gfx/DeviceInfo.hpp>

int main() {
    using xe::Core;
    using xe::input::isPressed;
    using xe::input::KeyCode;

    Core core;

    core.getPluginManager()->load("xe.gfx.gl3");

    /*
    auto deviceInfos = core.getGraphicsManager()->enumerateDevices();

    std::cout << "Available graphics devices:" << std::endl;

    for (const xe::gfx::DeviceInfo &deviceInfo : deviceInfos) {
        std::cout << deviceInfo << std::endl;
    }
    */

    auto device = core.getGraphicsManager()->createDevice();
    auto inputManager = device->getInputManager();
    auto keyboardStatus = inputManager->getKeyboard()->getStatus();

    // shaders
    std::string vertShader = R"(
        #version 330

        in vec3 v_coord;
        in vec4 v_color;
        
        void main() {
            gl_Position = vec4(v_coord, 1.0f);
        }
    )";
    
    std::string fragShader = R"(
        #version 330

        void main() {
            gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    )";

    std::list<xe::gfx::ShaderSource> sources = {
        {xe::gfx::ShaderType::Vertex, vertShader},
        {xe::gfx::ShaderType::Fragment, fragShader}
    };

    auto program = device->createProgram(sources);

    device->setProgram(program.get());

    xe::gfx::MeshFormat meshFormat {{
        {xe::gfx::BufferType::Vertex, 0, xe::DataType::Float32, 3, "v_coord"},
        {xe::gfx::BufferType::Vertex, 0, xe::DataType::Float32, 4, "v_color"}, 
        {xe::gfx::BufferType::Index, 1, xe::DataType::UInt32, 1} 
    }};
    
    // index data
    std::vector<unsigned int> indices = {
        0, 1, 2
    };
    
    // vertex data
    struct Vertex {
        xe::Vector3f coord;
        xe::Vector4f color;
        
        Vertex() {}

        Vertex(xe::Vector3f coord_, xe::Vector4f color_) 
            : coord(coord_), color(color_) {}
    };

    std::vector<Vertex> vertices = {
        //{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}},
        {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
    };

    auto mesh = device->createMesh(&meshFormat, {{vertices},{indices}});
    
    while(true) {
        inputManager->poll();

        if (isPressed(keyboardStatus->getKeyStatus(KeyCode::KeyEsc))) {
            break;
        }

        device->beginFrame(xe::gfx::ClearFlags::All, {{0.2f, 0.2f, 0.8f, 1.0f}});

        device->setMesh(mesh.get());
        device->draw(xe::gfx::Primitive::TriangleList, 0, 3);

        device->endFrame();
    }

    return 0;
}
