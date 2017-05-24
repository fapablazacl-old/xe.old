
#include <UnitTest++/UnitTest++.h>

#include <xe/Structure.hpp>
#include <xe/Vector.hpp>

namespace xe {

    template<typename T, size_t C>
    struct Vector;

    /** 
     * @brief A trait template-based class equivalent for attributes.
     */
    template<typename Type_>
    struct Field {
        typedef Type_ Type;
    };

    /**
     * @brief These collection of predefined vertex attributes
     */
    namespace fields {
        template<typename Type>
        struct Coord : Field<Type> {
            Type coord;
        };

        template<typename Type>
        struct Normal : Field<Type> {
            Type normal;
        };

        template<typename Type>
        struct Binormal : Field<Type> {
            Type binormal;
        };

        template<typename Type>
        struct Color : Field<Type> {
            Type color;
        };

        template<typename Type>
        struct Tangent : Field<Type> {
            Type tangent;
        };

        template<typename Type, size_t Index>
        struct TexCoord;

        template<typename Type>
        struct TexCoord<Type, 0> : Field<Type> {
            Type texCoord;
        };

        template<typename Type>
        struct TexCoord<Type, 1> : Field<Type> {
            Type texCoord2;
        };

        template<typename Type>
        struct TexCoord<Type, 2> : Field<Type> {
            Type texCoord3;
        };

        template<typename Type>
        struct TexCoord<Type, 3> : Field<Type> {
            Type texCoord4;
        };

        template<typename Type>
        struct TexCoord<Type, 4> : Field<Type> {
            Type texCoord5;
        };
    }

    /**
     * @brief Structure template. Aids the user in defining custom vertex formats and custom uniform formats.
     *
     * The main purpose of the Structure template is to, via metaprogramming tricks:
     *  - Eliminate the need for manual Vertex Formats and Uniform Formats.
     *  - Aiding the geometry generators to create dynamic objects using any user-supplied vertex structure and/or format.
     *  - Convert a vertex from one vertex format to another one.
     *
     * @comment I think the main challenge is to properly manage the compile-runtime brigde.
     */
    template<typename Field, typename ...Fields>
    struct Structure : Field, Fields... {
        Structure() {}

        Structure(const typename Field::Type &field1) {
        }
    };
}

TEST(TestStructure)
{
    typedef xe::Structure <
        xe::fields::Coord<xe::Vector3f>, 
        xe::fields::Normal<xe::Vector3f>, 
        xe::fields::TexCoord<xe::Vector2f, 0>
    > Vertex;

    Vertex v1, v2, v3;
}
