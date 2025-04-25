#include <iostream>
#include <fstream>
#include <string>

struct NODE{
    int key;
    NODE* p_next;
};

struct QUEUE{
    NODE* head;
    NODE* tail;
};

// các hàm sử dụng:

// tạo node
NODE* createNode(int value);

// khởi tạo queue
QUEUE* initializeQueue(QUEUE*& q);

// thêm phần tử vào queue
void enqueue(QUEUE*& q, int key);

// xóa phần tử khỏi queue
void enqueue(QUEUE*& q, int key);

// xem số lượng phần tử đang có
int size(QUEUE* q);

// xem queue có rỗng không
bool isEmpty(QUEUE* q);

// xử lý file, bao gồm:
    // đọc file từ in_directory
    // xuất file ra out_directory
    // xử lý trên queue mẫu tên là sample
void fileHandle(std::string in_directory, std::string out_directory, QUEUE* sample);

// quản lý việc xuất queue ra file
void printQueue(QUEUE* q, std::string out_dir);

// chi tiết hàm
NODE* createNode(int value){
    NODE* temp = new NODE;
    temp->key = value;
    temp->p_next = nullptr;

    return temp;
}

QUEUE* initializeQueue(QUEUE*& q){
    q->head = nullptr;
    q->tail = nullptr;

    return q;
}

void enqueue(QUEUE*& q, int key){
    if (q->head == nullptr){
        q->head = createNode(key);
        q->tail = q->head;

        return;
    }

    NODE* temp = createNode(key);
    q->tail->p_next = temp;
    q->tail = temp;
}

int dequeue(QUEUE*& q){
    if (q->head == nullptr){
        std::cerr << "Empty queue." << std::endl;
        return -1;
    }

    NODE* temp = q->head;
    q->head = q->head->p_next;
    int value = temp->key;
    delete temp;

    return value;
}

int size(QUEUE* q){
    NODE* cur = q->head;
    int count = 0;
    while (cur != nullptr){
        ++count;
        cur = cur->p_next;
    }

    return count;
}

bool isEmpty(QUEUE* q){
    return q->head == nullptr;
}   

void printQueue(QUEUE* q, std::string out_dir){
    // mở ở chế độ ios::app để ghi liên tục thay vì ghi đè vào file output.txt
    std::ofstream f(out_dir, std::ios::app);

    // queue rỗng -> xuất empty
    if (q->head == nullptr){
        f << "EMPTY" << std::endl;
        return;
    }

    NODE* temp = q->head;
    // duyệt queue và in ra
    while (temp != nullptr){
        f << temp->key << " ";
        temp = temp->p_next;
    }
    f << std::endl;
}

void fileHandle(std::string in_directory, std::string out_directory, QUEUE* sample){
    // biến f đọc file
    std::ifstream f (in_directory);
    // biến j ghi file
    std::ofstream j (out_directory, std::ios::app);
    // string để đọc lệnh từ f
    std::string s;
    // đọc cho đến hết file
    while(!f.eof()){
        // xóa khoảng trắng
        f >> std::ws;
        // đọc lệnh
        f >> s;
        // chia ra 3 trường hợp lệnh
            // trường hợp 1: khởi tạo
        if (s == "init"){
            // gọi hàm khởi tạo
            initializeQueue(sample);
            // trường hợp 2: thêm
        }else if(s == "enqueue"){
            // xóa khoảng trắng để đọc giá trị được enqueue
            f >> std::ws;
            int value = 0;
            f >> value;
            // gọi hàm enqueue
            enqueue(sample, value);
            // trường hợp 3: xóa
        }else if (s == "dequeue"){
            // gọi hàm dequeue
            dequeue(sample);
        }

        // gọi hàm xuất queue
        printQueue(sample, out_directory);
    }    
}

int main(){
    QUEUE* q;
    // các test case em dùng để kiểm tra xem đã cài queue đúng chưa
    
    /*
    initializeQueue(q);
    printQueue(q);

    enqueue(q, 1);
    printQueue(q);

    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    printQueue(q);

    int val = dequeue(q);
    std::cout << "Pop queue: " << val << std::endl;
    printQueue(q);

    val = dequeue(q);
    std::cout << "Pop queue: " << val << std::endl;
    printQueue(q);
    */

    // đọc và ghi file
    fileHandle("input.txt", "output.txt", q);

    return 0;
}