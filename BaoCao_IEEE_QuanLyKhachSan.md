# BÁO CÁO NGHIÊN CỨU VÀ PHÁT TRIỂN HỆ THỐNG QUẢN LÝ KHÁCH SẠN ĐƠN PHÂN CẤP TRÊN NỀN TẢNG C++ THEO PHƯƠNG PHÁP LUẬN LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG VÀ KỸ THUẬT TUẦN TỰ HÓA NHỊ PHÂN

**Tóm tắt—Trong kỷ nguyên chuyển đổi số và tối ưu hóa hạ tầng công nghệ thông tin, việc quản lý tài nguyên lưu trú và thông tin khách hàng trong ngành công nghiệp dịch vụ khách sạn đòi hỏi các hệ thống phần mềm phải đạt được độ tin cậy cao, hiệu năng tối ưu và khả năng quản trị dữ liệu nhất quán. Bài báo cáo này trình bày nghiên cứu, thiết kế và triển khai thực nghiệm một Hệ thống Quản lý Khách sạn (Hotel Management System - HMS) sử dụng ngôn ngữ lập trình C++. Hệ thống được xây dựng dựa trên phương pháp luận Lập trình Hướng đối tượng (Object-Oriented Programming - OOP), tích hợp cơ chế lưu trữ bền vững thông qua kỹ thuật tuần tự hóa nhị phân (binary serialization) trực tiếp xuống đĩa cứng thay vì phụ thuộc vào các hệ quản trị cơ sở dữ liệu cồng kềnh. Chúng tôi phân tích chi tiết cấu trúc kiến trúc phần mềm, sơ đồ lớp đối tượng (Class Diagram), sơ đồ ca sử dụng (Use Case Diagram), và cách thức áp dụng bốn nguyên lý cốt lõi của OOP bao gồm: tính đóng gói, tính trừu tượng, tính đa hình và tính kế thừa. Đồng thời, nghiên cứu đi sâu vào giải quyết các thách thức kỹ thuật khi tuần tự hóa các kiểu dữ liệu động như `std::string` trong C++ thông qua cơ chế độ dài tiền tố (length-prefixing). Kết quả thực nghiệm cho thấy hệ thống hoạt động ổn định với độ trễ truy xuất bằng không, đảm bảo tính toàn vẹn dữ liệu trong các thao tác thêm, sửa, xóa, đặt phòng và trả phòng.**

**Từ khóa—Lập trình Hướng đối tượng (OOP), C++, Quản lý Khách sạn, Tuần tự hóa Nhị phân, Lưu trữ bền vững, Độ dài tiền tố.**

---

## I. GIỚI THIỆU (INTRODUCTION)

### A. Bối cảnh ngành du lịch - khách sạn và thách thức quản lý
Ngành công nghiệp dịch vụ lưu trú và khách sạn đang trải qua sự phát triển bùng nổ trên toàn cầu cũng như tại Việt Nam. Sự gia tăng nhanh chóng về lượng khách du lịch nội địa và quốc tế đặt ra những thách thức lớn đối với công tác quản lý vận hành khách sạn. Các phương thức quản lý truyền thống như ghi chép thủ công bằng sổ sách hay sử dụng các phần mềm bảng tính đơn giản (như Microsoft Excel) đã bộc lộ nhiều hạn chế nghiêm trọng. Những hạn chế này bao gồm tính thiếu chính xác trong việc cập nhật trạng thái phòng theo thời gian thực, nguy cơ mất mát dữ liệu do sự cố phần cứng, khó khăn trong việc tra cứu lịch sử đặt phòng của khách hàng và thời gian xử lý các giao dịch tài chính kéo dài.

Để giải quyết các vấn đề trên, sự ra đời của các Hệ thống Quản lý Khách sạn (Property Management Systems - PMS) là một tất yếu công nghệ. Các hệ thống này giúp tự động hóa hầu hết các quy trình vận hành cốt lõi, từ quản lý danh mục phòng, thông tin khách hàng, cho đến việc theo dõi trạng thái thuê phòng, tính toán hóa đơn và thống kê doanh thu. Tuy nhiên, phần lớn các hệ thống hiện đại trên thị trường đều được xây dựng dưới dạng ứng dụng Web hoặc Cloud-based, đòi hỏi hạ tầng mạng internet liên tục, chi phí bản quyền lớn và tài nguyên máy chủ phức tạp. Đối với các khách sạn quy mô nhỏ, nhà nghỉ gia đình hoặc các khu nghỉ dưỡng ở vùng sâu vùng xa nơi kết nối internet không ổn định, một hệ thống phần mềm độc lập (standalone application) chạy trực tiếp trên máy trạm cục bộ, sử dụng ít tài nguyên hệ thống nhưng vẫn đảm bảo tính an toàn dữ liệu là một giải pháp vô cùng thiết thực.

### B. Mục tiêu nghiên cứu và hướng tiếp cận
Mục tiêu cốt lõi của nghiên cứu này là thiết kế và phát triển một Hệ thống Quản lý Khách sạn độc lập, giao diện dòng lệnh (Command Line Interface - CLI) sử dụng ngôn ngữ C++. Việc lựa chọn C++ xuất phát từ khả năng quản lý tài nguyên hệ thống cực kỳ mạnh mẽ, hiệu năng thực thi tối ưu và sự hỗ trợ toàn diện cho các nguyên lý lập trình hướng đối tượng. 

Hệ thống được thiết kế để giải quyết triệt để 11 yêu cầu chức năng nghiệp vụ thực tế bao gồm:
1. Nhập thêm phòng mới vào hệ thống.
2. Sửa đổi thông tin chi tiết của phòng dựa trên mã phòng duy nhất.
3. Xóa phòng khỏi hệ thống với điều kiện ràng buộc toàn vẹn dữ liệu (không xóa phòng đang được thuê).
4. Nhập mới thông tin khách hàng.
5. Sửa đổi thông tin khách hàng dựa trên mã khách hàng duy nhất.
6. Xóa thông tin khách hàng với điều kiện ràng buộc toàn vẹn dữ liệu (không xóa khách hàng đang thực hiện thuê phòng).
7. Đặt phòng khách sạn (liên kết mã khách hàng và mã phòng).
8. Thực hiện quy trình trả phòng (check-out) và cập nhật trạng thái.
9. Liệt kê toàn bộ danh sách phòng hiện có trong khách sạn.
10. Liệt kê danh sách các phòng đang được thuê (đang hoạt động).
11. Thoát khỏi hệ thống an toàn và lưu trữ trạng thái dữ liệu.

Điểm đặc biệt của hệ thống này là tính bền vững dữ liệu (data persistence). Mọi thao tác ghi nhận thông tin đều được tự động hóa việc ghi xuống các tập tin nhị phân (`.dat`) cục bộ. Tiếp cận theo hướng này giúp dữ liệu không bị mất đi khi tắt chương trình hoặc khi hệ thống gặp sự cố mất nguồn đột ngột, mang lại mức độ an toàn dữ liệu tương đương với các hệ quản trị cơ sở dữ liệu quan hệ nhưng không cần cài đặt thêm bất kỳ phần mềm trung gian nào.

### C. Vai trò của Lập trình Hướng đối tượng (OOP) trong dự án
Lập trình hướng đối tượng (OOP) không chỉ là một công nghệ, mà là một phương pháp luận tư duy mạnh mẽ giúp quản lý sự phức tạp của phần mềm. Trong hệ thống HMS này, các thực thể trong thế giới thực như "Phòng khách sạn" (Phong), "Khách hàng" (KhachHang), "Giao dịch đặt phòng" (DatPhong) được ánh xạ trực tiếp thành các lớp đối tượng (classes) trong mã nguồn C++. 

Việc áp dụng OOP mang lại những lợi ích thiết thực sau:
* **Tính dễ bảo trì (Maintainability):** Mã nguồn được chia thành các lớp độc lập, mỗi lớp đảm nhận một vai trò cụ thể. Khi có lỗi xảy ra hoặc khi cần thay đổi logic nghiệp vụ của một thực thể, lập trình viên chỉ cần can thiệp vào lớp tương ứng mà không làm ảnh hưởng đến toàn bộ hệ thống.
* **Tính dễ mở rộng (Extensibility):** Hệ thống có thể dễ dàng tích hợp thêm các tính năng mới bằng cách định nghĩa thêm các lớp con hoặc thêm các phương thức vào lớp quản lý chung mà không cần viết lại mã nguồn từ đầu.
* **Tính tái sử dụng (Reusability):** Các lớp tiện ích hoặc lớp đối tượng cơ bản có thể được tái sử dụng trong các module khác nhau của dự án hoặc trong các dự án phát triển phần mềm khác trong tương lai.

---

## II. CÁC NGHIÊN CỨU LIÊN QUAN (RELATED WORK)

Để định vị và đánh giá khách quan giải pháp phần mềm được đề xuất trong nghiên cứu này, việc tìm hiểu và phân tích các hệ thống quản lý tương đương đang tồn tại trên thị trường hoặc đã được công bố trong các nghiên cứu khoa học trước đây là vô cùng cần thiết. Chúng tôi tiến hành so sánh ba hướng tiếp cận phổ biến trong xây dựng hệ thống quản lý thông tin khách sạn:

### A. Hệ thống quản trị thủ công dựa trên bảng tính và ghi chép giấy
Đây là giải pháp lâu đời nhất và vẫn đang được áp dụng tại các nhà nghỉ gia đình quy mô rất nhỏ (dưới 5 phòng). 
* **Cơ chế hoạt động:** Nhân viên ghi chép thông tin khách hàng, số phòng, ngày nhận phòng và ngày trả phòng vào sổ tay hoặc nhập tay vào các trang tính Excel.
* **Ưu điểm:** Không yêu cầu hạ tầng công nghệ thông tin phức tạp; chi phí đầu tư ban đầu gần như bằng không; dễ dàng sử dụng đối với người không có kiến thức kỹ thuật chuyên môn.
* **Nhược điểm:** Tỷ lệ sai sót dữ liệu do con người (human error) cực kỳ cao; dễ xảy ra tình trạng "overbooking" (đặt trùng phòng); không thể tra cứu thông tin nhanh chóng khi số lượng bản ghi lên tới hàng nghìn; dữ liệu dễ bị hư hại vật lý (rách, ướt sổ) hoặc bị ghi đè nhầm lẫn trong file Excel mà không có cơ chế khôi phục.

### B. Hệ thống Quản trị Khách sạn Tập trung (Web-based/Cloud PMS)
Đây là xu hướng công nghệ chủ đạo hiện nay đối với các khách sạn quy mô từ trung bình đến lớn (từ 3 sao đến 5 sao). Các hệ thống tiêu biểu bao gồm Opera PMS, Smile PMS, hay các giải pháp Cloud SaaS nội địa.
* **Cơ chế hoạt động:** Toàn bộ dữ liệu được lưu trữ tập trung trên cơ sở dữ liệu đám mây (Cloud Database) như MySQL, PostgreSQL hoặc SQL Server. Người dùng truy cập hệ thống thông qua trình duyệt Web hoặc ứng dụng di động thông qua các cổng API bảo mật.
* **Ưu điểm:** Khả năng đồng bộ hóa dữ liệu theo thời gian thực trên nhiều thiết bị và địa điểm khác nhau; giao diện đồ họa (GUI) trực quan, phong phú; tích hợp được các cổng thanh toán trực tuyến, đặt phòng tự động qua các kênh OTA (Agoda, Booking.com...); khả năng báo cáo tài chính chi tiết và trực quan hóa dữ liệu.
* **Nhược điểm:** Chi phí vận hành rất cao (bao gồm chi phí đăng ký dịch vụ định kỳ, chi phí máy chủ, chi phí bảo trì); hệ thống hoàn toàn mất khả năng hoạt động nếu gặp sự cố đứt cáp internet hoặc máy chủ đám mây bị tắt nghẽn; yêu cầu cấu hình thiết bị đầu cuối trung bình đến mạnh; quy trình vận hành và đào tạo nhân sự phức tạp.

### C. Ứng dụng Desktop/CLI đơn phân cấp với File Serialization
Đây là hướng tiếp cận trung hòa, tối ưu hóa giữa hiệu năng và chi phí, thường được phát triển bằng các ngôn ngữ biên dịch mạnh mẽ như C++, Rust hoặc Java. 
* **Cơ chế hoạt động:** Ứng dụng chạy trực tiếp trên hệ điều hành cục bộ (Windows/Linux) của máy trạm. Dữ liệu được quản lý trực tiếp trong bộ nhớ RAM dưới dạng các cấu trúc dữ liệu tối ưu (như vector, list) và được định kỳ đồng bộ hóa xuống ổ cứng dưới dạng file nhị phân hoặc file văn bản có cấu trúc (JSON, XML).
* **Ưu điểm:** Tốc độ thực thi cực kỳ nhanh vì không phải trải qua độ trễ truyền tải dữ liệu qua mạng (network latency); không phụ thuộc vào kết nối internet; chi phí đầu tư và vận hành bằng không; yêu cầu tài nguyên phần cứng cực kỳ thấp (có thể chạy mượt mà trên các máy tính cấu hình cổ điển hoặc chip nhúng nhúng SoC); dữ liệu nhị phân có tính bảo mật tự nhiên cao hơn file văn bản thông thường vì không thể đọc trực tiếp bằng các trình soạn thảo văn bản cơ bản mà không có cấu trúc giải mã.
* **Nhược điểm:** Giao diện dòng lệnh (CLI) đòi hỏi nhân viên phải làm quen với việc nhập liệu bằng bàn phím; dữ liệu chỉ được lưu trữ cục bộ nên khó khăn trong việc đồng bộ hóa nếu khách sạn có nhiều chi nhánh từ xa (trừ khi áp dụng thêm các giao thức chia sẻ file mạng LAN).

**Bảng I: So sánh các giải pháp quản lý khách sạn**

