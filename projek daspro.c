#include<stdio.h>
#include<string.h>

#define MAX_SISWA 100

typedef struct {
    char nama[50];
    int nis;
    float nilai;
    char parameter[3];
} siswa;

siswa dataSiswa[MAX_SISWA];
int jumlahSiswa = 0;

void tambahData();
void hapusData();
void lihatData();
void cariData();
void urutkanData();
void hitungRataRata();
void SimpanDatakedalamFile();
void hitungParameter(float nilai, char *parameter);
void menu();

int main() {
    int pilihan;
    do {
        menu();
        printf("\nPilih menu: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1: tambahData(); break;
            case 2: hapusData(); break;
            case 3: lihatData(); break;
            case 4: cariData(); break;
            case 5: urutkanData(); break;
            case 6: hitungRataRata(); break;
            case 7: SimpanDatakedalamFile(); break;
            case 8: printf("Keluar dari program.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 8);
    return 0;
}

void menu() {
    printf("\n====== ClassScore Program ======\n");
    printf("+-------------------------------+\n");
    printf("|             Menu              |\n");
    printf("+-------------------------------+\n");
    printf("|1. Tambah Data Siswa           |\n");
    printf("|2. Hapus Data Siswa            |\n");
    printf("|3. Lihat Data Siswa            |\n");
    printf("|4. Cari Data Siswa             |\n");
    printf("|5. Urutkan Data Nilai Siswa    |\n");
    printf("|6. Hitung Rata-rata Nilai      |\n");
    printf("|7. Simpan Data ke dalam File   |\n");
    printf("|8. Keluar                      |\n");
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
        printf("Masukkan Nama: ");
        scanf(" %[^\n]", dataSiswa[jumlahSiswa].nama);
        printf("Masukkan NIS: ");
        scanf("%d", &dataSiswa[jumlahSiswa].nis);
        printf("Masukkan Nilai: ");
        scanf("%f", &dataSiswa[jumlahSiswa].nilai);
        hitungParameter(dataSiswa[jumlahSiswa].nilai, dataSiswa[jumlahSiswa].parameter);
        jumlahSiswa++;
        printf("Data berhasil ditambahkan!\n");
    } else {
        printf("Data penuh!\n");
    }
}

void hapusData() {
    int nis, i, j, found = 0;
    printf("Masukkan NIS yang ingin dihapus: ");
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
    printf("Masukkan NIS yang dicari: ");
    scanf("%d", &nis);

    for (int i = 0; i < jumlahSiswa; i++) {
        if (dataSiswa[i].nis == nis) {
            printf("Data ditemukan:\n");
            printf("Nama: %s\nNIS: %d\nNilai: %.2f\nParameter: %c\n", dataSiswa[i].nama, dataSiswa[i].nis, dataSiswa[i].nilai, dataSiswa[i].parameter);
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

// Fungsi menghitung rata-rata nilai
void hitungRataRata() {
    float total = 0.0;
    for (int i = 0; i < jumlahSiswa; i++) {
        total += dataSiswa[i].nilai;
    }
    float rataRata = total / jumlahSiswa;
    printf("Rata-rata nilai: %.2f\n", rataRata);
}

// Fungsi menyimpan data mahasiswa ke file
void SimpanDatakedalamFile() {
    char namaFile[50];
    FILE *file;

    if (jumlahSiswa == 0) {
        printf("Tidak ada data yang bisa disimpan!\n");
        return;
    }

    printf("Masukkan nama file untuk menyimpan data (contoh: data_mahasiswa.txt): ");
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
