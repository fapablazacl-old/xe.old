
#include "Model.hpp"

namespace demo {
    Model::~Model() {}

    std::size_t Model::getPartCount() const {
        return m_parts.size();
    }

    ModelPart* Model::getPart(const std::size_t index) {
        return m_parts[index].get();
    }

    const ModelPart* Model::getPart(const std::size_t index) const {
        return m_parts[index].get();
    }

    std::unique_ptr<Model> Model::create(std::size_t partCount) {
        auto model = std::make_unique<Model>();

        model->m_parts.resize(partCount);

        for (std::size_t i=0; i<partCount; i++) {
            model->m_parts[i] = std::make_unique<ModelPart>();
        }
    }
}
