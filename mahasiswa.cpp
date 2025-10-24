#include <iostream>
#include <fstream>
using namespace std;

struct Mahasiswa {
    string nama;
    string NISN;
    int umur;
    string jurusan;
    int hari, bulan, tahun;
};


struct NilaiMapel {
    float Matematika, IPA, BIn, BIng;
};


struct NilaiUjian {
    float uts, uas, tugas;
};


struct DataMahasiswa {
    Mahasiswa mhs;
    NilaiMapel mapel;
    NilaiUjian ujian;
    float akhirMapel;
    float rataUjian;
};


void tambahData();
void tampilData();
void cariSiswa();
float hitungNilaiAkhirMapel(NilaiMapel n);
float hitungRataUjian(NilaiUjian n);
void ranking();

int splitManual(string line, char delim, string arr[], int maxSize) {
    int idx = 0;
    string temp = "";
    for (char c : line) {
        if (c == delim) {
            if (idx < maxSize) {
                arr[idx++] = temp;
                temp = "";
            }
        } else {
            temp += c;
        }
    }
    if (idx < maxSize) arr[idx++] = temp;
    return idx;
}

int main() {
    int pilih;
    do {
        cout << "\n=== MENU DATA MAHASISWA ===\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampil Semua Data\n";
        cout << "3. Cari Mahasiswa (NISN)\n";
        cout << "4. Ranking Mahasiswa\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        switch(pilih) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: cariSiswa(); break;
            case 4: ranking(); break;
            case 5: cout << "Keluar dari program...\n"; break;
            default: cout << "Pilihan tidak ada!\n";
        }
    } while(pilih != 5);

    return 0;
}


float hitungNilaiAkhirMapel(NilaiMapel n) {
    return n.Matematika*0.35 + n.IPA*0.25 + n.BIn*0.2 + n.BIng*0.2;
}


float hitungRataUjian(NilaiUjian n) {
    return (n.uts + n.uas + n.tugas)/3.0;
}


void tambahData() {
    ofstream file("mahasiswa.txt", ios::app);
    DataMahasiswa d;

    cout << "Nama siswa           : "; getline(cin, d.mhs.nama);
    cout << "NISN                 : "; getline(cin, d.mhs.NISN);
    cout << "Umur                 : "; cin >> d.mhs.umur; cin.ignore();
    cout << "Jurusan              : "; getline(cin, d.mhs.jurusan);
    cout << "Tanggal lahir - hari : "; cin >> d.mhs.hari;
    cout << "Tanggal lahir - bulan: "; cin >> d.mhs.bulan;
    cout << "Tanggal lahir - tahun: "; cin >> d.mhs.tahun;

    cout << "Nilai Matematika     : "; cin >> d.mapel.Matematika;
    cout << "Nilai IPA            : "; cin >> d.mapel.IPA;
    cout << "Nilai B. Indonesia   : "; cin >> d.mapel.BIn;
    cout << "Nilai B. Inggris     : "; cin >> d.mapel.BIng;

    cout << "Nilai UTS            : "; cin >> d.ujian.uts;
    cout << "Nilai UAS            : "; cin >> d.ujian.uas;
    cout << "Nilai Tugas          : "; cin >> d.ujian.tugas;
    cin.ignore();

    d.akhirMapel = hitungNilaiAkhirMapel(d.mapel);
    d.rataUjian = hitungRataUjian(d.ujian);

    file << d.mhs.nama << "|" << d.mhs.NISN << "|" << d.mhs.umur << "|" << d.mhs.jurusan << "|"
         << d.mhs.hari << "|" << d.mhs.bulan << "|" << d.mhs.tahun << "|"
         << d.mapel.Matematika << "|" << d.mapel.IPA << "|" << d.mapel.BIn << "|" << d.mapel.BIng << "|"
         << d.ujian.uts << "|" << d.ujian.uas << "|" << d.ujian.tugas << "|"
         << d.akhirMapel << "|" << d.rataUjian << endl;

    file.close();
    cout << "\nData mahasiswa sudah disimpan.\n";
}


