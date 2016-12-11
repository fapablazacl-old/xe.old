
#include "Application.hpp"

#include "Camera.hpp"
#include "PhongMaterial.hpp"
#include "PhongPipeline.hpp"
#include "Mesh.hpp"

namespace demo {

    const float pi = 3.14159265358979f;

    /**
     * @brief Generate a sphere
     */
    static std::vector<xe::Vector3f> gensphere(const float radius, const std::size_t slices, const std::size_t stacks) {
        assert(slices >= 3);
        assert(stacks >= 3);

        float angle = 0.0f;

        const float slices_delta = 2.0f * pi / slices;
        const float stacks_delta = pi / stacks;

        const xe::Vector3f slices_axis = {0.0f, 1.0f, 0.0f};
        const xe::Vector3f stacks_axis = {1.0f, 0.0f, 0.0f};
        
        const xe::Vector3f point = {0.0f, radius, 0.0f};

        float slices_angle = slices_delta;
        float stacks_angle = stacks_delta;

        std::vector<xe::Vector3f> points;

        points.reserve((stacks - 1) * slices + 2);

        points.push_back(point);

        for (std::size_t i=0; i<stacks - 1; i++) {
            for (std::size_t j=0; j<slices; j++) {
                const auto mstacks = xe::Matrix4f::makeRotate(stacks_angle, stacks_axis);
                const auto mslices = xe::Matrix4f::makeRotate(slices_angle, slices_axis);

                points.push_back(xe::transform(mslices * mstacks, point));

                slices_angle += slices_delta;
            }

            slices_angle = slices_delta;
            stacks_angle += stacks_delta;
        }

        points.push_back(-point);

        return points;
    }

    static std::vector<std::uint32_t> gensphereindices(const std::size_t slices, const std::size_t stacks) {
        struct Grid {
            std::uint32_t base;
            std::uint32_t rows;
            std::uint32_t cols;

            std::uint32_t index(const std::uint32_t i, const std::uint32_t j) const {
                assert(i >= 0);
                assert(i < rows);
                assert(j >= 0);
                assert(j < cols);

                return base + i*cols + j;
            }
        };

        std::vector<std::uint32_t> indices;

        // top indices
        for (std::uint32_t i=1; i<slices; i++) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i);
        }

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back((std::uint32_t)slices);

        // body indices
        Grid grid = {1, (std::uint32_t)stacks, (std::uint32_t)slices};

        for (std::uint32_t i=0; i<stacks - 2; i++) {
            std::uint32_t i0, i1, i2, i3;

            for (std::uint32_t j=0; j<slices; j++) {
                if (j < slices - 1) {
                    i0 = grid.index(i + 0, j + 0);
                    i1 = grid.index(i + 0, j + 1);
                    i2 = grid.index(i + 1, j + 0);
                    i3 = grid.index(i + 1, j + 1);

                } else {
                    i0 = grid.index(i + 0, (std::uint32_t)slices - 1);
                    i1 = grid.index(i + 0, 0);
                    i2 = grid.index(i + 1, (std::uint32_t)slices - 1);
                    i3 = grid.index(i + 1, 0);
                }

                // first triangle
                indices.push_back(i0);
                indices.push_back(i1);
                indices.push_back(i2);

                // second triangle
                indices.push_back(i1);
                indices.push_back(i3);
                indices.push_back(i2);
            }
        }

        // bottom indices
        std::uint32_t lastPoint = ((std::uint32_t)stacks - 1) * (std::uint32_t)slices + 2 - 1;    // compute sphere point count

        for (std::uint32_t i=1; i<slices; i++) {
            indices.push_back(lastPoint);
            indices.push_back(lastPoint - (i + 1));
            indices.push_back(lastPoint + i);
        }

        indices.push_back(lastPoint);
        indices.push_back(lastPoint - 1);
        indices.push_back(lastPoint - (std::uint32_t)slices);

        return indices;
    }

    /**
     * @brief Generate the normal for any ellipsoid object (including spheres)
     */
    static std::vector<xe::Vector3f> genellipsoidnormals(const std::vector<xe::Vector3f> &coords) {
        std::vector<xe::Vector3f> normals;

        normals.resize(coords.size());

        for (std::size_t i=0; i<coords.size(); i++) {
            normals[i] = xe::normalize(coords[i]);
        }

        return normals;
    }
    
    /**
     * @brief Generate the normal
     */
    static std::vector<xe::Vector3f> gennormals(const std::vector<xe::Vector3f> &coords) {
        assert(coords.size()%3 == 0);

        std::vector<xe::Vector3f> normals;

        normals.resize(coords.size());

        for (std::size_t i=0; i<coords.size(); i+=3) {
            const xe::Vector3f v1 = coords[i + 1] - coords[i + 0];
            const xe::Vector3f v2 = coords[i + 2] - coords[i + 0];
            const xe::Vector3f normal = xe::normalize(xe::cross(v1, v2));

            normals[i + 0] = normal;
            normals[i + 1] = normal;
            normals[i + 2] = normal;
        }

        return normals;
    }

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
        std::vector<xe::Vector3f> coords = gensphere(1.0f, 16, 16);
        std::vector<xe::Vector3f> normals = genellipsoidnormals(coords);
        std::vector<std::uint32_t> indices = gensphereindices(16, 16);

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

        materials["blank"] = std::make_unique<PhongMaterial>();

        return materials;
    }

    xe::sg::ScenePtr Application::createScene() {
        xe::sg::Renderable* lookAtCamera = m_renderables["lookAtCamera"].get();
        xe::sg::Renderable* triangleMesh = m_renderables["triangleMesh"].get();

        assert(lookAtCamera);
        assert(triangleMesh);

        auto scene = std::make_unique<xe::sg::Scene>();

        scene
            ->setBackColor({0.2f, 0.2f, 0.8f, 1.0f})
            ->getNode()->setRenderable(lookAtCamera)
                ->createNode()->setRenderable(triangleMesh);

        return scene;
    }
}

int main(int argc, char **argv) {
    return demo::Application().run();
}
