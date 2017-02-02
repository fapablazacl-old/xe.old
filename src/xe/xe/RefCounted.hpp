
#pragma once

#ifndef __xe_refcounted_hpp__
#define __xe_refcounted_hpp__

#include <cassert>

namespace xe {
    class RefCounted {
    public:
        RefCounted() {}

        virtual ~RefCounted() {
            assert(m_refCount);
        }

        void addRef() {
            m_refCount++;
        }

        void release() {
            if (--m_refCount == 0) {
                delete this;
            }
        }

    private:
        int m_refCount = 0;
    };
}

#endif
