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
    string loaiPhong; // VIP / Thuong / Doi / Don / ....
    double giaPhong;
    bool trangThai; // 0. Da tra phong ; 1: Dang duoc thue
public:
    Phong();
    Phong(string maP, string tenP, string loaiP, double giaP);
    
    // Getter & Setter
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

    // Ghi file phong.dat
    void GhiFilePhong(ofstream &file) const;

    // Đọc file phong.dat
    void DocFilePhong(ifstream &file);
};

#endif