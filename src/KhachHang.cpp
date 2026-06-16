#include "../include/KhachHang.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std; 

KhachHang::KhachHang() : maKH(""), tenKH(""), SDT(""), CCCD("") {}
KhachHang::KhachHang(string ma, string ten, string sdt, string cccd)
    : maKH(TienIch::ChuanHoaMa(ma)), tenKH(ten), SDT(sdt), CCCD(cccd) {}

// Getter & Setter
string KhachHang::getMaKH() const
{
    return maKH;
}
void KhachHang::setMaKH(string ma)
{
    maKH = TienIch::ChuanHoaMa(ma);
}

string KhachHang::getTenKH() const
{
    return tenKH;
}
void KhachHang::setTenKH(string ten)
{
    tenKH = ten;
}

string KhachHang::getSDT() const
{
    return SDT;
}
void KhachHang::setSDT(string sdt)
{
    SDT = sdt;
}

string KhachHang::getCCCD() const
{
    return CCCD;
}
void KhachHang::setCCCD(string cccd)
{
    CCCD = cccd;
}

// Ghi file khachhang.dat
void KhachHang::GhiFileKhachHang(ofstream &file) const
{
    // Ghi mã khách hàng
    int maKHLength = maKH.size();
    file.write((char *)&maKHLength, sizeof(maKHLength));
    file.write(maKH.c_str(), maKHLength);

    // Ghi tên khách hàng
    int tenKHLength = tenKH.size();
    file.write((char *)&tenKHLength, sizeof(tenKHLength));
    file.write(tenKH.c_str(), tenKHLength);

    // Ghi SĐT khách hàng
    int sdtLength = SDT.size();
    file.write((char *)&sdtLength, sizeof(sdtLength));
    file.write(SDT.c_str(), sdtLength);

    // Ghi CCCD khách hàng
    int cccdLength = CCCD.size();
    file.write((char *)&cccdLength, sizeof(cccdLength));
    file.write(CCCD.c_str(), cccdLength);
}

// Đọc file khachhang.dat
void KhachHang::DocFileKhachHang(ifstream &file)
{
    // Đọc mã khách hàng
    int maKHLength;
    file.read((char *)&maKHLength, sizeof(maKHLength));
    maKH.resize(maKHLength);
    file.read(&maKH[0], maKHLength);

    // Đọc tên khách hàng
    int tenKHLength;
    file.read((char *)&tenKHLength, sizeof(tenKHLength));
    tenKH.resize(tenKHLength);
    file.read(&tenKH[0], tenKHLength);

    // Đọc SĐT khách hàng
    int sdtLength;
    file.read((char *)&sdtLength, sizeof(sdtLength));
    SDT.resize(sdtLength);
    file.read(&SDT[0], sdtLength);

    // Đọc CCCD khách hàng
    int cccdLength;
    file.read((char *)&cccdLength, sizeof(cccdLength));
    CCCD.resize(cccdLength);
    file.read(&CCCD[0], cccdLength);
}