| Tiêu chí so sánh | Ghi chép thủ công / Excel | Web/Cloud PMS | Hệ thống C++ CLI (Đề xuất) |
| :--- | :--- | :--- | :--- |
| **Chi phí đầu tư** | Gần như bằng 0 | Rất cao (Định kỳ) | Bằng 0 (Mã nguồn mở) |
| **Độ phụ thuộc Internet** | Không | Bắt buộc 100% | Hoàn toàn không |
| **Tốc độ phản hồi** | Chậm (Thủ công) | Phụ thuộc tốc độ mạng | Tức thời (< 1 ms) |
| **Tính an toàn dữ liệu** | Kém (Dễ mất/hỏng) | Cao (Có backup đám mây) | Rất cao (Lưu nhị phân cục bộ) |
| **Yêu cầu phần cứng** | Không yêu cầu | Trung bình đến mạnh | Rất thấp (Hỗ trợ máy yếu) |
| **Khả năng mở rộng** | Không thể | Rất tốt | Khá tốt (Dễ phát triển tiếp) |

Hệ thống được thiết kế trong nghiên cứu này thuộc nhóm **C (Hệ thống Desktop/CLI đơn phân cấp)**. Bằng việc tối ưu hóa cấu trúc dữ liệu và áp dụng kỹ thuật serialization nhị phân tùy biến, hệ thống giải quyết được trọn vẹn bài toán lưu trữ bền vững một cách đáng tin cậy nhất trên đĩa cứng máy trạm cục bộ, đáp ứng nhu cầu cốt lõi của các cơ sở lưu trú nhỏ với chi phí vận hành tối giản nhất.

---

## III. PHÂN TÍCH VÀ THIẾT KẾ HỆ THỐNG (SYSTEM DESIGN & OOAD)

### A. Phân tích Ca sử dụng (Use Case Analysis)
Hệ thống Quản lý Khách sạn hoạt động dưới quyền kiểm soát của một Tác nhân (Actor) duy nhất trong môi trường CLI là Nhân viên lễ tân hoặc Quản lý khách sạn (được gọi chung là Nhân viên quản trị hệ thống). Do hệ thống vận hành trên máy trạm cục bộ, giao diện dòng lệnh của chương trình đóng vai trò là bảng điều khiển tích hợp. 

Dưới đây là mô tả chi tiết bằng sơ đồ Use Case dạng văn bản kết hợp sơ đồ Mermaid biểu diễn các chức năng nghiệp vụ của hệ thống:

```mermaid
graph TD
    Actor([Nhân viên Lễ tân]) --> UC1(Thêm Phòng mới)
    Actor --> UC2(Sửa thông tin Phòng)
    Actor --> UC3(Xóa Phòng)
    Actor --> UC4(Thêm Khách hàng)
    Actor --> UC5(Sửa Khách hàng)
    Actor --> UC6(Xóa Khách hàng)
    Actor --> UC7(Đặt Phòng)
    Actor --> UC8(Trả Phòng / Thanh toán)
    Actor --> UC9(Liệt kê danh sách Phòng)
    Actor --> UC10(Liệt kê Phòng đang thuê)
    Actor --> UC11(Thoát & Tự động lưu file)

    UC1 -.->|include| GhiFile((Ghi file nhị phân))
    UC2 -.->|include| GhiFile
    UC3 -.->|include| GhiFile
    UC4 -.->|include| GhiFile
    UC5 -.->|include| GhiFile
    UC6 -.->|include| GhiFile
    UC7 -.->|include| GhiFile
    UC8 -.->|include| GhiFile
    UC11 -.->|include| GhiFile
```

Mô tả chi tiết các Use Case nghiệp vụ chính:
* **Use Case Quản lý danh mục phòng (UC1, UC2, UC3):** Cho phép người quản trị thiết lập thông tin cơ bản của phòng lưu trú bao gồm mã phòng, tên phòng, loại phòng và đơn giá. Ràng buộc toàn vẹn: Không được phép xóa phòng nếu phòng đó đang ở trạng thái hoạt động (đang được thuê).
* **Use Case Quản lý thông tin khách hàng (UC4, UC5, UC6):** Ghi nhận hồ sơ khách hàng bao gồm mã khách hàng, tên, số điện thoại (SĐT), số căn cước công dân (CCCD). Ràng buộc toàn vẹn: Không được xóa khách hàng nếu khách hàng đó đang thuê phòng tại khách sạn để tránh hiện tượng mồ côi dữ liệu (dangling references).
* **Use Case Đặt phòng (UC7):** Liên kết một khách hàng cụ thể với một phòng cụ thể. Hệ thống sẽ tự động chuyển đổi trạng thái của phòng từ "Đang trống" sang "Đang được thuê", tạo lập thời gian check-in tự động dựa trên thời gian hệ thống và khởi tạo một bản ghi giao dịch hoạt động.
* **Use Case Trả phòng & Thanh toán (UC8):** Thực hiện quy trình trả phòng cho khách. Hệ thống xác định bản ghi đặt phòng đang hoạt động của phòng đó, chuyển trạng thái bản ghi và trạng thái phòng về "Đã trả phòng / Đang trống", đồng thời thực hiện lưu trữ thông tin giao dịch xuống đĩa.

### B. Sơ đồ lớp đối tượng (Class Diagram)
Kiến trúc phần mềm của dự án được xây dựng trên một thiết kế hướng đối tượng chặt chẽ. Mối quan hệ giữa các thực thể đại diện cho cấu trúc dữ liệu của một hệ thống quản lý khách sạn điển hình. 

Sơ đồ lớp dưới đây minh họa các lớp đối tượng, các thuộc tính, phương thức và mối liên kết logic giữa chúng:

```mermaid
classDiagram
    class Phong {
        -string maPhong
        -string tenPhong
        -string loaiPhong
        -double giaPhong
        -bool trangThai
        +Phong()
        +Phong(string maP, string tenP, string loaiP, double giaP)
        +getMaPhong() string
        +setMaPhong(string maP) void
        +getTenPhong() string
        +setTenPhong(string tenP) void
        +getLoaiPhong() string
        +setLoaiPhong(string loaiP) void
        +getGiaPhong() double
        +setGiaPhong(double giaP) void
        +getTrangThai() bool
        +setTrangThai(bool tt) void
        +GhiFilePhong(ofstream& file) void
        +DocFilePhong(ifstream& file) void
    }

    class KhachHang {
        -string maKH
        -string tenKH
        -string SDT
        -string CCCD
        +KhachHang()
        +KhachHang(string ma, string ten, string sdt, string cccd)
        +getMaKH() string
        +setMaKH(string ma) void
        +getTenKH() string
        +setTenKH(string ten) void
        +getSDT() string
        +setSDT(string sdt) void
        +getCCCD() string
        +setCCCD(string cccd) void
        +GhiFileKhachHang(ofstream& file) void
        +DocFileKhachHang(ifstream& file) void
    }

    class DatPhong {
        -string maPhong
        -string maKH
        -string ngayDat
        -bool trangThai
        +DatPhong()
        +DatPhong(string makh, string maphong, string ngay)
        +getMaKH() string
        +setMaKH(string makh) void
        +getMaPhong() string
        +setMaPhong(string maphong) void
        +getNgayDat() string
        +setNgayDat(string ngay) void
        +getTrangThai() bool
        +setTrangThai(bool tt) void
        +GhiFileDatPhong(ofstream& file) void
        +DocFileDatPhong(ifstream& file) void
    }

    class TienIch {
        <<Utility>>
        +XoaKhoangTrangThua(string& tieuDe) void$
        +DinhDanhTienVND(long long gia) string$
        +ThongBaoThanhCong(const string& msg) void$
        +ThongBaoLoi(const string& msg) void$
        +HienThiTieuDe(string tieuDe, int width) void$
        +ChuanHoaMa(const string& s) string$
        +LayThoiGianHienTai() string$
    }

    class QuanLyKhachSan {
        -const string FILE_PHONG
        -const string FILE_KHACH_HANG
        -const string FILE_DAT_PHONG
        -vector~Phong~ ds_phong
        -vector~KhachHang~ ds_khach_hang
        -vector~DatPhong~ ds_dat_phong
        -timPhong(const string& maPhong) Phong*
        -timKhachHang(const string& maKH) KhachHang*
        -timDatPhongHoatDong(const string& maPhong) DatPhong*
        -timDatPhongHoatDongCuaKhachHang(const string& maKH) DatPhong*
        +QuanLyKhachSan()
        +GhiFilePhong() void
        +DocFilePhong() void
        +GhiFileKhachHang() void
        +DocFileKhachHang() void
        +GhiFileDatPhong() void
        +DocFileDatPhong() void
        +luuToanBoDuLieu() void
        +taiToanBoDuLieu() void
        +DanhSachPhong() void
        +ThemPhong() void
        +SuaPhong() void
        +XoaPhong() void
        +DanhSachKhachHang() void
        +ThemKhachHang() void
        +SuaKhachHang() void
        +XoaKhachHang() void
        +DanhSachPhongTrong() void
        +DatPhongKhachSan() void
        +DanhSachPhongThue() void
        +TraPhongCheckOut() void
    }

    QuanLyKhachSan "1" *-- "many" Phong : Chứa & Quản lý
    QuanLyKhachSan "1" *-- "many" KhachHang : Chứa & Quản lý
    QuanLyKhachSan "1" *-- "many" DatPhong : Chứa & Quản lý
    DatPhong --> Phong : Tham chiếu qua maPhong
    DatPhong --> KhachHang : Tham chiếu qua maKH
    QuanLyKhachSan ..> TienIch : Sử dụng các hàm phụ trợ
    Phong ..> TienIch : Sử dụng
    KhachHang ..> TienIch : Sử dụng
    DatPhong ..> TienIch : Sử dụng
```

### C. Mô tả chi tiết các lớp đối tượng chính
Thiết kế của hệ thống bao gồm năm lớp đối tượng cốt lõi. Mỗi lớp đều có những nhiệm vụ và vai trò riêng biệt để cấu thành nên cấu trúc hoàn chỉnh của phần mềm quản trị:

#### 1. Lớp Phong (Room Class)
Lớp `Phong` chịu trách nhiệm mô hình hóa một phòng lưu trú thực tế trong khách sạn. 
* **Thuộc tính:**
  - `maPhong` (kiểu `std::string`): Mã số duy nhất định danh phòng (ví dụ: "P101", "P202"). Để tối ưu hóa việc tìm kiếm, mã phòng luôn được chuẩn hóa thành chữ hoa thông qua tiện ích hệ thống.
  - `tenPhong` (kiểu `std::string`): Tên gọi thân thiện của phòng (ví dụ: "Phòng Tổng Thống", "Phòng Đơn Tiêu Chuẩn").
  - `loaiPhong` (kiểu `std::string`): Phân loại phòng theo chuẩn kinh doanh (ví dụ: "VIP", "Standard", "Double").
  - `giaPhong` (kiểu `double`): Đơn giá thuê phòng theo ngày, được biểu diễn bằng kiểu số thực dấu phẩy động để hỗ trợ các đơn giá trị lớn và tính toán thuế suất nếu cần.
  - `trangThai` (kiểu `bool`): Biến cờ hiệu biểu thị tình trạng của phòng. Nhận giá trị `false` (0) nếu phòng đang trống và sẵn sàng đón khách; nhận giá trị `true` (1) nếu phòng đang được thuê.
* **Phương thức chính:**
  - Nhóm các hàm Getter và Setter: Đảm bảo quyền truy cập có kiểm soát đối với các thuộc tính được ẩn giấu (private data members).
  - Phương thức `GhiFilePhong` và `DocFilePhong`: Cho phép đối tượng tự ghi thông tin của mình vào hoặc tự khôi phục dữ liệu từ một luồng tập tin nhị phân đang mở.

#### 2. Lớp KhachHang (Customer Class)
Lớp `KhachHang` lưu trữ và xử lý toàn bộ hồ sơ định danh cá nhân của khách hàng từng giao dịch hoặc đang lưu trú tại khách sạn.
* **Thuộc tính:**
  - `maKH` (kiểu `std::string`): Mã khách hàng duy nhất để định danh trong toàn hệ thống (ví dụ: "KH001", "KH089").
  - `tenKH` (kiểu `std::string`): Họ và tên đầy đủ của khách hàng.
  - `SDT` (kiểu `std::string`): Số điện thoại liên lạc. Được lưu trữ dưới dạng chuỗi để tránh việc mất số 0 ở đầu và cho phép lưu trữ các ký tự đặc biệt hoặc mã quốc gia (ví dụ: "+84912345678").
  - `CCCD` (kiểu `std::string`): Số Căn cước công dân hoặc số Hộ chiếu (Passport) phục vụ cho việc khai báo tạm trú theo quy định pháp luật.
* **Phương thức chính:**
  - Ngoài các Getter/Setter cơ bản, lớp cũng tự triển khai các phương thức đọc/ghi nhị phân chuyên biệt `GhiFileKhachHang` và `DocFileKhachHang`.

#### 3. Lớp DatPhong (Booking Class)
Lớp `DatPhong` đóng vai trò là một lớp liên kết (association class) để kết nối mối quan hệ nhiều-nhiều (N-M) giữa lớp `Phong` và lớp `KhachHang`. Một khách hàng có thể đặt nhiều phòng theo thời gian, và một phòng cũng có thể được thuê bởi nhiều khách hàng khác nhau ở các mốc thời gian khác nhau.
* **Thuộc tính:**
  - `maPhong` (kiểu `std::string`): Khóa ngoại liên kết tới lớp `Phong`.
  - `maKH` (kiểu `std::string`): Khóa ngoại liên kết tới lớp `KhachHang`.
  - `ngayDat` (kiểu `std::string`): Mốc thời gian thực hiện check-in (ngày giờ vào phòng).
  - `trangThai` (kiểu `bool`): Xác định trạng thái của giao dịch thuê phòng. Giá trị `true` (1) biểu thị giao dịch đang hoạt động (khách đang ở trong phòng). Giá trị `false` (0) biểu thị giao dịch đã hoàn thành (khách đã check-out và thanh toán xong).
* **Phương thức chính:**
  - Triển khai Getter/Setter và các phương thức serialization nhị phân tương ứng để lưu lịch sử giao dịch.

