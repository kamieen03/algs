#include "6.bst.hpp"

template <typename T> Node<T>* Node<T>::successor() const
{
    if (right_child)
    {
        return right_child->min_key();
    }
    else
    {
        Node<T>* N = parent;
        const Node<T>* current = this;
        while (N)
        {
            if (N->left_child && *current == *N->left_child)
            {
                return N;
            }
            else if (N->parent)
            {
                current = N;
                N = N->parent;
            }
            else
            {
                return nullptr;
            }
        }
    }
    return nullptr;
}

template <typename T> Node<T>* Node<T>::min_key()
{
    if (!left_child)
        return this;
    Node<T>* N = left_child.get();
    while (N)
    {
        if (N->left_child)
            N = N->left_child.get();
        else
            return N;
    }
    return nullptr;
}

template <typename T> Node<T>* Node<T>::max_key()
{
    if (!right_child)
        return this;
    Node<T>* N {right_child.get()};
    while (N)
    {
        if (N->right_child)
            N = N->right_child.get();
        else
            return N;
    }
    return nullptr;
}

template <typename T> size_t Node<T>::depth() const
{
    size_t left_d {0}, right_d {0};
    if (left_child)
        left_d  = left_child->depth();
    if (right_child)
        right_d = right_child->depth();
    return 1 + (left_d > right_d ? left_d : right_d);
}

template <typename T> void Node<T>::print_in_order() const
{
    if (left_child)
        left_child->print_in_order();
    std::cout << *this << " ";
    if (right_child)
        right_child->print_in_order();
}

template <typename T> bool Node<T>::operator==(const Node<T> &rhs) const
{
    return val == rhs.val;  // assuming Nodes are in the same tree
}

template <typename T> bool Node<T>::operator!=(const Node<T> &rhs) const
{
    return val != rhs.val;  // assuming Nodes are in the same tree
}


template <typename T> BST<T>::BST(const std::vector<T> &arr)
{
    for (const auto &x : arr)
        this->insert(x);
}

template <typename T> Node<T>* BST<T>::search(const T &val)
{
    Node<T>* N {head.get()};
    while (N)
    {
        if (val == N->get_val())
            return N;
        else if (val < N->get_val())
            N = N->left_child.get();
        else
            N = N->right_child.get();
    }
    return N;
}

template <typename T> Node<T>* BST<T>::insert(const T &val)
{
    if(!head)
    {
        head = std::make_unique<Node<T>>(val);
        return head.get();
    }

    Node<T>* N { head.get() };
    while (N)
    {
        if (val == N->get_val())    // keys should be unique
            return N;
        else if (val < N->get_val())
        {
            if (!N->left_child)
            {
                N->left_child = std::make_unique<Node<T>>(val);
                N->left_child->parent = N;
                return N->left_child.get();
            }
            else
            {
                N = N->left_child.get();
            }
        }
        else
        {
            if (!N->right_child)
            {
                N->right_child = std::make_unique<Node<T>>(val);
                N->right_child->parent = N;
                return N->right_child.get();
            }
            else
            {
                N = N->right_child.get();
            }
        }
    }
    return nullptr;
}

template <typename T> bool BST<T>::empty() const
{
    return head == nullptr;
}

template <typename T> Node<T>* BST<T>::min_key()
{
    if (!head) return nullptr;
    return head->min_key();
}

template <typename T> Node<T>* BST<T>::max_key()
{
    if (!head) return nullptr;
    return head->max_key();
}

template <typename T> size_t BST<T>::depth() const
{
    if (!head) return 0;
    return head->depth();
}

template <typename T> void BST<T>::print_in_order() const
{
    head->print_in_order();
    std::cout << std::endl;
}

template class BST<int>;

int main()
{
    std::vector<int> arr {4,2,7,8,3};
    BST<int> bst(arr);
    bst.search(1);
    bst.search(2);
    bst.insert(2);
    bst.insert(1);
    bst.insert(9);
    bst.print_in_order();
    std::cout << *bst.min_key() << " " << *bst.max_key() << std::endl;
    std::cout << bst.depth() << std::endl;
    auto N = bst.search(9);
    auto S = N->successor();
    if (S) std::cout << "Successor of " << *N << ": " << *S << std::endl;
    else std::cout << *N << " has no successor" << std::endl;
    return 0;
}
