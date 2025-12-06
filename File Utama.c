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
    printf("\n===== DAFTAR PRODUK =====\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Nama", "Harga", "Stok");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < jumlahProduk; i++)
    {
        printf("%-5d %-20s Rp %-10d %-10d\n",
               products[i].id,
               products[i].nama,
               products[i].harga,
               products[i].stok);
    }

    printf("-------------------------------------------------------\n");
}

void tampilkanSemuaProduk()
{
    printf("\n===== DAFTAR PRODUK =====\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Nama", "Harga", "Stok");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < jumlahProduk; i++)
    {
        printf("%-5d %-20s Rp %-10d %-10d\n",
               products[i].id,
               products[i].nama,
               products[i].harga,
               products[i].stok);
    }

    printf("-------------------------------------------------------\n");
}

// ===== EDIT PRODUK =====
void tambahProduk()
{
    while (1)
    {
        int pilih;
        printf("\n=== MENU EDIT PRODUK ===\n");
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
                printf("Tambah produk dibatalkan.\n");
                continue;
            }

            printf("Harga produk (0 untuk batal): ");
            scanf("%d", &p.harga);
            if (p.harga == 0)
            {
                printf("Tambah produk dibatalkan.\n");
                continue;
            }

            printf("Jumlah stok awal (0 untuk batal): ");
            scanf("%d", &p.stok);
            if (p.stok == 0)
            {
                printf("Tambah produk dibatalkan.\n");
                continue;
            }

            products[jumlahProduk] = p;
            jumlahProduk++;

            simpanProduk();
            printf("\nProduk baru berhasil ditambahkan!\n");
        }

        // ===== EDIT PRODUK =====
        else if (pilih == 2)
        {
            while (1) // LOOP UTAMA PEMILIHAN ID PRODUK
            {
                tampilkanProduk();

                int id;
                printf("\nMasukkan ID produk yang ingin diedit (0 untuk batal): ");
                scanf("%d", &id);

                if (id == 0)
                {
                    printf("Edit produk dibatalkan. Kembali ke menu tambah/update.\n");
                    break; // kembali ke menu tambah/update produk
                }

                int idx = cariProdukById(id);
                if (idx == -1)
                {
                    printf("Produk tidak ditemukan!\n");
                    continue;
                }

                while (1) // MENU EDIT DETAIL PRODUK
                {
                    printf("\n=== EDIT PRODUK (ID %d - %s) ===\n", products[idx].id, products[idx].nama);
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
                            printf("Edit nama dibatalkan.\n");
                            continue;
                        }
                        strcpy(products[idx].nama, namaBaru);
                        simpanProduk();
                        printf("Nama berhasil diperbarui!\n");
                    }
                    else if (pl == 2)
                    {
                        int hargaBaru;
                        printf("Harga baru (0 untuk batal): ");
                        scanf("%d", &hargaBaru);
                        if (hargaBaru == 0)
                        {
                            printf("Edit harga dibatalkan.\n");
                            continue;
                        }
                        products[idx].harga = hargaBaru;
                        simpanProduk();
                        printf("Harga berhasil diperbarui!\n");
                    }
                    else if (pl == 3)
                    {
                        int stokBaru;
                        printf("Stok baru (0 untuk batal): ");
                        scanf("%d", &stokBaru);
                        if (stokBaru == 0)
                        {
                            printf("Edit stok dibatalkan.\n");
                            continue;
                        }
                        products[idx].stok = stokBaru;
                        simpanProduk();
                        printf("Stok berhasil diganti!\n");
                    }
                    else if (pl == 4)
                    {
                        int tambah;
                        printf("Tambah stok (0 untuk batal): ");
                        scanf("%d", &tambah);
                        if (tambah == 0)
                        {
                            printf("Penambahan stok dibatalkan.\n");
                            continue;
                        }
                        products[idx].stok += tambah;
                        simpanProduk();
                        printf("Stok berhasil ditambah!\n");
                    }
                    else if (pl == 5)
                    {
                        printf("Selesai mengedit produk. Kembali memilih produk lain.\n");
                        break; // kembali ke pemilihan ID
                    }
                    else
                    {
                        printf("Pilihan tidak valid!\n");
                    }
                }
            }
        }
