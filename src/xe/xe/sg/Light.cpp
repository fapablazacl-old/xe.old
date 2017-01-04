
#include "Light.hpp"

#include "xe/sg/Pipeline.hpp"

namespace xe {
    void Light::renderWith(Pipeline *pipeline) {
        pipeline->render(this);
    }
}
