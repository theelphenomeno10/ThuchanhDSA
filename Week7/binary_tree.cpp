#include <iostream>
#include <vector>
#include <queue>

struct NODE{
    int key = 0;
    NODE* p_left = nullptr;
    NODE* p_right = nullptr;
};

// Tạo node
NODE* createNode(int data){
    // Khởi tạo node và gán giá trị cho các con trỏ
    NODE* temp = new NODE;

    temp->key = data;
    temp->p_left = nullptr;
    temp->p_right = nullptr;

    return temp;
}

// Duyệt trước
void Pre_Order(NODE* pRoot, std::vector<int>& result){
    // Nếu là trỏ null thì trả về
    if (pRoot == nullptr){
        return;
    }

    // In giá trị trước khi đệ quy qua trái và phải
    result.push_back(pRoot->key);
    Pre_Order(pRoot->p_left, result);
    Pre_Order(pRoot->p_right, result);
}

// Ghi kết quả duyệt trước vào vector
std::vector<int> NLR(NODE* pRoot){
    // Tạo mảng
    std::vector<int> result;

    // Gọi hàm duyệt trước
    Pre_Order(pRoot, result);
    
    return result;
}

// Duyệt giữa
void In_Order(NODE* pRoot, std::vector<int>& result){
    // Trỏ null thì trả về
    if (pRoot == nullptr){
        return;
    }

    // Đệ quy qua nhánh trái trước rồi in rồi đệ quy qua nhánh phải
    In_Order(pRoot->p_left, result);
    result.push_back(pRoot->key);
    In_Order(pRoot->p_right, result);
}

// Ghi kết quả duyệt giữa vào vector
std::vector<int> LNR(NODE* pRoot){
    // Tạo mảng
    std::vector<int> result;

    // Gọi hàm duyệt giữa
    In_Order(pRoot, result);
    return result;
}

// Duyệt sau
void Post_Order(NODE* pRoot, std::vector<int>& result){
    // Trỏ null thì trả về
    if (pRoot == nullptr){
        return;
    }

    // Đệ quy qua trái phải trước rồi mới in kết quả
    Post_Order(pRoot->p_left, result);
    Post_Order(pRoot->p_right, result);
    result.push_back(pRoot->key);
}

// Ghi kết quả duyệt sau vào vector
std::vector<int> LRN(NODE* pRoot){
    // Tạo mảng
    std::vector<int> result;

    // Ghi kết quả
    Post_Order(pRoot, result);
    return result;
}

// Duyệt theo tầng (dùng queue)
std::vector<std::vector<int>> LevelOrder(NODE* pRoot){
    std::queue<NODE*> q;
    
    // Đẩy vào queue giá trị root
    q.push(pRoot);

    // Mảng 2 chiều lưu kết quả
    std::vector<std::vector<int>> result;

    while(!q.empty()){
        // Mảng 1 chiều có tác dụng đẩy vào mảng 2 chiều result
        std::vector<int> list;

        // Duyệt theo tầng nên dùng limit để ngăn cách các tầng
        // Kích thước phần tử của tầng cũng chính là số lần lặp để duyệt theo tầng
        size_t limit = q.size();

        // Lặp lại đến khi tầng hết phần tử
        for (size_t i = 0; i < limit; i++){
            // Đẩy vào mảng 1 chiều kết quả trên đỉnh
            list.push_back(q.front()->key);

            // Nếu trái phải có node con thì đẩy vào
            if (q.front()->p_left != nullptr){
                q.push(q.front()->p_left);
            }

            if (q.front()->p_right != nullptr){
                q.push(q.front()->p_right);
            }

            // Xóa phần tử vừa xét
            q.pop();
        }

        // Đẩy mảng 1 chiều vào mảng 2 chiều
        result.push_back(list);
    }

    return result;
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

// Tổng giá trị các key
int sumNode(NODE* pRoot){
    // Nếu key là null thì tổng là 0
    if (pRoot == nullptr){
        return 0;
    }

    // Lấy tổng cây con trái + tổng cây con phải + giá trị của node đang xét
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
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

// Hàm tính tầng
int level(NODE* pRoot, NODE* p){
    // Cây rỗng thì trả về -1
    if (pRoot == nullptr){
        return -1;
    }

    // Tìm thấy p thì trả về 0 vì kết quả đã được đệ quy xuống
    if (pRoot == p){
        return 0;
    }

    // Tương tự logic ở hàm tính chiều cao, gọi các biến tạm và nếu
    // giá trị của biến tạm khác so với giá trị không tìm thấy (-1)
    // thì tức là có node đó
    int left_level = level(pRoot->p_left, p);
    if (left_level != -1){
        return 1 + left_level;
    }

    int right_level = level(pRoot->p_right, p);
    if (right_level != -1){
        return 1 + right_level;
    }

    // Chạy tới đây tức là không có node p
    return -1;
}

// Hàm tính số lá
int countLeaf(NODE* pRoot){
    // Cây rỗng -> 0 lá
    if (pRoot == nullptr){
        return 0;
    }

    // Nếu pRoot là lá thì +1
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr){
        return 1;
    }

    // Kiểm tra số lá ở 2 cây con phải trái
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}


