
#define BOOST_TEST_MODULE XE::Tests
#include <boost/test/included/unit_test.hpp>

#include <xe/Quaternion.hpp>

BOOST_AUTO_TEST_CASE(TestQuaternion)
{
    auto qz = xe::Quaternionf::makeZero();
    auto qi = xe::Quaternionf::makeIdentity();
    
    auto q_r1 = xe::Quaternionf({-1.0f, 1.0f, -1.0f}, 2.0f);
    auto q_r2 = xe::Quaternionf({2.0f, -0.25f, 0.5f}, -1.0f);
    auto q_r3 = xe::Quaternionf({0.5f, 0.25f, 1.5f}, 0.0f);
    
    // check accessors
    BOOST_CHECK_EQUAL(qz, xe::Quaternionf({0.0f, 0.0f, 0.0f}, 0.0f));
    BOOST_CHECK_EQUAL(qi, xe::Quaternionf({0.0f, 0.0f, 0.0f}, 1.0f));
    
    BOOST_CHECK_EQUAL(qi.v, xe::Vector3f(0.0f, 0.0f, 0.0f));
    BOOST_CHECK_EQUAL(qi.w, 1.0f);
    
    BOOST_CHECK_EQUAL(q_r1.x, -1.0f);
    BOOST_CHECK_EQUAL(q_r1.y, 1.0f);
    BOOST_CHECK_EQUAL(q_r1.z, -1.0f);
    BOOST_CHECK_EQUAL(q_r1.w, 2.0f);
    BOOST_CHECK_EQUAL(q_r1.v, xe::Vector3f(-1.0f, 1.0f, -1.0f));
    
    // check comparison operators
    BOOST_CHECK_EQUAL(q_r1, q_r1);
    BOOST_CHECK_NE(q_r1, q_r2);
    BOOST_CHECK_NE(q_r1, q_r3);
    
    // check operators
    BOOST_CHECK_EQUAL(qz + qz, qz);
    BOOST_CHECK_EQUAL(qi + qz, qi);
    BOOST_CHECK_EQUAL(q_r1 + qz, q_r1);
    BOOST_CHECK_EQUAL(q_r1 + q_r1, xe::Quaternionf(-2.0f, 2.0f, -2.0f, 4.0f));
    BOOST_CHECK_EQUAL(-q_r1, xe::Quaternionf(1.0f, -1.0f, 1.0f, -2.0f));
    BOOST_CHECK_EQUAL(+q_r1, xe::Quaternionf(-1.0f, 1.0f, -1.0f, 2.0f));
    BOOST_CHECK_EQUAL(q_r1 - q_r1, xe::Quaternionf(0.0f, 0.0f, 0.0f, 0.0f));
    BOOST_CHECK_EQUAL(2.0f * q_r1, xe::Quaternionf(-2.0f, 2.0f, -2.0f, 4.0f));
    BOOST_CHECK_EQUAL(q_r1 * 2.0f, xe::Quaternionf(-2.0f, 2.0f, -2.0f, 4.0f));
    
    BOOST_CHECK_EQUAL(q_r1 * qi, q_r1);
    BOOST_CHECK_EQUAL(q_r1 / qi, q_r1);
    BOOST_CHECK_EQUAL(q_r1 / q_r1, qi);
    
    std::cout << q_r1 << std::endl;
    std::cout << inverse(q_r1) << std::endl;
    
    // check global functions
    BOOST_CHECK_EQUAL(xe::norm_pow2(q_r1), 7.0f);
}
