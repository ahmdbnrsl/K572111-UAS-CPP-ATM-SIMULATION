#include "chalk.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace chalk;

struct User
{
    string Nama;
    string Password;
    int Saldo;
};

class ATM
{
    char option;
    vector<User> user;
    User isLoginUser;

public:
    void Start()
    {
        cout << bg::Blue.Wrap(" ======= [ MESIN ATM KOMPUTAMA ] ======= ") << endl
             << "Pilih Menu Dibawah ini\n"
             << "1. Daftar Akun\n"
             << "2. Login\n"
             << "3. Cek Saldo\n"
             << "4. Setor Tunai\n"
             << "5. Tarik Tunai\n"
             << "6. Transfer\n"
             << "7. Logout\n"
             << "MASUKAN OPSI SESUAI NOMOR DIATAS (EX: 1, 2, 3 dst) : ";
        cin >> option;
        switch (option)
        {
        case '1':
            Daftar();
            break;
        case '2':
            Login();
            break;
        case '3':
            Saldo();
            break;
        case '4':
            Setor();
            break;
        case '5':
            Tarik();
            break;
        case '6':
            Transfer();
            break;
        case '7':
            Logout();
            break;
        default:
            cout << bg::Red.Wrap(" [ OPSI YANG ANDA PILIH TIDAK TERSEDIA ] ") << endl;
            Start();
        }
    }

private:
    void Daftar()
    {
        string namaDaftar;
        string passworddaftar;
        int saldoAwal;

        if (!isLoginUser.Nama.empty())
        {
            cout << bg::Red.Wrap(" [ Anda Sudah Login, Silahkan logout Terlebih Dahulu ] ") << endl;
            Start();
        }
        else if (isLoginUser.Nama.empty())
        {
            cout << bg::Blue.Wrap(" << SILAHKAN MASUKAN DETAIL ANDA >> ") << endl;
            cout << "Masukan Nama Anda : ";
            cin >> namaDaftar;
            cout << "Masukan Password : ";
            cin >> passworddaftar;
            cout << "Masukan Saldo Pertama Anda : ";
            cin >> saldoAwal;

            if (user.size() != 0)
            {
                auto it = find_if(user.begin(), user.end(), [namaDaftar](const User &isUser)
                                  { return isUser.Nama == namaDaftar; });

                if (it != user.end())
                {
                    cout << bg::Red.Wrap(" [ Pendaftaran Gagal, Nama Tersebut Sudah Ada, Silahkan Daftar Ulang ] ") << endl;
                    Daftar();
                }
            }

            if (saldoAwal < 100000)
            {
                cout << bg::Red.Wrap(" [ Pendaftaran Gagal, Saldo Tidak Mencukupi, Silahkan Daftar Ulang ] ") << endl;
                Daftar();
            }
            else
            {
                User theUser = {
                    namaDaftar, passworddaftar, saldoAwal};
                user.push_back(theUser);

                cout << bg::Green.Wrap(" [ Pendaftaran Berhasil ] ") << endl;
                cout << "Nama : " << theUser.Nama << endl;
                cout << "Password : " << theUser.Password << endl;
                cout << "Saldo Anda : " << theUser.Saldo << endl;

                Start();
            }
        }
    }
    void Login()
    {
        if (!isLoginUser.Nama.empty())
        {
            cout << bg::Red.Wrap(" [ Anda Sudah Login, Silahkan logout Terlebih Dahulu ] ") << endl;
            Start();
        }
        else if (user.size() == 0)
        {
            cout << bg::Red.Wrap(" [ User Masih Kosong Silahkan Daftar Terlebih Dahulu ] ") << endl;
            Daftar();
        }
        else if (user.size() > 0)
        {
            string namaLogin;
            string passwordLogin;

            cout << bg::Blue.Wrap(" << SILAHKAN MASUKAN NAMA DAN PASSWORD ANDA >> ") << endl;
            cout << "Masukan Nama Anda : ";
            cin >> namaLogin;
            cout << "Masukan Password Anda : ";
            cin >> passwordLogin;

            auto it = find_if(user.begin(), user.end(), [namaLogin](const User &isUser)
                              { return isUser.Nama == namaLogin; });
            if ((it != user.end()) && (it->Nama == namaLogin) && (it->Password == passwordLogin))
            {
                cout << bg::Green.Wrap(" [ Login Berhasil ] ") << endl;
                isLoginUser = {
                    Nama : namaLogin,
                    Password : passwordLogin
                };
                Start();
            }
            else
            {
                cout << bg::Red.Wrap(" [ Login Gagal Password atau Nama Salah, Silahkan Login Ulang ] ") << endl;
                Login();
            }
        }
    }
    void Saldo()
    {
        if (user.size() == 0)
        {
            cout << bg::Red.Wrap(" [ User Masih Kosong Silahkan Daftar Terlebih Dahulu ] ") << endl;
            Daftar();
        }
        else if (isLoginUser.Nama.empty())
        {
            cout << bg::Red.Wrap(" [ Anda Belum Login, Silahkan Login Terlebih Dahulu ] ") << endl;
            Login();
        }
        else
        {
            string password;

            cout << bg::Blue.Wrap(" << MASUKAN PASSWORD UNTUK MENGECEK SALDO >> ") << endl;
            cout << "Password : ";
            cin >> password;
            if (password != isLoginUser.Password)
            {
                cout << bg::Red.Wrap(" [ Password Salah, Silahkan Ulangi ] ") << endl;
                Saldo();
            }
            else
            {
                for (auto &a : user)
                {
                    if (isLoginUser.Nama == a.Nama)
                    {
                        cout << "Saldo Anda Adalah : " << a.Saldo << endl;
                        Start();
                    }
                }
            }
        }
    }

