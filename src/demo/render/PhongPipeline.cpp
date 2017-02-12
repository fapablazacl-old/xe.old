
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

namespace xe { 
    PhongPipeline::PhongPipeline(xe::GraphicsDevice *device) 
        : m_device(device) {
        
        assert(device);
        
        m_program = device->createProgram({
            {xe::ShaderType::Vertex, FileUtil::load("assets/shaders/Phong.vert.glsl")}, 
            {xe::ShaderType::Fragment, FileUtil::load("assets/shaders/Phong.frag.glsl")}
        });
        
        assert(m_program);
        
        m_renderersStorage.emplace_back(new CameraRenderer(this));
        m_renderersStorage.emplace_back(new MeshRenderer(m_device));
        m_renderersStorage.emplace_back(new PhongLightRenderer(m_device));
        
        this->registerRenderer(std::type_index(typeid(Camera)), m_renderersStorage[0].get());
        this->registerRenderer(std::type_index(typeid(Mesh)), m_renderersStorage[1].get());
        this->registerRenderer(std::type_index(typeid(PhongLight)), m_renderersStorage[2].get());
    }

    PhongPipeline::~PhongPipeline() {}

    xe::Matrix4f PhongPipeline::getProjViewModel() const {
        return m_mvpTransform;
    }

    xe::Matrix4f PhongPipeline::getTransform(const TransformType transformType) const {
        return m_transforms[(int)transformType];
    }

    void PhongPipeline::syncModelViewProj() {
        assert(m_device);
        assert(m_program);
        assert(m_device->getProgram() == m_program.get());

        m_mvpTransform = this->getTransform(TransformType::Proj) * 
                        this->getTransform(TransformType::View) * 
                        this->getTransform(TransformType::Model);

        int location = m_program->getUniform("mat_projViewModel");

        m_device->setUniformMatrix(location, 1, false, m_mvpTransform.getPtr());
    }

    void PhongPipeline::setTransform(const TransformType transformType, const xe::Matrix4f &transform) {
        assert(m_device);
        assert(m_program);
        assert(m_device->getProgram() == m_program.get());

        m_transforms[(int)transformType] = transform;

        this->syncModelViewProj();
    }

    void PhongPipeline::beginFrame() {
        assert(m_device);
        assert(m_program);
        assert(!m_frame);

        m_frame = true;

        m_device->setProgram(m_program.get());
        m_device->beginFrame(xe::ClearFlags::All, xe::ClearParams());
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
}
