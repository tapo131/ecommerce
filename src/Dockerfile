
# Sử dụng một image cơ bản
FROM node:14

# Thiết lập thư mục làm việc trong container
WORKDIR /app

# Sao chép package.json và package-lock.json vào thư mục làm việc
COPY package*.json ./

# Cài đặt các dependencies
RUN npm install

# Sao chép tất cả các mã nguồn vào thư mục làm việc
COPY . .

# Mở cổng 3000 để kết nối đến ứng dụng
EXPOSE 3000

# Chạy ứng dụng khi container khởi chạy
CMD ["node", "app.js"]
