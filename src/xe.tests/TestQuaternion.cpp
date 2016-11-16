
#include <UnitTest++/UnitTest++.h>
#include <xe/Quaternion.hpp>

TEST(TestQuaternion_Accessors)
{
    auto qz = xe::Quaternionf::makeZero();
    auto qi = xe::Quaternionf::makeIdentity();
    
    auto q_r1 = xe::Quaternionf({-1.0f, 1.0f, -1.0f}, 2.0f);
    auto q_r2 = xe::Quaternionf({2.0f, -0.25f, 0.5f}, -1.0f);
    auto q_r3 = xe::Quaternionf({0.5f, 0.25f, 1.5f}, 0.0f);
    
    // check accessors
    CHECK_EQUAL(qz, xe::Quaternionf({0.0f, 0.0f, 0.0f}, 0.0f));
    CHECK_EQUAL(qi, xe::Quaternionf({0.0f, 0.0f, 0.0f}, 1.0f));
    
    CHECK_EQUAL(qi.v, xe::Vector3f(0.0f, 0.0f, 0.0f));
    CHECK_EQUAL(qi.w, 1.0f);
    
    CHECK_EQUAL(q_r1.x, -1.0f);
    CHECK_EQUAL(q_r1.y, 1.0f);
    CHECK_EQUAL(q_r1.z, -1.0f);
    CHECK_EQUAL(q_r1.w, 2.0f);
    CHECK_EQUAL(q_r1.v, xe::Vector3f(-1.0f, 1.0f, -1.0f));
    
    // check comparison operators
    CHECK_EQUAL(q_r1, q_r1);
    //CHECK_EQUAL(q_r1, q_r2);
    //CHECK_EQUAL(q_r1, q_r3);
}

TEST(TestQuaternion_Operators)
{
    auto qz = xe::Quaternionf::makeZero();
    auto qi = xe::Quaternionf::makeIdentity();
    
    auto q_r1 = xe::Quaternionf({-1.0f, 1.0f, -1.0f}, 2.0f);
    auto q_r2 = xe::Quaternionf({2.0f, -0.25f, 0.5f}, -1.0f);
    auto q_r3 = xe::Quaternionf({0.5f, 0.25f, 1.5f}, 0.0f);
    
    // check operators
    CHECK_EQUAL(qz + qz, qz);
    CHECK_EQUAL(qi + qz, qi);
    CHECK_EQUAL(q_r1 + qz, q_r1);
    CHECK_EQUAL(q_r1 + q_r1, xe::Quaternionf(-2.0f, 2.0f, -2.0f, 4.0f));
    CHECK_EQUAL(-q_r1, xe::Quaternionf(1.0f, -1.0f, 1.0f, -2.0f));
    CHECK_EQUAL(+q_r1, xe::Quaternionf(-1.0f, 1.0f, -1.0f, 2.0f));
    CHECK_EQUAL(q_r1 - q_r1, xe::Quaternionf(0.0f, 0.0f, 0.0f, 0.0f));
    CHECK_EQUAL(2.0f * q_r1, xe::Quaternionf(-2.0f, 2.0f, -2.0f, 4.0f));
    CHECK_EQUAL(q_r1 * 2.0f, xe::Quaternionf(-2.0f, 2.0f, -2.0f, 4.0f));
    
    CHECK_EQUAL(q_r1 * qi, q_r1);
    CHECK_EQUAL(q_r1 / qi, q_r1);
    //CHECK_EQUAL(q_r1 / q_r1, qi);
    
    // check global functions
    CHECK_EQUAL(xe::norm_pow2(q_r1), 7.0f);
}
