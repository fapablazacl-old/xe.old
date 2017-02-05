
#include "Application.hpp"

#include "render/Camera.hpp"
#include "render/PhongMaterial.hpp"
#include "render/PhongPipeline.hpp"
#include "render/PhongLight.hpp"
#include "render/Mesh.hpp"

#include <fstream>

#include <xe/IosStream.hpp>
#include <xe/FileStream.hpp>
#include <xe/gfx/Image.hpp>
#include <xe/sg/Generator.hpp>
#include <xe/sg/SphereGenerator.hpp>
#include <xe/sg/PlaneGenerator.hpp>

namespace demo {
    int Application::run() {
        using xe::isPressed;
        using xe::KeyCode;

        m_device = this->createDevice();
        m_meshFormat = this->createMeshFormat();

        m_pipeline = std::make_unique<xe::PhongPipeline>(m_device.get());
        m_sceneRenderer = std::make_unique<xe::SceneRenderer>(m_pipeline.get());

        m_textures = this->createTextures();
        
        m_materials = this->createMaterials();
        m_renderables = this->createRenderables();
        m_scene = this->createScene();

        m_meshNode = m_scene->getNode()->getNode(1);
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
        this->getPluginManager()->load("xe.gfx.fi");
        this->getPluginManager()->load("xe.gfx.gl3");
        //this->getPluginManager()->load("xe.gfx.gles2");
        //this->getPluginManager()->load("xe.gfx.d3d10");

        m_archive = xe::Archive::create("assets/");
    }

    Application::~Application() {}

    xe::GraphicsDevicePtr Application::createDevice() {
        auto deviceInfos = this->getGraphicsManager()->enumerateDevices();

        std::cout << "Available graphics devices:" << std::endl;

        for (const xe::GraphicsDeviceInfo &deviceInfo : deviceInfos) {
            std::cout << deviceInfo << std::endl;
        }

        return this->getGraphicsManager()->createDevice();
    }

    xe::MeshFormatPtr Application::createMeshFormat() {
        auto meshFormat = new xe::SubsetFormat {
            {0, xe::DataType::Float32, 3, "v_coord"},
            {1, xe::DataType::Float32, 3, "v_normal"},
            {2, xe::DataType::Float32, 2, "v_texcoord"}
        };

        return xe::MeshFormatPtr(meshFormat);
    }

    xe::RenderablePtr Application::createSphereRenderable() {
        xe::SphereGenerator sphereGenerator(64, 64);

        std::vector<xe::Vector3f> coords = sphereGenerator.genCoords(0.75f);
        
        std::vector<std::uint32_t> indices = sphereGenerator.genIndices();
        std::vector<xe::Vector3f> normals = sphereGenerator.genNormals(coords);
        std::vector<xe::Vector2f> texcoords = sphereGenerator.genTexCoords(normals);

        xe::SubsetDesc subsetDesc = {
            m_meshFormat.get(), 
            {{coords}, {normals}, {texcoords}}, 
            xe::DataType::UInt32, 
            {indices}
        };

        auto subset = m_device->createSubset(subsetDesc);
        auto mesh = std::make_unique<xe::Mesh>(std::move(subset));

        mesh->getEnvelope(0)->material = m_materials["custom"].get();
        mesh->getEnvelope(0)->primitive = xe::Primitive::TriangleList;
        mesh->getEnvelope(0)->count = indices.size();

        return std::move(mesh);
    }

