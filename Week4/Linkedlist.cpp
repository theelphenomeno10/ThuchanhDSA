#include <iostream>
#include <cassert>

struct NODE
{
    int key;
    NODE *p_next;
};

struct List
{
    NODE *p_head;
    NODE *p_tail;
    List(NODE *head = nullptr, NODE *tail = nullptr) : p_head(head), p_tail(tail) {}
};

// --- Define function prototypes ---
NODE *createNode(int data);
List *createList(NODE *p_node);
bool addHead(List *&L, int data);
bool addTail(List *&L, int data);
bool removeHead(List *&L);
void removeTail(List *&L);
void removeAll(List *&L);
void removeBefore(List *&L, int val);
void removeAfter(List *&L, int val);
bool addPos(List *&L, int data, int pos);
void removePos(List *&L, int data, int pos);
bool addBefore(List *&L, int data, int val);
bool addAfter(List *&L, int data, int val);
void printList(List *L);
int countElements(List *L);
List *reverseList(List *L);
void removeDuplicate(List *&L);
bool removeElement(List *&L, int key);

// function to create a list from an array
List *createListFromArray(int arr[], int n)
{
    List *newList = new List();
    newList->p_head = nullptr;
    newList->p_tail = nullptr;
    for (int i = 0; i < n; ++i)
    {
        addTail(newList, arr[i]);
    }
    return newList;
}

// function to compare two lists
bool areListsEqual(List *list1, List *list2)
{
    NODE *current1 = list1 ? list1->p_head : nullptr;
    NODE *current2 = list2 ? list2->p_head : nullptr;
    while (current1 && current2)
    {
        if (current1->key != current2->key)
        {
            return false;
        }
        current1 = current1->p_next;
        current2 = current2->p_next;
    }
    return (current1 == nullptr && current2 == nullptr);
}

// function to free the memory of a list
void freeList(List *L)
{
    NODE *current = L->p_head;
    while (current)
    {
        NODE *next = current->p_next;
        delete current;
        current = next;
    }
    delete L;
}

NODE *createNode(int data)
{
    // Tạo Node
    NODE* temp = new NODE;
    // Gán giá trị cho node
    temp->key = data;
    // Mặc định p_next là nullptr
    temp->p_next = nullptr;
    // Trả về node
    return temp;
}

List *createList(NODE *p_node)
{
    // Nếu p_node là nullptr
    if (p_node == nullptr){
        // Trả về danh sách rỗng
        return nullptr;
    }

    // Tạo danh sách tạm
    List *temp = new List;
    // Đặt p_node là list head và list tail
    temp->p_head = p_node;
    temp->p_tail = p_node;

    // Trả về list
    return temp;
}

bool addHead(List *&L, int data)
{
    // Tạo node với giá trị data
    NODE* tempNode = createNode(data);
    // Nếu list rỗng
    if (L->p_head == nullptr){
        // Tạo cho list l với giá trị vừa tạo
        L = createList(tempNode);
    }else{ // Nếu list không rỗng
        // Cho node vừa tạo trỏ đến list head
        tempNode->p_next = L->p_head;
        // Cập nhật list head là node vừa tạo
        L->p_head = tempNode;
    }

    return true;
}

bool addTail(List *&L, int data) // this function is kept for createListfromArray function
{
    NODE *newNode = createNode(data);
    if (L->p_head == nullptr)
    {
        L->p_head = newNode;
        L->p_tail = newNode;
    }
    else
    {
        L->p_tail->p_next = newNode;
        L->p_tail = newNode;
    }
    return true;
}

bool removeHead(List *&L)
{
    // Nếu danh sách rỗng -> trả về false
    if (L->p_head == nullptr){
        return false;
    // Nếu danh sách chỉ có 1 phần tử
    }else if (L->p_head->p_next == nullptr){
        // Xóa head
        NODE* temp = L->p_head;
        delete temp;
        // Xóa list
        L->p_head = nullptr;
        L->p_tail = nullptr;
        return true;
    // Nếu danh sách có nhiều phần tử
    }else{
    // Tạo node tạm lưu biến head cần xóa
        NODE* temp = L->p_head;
    // Cập nhật head mới
        L->p_head = temp->p_next;
    // Xóa node cũ
        delete temp;
        temp = nullptr;

        return true;
    }
}

