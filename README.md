Đây là Ai nhận diện rác thải chạy bằng bằng python và Yolov8
Dataset được lấy từ RoboFlow

+Những lệnh Import

| import                          | Mục đích chính                                                                  |
| ------------------------------- | ------------------------------------------------------------------------------- |
| os                              | Quản lý file/thư mục, đường dẫn                                                 |
| time                            | Tạo tên file dựa trên thời gian thực                                            |
| subprocess                      | Gọi lệnh hệ thống, dùng ffmpeg chuyển định dạng                                 |
| cv2 (opencv-python)             | Đọc webcam, xử lý ảnh, hiển thị ảnh                                             |
| flask                           | Xây dựng web app                                                                |
| werkzeug.utils.secure\_filename | Đảm bảo tên file upload hợp lệ                                                  |
| ultralytics.YOLO                | Load mô hình YOLOv8 và dự đoán                                                  |
| collections.Counter             | Đếm số lượng các class trong kết quả nhận diện                                  |
| torch                           | Chỉ cần khi xử lý sâu hơn với PyTorch (thường không bắt buộc khi chạy đơn giản) |


+Cấu trúc thư mục dự án
 
project_folder/
├── video_model.py # File Flask chính (chạy web server)
├── load_model.py # Dùng để test nhận diện từ webcam\
├── train.py # Dùng để train model
├── requirements.txt # Các thư viện cần cài đặt
├── best.pt(1,2) # Mô hình YOLOv8 đã huấn luyện
├── templates/
│ └── index.html # Giao diện HTML
├── static/
│ ├── style.css # CSS cho giao diện
│ ├── uploads/ # Thư mục lưu video hoặc ảnh upload
│ └── results/ # Thư mục lưu kết quả xử lý

+Cách cài ứng dụng
-Cài đặt thư viện qua file requirements.txt (pip install -r requirements.txt)
-Đặt file `best.pt` vào cùng cấp với `video_model.py`
-Hoặc thay đổi đường dẫn trong `YOLO("best,1,2.pt")`(mỗi pt sẽ nhận diện khác nhau do train dataset khác nhau)
-Sau đó chạy qua (python video_model.py), click qua đường link để hiện lên giao diện web server

+Cài đặt webcam từ điện thoại

1. Cài iVCam (Windows,iphone) hoặc DroidCam (Linux/Mac)
2. Cắm điện thoại qua USB hoặc dùng chung 1 WiFi
3. Xác định index camera trong OpenCV
    ```python
    cv2.VideoCapture(1)  # hoặc 2, 3... tuỳ máy
    ```
4. Gán đúng index trong video_model.py:
    ```python
    camera_index = 1

+cách chạy ứng dụng  
-Nếu muốn tải video lên web để sử lý nhấn vào chọn tệp chọn video muốn upload sau đó nhấn Tải video & xử lý sau khi sử lí xong kết qua sẽ được lưu về static\results\yolo_result
-nếu muốn sử dụng camera từ điện thoại thì chỉ cần nhấn nút Bắt đầu camera và sau dữ liệu sẽ được gửi và sử lí  
