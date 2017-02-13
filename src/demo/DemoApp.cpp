
#include "DemoApp.hpp"

#include "CameraEntity.hpp"
#include "MessageBus.hpp"
#include "MoveMessage.hpp"
#include "render/PhongPipeline.hpp"

#include <xe/Common.hpp>
#include <xe/Matrix.hpp>
#include <xe/PluginManager.hpp>
#include <xe/input/InputCode.hpp>
#include <xe/input/InputStatus.hpp>
#include <xe/gfx/GraphicsDeviceInfo.hpp>
#include <fstream>
#include <iostream>

namespace demo {

    struct DemoApp::Private {
    public:
        DemoApp *m_app = nullptr;

        std::unique_ptr<xe::GraphicsDevice> m_device;

        xe::SceneNode *m_meshNode = nullptr;
        //float m_angle = 0.0f;

        std::unique_ptr<xe::Pipeline> m_pipeline;
        std::unique_ptr<xe::SceneRenderer> m_sceneRenderer;

        std::unique_ptr<Resources> m_resources;

        demo::CameraEntity *m_cameraEntity = nullptr;

        std::vector<std::unique_ptr<Entity>> m_entities;

        std::unique_ptr<MessageBus> m_messageBus;

    public:
        Private(DemoApp *app) : m_app(app) {}

        std::unique_ptr<xe::GraphicsDevice> createDevice() {
            xe::GraphicsManager *manager = m_app->getGraphicsManager();

            auto deviceInfos = manager->enumerateDevices();

            std::cout << "Available graphics devices:" << std::endl;

            for (const xe::GraphicsDeviceInfo &deviceInfo : deviceInfos) {
                std::cout << deviceInfo << std::endl;
            }

            return manager->createDevice();
        }

        bool initialize() {
            m_device = this->createDevice();
            m_resources = std::make_unique<Resources>(m_device.get(), m_app->getGraphicsManager());
            m_pipeline = std::make_unique<xe::PhongPipeline>(m_device.get());
            m_sceneRenderer = std::make_unique<xe::SceneRenderer>(m_pipeline.get());

            m_meshNode = m_resources->getScene()->getRootNode()->getNode("sphere");

            auto camera = static_cast<xe::LookAtPerspectiveCamera*>(m_resources->getRenderable("lookAtCamera"));
            
            m_cameraEntity = new CameraEntity(camera, 0.1f, 0.5f, 0.5f);

            m_entities.emplace_back(m_cameraEntity);

            m_messageBus = std::make_unique<MessageBus>();

            return true;
        }

        bool doInput(xe::InputManager2 *inputManager) {
            inputManager->poll();

            if (inputManager->getStatus(xe::InputCode::KeyEsc) == xe::InputStatus::Press) {
                return false;
            }

            if (inputManager->getStatus(xe::InputCode::KeyLeft) == xe::InputStatus::Press) {
                m_messageBus->enqueue(std::make_unique<MoveMessage>(nullptr, m_cameraEntity, MoveType::StepLeft));
            }

            if (inputManager->getStatus(xe::InputCode::KeyRight) == xe::InputStatus::Press) {
                m_messageBus->enqueue(std::make_unique<MoveMessage>(nullptr, m_cameraEntity, MoveType::StepRight));
            }

            return true;
        }

        void updateAll(const float seconds) {
            m_messageBus->dispatch();

            for (auto &entity : m_entities) {
                entity->update(seconds);
            }
        }

        void mainLoop() {
            assert(m_meshNode);

            auto inputManager = m_device->getInputManager();
        
            //float angle = 0.0f;
            
            while(true) {
                /*
                angle += 0.3f;

                if (angle > 360.0f) {
                    angle = 0.0f;
                }
                */
                if (!this->doInput(inputManager)) {
                    break;
                }

                this->updateAll(0.02f);

                /*
                const float rad_angle = xe::rad(angle);

                const auto rotationX = xe::Matrix4f::makeRotateX(rad_angle);
                const auto rotationY = xe::Matrix4f::makeRotateY(rad_angle);
                const auto rotationZ = xe::Matrix4f::makeRotateZ(rad_angle);

                m_meshNode->setMatrix(rotationX * rotationY * rotationZ);
                */

                m_sceneRenderer->renderFrame(m_resources->getScene());
            }
        }
    };

    int DemoApp::run() {
        if (!m_impl->initialize()) {
            return 1;
        }

        m_impl->mainLoop();

        return 0;
    }

    DemoApp::DemoApp() : m_impl(new DemoApp::Private(this)) {
        this->getPluginManager()->load("xe.gfx.fi");
        this->getPluginManager()->load("xe.gfx.gl3");
    }

    DemoApp::~DemoApp() {}
}

int main(int argc, char **argv) {
    return demo::DemoApp().run();
}
