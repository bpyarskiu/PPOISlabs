#include <UnitTest++/UnitTest++.h>
#include "../include/Matrix.hpp"

TEST(MatrixDefaultConstructor) {
    Matrix m;
    CHECK_EQUAL(0, m.getRows());
    CHECK_EQUAL(0, m.getCols());
}

TEST(MatrixParameterizedConstructor) {
    Matrix m(2, 3);
    CHECK_EQUAL(2, m.getRows());
    CHECK_EQUAL(3, m.getCols());
    
    // Проверяем инициализацию нулями
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            CHECK_EQUAL(0.0, m.at(i, j));
        }
    }
}

TEST(MatrixCopyConstructor) {
    Matrix original(2, 2);
    original.at(0, 0) = 1.0;
    original.at(0, 1) = 2.0;
    original.at(1, 0) = 3.0;
    original.at(1, 1) = 4.0;
    
    Matrix copy(original);
    
    CHECK_EQUAL(2, copy.getRows());
    CHECK_EQUAL(2, copy.getCols());
    CHECK_EQUAL(1.0, copy.at(0, 0));
    CHECK_EQUAL(2.0, copy.at(0, 1));
    CHECK_EQUAL(3.0, copy.at(1, 0));
    CHECK_EQUAL(4.0, copy.at(1, 1));
}

TEST(MatrixPreIncrement) {
    Matrix m(2, 2);
    m.at(0, 0) = 1.0;
    m.at(0, 1) = 2.0;
    
    ++m;
    
    CHECK_EQUAL(2.0, m.at(0, 0));
    CHECK_EQUAL(3.0, m.at(0, 1));
}

TEST(MatrixPostIncrement) {
    Matrix m(2, 2);
    m.at(0, 0) = 1.0;
    m.at(0, 1) = 2.0;
    
    Matrix old = m++;
    
    CHECK_EQUAL(1.0, old.at(0, 0));
    CHECK_EQUAL(2.0, old.at(0, 1));
    CHECK_EQUAL(2.0, m.at(0, 0));
    CHECK_EQUAL(3.0, m.at(0, 1));
}

TEST(MatrixPreDecrement) {
    Matrix m(2, 2);
    m.at(0, 0) = 3.0;
    m.at(0, 1) = 4.0;
    
    --m;
    
    CHECK_EQUAL(2.0, m.at(0, 0));
    CHECK_EQUAL(3.0, m.at(0, 1));
}
TEST(MatrixPostDecrement) {
    Matrix m(2, 2);
    m.at(0, 0) = 3.0;
    m.at(0, 1) = 4.0;
    
    m--;
    
    CHECK_EQUAL(2.0, m.at(0, 0));
    CHECK_EQUAL(3.0, m.at(0, 1));
}

TEST(MatrixResizeLarger) {
    Matrix m(2, 2);
    m.at(0, 0) = 1.0;
    m.at(0, 1) = 2.0;
    m.at(1, 0) = 3.0;
    m.at(1, 1) = 4.0;
    
    m.resize(3, 3);
    
    CHECK_EQUAL(3, m.getRows());
    CHECK_EQUAL(3, m.getCols());
    CHECK_EQUAL(1.0, m.at(0, 0));
    CHECK_EQUAL(2.0, m.at(0, 1));
    CHECK_EQUAL(3.0, m.at(1, 0));
    CHECK_EQUAL(4.0, m.at(1, 1));
    CHECK_EQUAL(0.0, m.at(2, 2));
}

TEST(MatrixResizeSmaller) {
    Matrix m(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            m.at(i, j) = i * 3 + j + 1;
        }
    }
    
    m.resize(2, 2);
    
    CHECK_EQUAL(2, m.getRows());
    CHECK_EQUAL(2, m.getCols());
    CHECK_EQUAL(1.0, m.at(0, 0));
    CHECK_EQUAL(2.0, m.at(0, 1));
    CHECK_EQUAL(4.0, m.at(1, 0));
    CHECK_EQUAL(5.0, m.at(1, 1));
}

TEST(MatrixGetSubmatrix) {
    Matrix m(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            m.at(i, j) = i * 3 + j + 1;
        }
    }
    
    Matrix sub = m.getSubmatrix(1, 1, 2, 2);
    
    CHECK_EQUAL(2, sub.getRows());
    CHECK_EQUAL(2, sub.getCols());
    CHECK_EQUAL(5.0, sub.at(0, 0));
    CHECK_EQUAL(6.0, sub.at(0, 1));
    CHECK_EQUAL(8.0, sub.at(1, 0));
    CHECK_EQUAL(9.0, sub.at(1, 1));
}

TEST(MatrixIsSquare) {
    Matrix square(3, 3);
    Matrix nonSquare(2, 3);
    
    CHECK(square.isSquare());
    CHECK(!nonSquare.isSquare());
}

TEST(MatrixIsZero) {
    Matrix zero(2, 2);
    Matrix nonZero(2, 2);
    nonZero.at(0, 0) = 1.0;
    
    CHECK(zero.isZero());
    CHECK(!nonZero.isZero());
}

TEST(MatrixIsIdentity) {
    Matrix identity(3, 3);
    identity.at(0, 0) = 1.0;
    identity.at(1, 1) = 1.0;
    identity.at(2, 2) = 1.0;
    
    Matrix nonIdentity(3, 3);
    nonIdentity.at(0, 0) = 1.0;
    nonIdentity.at(0, 1) = 1.0;
    
    CHECK(identity.isIdentity());
    CHECK(!nonIdentity.isIdentity());
}

