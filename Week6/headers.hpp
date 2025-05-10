#ifndef COMPANY_INFORMATION_HASHING
#define COMPANY_INFORMATION_HASHING

// Các thư viện sử dụng
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

// Struct Company có tên, mã số thuế, địa chỉ
struct Company
{
    std::string name;
    std::string profix_tax;
    std::string address;
};

// Struct HashTable có khóa, công ty được hash, con trỏ để xử lý xung đột
    // Xung đột được xử lý theo kiểu Separate Chaining dùng con trỏ
struct HashTable
{
    long long key = -1;

    Company value;
    HashTable *collide = nullptr;
};

// Các hàm sử dụng
    // Đọc file vào vector
std::vector<Company> readCompanyList(std::string file_name);

    // Hash chuỗi
long long hashString(std::string company_name);

    // Khởi tạo bảng băm
HashTable *createHashTable(const std::vector<Company>& list_company);

    // Chèn vào bảng băm
void insert(HashTable*& hash_table, Company company);

    // Tìm kiếm trong bảng băm
Company* search(HashTable* hash_table, std::string company_name);

    // Hàm in giá trị của company
void Print_Company_Value(Company* company, std::string out_directory);

    // Hàm in ra giá trị cho output.txt
        // Sử dụng hàm in giá trị company
void Read_Search_File_And_Print(std::string search_file, HashTable* hash_table, std::string out_directory);

#endif