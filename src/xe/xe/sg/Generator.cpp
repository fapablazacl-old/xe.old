
#include "Generator.hpp"

#include <array>
#include <xe/Matrix.hpp>

namespace xe {

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
}