TEST(MatrixIsDiagonal) {
    Matrix diagonal(3, 3);
    diagonal.at(0, 0) = 1.0;
    diagonal.at(1, 1) = 2.0;
    diagonal.at(2, 2) = 3.0;
    
    Matrix nonDiagonal(3, 3);
    nonDiagonal.at(0, 0) = 1.0;
    nonDiagonal.at(0, 1) = 0.5;
    
    CHECK(diagonal.isDiagonal());
    CHECK(!nonDiagonal.isDiagonal());
}

TEST(MatrixIsSymmetric) {
    Matrix symmetric(3, 3);
    symmetric.at(0, 0) = 1.0; symmetric.at(0, 1) = 2.0; symmetric.at(0, 2) = 3.0;
    symmetric.at(1, 0) = 2.0; symmetric.at(1, 1) = 4.0; symmetric.at(1, 2) = 5.0;
    symmetric.at(2, 0) = 3.0; symmetric.at(2, 1) = 5.0; symmetric.at(2, 2) = 6.0;
    
    Matrix nonSymmetric(3, 3);
    nonSymmetric.at(0, 0) = 1.0; nonSymmetric.at(0, 1) = 2.0;
    nonSymmetric.at(1, 0) = 3.0;
    
    CHECK(symmetric.isSymmetric());
    CHECK(!nonSymmetric.isSymmetric());
}

TEST(MatrixIsUpperTriangular) {
    Matrix upper(3, 3);
    upper.at(0, 0) = 1.0; upper.at(0, 1) = 2.0; upper.at(0, 2) = 3.0;
    upper.at(1, 1) = 4.0; upper.at(1, 2) = 5.0;
    upper.at(2, 2) = 6.0;
    
    Matrix nonUpper(3, 3);
    nonUpper.at(0, 0) = 1.0; nonUpper.at(0, 1) = 2.0;
    nonUpper.at(1, 0) = 0.5;
    
    CHECK(upper.isUpperTriangular());
    CHECK(!nonUpper.isUpperTriangular());
}

TEST(MatrixIsLowerTriangular) {
    Matrix lower(3, 3);
    lower.at(0, 0) = 1.0;
    lower.at(1, 0) = 2.0; lower.at(1, 1) = 3.0;
    lower.at(2, 0) = 4.0; lower.at(2, 1) = 5.0; lower.at(2, 2) = 6.0;
    
    Matrix nonLower(3, 3);
    nonLower.at(0, 0) = 1.0; nonLower.at(0, 1) = 0.5;
    
    CHECK(lower.isLowerTriangular());
    CHECK(!nonLower.isLowerTriangular());
}

TEST(MatrixTranspose) {
    Matrix m(2, 3);
    m.at(0, 0) = 1.0; m.at(0, 1) = 2.0; m.at(0, 2) = 3.0;
    m.at(1, 0) = 4.0; m.at(1, 1) = 5.0; m.at(1, 2) = 6.0;
    
    Matrix transposed = m.transpose();
    
    CHECK_EQUAL(3, transposed.getRows());
    CHECK_EQUAL(2, transposed.getCols());
    CHECK_EQUAL(1.0, transposed.at(0, 0));
    CHECK_EQUAL(4.0, transposed.at(0, 1));
    CHECK_EQUAL(2.0, transposed.at(1, 0));
    CHECK_EQUAL(5.0, transposed.at(1, 1));
    CHECK_EQUAL(3.0, transposed.at(2, 0));
    CHECK_EQUAL(6.0, transposed.at(2, 1));
}

TEST(MatrixLoadFromFile) {
    // Создаем тестовый файл
    std::ofstream file("test_matrix.txt");
    file << "2 3\n1.5 2.5 3.5\n4.5 5.5 6.5";
    file.close();
    
    Matrix m;
    m.loadFromFile("test_matrix.txt");
    
    CHECK_EQUAL(2, m.getRows());
    CHECK_EQUAL(3, m.getCols());
    CHECK_CLOSE(1.5, m.at(0, 0), 1e-9);
    CHECK_CLOSE(2.5, m.at(0, 1), 1e-9);
    CHECK_CLOSE(3.5, m.at(0, 2), 1e-9);
    CHECK_CLOSE(4.5, m.at(1, 0), 1e-9);
    CHECK_CLOSE(5.5, m.at(1, 1), 1e-9);
    CHECK_CLOSE(6.5, m.at(1, 2), 1e-9);
    
    // Удаляем тестовый файл
    std::remove("test_matrix.txt");
}

// Тесты исключений
TEST(MatrixAccessOutOfBounds) {
    Matrix m(2, 2);
    CHECK_THROW(m.at(2, 0), std::out_of_range);
    CHECK_THROW(m.at(0, 2), std::out_of_range);
}

TEST(MatrixSubmatrixOutOfBounds) {
    Matrix m(2, 2);
    CHECK_THROW(m.getSubmatrix(1, 1, 2, 2), std::out_of_range);
}

TEST(MatrixLoadFromNonExistentFile) {
    Matrix m;
    CHECK_THROW(m.loadFromFile("non_existent_file.txt"), std::runtime_error);
}
int main(){
    return UnitTest::RunAllTests();

}