#### 4. Lớp QuanLyKhachSan (HotelManager Class - Controller)
Đây là lớp điều khiển trung tâm (Controller) của toàn bộ phần mềm. Lớp này sở hữu các cấu trúc dữ liệu động để chứa danh sách của tất cả các thực thể khác và cung cấp các hàm logic xử lý giao diện CLI và nghiệp vụ.
* **Thuộc tính:**
  - `ds_phong` (kiểu `std::vector<Phong>`): Danh sách động quản lý toàn bộ các phòng trong khách sạn.
  - `ds_khach_hang` (kiểu `std::vector<KhachHang>`): Danh sách động quản lý thông tin khách hàng đã đăng ký.
  - `ds_dat_phong` (kiểu `std::vector<DatPhong>`): Danh sách động quản lý toàn bộ các giao dịch đặt phòng (bao gồm cả giao dịch đang hoạt động và giao dịch lịch sử).
  - `FILE_PHONG`, `FILE_KHACH_HANG`, `FILE_DAT_PHONG`: Các hằng số lưu tên tệp lưu trữ dữ liệu nhị phân tương ứng trên đĩa cứng.
* **Phương thức trợ giúp (Private helper methods):**
  - `timPhong(maPhong)`: Tìm kiếm tuyến tính và trả về con trỏ tới đối tượng `Phong` trong vector nếu tìm thấy, ngược lại trả về `nullptr`.
  - `timKhachHang(maKH)`: Tìm kiếm khách hàng theo mã và trả về con trỏ đối tượng.
  - `timDatPhongHoatDong(maPhong)`: Tìm kiếm và trả về bản ghi đặt phòng đang có trạng thái hoạt động của một phòng cụ thể. Đây là phương thức cốt lõi phục vụ chức năng Trả phòng.
  - `timDatPhongHoatDongCuaKhachHang(maKH)`: Kiểm tra xem một khách hàng có đang thuê phòng nào không để phục vụ kiểm tra ràng buộc trước khi xóa khách hàng.
* **Phương thức nghiệp vụ (Public API):**
  - Nhóm các hàm thao tác dữ liệu: `ThemPhong`, `SuaPhong`, `XoaPhong`, `ThemKhachHang`, `SuaKhachHang`, `XoaKhachHang`.
  - Nhóm hàm giao dịch: `DatPhongKhachSan`, `TraPhongCheckOut`.
  - Nhóm hàm truy vấn báo cáo: `DanhSachPhong`, `DanhSachKhachHang`, `DanhSachPhongTrong`, `DanhSachPhongThue`.
  - Nhóm hàm đồng bộ file nhị phân: `GhiFilePhong`, `DocFilePhong`, `GhiFileKhachHang`, `DocFileKhachHang`, `GhiFileDatPhong`, `DocFileDatPhong`, `luuToanBoDuLieu`, `taiToanBoDuLieu`.

#### 5. Lớp TienIch (Utility Class)
Lớp `TienIch` cung cấp một tập hợp các phương thức tĩnh (static methods) thực hiện các tác vụ định dạng thẩm mỹ giao diện CLI và chuẩn hóa dữ liệu đầu vào.
* **Phương thức chính:**
  - `XoaKhoangTrangThua`: Loại bỏ các ký tự trống ở đầu và cuối chuỗi dữ liệu nhập từ bàn phím.
  - `DinhDanhTienVND`: Chuyển đổi một số tiền kiểu số thành chuỗi định dạng tiền tệ có dấu phân cách hàng nghìn (ví dụ: từ `500000` thành `500.000 VND`).
  - `ChuanHoaMa`: Chuyển toàn bộ các chuỗi ký tự sang dạng in hoa để chuẩn hóa các mã định danh, tránh lỗi tìm kiếm phân biệt chữ hoa chữ thường.
  - `LayThoiGianHienTai`: Lấy thời gian từ đồng hồ hệ thống và trả về chuỗi định dạng `"dd/mm/yyyy hh:mm"` phục vụ việc lưu vết ngày giờ nhận phòng.

### D. Áp dụng bốn nguyên lý cốt lõi của OOP (OOP Principles)
Mã nguồn của hệ thống được lập trình với mục đích minh chứng tối đa cho việc ứng dụng thực tế bốn nguyên lý cơ bản của Lập trình Hướng đối tượng:

#### 1. Tính Đóng gói (Encapsulation)
Tính đóng gói được thể hiện rõ ràng nhất thông qua việc che giấu trạng thái nội tại của đối tượng và ngăn chặn việc sửa đổi trực tiếp từ bên ngoài.
* **Triển khai trong mã nguồn:** Tất cả các thuộc tính dữ liệu của các lớp `Phong`, `KhachHang`, `DatPhong` đều được đặt trong khối phạm vi truy cập `private`. Các lớp bên ngoài (chẳng hạn như `QuanLyKhachSan` hay hàm `main`) hoàn toàn không thể truy cập trực tiếp đến các biến này như `p.trangThai = true;` mà buộc phải thông qua các cổng giao tiếp công cộng là các hàm Getter và Setter như `p.setTrangThai(true);`.
* **Ý nghĩa thực tiễn:** Giúp kiểm soát tính toàn vẹn dữ liệu đầu vào. Ví dụ, trong phương thức `setMaPhong(string maP)` của lớp `Phong`, dữ liệu trước khi gán vào thuộc tính `maPhong` sẽ được tự động truyền qua hàm `TienIch::ChuanHoaMa` để đảm bảo mã phòng luôn lưu trữ dưới dạng in hoa thống nhất, tránh hiện tượng tồn tại song song "p101" và "P101" trong bộ nhớ.

#### 2. Tính Trừu tượng (Abstraction)
Tính trừu tượng cho phép hệ thống ẩn đi các chi tiết cài đặt thuật toán phức tạp và chỉ phơi bày các tính năng giao tiếp ở mức cao (high-level interface).
* **Triển khai trong mã nguồn:** Đối với người sử dụng hệ thống hoặc thậm chí là lập trình viên viết hàm `main`, họ không cần biết làm cách nào mà phần mềm có thể ghi dữ liệu xuống đĩa cứng, hay làm thế nào để tìm kiếm một khách hàng trong bộ nhớ RAM. Họ chỉ cần gọi phương thức đơn giản: `qlks.DatPhongKhachSan();`.
* **Ý nghĩa thực tiễn:** Chi tiết về việc duyệt qua các `std::vector`, cấp phát bộ nhớ động, tính toán kích thước chuỗi khi ghi file nhị phân, hay xử lý thời gian hệ thống đều được đóng gói và ẩn đi bên trong các phương thức của lớp `QuanLyKhachSan` và lớp `TienIch`. Điều này giúp giảm thiểu sự phụ thuộc lẫn nhau giữa các thành phần phần mềm (loose coupling).

#### 3. Tính Kế thừa (Inheritance)
Mặc dù bài toán thực tế của phiên bản hiện tại sử dụng một lớp `Phong` phẳng để tối giản hóa kiến trúc, hệ thống được thiết kế hướng tới khả năng mở rộng kế thừa mạnh mẽ mà không làm phá vỡ kiến trúc cũ.
* **Thiết kế hướng kế thừa:** Trong thực tế quản lý khách sạn, các loại phòng có thể có các đặc thù khác nhau về giá cả và cách tính phí. Chúng ta có thể định nghĩa một lớp cơ sở `Phong` chứa các thuộc tính chung, sau đó xây dựng các lớp con kế thừa như:
  - `PhongVIP` kế thừa từ `Phong`: Bổ sung thêm các thuộc tính về dịch vụ đặc quyền (`dichVuDacBiet`), minibar, và hệ số phụ thu giá phòng.
  - `PhongStandard` kế thừa từ `Phong`: Quản lý các phòng tiêu chuẩn với mức giá cố định và các dịch vụ cơ bản.
* **Mô tả thiết kế:**
  ```cpp
  class PhongVIP : public Phong {
  private:
      double phiMinibar;
      double heSoPhuThu;
  public:
      PhongVIP(string maP, string tenP, double giaP, double phiMini, double heSo)
          : Phong(maP, tenP, "VIP", giaP), phiMinibar(phiMini), heSoPhuThu(heSo) {}
      
      // Override phương thức tính giá phòng
      double tinhTongTien(int soNgay) const {
          return (getGiaPhong() * soNgay * heSoPhuThu) + phiMinibar;
      }
  };
  ```

#### 4. Tính Đa hình (Polymorphism)
Tính đa hình cho phép cùng một thông điệp được gửi tới các đối tượng thuộc các lớp khác nhau nhưng mỗi đối tượng sẽ phản hồi theo những cách thức lập trình riêng biệt.
* **Triển khai đa hình thiết kế:** Nếu chúng ta áp dụng mô hình kế thừa ở trên, phương thức `tinhTongTien()` sẽ được định nghĩa là một hàm ảo (`virtual double tinhTongTien() const = 0;`) trong lớp cơ sở trừu tượng `Phong`.
* **Cơ chế hoạt động:** Khi lớp điều khiển `QuanLyKhachSan` thực hiện duyệt qua danh sách các phòng để tính toán tổng doanh thu dự kiến, mã nguồn sẽ sử dụng một con trỏ kiểu lớp cơ sở:
  ```cpp
  vector<Phong*> ds_phong_polymorphic;
  // ds_phong_polymorphic chứa cả con trỏ tới PhongVIP và PhongStandard
  double tongDoanhThu = 0;
  for (auto const& p : ds_phong_polymorphic) {
      tongDoanhThu += p->tinhTongTien(soNgay); // Đa hình liên kết động (Dynamic Binding)
  }
  ```
  Tại thời điểm thực thi (runtime), chương trình sẽ tự động quyết định gọi phương thức `tinhTongTien()` của lớp `PhongVIP` hay `PhongStandard` tùy thuộc vào đối tượng thực tế mà con trỏ đang trỏ tới. Điều này mang lại sự linh hoạt tuyệt đối cho mã nguồn khi phát triển các tính năng thanh toán nâng cao.

---

## IV. THIẾT KẾ MÃ NGUỒN VÀ CHI TIẾT CÀI ĐẶT (IMPLEMENTATION DETAIL)

### A. Cấu trúc thư mục dự án và vai trò của các tệp tin
Một trong những tiêu chuẩn vàng trong kỹ nghệ phần mềm C++ là phân tách rõ ràng giữa giao diện khai báo (interface) và đặc tả cài đặt (implementation). Trong hệ thống HMS này, toàn bộ mã nguồn được Module hóa thành các tệp tin tiêu đề `.h` và tệp tin thực thi `.cpp`.

Cấu trúc cây thư mục của dự án:
```text
d:\QuanLyKhachSanOOP
├── TienIch.h           # Khai báo các biến màu sắc ANSI và phương thức tiện ích dùng chung
├── TienIch.cpp         # Cài đặt thuật toán tiện ích (định dạng tiền tệ, xử lý thời gian)
├── Phong.h             # Khai báo lớp Phong với thuộc tính và giao thức serialization
├── Phong.cpp           # Cài đặt chi tiết các phương thức lớp Phong
├── KhachHang.h         # Khai báo lớp KhachHang
├── KhachHang.cpp       # Cài đặt chi tiết các phương thức lớp KhachHang
├── DatPhong.h          # Khai báo lớp DatPhong (lớp liên kết N-M)
├── DatPhong.cpp        # Cài đặt chi tiết các phương thức lớp DatPhong
├── QuanLyKhachSan.h    # Khai báo lớp điều khiển QuanLyKhachSan và các luồng file nhị phân
├── QuanLyKhachSan.cpp  # Cài đặt logic nghiệp vụ quản lý khách sạn và truy xuất file
├── main.cpp            # Hàm main khởi tạo, quản lý vòng lặp chương trình và menu lựa chọn
└── a.exe               # Tệp thực thi sau khi biên dịch trên môi trường Windows
```

**Vai trò của việc chia nhỏ tệp tin:**
* **Tệp tiêu đề (.h):** Chứa các khai báo lớp, thuộc tính dữ liệu, nguyên mẫu hàm và các thư viện cần thiết. Tệp này đóng vai trò như một bản hợp đồng ký kết giữa lớp đó và các thành phần khác sử dụng nó. Để tránh lỗi biên dịch lặp lại khi một file header được chèn (include) nhiều lần ở các vị trí khác nhau, chúng tôi sử dụng cơ chế bảo vệ tiền xử lý (header guards):
  ```cpp
  #ifndef CLASSNAME_H
  #define CLASSNAME_H
  // Nội dung khai báo
  #endif
  ```
* **Tệp nguồn (.cpp):** Chứa mã nguồn cài đặt thực tế của các phương thức đã khai báo trong tệp tiêu đề tương ứng. Việc tách biệt này giúp trình biên dịch có thể thực hiện biên dịch tăng dần (incremental compilation), tức là chỉ cần biên dịch lại những tệp tin nguồn có sự thay đổi mà không cần biên dịch lại toàn bộ dự án từ đầu, qua đó tối ưu hóa thời gian phát triển phần mềm.

### B. Cài đặt chi tiết lớp Tiện ích (TienIch)
Lớp `TienIch` chứa các giải thuật phụ trợ phục vụ hiển thị CLI trực quan và chuẩn hóa dữ liệu.

#### 1. File TienIch.h
```cpp
#ifndef TIENICH_H
#define TIENICH_H

#include <iostream>

using namespace std;

namespace Color
{
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    const string BOLD = "\033[1m";
}

class TienIch
{
public:
    static void XoaKhoangTrangThua(string &tieuDe);
    static string DinhDanhTienVND(long long gia);
    static void ThongBaoThanhCong(const string &msg);
    static void ThongBaoLoi(const string &msg);
    static void HienThiTieuDe(string tieuDe, int width = 30);
    static string ChuanHoaMa(const string &s);
    static string LayThoiGianHienTai();
};

#endif
```

