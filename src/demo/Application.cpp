
#include "Application.hpp"

namespace demo {
    int Application::run() {
        using xe::input::isPressed;
        using xe::input::KeyCode;

        m_device = this->createDevice();
        m_program = this->createProgram();
        m_meshFormat = this->createMeshFormat();

        auto inputManager = m_device->getInputManager();
        auto keyboardStatus = inputManager->getKeyboard()->getStatus();

        m_device->setProgram(m_program.get());

        // index data
        std::vector<unsigned int> indices = {
            1, 2, 3
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
        
        auto mesh = m_device->createSubset(m_meshFormat.get(), params);
        
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

            m_device->beginFrame(xe::gfx::ClearFlags::All, {{0.2f, 0.25f, 0.3f, 1.0f}});
        
            auto mvp = xe::Matrix4f::makeIdentity();
        
            mvp = xe::Matrix4f::makeRotate(angle * 3.14159265f / 180.0f, xe::Vector3f(0.0f, 1.0f, 0.0f));
        
            m_device->setUniformMatrix(m_program->getUniform("m_mvp"), 1, false, mvp.values);
        
            m_device->setMesh(mesh.get());
            m_device->draw(xe::gfx::Primitive::TriangleList, 0, 3);

            m_device->endFrame();
        }

        return 0;
    }

        Application::Application() {
        this->getPluginManager()->load("xe.gfx.gl3");
    }

    Application::~Application() {}

    xe::gfx::DevicePtr Application::createDevice() {
        /*
        auto deviceInfos = core.getGraphicsManager()->enumerateDevices();

        std::cout << "Available graphics devices:" << std::endl;

        for (const xe::gfx::DeviceInfo &deviceInfo : deviceInfos) {
            std::cout << deviceInfo << std::endl;
        }
        */

        return this->getGraphicsManager()->createDevice();
    }

    xe::gfx::ProgramPtr Application::createProgram() {
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

        return m_device->createProgram(sources);
    }

    xe::gfx::MeshFormatPtr Application::createMeshFormat() {
        auto meshFormat = new xe::gfx::SubsetFormat {
            {0, xe::DataType::Float32, 3, "v_coord"},
            {0, xe::DataType::Float32, 4, "v_color"},
            {1, xe::DataType::UInt32, 1}
        };

        return xe::gfx::MeshFormatPtr(meshFormat);
    }

    std::map<std::string, xe::sg::RenderablePtr> Application::createRenderableMap() {
        std::map<std::string, xe::sg::RenderablePtr> renderableMap;

        return renderableMap;
    }

    xe::sg::ScenePtr Application::createScene() {
        auto scene = std::make_unique<xe::sg::Scene>();

        return scene;
    }
}

int main() {
    return demo::Application().run();
}
