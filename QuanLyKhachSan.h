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
    const string FILE_PHONG = "phong.dat";
    const string FILE_KHACH_HANG = "khachhang.dat";
    const string FILE_DAT_PHONG = "datphong.dat";

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
    void GhiFilePhong() const;  
    void DocFilePhong();

    void GhiFileKhachHang() const;
    void DocFileKhachHang();

    void GhiFileDatPhong() const;
    void DocFileDatPhong();

    void luuToanBoDuLieu() const;

    void taiToanBoDuLieu();

    // --- QUẢN LÝ DANH SÁCH PHÒNG ---
    void DanhSachPhong();

    // 1. Thêm khách hàng
    void ThemPhong();

    // 2. Sửa thông tin phòng
    void SuaPhong();

    // 3. Xoa phong
    void XoaPhong();

    // --- QUẢN LÝ DANH SACH KHACH HANG ---
    void DanhSachKhachHang();

    // Thêm khách hàng
    void ThemKhachHang();

    // Sửa thông tin khách hàng
    void SuaKhachHang();

    // Xoa thong tin khach hang
    void XoaKhachHang();

    // Danh sách phong trống
    void DanhSachPhongTrong();

    void DatPhongKhachSan();

    // Danh sách các phòng đang được thuê
    void DanhSachPhongThue();

    // Check-Out
    void TraPhongCheckOut();
};

#endif