    xe::RenderablePtr Application::createPlaneRenderable() {
        xe::Generator generator;
        xe::PlaneGenerator planeGenerator;
        
        planeGenerator.slices = 5;
        planeGenerator.stacks = 5;

        const xe::Plane plane({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
        
        std::vector<xe::Vector3f> coords = planeGenerator.genCoords(plane, 5.0f, 5.0f);
        std::vector<std::uint32_t> indices = planeGenerator.genIndices();
        std::vector<xe::Vector3f> normals = generator.genNormals(coords, indices);
        std::vector<xe::Vector2f> texcoords = planeGenerator.genTexCoords();
        
        xe::SubsetDesc subsetDesc = {
            m_meshFormat.get(), 
            {{coords}, {normals}, {texcoords}}, 
            xe::DataType::UInt32, 
            {indices}
        };
        
        auto subset = m_device->createSubset(subsetDesc);
        auto mesh = std::make_unique<xe::Mesh>(std::move(subset));

        mesh->getEnvelope(0)->material = m_materials["custom"].get();
        mesh->getEnvelope(0)->primitive = xe::Primitive::TriangleList;
        mesh->getEnvelope(0)->count = indices.size();

        return std::move(mesh);
    }
    
    xe::RenderablePtr Application::createLightRenderable() {
        auto light = std::make_unique<xe::PhongLight>();

        return std::move(light);
    }
    
    std::map<std::string, xe::RenderablePtr> Application::createRenderables() {
        std::map<std::string, xe::RenderablePtr> renderables;

        // create a basic camera 
        renderables["lookAtCamera"] = std::make_unique<xe::LookAtPerspectiveCamera>();
        renderables["sphereMesh"] = this->createSphereRenderable();
        renderables["planeMesh"] = this->createPlaneRenderable();
        renderables["light"] = this->createLightRenderable();

        return renderables;
    }

    xe::TexturePtr Application::createTexture(const std::string &file) {
        assert(m_device);
        assert(file.size() > 0);
        
        auto stream = m_archive->open(file);

        xe::ImagePtr image = this->getGraphicsManager()->createImage(stream.get());
        assert(image);
        
        const xe::ImageDesc imageDesc = image->getDesc();
        
        assert(imageDesc.format != xe::PixelFormat::Unknown);
        
        xe::TextureDesc desc;
        desc.type = xe::TextureType::Tex2D;
        desc.format = xe::PixelFormat::RGB_8;
        desc.width = imageDesc.width;
        desc.height = imageDesc.height;
        
        return m_device->createTexture(desc, imageDesc.format, xe::getDataType(imageDesc.format), image->getPointer());
    }
    
    std::map<std::string, xe::TexturePtr> Application::createTextures() {
        std::map<std::string, xe::TexturePtr> textures;
        
        std::cout << "Loading texture 'rusted/rusted_plates_albedo.tif'" << std::endl;
        textures["rusted_plates_albedo"] = this->createTexture("materials/rusted/rusted_plates_albedo.tif");
        
        std::cout << "Loading texture 'materials/rusted/rusted_plates_diffuse.tif'" << std::endl;
        textures["rusted_plates_diffuse"] = this->createTexture("materials/rusted/rusted_plates_diffuse.tif");
        
        std::cout << "Loading texture 'materials/rusted/rusted_plates_heightmap.tif'" << std::endl;
        textures["rusted_plates_heightmap"] = this->createTexture("materials/rusted/rusted_plates_heightmap.tif");
        
        std::cout << "Loading texture 'materials/rusted/rusted_plates_normalmap.tif'" << std::endl;
        textures["rusted_plates_normalmap"] = this->createTexture("materials/rusted/rusted_plates_normalmap.tif");
        
        return textures;
    }

    xe::MaterialPtr Application::createCustomMaterial() {
        auto material = std::make_unique<PhongMaterial>();
        
        material->getLayer(0)->texture = m_textures["rusted_plates_diffuse"].get();
        
        material->getStatus()->cullFace = false;
        material->getStatus()->depthTest = true;
        material->getProperties()->diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        
        return material;
    }
    
    xe::MaterialPtr Application::createBlankMaterial() {
        auto blankMaterial = std::make_unique<PhongMaterial>();
        
        auto status = blankMaterial->getStatus();
        status->cullFace = true;
        status->depthTest = true;
        
        auto properties = blankMaterial->getProperties();
        properties->ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        properties->emission = {0.2f, 0.2f, 0.2f, 1.0f};
        properties->diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        
        return blankMaterial;
    }
    
    std::map<std::string, xe::MaterialPtr> Application::createMaterials() {
        std::map<std::string, xe::MaterialPtr> materials;

        materials["blank"] = this->createBlankMaterial();
        materials["custom"] = this->createCustomMaterial();
        
        return materials;
    }
    
    xe::ScenePtr Application::createScene() {
        xe::Renderable* lookAtCamera = m_renderables["lookAtCamera"].get();
        xe::Renderable* sphereMesh = m_renderables["sphereMesh"].get();
        xe::Renderable* planeMesh = m_renderables["planeMesh"].get();
        xe::Renderable* light = m_renderables["light"].get();

        assert(lookAtCamera);
        assert(sphereMesh);
        assert(planeMesh);

        auto scene = std::make_unique<xe::Scene>();

        scene
            ->setBackColor({0.2f, 0.3f, 0.8f, 1.0f})
            ->getNode()->setRenderable(lookAtCamera);

        scene->getNode()->createNode()->setRenderable(light);

        scene->getNode()->createNode()->setRenderable(sphereMesh);
        scene->getNode()->createNode()->setRenderable(planeMesh)->setMatrix(xe::Matrix4f::makeTranslate({0.0f, -1.0f, 0.0f, 1.0f}));
        
        return scene;
    }
}

int main(int argc, char **argv) {
    return demo::Application().run();
}
