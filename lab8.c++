#include <iostream>
#include <tuple>
#include <climits>
#include <vector>

using namespace std;


typedef int MyType;
class TreeNode{
    public:
        TreeNode(): data(0), left(nullptr), right(nullptr){}
        TreeNode(int d) : data(d), left(nullptr), right(nullptr){}
        ~TreeNode(){}
        int data;
        TreeNode* left;
        TreeNode* right;
};

void DestroyTree(TreeNode *root){
    if(root != nullptr){
        DestroyTree(root->left);
        DestroyTree(root->right);
        delete root;
    }
}

int CountNodes(TreeNode* root){
    if(!root){
        return 0;
    }else{
        int count = 1;
        count += CountNodes(root->left);
        count += CountNodes(root->right);
        return count;
    }
}

void PrintNode(TreeNode* root){
    cout << root->data << " ";
}



int MaxDepthTree(TreeNode* root){
    if(root == nullptr){
        return 0;
    }else if((root->left == nullptr) && (root->right == nullptr)){
        return 0;
    }else{
        //compute the depth of each subtree
        int leftDepth = MaxDepthTree(root->left);
        int rightDepth = MaxDepthTree(root->right);
        //use the larger subtree
        if(leftDepth > rightDepth){
            return leftDepth + 1;
        }else{
            return rightDepth + 1;
        }
    }
}

int GetNumberNodesGivenLevel(TreeNode* root, int level){
    if(root != nullptr){
        if(level ==0){
            return 1;
        }else{
            return GetNumberNodesGivenLevel(root->left, level -1) + 
                    GetNumberNodesGivenLevel(root->right, level -1);
        }
    }else{
        return 0;
    }
}

void GetNumberNodesLevel(TreeNode* root){
    int h = MaxDepthTree(root);
    int i;
    for(i = 0; i <= h; i++){
        cout << "level: " << i << " with "
            << GetNumberNodesGivenLevel(root, i) << " nodes" << endl;
    }
}

void InsertNode1(TreeNode* &root, MyType data){
    if(root == nullptr){
        root = new TreeNode(data);
    }else if(root->data == data){
        cout << "Value already in the tree." << endl;
    }else if(data < root->data){
        InsertNode1(root->left, data);
    }else{
        InsertNode1(root->right, data);
    }
}

TreeNode* FindMinNode(TreeNode *root){
    if(root == nullptr){
        return nullptr;
    }
    if(root->left != nullptr){
        return FindMinNode(root->left); //left is smaller
    }
    return root;
}

TreeNode* DeleteNode(TreeNode *root, MyType data){
    if(root == nullptr){
        return nullptr;
    }
    if(data < root->data){
        root->left = DeleteNode(root->left, data);
    }else if(data > root->data){
        root->right = DeleteNode(root->right, data);
    }else{
        //case 1 no children
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
        }else if(root->left == nullptr){
            TreeNode *temp = root;
            root = root->right;
            delete temp;
        }else if(root->right == nullptr){
            TreeNode *temp = root;
            root = root->left;
            delete temp;
        }else{
            //find minial value of right sub tree
            TreeNode *temp = FindMinNode(root->right);
            root->data = temp->data; //duplicate node
            //Delete the duplicate node
            root->right = DeleteNode(root->right, temp->data);
        }
    }
    return root;
}

TreeNode* RightRotate(TreeNode* root){
    if(root == nullptr || root->left == nullptr) return root;
    TreeNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

TreeNode* LeftRotate(TreeNode* root){
    if(root == nullptr || root->right == nullptr) return root;
    TreeNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}


void PrintGivenLevel(TreeNode* root, int lvl){
    if(root != nullptr){
        if(lvl == 0){
            cout << "_" << root->data << "_";
        }else{
            PrintGivenLevel(root->left, lvl -1);
            PrintGivenLevel(root->right, lvl -1);
        }
    }
}

void PrintLevelOrder(TreeNode* root){
    int h = MaxDepthTree(root);
    int i;
    for(i = 0; i <= h; i++){
        PrintGivenLevel(root, i);
        //at each line we have max 2^h
        cout << endl;
    }
}

class MyBST{
    public:
        MyBST(){ root = nullptr; }
        ~MyBST(){ DestroyTree(root); }

        void Insert(int data) { InsertNode1(root, data);}
        void Delete(int data){ root = DeleteNode(root, data);}


        void PrintLevelorder(){ PrintLevelOrder(root);}
        void PrintGetNumberNodesLevel(){ GetNumberNodesLevel(root);}

        int Height() { return MaxDepthTree(root);}
        int size(){ return CountNodes(root);}
        void RotateRight() { root = RightRotate(root);}
        void RotateLeft() { root = LeftRotate(root);}

    private:   
        TreeNode* root; 


};

void TestRotation(const string& name, const vector<int>& elements) {
    cout << "\nTesting sequence: " << name << endl;
    MyBST t;
    for (int val : elements) {
        t.Insert(val);
    }
    
    cout << "Before rotation:" << endl;
    t.PrintLevelorder();
    
    if (elements.size() == 3) {
        if (elements[1] < elements[0] && elements[2] > elements[0]) {
            cout << "\nAfter right rotation on root:" << endl;
            t.RotateRight();
            t.PrintLevelorder();
        } else if (elements[1] > elements[0] && elements[2] < elements[0]) {
            cout << "\nAfter left rotation on root:" << endl;
            t.RotateLeft();
            t.PrintLevelorder();
        } else if (elements[1] < elements[0] && elements[2] < elements[0]) {
            cout << "\nAfter right rotation on root:" << endl;
            t.RotateRight();
            t.PrintLevelorder();
        } else if (elements[1] > elements[0] && elements[2] > elements[0]) {
            cout << "\nAfter left rotation on root:" << endl;
            t.RotateLeft();
            t.PrintLevelorder();
        }
    }
}

int main(){
    TestRotation("20,10,15", {20, 10, 15});
    TestRotation("10,5,1", {10, 5, 1});
    TestRotation("10,20,30", {10, 20, 30});
    TestRotation("10,20,50", {10, 20, 50});

    return 0;
}