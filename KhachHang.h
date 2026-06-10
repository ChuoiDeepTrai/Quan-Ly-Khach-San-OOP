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
    // Getter & Setter
    string getMaKH() const;
    void setMaKH(string ma);

    string getTenKH() const;
    void setTenKH(string ten);

    string getSDT() const;
    void setSDT(string sdt);

    string getCCCD() const;
    void setCCCD(string cccd);

    // Ghi file khachhang.dat
    void GhiFileKhachHang(ofstream &file) const;

    // Đọc file khachhang.dat
    void DocFileKhachHang(ifstream &file);
};


#endif