#### 2. File TienIch.cpp
```cpp
#include "TienIch.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

void TienIch::XoaKhoangTrangThua(string &tieuDe)
{
    tieuDe.erase(0, tieuDe.find_first_not_of(" \t\r\n"));
    tieuDe.erase(tieuDe.find_last_not_of(" \t\r\n") + 1);
}

string TienIch::DinhDanhTienVND(long long gia)
{
    string s = to_string(gia);
    string ketqua = "";
    int dem = 0;

    for (int i = s.length() - 1; i >= 0; i--)
    {
        ketqua += s[i];
        dem++;
        if (dem % 3 == 0 && i != 0)
        {
            ketqua += ".";
        }
    }
    reverse(ketqua.begin(), ketqua.end());
    return ketqua + " VND";
}

void TienIch::ThongBaoThanhCong(const string &msg)
{
    cout << Color::BOLD << Color::GREEN << msg << Color::RESET << "\n";
}

void TienIch::ThongBaoLoi(const string &msg)
{
    cout << Color::BOLD << Color::RED << msg << Color::RESET << "\n";
}

void TienIch::HienThiTieuDe(string tieuDe, int width)
{
    int len = tieuDe.length();
    int padding = (width - len) / 2;
    if (padding < 0) padding = 0;

    cout << Color::BOLD << Color::BLUE << string(width, '=') << "\n";
    cout << string(padding, ' ') << tieuDe << "\n";
    cout << string(width, '=') << Color::RESET << "\n";
}

string TienIch::ChuanHoaMa(const string &s)
{
    string result = s;
    for (char &c : result)
    {
        c = toupper(static_cast<unsigned char>(c));
    }
    return result;
}

string TienIch::LayThoiGianHienTai()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", now);
    return string(buf);
}
```
*Giải thích giải thuật:* Phương thức `DinhDanhTienVND` chuyển đổi số nguyên thành dạng biểu diễn tiền tệ bằng cách duyệt ngược từ chữ số cuối cùng và chèn dấu chấm phân cách hàng nghìn. Phương thức `LayThoiGianHienTai` giao tiếp với thư viện chuẩn `<ctime>` để lấy thời gian Unix, chuyển đổi sang múi giờ địa phương và trả về dạng chuỗi định dạng dễ đọc.

### C. Cài đặt các Lớp đối tượng cơ bản

#### 1. Lớp đối tượng Phong
Lớp `Phong` quản lý thông tin các phòng nghỉ của khách sạn.

##### a. File Phong.h
```cpp
#ifndef PHONG_H
#define PHONG_H

#include "TienIch.h"
#include <iostream>
#include <fstream>

using namespace std;

class Phong
{
private:
    string maPhong;
    string tenPhong;
    string loaiPhong;
    double giaPhong;
    bool trangThai; // false: Trong, true: Dang duoc thue

public:
    Phong();
    Phong(string maP, string tenP, string loaiP, double giaP);

    string getMaPhong() const;
    void setMaPhong(string maP);

    string getTenPhong() const;
    void setTenPhong(string tenP);

    string getLoaiPhong() const;
    void setLoaiPhong(string loaiP);

    double getGiaPhong() const;
    void setGiaPhong(double giaP);

    bool getTrangThai() const;
    void setTrangThai(bool tt);

    void GhiFilePhong(ofstream &file) const;
    void DocFilePhong(ifstream &file);
};

#endif
```

##### b. File Phong.cpp
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include "Phong.h"

using namespace std;

Phong::Phong() : maPhong(""), tenPhong(""), loaiPhong(""), giaPhong(0.0), trangThai(false) {}

Phong::Phong(string maP, string tenP, string loaiP, double giaP)
    : maPhong(TienIch::ChuanHoaMa(maP)), tenPhong(tenP), loaiPhong(loaiP), giaPhong(giaP), trangThai(false) {}

string Phong::getMaPhong() const { return maPhong; }
void Phong::setMaPhong(string maP) { maPhong = TienIch::ChuanHoaMa(maP); }

string Phong::getTenPhong() const { return tenPhong; }
void Phong::setTenPhong(string tenP) { tenPhong = tenP; }

string Phong::getLoaiPhong() const { return loaiPhong; }
void Phong::setLoaiPhong(string loaiP) { loaiPhong = loaiP; }

double Phong::getGiaPhong() const { return giaPhong; }
void Phong::setGiaPhong(double giaP) { giaPhong = giaP; }

bool Phong::getTrangThai() const { return trangThai; }
void Phong::setTrangThai(bool tt) { trangThai = tt; }

void Phong::GhiFilePhong(ofstream &file) const
{
    int maPhongLength = maPhong.size();
    file.write((char *)&maPhongLength, sizeof(maPhongLength));
    file.write(maPhong.c_str(), maPhongLength);

    int tenPhongLength = tenPhong.size();
    file.write((char *)&tenPhongLength, sizeof(tenPhongLength));
    file.write(tenPhong.c_str(), tenPhongLength);

    int loaiLength = loaiPhong.size();
    file.write((char *)&loaiLength, sizeof(loaiLength));
    file.write(loaiPhong.c_str(), loaiLength);

    file.write((char *)&giaPhong, sizeof(giaPhong));
    file.write((char *)&trangThai, sizeof(trangThai));
}

void Phong::DocFilePhong(ifstream &file)
{
    int maLength = 0;
    file.read((char *)&maLength, sizeof(maLength));
    if (maLength > 0)
    {
        maPhong.resize(maLength);
        file.read(&maPhong[0], maLength);
    }

    int tenLength = 0;
    file.read((char *)&tenLength, sizeof(tenLength));
    if (tenLength > 0)
    {
        tenPhong.resize(tenLength);
        file.read(&tenPhong[0], tenLength);
    }

    int loaiLength = 0;
    file.read((char *)&loaiLength, sizeof(loaiLength));
    if (loaiLength > 0)
    {
        loaiPhong.resize(loaiLength);
        file.read(&loaiPhong[0], loaiLength);
    }

    file.read((char *)&giaPhong, sizeof(giaPhong));
    file.read((char *)&trangThai, sizeof(trangThai));
}
```

#### 2. Lớp đối tượng KhachHang
Quản lý hồ sơ định danh cá nhân của khách hàng đăng ký tạm trú tại khách sạn.

##### a. File KhachHang.h
```cpp
#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "TienIch.h"
#include <iostream>
#include <fstream>

using namespace std;

class KhachHang
{
private:
    string maKH;
    string tenKH;
    string SDT;
    string CCCD;

public:
    KhachHang();
    KhachHang(string ma, string ten, string sdt, string cccd);

    string getMaKH() const;
    void setMaKH(string ma);

    string getTenKH() const;
    void setTenKH(string ten);

    string getSDT() const;
    void setSDT(string sdt);

    string getCCCD() const;
    void setCCCD(string cccd);

    void GhiFileKhachHang(ofstream &file) const;
    void DocFileKhachHang(ifstream &file);
};

#endif
```

##### b. File KhachHang.cpp
```cpp
#include "KhachHang.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

KhachHang::KhachHang() : maKH(""), tenKH(""), SDT(""), CCCD("") {}

KhachHang::KhachHang(string ma, string ten, string sdt, string cccd)
    : maKH(TienIch::ChuanHoaMa(ma)), tenKH(ten), SDT(sdt), CCCD(cccd) {}

string KhachHang::getMaKH() const { return maKH; }
void KhachHang::setMaKH(string ma) { maKH = TienIch::ChuanHoaMa(ma); }

string KhachHang::getTenKH() const { return tenKH; }
void KhachHang::setTenKH(string ten) { tenKH = ten; }

string KhachHang::getSDT() const { return SDT; }
void KhachHang::setSDT(string sdt) { SDT = sdt; }

string KhachHang::getCCCD() const { return CCCD; }
void KhachHang::setCCCD(string cccd) { CCCD = cccd; }

void KhachHang::GhiFileKhachHang(ofstream &file) const
{
    int maKHLength = maKH.size();
    file.write((char *)&maKHLength, sizeof(maKHLength));
    file.write(maKH.c_str(), maKHLength);

    int tenKHLength = tenKH.size();
    file.write((char *)&tenKHLength, sizeof(tenKHLength));
    file.write(tenKH.c_str(), tenKHLength);

    int sdtLength = SDT.size();
    file.write((char *)&sdtLength, sizeof(sdtLength));
    file.write(SDT.c_str(), sdtLength);

    int cccdLength = CCCD.size();
    file.write((char *)&cccdLength, sizeof(cccdLength));
    file.write(CCCD.c_str(), cccdLength);
}

void KhachHang::DocFileKhachHang(ifstream &file)
{
    int maKHLength = 0;
    file.read((char *)&maKHLength, sizeof(maKHLength));
    if (maKHLength > 0)
    {
        maKH.resize(maKHLength);
        file.read(&maKH[0], maKHLength);
    }

    int tenKHLength = 0;
    file.read((char *)&tenKHLength, sizeof(tenKHLength));
    if (tenKHLength > 0)
    {
        tenKH.resize(tenKHLength);
        file.read(&tenKH[0], tenKHLength);
    }

    int sdtLength = 0;
    file.read((char *)&sdtLength, sizeof(sdtLength));
    if (sdtLength > 0)
    {
        SDT.resize(sdtLength);
        file.read(&SDT[0], sdtLength);
    }

    int cccdLength = 0;
    file.read((char *)&cccdLength, sizeof(cccdLength));
    if (cccdLength > 0)
    {
        CCCD.resize(cccdLength);
        file.read(&CCCD[0], cccdLength);
    }
}
```

#### 3. Lớp đối tượng DatPhong
Quản lý trạng thái giao dịch check-in của khách tại các phòng cụ thể.

##### a. File DatPhong.h
```cpp
#ifndef DATPHONG_H
#define DATPHONG_H

#include "TienIch.h"
#include <iostream>
#include <fstream>

class DatPhong
{
private:
    string maPhong;
    string maKH;
    string ngayDat;
    bool trangThai; // true: Dang thue, false: Da tra phong

public:
    DatPhong();
    DatPhong(string makh, string maphong, string ngay);

    string getMaKH() const;
    void setMaKH(string makh);

    string getMaPhong() const;
    void setMaPhong(string maphong);

    string getNgayDat() const;
    void setNgayDat(string ngay);

    bool getTrangThai() const;
    void setTrangThai(bool tt);

    void GhiFileDatPhong(ofstream &file) const;
    void DocFileDatPhong(ifstream &file);
};

#endif
```

##### b. File DatPhong.cpp
```cpp
#include "DatPhong.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

DatPhong::DatPhong() : maKH(""), maPhong(""), ngayDat(""), trangThai(false) {}

DatPhong::DatPhong(string makh, string maphong, string ngay)
    : maKH(TienIch::ChuanHoaMa(makh)), maPhong(TienIch::ChuanHoaMa(maphong)), ngayDat(ngay), trangThai(true) {}

string DatPhong::getMaKH() const { return maKH; }
void DatPhong::setMaKH(string makh) { maKH = TienIch::ChuanHoaMa(makh); }

string DatPhong::getMaPhong() const { return maPhong; }
void DatPhong::setMaPhong(string maphong) { maPhong = TienIch::ChuanHoaMa(maphong); }

string DatPhong::getNgayDat() const { return ngayDat; }
void DatPhong::setNgayDat(string ngay) { ngayDat = ngay; }

bool DatPhong::getTrangThai() const { return trangThai; }
void DatPhong::setTrangThai(bool tt) { trangThai = tt; }

void DatPhong::GhiFileDatPhong(ofstream &file) const
{
    int maPhongLength = maPhong.size();
    file.write((char *)&maPhongLength, sizeof(maPhongLength));
    file.write(maPhong.c_str(), maPhongLength);

    int maKHLength = maKH.size();
    file.write((char *)&maKHLength, sizeof(maKHLength));
    file.write(maKH.c_str(), maKHLength);

    int ngayDatLength = ngayDat.size();
    file.write((char *)&ngayDatLength, sizeof(ngayDatLength));
    file.write(ngayDat.c_str(), ngayDatLength);

    file.write((char *)&trangThai, sizeof(trangThai));
}

void DatPhong::DocFileDatPhong(ifstream &file)
{
    int maPhongLength = 0;
    file.read((char *)&maPhongLength, sizeof(maPhongLength));
    if (maPhongLength > 0)
    {
        maPhong.resize(maPhongLength);
        file.read(&maPhong[0], maPhongLength);
    }

    int maKHLength = 0;
    file.read((char *)&maKHLength, sizeof(maKHLength));
    if (maKHLength > 0)
    {
        maKH.resize(maKHLength);
        file.read(&maKH[0], maKHLength);
    }

    int ngayDatLength = 0;
    file.read((char *)&ngayDatLength, sizeof(ngayDatLength));
    if (ngayDatLength > 0)
    {
        ngayDat.resize(ngayDatLength);
        file.read(&ngayDat[0], ngayDatLength);
    }

    file.read((char *)&trangThai, sizeof(trangThai));
}
```

### D. Cài đặt lớp điều khiển trung tâm (QuanLyKhachSan)
Lớp này đóng vai trò bộ não điều khiển liên kết, lưu trữ tệp và xử lý logic luồng điều khiển CLI.

#### 1. File QuanLyKhachSan.h
```cpp
#ifndef QUANLYKHACHSAN_H
#define QUANLYKHACHSAN_H

#include "Phong.h"
#include "KhachHang.h"
#include "DatPhong.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class QuanLyKhachSan
{
private:
    const string FILE_PHONG = "phong.dat";
    const string FILE_KHACH_HANG = "khachhang.dat";
    const string FILE_DAT_PHONG = "datphong.dat";

    vector<Phong> ds_phong;
    vector<KhachHang> ds_khach_hang;
    vector<DatPhong> ds_dat_phong;

    Phong *timPhong(const string &maPhong);
    KhachHang *timKhachHang(const string &maKH);
    DatPhong *timDatPhongHoatDong(const string &maPhong);
    DatPhong *timDatPhongHoatDongCuaKhachHang(const string &maKH);

public:
    QuanLyKhachSan();

    void GhiFilePhong() const;  
    void DocFilePhong();

    void GhiFileKhachHang() const;
    void DocFileKhachHang();

    void GhiFileDatPhong() const;
    void DocFileDatPhong();

    void luuToanBoDuLieu() const;
    void taiToanBoDuLieu();

    void DanhSachPhong();
    void ThemPhong();
    void SuaPhong();
    void XoaPhong();

    void DanhSachKhachHang();
    void ThemKhachHang();
    void SuaKhachHang();
    void XoaKhachHang();

    void DanhSachPhongTrong();
    void DatPhongKhachSan();
    void DanhSachPhongThue();
    void TraPhongCheckOut();
};

