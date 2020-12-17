#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>

template <typename KEY, typename VAL>
struct node
{
    KEY key;
    VAL value;
    node *left;
    node *right;
    node *father;
};

template <typename K, typename V>
class map
{
public:
    map();
    ~map();
    map(const map &other);
    void insert(K key, V value);
    void erase(K key);
    bool contains(K key) const;
    void clear();
    void printAscending() const;
    void returnAscending(node<K, V> nodes[]) const;
    int getSize() const { return size; };
    void read(const std::string &path);
    void write(const std::string &path) const;
    const V &operator[](K key) const;
    bool operator==(const map &other) const;

private:
    void writeNode(std::ostream &out, node<K, V> *leaf) const;
    void deleteTree(node<K, V> *&leaf);
    void insert(K key, V value, node<K, V> *leaf);
    void insertTree(node<K, V> *leaf);
    node<K, V> *find(K key) const;
    node<K, V> *find(K key, node<K, V> *leaf) const;
    void printAscending(node<K, V> *leaf) const;
    void returnAscending(node<K, V> nodes[], int *n, node<K, V> *leaf) const;

    node<K, V> *root;
    int size;
};

template <typename K, typename V>
map<K, V>::map()
{
    root = NULL;
    size = 0;
}

template <typename K, typename V>
map<K, V>::~map()
{
    clear();
}

template<typename K, typename V>
map<K, V>::map(const map &other)
{
    root = NULL;
    size = 0;
    insertTree(other.root);
}

template <typename K, typename V>
void map<K, V>::deleteTree(node<K, V> *&leaf)
{
    if (leaf != NULL) {
        deleteTree(leaf->left);
        deleteTree(leaf->right);
        if (leaf->father != NULL) {
            if (leaf->key < leaf->father->key)
                leaf->father->left = NULL;
            else
                leaf->father->right = NULL;
        } else {
            root->father = NULL;
            root->left = NULL;
            root->right = NULL;
            root = NULL;
        }
        delete leaf;
        leaf = NULL;
        size--;
    }
}

template <typename K, typename V>
void map<K, V>::insert(K key, V value, node<K, V> *leaf)
{
    if (key < leaf->key) {
        if (leaf->left != NULL){
            insert(key, value, leaf->left);
        } else {
            leaf->left = new node<K, V>;
            leaf->left->key = key;
            leaf->left->value = value;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
            leaf->left->father = leaf;
            size++;
        }
    } else if (key > leaf->key) {
        if (leaf->right != NULL) {
            insert(key, value, leaf->right);
        } else {
            leaf->right = new node<K, V>;
            leaf->right->key = key;
            leaf->right->value = value;
            leaf->right->right = NULL;
            leaf->right->left = NULL;
            leaf->right->father = leaf;
            size++;
        }
    }
}

template <typename K, typename V>
void map<K, V>::insert(K key, V value)
{
    if(root != NULL) {
        insert(key, value, root);
    } else {
        root = new node<K, V>;
        root->key = key;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        root->father = NULL;
        size++;
    }
}

template<typename K, typename V>
void map<K, V>::insertTree(node<K, V> *leaf)
{
    if (leaf == NULL)
        return;
    insert(leaf->key, leaf->value);
    insertTree(leaf->left);
    insertTree(leaf->right);
}

template<typename K, typename V>
void map<K, V>::erase(K key)
{
    node<K, V> *nodeToErase = find(key);
    if (nodeToErase == NULL) {
        return;
    }
    node<K, V> *leftTree = nodeToErase->left;
    node<K, V> *rightTree = nodeToErase->right;
    if (nodeToErase->father != NULL) {
        if (nodeToErase->key < nodeToErase->father->key)
            nodeToErase->father->left = NULL;
        else
            nodeToErase->father->right = NULL;
    } else {
        root = NULL;
    }
    insertTree(leftTree);
    insertTree(rightTree);
    deleteTree(leftTree);
    deleteTree(rightTree);
    size--;
}

template <typename K, typename V>
node<K, V> *map<K, V>::find(K key, node<K, V> *leaf) const
{
    if(leaf != NULL){
        if(key == leaf->key) {
            return leaf;
        }
        if(key < leaf->key) {
            return find(key, leaf->left);
        } else {
            return find(key, leaf->right);
        }
    } else {
        return NULL;
    }
}

template <typename K, typename V>
node<K, V> *map<K, V>::find(K key) const
{
    return find(key, root);
}

template<typename K, typename V>
bool map<K, V>::contains(K key) const
{
    if (find(key) == NULL)
        return false;
    return true;
}

template <typename K, typename V>
void map<K, V>::clear(){
    deleteTree(root);
    if (root != NULL)
        delete root;
    root = NULL;
    size = 0;
}

template <typename K, typename V>
void map<K, V>::printAscending() const
{
    printAscending(root);
    std::cout << "\n";
}

template<typename K, typename V>
void map<K, V>::returnAscending(node<K, V> nodes[]) const
{
    int n = 0;
    returnAscending(nodes, &n, root);
}

template<typename K, typename V>
void map<K, V>::returnAscending(node<K, V> nodes[], int *n, node<K, V> *leaf) const
{
    if (leaf != NULL) {
        returnAscending(nodes, n, leaf->left);
        nodes[*n].key = leaf->key;
        nodes[*n].value = leaf->value;
        (*n)++;
        returnAscending(nodes, n, leaf->right);
    }
}

template<typename K, typename V>
void map<K, V>::read(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        std::cout << "Cannot open file.\n";
    K key;
    V value;
    clear();
    while (!file.eof()) {
        file >> key;
        std::getline(file, value);
        value = value.substr(1, value.size()-1);
        insert(key, value);
    }
    file.close();
}

template<typename K, typename V>
void map<K, V>::write(const std::string &path) const
{
    std::ofstream file(path);
    if (!file.is_open())
        std::cout << "Cannot open file.\n";
    writeNode(file, root);
    file.close();
}

template<typename K, typename V>
const V &map<K, V>::operator[](K key) const
{
    node<K, V> *n = find(key);
    if (n == NULL)
        throw 1;
    return n->value;
}

template<typename K, typename V>
bool map<K, V>::operator==(const map &other) const
{
    return 1;
}

template<typename K, typename V>
void map<K, V>::writeNode(std::ostream &out, node<K, V> *leaf) const
{
    if (leaf == NULL)
        return;
    out << leaf->key << ' ' << leaf->value << '\n';
    writeNode(out, leaf->left);
    writeNode(out, leaf->right);
}

template <typename K, typename V>
void map<K, V>::printAscending(node<K, V> *leaf) const
{
    if (leaf != NULL) {
        printAscending(leaf->left);
        std::cout << leaf->key << ": " << leaf->value << "\n";
        printAscending(leaf->right);
    }
}

#endif // MAP_H
