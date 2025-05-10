#include "headers.hpp"
#include "functions.cpp"

int main(int argc, char *argv[]){
    // Nếu có khác 4 tham số dòng lệnh thì sai syntax
    if (argc != 4){
        std::cerr << "Invalid number of arguments" << std::endl;
        std::cerr << "Correct syntax: " << argv[0] << " ./sample file ./input file ./output file" << std::endl;
        // -1 là lỗi sai syntax
        return -1;
    }

    // Địa chỉ file database là tham số 2
    std::string sampleFile = argv[1];

    // Địa chỉ file input tìm kiếm là tham số 3
    std::string inputFile = argv[2];

    // Địa chri file output là tham số 4
    std::string outputFile = argv[3];

    // Luồng đọc và khởi tạo database
    std::ifstream sample_input(sampleFile);

    // Kiểm lỗi file giá trị raw
    if (!sample_input.is_open()){
        std::cerr << "Cannot open sample file." << std::endl;
        return 1;
    }

    // Khởi tạo vector
    std::vector<Company> list_company = readCompanyList(sampleFile);
    
    // Khởi tạo bảng băm
    HashTable* hash_table = createHashTable(list_company);

    // Luồng đọc file tìm kiếm
    std::ifstream search_input(inputFile);

    // Kiểm lỗi file tìm kiếm
    if (!search_input.is_open()){
        std::cerr << "Cannot open search file." << std::endl;
        return 1;
    }

    // Luồng xuất file đã tìm kiếm
    std::ofstream file_output(outputFile);

    // Kiểm lỗi file xuất
    if (!file_output.is_open()){
        std::cerr << "Cannot open output file."  << std::endl;
        return 1;
    }

    // Xuất file
    Read_Search_File_And_Print(inputFile, hash_table, outputFile);

    return 0;
}