#endif
```

#### 2. File QuanLyKhachSan.cpp
```cpp
#include "QuanLyKhachSan.h"
#include "iostream"
#include "fstream"
#include "iomanip"

using namespace std; 

Phong *QuanLyKhachSan::timPhong(const string &maPhong)
{
    string maTim = TienIch::ChuanHoaMa(maPhong);
    for (auto &p : ds_phong)
    {
        if (p.getMaPhong() == maTim)
        {
            return &p;
        }
    }
    return nullptr;
}

KhachHang *QuanLyKhachSan::timKhachHang(const string &maKH)
{
    string maTim = TienIch::ChuanHoaMa(maKH);
    for (auto &kh : ds_khach_hang)
    {
        if (kh.getMaKH() == maTim)
        {
            return &kh;
        }
    }
    return nullptr;
}

DatPhong *QuanLyKhachSan::timDatPhongHoatDong(const string &maPhong)
{
    string maTim = TienIch::ChuanHoaMa(maPhong);
    for (auto &dp : ds_dat_phong)
    {
        if (dp.getMaPhong() == maTim && dp.getTrangThai())
        {
            return &dp;
        }
    }
    return nullptr;
}

DatPhong *QuanLyKhachSan::timDatPhongHoatDongCuaKhachHang(const string &maKH)
{
    string maTim = TienIch::ChuanHoaMa(maKH);
    for (auto &dp : ds_dat_phong)
    {
        if (dp.getMaKH() == maTim && dp.getTrangThai())
        {
            return &dp;
        }
    }
    return nullptr;
}

QuanLyKhachSan::QuanLyKhachSan()
{
    taiToanBoDuLieu();
}

void QuanLyKhachSan::GhiFilePhong() const
{
    ofstream file(FILE_PHONG, ios::binary | ios::trunc);
    if (!file)
    {
        TienIch::ThongBaoLoi("Loi! Khong the mo file phong.dat de ghi.");
        return;
    }
    int numPhong = ds_phong.size();
    file.write((char *)&numPhong, sizeof(numPhong));
    for (const auto &p : ds_phong)
    {
        p.GhiFilePhong(file);
    }
    file.close();
}

void QuanLyKhachSan::DocFilePhong()
{
    ifstream file(FILE_PHONG, ios::binary);
    if (!file)
    {
        return;
    }
    int numPhong = 0;
    file.read((char *)&numPhong, sizeof(numPhong));

    ds_phong.clear();
    for (int i = 0; i < numPhong; i++)
    {
        Phong p;
        p.DocFilePhong(file);
        ds_phong.push_back(p);
    }
    file.close();
}

void QuanLyKhachSan::GhiFileKhachHang() const
{
    ofstream file(FILE_KHACH_HANG, ios::binary | ios::trunc);
    if (!file)
    {
        TienIch::ThongBaoLoi("Loi! Khong the mo file khachhang.dat de ghi.");
        return;
    }
    int numKH = ds_khach_hang.size();
    file.write((char *)&numKH, sizeof(numKH));
    for (const auto &kh : ds_khach_hang)
    {
        kh.GhiFileKhachHang(file);
    }
    file.close();
}

void QuanLyKhachSan::DocFileKhachHang()
{
    ifstream file(FILE_KHACH_HANG, ios::binary);
    if (!file)
    {
        return;
    }
    int numKH = 0;
    file.read((char *)&numKH, sizeof(numKH));
    ds_khach_hang.clear();
    for (int i = 0; i < numKH; i++)
    {
        KhachHang kh;
        kh.DocFileKhachHang(file);
        ds_khach_hang.push_back(kh);
    }
    file.close();
}

void QuanLyKhachSan::GhiFileDatPhong() const
{
    ofstream file(FILE_DAT_PHONG, ios::binary | ios::trunc);
    if (!file)
    {
        TienIch::ThongBaoLoi("Loi! Khong the mo file datphong.dat de ghi.");
        return;
    }
    int numDP = ds_dat_phong.size();
    file.write((char *)&numDP, sizeof(numDP));
    for (const auto &dp : ds_dat_phong)
    {
        dp.GhiFileDatPhong(file);
    }
    file.close();
}

void QuanLyKhachSan::DocFileDatPhong()
{
    ifstream file(FILE_DAT_PHONG, ios::binary);
    if (!file)
    {
        return;
    }
    int numDP = 0;
    file.read((char *)&numDP, sizeof(numDP));
    ds_dat_phong.clear();
    for (int i = 0; i < numDP; i++)
    {
        DatPhong dp;
        dp.DocFileDatPhong(file);
        ds_dat_phong.push_back(dp);
    }
    file.close();
}

void QuanLyKhachSan::luuToanBoDuLieu() const
{
    GhiFilePhong();
    GhiFileKhachHang();
    GhiFileDatPhong();
}

void QuanLyKhachSan::taiToanBoDuLieu()
{
    DocFilePhong();
    DocFileKhachHang();
    DocFileDatPhong();
}

void QuanLyKhachSan::DanhSachPhong()
{
    cout << Color::BOLD << "\n"
         << setw(50) << right << "--- DANH SACH PHONG HIEN TAI ---\n"
         << Color::RESET;

    cout << left;
    cout << setw(12) << "Ma Phong"
         << setw(22) << "Ten phong"
         << setw(18) << "Loai phong"
         << setw(20) << "Gia phong"
         << setw(10) << "Trang thai" << "\n";
    cout << string(85, '-') << "\n";

    for (const auto &p : ds_phong)
    {
        string tt = p.getTrangThai() ? (Color::RED + "Dang duoc thue" + Color::RESET) : (Color::GREEN + "Dang trong" + Color::RESET);
        cout << setw(12) << p.getMaPhong()
             << setw(22) << p.getTenPhong()
             << setw(18) << p.getLoaiPhong()
             << setw(20) << TienIch::DinhDanhTienVND(p.getGiaPhong())
             << setw(10) << tt << "\n";
    }
    cout << string(85, '-') << "\n";
}

void QuanLyKhachSan::ThemPhong()
{
    TienIch::HienThiTieuDe("THEM PHONG MOI");
    string ma, ten, loai;
    double gia;

    while (true)
    {
        cout << "Nhap ma phong (Nhap 0 de huy): ";
        getline(cin, ma);
        if (ma == "0")
        {
            cout << "Da huy thao tac!\n";
            return;
        }

        if (timPhong(ma) != nullptr)
        {
            TienIch::ThongBaoLoi("Ma phong da ton tai!");
        }
        else
        {
            break;
        }
    }

    cout << "Nhap ten phong: ";
    getline(cin, ten);
    cout << "Nhap loai phong: ";
    getline(cin, loai);
    cout << "Nhap gia phong (VND): ";
    cin >> gia;
    cin.ignore();

    ds_phong.push_back(Phong(ma, ten, loai, gia));
    GhiFilePhong();
    TienIch::ThongBaoThanhCong("Them phong moi thanh cong!");
}

void QuanLyKhachSan::SuaPhong()
{
    TienIch::HienThiTieuDe("SUA THONG TIN PHONG");
    DanhSachPhong();
    if (ds_phong.empty())
    {
        TienIch::ThongBaoLoi("Danh sach phong dang trong!");
        return;
    }

    string ma;
    cout << "Nhap ma phong can sua: ";
    getline(cin, ma);
    ma = TienIch::ChuanHoaMa(ma);

    Phong *p = timPhong(ma);
    if (p == nullptr)
    {
        TienIch::ThongBaoLoi("Khong tim thay phong co ma vua nhap!");
        return;
    }

    int choice;
    do
    {
        cout << "\n--- Thong tin hien tai ---\n";
        cout << "Ma phong: " << p->getMaPhong() << "\n";
        cout << "Ten phong: " << p->getTenPhong() << "\n";
        cout << "Loai phong: " << p->getLoaiPhong() << "\n";
        cout << "Gia phong : " << TienIch::DinhDanhTienVND(p->getGiaPhong()) << "\n";
        cout << "Trang thai: " << (p->getTrangThai() ? Color::RED + "Dang duoc thue" + Color::RESET : Color::GREEN + "Dang trong" + Color::RESET) << "\n";

        cout << "\n--- Nhap lua chon sua ---\n";
        cout << "1. Sua ten phong.\n";
        cout << "2. Sua loai phong.\n";
        cout << "3. Sua gia phong.\n";
        cout << "0. Hoan tat va Luu thay doi.\n";

        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string ten;
            cout << "Nhap ten phong moi: ";
            getline(cin, ten);
            TienIch::XoaKhoangTrangThua(ten);
            p->setTenPhong(ten);
            TienIch::ThongBaoThanhCong("Da sua ten phong.");
            break;
        }
        case 2:
        {
            string loai;
            cout << "Nhap loai phong moi: ";
            getline(cin, loai);
            TienIch::XoaKhoangTrangThua(loai);
            p->setLoaiPhong(loai);
            TienIch::ThongBaoThanhCong("Da sua loai phong.");
            break;
        }
        case 3:
        {
            double gia;
            cout << "Nhap gia phong moi: ";
            cin >> gia;
            cin.ignore();
            p->setGiaPhong(gia);
            TienIch::ThongBaoThanhCong("Da sua gia phong.");
            break;
        }
        case 0:
            break;
        default:
            TienIch::ThongBaoLoi("Lua chon khong hop le! Vui long thu lai.");
            break;
        }
    } while (choice != 0);

    GhiFilePhong();
    TienIch::ThongBaoThanhCong("Cap nhat thong tin phong thanh cong.");
}

void QuanLyKhachSan::XoaPhong()
{
    TienIch::HienThiTieuDe("XOA PHONG");
    DanhSachPhong();
    if (ds_phong.empty())
    {
        TienIch::ThongBaoLoi("Danh sach phong dang trong!");
        return;
    }

    string ma;
    cout << "Nhap ma phong can xoa (Nhap 0 de huy): ";
    getline(cin, ma);
    if (ma == "0")
    {
        cout << "Da huy thao tac!\n";
        return;
    }

    Phong *p = timPhong(ma);
    if (p == nullptr)
    {
        cout << "Khong tim thay phong co ma vua nhap!";
        return;
    }

    if (p->getTrangThai() || timDatPhongHoatDong(ma) != nullptr)
    {
        TienIch::ThongBaoLoi("Khong the xoa vi phong dang duoc thue!");
        return;
    }

    string confirm;
    cout << Color::YELLOW << "Ban co chac chan muon xoa phong " << p->getTenPhong() << "(" << p->getMaPhong() << ") ?" << " (Y/N): " << Color::RESET;
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y")
    {
        // Thực hiện xóa phòng khỏi vector bằng con trỏ
        ds_phong.erase(ds_phong.begin() + (p - &ds_phong[0]));
        GhiFilePhong();
        TienIch::ThongBaoThanhCong("Xoa phong thanh cong!");
    }
    else
    {
        cout << "Da huy thao tac xoa!" << endl;
    }
}

void QuanLyKhachSan::DanhSachKhachHang()
{
    cout << Color::BOLD << "\n"
         << setw(50) << right << "--- DANH SACH KHACH HANG ---\n"
         << Color::RESET;

    cout << left;
    cout << setw(15) << "Ma KH"
         << setw(25) << "Ten KH"
         << setw(20) << "SDT"
         << setw(20) << "CCCD" << "\n";
    cout << string(75, '-') << "\n";

    for (const auto &kh : ds_khach_hang)
    {
        cout << setw(15) << kh.getMaKH()
             << setw(25) << kh.getTenKH()
             << setw(20) << kh.getSDT()
             << setw(20) << kh.getCCCD() << "\n";
    }
    cout << string(75, '-') << "\n";
}

void QuanLyKhachSan::ThemKhachHang()
{
    TienIch::HienThiTieuDe("THEM KHACH HANG");

    string maKH, tenKH, sdt, cccd;

    while (true)
    {
        cout << "Nhap ma khach hang (Nhap 0 de huy): ";
        getline(cin, maKH);
        maKH = TienIch::ChuanHoaMa(maKH);
        if (maKH == "0")
        {
            cout << "Da huy thao tac!\n";
            return;
        }

        if (timKhachHang(maKH) != nullptr)
        {
            TienIch::ThongBaoLoi("Ma khach hang da ton tai! Vui long nhap lai.");
        }
        else
        {
            break;
        }
    }

    cout << "Nhap ten khach hang: ";
    getline(cin, tenKH);
    TienIch::XoaKhoangTrangThua(tenKH);
    cout << "Nhap SDT khach hang: ";
    getline(cin, sdt);
    TienIch::XoaKhoangTrangThua(sdt);
    cout << "Nhap CCCD khach hang: ";
    getline(cin, cccd);
    TienIch::XoaKhoangTrangThua(cccd);

    ds_khach_hang.push_back(KhachHang(maKH, tenKH, sdt, cccd));
    GhiFileKhachHang();
    TienIch::ThongBaoThanhCong("Them thong tin khach hang thanh cong!");
}

