# ecommerce
#Running chatbot api: langverse\elasticsearch-7.10.2>elasticsearch.bat
#Running vrp api: 
Đảm bảo bạn đã cài đặt CMake và phiên bản của nó trên 3.1

cmake - -version

Chạy lệnh sau trong Terminal

g++ -std=c++11 main.cpp fileloader.cpp Graph.cpp colony.cpp vehicle.cpp -o main

./main

Để thay đổi thư mục input, truy cập file main.cpp và thay đổi tên thư mục ở dòng 24 "probs/Multi_depot/ThucNghiem/***.txt"

Các file input sẽ nằm trong file Multi_depot/ThucNghiem

—-------------------------------------------------------------------------------------------------------------

Hướng dẫn custom một data mới:

B1: Tạo một file .txt

B2: Dòng đầu tiên nhập 6 số nguyên tương ứng với

num_car>>car_capacity>>num_depot>>num_bike>>bike_capacity;

B3: n dòng tiếp theo nhập thông tin n điểm kho và khách hàng

Thông tin lần lượt là

x>>y>>demand>>openTime>>endTime>>serviceTime;

B4: nhập số -1 báo hiệu kết thúc khối

