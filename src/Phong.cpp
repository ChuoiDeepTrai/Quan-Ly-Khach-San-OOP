#include <iostream>
#include <fstream>
#include <string>
#include "../include/Phong.h"

using namespace std; 

Phong::Phong() : maPhong(""), tenPhong(""), loaiPhong(""), giaPhong(0.0), trangThai(false) {}
Phong::Phong(string maP, string tenP, string loaiP, double giaP)
    : maPhong(TienIch::ChuanHoaMa(maP)), tenPhong(tenP), loaiPhong(loaiP), giaPhong(giaP), trangThai(false) {}

// Getter & Setter
string Phong::getMaPhong() const
{
    return maPhong;
}
void Phong::setMaPhong(string maP)
{
    maPhong = TienIch::ChuanHoaMa(maP);
}

string Phong::getTenPhong() const
{
    return tenPhong;
}
void Phong::setTenPhong(string tenP)
{
    tenPhong = tenP;
}

string Phong::getLoaiPhong() const
{
    return loaiPhong;
}
void Phong::setLoaiPhong(string loaiP)
{
    loaiPhong = loaiP;
}

double Phong::getGiaPhong() const
{
    return giaPhong;
}
void Phong::setGiaPhong(double giaP)
{
    giaPhong = giaP;
}

bool Phong::getTrangThai() const
{
    return trangThai;
}
void Phong::setTrangThai(bool tt)
{
    trangThai = tt;
}

// Ghi file phong.dat
void Phong::GhiFilePhong(ofstream &file) const
{
    // Ghi mã phòng
    int maPhongLength = maPhong.size();
    file.write((char *)&maPhongLength, sizeof(maPhongLength));
    file.write(maPhong.c_str(), maPhongLength);

    // Ghi tên phòng
    int tenPhongLength = tenPhong.size();
    file.write((char *)&tenPhongLength, sizeof(tenPhongLength));
    file.write(tenPhong.c_str(), tenPhongLength);

    // Ghi loại phòng
    int loaiLength = loaiPhong.size();
    file.write((char *)&loaiLength, sizeof(loaiLength));
    file.write(loaiPhong.c_str(), loaiLength);

    // Ghi giá phòng (double)
    file.write((char *)&giaPhong, sizeof(giaPhong));

    // Ghi trang thai phong (bool)
    file.write((char *)&trangThai, sizeof(trangThai));
}

// Đọc file phong.dat
void Phong::DocFilePhong(ifstream &file)
{
    // Đọc mã phòng
    int maLength;
    if (!file.read((char *)&maLength, sizeof(maLength)) && maLength <= 0 && maLength > 1000)
    {
        file.setstate(ios::failbit);
        return;
    }
    maPhong.resize(maLength);
    file.read(&maPhong[0], maLength);

    // Đọc tên phòng
    int tenLength;
    if (!file.read((char *)&tenLength, sizeof(tenLength)) && tenLength <= 0 && tenLength > 1000)
    {
        file.setstate(ios::failbit);
        return;
    }
    tenPhong.resize(tenLength);
    file.read(&tenPhong[0], tenLength);

    // Đọc loại phòng
    int loaiLength;
    if (!file.read((char *)&loaiLength, sizeof(loaiLength)) && loaiLength <= 0 && loaiLength > 1000)
    {
        file.setstate(ios::failbit);
        return;
    }
    loaiPhong.resize(loaiLength);
    file.read(&loaiPhong[0], loaiLength);

    // Đọc giá phòng
    if(!file.read((char *)&giaPhong, sizeof(giaPhong)))
    {
        return;
    }

    // Đọc trạng thái phòng
    if(!file.read((char *)&trangThai, sizeof(trangThai)))
    {
        return;
    }
}
