#include <queue>
#include <vector>
#include <algorithm>

template <typename datatype>
class TreeNode
{
public:
    datatype val;
    int height;
    TreeNode<datatype>* left;
    TreeNode<datatype>* right;

    TreeNode(datatype value) : val(value), height(1), left(nullptr), right(nullptr) {}
};

template <typename datatype>
class AVLTree
{
public:
    int getHeight(TreeNode<datatype>* root)
    {
        return root ? root->height : 0;
    }

    int getBalance(TreeNode<datatype>* root)
    {
        if(!root) return 0;

        return getHeight(root->left) - getHeight(root->right);
    }

    TreeNode<datatype>* leftRotate(TreeNode<datatype>* root)
    {
        TreeNode<datatype>* newRoot = root->right;

        root->right = newRoot->left;
        newRoot->left = root;

        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    TreeNode<datatype>* rightRotate(TreeNode<datatype>* root)
    {
        TreeNode<datatype>* newRoot = root->left;

        root->left = newRoot->right;
        newRoot->right = root;

        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    TreeNode<datatype>* insert(TreeNode<datatype>* root, datatype val)
    {
        if(!root) 
            return new TreeNode<datatype>(val);

        if (val < root->val) root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);
        else return root;
    }

    std::vector<datatype> inorderTraversal(TreeNode<datatype>* root) 
    {
        std::vector<datatype> res;

        if (root) 
        {
            std::vector<datatype> left = inorderTraversal(root->left);
            res.insert(res.end(), left.begin(), left.end());

            res.push_back(root->val);

            std::vector<datatype> right = inorderTraversal(root->right);
            res.insert(res.end(), right.begin(), right.end());
        }

        return res;
    }

    std::vector<datatype> preOrderTraversal(TreeNode<datatype>* root) 
    {
        std::vector<datatype> res;

        if (root) 
        {
            res.push_back(root->val);

            std::vector<datatype> left = preOrderTraversal(root->left);
            res.insert(res.end(), left.begin(), left.end());

            std::vector<datatype> right = preOrderTraversal(root->right);
            res.insert(res.end(), right.begin(), right.end());
        }

        return res;
    }

    std::vector<datatype> postOrderTraversal(TreeNode<datatype>* root) 
    {
        std::vector<datatype> res;

        if (root) 
        {
            std::vector<datatype> left = postOrderTraversal(root->left);
            res.insert(res.end(), left.begin(), left.end());

            std::vector<datatype> right = postOrderTraversal(root->right);
            res.insert(res.end(), right.begin(), right.end());
            
            res.push_back(root->val);
        }

        return res;
    }

    std::vector<std::vector<datatype>> levelOrderTraversal(TreeNode<datatype>* root) 
    {
        std::vector<std::vector<datatype>> res;

        if (!root) return res;

        std::queue<TreeNode<datatype>*> q;
        q.push(root);

        while (!q.empty()) 
        {
            std::vector<datatype> level;
            int levelSize = q.size();
            
            for(int i = 0; i < levelSize; i++) 
            {
                TreeNode<datatype>* node = q.front();
                q.pop();

                level.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            res.push_back(level);
        }

        return res;
    }

     TreeNode<datatype>* remove(TreeNode<datatype>* root, datatype val)
    {
        if (!root) return nullptr;

        if (val < root->val)
            root->left = remove(root->left, val);
        else if (val > root->val)
            root->right = remove(root->right, val);
        else
        {
            if (!root->left || !root->right)
            {
                TreeNode<datatype>* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }
            TreeNode<datatype>* successor = minValueNode(root->right);
            root->val = successor->val;
            root->right = remove(root->right, successor->val);
        }


        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        return rebalanceAfterDelete(root);
    }

    TreeNode<datatype>* minValueNode(TreeNode<datatype>* node)
    {
        TreeNode<datatype>* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    TreeNode<datatype>* rebalance(TreeNode<datatype>* root, datatype val)
    {
        int bf = getBalance(root);

        if (bf > 1 && val < root->left->val)
            return rightRotate(root);
        if (bf > 1 && val > root->left->val)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (bf < -1 && val > root->right->val)
            return leftRotate(root);
        if (bf < -1 && val < root->right->val)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    TreeNode<datatype>* rebalanceAfterDelete(TreeNode<datatype>* root)
    {
        int bf = getBalance(root);

        if (bf > 1)
        {
            if (getBalance(root->left) >= 0)
                return rightRotate(root);
            else
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        else if (bf < -1)
        {
            if (getBalance(root->right) <= 0)
                return leftRotate(root);
            else
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }

        return root;
    }

    void clear(TreeNode<datatype>* root)
    {
        if (!root) return;
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }
};