
#include "Application.hpp"

#include "render/PhongPipeline.hpp"

#include <xe/Common.hpp>
#include <xe/Matrix.hpp>
#include <xe/PluginManager.hpp>
#include <xe/gfx/GraphicsDeviceInfo.hpp>
#include <fstream>
#include <iostream>

namespace demo {
    int Application::run() {
        using xe::isPressed;
        using xe::KeyCode;

        m_device = this->createDevice();
        m_resources = std::make_unique<DemoResources>(m_device.get(), this->getGraphicsManager());
        m_pipeline = std::make_unique<xe::PhongPipeline>(m_device.get());
        m_sceneRenderer = std::make_unique<xe::SceneRenderer>(m_pipeline.get());

        m_meshNode = m_resources->getScene()->getNode()->getNode(1);

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

            const float rad_angle = xe::rad(angle);

            const auto rotationX = xe::Matrix4f::makeRotateX(rad_angle);
            const auto rotationY = xe::Matrix4f::makeRotateY(rad_angle);
            const auto rotationZ = xe::Matrix4f::makeRotateZ(rad_angle);

            m_meshNode->setMatrix(rotationX * rotationY * rotationZ);

            m_sceneRenderer->renderFrame(m_resources->getScene());
        }

        return 0;
    }

    Application::Application() {
        this->getPluginManager()->load("xe.gfx.fi");
        this->getPluginManager()->load("xe.gfx.gl3");
        //this->getPluginManager()->load("xe.gfx.gles2");
        //this->getPluginManager()->load("xe.gfx.d3d10");
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
}

int main(int argc, char **argv) {
    return demo::Application().run();
}