    void Setor()
    {
        if (user.size() == 0)
        {
            cout << bg::Red.Wrap(" [ User Masih Kosong Silahkan Daftar Terlebih Dahulu ] ") << endl;
            Daftar();
        }
        else if (isLoginUser.Nama.empty())
        {
            cout << bg::Red.Wrap(" [ Anda Belum Login, Silahkan Login Terlebih Dahulu ] ") << endl;
            Login();
        }
        else
        {
            int jmlSaldo;
            string password;

            cout << bg::Blue.Wrap(" << SETOR TUNAI >> ") << endl;
            cout << "Masukan Jumlah Saldo Yang Ingin Anda Setorkan : ";
            cin >> jmlSaldo;
            cout << "Masukan Password Anda : ";
            cin >> password;

            if (jmlSaldo < 1000)
            {
                cout << bg::Red.Wrap(" [ Minimal Saldo Rp. 1.000 ] ") << endl;
                Setor();
            }
            else if (password != isLoginUser.Password)
            {
                cout << bg::Red.Wrap(" [ Password Yang Anda Masukan Salah ] ") << endl;
                Setor();
            }
            else
            {
                for (auto &a : user)
                {
                    if (isLoginUser.Nama == a.Nama)
                    {
                        a.Saldo += jmlSaldo;
                        cout << bg::Green.Wrap(" [ Saldo Berhasil Disetorkan, Silahkan Cek Saldo Untuk Mengeceknya ] ") << endl;
                        Saldo();
                    }
                }
            }
        }
    }

