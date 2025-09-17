#include <vector>
#include <queue>
#include <algorithm>

template <typename datatype>
class TreeNode
{
public:
    datatype val;
    TreeNode<datatype>* left;
    TreeNode<datatype>* right;

    TreeNode(datatype value) : val(value), left(nullptr), right(nullptr) {}
};

template <typename datatype>
class BST
{
private:
    TreeNode<datatype>* root;

    TreeNode<datatype>* insert(TreeNode<datatype>* node, datatype value)
    {
        if(!node) return new TreeNode<datatype>(value);

        if(value < node->val) node->left = insert(node->left, value);
        else if(value > node->val) node->right = insert(node->right, value);
        
        return node;
    }

    TreeNode<datatype>* remove(TreeNode<datatype>* node, datatype value)
    {
        if(!node) return nullptr;

        if(value < node->val) node->left = remove(node->left, value);
        else if(value > node->val) node->right = remove(node->right, value);
        else
        {
            if(!node->left)
            {
                TreeNode<datatype>* temp = node->right;
                delete node;
                return temp;
            }
            if(!node->right)
            {
                TreeNode<datatype>* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode<datatype>* minNode = node->right;

            while(minNode->left) minNode = minNode->left;
            node->val = minNode->val;
            node->right = remove(node->right, minNode->val);
        }

        return node;
    }

    bool find(TreeNode<datatype>* node, datatype value) const
    {
        if(!node) return false;

        if(node->val == value) return true;
        if(value < node->val) return find(node->left, value);
        else return find(node->right, value);
    }

    TreeNode<datatype>* findNode(TreeNode<datatype>* node, datatype value) const
    {
        if(!node || node->val == value) return node;
        if(value < node->val) return contain(node->left, value);
        else return contain(node->right, value);
    }

    size_t getHeight(TreeNode<datatype>* node) const
    {
        if(!node) return 0;

        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    bool isEmpty(TreeNode<datatype>* node) const { return node == nullptr; }

    void clear(TreeNode<datatype>* node)
    {
        if(!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }

    std::vector<datatype> preOrder(TreeNode<datatype>* node) const
    {
        if(!node) return {};

        std::vector<datatype> res;

        res.push_back(node->val);

        std::vector<datatype> left = preOrder(node->left);
        res.insert(res.end(), left.begin(), left.end());

        std::vector<datatype> right = preOrder(node->right);
        res.insert(res.end(), right.begin(), right.end());

        return res;
    }

    std::vector<datatype> inOrder(TreeNode<datatype>* node) const
    {
        if(!node) return {};

        std::vector<datatype> res;

        std::vector<datatype> left = inOrder(node->left);
        res.insert(res.end(), left.begin(), left.end());

        res.push_back(node->val);

        std::vector<datatype> right = inOrder(node->right);
        res.insert(res.end(), right.begin(), right.end());

        return res;
    }

    std::vector<datatype> postOrder(TreeNode<datatype>* node) const
    {
        if(!node) return {};

        std::vector<datatype> res;

        std::vector<datatype> left = postOrder(node->left);
        res.insert(res.end(), left.begin(), left.end());

        std::vector<datatype> right = postOrder(node->right);
        res.insert(res.end(), right.begin(), right.end());

        res.push_back(node->val);

        return res;
    }

    std::vector<std::vector<datatype>> levelOrder(TreeNode<datatype>* node) const
    {
        if(!node) return {};

        std::queue<TreeNode<datatype>*> q;
        std::vector<std::vector<datatype>> res;
        std::vector<datatype> path;
        q.push(node);

        while(!q.empty())
        {
            int size = q.size();
            for(int i = 0; i < size; i++)
            {
                TreeNode<datatype>* cur = q.front();
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

    void insert(datatype value) { root = insert(root, value); }

    void remove(datatype value) { root = remove(root, value); }

    bool find(datatype value) const { return find(root, value); }

    TreeNode<datatype>* findNode(datatype value) const { return contain(root, value); }

    std::vector<datatype> preOrder() const { return preOrder(root); }

    std::vector<datatype> inOrder() const { return inOrder(root); }

    std::vector<datatype> postOrder() const { return postOrder(root); }

    std::vector<std::vector<datatype>> levelOrder() const { return levelOrder(root); }

    void clear() { clear(root); }

    datatype Min()
    {
        if(!root)
            throw std::out_of_range("Tree is empty");

        TreeNode<datatype>* minNode = root;

        while(minNode->left) minNode = minNode->left;

        return minNode->val;
    }

    datatype Max()
    {
        if(!root)
            throw std::out_of_range("Tree is empty");

        TreeNode<datatype>* maxNode = root;

        while(maxNode->right) maxNode = maxNode->right;

        return maxNode->val;
    }

    ~BST() { clear(); }
};