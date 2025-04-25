#include "headers.hpp"
#include "functions_used_include_DataGenerator.cpp"

int main(int argc, char* argv[]){
    // Chọn 5 kích cỡ mảng để tăng tính trực quan so với 4 kích cỡ mảng
        // Chọn tới giá trị tối đa là 30000 vì nếu chạy đến 50000 thì Quick sort sẽ bị tràn stack (vì kích cỡ tối đa của stack chỉ là 32000 phép gọi đệ quy)
    int size[6] = {1000, 3000, 5000, 10000, 30000};

    // Chọn cấp phát mảng động để dễ dàng xử lý hơn so với mảng tĩnh
    int *a = nullptr;
    // Biến đo số phép so sánh
    long long comparisionCount = 0;

    // Chương trình có chức năng đọc file input.txt và sắp xếp lại xuất ra file output.txt
        // Biến option ghi lại là có giá trị được nhập từ command line không, nếu không thì sẽ là -1
    int option;
        // Biến temp ghi lại thuật toán sắp xếp nào được lựa chọn
        // Ví dụ: ./main.exe -a merge-sort -i ./input.txt -o ./output.txt thì temp = 6 và gọi merge-sort
    int temp;
    // 2 string ghi lại địa chỉ nhập xuất file
    string in_dest, out_dest;

    while ((option = getopt(argc, argv, "a:i:o:")) != -1) {
        switch(option) {
            case 'a': {
                string algo(optarg);
                if (algo == "selection-sort") temp = 0;
                else if (algo == "insertion-sort") temp = 1;
                else if (algo == "bubble-sort") temp = 2;
                else if (algo == "shaker-sort") temp = 3;
                else if (algo == "shell-sort") temp = 4;
                else if (algo == "heap-sort") temp = 5;
                else if (algo == "merge-sort") temp = 6;
                else if (algo == "quick-sort") temp = 7;
                else if (algo == "counting-sort") temp = 8;
                else if (algo == "radix-sort") temp = 9;
                else if (algo == "flash-sort") temp = 10;
                else {
                    cerr << "Invalid algorithm argument." << endl;
                    return -1;
                }
                break;
            }

            case 'i': {
                in_dest = optarg;
                break;
            }

            case 'o': {
                out_dest = optarg;
                break;
            }

            default: {
                cerr << "Invalid argument." << endl;
                return -1;
            }
        }
    }

    // Đọc file đầu vào
    ifstream fin(in_dest);

    int n = 0;
    long long countTemp = 0;
    fin >> n;
    // Xóa kí tự khoảng trắng (whitespace)
    fin >> ws;
    int p[n];
    for (int i = 0; i < n; i++){
        fin >> p[i];
        fin >> ws;
    }
    switch(temp){
        case 0:
        Selection_sort(p, n, countTemp);
        break;
        case 1:
        Insertion_sort(p, n, countTemp);
        break;
        case 2:
        Bubble_sort(p, n, countTemp);
        break;
        case 3:
        Shaker_sort(p, n, countTemp);
        break;
        case 4:
        Shell_sort(p, n, countTemp);
        break;
        case 5:
        Heap_sort(p, n, countTemp);
        break;
        case 6:
        Merge_sort(p, 0, n - 1, countTemp);
        break;
        case 7:
        Quick_sort_Lomuto_without_medianOfThree(p, 0, n - 1, countTemp);
        break;
        case 8:
        Counting_sort(p, n, countTemp);
        break;
        case 9:{
            Radix_sort(a, n, countTemp);
            break;
        }
        case 10:
        Flash_sort(a, n, countTemp);
        break;
    }

    // Này dùng để ghi ra các giá trị về thời gian và phép so sánh để lập biểu đồ ở file report.pdf
    ofstream fout("1.txt");
    
    // Ghi ra mảng được sắp xếp
    ofstream f(out_dest);

    for (int i = 0; i < n; i++){
        f << p[i] << " ";
    }

    f.close();
    
    // Chương trình có chức năng tính thời gian chạy và số phép so sánh của thuật toán
        // Vòng for đầu tiên để lựa kiểu phân bố dữ liệu (ngẫu nhiên, đã được sắp xếp, được sắp xếp ngược, gần như được sắp xếp) của mảng
    for (int i = 0; i < 4; i++){
        switch(i){
            case 0:
            cout << "For random data array: " << endl;
            fout << "For random data array: " << endl;
            break;
            case 1:
            cout << "For sorted data array: " << endl;
            fout << "For sorted data array: " << endl;
            break;
            case 2:
            cout << "For reversed data array: " << endl;
            fout << "For reversed data array: " << endl;
            break;
            case 3:
            cout << "For nearly sorted data array: " << endl;
            fout << "For nearly sorted data array: " << endl;
            break;
        }

            // Vòng for thứ 2 để chọn kích cỡ mảng
        for (int j = 0; j < 5; j++){
            switch(j){
                case 0:
                cout << "For array with size of 1000: " << endl;
                fout << "For array with size of 1000: " << endl;
                break;
                case 1:
                cout << "For array with size of 3000: " << endl;
                fout << "For array with size of 3000: " << endl;
                break;
                case 2:
                cout << "For array with size of 5000: " << endl;
                fout << "For array with size of 5000: " << endl;
                break;
                case 3:
                cout << "For array with size of 10000: " << endl;
                fout << "For array with size of 10000: " << endl;
                break;
                case 4:
                cout << "For array with size of 30000: " << endl;
                fout << "For array with size of 30000: " << endl;
            }
            // Xóa mảng
            delete a;
            // Tái cấp phát
            a = new int [size[j]];
            // Tạo dữ liệu với những setting ở vòng lặp trên
            GenerateData(a, size[j], i);

            // Biến đo số phép so sánh
            comparisionCount = 0;
            // Hàm đo thời gian
            long long timeTaken = measureTime([&](){
                Selection_sort(a, size[j], comparisionCount);
            });
            // Xuất ra màn hình
            cout << "Selection sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            // Xuất ra file để xử lý dữ liệu làm biểu đồ
            fout << "Selection sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            // Thực hiện tương tự các bước trên cho các thuật toán còn lại
            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Insertion_sort(a, size[j], comparisionCount);
            });
            cout << "Insertion sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Insertion sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Bubble_sort(a, size[j], comparisionCount);
            });
            cout << "Bubble sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Bubble sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Shaker_sort(a, size[j], comparisionCount);
            });
            cout << "Shaker sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Shaker sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;
            
            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Shell_sort(a, size[j], comparisionCount);
            });
            cout << "Shell sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Shell sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Heap_sort(a, size[j], comparisionCount);
            });
            cout << "Heap sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Heap sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Merge_sort(a, 0, size[j] - 1, comparisionCount);
            });
            cout << "Merge sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Merge sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Quick_sort_Hoare_with_medianOfThree(a, 0, size[j] - 1, comparisionCount);
            });
            cout << "Quick sort Hoare with median of three (most optimized): " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Quick sort Hoare with median of three (most optimized): " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Quick_sort_Lomuto_with_medianOfThree(a, 0, size[j] - 1, comparisionCount);
            });
            cout << "Quick sort Lomuto with median of three: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Quick sort Lomuto with median of three: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;


            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Quick_sort_Hoare_without_medianOfThree(a, 0, size[j] - 1, comparisionCount);
            });
            cout << "Quick sort Hoare without median of three: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Quick sort Hoare without median of three: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Quick_sort_Lomuto_without_medianOfThree(a, 0, size[j] - 1, comparisionCount);
            });
            cout << "Quick sort Lomuto without median of three (least optimized): " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Quick sort Lomuto without median of three (least optimized): " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;
            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Counting_sort(a, size[j], comparisionCount);
            });
            cout << "Counting sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Counting sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Radix_sort(a, size[j], comparisionCount);
            });
            cout << "Radix sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Radix sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;

            delete a;
            a = new int [size[j]];
            GenerateData(a, size[j], i);

            comparisionCount = 0;
            timeTaken = measureTime([&](){
                Flash_sort(a, size[j], comparisionCount);
            });
            cout << "Flash sort: " << endl;
            cout << "Comparision count: " << comparisionCount << endl;
            cout << "Time used: " << timeTaken << endl;
            cout << endl;
            fout << "Flash sort: " << endl;
            fout << "Comparision count: " << comparisionCount << endl;
            fout << "Time used: " << timeTaken << endl;
            fout << endl;
        }
    }

    // Thu hồi bộ nhớ đã cấp phát
    delete a;
    a = nullptr;

    return 0;
}