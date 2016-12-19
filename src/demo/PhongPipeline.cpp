
#include "PhongPipeline.hpp"

#include "Renderable.hpp"
#include "Renderer.hpp"

#include "Camera.hpp"
#include "Mesh.hpp"
#include "PhongLight.hpp"

#include "CameraRenderer.hpp"
#include "MeshRenderer.hpp"
#include "PhongLightRenderer.hpp"

#include <xe/FileUtil.hpp>

namespace xe { namespace sg {
    
    PhongPipeline::PhongPipeline(xe::gfx::Device *device) 
        : m_device(device) {
        
        assert(device);
        
        m_program = device->createProgram({
            {xe::gfx::ShaderType::Vertex, FileUtil::load("assets/shaders/Phong.vert.glsl")}, 
            {xe::gfx::ShaderType::Fragment, FileUtil::load("assets/shaders/Phong.frag.glsl")}
        });
        
        assert(m_program);
        
        m_renderersStorage.emplace_back(new CameraRenderer(this));
        m_renderersStorage.emplace_back(new MeshRenderer(m_device));
        m_renderersStorage.emplace_back(new PhongLightRenderer(m_device));
        
        this->registerRenderer(std::type_index(typeid(xe::sg::Camera)), m_renderersStorage[0].get());
        this->registerRenderer(std::type_index(typeid(xe::sg::Mesh)), m_renderersStorage[1].get());
        this->registerRenderer(std::type_index(typeid(xe::sg::PhongLight)), m_renderersStorage[2].get());
    }

    PhongPipeline::~PhongPipeline() {}

    xe::Matrix4f PhongPipeline::getTransformation() const {
        return m_projViewModel;
    }
    
    void PhongPipeline::syncModelViewProj() {
        assert(m_device);
        assert(m_program);
        assert(m_device->getProgram() == m_program.get());

        m_projViewModel = m_proj * m_view * m_model;

        int location = m_program->getUniform("mat_projViewModel");

        m_device->setUniformMatrix(location, 1, false, m_projViewModel.getPtr());
    }

    void PhongPipeline::setModelMatrix(const xe::Matrix4f &transformation) {
        assert(m_device);
        assert(m_program);
        assert(m_device->getProgram() == m_program.get());

        m_model = transformation;

        this->syncModelViewProj();
    }

    void PhongPipeline::setProjMatrix(const xe::Matrix4f &proj) {
        assert(m_device);
        assert(m_program);
        assert(m_device->getProgram() == m_program.get());

        m_proj = proj;

        this->syncModelViewProj();
    }

    void PhongPipeline::setViewMatrix(const xe::Matrix4f &view) {
        assert(m_device);
        assert(m_program);
        assert(m_device->getProgram() == m_program.get());

        m_view = view;

        this->syncModelViewProj();
    }

    void PhongPipeline::beginFrame(const xe::Vector4f &clearColor) {
        assert(m_device);
        assert(m_program);
        assert(!m_frame);

        m_frame = true;

        m_device->setProgram(m_program.get());
        m_device->beginFrame(xe::gfx::ClearFlags::All, xe::gfx::ClearParams(clearColor));
    }

    void PhongPipeline::render(Renderable *renderable) {
        assert(m_device);
        assert(m_program);
        assert(renderable);
        assert(m_frame);

        auto rendererIt = m_renderers.find(renderable->getTypeIndex());

        assert(rendererIt != m_renderers.end());

        rendererIt->second->render(renderable);
    }

    void PhongPipeline::endFrame() {
        assert(m_device);
        assert(m_program);
        assert(m_frame);

        m_frame = false;
        m_device->endFrame();
    }

    void PhongPipeline::registerRenderer(const std::type_index &renderableType, Renderer *renderer) {
        assert(renderer);
        assert(m_renderers.find(renderableType) == m_renderers.end());

        m_renderers.insert({renderableType, renderer});
    }

    void PhongPipeline::unregisterRenderer(const std::type_index &renderableType, Renderer *renderer) {
        assert(renderer);
        assert(m_renderers.find(renderableType) != m_renderers.end());

        m_renderers.erase(m_renderers.find(renderableType));
    }
}}
