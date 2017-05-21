
#include "DemoApp.hpp"
#include "Resources.hpp"
#include "system/CameraEntity.hpp"
#include "system/MessageBus.hpp"
#include "system/MoveMessage.hpp"
#include "system/InputSystem.hpp"
#include "system/MessageHandler.hpp"
#include "util/FrameTimer.hpp"
#include "render/PhongPipeline.hpp"

#include <xe/Common.hpp>
#include <xe/io/Archive.hpp>
#include <xe/PluginManager.hpp>
#include <xe/math/Matrix.hpp>
#include <xe/input/InputCode.hpp>
#include <xe/input/InputStatus.hpp>
#include <xe/gfx/GraphicsDeviceInfo.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/sg/GenericSceneManager.hpp>
#include <fstream>
#include <iostream>

namespace demo {

    struct DemoApp::Private {
    public:
        DemoApp *m_app = nullptr;

        std::unique_ptr<xe::GraphicsDevice> m_device;

        xe::SceneNode *m_rootNode = nullptr;
        xe::SceneNode *m_meshNode = nullptr;
        //float m_angle = 0.0f;

        std::unique_ptr<xe::PhongPipeline> m_pipeline;
        std::unique_ptr<xe::SceneManager> m_sceneManager;

        std::unique_ptr<Resources> m_resources;

        demo::CameraEntity *m_cameraEntity = nullptr;

        std::vector<std::unique_ptr<Entity>> m_entities;
        std::unique_ptr<MessageBus> m_messageBus;

        std::vector<std::unique_ptr<System>> m_systems;

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
            m_pipeline = std::make_unique<xe::PhongPipeline>(m_device.get());
            m_resources = std::make_unique<Resources>(m_pipeline.get(), m_device.get(), m_app->getGraphicsManager());
            m_sceneManager = std::make_unique<xe::GenericSceneManager>();

            auto scene  = m_resources->getScene();

            m_meshNode = scene->createNode();

            auto camera = static_cast<xe::LookAtPerspectiveCamera*>(m_resources->getRenderable("lookAtCamera"));
            
            m_cameraEntity = new CameraEntity(camera, 0.1f, 1.5f, 1.5f);

            m_entities.emplace_back(m_cameraEntity);

            m_messageBus = std::make_unique<MessageBus>();

            m_systems.emplace_back(new InputSystem(m_messageBus.get(), m_device->getInputManager(), m_cameraEntity));

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
            
            xe::FrameTimer timer;

            float angle = 0.0f;

            float seconds = timer.getSeconds();

            while(true) {
                inputManager->poll();

                // get timing for current frame
                seconds = timer.getSeconds();

                // compute rotation angle
                angle += 60.0f * seconds;

                if (angle > 360.0f) {
                    angle = 0.0f;
                }

                // update all entities
                this->updateAll(seconds);

                /*
                const float rad_angle = xe::rad(angle);

                const auto rotationX = xe::Matrix4f::makeRotateX(rad_angle);
                const auto rotationY = xe::Matrix4f::makeRotateY(rad_angle);
                const auto rotationZ = xe::Matrix4f::makeRotateZ(rad_angle);
                m_meshNode->set(rotationX * rotationY * rotationZ);
                */
                
                m_device->beginFrame();
                m_sceneManager->renderAll(m_resources->getScene()->getRoot());
                m_device->endFrame();
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
        this->getPluginManager()->load("xe.gfx.png");
        this->getPluginManager()->load("xe.gfx.gl3");
    }

    DemoApp::~DemoApp() {}
}

int main(int argc, char **argv) {
    return demo::DemoApp().run();
}
