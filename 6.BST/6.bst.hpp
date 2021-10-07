#include <memory>
#include <vector>
#include <iostream>
#include <optional>

template <typename T> class BST;

template <typename T> class Node
{
    private:
        const T val;
        std::unique_ptr<Node<T>> left_child;
        std::unique_ptr<Node<T>> right_child;
        Node<T>* parent;
        friend class BST<T>;

    public:
        Node(const T &val):
            val(val),
            left_child(nullptr),
            right_child(nullptr),
            parent(nullptr)
        {}
        T get_val() const {return val;};
        friend std::ostream& operator<<(std::ostream &os, const Node<T> &n)
        {
            os << "N(" << n.val << ")";
            return os;
        }
        Node<T>* successor() const;
        Node<T>* min_key();
        Node<T>* max_key();
        size_t depth() const;
        void print_in_order() const;
        inline bool operator==(const Node<T> &rhs) const;
        inline bool operator!=(const Node<T> &rhs) const;
};

template <typename T> class BST
{
    private:
        std::unique_ptr<Node<T>> head;
    public:
        BST():
            head(nullptr)
        {}
        BST(const std::vector<T> &arr);
        Node<T>* search(const T &val);
        Node<T>* insert(const T &val);
        bool empty() const;
        Node<T>* min_key();
        Node<T>* max_key();
        size_t depth() const;
        void print_in_order() const;
};