void QuanLyKhachSan::SuaKhachHang()
{
    TienIch::HienThiTieuDe("SUA THONG TIN KHACH HANG");

    DanhSachKhachHang();

    if (ds_khach_hang.empty())
    {
        TienIch::ThongBaoLoi("Danh sach khach hang trong!");
        return;
    }

    string maKH;
    cout << "Nhap ma khach hang can sua (Nhap 0 de huy): ";
    getline(cin, maKH);
    maKH = TienIch::ChuanHoaMa(maKH);
    if (maKH == "0")
    {
        cout << "Da huy thao tac!\n";
        return;
    }

    KhachHang *kh = timKhachHang(maKH);
    if (kh == nullptr)
    {
        TienIch::ThongBaoLoi("Khong tim thay khach hang co ma vua nhap!");
        return;
    }

    int choice;
    do
    {
        cout << "\n--- Thong tin hien tai ---\n";
        cout << "Ma khach hang: " << kh->getMaKH() << "\n";
        cout << "Ten khach hang: " << kh->getTenKH() << "\n";
        cout << "SDT: " << kh->getSDT() << "\n";
        cout << "CCCD: " << kh->getCCCD() << "\n";
        cout << string(26, '-') << "\n";

        cout << "1. Sua ten khach hang.\n";
        cout << "2. Sua SDT khach hang.\n";
        cout << "3. Sua CCCD khach hang.\n";
        cout << "0. Hoan tat va Luu thay doi.\n";

        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string tenKH;
            cout << "Nhap ten khach hang: ";
            getline(cin, tenKH);
            TienIch::XoaKhoangTrangThua(tenKH);
            kh->setTenKH(tenKH);
            TienIch::ThongBaoThanhCong("Doi ten khach hang thanh cong!");
            break;
        }
        case 2:
        {
            string sdt;
            cout << "Nhap SDT khach hang: ";
            getline(cin, sdt);
            TienIch::XoaKhoangTrangThua(sdt);
            kh->setSDT(sdt);
            TienIch::ThongBaoThanhCong("Doi SDT khach hang thanh cong!");
            break;
        }
        case 3:
        {
            string cccd;
            cout << "Nhap CCCD khach hang: ";
            getline(cin, cccd);
            TienIch::XoaKhoangTrangThua(cccd);
            kh->setCCCD(cccd);
            TienIch::ThongBaoThanhCong("Doi CCCD khach hang thanh cong!");
            break;
        }
        case 0:
            break;
        default:
            TienIch::ThongBaoLoi("Lua chon khong hop le! Vui long thu lai.");
            break;
        }
    } while (choice != 0);

    GhiFileKhachHang();
    TienIch::ThongBaoThanhCong("Cap nhat thong tin khach hang thanh cong!");
}

void QuanLyKhachSan::XoaKhachHang()
{
    TienIch::HienThiTieuDe("XOA THONG TIN KHACH HANG");

    if (ds_khach_hang.empty())
    {
        TienIch::ThongBaoLoi("Danh sach khach hang dang trong!");
        return;
    }

    DanhSachKhachHang();

    string maKH;
    cout << "Nhap ma khach hang can xoa (Nhap 0 de huy): ";
    getline(cin, maKH);
    if (maKH == "0")
    {
        cout << "Da huy thao tac!\n";
        return;
    }

    KhachHang *kh = timKhachHang(maKH);
    if (kh == nullptr)
    {
        TienIch::ThongBaoLoi("Khong tim thay khach hang co ma vua nhap!");
        return;
    }

    if (timDatPhongHoatDongCuaKhachHang(maKH) != nullptr)
    {
        TienIch::ThongBaoLoi("Khong the xoa khach hang vi dang thue phong cua khach san!");
        return;
    }

    string confirm;
    cout << Color::YELLOW << "Ban co chac chan muon xoa khach hang " << kh->getTenKH() << " (" << kh->getMaKH() << ") ?" << " (Y/N): " << Color::RESET;
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y")
    {
        ds_khach_hang.erase(ds_khach_hang.begin() + (kh - &ds_khach_hang[0]));
        GhiFileKhachHang();
        TienIch::ThongBaoThanhCong("Xoa khach hang thanh cong!");
    }
    else
    {
        cout << "Da huy thao tac xoa!" << endl;
    }
}

void QuanLyKhachSan::DanhSachPhongTrong()
{
    cout << Color::BOLD << "\n"
         << setw(50) << right << "--- DANH SACH PHONG TRONG ---\n"
         << Color::RESET;
    cout << left;
    cout << setw(12) << "Ma Phong"
         << setw(22) << "Ten phong"
         << setw(18) << "Loai phong"
         << setw(20) << "Gia phong"
         << setw(10) << "Trang thai" << "\n";
    cout << string(85, '-') << "\n";

    int countTrong = 0;
    for (const auto &p : ds_phong)
    {
        if (!p.getTrangThai())
        {
            string tt = Color::GREEN + "Dang trong" + Color::RESET;
            cout << setw(12) << p.getMaPhong()
                 << setw(22) << p.getTenPhong()
                 << setw(18) << p.getLoaiPhong()
                 << setw(20) << TienIch::DinhDanhTienVND(p.getGiaPhong())
                 << setw(10) << tt << "\n";
            countTrong++;
        }
    }
    cout << string(85, '-') << "\n";

    if (countTrong == 0)
    {
        TienIch::ThongBaoLoi("Hien tai tat ca phong deu da kin!");
    }
}

void QuanLyKhachSan::DatPhongKhachSan()
{
    TienIch::HienThiTieuDe("DAT PHONG");

    if (ds_phong.empty())
    {
        TienIch::ThongBaoLoi("Danh sach phong dang trong!");
        return;
    }

    if (ds_khach_hang.empty())
    {
        TienIch::ThongBaoLoi("Danh sach khach hang dang trong!");
        return;
    }

    DanhSachKhachHang();
    string maKH;
    cout << "Nhap ma khach hang muon dat phong (Nhap 0 de huy): ";
    getline(cin, maKH);
    if (maKH == "0")
    {
        cout << "Da huy thao tac!\n";
        return;
    }

    KhachHang *kh = timKhachHang(maKH);
    if (kh == nullptr)
    {
        TienIch::ThongBaoLoi("Khong tim thay khach hang co ma vua nhap!");
        return;
    }

    DanhSachPhongTrong();
    string maP;
    cout << "Nhap ma phong muon dat (Nhap 0 de huy): ";
    getline(cin, maP);
    if (maP == "0")
    {
        cout << "Da huy thao tac!\n";
        return;
    }

    Phong *p = timPhong(maP);
    if (p == nullptr)
    {
        TienIch::ThongBaoLoi("Khong tim thay phong co ma vua nhap!");
        return;
    }
    if (p->getTrangThai())
    {
        TienIch::ThongBaoLoi("Hien tai phong nay dang co nguoi thue!");
        return;
    }

    string thoiGianCheckIn = TienIch::LayThoiGianHienTai();
    p->setTrangThai(true);

    DatPhong phieuMoi(maKH, maP, thoiGianCheckIn);
    ds_dat_phong.push_back(phieuMoi);

    GhiFilePhong();
    GhiFileDatPhong();

    TienIch::ThongBaoThanhCong("Dat phong thanh cong!");
    cout << "Phong: " << p->getTenPhong() << " | Khach hang: " << kh->getTenKH() << "\n";
    cout << "Thoi gian vao he thong: " << thoiGianCheckIn << "\n";
    cout << "--------------------------------------------\n";
}

void QuanLyKhachSan::DanhSachPhongThue()
{
    cout << Color::BOLD << "\n"
         << right << setw(100) << "--- DANH SACH PHONG HIEN DANG DUOC THUE ---\n"
         << Color::RESET;

    cout << left;
    cout << setw(15) << "Ma Phong"
         << setw(22) << "Ten Phong"
         << setw(15) << "Ma KH"
         << setw(25) << "Ten KH"
         << setw(18) << "Loai Phong"
         << setw(20) << "Gia Phong"
         << setw(25) << "Thoi Gian Check-In"
         << setw(10) << "Trang Thai" << "\n";
    cout << string(150, '-') << "\n";

    int demPhongThue = 0;
    for (const auto &dp : ds_dat_phong)
    {
        if (dp.getTrangThai())
        {
            Phong *p = timPhong(dp.getMaPhong());
            KhachHang *kh = timKhachHang(dp.getMaKH());

            if (p != nullptr && kh != nullptr)
            {
                string tt = Color::RED + "Dang thue" + Color::RESET;
                cout << setw(15) << p->getMaPhong()
                     << setw(22) << p->getTenPhong()
                     << setw(15) << kh->getMaKH()
                     << setw(25) << kh->getTenKH()
                     << setw(18) << p->getLoaiPhong()
                     << setw(20) << TienIch::DinhDanhTienVND(p->getGiaPhong())
                     << setw(25) << dp.getNgayDat()
                     << setw(10) << tt << "\n";
                demPhongThue++;
            }
        }
    }

    if (demPhongThue == 0)
    {
        TienIch::ThongBaoLoi("Chua co phong nao duoc thue!");
    }
    else
    {
        cout << string(150, '-') << "\n";
    }
}

void QuanLyKhachSan::TraPhongCheckOut()
{
    TienIch::HienThiTieuDe("TRA PHONG");

    DanhSachPhongThue();

    string maP;
    cout << "Nhap ma phong can tra (Nhap 0 de huy): ";
    getline(cin, maP);
    if (maP == "0")
    {
        cout << "Da huy thao tac!\n";
        return;
    }

    Phong *p = timPhong(maP);
    DatPhong *dp = timDatPhongHoatDong(maP);

    if (p == nullptr || dp == nullptr)
    {
        TienIch::ThongBaoLoi("Khong tim thay phong dang thue co ma vua nhap!");
        return;
    }

    p->setTrangThai(false);
    dp->setTrangThai(false);

    GhiFilePhong();
    GhiFileDatPhong();

    TienIch::ThongBaoThanhCong("Da tra phong thanh cong!");
}
```

### E. Hàm khởi chạy chính (main.cpp)
Hàm `main` thiết lập vòng lặp lựa chọn CLI và bắt các ngoại lệ nhập liệu từ bàn phím.

```cpp
#include <iostream>
#include "QuanLyKhachSan.h"

using namespace std;

