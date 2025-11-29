#pragma once
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>

template<typename T>
class SimpleSet {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    size_t size_;
    
    // Вспомогательные методы
    bool insertRecursive(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return true;
        }
        
        if (value < node->value) {
            return insertRecursive(node->left, value);
        } else if (value > node->value) {
            return insertRecursive(node->right, value);
        }
        
        return false;
    }
    
    bool containsRecursive(const std::unique_ptr<Node>& node, const T& value) const {
        if (!node) return false;
        
        if (value == node->value) return true;
        if (value < node->value) return containsRecursive(node->left, value);
        return containsRecursive(node->right, value);
    }
    
    void inOrderRecursive(const std::unique_ptr<Node>& node, 
                         std::function<void(const T&)> callback) const {
        if (!node) return;
        
        inOrderRecursive(node->left, callback);
        callback(node->value);
        inOrderRecursive(node->right, callback);
    }
    
    std::unique_ptr<Node> copyRecursive(const std::unique_ptr<Node>& node) const {
        if (!node) return nullptr;
        
        auto newNode = std::make_unique<Node>(node->value);
        newNode->left = copyRecursive(node->left);
        newNode->right = copyRecursive(node->right);
        
        return newNode;
    }
    
    std::unique_ptr<Node> removeRecursive(std::unique_ptr<Node> node, const T& value, bool& removed) {
        if (!node) return nullptr;

        if (value < node->value) {
            node->left = removeRecursive(std::move(node->left), value, removed);
        } else if (value > node->value) {
            node->right = removeRecursive(std::move(node->right), value, removed);
        } else {
            // Найден узел для удаления
            removed = true;
            if (!node->left) return std::move(node->right);
            if (!node->right) return std::move(node->left);

            // У узла два потомка - находим минимальный в правом поддереве
            Node* minNode = findMin(node->right.get());
            node->value = minNode->value;
            node->right = removeRecursive(std::move(node->right), minNode->value, removed);
        }
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }
public:
    SimpleSet() : root(nullptr), size_(0) {}
    
    SimpleSet(const SimpleSet& other) : size_(other.size_) {
        root = copyRecursive(other.root);
    }
    
    SimpleSet(SimpleSet&& other) noexcept 
        : root(std::move(other.root)), size_(other.size_) {
        other.size_ = 0;
    }
    
    ~SimpleSet() = default;
    
    SimpleSet& operator=(const SimpleSet& other) {
        if (this != &other) {
            clear();
            root = copyRecursive(other.root);
            size_ = other.size_;
        }
        return *this;
    }
    
    SimpleSet& operator=(SimpleSet&& other) noexcept {
        if (this != &other) {
            clear();
            root = std::move(other.root);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Основные методы
    bool insert(const T& value) {
        if (contains(value)) {
            return false;
        }
        bool result = insertRecursive(root, value);
        if (result) size_++;
        return result;
    }
    
     // Удаление элемента
    bool remove(const T& value) {
        bool removed = false;
        root = removeRecursive(std::move(root), value, removed);
        if (removed) size_--;
        return removed;
    }

    bool contains(const T& value) const {
        return containsRecursive(root, value);
    }
    
    size_t size() const {
        return size_;
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    void clear() {
        root.reset();
        size_ = 0;
    }
    
    // Для итерации
    void forEach(std::function<void(const T&)> callback) const {
        inOrderRecursive(root, callback);
    }
    
    // Операторы сравнения
    bool operator==(const SimpleSet& other) const {
        if (size_ != other.size_) return false;
        
        std::vector<T> thisElements, otherElements;
        
        forEach([&](const T& value) {
            thisElements.push_back(value);
        });
        
        other.forEach([&](const T& value) {
            otherElements.push_back(value);
        });
        
        std::sort(thisElements.begin(), thisElements.end());
        std::sort(otherElements.begin(), otherElements.end());
        
        return thisElements == otherElements;
    }
    
    bool operator<(const SimpleSet& other) const {
        std::vector<T> thisElements, otherElements;
        
        forEach([&](const T& value) {
            thisElements.push_back(value);
        });
        
        other.forEach([&](const T& value) {
            otherElements.push_back(value);
        });
        
        std::sort(thisElements.begin(), thisElements.end());
        std::sort(otherElements.begin(), otherElements.end());
        
        return thisElements < otherElements;
    }

   

    // Операции над множествами
    SimpleSet operator+(const SimpleSet& other) const { // Объединение
        SimpleSet result = *this;
        other.forEach([&](const T& value) {
            result.insert(value);
        });
        return result;}

    SimpleSet& operator+=(const SimpleSet& other) {
        other.forEach([this](const T& value) {
            insert(value);
        });
        return *this;
    }

    SimpleSet operator*(const SimpleSet& other) const { // Пересечение
        SimpleSet result;
        forEach([&](const T& value) {
            if (other.contains(value)) {
                result.insert(value);
            }
        });
        return result;}

    SimpleSet& operator*=(const SimpleSet& other) {
        SimpleSet result;
        forEach([&](const T& value) {
            if (other.contains(value)) {
                result.insert(value);
            }
        });
        *this = result;
        return *this;
    }

    SimpleSet operator-(const SimpleSet& other) const { // Разность
        SimpleSet result;
        forEach([&](const T& value) {
            if (!other.contains(value)) {
                result.insert(value);
            }
        });
        return result;}

    SimpleSet& operator-=(const SimpleSet& other) {
        SimpleSet result;
        forEach([&](const T& value) {
            if (!other.contains(value)) {
                result.insert(value);
            }
        });
        *this = result;
        return *this;
    }
};

// Специализация для std::unique_ptr<T>
template<typename T>
class SimpleSet<std::unique_ptr<T>>  {
private:
    struct Node {
        std::unique_ptr<T> value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        Node(std::unique_ptr<T> val) : value(std::move(val)), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    size_t size_;
    
    // Вспомогательные методы
    bool insertRecursive(std::unique_ptr<Node>& node, std::unique_ptr<T> value) {
        if (!node) {
            node = std::make_unique<Node>(std::move(value));
            return true;
        }
        
        if (*value < *node->value) {
            return insertRecursive(node->left, std::move(value));
        } else if (*value > *node->value) {
            return insertRecursive(node->right, std::move(value));
        }
        
        return false;}
    
    bool containsRecursive(const std::unique_ptr<Node>& node, const T& value) const {
        if (!node) return false;
        
        if (value == *node->value) return true;
        if (value < *node->value) return containsRecursive(node->left, value);
        return containsRecursive(node->right, value);
    }
    
    void inOrderRecursive(const std::unique_ptr<Node>& node, 
                         std::function<void(const std::unique_ptr<T>&)> callback) const {
        if (!node) return;
        
        inOrderRecursive(node->left, callback);
        callback(node->value);
        inOrderRecursive(node->right, callback);
    }
    
    std::unique_ptr<Node> copyRecursive(const std::unique_ptr<Node>& node) const {
        if (!node) return nullptr;
        
        auto new_value = std::make_unique<T>(*node->value);
        auto newNode = std::make_unique<Node>(std::move(new_value));
        newNode->left = copyRecursive(node->left);
        newNode->right = copyRecursive(node->right);
        return newNode;}

    std::unique_ptr<Node> removeRecursive(std::unique_ptr<Node> node, const T& value, bool& removed) {
        if (!node) return nullptr;

        if (value < *node->value) {
            node->left = removeRecursive(std::move(node->left), value, removed);
        } else if (value > *node->value) {
            node->right = removeRecursive(std::move(node->right), value, removed);
        } else {
            // Найден узел для удаления
            removed = true;
            if (!node->left) return std::move(node->right);
            if (!node->right) return std::move(node->left);

            // У узла два потомка - находим минимальный в правом поддереве
            Node* minNode = findMin(node->right.get());
            node->value = std::make_unique<T>(*minNode->value);
            node->right = removeRecursive(std::move(node->right), *minNode->value, removed);
        }
        return node;}

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;}
    
public:
    SimpleSet() : root(nullptr), size_(0) {}
    
    SimpleSet(const SimpleSet& other) : size_(other.size_) {
        root = copyRecursive(other.root);
    }
    
    SimpleSet(SimpleSet&& other) noexcept 
        : root(std::move(other.root)), size_(other.size_) {
        other.size_ = 0;
    }
    
    ~SimpleSet() = default;
    
    SimpleSet& operator=(const SimpleSet& other) {
        if (this != &other) {
            clear();
            root = copyRecursive(other.root);
            size_ = other.size_;
        }
        return *this;
    }
    
    SimpleSet& operator=(SimpleSet&& other) noexcept {
        if (this != &other) {
            clear();
            root = std::move(other.root);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    bool insert(std::unique_ptr<T> value) {
        if (contains(*value)) {
            return false;
        }
        bool result = insertRecursive(root, std::move(value));
        if (result) size_++;
        return result;}
    
    bool remove(const T& value) {
        bool removed = false;
        root = removeRecursive(std::move(root), value, removed);
        if (removed) size_--;
        return removed;
    }

    bool contains(const T& value) const {
        return containsRecursive(root, value);
    }
    
    size_t size() const {
        return size_;
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    void clear() {
        root.reset();
        size_ = 0;
    }
    
    void forEach(std::function<void(const std::unique_ptr<T>&)> callback) const {
        inOrderRecursive(root, callback);
    }
    
    bool operator==(const SimpleSet& other) const {
        if (size_ != other.size_) return false;
        
        // Для сравнения множеств указателей, мы сравниваем сами объекты
        std::vector<T> thisElements, otherElements;
        
        forEach([&](const std::unique_ptr<T>& value) {
            thisElements.push_back(*value);
        });
        
        other.forEach([&](const std::unique_ptr<T>& value) {
            otherElements.push_back(*value);
        });
        
        std::sort(thisElements.begin(), thisElements.end());
        std::sort(otherElements.begin(), otherElements.end());
        
        return thisElements == otherElements;
    }
    
    bool operator<(const SimpleSet& other) const {
        std::vector<T> thisElements, otherElements;
        
        forEach([&](const std::unique_ptr<T>& value) {
            thisElements.push_back(*value);
        });
        
        other.forEach([&](const std::unique_ptr<T>& value) {
            otherElements.push_back(*value);
        });
        
        std::sort(thisElements.begin(), thisElements.end());
        std::sort(otherElements.begin(), otherElements.end());
        
        return thisElements < otherElements;
    }
    bool operator>(const SimpleSet& other) const{
        return !(*this < other);
    }
    
    SimpleSet operator+(const SimpleSet& other) const { // Объединение
        SimpleSet result = *this;
        other.forEach([&](const std::unique_ptr<T>& value) {
            if (!result.contains(*value)) {
                result.insert(std::make_unique<T>(*value));
            }
        });
        return result;
    }

    SimpleSet& operator+=(const SimpleSet& other) {
        other.forEach([this](const std::unique_ptr<T>& value) {
            if (!contains(*value)) {
                insert(std::make_unique<T>(*value));
            }
        });
        return *this;
    }

    SimpleSet operator*(const SimpleSet& other) const { // Пересечение
        SimpleSet result;
        forEach([&](const std::unique_ptr<T>& value) {
            if (other.contains(*value)) {
                result.insert(std::make_unique<T>(*value));
            }
        });
        return result;
    }

    SimpleSet& operator*=(const SimpleSet& other) {
        SimpleSet result;
        forEach([&](const std::unique_ptr<T>& value) {
            if (other.contains(*value)) {
                result.insert(std::make_unique<T>(*value));
            }
        });
        *this = result;
        return *this;
    }

    SimpleSet operator-(const SimpleSet& other) const { // Разность
        SimpleSet result;
        forEach([&](const std::unique_ptr<T>& value) {
            if (!other.contains(*value)) {
                result.insert(std::make_unique<T>(*value));
            }
        });
        return result;
    }

    SimpleSet& operator-=(const SimpleSet& other) {
        SimpleSet result;
        forEach([&](const std::unique_ptr<T>& value) {
            if (!other.contains(*value)) {
                result.insert(std::make_unique<T>(*value));
            }
        });
        *this = result;
        return *this;
    }
};