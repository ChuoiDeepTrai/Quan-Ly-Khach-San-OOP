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
    // Xóa khoảng trắng thừa trong chuỗi
    static void XoaKhoangTrangThua(string &tieuDe);

    // Định dạng lại tiền tệ nhập vào
    static string DinhDanhTienVND(long long gia);

    // Thông báo thành công khi hoàn thành xong chức năng
    static void ThongBaoThanhCong(const string &msg);

    // Thông báo lỗi khi gặp điều kiện không phù hợp
    static void ThongBaoLoi(const string &msg);

    // Hiển thị các tiêu đề khi chọn các chức năng
    static void HienThiTieuDe(string tieuDe, int width = 30);

    // Chuẩn hóa mã chữ thường sang chữ in hoa
    static string ChuanHoaMa(const string &s);

    // Lấy thời gian hiện tại
    static string LayThoiGianHienTai();
};

#endif