#include <iostream>
#include "include/QuanLyKhachSan.h"

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
        cin >> choice;
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
            break;
        case 8:
            qlks.TraPhongCheckOut();
            break;
        case 9:
            qlks.DanhSachPhongTrong();
            break;
        case 10:
            qlks.DanhSachPhongThue();
            break;
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