    void Tarik()
    {
        if (user.size() == 0)
        {
            cout << bg::Red.Wrap(" [ User Masih Kosong Silahkan Daftar Terlebih Dahulu ] ") << endl;
            Daftar();
        }
        else if (isLoginUser.Nama.empty())
        {
            cout << bg::Red.Wrap(" [ Anda Belum Login, Silahkan Login Terlebih Dahulu ] ") << endl;
            Login();
        }
        else
        {
            int jmlSaldo;
            string password;

            cout << bg::Blue.Wrap(" << TARIK TUNAI >> ") << endl;
            cout << "Masukan Jumlah Saldo Yang Ingin Anda Tarik : ";
            cin >> jmlSaldo;
            cout << "Masukan Password Anda : ";
            cin >> password;

            if (password != isLoginUser.Password)
            {
                cout << bg::Red.Wrap(" [ Password Yang Anda Masukan Salah ] ") << endl;
                Setor();
            }
            else
            {
                for (auto &a : user)
                {
                    if (isLoginUser.Nama == a.Nama)
                    {
                        if (a.Saldo < jmlSaldo)
                        {
                            cout << bg::Red.Wrap(" [ Saldo Anda Tidak Mencukupi Untuk Melakukan Tarik Tunai ] ") << endl;
                            Setor();
                        }
                        else
                        {
                            a.Saldo -= jmlSaldo;
                            cout << bg::Green.Wrap(" [ Saldo Berhasil Ditarik, Silahkan Cek Saldo Untuk Mengeceknya ] ") << endl;
                            Saldo();
                        }
                    }
                }
            }
        }
    }

    void Transfer()
    {
        if (user.size() == 0)
        {
            cout << bg::Red.Wrap(" [ User Masih Kosong Silahkan Daftar Terlebih Dahulu ] ") << endl;
            Daftar();
        }
        else if (isLoginUser.Nama.empty())
        {
            cout << bg::Red.Wrap(" [ Anda Belum Login, Silahkan Login Terlebih Dahulu ] ") << endl;
            Login();
        }
        else
        {
            int jmlSaldo;
            string namaTujuan;
            string password;

            cout << bg::Blue.Wrap(" << TRANSFER >> ") << endl;
            cout << "Masukan Nama Tujuan Tansfer : ";
            cin >> namaTujuan;
            cout << "Masukan Jumlah Saldo yang ingin Anda Transfer : ";
            cin >> jmlSaldo;
            cout << "Masukan Password Anda : ";
            cin >> password;

            if (password != isLoginUser.Password)
            {
                cout << bg::Red.Wrap(" [ Password Yang Anda Masukan Salah ] ") << endl;
                Setor();
            }
            else if (namaTujuan == isLoginUser.Nama)
            {
                cout << bg::Red.Wrap(" [ Anda Tidak Bisa Transfer Ke diri sendiri ] ") << endl;
                Setor();
            }
            else
            {

                auto it = find_if(user.begin(), user.end(), [namaTujuan](const User &isUser)
                                  { return isUser.Nama == namaTujuan; });

                if (it != user.end())
                {

                    for (auto &a : user)
                    {
                        if (isLoginUser.Nama == a.Nama)
                        {
                            if (jmlSaldo < a.Saldo)
                            {
                                it->Saldo += jmlSaldo;
                                a.Saldo -= jmlSaldo;
                                cout << bg::Green.Wrap(" [ Transfer Berhasil, Silahkan Cek Sisa Saldo Anda ] ") << endl;
                                Saldo();
                            }
                            else
                            {
                                cout << bg::Red.Wrap(" [ Saldo Anda Tidak Mencukupi Untuk Transfer, Silahkan setor tunai dahulu ] ") << endl;
                                Setor();
                            }
                        }
                    }
                }
                else
                {
                    cout << bg::Red.Wrap(" [ Nama tujuan tidak Ditemukan ] ") << endl;
                    Transfer();
                }
            }
        }
    }

    void Logout()
    {
        if (user.size() == 0)
        {
            cout << bg::Red.Wrap(" [ User Masih Kosong Silahkan Daftar Terlebih Dahulu ] ") << endl;
            Daftar();
        }
        else if (isLoginUser.Nama.empty())
        {
            cout << bg::Red.Wrap(" [ Anda Sedang Tidak Login ] ") << endl;
            Login();
        }
        else
        {
            isLoginUser = {};
            cout << bg::Green.Wrap(" [ Logout Berhasil ] ") << endl;
            Login();
        }
    }
};

int main()
{
    ATM atm;
    atm.Start();
    return 0;
}