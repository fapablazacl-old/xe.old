
#pragma once 

#ifndef  __xe_sfx_sourcedesc_hpp__
#define  __xe_sfx_sourcedesc_hpp__

#include <xe/Vector.hpp>

namespace xe {

    class Buffer;

    enum class SourceType {
        Undetermined, 
        Static, 
        Streaming
    };

    enum class SourceState {
        Stopped, 
        Playing
    };

    struct SourceData {
        float pitch;
        float gain;
        float maxDistance;
        float rolloffFactor;
        float referenceDistance;
        float minGain;
        float maxGain;
        float coneOuterGain;
        float coneInnerAngle;
        float coneOuterAngle;

        xe::Vector3f position;
        xe::Vector3f velocity;
        xe::Vector3f direction;

        bool relative;

        SourceType type;

        bool looping;
        Buffer *buffer;

        SourceState state;
        int buffersQueued;
        int buffersProcessed;

        int offsetInSeconds;
        int offsetInSamples;
        int offsetInBytes;
    };
}

#endif 
