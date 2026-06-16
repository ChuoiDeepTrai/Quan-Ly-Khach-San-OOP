#include "../include/DatPhong.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

DatPhong::DatPhong() : maKH(""), maPhong(""), ngayDat(""), trangThai(false) {}
DatPhong::DatPhong(string makh, string maphong, string ngay)
    : maKH(TienIch::ChuanHoaMa(makh)), maPhong(TienIch::ChuanHoaMa(maphong)), ngayDat(ngay), trangThai(true) {}

// Getter & Setter
string DatPhong::getMaKH() const
{
    return maKH;
}
void DatPhong::setMaKH(string makh)
{
    maKH = TienIch::ChuanHoaMa(makh);
}

string DatPhong::getMaPhong() const
{
    return maPhong;
}
void DatPhong::setMaPhong(string maphong)
{
    maPhong = TienIch::ChuanHoaMa(maphong);
}

string DatPhong::getNgayDat() const
{
    return ngayDat;
}
void DatPhong::setNgayDat(string ngay)
{
    ngayDat = ngay;
}

bool DatPhong::getTrangThai() const
{
    return trangThai;
}
void DatPhong::setTrangThai(bool tt)
{
    trangThai = tt;
}

// Ghi file datphong.dat
void DatPhong::GhiFileDatPhong(ofstream &file) const
{
    // Ghi mã phòng
    int maPhongLength = maPhong.size();
    file.write((char *)&maPhongLength, sizeof(maPhongLength));
    file.write(maPhong.c_str(), maPhongLength);

    // Ghi mã khách hàng
    int maKHLength = maKH.size();
    file.write((char *)&maKHLength, sizeof(maKHLength));
    file.write(maKH.c_str(), maKHLength);

    // Ghi ngày đặt
    int ngayDatLength = ngayDat.size();
    file.write((char *)&ngayDatLength, sizeof(ngayDatLength));
    file.write(ngayDat.c_str(), ngayDatLength);

    // Ghi trạng thái
    file.write((char *)&trangThai, sizeof(trangThai));
}

// Đọc file datphong.dat
void DatPhong::DocFileDatPhong(ifstream &file)
{
    // Đọc mã phòng
    int maPhongLength;
    file.read((char *)&maPhongLength, sizeof(maPhongLength));
    maPhong.resize(maPhongLength);
    file.read(&maPhong[0], maPhongLength);

    // Đọc ma khách hàng
    int maKHLength;
    file.read((char *)&maKHLength, sizeof(maKHLength));
    maKH.resize(maKHLength);
    file.read(&maKH[0], maKHLength);

    // Đọc ngày đặt
    int ngayDatLength;
    file.read((char *)&ngayDatLength, sizeof(ngayDatLength));
    ngayDat.resize(ngayDatLength);
    file.read(&ngayDat[0], ngayDatLength);

    // Đọc trạng thái đặt phòng
    file.read((char *)&trangThai, sizeof(trangThai));
}