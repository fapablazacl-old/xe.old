
#pragma once 

#ifndef __xe_sg_renderable_hpp__
#define __xe_sg_renderable_hpp__

#include <xe/PreDef.hpp>
#include <xe/math/Box.hpp>

namespace xe {

    enum RenderableOutcome {
        None, 
        Graphic, 
        Sound,
    };

    /**
     * @brief Get a description
     */
    struct RenderableInfo {
        //! The outcome after render
        RenderableOutcome outcome;

        //! The relative bounding box of the renderable
        Boxf box;   
    };

    /**
     * @brief A Renderable changes the multimedia state when it is rendered.
     */
    class XE_API Renderable {
    public:
        virtual ~Renderable();

        /**
         * @brief Get the information of the renderable
         */
        virtual RenderableInfo getInfo() = 0;

        /**
         * @brief Render the renderable
         */
        virtual void render() = 0;
    };
}

#endif 
