#include<stdio.h>
#include<string.h>
#include <stdbool.h>

#define MAX_SISWA 100
#define MAX_USERS 50

typedef struct {
    char nama[50];
    int nis;
    float nilai;
    char parameter[3];
} siswa;

typedef struct {
    char username[20];
    char password[20];
} user;

siswa dataSiswa[MAX_SISWA];
user users[MAX_USERS];

int jumlahSiswa = 0;
int userCount = 0;
bool isLoggedIn = false; // Variabel global untuk status login

void signIn();
void login();
void logout();
void tambahData();
void hapusData();
void lihatData();
void cariData();
void urutkanData();
void hitungRataRata();
void SimpanDatakedalamFile();
void BacaDataDariFile();
void hitungParameter(float nilai, char *parameter);
void menu();

void menu() {
    printf("+-------------------------------+\n");
    printf("| Program Penilaian Data Siswa  |\n");
    printf("|_______________________________|\n");
    printf("|                               |\n");
    printf("|             Menu              |\n");
    printf("+-------------------------------+\n");
    printf("|1. Tambah Data Siswa           |\n");
    printf("|2. Hapus Data Siswa            |\n");
    printf("|3. Lihat Data Siswa            |\n");
    printf("|4. Cari Data Siswa             |\n");
    printf("|5. Urutkan Data Nilai Siswa    |\n");
    printf("|6. Hitung Rata-Rata Nilai      |\n");
    printf("|7. Simpan Data ke dalam File   |\n");
    printf("|8. Baca Data Dari File         |\n");
    printf("|9. Log Out                     |\n");
    printf("|10. Keluar                     |\n");
    printf("+-------------------------------+\n");
}

void hitungParameter(float nilai, char *parameter) {
    if (nilai >= 85) strcpy(parameter, "A");
    else if (nilai >= 80) strcpy(parameter, "A-");
    else if (nilai >= 75) strcpy(parameter, "B+");
    else if (nilai >= 70) strcpy(parameter, "B");
    else if (nilai >= 65) strcpy(parameter, "B-");
    else if (nilai >= 60) strcpy(parameter, "C");
    else if (nilai >= 50) strcpy(parameter, "D");
    else strcpy(parameter, "E");
}

void tambahData() {
    if (jumlahSiswa < MAX_SISWA) {
        printf("Masukkan Nama\t\t\t: ");
        scanf(" %[^\n]", dataSiswa[jumlahSiswa].nama);
        printf("Masukkan NIS\t\t\t: ");
        scanf("%d", &dataSiswa[jumlahSiswa].nis);
        printf("Masukkan Nilai\t\t\t: ");
        scanf("%f", &dataSiswa[jumlahSiswa].nilai);
        hitungParameter(dataSiswa[jumlahSiswa].nilai, dataSiswa[jumlahSiswa].parameter);
        jumlahSiswa++;
        printf("Data berhasil ditambahkan!\n");
    } else {
        printf("Data penuh!\n");
    }
}

void signIn() {
    if (userCount >= MAX_USERS) {
        printf("Maksimum jumlah pengguna tercapai!\n");
        return;
    }

    char username[20], password[20];
    int usernameExists = 0;

    printf("Masukkan username baru\t\t: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            usernameExists = 1;
            break;
        }
    }

    if (usernameExists) {
        printf("Username sudah digunakan, coba lagi dengan username yang berbeda.\n");
        return;
    }

    printf("Masukkan password baru\t\t: ");
    scanf("%s", password);

    // Tambahkan pengguna baru
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    printf("Sign In berhasil! Anda sekarang bisa login.\n");
}

void login() {
    system("cls || clear");
    char username[20], password[20];
    int found = 0;

    printf("Masukkan username\t\t: ");
    scanf("%s", username);
    printf("Masukkan password\t\t: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            found = 1;
            isLoggedIn = true; 
            printf("Login berhasil! Selamat datang, %s.\n", username);
            return;
        }
    }

    if (!found) {
        printf("Username atau password salah, coba lagi.\n");
    }
}

void hapusData() {
    int nis, i, j, found = 0;
    printf("Masukkan NIS yang ingin dihapus\t: ");
    scanf("%d", &nis);

    for (i = 0; i < jumlahSiswa; i++) {
        if (dataSiswa[i].nis == nis) {
            found = 1;
            for (j = i; j < jumlahSiswa - 1; j++) {
                dataSiswa[j] = dataSiswa[j + 1];
            }
            jumlahSiswa--;
            printf("Data berhasil dihapus!\n");
            break;
        }
    }
    if (!found) printf("Data tidak ditemukan!\n");
}

void lihatData() {
        printf("\n================================================== Data Siswa ===============================================\n");
    printf("No\t\t\tNama\t\t\tNIS\t\t\tNilai\t\t\tParameter\n");
    printf("+------------------------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < jumlahSiswa; i++) {
        printf("%d\t\t\t%s\t\t\t%d\t\t\t%.2f\t\t\t%s\n", i + 1, dataSiswa[i].nama, dataSiswa[i].nis, dataSiswa[i].nilai, dataSiswa[i].parameter);
    }
}

