
#pragma once 

#ifndef __xe_sfx_listener_hpp__
#define __xe_sfx_listener_hpp__

#include <xe/PreDef.hpp>
#include <xe/Vector.hpp>

namespace xe {
    class XE_API Listener {
    public:
        virtual ~Listener();

        virtual void setPosition(const Vector3f &value) = 0;

        virtual void setVelocity(const Vector3f &value) = 0;

        virtual void setLookAt(const Vector3f &value) = 0;

        virtual void setUp(const Vector3f &value) = 0;

        virtual Vector3f getPosition() const = 0;

        virtual Vector3f getVelocity() const = 0;

        virtual Vector3f getLookAt() const = 0;

        virtual Vector3f getUp() const = 0;
    };
}

#endif
