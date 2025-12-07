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

        else
        {
            printf("Pilihan tidak valid!\n");
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
        printf("Produk tidak ditemukan!\n");
        return;
    }

    for (int i = idx; i < jumlahProduk - 1; i++)
    {
        products[i] = products[i + 1];
    }

    jumlahProduk--;
    simpanProduk();
    printf("Produk berhasil dihapus!\n");
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
        i++;
    }
}

void tampilkanKwitansi(struct ItemTransaksi item[], int jumlahItem, int total,
                       int potongan, int totalSetelahDiskon, int bayar, int kembali)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    printf("\n======= KWITANSI PEMBELIAN =======\n");
    printf("Tanggal: %02d-%02d-%04d  %02d:%02d:%02d\n",
           t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
           t->tm_hour, t->tm_min, t->tm_sec);

    for (int i = 0; i < jumlahItem; i++)
    {
        int idx = cariProdukById(item[i].idProduk);
        printf("%-15s x%-3d = Rp %d\n",
               products[idx].nama,
               item[i].qty,
               item[i].subtotal);
    }

    printf("----------------------------------\n");
    printf("TOTAL SEBELUM DISKON : Rp %d\n", total);
    printf("POTONGAN DISKON      : Rp %d\n", potongan);
    printf("TOTAL SETELAH DISKON : Rp %d\n", totalSetelahDiskon);
    printf("BAYAR                : Rp %d\n", bayar);
    printf("KEMBALIAN            : Rp %d\n", kembali);
    printf("==================================\n");
}

