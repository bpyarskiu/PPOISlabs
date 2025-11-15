#include "../include/Matrix.hpp"

// Вспомогательные приватные методы
void Matrix::clear() {
    if (data_ != nullptr) {
        for (size_t i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}

void Matrix::allocateMemory(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        data_ = nullptr;
        return;
    }
    
    data_ = new double*[rows];
    for (size_t i = 0; i < rows; ++i) {
        data_[i] = new double[cols](); // Инициализация нулями
    }
}

// Конструкторы и деструктор
Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(nullptr) {
    if (rows > 0 && cols > 0) {
        allocateMemory(rows, cols);
    }
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    if (rows_ > 0 && cols_ > 0) {
        allocateMemory(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                data_[i][j] = other.data_[i][j];
            }
        }
    }
}

Matrix::~Matrix() {
    clear();
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        Matrix temp(other);
        std::swap(rows_, temp.rows_);
        std::swap(cols_, temp.cols_);
        std::swap(data_, temp.data_);
    }
    return *this;
}

// Операторы инкремента/декремента
Matrix& Matrix::operator++() {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            ++data_[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    ++(*this);
    return temp;
}

Matrix& Matrix::operator--() {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            --data_[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator--(int) {
    Matrix temp(*this);
    --(*this);
    return temp;
}

// Основные методы
void Matrix::resize(size_t new_rows, size_t new_cols) {
    if (new_rows == rows_ && new_cols == cols_) {
        return;
    }

    // Создаем временную матрицу нового размера
    Matrix temp(new_rows, new_cols);
    
    // Копируем данные из старой матрицы
    size_t min_rows = std::min(rows_, new_rows);
    size_t min_cols = std::min(cols_, new_cols);
    
    for (size_t i = 0; i < min_rows; ++i) {
        for (size_t j = 0; j < min_cols; ++j) {
            temp.data_[i][j] = data_[i][j];
        }
    }
    
    // Заменяем текущую матрицу временной
    *this = temp;
}
/**
 * 
 */
void Matrix::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    size_t rows, cols;
    file >> rows >> cols;
    
    if (file.fail()) {
        throw std::runtime_error("Error reading matrix dimensions from file");
    }
    
    Matrix temp(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (!(file >> temp.data_[i][j])) {
                throw std::runtime_error("Error reading matrix data from file");
            }
        }
    }
    
    *this = temp;
}

Matrix Matrix::getSubmatrix(size_t start_row, size_t start_col, size_t sub_rows, size_t sub_cols) const {
    if (start_row + sub_rows > rows_ || start_col + sub_cols > cols_) {
        throw std::out_of_range("Submatrix dimensions exceed matrix bounds");
    }
    
    Matrix result(sub_rows, sub_cols);
    for (size_t i = 0; i < sub_rows; ++i) {
        for (size_t j = 0; j < sub_cols; ++j) {
            result.data_[i][j] = data_[start_row + i][start_col + j];
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result.data_[j][i] = data_[i][j];
        }
    }
    return result;
}

// Проверки типа матрицы
bool Matrix::isSquare() const {
    return rows_ == cols_;
}

bool Matrix::isZero() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (data_[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isIdentity() const {
    if (!isSquare()) return false;
    
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (i == j) {
                if (data_[i][j] != 1.0) return false;
            } else {
                if (data_[i][j] != 0.0) return false;
            }
        }
    }
    return true;
}

bool Matrix::isDiagonal() const {
    if (!isSquare()) return false;
    
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (i != j && data_[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isSymmetric() const {
    if (!isSquare()) return false;
    
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = i + 1; j < cols_; ++j) {
            if (data_[i][j] != data_[j][i]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isUpperTriangular() const {
    if (!isSquare()) return false;
    
    for (size_t i = 1; i < rows_; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (data_[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isLowerTriangular() const {
    if (!isSquare()) return false;
    
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = i + 1; j < cols_; ++j) {
            if (data_[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

// Методы доступа
double& Matrix::at(size_t i, size_t j) {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data_[i][j];
}

const double& Matrix::at(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data_[i][j];
}

// Вспомогательные методы
void Matrix::fill(double value) {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] = value;
        }
    }
}

void Matrix::print() const {
    std::cout << *this;
}

// Дружественная функция для вывода
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (size_t i = 0; i < m.rows_; ++i) {
        for (size_t j = 0; j < m.cols_; ++j) {
            os << m.data_[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}