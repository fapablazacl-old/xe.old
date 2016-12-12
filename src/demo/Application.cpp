
#include "Application.hpp"

#include <xe/sg/Generator.hpp>

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

        m_meshNode = m_scene->getNode()->getNode(0);
        assert(m_meshNode);

        auto inputManager = m_device->getInputManager();
        auto keyboardStatus = inputManager->getKeyboard()->getStatus();
        
        float angle = 0.0f;
    
        while(true) {
            angle += 0.3f;

            if (angle > 360.0f) {
                angle = 0.0f;
            }

            inputManager->poll();

            if (isPressed(keyboardStatus->getKeyStatus(KeyCode::KeyEsc))) {
                break;
            }

            const float rad_angle = xe::radians(angle);

            const auto rotationX = xe::Matrix4f::makeRotateX(rad_angle);
            const auto rotationY = xe::Matrix4f::makeRotateY(rad_angle);
            const auto rotationZ = xe::Matrix4f::makeRotateZ(rad_angle);

            m_meshNode->setMatrix(rotationX * rotationY * rotationZ);

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
            {1, xe::DataType::Float32, 3, "v_normal"},
            {2, xe::DataType::UInt32, 1}    // index buffer
        };

        return xe::gfx::MeshFormatPtr(meshFormat);
    }

    std::map<std::string, xe::sg::RenderablePtr> Application::createRenderables() {
        std::map<std::string, xe::sg::RenderablePtr> renderables;

        // create a basic camera 
        renderables["lookAtCamera"] = std::make_unique<xe::sg::LookAtPerspectiveCamera>();

        // create a colored triangle mesh
        xe::sg::Generator generator;
        xe::sg::SphereGenerator sphereGenerator(16, 16);

        std::vector<xe::Vector3f> coords = sphereGenerator.genCoords(1.0f);
        std::vector<std::uint32_t> indices = sphereGenerator.genIndices();

        std::vector<xe::Vector3f> normals = sphereGenerator.genNormals(coords);

        std::vector<xe::gfx::BufferCreateParams> params = {
            {xe::gfx::BufferType::Vertex, coords}, 
            {xe::gfx::BufferType::Vertex, normals}, 
            {xe::gfx::BufferType::Index, indices}
        };
        
        auto subset = m_device->createSubset(m_meshFormat.get(), params);
        auto mesh = std::make_unique<xe::sg::Mesh>(std::move(subset));

        mesh->getEnvelope(0)->material = m_materials["blank"].get();
        mesh->getEnvelope(0)->primitive = xe::gfx::Primitive::TriangleList;
        mesh->getEnvelope(0)->count = indices.size();

        renderables["triangleMesh"] = std::move(mesh);

        return renderables;
    }

    std::map<std::string, xe::gfx::MaterialPtr> Application::createMaterials() {
        std::map<std::string, xe::gfx::MaterialPtr> materials;

        auto blankMaterial = std::make_unique<PhongMaterial>();

        auto status = blankMaterial->getStatus();

        status->cullFace = true;
        status->depthTest = true;

        auto properties = blankMaterial->getProperties();

        properties->ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        properties->emission = {0.2f, 0.2f, 0.2f, 1.0f};
        properties->diffuse = {1.0f, 1.0f, 1.0f, 1.0f};

        materials["blank"] = std::move(blankMaterial);

        return materials;
    }

    xe::sg::ScenePtr Application::createScene() {
        xe::sg::Renderable* lookAtCamera = m_renderables["lookAtCamera"].get();
        xe::sg::Renderable* triangleMesh = m_renderables["triangleMesh"].get();

        assert(lookAtCamera);
        assert(triangleMesh);

        auto scene = std::make_unique<xe::sg::Scene>();

        scene
            ->setBackColor({0.2f, 0.3f, 0.8f, 1.0f})
            ->getNode()->setRenderable(lookAtCamera)
                ->createNode()->setRenderable(triangleMesh);

        return scene;
    }
}

int main(int argc, char **argv) {
    return demo::Application().run();
}
