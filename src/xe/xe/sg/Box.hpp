
#pragma once

#ifndef __xe_sg_box_hpp__
#define __xe_sg_box_hpp__

#include <xe/Boundary.hpp>

namespace xe {
    template<typename OtherSolid>
    xe::Boxf box(const OtherSolid &solid);
    
    xe::Boxf box(const xe::Boxf &solid);

    template<typename OtherSolid>
    inline xe::Boxf box(const OtherSolid &solid) {
        return xe::Boxf();
    }
    
    inline xe::Boxf box(const xe::Boxf &solid) {
        return solid;
    }
}

#endif  
