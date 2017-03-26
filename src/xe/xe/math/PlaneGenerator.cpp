
#include "PlaneGenerator.hpp"

#include <array>
#include <xe/math/Matrix.hpp>

namespace xe {
    std::vector<xe::Vector3f> PlaneGenerator::genCoords(const Plane_f &plane, const float width, const float length) const {
        assert(width > 0.0f);
        assert(length > 0.0f);
        assert(xe::norm(plane.getNormal()) > 0.0f);

        std::vector<xe::Vector3f> coords(this->getCoordCount());

        const auto pn = plane.getNormal();
        const auto pp = plane.getPosition();

        const xe::Vector3f top = {0.0, 1.0, 0.0};
        const xe::Vector2f delta = {1.0f/slices, 1.0f/stacks};

        xe::Matrix4f rotation;

        if (top != pn) {
            const auto radians = std::acos(xe::dot(pn, top));
            const auto axis = xe::cross(pn, top);

            rotation = xe::Matrix4f::makeRotate(radians, axis);
        } else {
            rotation = xe::Matrix4f::makeIdentity();
        }

        const xe::Vector3f up = {0.0f, 1.0f, 0.0f};
        const xe::Vector3f right = xe::transform(rotation, {1.0, 0.0, 0.0}) * width;
        const xe::Vector3f forward = xe::transform(rotation, {0.0, 0.0, -1.0}) * length;
        const xe::Vector3f center = pp;

        int index = 0;

        for (float i=-0.5f; i<0.5f; i+=delta.y) {
            for (float j=-0.5f; j<0.5f; j+=delta.x) {

                std::array<xe::Vector3f, 4> points = {
                    center + (j + 0.0f   )*right + float(i + 0.0f   )*forward,
                    center + (j + delta.x)*right + float(i + 0.0f   )*forward,
                    center + (j + 0.0f   )*right + float(i + delta.y)*forward,
                    center + (j + delta.x)*right + float(i + delta.y)*forward
                };

                coords[index++] = points[0];
                coords[index++] = points[1];
                coords[index++] = points[2];

                coords[index++] = points[2];
                coords[index++] = points[1];
                coords[index++] = points[3];
            }
        }

        return coords;
    }
    
    std::size_t PlaneGenerator::getCoordCount() const {
        return slices * stacks * 6;
    }

    std::vector<std::uint32_t> PlaneGenerator::genIndices() const {
        std::vector<std::uint32_t> indices;

        indices.resize(this->getCoordCount());

        for (std::size_t i=0; i<this->getCoordCount(); i++) {
            indices[i] = static_cast<std::uint32_t>(i);
        }

        return indices;
    }

    std::vector<xe::Vector3f> PlaneGenerator::genNormals(const Plane_f &plane) const {
        std::vector<xe::Vector3f> normals;

        normals.resize(this->getCoordCount());

        for (xe::Vector3f &normal : normals) {
            normal = plane.getNormal();
        }

        return normals;
    }
    
    std::vector<xe::Vector2f> PlaneGenerator::genTexCoords() const {
        const xe::Vector2f points[] = {
            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
        };
        
        std::vector<xe::Vector2f> texCoords;
        
        for (int i=0; i<stacks; i++) {
            for (int j=0; j<slices; j++) {
                texCoords.push_back(points[0]);
                texCoords.push_back(points[2]);
                texCoords.push_back(points[1]);

                texCoords.push_back(points[1]);
                texCoords.push_back(points[2]);
                texCoords.push_back(points[3]);
            }
        }

        return texCoords;
    }
}
