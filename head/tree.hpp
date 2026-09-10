#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <stdexcept>
#include <utility>

template <typename T>
class BinaryTree {
private:
    // ==================== 节点结构 ====================
    struct Node {
        T data;
        Node* left;
        Node* right;

        explicit Node(const T& value)
            : data(value), left(nullptr), right(nullptr) {}

        explicit Node(T&& value)
            : data(std::move(value)), left(nullptr), right(nullptr) {}
    };

    Node* root_ = nullptr;
    size_t size_ = 0;

    // ==================== 内部辅助函数 ====================

    // 递归删除整棵子树
    static void destroy(Node* node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

    // 递归复制一棵树
    static Node* clone(const Node* node) {
        if (node == nullptr)
            return nullptr;

        Node* new_node = new Node(node->data);

        // 如果下面过程中出现异常，需要释放已经创建的节点
        try {
            new_node->left = clone(node->left);
            new_node->right = clone(node->right);
        }
        catch (...) {
            destroy(new_node);
            throw;
        }

        return new_node;
    }

    // 统计节点数量
    static size_t count_nodes(const Node* node) {
        if (node == nullptr)
            return 0;

        return 1 +
               count_nodes(node->left) +
               count_nodes(node->right);
    }

    // 计算树高
    static size_t height(const Node* node) {
        if (node == nullptr)
            return 0;

        return 1 + std::max(
            height(node->left),
            height(node->right)
        );
    }

    // 前序遍历
    static void preorder(
        const Node* node,
        const std::function<void(const T&)>& visit
    ) {
        if (node == nullptr)
            return;

        visit(node->data);
        preorder(node->left, visit);
        preorder(node->right, visit);
    }

    // 中序遍历
    static void inorder(
        const Node* node,
        const std::function<void(const T&)>& visit
    ) {
        if (node == nullptr)
            return;

        inorder(node->left, visit);
        visit(node->data);
        inorder(node->right, visit);
    }

    // 后序遍历
    static void postorder(
        const Node* node,
        const std::function<void(const T&)>& visit
    ) {
        if (node == nullptr)
            return;

        postorder(node->left, visit);
        postorder(node->right, visit);
        visit(node->data);
    }

    // 查找值
    static Node* find_node(Node* node, const T& value) {
        if (node == nullptr)
            return nullptr;

        if (node->data == value)
            return node;

        Node* result = find_node(node->left, value);

        if (result != nullptr)
            return result;

        return find_node(node->right, value);
    }

    static const Node* find_node(
        const Node* node,
        const T& value
    ) {
        if (node == nullptr)
            return nullptr;

        if (node->data == value)
            return node;

        const Node* result = find_node(node->left, value);

        if (result != nullptr)
            return result;

        return find_node(node->right, value);
    }

public:
    // ==================== 构造与析构 ====================

    BinaryTree() = default;

    ~BinaryTree() {
        clear();
    }

    // 拷贝构造
    BinaryTree(const BinaryTree& other)
        : root_(clone(other.root_)),
          size_(other.size_) {}

    // 移动构造
    BinaryTree(BinaryTree&& other) noexcept
        : root_(other.root_),
          size_(other.size_) {
        other.root_ = nullptr;
        other.size_ = 0;
    }

    // 拷贝赋值
    BinaryTree& operator=(const BinaryTree& other) {
        if (this == &other)
            return *this;

        BinaryTree temp(other);

        std::swap(root_, temp.root_);
        std::swap(size_, temp.size_);

        return *this;
    }

    // 移动赋值
    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this == &other)
            return *this;

        clear();

        root_ = other.root_;
        size_ = other.size_;

        other.root_ = nullptr;
        other.size_ = 0;

        return *this;
    }

    // ==================== 基本信息 ====================

    bool empty() const noexcept {
        return root_ == nullptr;
    }

    size_t size() const noexcept {
        return size_;
    }

    size_t height() const {
        return height(root_);
    }

    void clear() noexcept {
        destroy(root_);
        root_ = nullptr;
        size_ = 0;
    }

    // ==================== 根节点操作 ====================

    // 设置根节点
    void set_root(const T& value) {
        if (root_ != nullptr) {
            throw std::logic_error("root already exists");
        }

        root_ = new Node(value);
        size_ = 1;
    }

    void set_root(T&& value) {
        if (root_ != nullptr) {
            throw std::logic_error("root already exists");
        }

        root_ = new Node(std::move(value));
        size_ = 1;
    }

    // 获取根节点
    T& root() {
        if (root_ == nullptr)
            throw std::out_of_range("tree is empty");

        return root_->data;
    }

    const T& root() const {
        if (root_ == nullptr)
            throw std::out_of_range("tree is empty");

        return root_->data;
    }

    // ==================== 遍历 ====================

    // 前序：根 -> 左 -> 右
    void preorder(
        const std::function<void(const T&)>& visit
    ) const {
        preorder(root_, visit);
    }

    // 中序：左 -> 根 -> 右
    void inorder(
        const std::function<void(const T&)>& visit
    ) const {
        inorder(root_, visit);
    }

    // 后序：左 -> 右 -> 根
    void postorder(
        const std::function<void(const T&)>& visit
    ) const {
        postorder(root_, visit);
    }

    // 层序遍历：使用 queue
    void levelorder(
        const std::function<void(const T&)>& visit
    ) const {
        if (root_ == nullptr)
            return;

        std::queue<Node*> q;
        q.push(root_);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            visit(current->data);

            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }
    }

    // ==================== 转换成 vector ====================

    std::vector<T> preorder() const {
        std::vector<T> result;

        preorder([&result](const T& value) {
            result.push_back(value);
        });

        return result;
    }

    std::vector<T> inorder() const {
        std::vector<T> result;

        inorder([&result](const T& value) {
            result.push_back(value);
        });

        return result;
    }

    std::vector<T> postorder() const {
        std::vector<T> result;

        postorder([&result](const T& value) {
            result.push_back(value);
        });

        return result;
    }

    std::vector<T> levelorder() const {
        std::vector<T> result;

        levelorder([&result](const T& value) {
            result.push_back(value);
        });

        return result;
    }

    // ==================== 查找 ====================

    bool contains(const T& value) const {
        return find_node(root_, value) != nullptr;
    }

    T* find(const T& value) {
        Node* node = find_node(root_, value);

        if (node == nullptr)
            return nullptr;

        return &node->data;
    }

    const T* find(const T& value) const {
        const Node* node = find_node(root_, value);

        if (node == nullptr)
            return nullptr;

        return &node->data;
    }
};

#endif // BINARY_TREE_H
//谢谢gpt喵，谢谢gpt谢谢喵！