void removeTail(List *&L)
{
    // Nếu list rỗng -> return
    if (L->p_head == nullptr){
        return;
    // Nếu list có 1 phần tử
    }else if (L->p_head->p_next == nullptr){
        // Xóa list
        L->p_head = nullptr;
        L->p_tail = nullptr;
    // Nếu list có nhiều phần tử
    }else{
        NODE* cur = L->p_head;
        // Lấy node trước tail
        while (cur->p_next != L->p_tail){
            cur = cur->p_next;
        }

        // Xóa tail
        delete L->p_tail;
        L->p_tail = nullptr;
        // Tạo tail mới
        L->p_tail = cur;
        L->p_tail->p_next = nullptr;
    }
    
    return;
}

void removeAll(List *&L)
{
    // Tạo node cur chạy qua list
    NODE* cur = L->p_head;
    // Xoá đến khi không còn node
    while (cur != nullptr){
        removeHead(L);
        cur = L->p_head;
    }
    return;
}

// Remove a node before a given value in the list if it exists, otherwise do nothing
void removeBefore(List *&L, int val)
{
    // Nếu list rỗng hoặc chỉ có 1 phần tử, trả về
    if (L->p_head == nullptr || L->p_head->p_next == nullptr){
        return;
    }else{
        // cur là phần tử chạy trước để tìm val
        // logic ở đây là nối prev với cur để xóa target
        NODE* cur = L->p_head;
        // target là phần tử được xóa
        NODE* target = nullptr;
        // prev là phần tử trước target
        NODE* prev = nullptr;
        // vòng lặp chạy tìm val
        while (cur != nullptr && cur->key != val){
            prev = target;
            target = cur;
            cur = cur->p_next;
        }

        // nếu không có val
        if (cur == nullptr){
            return;
        }

        prev->p_next = cur;
        delete target;
        target = nullptr;
    }

    return;
}

void removeAfter(List *&L, int val)
{
    // List rỗng -> trả về list
    if (L->p_head == nullptr){
        return;
    }

    // Khởi tạo node cur là vị trí cần kiểm
    // target là vị trí cần xóa
    // next là vị trí sau vị trí cần xóa

    NODE* cur = L->p_head;

    NODE* target = nullptr;
    // Kiểm tra tính hợp lệ của target
    if (cur->p_next != nullptr){
        target = cur->p_next;
    }

    NODE* next = nullptr;
    // Kiểm tra tính hợp lệ của next
    if (cur->p_next != nullptr && cur->p_next->p_next != nullptr){
        next = cur->p_next->p_next;
    }

    // Vòng lặp tìm node có giá trị val
    while (cur != nullptr && cur->key != val){
        // Đẩy next lên next->p_next nếu hợp lệ
        if (next != nullptr){
            next = next->p_next;
        }

        // Tương tự
        if (target != nullptr){
            target = target->p_next;
        }

        cur = cur->p_next;
    }

    // Nếu hết vòng lặp mà vẫn không tìm được (cur == nullptr) -> return

    // Ngược lại
    if (cur != nullptr){
        // Gán cur->p_next là node next (lưu địa chỉ kế tiếp trỏ đến của node bị xóa)
        cur->p_next = next;

        delete target;
        target = nullptr;
    }

    return;
}

bool addPos(List *&L, int data, int pos)
{
    // Nếu rơi vào 2 trường hợp vô lý:
        // pos âm
        // list rỗng và pos khác 0 -> return false
    if (pos < 0 || (L->p_head == nullptr && pos != 0)){
        return false;
    }

    // pos = 0 tức là chèn vào đầu list
    if (pos == 0){
        addHead(L, data);
        return true;
    }

    // biến next chạy tìm node kế
    NODE* next = L->p_head;
    // biến prev chạy tìm node sau
    NODE* prev = nullptr;
    
    // dò tìm pos cần chèn, prev lưu lại vị trí node ở sau và next lưu vị trí node ở trước
    // dừng khi pos = 0
    while (next != nullptr && pos > 0){
        prev = next;
        next = next->p_next;
        pos--;
    }

    // trường hợp ra ngoài phạm vi list -> trả về false
    if (pos > 0){
        return false;
    }

    // trường hợp chèn đuôi
    if (next == nullptr){
        addTail(L, data);
        return true;
    }

    // trường hợp chèn giữa
    NODE* temp = createNode(data);
    prev->p_next = temp;
    temp->p_next = next;

    return true;
}

