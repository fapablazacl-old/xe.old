
#include "PhongPipeline.hpp"

#include "Renderable.hpp"
#include "Renderer.hpp"

#include "CameraRenderer.hpp"
#include "MeshRenderer.hpp"
#include "PhongLightRenderer.hpp"

namespace xe { namespace sg {

    extern const std::string vertexShader;

    extern const std::string fragmentShader;

    PhongPipeline::PhongPipeline(xe::gfx::Device *device) 
        : m_device(device), m_projViewModel(xe::Matrix4f::makeIdentity()) {

        assert(device);

        m_program = device->createProgram({
            {xe::gfx::ShaderType::Vertex, vertexShader}, 
            {xe::gfx::ShaderType::Fragment, fragmentShader}
        });

        m_renderersStorage.emplace_back(new CameraRenderer(this));
        m_renderersStorage.emplace_back(new MeshRenderer(m_device));
        m_renderersStorage.emplace_back(new PhongLightRenderer(m_device));

        assert(m_program);
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

    void PhongPipeline::setTransformation(const xe::Matrix4f &transformation) {
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

        auto rendererIt = m_renderers.find(std::type_index(typeid(renderable)));

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

    const std::string vertexShader = R"(
#version 330

uniform mat4x4 mat_projViewModel;

attribute vec3 v_coord;
attribute vec3 v_normal;
//attribute vec2 v_texcoord;

out vec3 p_normal;
out vec2 p_texcoord;

void main() {
    gl_Position = mat_projViewModel * v_coord;
    p_texcoord = v_texcoord;
}

)";

    const std::string fragmentShader = R"(
#version 330

// vertex data
in vec3 p_normal;
//in vec2 p_texcoord;

out vec4 p_color;

// material data
uniform vec4 m_ambient;
uniform vec4 m_diffuse;
uniform vec4 m_specular;
uniform float m_shininess;

// light data
const int LT_POINT = 0;
const int LT_DIRECTIONAL = 1;

uniform int l_type;
uniform vec3 l_position;
uniform vec3 l_direction;
uniform vec4 l_ambient;
uniform vec4 l_diffuse;
uniform vec4 l_specular;

void main() {
    p_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";

}}