void cariData() {
        int nis, found = 0;
    printf("Masukkan NIS yang dicari\t: ");
    scanf("%d", &nis);

    for (int i = 0; i < jumlahSiswa; i++) {
        if (dataSiswa[i].nis == nis) {
            printf("Data ditemukan:\n");
            printf("Nama\t\t\t: %s\nNIS\t\t\t: %d\nNilai\t\t\t: %.2f\nParameter\t\t: %s\n", dataSiswa[i].nama, dataSiswa[i].nis, dataSiswa[i].nilai, dataSiswa[i].parameter);
            found = 1;
            break;
        }
    }
    if (!found) printf("Data tidak ditemukan!\n");
}

void urutkanData() {
    siswa temp;
    for (int i = 0; i < jumlahSiswa - 1; i++) {
        for (int j = 0; j < jumlahSiswa - i - 1; j++) {
            if (dataSiswa[j].nilai < dataSiswa[j + 1].nilai) {
                temp = dataSiswa[j];
                dataSiswa[j] = dataSiswa[j + 1];
                dataSiswa[j + 1] = temp;
            }
        }
    }
    printf("Data berhasil diurutkan dari nilai tertinggi ke terendah.\n");
}

void hitungRataRata() {
       float total = 0.0;
    for (int i = 0; i < jumlahSiswa; i++) {
        total += dataSiswa[i].nilai;
    }
    float rataRata = total / jumlahSiswa;
    printf("Rata-rata nilai\t\t\t: %.2f\n", rataRata);
}

void SimpanDatakedalamFile() {
     char namaFile[50];
    FILE *file;

    if (jumlahSiswa == 0) {
        printf("Tidak ada data yang bisa disimpan!\n");
        return;
    }

    printf("Masukkan nama file (.txt)\t: ");
    scanf(" %[^\n]", namaFile);

    file = fopen(namaFile, "w");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(file, "===== Data Mahasiswa =====\n");
    fprintf(file, "No\tNama\t\tNIM\tNilai\tGrade\n");

    for (int i = 0; i < jumlahSiswa; i++) {
        fprintf(file, "%d\t%s\t%d\t%.2f\t%s\n", i + 1,
                dataSiswa[i].nama,
                dataSiswa[i].nis,
                dataSiswa[i].nilai,
                dataSiswa[i].parameter);
    }

    fclose(file);
    printf("Data berhasil disimpan ke file: %s\n", namaFile);
}

void BacaDataDariFile() {
    char namaFile[50];
    printf("Masukkan nama file yang ingin dibaca (contoh: data_siswa.txt): ");
    scanf(" %[^\n]", namaFile);

    FILE *file = fopen(namaFile, "r");
    if (!file) {
        printf("File '%s' tidak ditemukan atau gagal dibuka!\n", namaFile);
        return;
    }

    jumlahSiswa = 0;
    while (!feof(file)) {
        char nama[50];
        int nis;
        float nilai;
        char parameter[5];

        int hasil = fscanf(file, "%s %d %f %s", nama, &nis, &nilai, parameter);

        if (hasil == 4 && nis > 0 && nilai > 0) {
            strcpy(dataSiswa[jumlahSiswa].nama, nama);
            dataSiswa[jumlahSiswa].nis = nis;
            dataSiswa[jumlahSiswa].nilai = nilai;
            strcpy(dataSiswa[jumlahSiswa].parameter, parameter);
            jumlahSiswa++;
        }
    }

    fclose(file);
    printf("Data siswa berhasil diimpor. Jumlah data: %d\n", jumlahSiswa);
}

void logout() {
    system("cls || clear");
    if (isLoggedIn) { 
        isLoggedIn = false; 
        printf("Logout berhasil! Anda telah keluar dari sistem.\n");
    } else {
        printf("Anda belum login.\n");
    }
}

int main() {
    printf("\n    *    *  SELAMAT DATANG PADA PROGRAM  *   *\n");
    printf("\n *      *      *     CLASSSCORE     *      *   *\n");
    int pilihan;

    do {
        if (!isLoggedIn) { // Jika belum login
            printf("\n=== SILAKAN SIGN IN & LOG IN TERLEBIH DAHULU ===\n");
            printf("1. Sign In\n");
            printf("2. Login\n");
            printf("3. Keluar\n");
            printf("Pilih menu\t\t\t: ");
            scanf("%d", &pilihan);

            switch (pilihan) {
                case 1: signIn(); break;
                case 2: login(); break;
                case 3: printf("Keluar dari program.\n"); return 0;
                default: printf("Pilihan tidak valid!\n");
            }
        } else {
            menu();
            printf("\nPilih menu\t\t\t: ");
            scanf("%d", &pilihan);

            switch (pilihan) {
                case 1: tambahData(); break;
                case 2: hapusData(); break;
                case 3: lihatData(); break;
                case 4: cariData(); break;
                case 5: urutkanData(); break;
                case 6: hitungRataRata(); break;
                case 7: SimpanDatakedalamFile(); break;
                case 8: BacaDataDariFile(); break;
                case 9: logout();break;
                case 10: printf("Keluar dari program.\n"); return 0;
                default: printf("Pilihan tidak valid!\n");
            }
        }
    } while (pilihan != 10);
    return 0;
}
