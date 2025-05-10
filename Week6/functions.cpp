#include "headers.hpp"

// Đọc file và ghi vào vector
std::vector<Company> readCompanyList(std::string file_name)
{
    // Luồng đọc
    std::ifstream fin(file_name);

    // Biến đọc
    std::string reading_pointer = "";

    // Mảng ghi
    std::vector<Company> company_list;

    // Bỏ qua dòng đầu
    std::getline(fin, reading_pointer);

    // Đọc đến khi hết
    while (std::getline(fin, reading_pointer))
    {
        Company temp;
        // Tạo luồng stringstream để đọc dễ hơn, mỗi lần lặp sẽ reset luồng ss
        std::stringstream reader(reading_pointer);

        // Đọc dữ liệu vào cho biến tạm
        std::getline(reader, temp.name, '|');
        std::getline(reader, temp.profix_tax, '|');
        std::getline(reader, temp.address, '|');

        // Đẩy biến tạm
        company_list.push_back(temp);
    }

    return company_list;
}

// Mã hóa key
long long hashString(std::string company_name)
{
    // Giá trị tổng
    long long sum = 0;

    // Giá trị của số mũ p^i
    long long power = 1;

    // Hai tham số không đổi
    const long long MOD = 2000;
    const int P = 31;

    // Nếu chuỗi ít hơn 20 kí tự, lấy toàn bộ chuỗi
    // Nếu chuỗi dài hơn 20 kí tự, lấy 20 kí tự cuối
    size_t start_position;
    if (company_name.length() < 20){
        start_position = 0;
    }
    else{
        start_position = company_name.length() - 20;
    }

    // Biến i chạy tùy theo số lượng kí tự được lấy ở trên
    for (size_t i = 0; i < company_name.length() - start_position; i++)
    {
        // Chuyển đổi kí tự từ mã ASCII qua long long
            // Vì i chạy từ 0 nên để lấy đúng 20 kí tự cuối thì lấy start_position + i
        long long char_value = company_name[start_position + i];

        // Sử dụng tính chất modulo tổng bằng tổng các modulo
        sum = (sum + char_value * power) % MOD;

        // Tăng số mũ lên 1 lần
            // Lấy modulo vì tính chất trên để rút gọn số, tránh tràn
        power = (power * P) % MOD;
    }

    return sum;
}

// Khởi tạo bảng băm
HashTable *createHashTable(const std::vector<Company>& list_company){
    HashTable *h = new HashTable[2000];

    for (size_t i = 0; i < list_company.size(); i++)
    {
        // Biến lưu địa chỉ
        long long hash_key = hashString(list_company[i].name);

        // Nếu chưa có giá trị thì gán giá trị của công ty vào đó
        if (h[hash_key].key == -1)
        {
            h[hash_key].value = list_company[i];
            h[hash_key].key = hash_key;
        }
        // Đã có giá trị thì xử lý đụng độ
        else
        {
            // Con trỏ lưu giá trị đang đọc
            HashTable *temp = new HashTable;

            // Gán các giá trị đang đọc
            temp->value = list_company[i];
            temp->key = hash_key;
            
            // Cơ chế xử lý đụng độ giống như insert head trong linked list
            temp->collide = h[hash_key].collide;
            h[hash_key].collide = temp;
        }
    }

    return h;
}

// Chèn
void insert(HashTable*& hash_table, Company company)
{
    // Biến lấy địa chỉ
    long long hash_key = hashString(company.name);

    // Nếu chưa có giá trị thì thêm vào ô đó của bảng băm
    if (hash_table[hash_key].key == -1){
        hash_table[hash_key].value = company;
        hash_table[hash_key].key = hash_key;
    }
    // Nếu đã có thì thêm vào và xử lý đụng độ theo kiểu insert head
    else{
        HashTable* temp = new HashTable;
        temp->value = company;
        temp->key = hash_key;
        temp->collide = hash_table[hash_key].collide;
        hash_table[hash_key].collide = temp;
    }
}

// Tìm kiếm
Company* search(HashTable* hash_table, std::string company_name){
    // Lấy địa chỉ
    long long hash_key = hashString(company_name);

    // Nếu không có giá trị
    if (hash_table[hash_key].key == -1){
        return nullptr; 
    }
    // Nếu đã có
    else{
        // Con trỏ kết quả
        Company* temp = new Company;

        // Nếu không đụng độ thì gán giá trị cho con trỏ kết quả và trả về
        if (hash_table[hash_key].collide == nullptr){
            temp->address = hash_table[hash_key].value.address;
            temp->name = hash_table[hash_key].value.name;
            temp->profix_tax = hash_table[hash_key].value.profix_tax;
        }
        // Nếu đụng độ thì chia ra hai trường hợp nhỏ
        else{
            // Con trỏ đầu tiên trong linked list đụng độ là giá trị cần tìm
                // Gán giá trị và trả về
            if (hash_table[hash_key].value.name == company_name){
                temp->name = hash_table[hash_key].value.name;
                temp->address = hash_table[hash_key].value.address;
                temp->profix_tax = hash_table[hash_key].value.profix_tax;

                return temp;
            }

            // Ngược lại thì duyệt cho đến khi tìm thấy
            HashTable* cur = hash_table[hash_key].collide;

            // Duyệt như khi dùng Linked list
            while(cur->value.name != company_name){
                cur = cur->collide;
            }
            // Sau vòng lặp thì đã tìm thấy giá trị

            // Nếu chạy hết vòng lặp vẫn không có
            if (cur == nullptr){
                return nullptr;
            }

            // Nếu đã tìm thấy thì gán và trả về
            temp->name = cur->value.name;
            temp->address = cur->value.address;
            temp->profix_tax = cur->value.profix_tax;
        }

        return temp;
    }
}

// In giá trị theo đúng định dạng
void Print_Company_Value(Company* company, std::string out_directory){
    // Luồng xuất
    std::ofstream fout(out_directory, std::ios::app);

    // Nếu không tìm thấy
    if (company == nullptr){
        std::cerr << "Company not found!" << std::endl;
        return;
    }

    // Định dạng xuất
    fout << company->name << "|" << company->profix_tax << "|" << company->address << std::endl;
}

// Tìm và in
void Read_Search_File_And_Print(std::string search_file, HashTable* hash_table, std::string out_directory)
{
    // Luồng đọc
    std::ifstream fin(search_file);
    std::string reading_pointer = "";

    // Đọc đến hết file input
    while (std::getline(fin, reading_pointer))
    {
        // Gọi hàm tìm kiếm để lấy giá trị
        Company* company = search(hash_table, reading_pointer);

        // Gọi hàm in
        Print_Company_Value(company, out_directory);
    }
}