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
    bool trangThai; // 0. Da check-out, 1. Dang duoc thue
public:
    DatPhong();
    DatPhong(string makh, string maphong, string ngay);

    // Getter & Setter
    string getMaKH() const;
    void setMaKH(string makh);

    string getMaPhong() const;
    void setMaPhong(string maphong);

    string getNgayDat() const;
    void setNgayDat(string ngay);

    bool getTrangThai() const;
    void setTrangThai(bool tt);
    
    // Ghi file datphong.dat
    void GhiFileDatPhong(ofstream &file) const;

    // Đọc file datphong.dat
    void DocFileDatPhong(ifstream &file);
};

#endif