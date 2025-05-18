#include <iostream>

struct NODE{
    int key;
    NODE* p_left = nullptr;
    NODE* p_right = nullptr;
};

// Tạo node
NODE* createNode(int data){
    NODE* temp = new NODE;

    temp->key = data;
    temp->p_left = nullptr;
    temp->p_right = nullptr;

    return temp;
}

// Tìm kiếm
NODE* Search(NODE* pRoot, int x){
    // Nếu rỗng hoặc tìm thấy thì trả về chính nó
    if (pRoot == nullptr || pRoot->key == x){
        return pRoot;
    }

    // Nhỏ hơn giá trị cần tìm thì duyệt qua phải
    if (pRoot->key < x){
        return Search(pRoot->p_right, x);
    }
    // Lớn hơn giá trị cần tìm thì duyệt qua trái
    else{
        return Search(pRoot->p_left, x);
    }
}

// Chèn
void Insert(NODE*& pRoot, int x){
    // Rỗng thì khởi tạo
    if (pRoot == nullptr){
        pRoot = createNode(x);
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
        return;
    }
}

// Xóa
void Delete(NODE*& pRoot, int x){
    // Nếu cây rỗng -> trả về
    if (pRoot == nullptr){
        return;
    }

    // Lớn hơn thì qua trái
    if (pRoot->key > x){
        Delete(pRoot->p_left, x);
    }
    // Nhỏ hơn qua phải
    else if (pRoot->key < x){
        Delete(pRoot->p_right, x);
    }
    // Tìm thấy
    else{
        // Nếu node có 1 hoặc 0 con
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr){
            // Lấy node cũ
            NODE* temp = pRoot;
            
            // Gán cho root node không null hoặc node phải nếu cả 2 null
            pRoot = pRoot->p_left != nullptr ? pRoot->p_left : pRoot->p_right;

            // Xóa node cũ
            delete temp;
        }
        // Nếu node có 2 con
        else{
            // Lấy con nhỏ nhất bên phải
            NODE* successor = pRoot->p_right;
            while (successor != nullptr){
                successor = successor->p_left;
            }

            // Gán giá trị cho node được xóa
            pRoot->key = successor->key;

            // Xóa node vừa bị lấy giá trị
            Delete(pRoot->p_right, successor->key);
        }
    }
}

// Tạo cây từ mảng
NODE* createTree(int a[], int n){
    NODE* pRoot = nullptr;

    // Duyệt từ đầu đến cuối mảng và insert từng số
    for (size_t i = 0; i < n; i++){
        Insert(pRoot, a[i]);
    }

    return pRoot;
}

