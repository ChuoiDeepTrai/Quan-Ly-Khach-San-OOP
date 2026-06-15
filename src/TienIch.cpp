#include "../include/TienIch.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

// Xóa khoảng trắng thừa trong chuỗi
void TienIch::XoaKhoangTrangThua(string &tieuDe)
{
    tieuDe.erase(0, tieuDe.find_first_not_of(" \t\r\n"));
    tieuDe.erase(tieuDe.find_last_not_of(" \t\r\n") + 1);
}

// Định dạng lại tiền tệ nhập vào
string TienIch::DinhDanhTienVND(long long gia)
{
    string s = to_string(gia);
    string ketqua = "";
    int dem = 0;

    // Duyệt ngược từ cuối dãy số để thêm dấu châm ngăn cách
    for (int i = s.length() - 1; i >= 0; i--)
    {
        ketqua += s[i];
        dem++;
        if (dem % 3 == 0 && i != 0)
        {
            ketqua += "."; // dấu chấm cách hàng nghìn
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

// Hiển thị tiêu đề
void TienIch::HienThiTieuDe(string tieuDe, int width)
{
    int len = tieuDe.length();
    int padding = (width - len) / 2;

    // In dòng trên
    cout << Color::BOLD << Color::BLUE << string(width, '=') << "\n";

    // In tiêu đề căn giữa
    cout << string(padding, ' ') << tieuDe << "\n";

    // In dòng dưới
    cout << string(width, '=') << Color::RESET << "\n";
}

// Chuẩn hóa mã chữ thường sang chữ in hoa
string TienIch::ChuanHoaMa(const string &s)
{
    string result = s;
    for (char &c : result)
    {
        c = toupper(static_cast<unsigned char>(c));
    }
    return result;
}

// Lấy thời gian hiện tại
string TienIch::LayThoiGianHienTai()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", now);
    return string(buf);
}