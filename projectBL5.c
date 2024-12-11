#include <stdio.h>
#include <string.h>

#define MAX_KHO 10         // So luong kho nho
#define MAX_ITEMS 1000    // So luong toi da cho trong moi kho

// Cau truc de luu thong tin hang hoa
typedef struct {
    char maSanPham[11];
    char tenSanPham[51];
    char khoiLuong[21];
    int soLuong;
    char ngayNhap[15]; //    date : dd/mm/yyyy
} HangHoa;


// Mang luu danh sach hang hoa trong moi kho nho
HangHoa khoSmall[MAX_KHO][MAX_ITEMS];
int soLuongHangHoa[MAX_KHO] = {0}; // Mang luu so luong hang hoa hien tai trong moi kho nho

// Ham doc du lieu tu cac file kho
void docDuLieuKho() {
	int kho;
    for (kho = 0; kho < MAX_KHO; kho++) {
        char tenFile[20];
        sprintf(tenFile, "kho%d.txt", kho + 1);  // Tao ten file: kho1.txt, kho2.txt,...

        FILE *file = fopen(tenFile, "r");
        if (file == NULL) {
            printf("Khong the mo file %s.\n", tenFile);
            continue;
        }
	int i = 0;
        while (fscanf(file, "%d %10s %50s %20s %d %10s",
              &i,
              khoSmall[kho][i].maSanPham,
              khoSmall[kho][i].tenSanPham,
              khoSmall[kho][i].khoiLuong,
              &khoSmall[kho][i].soLuong,
              khoSmall[kho][i].ngayNhap) != EOF) {
    i++;
    if (i >= MAX_ITEMS) break;
}

        soLuongHangHoa[kho] = i; // Luu so luong hang hoa trong kho
        fclose(file);
    }
}

// Ham tinh tong so cho trong kho nho
int tinhChotTrongKho(int khoIndex) {
    int tongSoLuong = 0;
    int i;
    
    for (i = 0; i < soLuongHangHoa[khoIndex]; i++) {
        tongSoLuong += khoSmall[khoIndex][i].soLuong;
    }
    return MAX_ITEMS - tongSoLuong;
}

// Ham kiem tra tong kho
void kiemTraTongKho() {
    int tongChotTrong = 0;
    int khoTrongNhieuNhat = 0;
    int khoGanHetChot = 0;
    int maxChotTrong = -1;
    int minChotTrong = MAX_ITEMS + 1;
    int i;

    for (i = 0; i < MAX_KHO; i++) {
        int chotTrong = tinhChotTrongKho(i);
        tongChotTrong += chotTrong;

        // Tim kho con trong nhieu nhat
        if (chotTrong > maxChotTrong) {
            maxChotTrong = chotTrong;
            khoTrongNhieuNhat = i;
        }

        // Tim kho gan het cho
        if (chotTrong < minChotTrong) {
            minChotTrong = chotTrong;
            khoGanHetChot = i;
        }
    }

    // Hien thi ket qua
    printf("\n--- Kiem tra tong kho ---\n");
    printf("Tong so cho trong tat ca cac kho: %d\n", tongChotTrong);
    printf("Kho con trong nhieu nhat la kho %d voi %d cho trong.\n", khoTrongNhieuNhat + 1, maxChotTrong);
    printf("Kho gan het cho nhat la kho %d voi %d cho trong.\n", khoGanHetChot + 1, minChotTrong);
}

