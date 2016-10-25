
#include <iostream>
#include <xe/Core.hpp>
#include <xe/Matrix.hpp>
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
        
        out vec4 f_color;
        
        uniform mat4 m_mvp;
            
        void main() {
            gl_Position = m_mvp * vec4(v_coord, 1.0f);
            f_color = v_color;
        }
    )";
    
    std::string fragShader = R"(
        #version 330

        in vec4 f_color;
            
        void main() {
            gl_FragColor = f_color;
        }
    )";

    std::list<xe::gfx::ShaderSource> sources = {
        {xe::gfx::ShaderType::Vertex, vertShader},
        {xe::gfx::ShaderType::Fragment, fragShader}
    };

    auto program = device->createProgram(sources);
    
    device->setProgram(program.get());

    xe::gfx::MeshFormat meshFormat {{
        {0, xe::DataType::Float32, 3, "v_coord"},
        {0, xe::DataType::Float32, 4, "v_color"},
        {1, xe::DataType::UInt32, 1}
    }};
    
    // index data
    std::vector<unsigned int> indices = {
        1, 2, 3
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
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
        {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
    };

    std::vector<xe::gfx::BufferCreateParams> params = {
        {xe::gfx::BufferType::Vertex, vertices},
        {xe::gfx::BufferType::Index, indices}
    };
    
    auto mesh = device->createMesh(&meshFormat, params);
    
    float angle = 0.0f;
    
    while(true) {
        angle ++;
        
        if (angle > 360.0f) {
            angle = 0.0f;
        }
        
        inputManager->poll();

        if (isPressed(keyboardStatus->getKeyStatus(KeyCode::KeyEsc))) {
            break;
        }

        device->beginFrame(xe::gfx::ClearFlags::All, {{0.2f, 0.25f, 0.3f, 1.0f}});
        
        auto mvp = xe::Matrix4f::makeIdentity();
        
        mvp = xe::Matrix4f::makeRotate(angle * 3.14159265f / 180.0f, xe::Vector3f(0.0f, 1.0f, 0.0f));
        
        device->setUniformMatrix(program->getUniform("m_mvp"), 1, false, mvp.values);
        
        device->setMesh(mesh.get());
        device->draw(xe::gfx::Primitive::TriangleList, 0, 3);

        device->endFrame();
    }

    return 0;
}
