
#pragma once

#include <vector>

#include "xe/Flags.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Vector.hpp"
#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/Texture.hpp"

namespace xe { namespace gfx {

    enum class TextureFilter {
        Linear,
        Nearest
    };
    
    enum class TextureWrap {
        Clamp,
        Repeat
    };
    
    struct MaterialLayer {
        Texture *texture = nullptr;

        TextureFilter magFilter = TextureFilter::Linear;
        TextureFilter minFilter = TextureFilter::Linear;
        
        TextureWrap xWrap = TextureWrap::Repeat;
        TextureWrap yWrap = TextureWrap::Repeat;
        TextureWrap zWrap = TextureWrap::Repeat;
        TextureWrap wWrap = TextureWrap::Repeat;

        MaterialLayer() {}
        explicit MaterialLayer(Texture *texture_) : texture(texture_) {}
    };
    
    /**
     * @brief Material device status
     */
    struct MaterialStatus {
        bool cullFace = false;
        bool depthTest = false;
        bool blending = false;
    };

    /** 
     * @brief Material base class.
     */
    class Material {
    public:
        Material() {}

        virtual ~Material() {}

        const MaterialStatus* getStatus() const {
            return &m_status;
        }

        MaterialStatus* getStatus() {
            return &m_status;
        }

        std::size_t getLayerCount() const {
            return m_layers.size();
        }

        MaterialLayer* getLayer(const std::size_t index) {
            return &m_layers[index];
        }

        const MaterialLayer* getLayer(const std::size_t index) const {
            return &m_layers[index];
        }

        virtual void render(xe::gfx::Device *device) = 0;

    private:
        std::vector<MaterialLayer> m_layers;
        MaterialStatus m_status;
    };

    typedef std::unique_ptr<Material> MaterialPtr; 
}} 
