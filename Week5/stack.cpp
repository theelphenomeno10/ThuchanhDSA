#include <iostream>
#include <fstream>
#include <string>

struct NODE{
    int key;
    NODE* p_next;
};

struct STACK{
    NODE* s_top;
};

// các hàm sử dụng

// tạo node
NODE* createNode(int key);

// khởi tạo stack
STACK* initializeStack(STACK* s);

// push node vào stack theo quy tắc FIFO
void push(STACK*& s, int key);

// pop node khỏi stack theo quy tắc FIFO
int pop(STACK*& s);

// lấy số phần tử trong stack
int size(STACK* s);

// kiểm tra xem stack có rỗng không
bool isEmpty(STACK* s);

// in stack ra output.txt
void printStack(STACK* s, std::string out_dir);

// xử lý file bao gồm:
    // đọc file từ in_directory
    // xuất file ra out_directory
    // xử lý trên stack
void fileHandle(std::string in_directory, std::string out_directory, STACK* sample);

// hàm tạo node cơ bản
NODE* createNode(int key){
    NODE* temp = new NODE;
    temp->key = key;
    temp->p_next = nullptr;

    return temp;
}

// khởi tạo stack
STACK* initializeStack(STACK* s){
    // vì stop null nên ta sẽ tạo node cho nó
    s->s_top = nullptr;

    return s;
}

void push(STACK*& s, int key){
    // stack rỗng thì khởi tạo stack
    if (s->s_top == nullptr){
        s->s_top = createNode(key);
        return;
    }

    // push theo kiểu FIFO
    // insert head
    NODE* temp = createNode(key);
    temp->p_next = s->s_top;
    s->s_top = temp;

    return;
}

int pop(STACK*& s){
    // stack rỗng -> xuất ra màn hình
    if (s->s_top == nullptr){
        std::cout << "No member in stack" << std::endl;
        return -1;
    }

    // pop kiểu FIFO
    // removeHead
    NODE* temp = s->s_top;
    s->s_top = s->s_top->p_next;
    int value = temp->key;
    delete temp;
    temp = nullptr;

    return value;
}

int size(STACK* s){
    // duyệt hết stack và đếm số node
    NODE* temp = s->s_top;
    int count = 0;

    while (temp != nullptr){
        count++;
        temp = temp->p_next;
    }

    return count;
}

bool isEmpty(STACK* s){
    // trả về liệu s->top có là null không
    return s->s_top == nullptr;
}

void printStack(STACK* s, std::string out_dir){
    // mở ở chế độ ios::app để ghi liên tục thay vì ghi đè vào file output.txt
    std::ofstream f(out_dir, std::ios::app);

    // stack rỗng -> xuất empty
    if (s->s_top == nullptr){
        f << "EMPTY" << std::endl;
        return;
    }

    NODE* temp = s->s_top;
    // duyệt stack và in ra
    while (temp != nullptr){
        f << temp->key << " ";
        temp = temp->p_next;
    }
    f << std::endl;
}

void fileHandle(std::string in_directory, std::string out_directory, STACK* sample){
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
            initializeStack(sample);
            // trường hợp 2: push
        }else if(s == "push"){
            // xóa khoảng trắng để đọc giá trị được push
            f >> std::ws;
            int value = 0;
            f >> value;
            // gọi hàm push
            push(sample, value);
            // trường hợp 3: pop
        }else if (s == "pop"){
            // gọi hàm pop
            pop(sample);
        }

        // gọi hàm xuất stack
        printStack(sample, out_directory);
    }    
}

int main(){
    STACK* s;
    // các test case em tự thiết kế để kiểm tra tính chính xác của hàm
    /*
    initializeStack(s, 1);
    printStack(s);
    push(s, 2);
    push(s, 3);
    printStack(s);
    int value = pop(s);
    std::cout << "Pop value: " << value << std::endl;
    std::cout << "Is stack empty: " << isEmpty(s) << std::endl;
    printStack(s);
    pop(s);
    pop(s);
    std::cout << "Is stack empty: " << isEmpty(s) << std::endl;
    */
   
    // đọc và ghi file
    fileHandle("input.txt", "output.txt", s);

    return 0;
}