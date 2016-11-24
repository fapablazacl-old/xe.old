
#include <UnitTest++/UnitTest++.h>
#include <xe/Vector.hpp>

TEST(TestVector_Accessors)
{
    xe::Vector3f v0 (0.0f, 0.0f, 0.0f);
    
    xe::Vector3f v1;
    v1.x = 0.0f;
    v1.y = 1.0f;
    v1.z = 2.0f;
    
    xe::Vector3f v2 = {-2.0f, 0.0f, 1.0f};
    
    xe::Vector3f v3;
    v3[0] = 1.0f;
    v3[1] = 2.0f;
    v3[2] = -3.0f;
    
    CHECK_EQUAL(v0[0], 0.0f);
    CHECK_EQUAL(v0[1], 0.0f);
    CHECK_EQUAL(v0[2], 0.0f);
    
    CHECK_EQUAL(v1[0], 0.0f);
    CHECK_EQUAL(v1[1], 1.0f);
    CHECK_EQUAL(v1[2], 2.0f);
    
    CHECK_EQUAL(v2[0], -2.0f);
    CHECK_EQUAL(v2[1], 0.0f);
    CHECK_EQUAL(v2[2], 1.0f);
    
    CHECK_EQUAL(v3.x, 1.0f);
    CHECK_EQUAL(v3.y, 2.0f);
    CHECK_EQUAL(v3.z, -3.0f);
}

TEST(TestVector_Operators)
{
    xe::Vector3f v1(0.0f, 1.0f, 2.0f);
    xe::Vector3f v2(-2.0f, 0.0f, 1.0f);
    xe::Vector3f v3(1.0f, -1.0f, -3.0f);
    
    xe::Vector3f v1_sub_v1(0.0f, 0.0f, 0.0f);
    xe::Vector3f v1_add_v1(0.0f, 2.0f, 4.0f);
    xe::Vector3f v1_mul_3(0.0f, 3.0f, 6.0f);
    xe::Vector3f v1_div_2(0.0f, 0.5f, 1.0f);
    xe::Vector3f v1_mul_neg_3(0.0f, -3.0f, -6.0f);
    xe::Vector3f v2_add_v3(-1.0f, -1.0f, -2.0f);
    xe::Vector3f v2_sub_v3(-3.0f, 1.0f, 4.0f);
    
    CHECK_EQUAL(v1, v1);
    CHECK_EQUAL(v2, v2);
    CHECK_EQUAL(v3, v3);
    
    CHECK_EQUAL(v1 - v1, v1_sub_v1);
    CHECK_EQUAL(v1 + v1, v1_add_v1);
    CHECK_EQUAL(v1 * 3.0f, v1_mul_3);
    CHECK_EQUAL(3.0f * v1, v1_mul_3);
    CHECK_EQUAL(v1 / 2.0f, v1_div_2);
    CHECK_EQUAL(v1 * -3.0f, v1_mul_neg_3);
    CHECK_EQUAL(v2 + v3, v2_add_v3);
    CHECK_EQUAL(v2 - v3, v2_sub_v3);
}