// Xóa cây
void removeTree(NODE* & pRoot){
    // Xóa theo kiểu Post-order
    if (pRoot == nullptr){
        return;
    }

    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

// Hàm phụ trợ tính chiều cao
int height(NODE* pRoot){
    // Nếu root rỗng thì cây hoặc không có phần tử nào hoặc không tìm thấy giá trị 
    // Trả về -1 vì yêu cầu đề đã cộng 1 ở đệ quy dưới
    if (pRoot == nullptr){
        return -1;
    }

    // Cộng thêm cho max của chiều cao 2 cây con
    if (height(pRoot->p_left) > height(pRoot->p_right)){
        return 1 + height(pRoot->p_left);
    }
    else{
        return 1 + height(pRoot->p_right);
    }
}

// Tính chiều cao node
int heightNode(NODE* pRoot, int value){
    // Nếu cây rỗng trả về -1
    if (pRoot == nullptr){
        return -1;
    }

    // Nếu thấy value thì trả về height
    if (pRoot->key == value){
        return height(pRoot);
    }

    // Gọi biến tạm để lưu giá trị thuận tiện xét đệ quy
    // Giá trị được lưu ở đây là chiều cao của cây con trái
    int left_value = heightNode(pRoot->p_left, value);

    // Lúc đệ quy lại nếu không tìm thấy node value thì sẽ trả về -1 nên nếu
    // left_value khác -1 thì tức là đã tìm thấy
    if (left_value != -1){
        return left_value;
    }

    // Chạy tới đây tức là cây con trái không có value, kiểm tra cây con phải
    return heightNode(pRoot->p_right, value);
}

// Đếm số node
int countNode(NODE* pRoot){
    // Node là null thì không tăng thêm
    if (pRoot == nullptr){
        return 0;
    }

    // Đệ quy qua cây con trái và cây con phải nếu node không là null
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// Đếm số node bên trái -> đếm số node nhỏ hơn giá tị x
int countLess(NODE* pRoot, int x) {
    if (pRoot == nullptr){
        return 0;
    }

    if (pRoot->key < x) {
        // Node hiện tại được tính, tiếp tục đếm ở cả hai nhánh
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    } else {
        // Node hiện tại và nhánh phải >= x, chỉ cần xét nhánh trái
        return countLess(pRoot->p_left, x);
    }
}

// Đếm số node bên phải -> lớn hơn giá trị x
int countGreater(NODE* pRoot, int x) {
    if (pRoot == nullptr){
        return 0;
    }

    if (pRoot->key > x) {
        // Node hiện tại được tính, tiếp tục đếm ở cả hai nhánh
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    } else {
        // Node hiện tại và nhánh trái <= x, chỉ cần xét nhánh phải
        return countGreater(pRoot->p_right, x);
    }
}

// Cấu trúc hỗ trợ kiểm tra cây BST vì hàm isBST không cho truyền tham số
struct Result_of_Checking_BST{
    // Lưu trạng thái có còn là BST không
    bool isBST;

    // Lưu node gần nhất kiểm tra
    NODE* visited;
};

// Hàm kiểm tra cây BST
Result_of_Checking_BST checkBST(NODE* pRoot){
    // Nếu null thì đệ quy lại kiểm tiếp
    if (pRoot == nullptr){
        return {true, nullptr};
    }

    // Đệ quy qua trái
    // Logic là đi theo LNR vì lúc này giá trị sẽ tăng dần -> không tăng dần thì không phải BST
    Result_of_Checking_BST left = checkBST(pRoot->p_left);

    // Nếu không còn là BST thì tất cả các lần đệ quy còn chờ sẽ là false
    if (left.isBST == false){
        return {false, nullptr};
    }

    // Nếu node trái là null và node nhỏ hơn hoặc bằng node đã ghé qua thì false
    // Vì tính chất tăng dần của duyệt LNR
    if (left.visited != nullptr && pRoot->key <= left.visited->key){
        return {false, nullptr};
    }

    // Kiểm tra cây con phải (LNR)
    Result_of_Checking_BST right = checkBST(pRoot->p_right);

    // Tương tự, nếu không thỏa mãn tính chất BST thì tất cả các lần đệ quy là false
    if (right.isBST == false){
        return {false, nullptr};
    }

    // Nếu node phải vừa duyệt là rỗng thì trả về true và node đã ghé cũ
    if (right.visited != nullptr){
        return {true, right.visited};
    }
    // Nếu node phải vừa duyệt không rỗng thì trả về true và node hiện tại đang duyệt
    else{
        return {true, pRoot};
    }
}

// Hàm duyệt tính chất BST
bool isBST(NODE* pRoot){
    // Trả về kết quả trạng thái của hàm kiểm tra cây BST
    return checkBST(pRoot).isBST;
}

// Hàm kiểm tra cây đầy đủ
bool isFullTree(NODE* pRoot){
    // Nếu cây null thì tiếp tục
    if (pRoot == nullptr){
        return true;
    }

    // Nếu cả 2 rỗng thì true và tiếp tục
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr){
        return true;
    }

    // Nếu cả 2 có thì đệ quy kiểm tra tiếp
    if (pRoot->p_left != nullptr && pRoot->p_right != nullptr){
        return isFullTree(pRoot->p_left) && isFullTree(pRoot->p_right);
    }

    // Ngược lại thì false và các lần trả về sau đều là false vì điều kiện true là 2 bên đều thỏa mãn (&&)
    return false;
}

// Hàm kiểm tra cây nhị phân cân bằng đầy đủ
bool isFullBST(NODE* pRoot){
    // Gọi 2 hàm kiểm tra
    return isBST(pRoot) && isFullTree(pRoot);
}
