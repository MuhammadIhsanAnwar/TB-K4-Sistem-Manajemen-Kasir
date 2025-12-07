// Tugas Besar Kelompok 4 - Sistem Manajemen Kasir
// 1. Muhammad Ihsan Anwar - 251402044 
// 2. Nadine Tantiara Hutagaol - 251402050
// 3. Rizky Cristian Fero Sihombing - 251402056
// 4. Juda Benhur Turnip - 251402096
// 5. Salsabila Salwa Rizki - 251402123

// File yang diinput: produk.txt
// Format file produk.txt:
// nomor|nama|harga|stok

// File yang dioutput: kwitansi_1.txt, kwitansi_2.txt, ..., laporan_transaksi_1.txt, laporan_transaksi_2.txt, ...

#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

// ===== WARNA ANSI =====
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"
#define UNDERLINE "\x1b[4m"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define ORANGE  "\x1b[38;5;208m"   

#define BG_RED    "\x1b[41m"
#define BG_GREEN  "\x1b[42m"
#define BG_YELLOW "\x1b[43m"
#define BG_BLUE   "\x1b[44m"

// ===== STRUKTUR DATA =====
struct Product
{
    int id;
    char nama[50];
    int harga;
    int stok;
};

struct ItemTransaksi
{
    int idProduk;
    int qty;
    int subtotal;
};

struct Product products[100];
int jumlahProduk = 0;

// ====== KERANJANG GLOBAL - TIDAK HILANG WALAU KELUAR KE MENU UTAMA ======
struct ItemTransaksi keranjang[50];
int jumlahItem = 0;

// ===== INPUT FILE PRODUK =====
void loadProduk()
{
    FILE *f = fopen("produk.txt", "r");
    if (!f)
        return;

    while (!feof(f))
    {
        fscanf(f, "%d|%49[^|]|%d|%d\n",
               &products[jumlahProduk].id,
               products[jumlahProduk].nama,
               &products[jumlahProduk].harga,
               &products[jumlahProduk].stok);
        jumlahProduk++;
    }
    fclose(f);
}

void simpanProduk()
{
    FILE *f = fopen("produk.txt", "w");
    for (int i = 0; i < jumlahProduk; i++)
    {
        fprintf(f, "%d|%s|%d|%d\n",
                products[i].id,
                products[i].nama,
                products[i].harga,
                products[i].stok);
    }
    fclose(f);
}

// ===== MENCARI PRODUK =====
int cariProdukById(int id)
{
    for (int i = 0; i < jumlahProduk; i++)
    {
        if (products[i].id == id)
            return i;
    }
    return -1;
}

// ===== MENAMPILKAN PRODUK =====
void tampilkanProduk()
{
    printf("\n%s%s%s===================== DAFTAR PRODUK =====================%s\n",
           BOLD, UNDERLINE, MAGENTA, RESET);
    printf("\n");
    printf("%s%-5s %-20s %-10s %-10s%s\n",
           BOLD, "ID", "Nama", "Harga", "Stok", RESET);

    // Garis pemisah: biru lembut
    printf("%s-------------------------------------------------------%s\n",
           BLUE, RESET);

    // Isi tabel: default (atau putih/cyan — di sini pakai WHITE biar konsisten & jelas)
    for (int i = 0; i < jumlahProduk; i++)
    {
        printf("%s%-5d %-20s Rp %-10d %-10d%s\n",
               WHITE,
               products[i].id,
               products[i].nama,
               products[i].harga,
               products[i].stok,
               RESET);
    }

    // Garis akhir
    printf("%s-------------------------------------------------------%s\n",
           BLUE, RESET);
}

void tampilkanSemuaProduk()
{
    printf("\n%s%s%s===================== DAFTAR PRODUK =====================%s\n",
           BOLD, UNDERLINE, MAGENTA, RESET);
    
    printf("\n");  // baris kosong setelah judul

    // Header kolom: tebal putih
    printf("%s%-5s %-20s %-10s %-10s%s\n",
           BOLD, "ID", "Nama", "Harga", "Stok", RESET);

    // Garis pemisah: biru lembut
    printf("%s-------------------------------------------------------%s\n",
           BLUE, RESET);
           
    for (int i = 0; i < jumlahProduk; i++)
