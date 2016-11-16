
#include <UnitTest++/UnitTest++.h>
#include <xe/Matrix.hpp>

TEST(TestMatrixAccessors)
{
    const xe::Matrix4f matA = {
        {1.0f, 2.0f, 1.0f, 0.0f}, 
        {2.0f, 1.0f, -3.0f, -1.0f}, 
        {-3.0f, 2.0f, 1.0f, 0.0f}, 
        {2.0f, -1.0f, 0.0f, -1.0f}
    };
    
    const xe::Matrix4f matB = {
        {-3.0f, 1.0f, 5.0f, 1.0f},
        {1.0f, 2.0f, -1.0f, 1.0f},
        {1.0f, 2.0f, 1.0f, -2.0f},
        {1.0f, -1.0f, -3.0f, -1.0f}
    };
    
    const auto subIdentity = xe::Matrix3f::makeIdentity();
    
    const auto identity = xe::Matrix4f::makeIdentity();
    
    const auto zero = xe::Matrix3f::makeZero();
    
    const xe::Matrix4f matAddResult = {
        {-2.0f,  3.0f,  6.0f,  1.0f},
        { 3.0f,  3.0f, -4.0f,  0.0f},
        {-2.0f,  4.0f,  2.0f, -2.0f},
        { 3.0f, -2.0f, -3.0f, -2.0f}
    };
    
    const xe::Matrix4f matSubResult = {
        { 4.0f,  1.0f, -4.0f, -1.0f},
        { 1.0f, -1.0f, -2.0f, -2.0f},
        {-4.0f,  0.0f,  0.0f,  2.0f},
        { 1.0f,  0.0f,  3.0f,  0.0f}
    };
    
    const xe::Matrix4f matMulResult = {
        {  0.0f,  7.0f,  4.0f,   1.0f},
        { -9.0f, -1.0f,  9.0f,  10.0f},
        { 12.0f,  3.0f, -16.0f, -3.0f},
        { -8.0f,  1.0f,  14.0f,  2.0f}
    };
    
    const xe::Matrix4f matDivResult = {
        {-1.0f, 2.0f, 0.f,  0.0f},
        { 2.0f, 0.0f, 3.0f, -1.0f},
        {-3.0f, 1.0f, 1.0f,  0.0f},
        { 2.0f, 1.0f, 0.0f,  1.0f}
    };
    
    const xe::Matrix4f invMatA = {
        {0.25000f,  0.000f, -0.25000f,  0.000},
        {0.28125f,  0.125f,  0.09375f, -0.125},
        {0.18750f, -0.250f,  0.06250f,  0.250},
        {0.21875f, -0.125f, -0.59375f, -0.875}
    };
 
    const float detA = -32.0f;
    
    xe::Matrix4f aux;
    
    // matrix element retrieval by function paramenters
    CHECK_EQUAL(matA.get(0, 0), 1.0f);
    CHECK_EQUAL(matA.get(0, 1), 2.0f);
    CHECK_EQUAL(matA.get(0, 2), 1.0f);
    CHECK_EQUAL(matA.get(0, 3), 0.0f);
        
    CHECK_EQUAL(matA.get(1, 0), 2.0f);
    CHECK_EQUAL(matA.get(1, 1), 1.0f);
    CHECK_EQUAL(matA.get(1, 2), -3.0f);
    CHECK_EQUAL(matA.get(1, 3), -1.0f);
        
    CHECK_EQUAL(matA.get(2, 0), -3.0f);
    CHECK_EQUAL(matA.get(2, 1), 2.0f);
    CHECK_EQUAL(matA.get(2, 2), 1.0f);
    CHECK_EQUAL(matA.get(2, 3), 0.0f);
        
    CHECK_EQUAL(matA.get(3, 0), 2.0f);
    CHECK_EQUAL(matA.get(3, 1), -1.0f);
    CHECK_EQUAL(matA.get(3, 2), 0.0f);
    CHECK_EQUAL(matA.get(3, 3), -1.0f);
        
    // matrix element retrieval by template paramenters
    CHECK_EQUAL( (matA.get<0, 0>()), 1.0f);
    CHECK_EQUAL( (matA.get<0, 1>()), 2.0f);
    CHECK_EQUAL( (matA.get<0, 2>()), 1.0f);
    CHECK_EQUAL( (matA.get<0, 3>()), 0.0f);
        
    CHECK_EQUAL( (matA.get<1, 0>()), 2.0f);
    CHECK_EQUAL( (matA.get<1, 1>()), 1.0f);
    CHECK_EQUAL( (matA.get<1, 2>()), -3.0f);
    CHECK_EQUAL( (matA.get<1, 3>()), -1.0f);
        
    CHECK_EQUAL( (matA.get<2, 0>()), -3.0f);
    CHECK_EQUAL( (matA.get<2, 1>()), 2.0f);
    CHECK_EQUAL( (matA.get<2, 2>()), 1.0f);
    CHECK_EQUAL( (matA.get<2, 3>()), 0.0f);
        
    CHECK_EQUAL( (matA.get<3, 0>()), 2.0f);
    CHECK_EQUAL( (matA.get<3, 1>()), -1.0f);
    CHECK_EQUAL( (matA.get<3, 2>()), 0.0f);
    CHECK_EQUAL( (matA.get<3, 3>()), -1.0f);
        
    // matrix row vectors
    CHECK_EQUAL(matA.getRow(0), xe::Vector4f(1.0f, 2.0f, 1.0f, 0.0f));
    CHECK_EQUAL(matA.getRow(1), xe::Vector4f(2.0f, 1.0f, -3.0f, -1.0f));
    CHECK_EQUAL(matA.getRow(2), xe::Vector4f(-3.0f, 2.0f, 1.0f, 0.0f));
    CHECK_EQUAL(matA.getRow(3), xe::Vector4f(2.0f, -1.0f, 0.0f, -1.0f));
        
    // matrix column vectors
    CHECK_EQUAL(matA.getColumn(0), xe::Vector4f(1.0f, 2.0f, -3.0f, 2.0f));
    CHECK_EQUAL(matA.getColumn(1), xe::Vector4f(2.0f, 1.0f, 2.0f, -1.0f));
    CHECK_EQUAL(matA.getColumn(2), xe::Vector4f(1.0f, -3.0f, 1.0f, 0.0f));
    CHECK_EQUAL(matA.getColumn(3), xe::Vector4f(0.0f, -1.0f, 0.0f, -1.0f));
        
    // matrix direct comparison
    CHECK(matA != matB);
        
    // matrix scale
    CHECK_EQUAL(matA * -1.0f, -matA);
    CHECK_EQUAL(matA * -1.0f, -1.0f * matA);
    CHECK_EQUAL(matA * 1.0f, matA);
        
    // matrix adition 
    CHECK_EQUAL(matAddResult, matA + matB);
    CHECK_EQUAL(matSubResult, matA - matB);
        
    aux = matA; aux += matB;
    CHECK_EQUAL(matAddResult, aux);
        
    aux = matA; aux -= matB;
    CHECK_EQUAL(matSubResult, aux);
        
    // submatrix
    CHECK_EQUAL(subIdentity, identity.getSubMatrix(0, 0));
        
    // matrix determinant
    CHECK_EQUAL( abs(identity), 1.0f );
    CHECK_EQUAL( abs(matA), detA );
        
    //matrix multiply
    CHECK_EQUAL(matMulResult, matA * matB);
    CHECK_EQUAL(matMulResult, ((aux = matA) *= matB));
    
	CHECK_EQUAL(identity, identity * identity);

	CHECK_EQUAL(matA, matA * identity);
	CHECK_EQUAL(matA, identity * matA);

    //inverse matrix
    aux = inverse(matA);

	CHECK_EQUAL( invMatA, aux );

	// vector transformation
	xe::Matrix4f translation = xe::Matrix4f::makeTranslate({1.0f, 1.0f, 1.0f, 1.0f});
	xe::Vector3f position1 = {0.0f, -1.0f, 0.0f};
	xe::Vector3f position2_1 = {1.0f,  0.0f, 1.0f};
	xe::Vector3f position2_2 = xe::transform<float, 4>(translation, position1);
	
	CHECK_EQUAL(position2_1, position2_2);
}
