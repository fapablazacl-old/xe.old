
#pragma once 

#ifndef __xe_sfx_soundmanager_hpp__
#define __xe_sfx_soundmanager_hpp__

#include <vector>
#include <memory>
#include <xe/PreDef.hpp>

namespace xe {

    class SoundDevice;
    class SoundDeviceInfo;

    class XE_API SoundManager {
    public:
        virtual ~SoundManager();

        virtual std::vector<SoundDeviceInfo> enumerateDevices() const = 0;

        virtual std::unique_ptr<SoundDevice> createDevice() = 0;
    };
}

#endif
