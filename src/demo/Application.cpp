
#include "Application.hpp"

#include "Camera.hpp"
#include "PhongMaterial.hpp"
#include "PhongPipeline.hpp"
#include "Mesh.hpp"

namespace demo {
    int Application::run() {
        using xe::input::isPressed;
        using xe::input::KeyCode;

        m_device = this->createDevice();
        m_meshFormat = this->createMeshFormat();

        m_pipeline = std::make_unique<xe::sg::PhongPipeline>(m_device.get());
        m_sceneRenderer = std::make_unique<xe::sg::SceneRenderer>(m_pipeline.get());

        m_materials = this->createMaterials();
        m_renderables = this->createRenderables();
        m_scene = this->createScene();

        auto inputManager = m_device->getInputManager();
        auto keyboardStatus = inputManager->getKeyboard()->getStatus();
        
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

            m_sceneRenderer->renderFrame(m_scene.get());
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

    xe::gfx::MeshFormatPtr Application::createMeshFormat() {
        auto meshFormat = new xe::gfx::SubsetFormat {
            {0, xe::DataType::Float32, 3, "v_coord"},
            {0, xe::DataType::Float32, 3, "v_normal"}
        };

        return xe::gfx::MeshFormatPtr(meshFormat);
    }

    std::map<std::string, xe::sg::RenderablePtr> Application::createRenderables() {
        std::map<std::string, xe::sg::RenderablePtr> renderables;

        // create a basic camera 
        renderables["lookAtCamera"] = std::make_unique<xe::sg::LookAtPerspectiveCamera>();

        // create a colored triangle mesh
        std::vector<float> vertices = {
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        std::vector<xe::gfx::BufferCreateParams> params = {
            {xe::gfx::BufferType::Vertex, vertices}
        };
        
        auto subset = m_device->createSubset(m_meshFormat.get(), params);
        auto mesh = std::make_unique<xe::sg::Mesh>(std::move(subset));

        mesh->getEnvelope(0)->material = m_materials["blank"].get();
        mesh->getEnvelope(0)->primitive = xe::gfx::Primitive::TriangleStrip;
        mesh->getEnvelope(0)->count = 3;

        m_renderables["triangleMesh"] = std::move(mesh);

        return renderables;
    }

    std::map<std::string, xe::gfx::MaterialPtr> Application::createMaterials() {
        std::map<std::string, xe::gfx::MaterialPtr> materials;

        // create a basic material, default material
        materials["blank"] = std::make_unique<PhongMaterial>();

        return materials;
    }

    xe::sg::ScenePtr Application::createScene() {
        auto scene = std::make_unique<xe::sg::Scene>();

        scene
            ->setBackColor({0.2f, 0.2f, 0.8f, 1.0f})
            ->getNode()->setRenderable(m_renderables["lookAtCamera"].get())
                ->createNode()->setRenderable(m_renderables["triangleMesh"].get());

        return scene;
    }
}

int main() {
    return demo::Application().run();
}