void tampilData() {
    ifstream file("mahasiswa.txt");
    string line;
    string data[20];

    cout << "\n=== DATA MAHASISWA ===\n";
    cout << "Nama\tNISN\tUmur\tJurusan\tTTL\tMtk\tIPA\tBIn\tBIng\tUTS\tUAS\tTugas\tAkhirMapel\tRataUjian\n";

    while(getline(file, line)) {
        splitManual(line, '|', data, 20);
        cout << data[0] << "\t" << data[1] << "\t" << data[2] << "\t" << data[3] << "\t"
             << data[4] << "-" << data[5] << "-" << data[6] << "\t"
             << data[7] << "\t" << data[8] << "\t" << data[9] << "\t" << data[10] << "\t"
             << data[11] << "\t" << data[12] << "\t" << data[13] << "\t" << data[14] << "\t" << data[15] << "\n";
    }

    file.close();
}


void cariSiswa() {
    ifstream file("mahasiswa.txt");
    string line, data[20];
    string cari;
    bool ketemu = false;

    cout << "Masukkan NISN: "; getline(cin, cari);

    while(getline(file, line)) {
        splitManual(line, '|', data, 20);
        if(data[1] == cari) {
            cout << "\nData Ditemukan:\n";
            cout << "Nama\tNISN\tUmur\tJurusan\tTTL\tMtk\tIPA\tBIn\tBIng\tUTS\tUAS\tTugas\tAkhirMapel\tRataUjian\n";
            cout << data[0] << "\t" << data[1] << "\t" << data[2] << "\t" << data[3] << "\t"
                 << data[4] << "-" << data[5] << "-" << data[6] << "\t"
                 << data[7] << "\t" << data[8] << "\t" << data[9] << "\t" << data[10] << "\t"
                 << data[11] << "\t" << data[12] << "\t" << data[13] << "\t" << data[14] << "\t" << data[15] << "\n";
            ketemu = true;
            break;
        }
    }

    if(!ketemu) cout << "Data tidak ditemukan.\n";
    file.close();
}


void ranking() {
    ifstream file("mahasiswa.txt");
    string line, data[20];
    DataMahasiswa d[100];
    int i = 0;

    while(getline(file, line)) {
        splitManual(line, '|', data, 20);
        d[i].mhs.nama = data[0];
        d[i].mhs.NISN = data[1];
        d[i].mapel.Matematika = stof(data[7]);
        d[i].mapel.IPA = stof(data[8]);
        d[i].mapel.BIn = stof(data[9]);
        d[i].mapel.BIng = stof(data[10]);
        d[i].ujian.uts = stof(data[11]);
        d[i].ujian.uas = stof(data[12]);
        d[i].ujian.tugas = stof(data[13]);
        d[i].akhirMapel = stof(data[14]);
        d[i].rataUjian = stof(data[15]);
        i++;
    }

    
    for(int a=0; a<i-1; a++) {
        for(int b=a+1; b<i; b++) {
            if(d[b].akhirMapel > d[a].akhirMapel) {
                DataMahasiswa tmp = d[a];
                d[a] = d[b];
                d[b] = tmp;
            }
        }
    }

    
    cout << "\n=== RANKING MAHASISWA LENGKAP ===\n";
    cout << "No\tNama\tNISN\tMtk\tIPA\tBIn\tBIng\tUTS\tUAS\tTugas\tAkhirMapel\tRataUjian\n";
    for(int a=0; a<i; a++) {
        cout << a+1 << "\t" << d[a].mhs.nama << "\t" << d[a].mhs.NISN << "\t"
             << d[a].mapel.Matematika << "\t" << d[a].mapel.IPA << "\t"
             << d[a].mapel.BIn << "\t" << d[a].mapel.BIng << "\t"
             << d[a].ujian.uts << "\t" << d[a].ujian.uas << "\t"
             << d[a].ujian.tugas << "\t" << d[a].akhirMapel << "\t" << d[a].rataUjian << "\n";
    }

    file.close();
    
    
}
