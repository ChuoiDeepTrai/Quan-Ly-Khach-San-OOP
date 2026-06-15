#include "../include/QuanLyKhachSan.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std; 

// 1. Tìm phòng theo mã phòng
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

// 2. Tìm khách hàng theo mã Khách hàng
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

// 3.
// 3.1. Tìm bản ghi đặt phòng đang hoạt động cho một phòng cụ thể
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

// 3.2. Tìm xem khách hàng có bản ghi đặt phòng đang hoạt động nào không
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

// =====================================
// --- XỬ LÝ FILE  ---
// =====================================

// 1. Ghi/Đọc file phòng
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
    // Đọc số lượng phòng
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

// 2. Ghi/Đọc file khách hàng
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

    // Đọc số lượng khách hàng
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

// 3. Ghi/Đọc file đặt phòng
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

// 4. Tải/Load các file
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

// =====================================
// --- QUẢN LÝ DANH SÁCH ---
// =====================================

// 1. Danh sách phòng.
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

// 2. Danh sách khách hàng
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

// 3. Danh sách phòng đang trống
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
        string tt = Color::GREEN + "Dang trong" + Color::RESET;
        if (!p.getTrangThai())
        {
            cout << left;
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
        return;
    }
}

// 4. Danh sách phòng đang được thuê
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

            string tenP = p->getTenPhong();
            string loaiP = p->getLoaiPhong();
            string giaP = TienIch::DinhDanhTienVND(p->getGiaPhong());

            string tenkh = kh->getTenKH();

            string tt = Color::RED + "Dang thue" + Color::RESET;

            cout << setw(15) << p->getMaPhong()
                 << setw(22) << tenP
                 << setw(15) << kh->getMaKH()
                 << setw(25) << tenkh
                 << setw(18) << loaiP
                 << setw(20) << giaP
                 << setw(25) << dp.getNgayDat()
                 << setw(10) << tt << "\n";

            demPhongThue++;
        }
    }

    if (demPhongThue == 0)
    {
        TienIch::ThongBaoLoi("Chua co phong nao duoc thue!");
        return;
    }
    cout << string(150, '-') << "\n";
}

// =====================================
// --- CÁC CHỨC NĂNG CHÍNH ---
// =====================================

// 1. Thêm khách hàng
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

// 2. Sửa thông tin phòng
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
    cout << "Nhap ma phong can sua (Nhap 0 de huy): ";
    getline(cin, ma);
    if (ma == "0")
    {
        cout << "Da huy thao tac!\n";
        return;
    }

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

        cout << "\n--- Nhap lua chon ---\n";
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
            p->setTenPhong(ten);
            TienIch::ThongBaoThanhCong("Da sua ten phong.");
            break;
        }
        case 2:
        {
            string loai;
            cout << "Nhap loai phong moi: ";
            getline(cin, loai);
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

// 3. Xóa phòng
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

// 4. Sửa thông tin khách hàng
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
            kh->setTenKH(tenKH);
            TienIch::ThongBaoThanhCong("Doi ten khach hang thanh cong!");
            break;
        }
        case 2:
        {
            string sdt;
            cout << "Nhap SDT khach hang: ";
            getline(cin, sdt);
            kh->setSDT(sdt);
            TienIch::ThongBaoThanhCong("Doi SDT khach hang thanh cong!");
            break;
        }
        case 3:
        {
            string cccd;
            cout << "Nhap CCCD khach hang: ";
            getline(cin, cccd);
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

// 5. Xóa khách hàng
void QuanLyKhachSan::XoaKhachHang()
{
    TienIch::HienThiTieuDe("XOA KHACH HANG");

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
    cout << Color::YELLOW << "Ban co chac chan muon xoa phong " << kh->getTenKH() << "(" << kh->getMaKH() << ") ?" << " (Y/N): " << Color::RESET;
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y")
    {
        // Thực hiện xóa khách hàng khỏi vector bằng con trỏ
        ds_khach_hang.erase(ds_khach_hang.begin() + (kh - &ds_khach_hang[0]));
        GhiFileKhachHang();
        TienIch::ThongBaoThanhCong("Xoa khach hang thanh cong!");
    }
    else
    {
        cout << "Da huy thao tac xoa!" << endl;
    }
}

// 6. Đặt phòng khách sạn (check-in)
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

// 7. Trả phòng khách sạn (check-out)
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