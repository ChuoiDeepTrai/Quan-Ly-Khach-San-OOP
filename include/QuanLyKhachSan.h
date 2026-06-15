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
    // Tên các tệp dữ liệu nhị phân
    const string FILE_PHONG      = "data/phong.dat";
    const string FILE_KHACH_HANG  = "data/khachhang.dat";
    const string FILE_DAT_PHONG   = "data/datphong.dat";

    // Biến toàn cục
    vector<Phong> ds_phong;
    vector<KhachHang> ds_khach_hang;
    vector<DatPhong> ds_dat_phong;

    // 1. Tìm phòng theo mã phòng
    Phong *timPhong(const string &maPhong);

    // 2. Tìm khách hàng theo mã Khách hàng
    KhachHang *timKhachHang(const string &maKH);

    // 3.
    // 3.1. Tìm bản ghi đặt phòng đang hoạt động cho một phòng cụ thể
    DatPhong *timDatPhongHoatDong(const string &maPhong);

    // 3.2. Tìm xem khách hàng có bản ghi đặt phòng đang hoạt động nào không
    DatPhong *timDatPhongHoatDongCuaKhachHang(const string &maKH);

public:
    QuanLyKhachSan();

    // --- XỬ LÝ FILE  ---
    // 1. Ghi/Đọc file phòng
    void GhiFilePhong() const;  
    void DocFilePhong();

    // 2. Ghi/Đọc file khách hàng
    void GhiFileKhachHang() const;
    void DocFileKhachHang();

    // 4. Ghi/Đọc file đặt phòng
    void GhiFileDatPhong() const;
    void DocFileDatPhong();

    // Tải/Lưu dữ liệu
    void luuToanBoDuLieu() const;
    void taiToanBoDuLieu();

    // --- QUẢN LÝ DANH SÁCH ---
    // 1. Danh sách phòng
    void DanhSachPhong();

    // 2. Danh sách khách hàng
    void DanhSachKhachHang();

    // 3. Danh sách phong trống
    void DanhSachPhongTrong();

    // 4. Danh sách các phòng đang được thuê
    void DanhSachPhongThue();

    // --- Các chức năng chính ---
    // 1. Thêm khách hàng
    void ThemPhong();

    // 2. Sửa thông tin phòng
    void SuaPhong();

    // 3. Xoa phong
    void XoaPhong();

    // 4. Thêm khách hàng
    void ThemKhachHang();

    // 5. Sửa thông tin khách hàng
    void SuaKhachHang();

    // 6. Xóa khách hàng
    void XoaKhachHang();

    // 7. Đặt phòng khách sạn (check-in)
    void DatPhongKhachSan();

    // 8. Trả phòng khách sạn (check-out)
    void TraPhongCheckOut();
};

#endif