void removePos(List *&L, int data, int pos)
{
    // Mảng không có phần tử nào -> không xóa được
    if (L->p_head == nullptr){
        return;
    }

    // pos = 0 -> xóa đầu list
    if (pos == 0){
        removeHead(L);
        return;
    }

    // prev lưu vị trí trước vị trí xóa
    NODE* prev = L->p_head;
    // next lưu vị trí sau vị trí xóa
    NODE* next = nullptr;
    if (prev->p_next != nullptr){
        next = prev->p_next;
    }

    // giảm xuống 1 lần vì đã khởi tạo giá trị trước
    pos--;
    // tăng các node lên khi pos chưa hết hoặc next chưa vượt qua giới hạn mảng
    while (pos > 0 && next != nullptr){
        // tăng prev
        prev = next;
        // tăng next
        next = next->p_next;
        // prev luôn đi theo sau next
        
        // giảm pos
        pos--;
    }

    // nếu vượt quá giới hạn list -> return
    if (pos > 0){
        return;
    }

    // nếu next là tail -> xóa tail
    if (next == L->p_tail){
        removeTail(L);
        return;
    }

    // nếu xóa node giữa list
    prev->p_next = next->p_next;
    delete next;
    return;
}

// Insert an integer before a value of a given List:
bool addBefore(List *&L, int data, int val)
{
    // nếu list rỗng -> trả về false
    if (L->p_head == nullptr){
        return false;
    }

    // target là node có giá trị val
    NODE* target = L->p_head;
    // prev là node có giá trị trước target
    NODE* prev = nullptr;
    // chạy đến khi target ra khỏi mảng hoặc tìm đc val
    while (target != nullptr && target->key != val){
        prev = target;
        target = target->p_next;
        // prev luôn ở sau target
    }

    // nếu target là đầu -> addHead
    if (target == L->p_head){
        addHead(L, data);
        return true;
    }

    // nếu target là đuôi -> addTail
    if (target == L->p_tail){
        addTail(L, data);
        return true;
    }

    // nếu không có val -> trả về false
    if (target == nullptr){
        return false;
    }

    // chèn vào với val ở giữa list
    NODE* temp = createNode(data);
    prev->p_next = temp;
    temp->p_next = target;

    return true;
}

bool addAfter(List *&L, int data, int val)
{
    // list rỗng -> return false
    if (L->p_head == nullptr){
        return false;
    }

    // target lưu lại vị trí val
    NODE* target = L->p_head;
    // chạy đến khi tìm được val hoặc out of bound
    while (target != nullptr && target->key != val){
        target = target->p_next;
    }

    // out of bound -> false
    if (target == nullptr){
        return false;
    }

    // target là đuôi -> chèn đuôi
    if (target == L->p_tail){
        addTail(L, data);
        return true;
    }

    // target ở giữa
    NODE* temp = createNode(data);
    temp->p_next = target->p_next;
    target->p_next = temp;

    return false;
}

void printList(List *L)
{
    // tạo biến tạm ở đầu list
    NODE* cur = L->p_head;

    // chạy cho đến khi end list
    while (cur != nullptr){
        // vừa chạy vừa xuất giá trị
        std::cout << cur->key << " ";
        cur = cur->p_next;
    }
    return;
}

int countElements(List *L)
{
    // biến count đếm số phần tử
    int count = 0;
    NODE* cur = L->p_head;
    // chạy cho đến khi end list
    while (cur != nullptr){
    // vừa chạy vừa xuất giá trị
        count++;
        cur = cur->p_next;
    }
    return count;
}

List *reverseList(List *L)
{
    // Nếu list không có hoặc có 1 phần tử -> trả về list
    if (L->p_head == nullptr || L->p_head->p_next == nullptr){
        return L;
    }

    // Lưu lại biến p_head để tí đổi thành p_tail
    NODE* temp = L->p_head;

    // left là phần tử được trỏ đến
    NODE* left = nullptr;
    // right là phần tử trỏ đến
    NODE* right = L->p_head;
    // holder là phần tử kế tiếp cần xử lý
    NODE* holder = L->p_head->p_next;

    // nối right đến left và dịch right đến holder để tiếp tục vòng lặp
    while (right != nullptr){
        right->p_next = left;
        left = right;
        right = holder;
        if (holder != nullptr){
            holder = holder->p_next;
        }
    }
    
    // đổi head và tail
    L->p_head = left;
    L->p_tail = temp;
    temp->p_next = nullptr;

    return L;
}

#include <vector>

