
#include "PlaneGenerator.hpp"

namespace xe {

    //std::vector<xe::Vector3f> PlaneGenerator::genCoords(const Plane &plane) const {
    //    std::vector<xe::Vector3f> coords;

    //    coords.reserve(this->getCoordCount());

    //    const xe::Vector3f top = {0.0, 1.0, 0.0};

    //    xe::Matrix4f rotation = xe::Matrix4f::makeIdentity();
    //    if (top != plane.normal) {
    //        const float radians = xe::dot(plane.normal, top);
    //        const xe::Vector3f axis = xe::cross(plane.normal, top);

    //        rotation = xe::Matrix4f::makeRotate(radians, axis);
    //    }

    //    const xe::Vector3f up = plane.normal;
    //    const xe::Vector3f forward = xe::transform(rotation, {0.0, 0.0, 1.0});
    //    const xe::Vector3f right = xe::transform(rotation, {1.0, 0.0, 0.0});

    //    const xe::Vector3f center = plane.point;

    //    // compute the geometry patch
    //    for (int i=0; i<stacks; i++) {
    //        for (int j=0; j<slices; j++) {
    //            // i, j are the coordinates of the current grid element.
    //            // each grid element has 4 points, so we need to generate six points (three per triangle)
    //            std::array<xe::Vector3f, 4> points = {
    //                center + float(j + 0)*right + float(i + 0)*forward,
    //                center + float(j + 1)*right + float(i + 0)*forward,
    //                center + float(j + 0)*right + float(i + 1)*forward,
    //                center + float(j + 1)*right + float(i + 1)*forward
    //            };

    //            coords.push_back(points[0]);
    //            coords.push_back(points[1]);
    //            coords.push_back(points[2]);

    //            coords.push_back(points[2]);
    //            coords.push_back(points[1]);
    //            coords.push_back(points[3]);
    //        }
    //    }

    //    for (auto coord : coords) {
    //        std::cout << coord << std::endl;
    //    }

    //    return coords;
    //}

    std::vector<xe::Vector3f> PlaneGenerator::genCoords(const Plane &plane) const {
        std::vector<xe::Vector3f> coords;

        coords.reserve(this->getCoordCount());

        const xe::Vector3f points[] = {
            /*
            {-0.25f, 0.0f,  0.25f},
            { 0.25f, 0.0f,  0.25f},
            {-0.25f, 0.0f, -0.25f},
            { 0.25f, 0.0f, -0.25f}, 
            */
            {-0.25f, 0.25f,  0.0f},
            { 0.25f, 0.25f,  0.0f},
            {-0.25f, -0.25f, 0.0f},
            { 0.25f, -0.25f, 0.0f}
        };

        coords.push_back(points[0]);
        coords.push_back(points[2]);
        coords.push_back(points[1]);

        coords.push_back(points[1]);
        coords.push_back(points[2]);
        coords.push_back(points[3]);
        
        for (auto coord : coords) {
            std::cout << coord << std::endl;
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

    std::vector<xe::Vector3f> PlaneGenerator::genNormals(const Plane &plane) const {
        std::vector<xe::Vector3f> normals;

        normals.resize(this->getCoordCount());

        for (xe::Vector3f &normal : normals) {
            normal = plane.normal;
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
        
        texCoords.push_back(points[0]);
        texCoords.push_back(points[2]);
        texCoords.push_back(points[1]);

        texCoords.push_back(points[1]);
        texCoords.push_back(points[2]);
        texCoords.push_back(points[3]);        
        
        return texCoords;
    }
}
