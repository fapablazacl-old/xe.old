
#include "Generator.hpp"

#include <array>
#include <xe/Matrix.hpp>

namespace xe { namespace sg {

    //struct Triangle {
    //    Triangle(const xe::Vector3f p0_, const xe::Vector3f p1_, const xe::Vector3f p2_) 
    //        : p0(p0_), p1(p1_), p2(p2_), normal(getNormal()) {
    //    }

    //    const xe::Vector3f p0, p1, p2;
    //    const xe::Vector3f normal;

    //private:
    //    xe::Vector3f getNormal() const {
    //        const xe::Vector3f v1 = p1 - p0;
    //        const xe::Vector3f v2 = p2 - p0;

    //        return xe::normalize(xe::cross(v1, v2));
    //    }
    //};

    std::vector<xe::Vector3f> Generator::genNormals(const std::vector<xe::Vector3f> &coords) const  {
        assert(coords.size()%3 == 0);

        std::vector<xe::Vector3f> normals;

        normals.resize(coords.size());

        for (std::size_t i=0; i<coords.size(); i+=3) {
            const xe::Vector3f p0 = coords[i + 0];
            const xe::Vector3f p1 = coords[i + 1];
            const xe::Vector3f p2 = coords[i + 2];

            const xe::Vector3f v1 = p1 - p0;
            const xe::Vector3f v2 = p2 - p0;
            const xe::Vector3f normal = xe::normalize(xe::cross(v1, v2));

            normals[i + 0] = normal;
            normals[i + 1] = normal;
            normals[i + 2] = normal;
        }

        return normals;
    }

    std::vector<xe::Vector3f> Generator::genNormals(const std::vector<xe::Vector3f> &coords, const std::vector<std::uint32_t> &indices) const {
        assert(indices.size() > 0);
        assert(indices.size() % 3 == 0);

        std::vector<xe::Vector3f> normals;

        normals.resize(coords.size());

        for (std::size_t i=0; i<indices.size(); i+=3) {
            const xe::Vector3f p0 = coords[indices[i + 0]];
            const xe::Vector3f p1 = coords[indices[i + 1]];
            const xe::Vector3f p2 = coords[indices[i + 2]];

            const xe::Vector3f v1 = p1 - p0;
            const xe::Vector3f v2 = p2 - p0;
            const xe::Vector3f normal = xe::normalize(xe::cross(v1, v2));

            normals[indices[i + 0]] = normal;
            normals[indices[i + 1]] = normal;
            normals[indices[i + 2]] = normal;
        }

        return normals;
    }
    
    std::size_t SphereGenerator::getCoordCount() const {
        return (stacks - 1) * slices + 2;
    }

    std::vector<xe::Vector3f> SphereGenerator::genCoords(const float radius) const {
        assert(slices >= 3);
        assert(stacks >= 3);
        assert(radius > 0.0f);

        float angle = 0.0f;

        const float slices_delta = 2.0f * pi / slices;
        const float stacks_delta = pi / stacks;

        const xe::Vector3f slices_axis = {0.0f, 1.0f, 0.0f};
        const xe::Vector3f stacks_axis = {1.0f, 0.0f, 0.0f};
        
        const xe::Vector3f point = {0.0f, radius, 0.0f};

        float slices_angle = slices_delta;
        float stacks_angle = stacks_delta;

        std::vector<xe::Vector3f> points;

        points.reserve(this->getCoordCount());

        points.push_back(point);

        for (std::size_t i=0; i<stacks - 1; i++) {
            for (std::size_t j=0; j<slices; j++) {
                const auto mstacks = xe::Matrix4f::makeRotate(stacks_angle, stacks_axis);
                const auto mslices = xe::Matrix4f::makeRotate(slices_angle, slices_axis);

                points.push_back(xe::transform(mslices * mstacks, point));

                slices_angle += slices_delta;
            }

            slices_angle = slices_delta;
            stacks_angle += stacks_delta;
        }

        points.push_back(-point);

        return points;
    }

    std::vector<std::uint32_t> SphereGenerator::genIndices() const {
        struct Grid {
            std::uint32_t base;
            std::uint32_t rows;
            std::uint32_t cols;

            std::uint32_t index(const std::uint32_t i, const std::uint32_t j) const {
                assert(i >= 0);
                assert(i < rows);
                assert(j >= 0);
                assert(j < cols);

                return base + i*cols + j;
            }
        };

        std::vector<std::uint32_t> indices;

        // top indices
        for (std::uint32_t i=1; i<slices; i++) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i);
        }

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back((std::uint32_t)slices);

        // body indices
        Grid grid = {1, (std::uint32_t)stacks, (std::uint32_t)slices};

        for (std::uint32_t i=0; i<stacks - 2; i++) {
            std::uint32_t i0, i1, i2, i3;

            for (std::uint32_t j=0; j<slices; j++) {
                if (j < slices - 1) {
                    i0 = grid.index(i + 0, j + 0);
                    i1 = grid.index(i + 0, j + 1);
                    i2 = grid.index(i + 1, j + 0);
                    i3 = grid.index(i + 1, j + 1);

                } else {
                    i0 = grid.index(i + 0, (std::uint32_t)slices - 1);
                    i1 = grid.index(i + 0, 0);
                    i2 = grid.index(i + 1, (std::uint32_t)slices - 1);
                    i3 = grid.index(i + 1, 0);
                }

                // first triangle
                indices.push_back(i0);
                indices.push_back(i1);
                indices.push_back(i2);

                // second triangle
                indices.push_back(i1);
                indices.push_back(i3);
                indices.push_back(i2);
            }
        }

        // bottom indices
        const std::uint32_t lastPoint = (std::uint32_t)this->getCoordCount() - 1;    // compute sphere point count

        for (std::uint32_t i=1; i<slices; i++) {
            indices.push_back(lastPoint);
            indices.push_back(lastPoint - (i + 1));
            indices.push_back(lastPoint - i);
        }

        indices.push_back(lastPoint);
        indices.push_back(lastPoint - 1);
        indices.push_back(lastPoint - (std::uint32_t)slices);
        
        return indices;
    }

    /**
     * @brief Generate the normal for any ellipsoid object (including spheres)
     */
    std::vector<xe::Vector3f> SphereGenerator::genNormals(const std::vector<xe::Vector3f> &coords) const {
        std::vector<xe::Vector3f> normals;

        normals.resize(coords.size());

        for (std::size_t i=0; i<coords.size(); i++) {
            normals[i] = xe::normalize(coords[i]);
        }

        return normals;
    }
}}

namespace xe { namespace sg {

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
}}
