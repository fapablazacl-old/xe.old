
#include <memory>
#include <xe/Core.hpp>
#include <xe/PluginManager.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/math/Vector.hpp>

namespace triangle {

    struct Vertex {
        xe::Vector3f coord;
        xe::Vector4f color;
    };

    class Application : public xe::Core {
    public:
        Application() {
            this->getPluginManager()->load("xe.gfx.gl3");

            // create a device
            m_device = this->getGraphicsManager()->createDevice();

            // setup a vertex format 
            m_subsetFormat = {
                {0, xe::DataType::Float32, 3, "v_coord"}, 
                {0, xe::DataType::Float32, 4, "v_color"}
            };

            // setup a shader program 
            m_program = m_device->createProgram({
                { 
                    xe::ShaderType::Vertex, R"(
#version 330

attribute vec3 v_coord;
attribute vec4 v_color;

out vec4 p_color;

void main() {
    gl_Position = vec4(v_coord, 1.0);
    p_color = v_color;
}
                    )"
                }, 
                {
                    xe::ShaderType::Fragment, R"(
#version 330

in vec4 p_color;

out vec4 f_color;

void main() {
    f_color = p_color;
}
                    )"
                }
            });

            // create the triangle geometry 
            std::vector<Vertex> vertices = {
                {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}, 
                {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}}, 
                {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
            };

            
        }

        ~Application() {}

    private:
        xe::GraphicsDevicePtr m_device;
        xe::SubsetFormat m_subsetFormat;
        xe::ProgramPtr m_program;
        xe::SubsetPtr m_triangleSubset;
    };
}

int main(int argc, char **argv) {

    return 0;
}