// Ham tim kiem tren tong kho
void timKiemTrenTongKho() {
    int luaChon;
    printf("\nTim kiem theo:\n");
    printf("1. Ten san pham\n");
    printf("2. Ngay nhap kho\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &luaChon);

    if (luaChon == 1) {
        char tenTimKiem[51];
        printf("\nNhap ten hang hoa can tim: ");
        scanf(" %50[^\n]", tenTimKiem);

        int timThay = 0;
    int i,j;
        for (i = 0; i < MAX_KHO; i++) {
            for (j = 0; j < soLuongHangHoa[i]; j++) {
                if (strcmp(khoSmall[i][j].tenSanPham, tenTimKiem) == 0) {
                    printf("Hang hoa \"%s\" (Ma: %s) co trong kho %d, So luong: %d, Ngay nhap: %s\n", 
                           khoSmall[i][j].tenSanPham, khoSmall[i][j].maSanPham, i + 1, 
                           khoSmall[i][j].soLuong, khoSmall[i][j].ngayNhap);
                    timThay = 1;
                }
            }
        }
        if (!timThay) {
            printf("Khong tim thay hang hoa \"%s\" trong tong kho.\n", tenTimKiem);
        }

    } else if (luaChon == 2) {
        char ngayTimKiem[11];
        printf("\nNhap ngay nhap kho can tim (dd/mm/yyyy): ");
        scanf("%s", ngayTimKiem);

        int timThay = 0;
    int i,j;
        for (i = 0; i < MAX_KHO; i++) {
            for (j = 0; j < soLuongHangHoa[i]; j++) {
                if (strcmp(khoSmall[i][j].ngayNhap, ngayTimKiem) == 0) {
                    printf("Hang hoa \"%s\" (Ma: %s) co trong kho %d, So luong: %d, Ngay nhap: %s\n", 
                           khoSmall[i][j].tenSanPham, khoSmall[i][j].maSanPham, i + 1, 
                           khoSmall[i][j].soLuong, khoSmall[i][j].ngayNhap);
                    timThay = 1;
                }
            }
        }
        if (!timThay) {
            printf("Khong tim thay hang hoa nhap vao ngay \"%s\" trong tong kho.\n", ngayTimKiem);
        }

    } else {
        printf("Lua chon khong hop le.\n");
    }
}

// Menu Tong Kho
void menuTongKho() {
    int choice;
    do {
        printf("\n--- MENU TONG KHO ---\n");
        printf("1. Kiem tra tong kho\n");
        printf("2. Tim kiem tren tong kho\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                kiemTraTongKho();
                break;
            case 2:
                timKiemTrenTongKho();
                break;
            case 0:
                printf("\nQuay lai menu chinh.\n");
                break;
            default:
                printf("\nLua chon khong hop le. Vui long thu lai!\n");
        }
    } while (choice != 0);
}

// Menu Kho Nho
void menuKhoNho() {
    int choice;
    int i;
    
    do {
        printf("\n--- MENU KHO NHO ---\n");
        printf("1. Danh sach kho\n");
        printf("2. Di chuyen toan bo hang sang kho khac\n");
        printf("3. Them hang vao kho\n");
        printf("4. Xuat hang di kho khac\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

                switch (choice) {
            case 1:
                printf("\nDanh sach kho:\n");
                for (i = 0; i < MAX_KHO; i++) {
                    printf("Kho %d: %d hang hoa\n", i + 1, soLuongHangHoa[i]);
                }

                // Thêm l?a ch?n Ki?m tra kho
                int luaChonKiemTraKho;
                printf("\nNhap lua chon (1. Kiem tra kho / 0. Quay lai): ");
                scanf("%d", &luaChonKiemTraKho);

                if (luaChonKiemTraKho == 1) {
                    int khoCheck;
                    printf("Nhap so kho can kiem tra (1-%d): ", MAX_KHO);
                    scanf("%d", &khoCheck);
                    if (khoCheck < 1 || khoCheck > MAX_KHO) {
                        printf("Kho khong hop le.\n");
                    } else {
                        kiemTraKho(khoCheck - 1); // G?i hàm kiêm tra kho
                    }
                }
                break;
            case 2: {
    	int khoDi, khoDen;

    // Nh?p kho chuy?n di và kho chuy?n d?n
    	printf("Nhap so kho chuyen di (1-10): ");
    	scanf("%d", &khoDi);
    	printf("Nhap so kho chuyen den (1-10): ");
   	 scanf("%d", &khoDen);

    // Ki?m tra di?u ki?n kho h?p l?
    	if (khoDi < 1 || khoDi > MAX_KHO || khoDen < 1 || khoDen > MAX_KHO) {
        printf("Kho chuyen di hoac chuyen den khong hop le. Chi chap nhan tu 1 den 10.\n");
    }   else if (khoDi == khoDen) {
        printf("Kho chuyen di va chuyen den phai khac nhau.\n");
    }   else if (soLuongHangHoa[khoDi - 1] == 0) {
        printf("Kho %d khong co hang de chuyen.\n", khoDi);
    }   else {
        // Th?c hi?n di chuy?n
        diChuyenHang(khoDi - 1, khoDen - 1);
    }
    	break;
		}

            case 3:
                themHangVaoKho();
                break;
            case 4:
                // Hàm xu?t hàng di kho khác s? du?c vi?t ? dây
                break;
            case 0:
                printf("\nQuay lai menu chinh.\n");
                break;
            default:
                printf("\nLua chon khong hop le. Vui long thu lai!\n");
        }
    } while (choice != 0);
}
void kiemTraKho(int khoIndex) {
	int i;
    printf("\n--- KIEM TRA KHO %d ---\n", khoIndex + 1);
    printf("STT   Ma San Pham   Ten San Pham                     Khoi Luong    So Luong   Ngay Nhap\n");

    for (i = 0; i < soLuongHangHoa[khoIndex]; i++) {
        printf("%-5d %-15s %-30s %-15s %-10d %-15s\n", 
                i + 1, 
                khoSmall[khoIndex][i].maSanPham, 
                khoSmall[khoIndex][i].tenSanPham, 
                khoSmall[khoIndex][i].khoiLuong, 
                khoSmall[khoIndex][i].soLuong, 
                khoSmall[khoIndex][i].ngayNhap);
    }
}
void diChuyenHang(int khoDi, int khoDen) {
    int i;

    // Ki?m tra n?u kho dích không d? ch? ch?a
    if (soLuongHangHoa[khoDen] + soLuongHangHoa[khoDi] > MAX_ITEMS) {
        printf("Kho %d khong du suc chua toan bo hang chuyen den.\n", khoDen + 1);
        return;
    }

    // Di chuy?n hàng t? khoDi sang khoDen
    for (i = 0; i < soLuongHangHoa[khoDi]; i++) {
        int sttMoi = soLuongHangHoa[khoDen];  // V? trí m?i trong kho dích
        khoSmall[khoDen][sttMoi] = khoSmall[khoDi][i];  // Sao chép d? li?u d?y d?
        soLuongHangHoa[khoDen]++;  // Ch? tang khi sao chép thành công
    }

    // Xóa d? li?u c?a khoDi trong b? nh?
    for (i = 0; i < soLuongHangHoa[khoDi]; i++) {
        strcpy(khoSmall[khoDi][i].maSanPham, "");
        strcpy(khoSmall[khoDi][i].tenSanPham, "");
        strcpy(khoSmall[khoDi][i].khoiLuong, "");
        khoSmall[khoDi][i].soLuong = 0;
        strcpy(khoSmall[khoDi][i].ngayNhap, "");
    }
    soLuongHangHoa[khoDi] = 0;  // Ð?t s? lu?ng hàng trong khoDi v? 0

    // C?p nh?t d? li?u file
    char fileNguon[20], fileDich[20];
    sprintf(fileNguon, "kho%d.txt", khoDi + 1);
    sprintf(fileDich, "kho%d.txt", khoDen + 1);

    // Ghi d? li?u m?i vào file dích
    FILE *file = fopen(fileDich, "w");
    if (file == NULL) {
        printf("Khong the ghi du lieu vao file %s.\n", fileDich);
        return;
    }
    for (i = 0; i < soLuongHangHoa[khoDen]; i++) {
        fprintf(file, "%d %s %s %s %d %s\n", 
                i + 1, 
                khoSmall[khoDen][i].maSanPham, 
                khoSmall[khoDen][i].tenSanPham, 
                khoSmall[khoDen][i].khoiLuong, 
                khoSmall[khoDen][i].soLuong,
                khoSmall[khoDen][i].ngayNhap);
    }
    fclose(file);

    file = fopen(fileNguon, "w");
    if (file != NULL) {
        fclose(file);
    } else {
        printf("Khong the xoa du lieu trong file %s.\n", fileNguon);
    }

    printf("Da chuyen toan bo hang tu kho %d sang kho %d.\n", khoDi + 1, khoDen + 1);
}
void themHangVaoKho() {
    int khoChon;
    printf("Ch?n kho d? thêm hàng (1-%d): ", MAX_KHO);
    scanf("%d", &khoChon);
    khoChon--; // Chuy?n thành ch? s? m?ng (t? 0 d?n MAX_KHO-1)

    if (khoChon < 0 || khoChon >= MAX_KHO) {
        printf("Kho không h?p l?.\n");
        return;
    }

    if (soLuongHangHoa[khoChon] >= MAX_ITEMS) {
        printf("Kho dã d?y, không th? thêm hàng.\n");
        return;
    }

    HangHoa hangMoi;
    printf("Nh?p mã s?n ph?m: ");
    scanf(" %10s", hangMoi.maSanPham);
    printf("Nh?p tên s?n ph?m: ");
    scanf(" %50[^\n]", hangMoi.tenSanPham);
    printf("Nh?p kh?i lu?ng (vd: 3kg): ");
    scanf(" %20s", hangMoi.khoiLuong);
    printf("Nh?p s? lu?ng: ");
    scanf("%d", &hangMoi.soLuong);
    printf("Nh?p ngày nh?p (dd/mm/yyyy): ");
    scanf(" %14s", hangMoi.ngayNhap);

    // Thêm hàng m?i vào kho
    khoSmall[khoChon][soLuongHangHoa[khoChon]] = hangMoi;
    soLuongHangHoa[khoChon]++;

    // Luu l?i vào file
    char tenFile[20];
    sprintf(tenFile, "kho%d.txt", khoChon + 1);
    FILE *file = fopen(tenFile, "a");
    if (file != NULL) {
        fprintf(file, "%d %s %s %s %d %s\n", 
                soLuongHangHoa[khoChon], 
                hangMoi.maSanPham, 
                hangMoi.tenSanPham, 
                hangMoi.khoiLuong, 
                hangMoi.soLuong, 
                hangMoi.ngayNhap);
        fclose(file);
        printf("Thêm hàng vào kho %d thành công.\n", khoChon + 1);
    } else {
        printf("Không th? ghi vào file.\n");
    }
}


// Menu Hang Hoa
void menuHangHoa() {
    int choice;
    do {
        printf("\n--- MENU HANG HOA ---\n");
        printf("1. Tim kiem hang hoa\n");
        printf("2. Kiem tra hang hoa\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                timKiemTrenTongKho();
                break;
            case 2:
                // Ham kiem tra hang hoa se duoc viet o day
                break;
            case 0:
                printf("\nQuay lai menu chinh.\n");
                break;
            default:
                printf("\nLua chon khong hop le. Vui long thu lai!\n");
        }
    } while (choice != 0);
}

int main() {
    docDuLieuKho();  // Doc du lieu tu cac file kho

    int choice;
    do {
        printf("\n=== MENU QUAN LY KHO ===\n");
        printf("1. Tong Kho\n");
        printf("2. Kho Nho\n");
        printf("3. Hang Hoa\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                menuTongKho();
                break;
            case 2:
                menuKhoNho();
                break;
            case 3:
                menuHangHoa();
                break;
            case 0:
                printf("\nThoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("\nLua chon khong hop le. Vui long thu lai!\n");
        }
    } while (choice != 0);

    return 0;
}