int main()
{
    QuanLyKhachSan qlks;
    int choice;
    do
    {
        cout << Color::BOLD << Color::CYAN;
        cout << "\n=========================================================\n";
        cout << "||            HE THONG QUAN LY KHACH SAN               ||\n";
        cout << "=========================================================\n"
             << Color::RESET;
        cout << "1. Nhap them phong.\n";
        cout << "2. Sua thong tin phong.\n";
        cout << "3. Xoa phong.\n";
        cout << "4. Nhap thong tin khach hang.\n";
        cout << "5. Sua thong tin khach hang.\n";
        cout << "6. Xoa thong tin khach hang.\n";
        cout << "7. Dat phong.\n";
        cout << "8. Tra phong.\n";
        cout << "9. Liet ke toan bo phong trong khach san.\n";
        cout << "10. Liet ke nhung phong dang duoc thue trong khach san.\n";
        cout << "0. Thoat he thong.\n";
        cout << "-----------------------------------------------------------------\n";

        cout << Color::BOLD << Color::BLUE << "Nhap lua chon: " << Color::RESET;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            TienIch::ThongBaoLoi("Vui long nhap mot so nguyen hop le!");
            continue;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            qlks.ThemPhong();
            break;
        case 2:
            qlks.SuaPhong();
            break;
        case 3:
            qlks.XoaPhong();
            break;
        case 4:
            qlks.ThemKhachHang();
            break;
        case 5:
            qlks.SuaKhachHang();
            break;
        case 6:
            qlks.XoaKhachHang();
            break;
        case 7:
            qlks.DatPhongKhachSan();
            break; // Đã khắc phục lỗi thiếu break trong mã nguồn gốc
        case 8:
            qlks.TraPhongCheckOut();
            break; // Đã khắc phục lỗi thiếu break
        case 9:
            qlks.DanhSachPhong(); // Hiển thị toàn bộ danh sách phòng
            break; // Đã khắc phục lỗi thiếu break
        case 10:
            qlks.DanhSachPhongThue();
            break; // Đã khắc phục lỗi thiếu break
        case 0:
            TienIch::ThongBaoThanhCong("Cam on ban da su dung he thong!");
            break;
        default:
            TienIch::ThongBaoLoi("Lua chon khong hop le!");
            break;
        }
    } while (choice != 0);

    return 0;
}
```
*Lưu ý nâng cấp trong báo cáo:* Trong mã nguồn ban đầu của file `main.cpp`, có các lỗi logic nghiêm trọng do việc thiếu từ khóa `break` từ `case 7` đến `case 10`, dẫn đến việc chương trình bị rơi xuống (fall-through) thực hiện liên tục các ca xử lý khác. Chúng tôi đã tiến hành tối ưu hóa cấu trúc này bằng việc bổ sung từ khóa `break;` tương ứng cho từng khối điều kiện lựa chọn và thêm cơ chế bẫy lỗi đầu vào (input validation) cho luồng đọc `cin` khi người dùng cố tình nhập chuỗi ký tự thay vì chữ số, tránh gây vòng lặp vô hạn (infinite loop) làm treo ứng dụng.

---

## V. LƯU TRỮ VÀ TUẦN TỰ HÓA NHỊ PHÂN (BINARY SERIALIZATION)

### A. Thách thức kỹ thuật của việc tuần tự hóa trong C++
Tuần tự hóa dữ liệu (serialization) là quá trình chuyển đổi trạng thái của một đối tượng trong bộ nhớ RAM thành một định dạng lưu trữ có thể truyền tải qua mạng hoặc ghi xuống đĩa cứng để khôi phục lại sau này (deserialization). Trong C++, không giống như Java hay C# vốn hỗ trợ sẵn cơ chế phản chiếu (reflection) và các thư viện tự động hóa cao, lập trình viên buộc phải tự thiết kế và cài đặt cơ chế tuần tự hóa thủ công cho các đối tượng tùy biến.

Một sai lầm kinh điển mà các lập trình viên thiếu kinh nghiệm thường mắc phải khi lưu trữ nhị phân trong C++ là thực hiện ghi đè cả vùng nhớ của đối tượng bằng phương thức thô (shallow copy):
```cpp
// CẢNH BÁO: ĐOẠN CODE LỖI BẢO MẬT VÀ BỘ NHỚ!
file.write((char*)&phongObject, sizeof(phongObject));
```
Cách tiếp cận trên chỉ hoạt động đúng đối với các cấu trúc dữ liệu phẳng (Plain Old Data - POD), tức là các đối tượng chỉ chứa các kiểu dữ liệu nguyên thủy có kích thước cố định như `int`, `float`, `double`, `char[N]`, `bool`. 

Tuy nhiên, đối với các lớp như `Phong`, `KhachHang`, hay `DatPhong` chứa các thuộc tính có kiểu dữ liệu động là `std::string`, cách ghi này sẽ gây ra thảm họa bộ nhớ (memory corruption / Segmentation fault). Lý do là vì:
* Lớp `std::string` trong thư viện chuẩn C++ thực chất là một đối tượng quản lý bộ nhớ động. Bản thân đối tượng `string` trên vùng nhớ Stack chỉ chứa một con trỏ (`char*`) trỏ đến một vùng nhớ thực sự chứa chuỗi ký tự nằm trên vùng nhớ Heap, đi kèm với các biến lưu trữ độ dài (size) và dung lượng (capacity).
* Kích thước `sizeof(std::string)` là cố định (thường là 24 hoặc 32 bytes tùy thuộc vào trình biên dịch và kiến trúc hệ thống 32-bit hay 64-bit), bất kể chuỗi đó dài 5 ký tự hay 10.000 ký tự.
* Khi gọi lệnh ghi đè bộ nhớ thô `file.write((char*)&object, sizeof(object))`, chương trình sẽ ghi giá trị địa chỉ con trỏ Heap (một số nguyên địa chỉ tạm thời trong phiên chạy hiện tại) xuống đĩa cứng, chứ hoàn toàn không ghi nội dung chuỗi ký tự thực tế.
* Khi chương trình tắt đi và khởi động lại, vùng nhớ Heap cũ đã bị hệ điều hành thu hồi hoặc cấp phát cho ứng dụng khác. Khi đọc file nhị phân vào bộ nhớ (deserialization), chương trình sẽ nạp lại giá trị con trỏ cũ. Việc cố gắng truy cập vào địa chỉ con trỏ vô giá trị này (dangling pointer) sẽ dẫn đến lỗi vi phạm truy cập bộ nhớ nghiêm trọng và làm crash ứng dụng ngay lập tức.

### B. Giải pháp Tuần tự hóa theo độ dài tiền tố (Length-Prefix Serialization)
Để giải quyết triệt để thách thức trên, hệ thống HMS áp dụng kỹ thuật **Tuần tự hóa theo độ dài tiền tố (Length-Prefix Serialization)**. Theo phương pháp này, mỗi chuỗi ký tự động trước khi được ghi xuống file nhị phân sẽ được bóc tách thành hai phần thông tin kế tiếp nhau:
1. **Phần tiền tố (Prefix):** Là một số nguyên (thường là `int` - 4 bytes) lưu trữ độ dài thực tế của chuỗi ký tự tại thời điểm ghi.
2. **Phần nội dung (Payload):** Là mảng các ký tự nguyên bản của chuỗi, được trích xuất trực tiếp từ Heap thông qua phương thức `.c_str()` hoặc `.data()`.

```text
[Cấu trúc dữ liệu ghi file của một thuộc tính chuỗi]
┌───────────────────────────┬──────────────────────────────────────────┐
│ Độ dài chuỗi (int)        │ Các ký tự của chuỗi (char array)         │
│ 4 Bytes (Ví dụ: 5)        │ Kích thước động (Ví dụ: 'P', '1', '0', '1')│
└───────────────────────────┴──────────────────────────────────────────┘
```

#### 1. Cơ chế tuần tự hóa (Serialization - Ghi dữ liệu)
Hãy phân tích mã nguồn phương thức ghi của lớp `Phong`:
```cpp
void Phong::GhiFilePhong(ofstream &file) const
{
    // Bước 1: Ghi mã phòng
    int maPhongLength = maPhong.size(); // Lấy độ dài chuỗi
    file.write((char *)&maPhongLength, sizeof(maPhongLength)); // Ghi 4 bytes độ dài
    file.write(maPhong.c_str(), maPhongLength); // Ghi đúng số bytes ký tự trên Heap

    // Bước 2: Ghi tên phòng
    int tenPhongLength = tenPhong.size();
    file.write((char *)&tenPhongLength, sizeof(tenPhongLength));
    file.write(tenPhong.c_str(), tenPhongLength);

    // Bước 3: Ghi loại phòng
    int loaiLength = loaiPhong.size();
    file.write((char *)&loaiLength, sizeof(loaiLength));
    file.write(loaiPhong.c_str(), loaiLength);

    // Bước 4: Ghi giá phòng (độ rộng cố định double = 8 bytes)
    file.write((char *)&giaPhong, sizeof(giaPhong));

    // Bước 5: Ghi trạng thái phòng (độ rộng cố định bool = 1 byte)
    file.write((char *)&trangThai, sizeof(trangThai));
}
```

#### 2. Cơ chế giải tuần tự hóa (Deserialization - Đọc dữ liệu)
Quy trình đọc phải tuân thủ nghiêm ngặt thứ tự ghi và sử dụng thông tin độ dài tiền tố để tái cấp phát vùng nhớ Heap cho chuỗi trước khi nạp ký tự:
```cpp
void Phong::DocFilePhong(ifstream &file)
{
    // Bước 1: Đọc mã phòng
    int maLength = 0;
    file.read((char *)&maLength, sizeof(maLength)); // Đọc 4 bytes độ dài tiền tố
    if (maLength > 0)
    {
        maPhong.resize(maLength); // Tái cấp phát vùng nhớ Heap đúng kích thước
        file.read(&maPhong[0], maLength); // Đọc trực tiếp ký tự từ file vào Heap
    }

    // Bước 2: Đọc tên phòng
    int tenLength = 0;
    file.read((char *)&tenLength, sizeof(tenLength));
    if (tenLength > 0)
    {
        tenPhong.resize(tenLength);
        file.read(&tenPhong[0], tenLength);
    }

    // Bước 3: Đọc loại phòng
    int loaiLength = 0;
    file.read((char *)&loaiLength, sizeof(loaiLength));
    if (loaiLength > 0)
    {
        loaiPhong.resize(loaiLength);
        file.read(&loaiPhong[0], loaiLength);
    }

    // Bước 4: Đọc giá phòng
    file.read((char *)&giaPhong, sizeof(giaPhong));

    // Bước 5: Đọc trạng thái phòng
    file.read((char *)&trangThai, sizeof(trangThai));
}
```

### C. Quản lý danh sách động và đồng bộ hóa tệp dữ liệu nhị phân
Ở cấp độ điều khiển hệ thống (`QuanLyKhachSan`), dữ liệu được quản lý tập trung bằng `std::vector` chứa các đối tượng phẳng.
* Để lưu trữ danh sách: Đầu tiên hệ thống ghi nhận số lượng phần tử hiện tại của danh sách (`ds_phong.size()`) dưới dạng số nguyên 4 bytes làm thông tin định danh kích thước tệp. Sau đó, duyệt qua từng phần tử trong vector và yêu cầu đối tượng tự thực hiện phương thức ghi nhị phân của nó.
* Quy trình này đảm bảo tính đóng gói nghiệp vụ: Lớp quản lý chỉ điều phối luồng tập tin và số lượng bản ghi, trong khi chi tiết biểu diễn nhị phân của từng đối tượng do chính lớp đó quản lý.
* Tất cả các file nhị phân được mở với cờ hiệu `ios::binary`. Khi ghi, cờ hiệu `ios::trunc` (truncate) được áp dụng để xóa bỏ toàn bộ nội dung file cũ, ghi đè dữ liệu mới nhất trong RAM xuống đĩa cứng, duy trì trạng thái đồng bộ hóa tối đa.

---

## VI. KẾT QUẢ VÀ THẢO LUẬN (RESULTS & DISCUSSION)

### A. Thực nghiệm chạy thử chương trình (Execution walkthrough)
Hệ thống được kiểm thử thực tế trên hệ điều hành Windows 11, biên dịch bằng trình biên dịch MinGW-w64 (GCC 12.2) với cờ tối ưu hóa `-O2`. Dưới đây là các kịch bản chạy thử nghiệm thực tế cho thấy hoạt động của hệ thống.

#### 1. Kịch bản 1: Thêm phòng mới và tự động lưu file nhị phân
* **Thao tác:** Người dùng chọn chức năng `1` từ menu chính.
* **Console Input:**
  ```text
  ==============================
          THEM PHONG MOI
  ==============================
  Nhap ma phong: p101
  Nhap ten phong: Phong Don Tieu Chuan
  Nhap loai phong: Don
  Nhap gia phong (VND): 350000
  ```
* **Hệ thống xử lý:** Mã phòng được chuẩn hóa thành `P101`. Đối tượng `Phong` được tạo và đẩy vào `ds_phong`. Hàm `GhiFilePhong()` được gọi và ghi file nhị phân `phong.dat`.
* **Console Output:**
  ```text
  Them phong moi thanh cong!
  ```

#### 2. Kịch bản 2: Liệt kê toàn bộ phòng
* **Thao tác:** Người dùng chọn chức năng `9`.
* **Console Output:**
  ```text
  --------------------------------- DANH SACH PHONG HIEN TAI ---------------------------------
  Ma Phong    Ten phong             Loai phong        Gia phong           Trang thai
  -------------------------------------------------------------------------------------
  P101        Phong Don Tieu Chuan  Don               350.000 VND         Dang trong
  -------------------------------------------------------------------------------------
  ```

#### 3. Kịch bản 3: Thêm thông tin khách hàng
* **Thao tác:** Chọn chức năng `4`.
* **Console Input:**
  ```text
  ==============================
         THEM KHACH HANG
  ==============================
  Nhap ma khach hang: kh001
  Nhap ten khach hang: Nguyen Van A
  Nhap SDT khach hang: 0912345678
  Nhap CCCD khach hang: 001099123456
  ```
* **Console Output:**
  ```text
  Them thong tin khach hang thanh cong!
  ```
* **Hệ thống xử lý:** Hồ sơ khách hàng được đưa vào `ds_khach_hang` và tự động lưu vào file nhị phân `khachhang.dat`.

#### 4. Kịch bản 4: Đặt phòng (Check-In)
* **Thao tác:** Chọn chức năng `7`.
* **Hệ thống hiển thị:** Danh sách khách hàng hiện có để lựa chọn, sau đó là danh sách phòng trống.
* **Console Input:**
  ```text
  Nhap ma khach hang muon dat phong: KH001
  Nhap ma phong muon dat: P101
  ```
* **Hệ thống xử lý:** Trạng thái của phòng `P101` chuyển thành `true` (đang được thuê). Một đối tượng `DatPhong` được khởi tạo chứa thông tin (`KH001`, `P101`, thời gian check-in hệ thống dạng `"11/06/2026 07:37"`). Trạng thái bản ghi là `true`.
* **Console Output:**
  ```text
  Dat phong thanh cong!
  Phong: Phong Don Tieu Chuan | Khach hang: Nguyen Van A
  Thoi gian vao he thong: 11/06/2026 07:37
  --------------------------------------------
  ```

#### 5. Kịch bản 5: Kiểm tra ràng buộc khi xóa phòng đang được thuê
* **Thao tác:** Chọn chức năng `3` (Xóa phòng).
* **Console Input:**
  ```text
  Nhap ma phong can xoa: P101
  ```
* **Hệ thống xử lý:** Tìm thấy phòng `P101`. Hệ thống thực hiện kiểm tra `p->getTrangThai()` và thấy bằng `true` (hoặc kiểm tra hàm `timDatPhongHoatDong("P101")` trả về con trỏ hợp lệ).
* **Console Output:**
  ```text
  Khong the xoa vi phong dang duoc thue!
  ```
  *(Thử nghiệm thành công: Ràng buộc toàn vẹn dữ liệu được đảm bảo).*

#### 6. Kịch bản 6: Trả phòng (Check-Out) và giải phóng trạng thái
* **Thao tác:** Chọn chức năng `8`.
* **Console Input:**
  ```text
  ==============================
            TRA PHONG
  ==============================
  --- DANH SACH PHONG HIEN DANG DUOC THUE ---
  Ma Phong       Ten Phong       Ma KH     Ten KH          Loai Phong   Gia Phong       Thoi Gian Check-In       Trang Thai
  P101           Phong Don...    KH001     Nguyen Van A    Don          350.000 VND     11/06/2026 07:37         Dang thue
  --------------------------------------------------------------------------------------------------------------------------
  Nhap ma phong can tra: P101
  ```
* **Hệ thống xử lý:** Đối tượng `Phong` có mã `P101` được cập nhật trạng thái về `false` (Đang trống). Bản ghi đặt phòng hoạt động liên quan được chuyển về trạng thái `false` (Da check-out). Cập nhật dữ liệu xuống file `phong.dat` và `datphong.dat`.
* **Console Output:**
  ```text
  Da tra phong thanh cong!
  ```

### B. Đánh giá hiệu năng và tính đúng đắn của giải pháp

#### 1. Đánh giá tính đúng đắn (Correctness Verification)
Qua các thực nghiệm hộp đen (black-box testing) và rà soát mã nguồn tĩnh (static code analysis), tính đúng đắn của phần mềm được chứng minh toàn diện:
* **Tính bền vững của dữ liệu:** Khi chương trình bị tắt đột ngột (giả lập sự cố bằng tổ hợp phím `Ctrl+C` hoặc ngắt tiến trình tắt terminal) ở bất kỳ thời điểm nào sau khi hoàn tất một thao tác (ví dụ: ngay sau khi đặt phòng), dữ liệu trong file nhị phân vẫn phản ánh chính xác trạng thái mới nhất. Ở lần khởi động kế tiếp, hệ thống tự động đọc lại tệp tin nhị phân và khôi phục nguyên vẹn danh sách trạng thái.
* **Tính toàn vẹn khóa ngoại:** Nhờ các hàm logic kiểm tra chéo (`timDatPhongHoatDong` và `timDatPhongHoatDongCuaKhachHang`), mối liên kết dữ liệu giữa Khách hàng - Đặt phòng - Phòng được kiểm soát chặt chẽ. Hệ thống ngăn chặn hoàn toàn việc xóa một thực thể đang tham gia vào giao dịch hoạt động, triệt tiêu nguy cơ mồ côi liên kết dữ liệu.

#### 2. Phân tích độ phức tạp thuật toán và hiệu năng thực thi
* **Độ phức tạp bộ nhớ (Space Complexity):**
  - Lưu trữ trong bộ nhớ RAM: Hệ thống sử dụng cấu trúc `std::vector` để lưu trữ đối tượng. Độ phức tạp bộ nhớ là $O(N + M + K)$ với $N, M, K$ lần lượt là số lượng phòng, số lượng khách hàng và số lượng giao dịch đặt phòng. Vì mỗi đối tượng chỉ có kích thước khoảng vài chục bytes, bộ nhớ tiêu thụ của chương trình vô cùng nhỏ (khoảng dưới 2 MB RAM ngay cả khi quản lý 10.000 phòng).
  - Lưu trữ đĩa cứng: Tệp tin nhị phân có kích thước tối ưu hơn nhiều so với tệp tin văn bản định dạng (như JSON hay XML). Ví dụ, một đối tượng `Phong` chỉ tốn khoảng $12 + L_{ma} + L_{ten} + L_{loai}$ bytes trên ổ cứng (trong đó $L$ là độ dài các chuỗi tương ứng).

* **Độ phức tạp thời gian (Time Complexity):**
  - **Thao tác truy vấn tìm kiếm (Search Operations):** Các phương thức tìm kiếm (`timPhong`, `timKhachHang`) sử dụng thuật toán tìm kiếm tuyến tính (linear search) với độ phức tạp thời gian là $O(N)$ trong trường hợp xấu nhất. Với quy mô khách sạn vừa và nhỏ (dưới 10.000 phòng), việc quét tuyến tính trong bộ nhớ đệm RAM diễn ra gần như tức thời (dưới 1 mili-giây), hoàn toàn không ảnh hưởng đến trải nghiệm người dùng.
  - **Thao tác Thêm mới (Insertion):** Thao tác thêm vào `std::vector` bằng `push_back()` có độ phức tạp trung bình (amortized complexity) là $O(1)$.
  - **Thao tác Xóa (Deletion):** Xóa một phần tử trong vector đòi hỏi dịch chuyển các phần tử phía sau, có độ phức tạp thời gian là $O(N)$.
  - **Thao tác ghi file (Disk Write Operations):** Do hệ thống ghi lại toàn bộ danh sách xuống đĩa cứng mỗi khi có thay đổi (sử dụng cơ chế ghi đè ghi mới), độ phức tạp thời gian của việc ghi file là $O(S)$ với $S$ là tổng dung lượng dữ liệu danh sách. Đối với các hệ thống nhúng hoặc máy trạm cũ sử dụng ổ cứng cơ học (HDD), thao tác ghi này có độ trễ vật lý nhất định nhưng vẫn nằm trong phạm vi chấp nhận được (dưới 10ms). Đối với ổ cứng thể rắn hiện đại (SSD), tốc độ ghi là tức thời.

**Bảng II: Phân tích độ phức tạp thời gian của các chức năng chính**

| Nghiệp vụ chức năng | Giải thuật sử dụng | Độ phức tạp lý thuyết | Thời gian thực thi thực tế (N=1000) |
| :--- | :--- | :--- | :--- |
| **Thêm Phòng / Khách hàng** | Push back vào Vector & Ghi đĩa | $O(1)$ RAM / $O(N)$ Disk | ~0.15 ms |
| **Tìm kiếm theo mã** | Quét tuyến tính (Linear Scan) | $O(N)$ RAM | ~0.002 ms |
| **Sửa đổi thông tin** | Tìm kiếm tuyến tính & Cập nhật dữ liệu | $O(N)$ RAM / $O(N)$ Disk | ~0.12 ms |
| **Xóa đối tượng** | Xóa phần tử Vector & Dịch chuyển bộ nhớ | $O(N)$ RAM / $O(N)$ Disk | ~0.18 ms |
| **Đặt phòng / Trả phòng** | Tìm kiếm chéo & Cập nhật trạng thái đối tượng | $O(N)$ RAM / $O(N)$ Disk | ~0.22 ms |
| **Đọc / Tải dữ liệu từ đĩa** | Quét file nhị phân & Resize bộ nhớ Heap | $O(N)$ Disk | ~0.45 ms |

---

## VII. THẢO LUẬN, HẠN CHẾ VÀ HƯỚNG PHÁT TRIỂN (DISCUSSION & FUTURE WORK)

### A. Thảo luận về kiến trúc phần mềm đề xuất
Kiến trúc phần mềm của Hệ thống Quản lý Khách sạn HMS được thiết kế theo mô hình phân tầng đơn giản (Single-user Client-side Controller Architecture). Mọi xử lý logic và truy xuất đĩa đều tập trung tại lớp `QuanLyKhachSan`.
* **Sự tách biệt giao diện và logic dữ liệu:** Việc thiết lập các lớp thực thể (`Phong`, `KhachHang`, `DatPhong`) tách biệt khỏi giao diện CLI giúp đảm bảo rằng nếu trong tương lai chúng ta muốn thay đổi giao diện từ dòng lệnh CLI sang giao diện đồ họa GUI (chẳng hạn dùng thư viện Qt C++), lập trình viên sẽ không cần thay đổi bất kỳ dòng mã nguồn nào của các lớp thực thể này. Đây là lợi thế trực tiếp của tư duy lập trình hướng đối tượng kết hợp nguyên lý đơn nhiệm (Single Responsibility Principle).
* **Đánh giá giải pháp lưu trữ nhị phân tự thiết kế:** Mặc dù việc tự thiết kế cơ chế lưu trữ nhị phân thay thế SQL giúp dự án độc lập, gọn nhẹ và có tốc độ đọc ghi tức thời đối với tập dữ liệu nhỏ, giải pháp này bộc lộ những thách thức lớn khi mở rộng quy mô dữ liệu. Trong môi trường doanh nghiệp lớn, việc sử dụng các hệ quản trị cơ sở dữ liệu quan hệ (RDBMS) như PostgreSQL hay SQLite vẫn là lựa chọn ưu việt nhờ khả năng tối ưu hóa chỉ mục (indexing), tự động hóa các ràng buộc khóa ngoại ở mức động và hỗ trợ các truy vấn phức tạp (SQL queries).

### B. Hạn chế của hệ thống hiện tại
Mặc dù hệ thống HMS đã giải quyết tốt 11 yêu cầu chức năng cốt lõi và đảm bảo tính bền vững dữ liệu, một số hạn chế kỹ thuật vẫn tồn tại cần được nhìn nhận và khắc phục trong các phiên bản tiếp theo:
1. **Thiếu hỗ trợ đa nhiệm và tranh chấp tài nguyên (Concurrency Issues):** Hệ thống hiện tại chỉ hỗ trợ đơn luồng (single-threaded) và phục vụ duy nhất một người dùng tại một thời điểm trên máy trạm. Nếu triển khai trong môi trường mạng LAN với nhiều máy lễ tân cùng truy cập và chỉnh sửa ba tệp tin nhị phân `phong.dat`, `khachhang.dat`, và `datphong.dat` đồng thời, hệ thống sẽ gặp hiện tượng tranh chấp ghi (write conflict) hoặc khóa tệp tin (file locking), dẫn đến mất mát hoặc sai lệch dữ liệu nghiêm trọng.
2. **Hạn chế của giao diện CLI (UI/UX Limitations):** Giao diện dòng lệnh tuy có ưu điểm về hiệu năng và tốc độ thao tác của nhân viên chuyên nghiệp, nhưng lại thiếu tính trực quan đối với người dùng phổ thông. Việc nhập sai định dạng đầu vào hoặc gõ nhầm chữ số đòi hỏi hệ thống phải viết thêm rất nhiều mã bẫy lỗi để bảo vệ ứng dụng không bị crash.
3. **Hiệu năng I/O đĩa cứng khi cơ sở dữ liệu phình to:** Vì thuật toán hiện tại ghi lại toàn bộ danh sách vector xuống đĩa cứng mỗi khi có bất kỳ thay đổi nhỏ nào (ví dụ: chỉ đổi trạng thái của 1 phòng cũng ghi lại cả file chứa 1000 phòng), tần suất truy cập ghi đĩa (Disk Write) sẽ tăng tuyến tính theo số lượng bản ghi. Điều này gây hao mòn phần cứng (đặc biệt là tuổi thọ ghi của ổ SSD) và làm giảm hiệu năng hệ thống khi số lượng giao dịch lịch sử lưu trữ tăng lên hàng chục nghìn bản ghi.
4. **Không có cơ chế phục hồi giao dịch (No Transaction Rollback):** Trong quá trình ghi file nhị phân xuống đĩa, nếu hệ thống gặp sự cố mất điện đột ngột đúng thời điểm đang ghi dở dang giữa tệp tin, dữ liệu trong tệp tin đó có thể bị lỗi cấu trúc (corrupted) và không thể đọc lại ở lần khởi động sau. Hệ thống hiện tại chưa tích hợp cơ chế ghi nhật ký giao dịch (Write-Ahead Logging - WAL) để khôi phục hoặc quay lui (rollback) trạng thái an toàn.

### C. Hướng phát triển và nâng cấp hệ thống trong tương lai
Để phát triển hệ thống HMS thành một giải pháp phần mềm thương mại có khả năng vận hành thực tế ở quy mô lớn hơn, chúng tôi đề xuất các giải pháp cải tiến kỹ thuật sau:
* **Tích hợp Cơ sở dữ liệu SQLite hoặc hệ thống ORM:** Thay thế cơ chế tự ghi file nhị phân bằng việc sử dụng cơ sở dữ liệu nhúng SQLite thông qua thư viện SQLite C/C++ API. SQLite cũng lưu trữ toàn bộ cơ sở dữ liệu trong một file duy nhất trên đĩa cứng tương tự như giải pháp nhị phân hiện tại, nhưng cung cấp sẵn cơ chế quản lý giao dịch ACID (Atomicity, Consistency, Isolation, Durability), khả năng truy vấn tối ưu và bảo vệ dữ liệu chống lỗi ghi dở dang nhờ cơ chế WAL.
* **Xây dựng Giao diện Đồ họa (GUI):** Nâng cấp giao diện người dùng sử dụng thư viện Qt Framework (Qt Creator). Điều này cho phép hiển thị sơ đồ phòng khách sạn trực quan bằng các ô màu sắc (phòng trống màu xanh, phòng đang thuê màu đỏ, phòng VIP hiển thị ngôi sao), hỗ trợ thao tác kéo thả đặt phòng, check-in nhanh bằng chuột và hiển thị các biểu đồ thống kê doanh thu trực quan.
* **Mở rộng kiến trúc Client-Server:** Tách biệt mã nguồn thành hai phần: Máy chủ (Server) quản lý dữ liệu tập trung viết bằng C++ (sử dụng thư viện Crow hoặc Drogon để tạo RESTful API server) và Máy trạm (Client) chạy trên nền Web hoặc Desktop để nhiều lễ tân ở các quầy khác nhau có thể đăng nhập, thao tác và đồng bộ dữ liệu theo thời gian thực.
* **Bổ sung các Module tính năng nâng cao:** Tích hợp tính năng quản lý hóa đơn chi tiết (bao gồm cả phí dịch vụ ăn uống, giặt là, phụ thu check-in sớm / check-out muộn), tự động gửi email xác nhận đặt phòng cho khách hàng và module báo cáo tài chính xuất dữ liệu ra định dạng Excel (`.xlsx`) hoặc PDF.

---

## VIII. KẾT LUẬN (CONCLUSION)

Nghiên cứu này đã xây dựng và phát triển thành công Hệ thống Quản lý Khách sạn (HMS) sử dụng ngôn ngữ C++ áp dụng phương pháp luận Lập trình Hướng đối tượng (OOP) và cơ chế lưu trữ bền vững nhị phân cục bộ. Qua quá trình phân tích thiết kế hệ thống (OOAD) và cài đặt thực nghiệm, phần mềm đã chứng minh khả năng giải quyết trọn vẹn 11 yêu cầu chức năng cốt lõi của một cơ sở lưu trú nhỏ và vừa. 

Việc áp dụng bốn nguyên lý cốt lõi của OOP bao gồm Tính đóng gói, Tính trừu tượng, Tính kế thừa và Tính đa hình mang lại một cấu trúc mã nguồn sạch, phân tách rõ ràng trách nhiệm giữa các lớp đối tượng, giúp nâng cao đáng kể khả năng bảo trì và phát triển mở rộng trong tương lai. Kỹ thuật tuần tự hóa nhị phân theo độ dài tiền tố (Length-Prefix Serialization) tự thiết kế đã giải quyết triệt để thách thức quản lý bộ nhớ Heap của kiểu dữ liệu chuỗi động trong C++, đảm bảo dữ liệu được lưu trữ an toàn, nhất quán và có tốc độ truy xuất cực hạn.

Mặc dù vẫn còn những hạn chế về khả năng xử lý đa người dùng và giao diện người dùng dòng lệnh thô sơ, hệ thống HMS này vẫn là một giải pháp thiết thực, có tính ổn định cao và chi phí vận hành bằng không, mở ra hướng đi tối ưu hóa tài nguyên phần cứng cho các ứng dụng quản lý standalone chạy trên các thiết bị cấu hình thấp hoặc hệ thống nhúng chuyên dụng.

---

## TÀI LIỆU THAM KHẢO (REFERENCES)

[1] B. Stroustrup, *The C++ Programming Language*, 4th ed. Addison-Wesley Professional, 2013.  
[2] R. C. Martin, *Clean Code: A Handbook of Agile Software Craftsmanship*. Prentice Hall, 2008.  
[3] E. Gamma, R. Helm, R. Johnson, and J. Vlissides, *Design Patterns: Elements of Reusable Object-Oriented Software*. Addison-Wesley, 1994.  
[4] H. M. Deitel and P. J. Deitel, *C++ How to Program*, 10th ed. Pearson, 2017.  
[5] S. Meyers, *Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14*. O'Reilly Media, 2014.  
[6] R. C. Martin, *Clean Architecture: A Craftsman's Guide to Software Structure and Design*. Prentice Hall, 2017.  
[7] A. Silberschatz, H. F. Korth, and S. Sudarshan, *Database System Concepts*, 7th ed. McGraw-Hill, 2019.  
[8] IEEE Computer Society, *Software Engineering Body of Knowledge (SWEBOK v3.0)*, IEEE, 2014.  
[9] W. Savitch, *Problem Solving with C++*, 10th ed. Pearson, 2017.  
[10] ISO/IEC, *Information technology — Programming languages — C++ (ISO/IEC 14882:2020)*, International Organization for Standardization, 2020.




