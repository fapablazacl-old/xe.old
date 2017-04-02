
#include "PhongPipeline.hpp"

#include "Camera.hpp"
#include "Mesh.hpp"
#include "PhongLight.hpp"

#include <xe/sg/Renderable.hpp>

#include <xe/io/FileUtil.hpp>

namespace xe { 
    PhongPipeline::PhongPipeline(xe::GraphicsDevice *device) 
        : m_device(device) {
        
        assert(device);
        
        m_program = device->createProgram({
            {xe::ShaderType::Vertex, FileUtil::load("assets/shaders/Phong.vert.glsl")}, 
            {xe::ShaderType::Fragment, FileUtil::load("assets/shaders/Phong.frag.glsl")}
        });
        
        assert(m_program);
    }

    PhongPipeline::~PhongPipeline() {}

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

    void PhongPipeline::endFrame() {
        assert(m_device);
        assert(m_program);
        assert(m_frame);

        m_frame = false;
        m_device->endFrame();
    }
}
