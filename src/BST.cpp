#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept>


template <typename T>
class TreeNode
{
public:
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T value) : val(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST
{
private:
    TreeNode<T>* root;

    TreeNode<T>* insert(TreeNode<T>* node, T value)
    {
        if(!node) return new TreeNode<T>(value);

        if(value < node->val) node->left = insert(node->left, value);
        else if(value > node->val) node->right = insert(node->right, value);
        
        return node;
    }

    TreeNode<T>* remove(TreeNode<T>* node, T value)
    {
        if(!node) return nullptr;

        if(value < node->val) node->left = remove(node->left, value);
        else if(value > node->val) node->right = remove(node->right, value);
        else
        {
            if(!node->left)
            {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            if(!node->right)
            {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode<T>* minNode = node->right;

            while(minNode->left) minNode = minNode->left;
            node->val = minNode->val;
            node->right = remove(node->right, minNode->val);
        }

        return node;
    }

    bool find(TreeNode<T>* node, T value) const
    {
        if(!node) return false;

        if(node->val == value) return true;
        if(value < node->val) return find(node->left, value);
        else return find(node->right, value);
    }

    TreeNode<T>* findNode(TreeNode<T>* node, T value) const
    {
        if(!node || node->val == value) return node;
        if(value < node->val) return contain(node->left, value);
        else return contain(node->right, value);
    }

    size_t getHeight(TreeNode<T>* node) const
    {
        if(!node) return 0;

        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    bool isEmpty(TreeNode<T>* node) const { return node == nullptr; }

    void clear(TreeNode<T>* node)
    {
        if(!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }

    std::vector<T> preOrder(TreeNode<T>* node) const
    {
        if(!node) return {};

        std::vector<T> res;

        res.push_back(node->val);

        std::vector<T> left = preOrder(node->left);
        res.insert(res.end(), left.begin(), left.end());

        std::vector<T> right = preOrder(node->right);
        res.insert(res.end(), right.begin(), right.end());

        return res;
    }

    std::vector<T> inOrder(TreeNode<T>* node) const
    {
        if(!node) return {};

        std::vector<T> res;

        std::vector<T> left = inOrder(node->left);
        res.insert(res.end(), left.begin(), left.end());

        res.push_back(node->val);

        std::vector<T> right = inOrder(node->right);
        res.insert(res.end(), right.begin(), right.end());

        return res;
    }

    std::vector<T> postOrder(TreeNode<T>* node) const
    {
        if(!node) return {};

        std::vector<T> res;

        std::vector<T> left = postOrder(node->left);
        res.insert(res.end(), left.begin(), left.end());

        std::vector<T> right = postOrder(node->right);
        res.insert(res.end(), right.begin(), right.end());

        res.push_back(node->val);

        return res;
    }

    std::vector<std::vector<T>> levelOrder(TreeNode<T>* node) const
    {
        if(!node) return {};

        std::queue<TreeNode<T>*> q;
        std::vector<std::vector<T>> res;
        std::vector<T> path;
        q.push(node);

        while(!q.empty())
        {
            int size = q.size();
            for(int i = 0; i < size; i++)
            {
                TreeNode<T>* cur = q.front();
                q.pop();

                path.push_back(cur->val);

                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }

            res.emplace_back(path);
            path.clear();
        }

        return res;
    }
    
public:
    BST() : root(nullptr) {}

    bool isEmpty() const { return root == nullptr; }

    size_t getHeight() const { return getHeight(root); }

    void insert(T value) { root = insert(root, value); }

    void remove(T value) { root = remove(root, value); }

    bool find(T value) const { return find(root, value); }

    TreeNode<T>* findNode(T value) const { return contain(root, value); }

    std::vector<T> preOrder() const { return preOrder(root); }

    std::vector<T> inOrder() const { return inOrder(root); }

    std::vector<T> postOrder() const { return postOrder(root); }

    std::vector<std::vector<T>> levelOrder() const { return levelOrder(root); }

    void clear() { clear(root); }

    T Min()
    {
        if(!root)
            throw std::out_of_range("Tree is empty");

        TreeNode<T>* minNode = root;

        while(minNode->left) minNode = minNode->left;

        return minNode->val;
    }

    T Max()
    {
        if(!root)
            throw std::out_of_range("Tree is empty");

        TreeNode<T>* maxNode = root;

        while(maxNode->right) maxNode = maxNode->right;

        return maxNode->val;
    }

    ~BST() { clear(); }
};