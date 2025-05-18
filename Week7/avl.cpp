#include <iostream>

struct NODE{
    int key, height;
    NODE* p_left;
    NODE* p_right;
};

// Tạo node
NODE* createNODE(int value){
    NODE* temp = new NODE;

    temp->key = value;
    temp->height = 0;
    temp->p_left = nullptr;
    temp->p_right = nullptr;

    return temp;
}

// Tính chiều cao (-1 nếu rỗng và height nếu không rỗng)
int height(NODE*& pRoot){
    return pRoot != nullptr ? pRoot->height : -1;
}

// Tính chỉ số cân bằng (chiều cao node con trái - chiều cao node con phải)
int balance_factor(NODE* pRoot){
    return pRoot != nullptr ? height(pRoot->p_left) - height(pRoot->p_right) : 0;
}

// Hàm phụ trợ tìm giá trị max
int max(int a, int b){
    return a > b ? a : b;
}

// Cập nhật chiều cao
void UpdateHeight(NODE*& pRoot){
    if (pRoot == nullptr){
        return;
    }

    // +1 cho chiều cao tối đa của cây con trái phải
    pRoot->height = (1 + max(height(pRoot->p_left), height(pRoot->p_right)));
}

// Xoay trái cho cây lệch phải
NODE* rotate_left(NODE*& x){
    // y là cây con phải của x
    NODE* y = x->p_right;

    // z là cây con trái của y
    NODE* z = y->p_left;

    // x trở thành cây con trái của y
    y->p_left = x;

    // z trở thành cây con phải của x 
    // Đảm bảo tính chất BST vì z lớn hơn x nhưng nhỏ hơn y
    x->p_right = z;

    // Cập nhật chiều cao từ dưới lên
    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

// Xoay phải cho cây lệch trái
NODE* rotate_right(NODE*& x){
    // y là cây con trái của x
    NODE* y = x->p_left;

    // z là cây con phải của y
    NODE* z = y->p_right;

    // x trở thành cây con phải của y
    y->p_right = x;

    // z trở thành cây con trái của z
    // Đảm bảo tính chất BST vì z lớn hơn y nhỏ hơn x
    x->p_left = z;

    // Cập nhật chiều cao từ dưới lên
    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

// Hàm xoay để tiện tái sử dụng
NODE* rotate(NODE* root){
    // Rỗng thì không thể xoay
    if (root == nullptr){
        return root;
    }

    // Tính chỉ số cân bằng để dễ debug
    int bf = balance_factor(root);

    // Nếu lệch trái
    if (bf > 1) {
        // Lệch LL
        if (balance_factor(root->p_left) >= 0)
            // Xoay phải
            return rotate_right(root);
        // Lệch LR
        else {
            // Xoay trái node con trái để đưa về lệch LL
            root->p_left = rotate_left(root->p_left);
            // Xoay phải
            return rotate_right(root);
        }
    }

    // Lệch phải
    if (bf < -1) {
        // Lệch RR
        if (balance_factor(root->p_right) <= 0)
            // Xoay trái
            return rotate_left(root);
        // Lệch RL
        else {
            // Xoay phải cây con phải đưa về lệch RR
            root->p_right = rotate_right(root->p_right);
            // Xoay phải
            return rotate_left(root);
        }
    }

    return root;
}

// Hàm chèn hoạt động như bình thường nhưng có thêm xoay sau khi chèn
void Insert(NODE*& pRoot, int x){
    // Rỗng thì tạo mới
    if (pRoot == nullptr){
        pRoot = createNODE(x);
        return;
    }

    // Nhỏ hơn thì qua phải
    if (pRoot->key < x){
        Insert(pRoot->p_right, x);
    }
    // Lớn hơn thì qua trái
    else if (pRoot->key > x){
        Insert(pRoot->p_left, x);
    }
    // Bằng tức là đã có node đó, trả về để bảo đảm tính chất BST
    else{
        std::cerr << "Existed value." << std::endl;
    }

    // Khác hơn so với chèn BST là có cập nhật chiều cao và xoay
    UpdateHeight(pRoot);
    pRoot = rotate(pRoot);
}

// Hàm xóa hoạt động như bình thường nhưng có thêm xoay
void Remove(NODE*& pRoot, int x){
    // Rỗng hoặc không tìm thấy thì không xóa được
    if (pRoot == nullptr){
        return;
    }

    // Lớn hơn thì qua phải
    if (pRoot->key > x){
        Remove(pRoot->p_left, x);
    }
    // Nhỏ hơn thì qua trái
    else if (pRoot->key < x){
        Remove(pRoot->p_right, x);
    }
    // Bằng thì xóa
    else{
        // Có một hoặc không có con thì dùng 1 logic để xử lý
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr){
            // Gán lấy node cũ để xóa
            NODE* temp = pRoot;
            // Lấy node không rỗng nếu cây có 1 con
            pRoot = pRoot->p_left != nullptr ? pRoot->p_left : pRoot->p_right;
            // Xóa node cũ
            delete temp;
        }
        // Nếu có 2 con
        else{
            // Lấy node con nhỏ nhất bên phải
            NODE* successor = pRoot->p_right;
            while (successor->p_left != nullptr){
                successor = successor->p_left;
            }

            // Gán giá trị cho node được xóa
            pRoot->key = successor->key;
            // Xóa node dùng để thế giá trị
            Remove(pRoot->p_right, pRoot->key);
        }
    }

    // Cập nhật chiều cao và xoay
    UpdateHeight(pRoot);
    pRoot = rotate(pRoot);
}

// Hàm kiểm tra xem cây có phải BST hay không
bool isBST(NODE* pRoot, int minVal, int maxVal){
    // Rỗng thì check tiếp
    if (pRoot == nullptr){
        return true;
    }

    // Nếu nhỏ hơn minVal hoặc lớn hơn maxVal thì false
    // Logic ở đây là khoanh vùng giá trị của cây
    // Nếu qua nhánh trái thì minVal là pRoot
    // Nếu qua nhánh phải thì maxVal là pRoot
    if (pRoot->key <= minVal || pRoot->key >= maxVal){
        return false;
    }

    return isBST(pRoot->p_left, minVal, pRoot->key) && isBST(pRoot->p_right, pRoot->key, maxVal);
}

// Hàm kiểm tra độ cao và tính cân bằng AVL, trả về độ cao của cây
int checkHeight(NODE* pRoot, bool &isBalanced){
    // Nếu rỗng thì -1 theo quy ước
    if (pRoot == nullptr){
        return -1;
    }

    // Tính chiều cao cây con trái
    int leftHeight = checkHeight(pRoot->p_left, isBalanced);

    // Tính chiều cao cây con phải
    int rightHeight = checkHeight(pRoot->p_right, isBalanced);

    // Nếu chiều cao trái và chiều cao phải chênh quá 1 -> mất cân bằng
    if (std::abs(leftHeight - rightHeight) > 1){
        isBalanced = false;
    }

    // Trả về giá trị chiều cao của node vừa duyệt
    return std::max(leftHeight, rightHeight) + 1;
}

// Hàm chính kiểm tra AVL
bool isAVLTree(NODE* pRoot){
    // Kiểm tra BST
    if (isBST(pRoot, INT_MIN, INT_MAX) == false){
        return false;
    }

    // Kiểm tra tính cân bằng
    bool isBalanced = true;
    checkHeight(pRoot, isBalanced);
    
    return isBalanced;
}
