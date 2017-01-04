
#pragma once

#ifndef __xe_sg_scene_hpp__
#define __xe_sg_scene_hpp__

#include <memory>
#include "xe/Vector.hpp"
#include "xe/sg/SceneNode.hpp"

namespace xe {
    class XE_API Scene {
    public:
        Scene();
        ~Scene();

        const SceneNode* getNode() const;
        
        SceneNode* getNode();

        Vector4f getBackColor() const;

        Scene* setBackColor(const Vector4f &color);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };

    typedef std::unique_ptr<Scene> ScenePtr;
}

#endif
