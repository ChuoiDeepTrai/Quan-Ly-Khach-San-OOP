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

string TienIch::NhapChuoi(const string &promt)
{
    string s;
    while (true)
    {
        cout << promt;
        getline(cin, s);
        XoaKhoangTrangThua(s);
        if (s.empty())
        {
            ThongBaoLoi("Khong duoc de trong!\n");
            continue;
        }
        break;
    }
    return s;
}

double TienIch::NhapSoThuc(const string &promt, double val)
{   
    while (true)
    {
        string s;
        cout << promt;
        getline(cin, s);
        TienIch::XoaKhoangTrangThua(s);

        if(s.empty())
        {
            TienIch::ThongBaoLoi("Khong duoc bo trong!\n");
            continue;
        }

        try
        {
            size_t giaTri;
            val = stod(s, &giaTri);

            if(giaTri < s.length())
            {
                TienIch::ThongBaoLoi("Loi: Thong tin chua ky tu la! Vui long thu lai.");
                continue;
            }

            if(val < 0)
            {
                TienIch::ThongBaoLoi("Loi: Gia tri khong duoc am! Vui long thu lai.");
                continue;
            }
            break;
        }
        catch(...)
        {
            TienIch::ThongBaoLoi("Khong hop le! Vui long nhap mot so thuc.");
        }
    }
    return val;
}

// Hàm nhập số nguyên
int TienIch::NhapSoNguyen(const string &promt, int val)
{
        while (true)
    {
        string s;
        cout << promt;
        getline(cin, s);
        TienIch::XoaKhoangTrangThua(s);

        if(s.empty())
        {
            TienIch::ThongBaoLoi("Khong duoc bo trong!\n");
            continue;
        }

        try
        {
            size_t giaTri;
            val = stod(s, &giaTri);

            if(giaTri < s.length())
            {
                throw string(Color::BOLD + Color::RED + "Chua ky tu la!" + Color::RESET);
                continue;
            }

            if(val < 0)
            {
                throw string(Color::BOLD + Color::RED + "Loi! Vui long thu lai!" + Color::RESET);
                continue;
            }
            break;
        }
        catch(...)
        {
            TienIch::ThongBaoLoi("Khong hop le! Vui long nhap mot so nguyen.");
        }
    }
    return val;
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

void TienIch::ThongBaoThanhCong(const string &promt)
{
    cout << Color::BOLD << Color::GREEN << promt << Color::RESET << "\n";
}

void TienIch::ThongBaoLoi(const string &promt)
{
    cout << Color::BOLD << Color::RED << promt << Color::RESET << "\n";
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