void simpanKwitansiFile(struct ItemTransaksi item[], int jumlahItem, int total,
                        int potongan, int totalSetelahDiskon, int bayar, int kembali)
{ 
    int no = getNextKwitansiNumber();

    char filename[50];
    sprintf(filename, "kwitansi_%d.txt", no);

    FILE *f = fopen(filename, "w");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(f, "======= KWITANSI PEMBELIAN =======\n");
    fprintf(f, "Tanggal: %02d-%02d-%04d  %02d:%02d:%02d\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec);

    for (int i = 0; i < jumlahItem; i++)
    {
        int idx = cariProdukById(item[i].idProduk);
        fprintf(f, "%-15s x%-3d = Rp %d\n",
                products[idx].nama,
                item[i].qty,
                item[i].subtotal);
    }

    fprintf(f, "----------------------------------\n");
    fprintf(f, "TOTAL SEBELUM DISKON : Rp %d\n", total);
    fprintf(f, "POTONGAN DISKON      : Rp %d\n", potongan);
    fprintf(f, "TOTAL SETELAH DISKON : Rp %d\n", totalSetelahDiskon);
    fprintf(f, "BAYAR                : Rp %d\n", bayar);
    fprintf(f, "KEMBALIAN            : Rp %d\n", kembali);
    fprintf(f, "==================================\n");

    fclose(f);

    printf("\nFile kwitansi berhasil dibuat: %s\n", filename);
}

// ===== MENU TRANSAKSI =====
void mulaiTransaksi()
{
    int running = 1;

    while (running)
    {
        int pilih;
        printf("\n=== MENU TRANSAKSI ===\n");
        printf("1. Tambah Produk ke Keranjang\n");
        printf("2. Lihat Keranjang\n");
        printf("3. Hapus Item dari Keranjang\n");
        printf("4. Selesai & Bayar\n");
        printf("5. Kembali ke Menu Utama\n");
        printf("6. Lihat Produk\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        if (pilih == 5)
        {
            printf("\nKembali ke menu utama.\n");
            return;
        }

        if (pilih == 6)
        {
            tampilkanSemuaProduk();
            continue;
        }

        if (pilih == 1)
        {
            while (1)
            {
                int id, qty;
                printf("\nMasukkan ID produk (0 untuk selesai): ");
                scanf("%d", &id);

                if (id == 0)
                    break;

                int idx = cariProdukById(id);
                if (idx == -1)
                {
                    printf("Produk tidak ditemukan!\n");
                    continue;
                }

                printf("Masukkan jumlah: ");
                scanf("%d", &qty);

                if (qty > products[idx].stok)
                {
                    printf("Stok tidak cukup!\n");
                    continue;
                }

                products[idx].stok -= qty;

                keranjang[jumlahItem].idProduk = id;
                keranjang[jumlahItem].qty = qty;
                keranjang[jumlahItem].subtotal = products[idx].harga * qty;
                jumlahItem++;

                printf("%s sejumlah %d berhasil ditambahkan ke keranjang.\n",
                       products[idx].nama, qty);
            }
        }

        else if (pilih == 2)
        {
            if (jumlahItem == 0)
            {
                printf("\nKeranjang masih kosong.\n");
            }
            else
            {
                printf("\n=== ISI KERANJANG ===\n");
                for (int i = 0; i < jumlahItem; i++)
                {
                    int idx = cariProdukById(keranjang[i].idProduk);
                    printf("%d. %s x%d = Rp %d\n",
                           i + 1,
                           products[idx].nama,
                           keranjang[i].qty,
                           keranjang[i].subtotal);
                }
            }
        }

        else if (pilih == 3)
        {
            if (jumlahItem == 0)
            {
                printf("\nKeranjang kosong.\n");
                continue;
            }

            int hapus;
            while (1)
            {
                printf("\n=== HAPUS ITEM ===\n");
                printf("0. Batal\n");

                for (int i = 0; i < jumlahItem; i++)
                {
                    int idx = cariProdukById(keranjang[i].idProduk);
                    printf("%d. %s x%d = Rp %d\n",
                           i + 1,
                           products[idx].nama,
                           keranjang[i].qty,
                           keranjang[i].subtotal);
                }

                printf("Pilih item: ");
                scanf("%d", &hapus);

                if (hapus == 0)
                    break;

                if (hapus < 1 || hapus > jumlahItem)
                {
                    printf("Pilihan tidak valid!\n");
                    continue;
                }

                int idxH = hapus - 1;

                int idp = keranjang[idxH].idProduk;
                int idxP = cariProdukById(idp);

                products[idxP].stok += keranjang[idxH].qty;

                for (int i = idxH; i < jumlahItem - 1; i++)
                    keranjang[i] = keranjang[i + 1];

                jumlahItem--;

                printf("Item dihapus.\n");
                break;
            }
        }

        else if (pilih == 4)
        {
            if (jumlahItem == 0)
            {
                printf("Keranjang kosong.\n");
                continue;
            }

            running = 0;
        }

        else
        {
            printf("Pilihan tidak valid!\n");
        }
    }

    int total = 0;
    for (int i = 0; i < jumlahItem; i++)
        total += keranjang[i].subtotal;

    printf("\nTotal belanja: %d\n", total);

    float diskon = 0;
    if (total > 150000)
        diskon = 5;
    else if (total > 100000)
        diskon = 3;
    else if (total > 75000)
        diskon = 2;

    int potongan = (int)(total * (diskon / 100));
    int totalDiskon = total - potongan;

    printf("Diskon %.0f%% -> Potongan: %d\n", diskon, potongan);
    printf("Total setelah diskon: %d\n", totalDiskon);

    int bayar;
    while (1)
    {
        printf("Uang bayar: ");
        scanf("%d", &bayar);

        if (bayar < totalDiskon)
        {
            printf("Uang kurang!\n");
        }
        else
            break;
    }

    int kembali = bayar - totalDiskon;
    printf("Kembalian: %d\n", kembali);

    simpanProduk();

    tampilkanKwitansi(keranjang, jumlahItem, total, potongan,
                      totalDiskon, bayar, kembali);

    simpanKwitansiFile(keranjang, jumlahItem, total, potongan,
                       totalDiskon, bayar, kembali);

    jumlahItem = 0; // RESET KERANJANG SETELAH SELESAI TRANSAKSI
}

// ===== OUTPUT LAPORAN TRANSAKSI =====
void laporanTransaksi()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (!d)
    {
        printf("Gagal membuka folder.\n");
        return;
    }

    int jumlahTransaksi = 0;
    long totalPendapatan = 0;

    // Untuk menyimpan laporan sementara
    struct
    {
        char tanggal[100];
        int totalAkhir;
        char namaFile[50];
    } data[500];

    printf("\n====== LAPORAN TRANSAKSI ======\n");

    while ((dir = readdir(d)) != NULL)
    {
        if (strncmp(dir->d_name, "kwitansi_", 9) == 0)
        {
            FILE *f = fopen(dir->d_name, "r");
            if (!f)
                continue;

            char line[200];
            char tanggal[100] = "-";
            int totalAkhir = 0;

            while (fgets(line, sizeof(line), f))
            {
                if (strncmp(line, "Tanggal:", 8) == 0)
                {
                    strcpy(tanggal, line + 9);
                }
                if (strstr(line, "TOTAL SETELAH DISKON") != NULL)
                {
                    char *ptr = strstr(line, "Rp");
                    if (ptr)
                        sscanf(ptr + 2, "%d", &totalAkhir);
                }
            }

            fclose(f);

            strcpy(data[jumlahTransaksi].tanggal, tanggal);
            data[jumlahTransaksi].totalAkhir = totalAkhir;
            strcpy(data[jumlahTransaksi].namaFile, dir->d_name);

            totalPendapatan += totalAkhir;
            jumlahTransaksi++;
        }
    }
    closedir(d);

    // Tampilkan ke layar
    for (int i = 0; i < jumlahTransaksi; i++)
    {
        printf("%d. File: %s\n", i + 1, data[i].namaFile);
        printf("   Tanggal : %s", data[i].tanggal);
        printf("   Total   : Rp %d\n\n", data[i].totalAkhir);
    }

    printf("JUMLAH TRANSAKSI : %d\n", jumlahTransaksi);
    printf("TOTAL PENDAPATAN : Rp %ld\n", totalPendapatan);
    printf("================================\n");

    // ====== SIMPAN KE FILE LAPORAN OTOMATIS ======
    int no = getNextLaporanNumber();

    char filename[50];
    sprintf(filename, "laporan_transaksi_%d.txt", no);

    FILE *out = fopen(filename, "w");

    fprintf(out, "========== LAPORAN TRANSAKSI ==========\n\n");

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        fprintf(out, "%d. File: %s\n", i + 1, data[i].namaFile);
        fprintf(out, "   Tanggal : %s", data[i].tanggal);
        fprintf(out, "   Total   : Rp %d\n\n", data[i].totalAkhir);
    }

    fprintf(out, "JUMLAH TRANSAKSI : %d\n", jumlahTransaksi);
    fprintf(out, "TOTAL PENDAPATAN : Rp %ld\n", totalPendapatan);
    fprintf(out, "=========================================\n");

    fclose(out);

    printf("\nFile laporan berhasil dibuat: %s\n", filename);
}

// ===== MENU UTAMA =====
void menuUtama()
{
    while (1)
    {
        int pilih;

        printf("\n=== SISTEM KASIR ===\n");
        printf("1. Edit Produk\n");
        printf("2. Lihat Produk\n");
        printf("3. Hapus Produk\n");
        printf("4. Mulai Transaksi\n");
        printf("5. Laporan Transaksi\n");
        printf("6. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih)
        {
        case 1:
            tambahProduk();
            break;
        case 2:
            tampilkanProduk();
            break;
        case 3:
            hapusProduk();
            break;
        case 4:
            mulaiTransaksi();
            break;
        case 5:
            laporanTransaksi();
            break;
        case 6:
            return;
        default:
            printf("Pilihan tidak valid!\n");
        }
    }
}

int main()
{
    loadProduk();
    menuUtama();
    return 0;
}