void removeDuplicate(List *&L)
{    
    // Nếu mảng chỉ có 1 phần tử hoặc không có phần tử nào
    if (L->p_head == nullptr || L->p_head->p_next == nullptr){
        return;
    }

    // vector lưu trữ giá trị của các key
    std::vector<int> keyList;

    // biến prev lưu vị trí của phần tử trước
    NODE* prev = L->p_head;
    // biến cur kiểm tra xem key đã xuất hiện chưa
    NODE* cur = L->p_head->p_next;
    // biến next lưu lại vị trí của phần tử kế tiếp
    NODE* next = L->p_head->p_next->p_next;
    // biến lưu trạng thái có tồn tại rồi hay chưa
    bool exist = false;
    // đẩy giá trị key đầu tiên
    keyList.push_back(prev->key);

    while (cur != nullptr){
        // mặc định là chưa xuất hiện
        exist = false;
        // duyệt qua và cập nhật trạng thái xuất hiện
        for (int i = 0; i < keyList.size(); i++){
            if (cur->key == keyList[i]){
                exist = true;
            }
        }

        // nếu chưa xuất hiện
        if (!exist){
            // đẩy vào mảng
            keyList.push_back(cur->key);

            // đẩy các biến lưu trữ vị trí lên
            prev = cur;
            cur = next;
            if (next != nullptr){
                next = next->p_next;
            }
        }else{
            // nếu đã xuất hiện

            // gắn cho phần tử trước với phần tử sau để bỏ qua phần tử lặp
            prev->p_next = next;
            // xóa phần tử lặp
            delete cur;
            
            // tiếp tục vòng lặp với cur lên vị trí chưa lặp gần nhất và next lên thêm 1 vị trí
            cur = next;
            if (next != nullptr){
                next = next->p_next;
            }
        }
    }
    return;
}

bool removeElement(List *&L, int key)
{
    // nếu list rỗng -> trả về
    if (L->p_head == nullptr){
        return false;
    }

    // prev lưu lại vị trí trước cur
    NODE* prev = nullptr;
    // cur là biến chạy tìm phần tử có chứa giá trị cần tìm
    NODE* cur = L->p_head;

    // hàm chạy cur sao cho prev luôn ở sau cur
    while (cur != nullptr && cur->key != key){
        prev = cur;
        cur = cur->p_next;
    }

    // nếu cur là ở đầu -> removeHead
    if (cur == L->p_head){
        removeHead(L);
        return true;
    }

    // không tìm thấy cur -> false
    if (cur == nullptr){
        return false;
    }

    // nếu cur nằm ở giữa hoặc cuối cùng
        // nối prev với phần tử sau cur
        // xóa cur
    prev->p_next = cur->p_next;
    delete cur;

    return true;
}

// --- Function main to test the above functions ---

