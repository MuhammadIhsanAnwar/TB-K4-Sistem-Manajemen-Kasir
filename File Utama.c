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
    {
        printf("%-5d %-20s Rp %-10d %-10d\n",
               products[i].id,
               products[i].nama,
               products[i].harga,
               products[i].stok);
    }

    printf("%s-------------------------------------------------------%s\n",
           BLUE, RESET);
}

// ===== EDIT PRODUK =====
void tambahProduk()
{
    while (1)
    {
        int pilih;
        
        // Judul utama: tebal + underline + magenta
        printf("\n%s%s%s=== MENU EDIT PRODUK ===%s\n",
               BOLD, UNDERLINE, MAGENTA, RESET);
        printf("1. Tambah Produk Baru\n");
        printf("2. Edit Produk\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        if (pilih == 3)
            return;

        // ===== TAMBAH PRODUK BARU =====
        if (pilih == 1)
        {
            struct Product p;

            if (jumlahProduk == 0)
                p.id = 1;
            else
                p.id = products[jumlahProduk - 1].id + 1;

            printf("\nID produk otomatis: %d\n", p.id);

            printf("Nama produk (0 untuk batal): ");
            scanf(" %[^\n]", p.nama);
            if (strcmp(p.nama, "0") == 0)
            {
                printf("%sTambah produk dibatalkan.%s\n", RED, RESET);
                continue;
            }

            printf("Harga produk (0 untuk batal): ");
            scanf("%d", &p.harga);
            if (p.harga == 0)
            {
                printf("%sTambah produk dibatalkan.%s\n", RED, RESET);
                continue;
            }

            printf("Jumlah stok awal (0 untuk batal): ");
            scanf("%d", &p.stok);
            if (p.stok == 0)
            {
                printf("%sTambah produk dibatalkan.%s\n", RED, RESET);
                continue;
            }

            products[jumlahProduk] = p;
            jumlahProduk++;

            simpanProduk();
            printf("\n%sProduk baru berhasil ditambahkan!%s\n", GREEN, RESET);
        }

        // ===== EDIT PRODUK =====
        else if (pilih == 2)
        {
            while (1)
            {
                tampilkanProduk();

                int id;
                printf("\nMasukkan ID produk yang ingin diedit (0 untuk batal): ");
                scanf("%d", &id);

                if (id == 0)
                {
                    printf("%sEdit produk dibatalkan. Kembali ke menu tambah/update.%s\n",
                           RED, RESET);
                    break;
                }

                int idx = cariProdukById(id);
                if (idx == -1)
                {
                    printf("%sProduk tidak ditemukan!%s\n", RED, RESET);
                    continue;
                }

                while (1)
                {
                    // Judul edit: tebal + underline + magenta
                    printf("\n%s%s%s=== EDIT PRODUK (ID %d - %s) ===%s\n",
                           BOLD, UNDERLINE, MAGENTA, products[idx].id, products[idx].nama, RESET);
                    printf("1. Edit Nama Produk\n");
                    printf("2. Edit Harga Produk\n");
                    printf("3. Ubah Stok (Replace)\n");
                    printf("4. Tambah Stok (+)\n");
                    printf("5. Selesai Mengedit Produk Ini\n");
                    printf("Pilih: ");

                    int pl;
                    scanf("%d", &pl);

                    if (pl == 1)
                    {
                        char namaBaru[50];
                        printf("Nama baru (0 untuk batal): ");
                        scanf(" %[^\n]", namaBaru);
                        if (strcmp(namaBaru, "0") == 0)
                        {
                            printf("%sEdit nama dibatalkan.%s\n", RED, RESET);
                            continue;
                        }
                        strcpy(products[idx].nama, namaBaru);
                        simpanProduk();
                        printf("%sNama berhasil diperbarui!%s\n", GREEN, RESET);
                    }
                    else if (pl == 2)
                    {
                        int hargaBaru;
                        printf("Harga baru (0 untuk batal): ");
                        scanf("%d", &hargaBaru);
                        if (hargaBaru == 0)
                        {
                            printf("%sEdit harga dibatalkan.%s\n", RED, RESET);
                            continue;
                        }
                        products[idx].harga = hargaBaru;
                        simpanProduk();
                        printf("%sHarga berhasil diperbarui!%s\n", GREEN, RESET);
                    }
                    else if (pl == 3)
                    {
                        int stokBaru;
                        printf("Stok baru (0 untuk batal): ");
                        scanf("%d", &stokBaru);
                        if (stokBaru == 0)
                        {
                            printf("%sEdit stok dibatalkan.%s\n", RED, RESET);
                            continue;
                        }
                        products[idx].stok = stokBaru;
                        simpanProduk();
                        printf("%sStok berhasil diganti!%s\n", GREEN, RESET);
                    }
                    else if (pl == 4)
                    {
                        int tambah;
                        printf("Tambah stok (0 untuk batal): ");
                        scanf("%d", &tambah);
                        if (tambah == 0)
                        {
                            printf("%sPenambahan stok dibatalkan.%s\n", RED, RESET);
                            continue;
                        }
                        products[idx].stok += tambah;
                        simpanProduk();
                        printf("%sStok berhasil ditambah!%s\n", GREEN, RESET);
                    }
                    else if (pl == 5)
                    {
                        printf("Selesai mengedit produk. Kembali memilih produk lain.\n");
                        break;
                    }
                    else
                    {
                        printf("%sPilihan tidak valid!%s\n", RED, RESET);
                    }
                }
            }
        }

        else
        {
            printf("%sPilihan tidak valid!%s\n", RED, RESET);
        }
    }
}
// ===== HAPUS PRODUK =====
void hapusProduk()
{
    int id;
    printf("\nMasukkan ID produk yang ingin dihapus: ");
    scanf("%d", &id);

    int idx = cariProdukById(id);
    if (idx == -1)
    {
        printf("%sProduk tidak ditemukan!%s\n", RED, RESET);
        return;
    }

    for (int i = idx; i < jumlahProduk - 1; i++)
    {
        products[i] = products[i + 1];
    }

    jumlahProduk--;
    simpanProduk();
    printf("%sProduk berhasil dihapus!%s\n", GREEN, RESET);
}

// ===== OUTPUT KWITANSI =====
int getNextKwitansiNumber()
{
    int i = 1;
    char filename[50];
    FILE *f;

    while (1)
    {
        sprintf(filename, "kwitansi_%d.txt", i);
        f = fopen(filename, "r");

        if (f == NULL)
        {
            return i;
        }

        fclose(f);
        i++;
    }
}

int getNextLaporanNumber()
{
    int i = 1;
    char filename[50];
    FILE *f;

    while (1)
    {
        sprintf(filename, "laporan_transaksi_%d.txt", i);
        f = fopen(filename, "r");
        if (f == NULL)
        {
            return i;
        }
        fclose(f);
