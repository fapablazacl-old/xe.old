
#include "Resources.hpp"

#include "Archive.hpp"

#include "render/Camera.hpp"
#include "render/PhongMaterial.hpp"
#include "render/PhongLight.hpp"
#include "render/Mesh.hpp"

#include <iostream>
#include <map>

#include <xe/IosStream.hpp>
#include <xe/FileStream.hpp>
#include <xe/Matrix.hpp>

#include <xe/gfx/Image.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/gfx/GraphicsDeviceInfo.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/SubsetFormat.hpp>
#include <xe/gfx/GraphicsManager.hpp>

#include <xe/sg/SceneNode.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/Generator.hpp>
#include <xe/sg/SphereGenerator.hpp>
#include <xe/sg/PlaneGenerator.hpp>

namespace demo {

    struct Resources::Private {
    public:
        Private(xe::GraphicsDevice *device, xe::GraphicsManager *manager) 
            : m_device(device), m_manager(manager) {
        
            m_archive = xe::Archive::create("assets/");

            m_meshFormat = this->createMeshFormat();
            m_textures = this->createTextures();
        
            m_materials = this->createMaterials();
            m_renderables = this->createRenderables();
            m_scene = this->createScene();
        }

        xe::GraphicsDevice *m_device = nullptr;
        xe::GraphicsManager *m_manager = nullptr;

        std::map<std::string, std::unique_ptr<xe::Renderable>> m_renderables;
        std::map<std::string, std::unique_ptr<xe::Material>> m_materials;
        std::map<std::string, std::unique_ptr<xe::Texture>> m_textures;
        std::unique_ptr<xe::SubsetFormat> m_meshFormat;
        std::unique_ptr<xe::Scene> m_scene;
        std::unique_ptr<xe::Archive> m_archive;

    public:
        std::unique_ptr<xe::SubsetFormat> createMeshFormat() {
            auto meshFormat = new xe::SubsetFormat {
                {0, xe::DataType::Float32, 3, "v_coord"},
                {1, xe::DataType::Float32, 3, "v_normal"},
                {2, xe::DataType::Float32, 2, "v_texcoord"}
            };

            return std::unique_ptr<xe::SubsetFormat>(meshFormat);
        }

        std::unique_ptr<xe::Renderable> createSphereRenderable() {
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

        std::unique_ptr<xe::Renderable> createPlaneRenderable() {
            xe::Generator generator;
            xe::PlaneGenerator planeGenerator;
        
            planeGenerator.slices = 5;
            planeGenerator.stacks = 5;

            const xe::Plane plane({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
        
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
    
        std::unique_ptr<xe::Renderable> createLightRenderable() {
            auto light = std::make_unique<xe::PhongLight>();

            auto &properties = *light->getProperties();

            properties.direction = xe::normalize(xe::Vector3f(-0.25f, 1.0f, -0.5f));

            return std::move(light);
        }
    
        std::map<std::string, std::unique_ptr<xe::Renderable>> createRenderables() {
            std::map<std::string, std::unique_ptr<xe::Renderable>> renderables;

            // create a basic camera 
            renderables["lookAtCamera"] = std::make_unique<xe::LookAtPerspectiveCamera>();
            renderables["sphereMesh"] = this->createSphereRenderable();
            renderables["planeMesh"] = this->createPlaneRenderable();
            renderables["light"] = this->createLightRenderable();

            return renderables;
        }

        xe::TexturePtr createTexture(const std::string &file) {
            assert(m_device);
            assert(file.size() > 0);
        
            auto stream = m_archive->open(file);

            xe::ImagePtr image = m_manager->createImage(stream.get());
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
    
        std::map<std::string, xe::TexturePtr> createTextures() {
            std::map<std::string, xe::TexturePtr> textures;

            // std::cout << "Loading texture 'rusted/rusted_plates_albedo.tif'" << std::endl;
            textures["rusted_plates_albedo"] = this->createTexture("materials/rusted/rusted_plates_albedo.tif");
        
            // std::cout << "Loading texture 'materials/rusted/rusted_plates_diffuse.tif'" << std::endl;
            textures["rusted_plates_diffuse"] = this->createTexture("materials/rusted/rusted_plates_diffuse.tif");
        
            // std::cout << "Loading texture 'materials/rusted/rusted_plates_heightmap.tif'" << std::endl;
            textures["rusted_plates_heightmap"] = this->createTexture("materials/rusted/rusted_plates_heightmap.tif");
        
            // std::cout << "Loading texture 'materials/rusted/rusted_plates_normalmap.tif'" << std::endl;
            textures["rusted_plates_normalmap"] = this->createTexture("materials/rusted/rusted_plates_normalmap.tif");
        
            return textures;
        }

        xe::MaterialPtr createCustomMaterial() {
            auto material = std::make_unique<PhongMaterial>();
        
            material->getLayer(0)->texture = m_textures["rusted_plates_diffuse"].get();
        
            material->getStatus()->cullFace = false;
            material->getStatus()->depthTest = true;
            material->getProperties()->diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        
            return material;
        }
    
        xe::MaterialPtr createBlankMaterial() {
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
    
        std::map<std::string, xe::MaterialPtr> createMaterials() {
            std::map<std::string, xe::MaterialPtr> materials;

            materials["blank"] = this->createBlankMaterial();
            materials["custom"] = this->createCustomMaterial();
        
            return materials;
        }
    
        std::unique_ptr<xe::Scene> createScene() {
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
                ->getRootNode()->setRenderable(lookAtCamera);

            scene->getRootNode()->createNode("light")->setRenderable(light);

            scene->getRootNode()->createNode("sphere")->setRenderable(sphereMesh);
            scene->getRootNode()->createNode("plane")->setRenderable(planeMesh)->setMatrix(xe::Matrix4f::makeTranslate({0.0f, -1.0f, 0.0f, 1.0f}));
        
            return scene;
        }
    };

    Resources::Resources(xe::GraphicsDevice *device, xe::GraphicsManager *manager) 
        : m_impl(new Resources::Private(device, manager)) {
    }

    Resources::~Resources() {}

    xe::Scene* Resources::getScene() {
        assert(m_impl);

        return m_impl->m_scene.get();
    }

    xe::Renderable* Resources::getRenderable(const std::string &name) {
        assert(m_impl);
        
        return m_impl->m_renderables[name].get();
    }
}