int main()
{
    std::cout << "--- Begin running test cases ---" << std::endl;

    // Test case 1: createNode /////////////////////////////////////////////////
    std::cout << "Test createNode: ";
    NODE *node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->p_next == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test case 2: createList //////////////////////////////////////////////////
    std::cout << "Test createList: ";
    NODE *head2 = createNode(20);
    List *list2 = createList(head2);
    assert(list2 != nullptr && list2->p_head == head2 && list2->p_tail == head2);
    std::cout << "Passed" << std::endl;
    freeList(list2);

    // Test case 3: addHead //////////////////////////////////////////////////////
    std::cout << "Test addHead: ";
    List *list3 = new List();
    assert(addHead(list3, 30));
    assert(list3->p_head != nullptr && list3->p_head->key == 30 && list3->p_tail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->p_head->key == 40 && list3->p_head->p_next->key == 30 && list3->p_tail->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(list3);

    // Test case 4: addTail /////////////////////////////////////////////////////////
    std::cout << "Test addTail: ";
    List *list4 = new List();
    assert(addTail(list4, 50));
    assert(list4->p_head != nullptr && list4->p_head->key == 50 && list4->p_tail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->p_head->key == 50 && list4->p_tail->key == 60 && list4->p_head->p_next->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(list4);

    // Test case 5: removeHead //////////////////////////////////////////////////////////////////
    std::cout << "Test removeHead: ";
    int arr1[3] = {70, 80, 90};
    List *list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->p_head->key == 80);
    assert(removeHead(list5) && list5->p_head->key == 90);
    assert(removeHead(list5) && list5->p_head == nullptr && list5->p_tail == nullptr);
    assert(!removeHead(list5)); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(list5);

    // Test case 6: removeTail ///////////////////////////////////////////////////////////////////
    std::cout << "Test removeTail: ";
    int arr2[3] = {100, 110, 120};
    List *list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6->p_tail->key == 110 && list6->p_tail->p_next == nullptr);
    removeTail(list6);
    assert(list6->p_tail->key == 100 && list6->p_tail->p_next == nullptr && list6->p_head == list6->p_tail);
    removeTail(list6);
    assert(list6->p_head == nullptr && list6->p_tail == nullptr);
    List *emptyList6 = new List();
    removeTail(emptyList6); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(emptyList6);
    freeList(list6);

    // Test case 7: removeAll /////////////////////////////////////////////////////////////////////
    std::cout << "Test removeAll: ";
    int arr3[3] = {130, 140, 150};
    List *list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->p_head == nullptr && list7->p_tail == nullptr);
    List *emptyList7 = new List();
    removeAll(emptyList7); // Remove from empty list
    assert(emptyList7->p_head == nullptr && emptyList7->p_tail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(emptyList7);
    freeList(list7);

    // Test case 8: removeBefore //////////////////////////////////////////////////////////////////////
    std::cout << "Test removeBefore: ";
    int arr4[5] = {160, 170, 180, 190, 200};
    List *list8 = createListFromArray(arr4, 5);

    // testcase 1
    removeBefore(list8, 180);
    int expectedArr8[4] = {160, 180, 190, 200};
    List *expectedList8 = createListFromArray(expectedArr8, 4);
    assert(areListsEqual(list8, expectedList8));

    // testcase 2
    removeBefore(list8, 200);
    int expectedArr8_2[3] = {160, 180, 200};
    List *expectedList8_2 = createListFromArray(expectedArr8_2, 3);
    assert(areListsEqual(list8, expectedList8_2));

    // testcase 3
    removeBefore(list8, 170); // Don't have any element before
    int expectedArr8_2_2[3] = {160, 180, 200};
    List *expectedList8_2_2 = createListFromArray(expectedArr8_2_2, 3);
    assert(areListsEqual(list8, expectedList8_2_2));

    // free memory
    freeList(expectedList8);
    freeList(expectedList8_2);
    freeList(expectedList8_2_2);
    freeList(list8);
    std::cout << "Passed" << std::endl;

    // Test case 9: remove after ////////////////////////////////////////////////////////////
    std::cout << "Test removeAfter: ";
    int arr5[4] = {220, 230, 240, 250};
    List *list9 = createListFromArray(arr5, 4);
    // testcase 1
    removeAfter(list9, 220);
    int expectedArr9[3] = {220, 240, 250};
    List *expectedList9 = createListFromArray(expectedArr9, 3);
    assert(areListsEqual(list9, expectedList9));
    // testcase 2
    removeAfter(list9, 250); // Don't have any element after
    int expectedArr9_2[3] = {220, 240, 250};
    List *expectedList9_2 = createListFromArray(expectedArr9_2, 3);
    assert(areListsEqual(list9, expectedList9_2));
    // testcase 3
    removeAfter(list9, 240);
    int expectedArr9_3[2] = {220, 240};
    List *expectedList9_3 = createListFromArray(expectedArr9_3, 2);
    assert(areListsEqual(list9, expectedList9_3));
    // testcase 4
    int arr9_single[1] = {260};
    List *list9_single = createListFromArray(arr9_single, 1);
    removeAfter(list9_single, 260);
    int expectedArr9_single[1] = {260};
    List *expectedList9_single = createListFromArray(expectedArr9_single, 1);
    assert(areListsEqual(list9_single, expectedList9_single));
    // testcase 5
    List *emptyList9 = new List();
    removeAfter(emptyList9, 270);
    assert(areListsEqual(emptyList9, new List()));
    // free memory
    freeList(expectedList9);
    freeList(expectedList9_2);
    freeList(expectedList9_3);
    freeList(expectedList9_single);
    freeList(list9);
    freeList(list9_single);
    freeList(emptyList9);
    std::cout << "Passed" << std::endl;

    // // Test case 10: addPos /////////////////////////////////////////////////////////
    std::cout << "Test addPos: ";
    List *list10 = new List();
    assert(addPos(list10, 280, 0));
    assert(list10->p_head != nullptr && list10->p_head->key == 280 && list10->p_tail->key == 280);
    assert(addPos(list10, 290, 1));
    assert(list10->p_head->key == 280 && list10->p_tail->key == 290 && list10->p_head->p_next->key == 290);
    assert(addPos(list10, 300, 1));
    assert(list10->p_head->key == 280 && list10->p_tail->key == 290 && list10->p_head->p_next->key == 300);
    assert(list10->p_head->p_next->p_next->key == 290);
    assert(addPos(list10, 310, 3));
    assert(list10->p_head->key == 280 && list10->p_tail->key == 310 && list10->p_head->p_next->key == 300);
    assert(list10->p_head->p_next->p_next->key == 290 && list10->p_head->p_next->p_next->p_next->key == 310);
    assert(!addPos(list10, 320, 5));  // Positions out of range
    assert(!addPos(list10, 330, -1)); // Negative position
    // free memory
    freeList(list10);
    std::cout << "Passed" << std::endl;

    // Test case 11: RemovePos /////////////////////////////////////////////////////////
    std::cout << "Test RemovePos: ";
    int arr11[5] = {340, 350, 360, 370, 380};
    List *list11 = createListFromArray(arr11, 5);
    assert(list11->p_head->key == 340 && list11->p_tail->key == 380);
    // testcase 1
    removePos(list11, 340, 0);
    assert(list11->p_head->key == 350 && list11->p_tail->key == 380);
    assert(list11->p_head->p_next->key == 360 && list11->p_head->p_next->p_next->key == 370 && list11->p_head->p_next->p_next->p_next->key == 380);
    assert(list11->p_head->p_next->p_next->p_next->p_next == nullptr);
    // testcase 2
    removePos(list11, 370, 2);
    assert(list11->p_head->key == 350 && list11->p_tail->key == 380);
    assert(list11->p_head->p_next->key == 360 && list11->p_head->p_next->p_next->key == 380);
    assert(list11->p_head->p_next->p_next->p_next == nullptr);
    // testcase 3
    removePos(list11, 350, 5); // Positions out of range
    assert(list11->p_head->key == 350 && list11->p_tail->key == 380);
    assert(list11->p_head->p_next->key == 360 && list11->p_head->p_next->p_next->key == 380);
    assert(list11->p_head->p_next->p_next->p_next == nullptr);
    // free memory
    freeList(list11);
    std::cout << "Passed" << std::endl;

    // Test case 12: addBefore /////////////////////////////////////////////////////////
    std::cout << "Test addBefore: ";
    int arr12[4] = {390, 400, 410, 420};
    List *list12 = createListFromArray(arr12, 4);
    assert(list12->p_head->key == 390 && list12->p_tail->key == 420);
    // testcase 1
    addBefore(list12, 380, 400);
    int arr12_1[5] = {390, 380, 400, 410, 420};
    List *expectedList12_1 = createListFromArray(arr12_1, 5);
    assert(areListsEqual(list12, expectedList12_1));
    // testcase 2
    addBefore(list12, 370, 390);
    int arr12_2[6] = {370, 390, 380, 400, 410, 420};
    List *expectedList12_2 = createListFromArray(arr12_2, 6);
    assert(areListsEqual(list12, expectedList12_2));
    // testcase 3
    addBefore(list12, 360, 350); // Don't have any element before
    int arr12_3[6] = {370, 390, 380, 400, 410, 420};
    List *expectedList12_3 = createListFromArray(arr12_3, 6);
    assert(areListsEqual(list12, expectedList12_3));
    // free memory
    freeList(list12);
    freeList(expectedList12_1);
    freeList(expectedList12_2);
    freeList(expectedList12_3);
    std::cout << "Passed" << std::endl;

    // Test case 13: addAfter /////////////////////////////////////////////////////////
    std::cout << "Test addAfter: ";
    int arr13[4] = {430, 440, 450, 460};
    List *list13 = createListFromArray(arr13, 4);
    assert(list13->p_head->key == 430 && list13->p_tail->key == 460);
    // testcase 1
    addAfter(list13, 470, 440);
    int arr13_1[5] = {430, 440, 470, 450, 460};
    List *expectedList13_1 = createListFromArray(arr13_1, 5);
    assert(areListsEqual(list13, expectedList13_1));
    // testcase 2
    addAfter(list13, 480, 460);
    int arr13_2[6] = {430, 440, 470, 450, 460, 480};
    List *expectedList13_2 = createListFromArray(arr13_2, 6);
    assert(areListsEqual(list13, expectedList13_2));
    // testcase 3
    addAfter(list13, 490, 200); // Don't have any element after
    int arr13_3[6] = {430, 440, 470, 450, 460, 480};
    List *expectedList13_3 = createListFromArray(arr13_3, 6);
    assert(areListsEqual(list13, expectedList13_3));
    // free memory
    freeList(expectedList13_1);
    freeList(expectedList13_2);
    freeList(expectedList13_3);
    freeList(list13);
    std::cout << "Passed" << std::endl;

    // Test case 14: printList /////////////////////////////////////////////////////////
    std::cout << "Test printList: "; // Don't need to assert anything
    std::cout << "Passed" << std::endl;

    // Test case 15: countElements /////////////////////////////////////////////////////////
    std::cout << "Test countElements: ";
    // Test case 1
    int arr15[5] = {500, 510, 520, 530, 540};
    List *list15 = createListFromArray(arr15, 5);
    assert(countElements(list15) == 5);
    // Test case 2
    int arr15_2[3] = {550, 560, 570};
    List *list15_2 = createListFromArray(arr15_2, 3);
    assert(countElements(list15_2) == 3);
    // Test case 3
    int arr15_3[1] = {580};
    List *list15_3 = createListFromArray(arr15_3, 1);
    assert(countElements(list15_3) == 1);
    // Test case 4
    List *emptyList15 = new List();
    assert(countElements(emptyList15) == 0);
    // free memory
    freeList(list15);
    freeList(list15_2);
    freeList(list15_3);
    freeList(emptyList15);
    std::cout << "Passed" << std::endl;

    // Test case 16: reverseList /////////////////////////////////////////////////////////
    std::cout << "Test reverseList: ";
    // Test case 1
    int arr16[5] = {590, 600, 610, 620, 630};
    List *list16 = createListFromArray(arr16, 5);
    List *reversedList16 = reverseList(list16);
    int expectedArr16[5] = {630, 620, 610, 600, 590};
    List *expectedList16 = createListFromArray(expectedArr16, 5);
    assert(areListsEqual(reversedList16, expectedList16));
    // Test case 2
    int arr16_2[3] = {640, 650, 660};
    List *list16_2 = createListFromArray(arr16_2, 3);
    List *reversedList16_2 = reverseList(list16_2);
    int expectedArr16_2[3] = {660, 650, 640};
    List *expectedList16_2 = createListFromArray(expectedArr16_2, 3);
    assert(areListsEqual(reversedList16_2, expectedList16_2));
    // Test case 3
    int arr16_3[1] = {670};
    List *list16_3 = createListFromArray(arr16_3, 1);
    List *reversedList16_3 = reverseList(list16_3);
    int expectedArr16_3[1] = {670};
    List *expectedList16_3 = createListFromArray(expectedArr16_3, 1);
    assert(areListsEqual(reversedList16_3, expectedList16_3));
    // Test case 4
    List *emptyList16 = new List();
    List *reversedList16_4 = reverseList(emptyList16);
    assert(reversedList16_4->p_head == nullptr && reversedList16_4->p_tail == nullptr);
    // free memory
    freeList(expectedList16);
    freeList(expectedList16_2);
    freeList(expectedList16_3);
    freeList(reversedList16);
    freeList(reversedList16_2);
    freeList(reversedList16_3);
    freeList(reversedList16_4);
    // freeList(list16);
    // freeList(list16_2);
    // freeList(list16_3);
    // freeList(emptyList16);
    std::cout << "Passed" << std::endl;

    // Test case 17: removeDuplicate /////////////////////////////////////////////////////////
    std::cout << "Test removeDuplicate: ";
    // Test case 1
    int arr17[6] = {680, 690, 690, 700, 710, 710};
    List *list17 = createListFromArray(arr17, 6);
    removeDuplicate(list17);
    int expectedArr17[4] = {680, 690, 700, 710};
    List *expectedList17 = createListFromArray(expectedArr17, 4);
    assert(areListsEqual(list17, expectedList17));
    // Test case 2
    int arr17_2[5] = {720, 730, 740, 740, 740};
    List *list17_2 = createListFromArray(arr17_2, 5);
    removeDuplicate(list17_2);
    int expectedArr17_2[3] = {720, 730, 740};
    List *expectedList17_2 = createListFromArray(expectedArr17_2, 3);
    assert(areListsEqual(list17_2, expectedList17_2));
    // Test case 3
    int arr17_3[4] = {750, 760, 760, 770};
    List *list17_3 = createListFromArray(arr17_3, 4);
    removeDuplicate(list17_3);
    int expectedArr17_3[3] = {750, 760, 770};
    List *expectedList17_3 = createListFromArray(expectedArr17_3, 3);
    assert(areListsEqual(list17_3, expectedList17_3));
    // Test case 4
    int arr17_4[2] = {780, 780};
    List *list17_4 = createListFromArray(arr17_4, 2);
    removeDuplicate(list17_4);
    int expectedArr17_4[1] = {780};
    List *expectedList17_4 = createListFromArray(expectedArr17_4, 1);
    assert(areListsEqual(list17_4, expectedList17_4));
    // Test case 5
    int arr17_5[1] = {790};
    List *list17_5 = createListFromArray(arr17_5, 1);
    removeDuplicate(list17_5);
    int expectedArr17_5[1] = {790};
    List *expectedList17_5 = createListFromArray(expectedArr17_5, 1);
    assert(areListsEqual(list17_5, expectedList17_5));
    // Test case 6
    List *emptyList17 = new List();
    removeDuplicate(emptyList17);
    assert(emptyList17->p_head == nullptr && emptyList17->p_tail == nullptr);
    // free memory
    freeList(expectedList17);
    freeList(expectedList17_2);
    freeList(expectedList17_3);
    freeList(expectedList17_4);
    freeList(expectedList17_5);
    freeList(list17);
    freeList(list17_2);
    freeList(list17_3);
    freeList(list17_4);
    freeList(list17_5);
    freeList(emptyList17);
    std::cout << "Passed" << std::endl;

    // Test case 18: removeElement /////////////////////////////////////////////////////////
    std::cout << "Test removeElement: ";
    // Test case 1
    int arr18[5] = {800, 810, 820, 830, 840};
    List *list18 = createListFromArray(arr18, 5);
    assert(removeElement(list18, 820));
    int expectedArr18[4] = {800, 810, 830, 840};
    List *expectedList18 = createListFromArray(expectedArr18, 4);
    assert(areListsEqual(list18, expectedList18));
    // Test case 2
    int arr18_2[3] = {850, 860, 870};
    List *list18_2 = createListFromArray(arr18_2, 3);
    assert(removeElement(list18_2, 850));
    int expectedArr18_2[2] = {860, 870};
    List *expectedList18_2 = createListFromArray(expectedArr18_2, 2);
    assert(areListsEqual(list18_2, expectedList18_2));
    // Test case 3
    int arr18_3[4] = {880, 890, 900, 910};
    List *list18_3 = createListFromArray(arr18_3, 4);
    assert(removeElement(list18_3, 910));
    int expectedArr18_3[3] = {880, 890, 900};
    List *expectedList18_3 = createListFromArray(expectedArr18_3, 3);
    assert(areListsEqual(list18_3, expectedList18_3));
    // Test case 4
    int arr18_4[2] = {920, 930};
    List *list18_4 = createListFromArray(arr18_4, 2);
    assert(removeElement(list18_4, 920));
    int expectedArr18_4[1] = {930};
    List *expectedList18_4 = createListFromArray(expectedArr18_4, 1);
    assert(areListsEqual(list18_4, expectedList18_4));
    // Test case 5
    int arr18_5[1] = {940};
    List *list18_5 = createListFromArray(arr18_5, 1);
    assert(removeElement(list18_5, 940));
    int expectedArr18_5[0] = {};
    List *expectedList18_5 = createListFromArray(expectedArr18_5, 0);
    assert(areListsEqual(list18_5, expectedList18_5));
    // Test case 6
    List *emptyList18 = new List();
    assert(!removeElement(emptyList18, 950)); // Remove from empty list
    assert(emptyList18->p_head == nullptr && emptyList18->p_tail == nullptr);
    // free memory
    freeList(expectedList18);
    freeList(expectedList18_2);
    freeList(expectedList18_3);
    freeList(expectedList18_4);
    freeList(expectedList18_5);
    freeList(list18);
    freeList(list18_2);
    freeList(list18_3);
    freeList(list18_4);
    freeList(list18_5);
    freeList(emptyList18);
    std::cout << "Passed" << std::endl;
    std::cout << "--- End running test cases ---" << std::endl;
    return 0;
}