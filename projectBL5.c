#include <stdio.h>
#include <string.h>

#define MAX_KHO 10         // So luong kho nho
#define MAX_ITEMS 1000    // So luong toi da cho trong moi kho

// Cau truc de luu thong tin hang hoa
typedef struct {
    char maSanPham[11];  // Ma san pham (toi da 10 ky tu + 1 cho dau ket thuc chuoi '\0')
    char tenSanPham[51]; // Ten san pham (toi da 50 ky tu + 1 cho dau ket thuc chuoi '\0')
    char khoiLuong[21];  // Khoi luong (toi da 20 ky tu + 1 cho dau ket thuc chuoi '\0')
    int soLuong;         // So luong hang hoa (toi da 20)
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
        while (fscanf(file, "%d %10s %50s %20s %d",  // Doc du lieu voi gioi han ky tu
                       &i, // So thu tu khong can dung
                       khoSmall[kho][i].maSanPham, 
                       khoSmall[kho][i].tenSanPham, 
                       khoSmall[kho][i].khoiLuong, 
                       &khoSmall[kho][i].soLuong) != EOF) {
            i++;
            if (i >= MAX_ITEMS) break; // Dam bao khong vuot qua so luong cho toi da trong kho
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
    char tenTimKiem[50];
    printf("\nNhap ten hang hoa can tim: ");
    scanf("%s", tenTimKiem);
    int i,j;

    int timThay = 0;
    for (i = 0; i < MAX_KHO; i++) {
        for (j = 0; j < soLuongHangHoa[i]; j++) {
            if (strcmp(khoSmall[i][j].tenSanPham, tenTimKiem) == 0) {
                printf("Hang hoa \"%s\" (Ma: %s) co trong kho %d voi so luong: %d\n", 
                       khoSmall[i][j].tenSanPham, khoSmall[i][j].maSanPham, i + 1, khoSmall[i][j].soLuong);
                timThay = 1;
                break;
            }
        }
    }
    if (!timThay) {
        printf("Khong tim thay hang hoa \"%s\" trong tong kho.\n", tenTimKiem);
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
        printf("2. Kiem tra kho\n");
        printf("3. Di chuyen toan bo hang sang kho khac\n");
        printf("4. Them hang vao kho\n");
        printf("5. Xuat hang di kho khac\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nDanh sach kho:\n");
                for (i = 0; i < MAX_KHO; i++) {
                    printf("Kho %d: %d hang hoa\n", i + 1, soLuongHangHoa[i]);
                }
                break;
            case 2:
                // Ham kiem tra kho se duoc viet o day
                break;
            case 3:
                // Ham di chuyen hang se duoc viet o day
                break;
            case 4:
                // Ham them hang vao kho se duoc viet o day
                break;
            case 5:
                // Ham xuat hang di kho khac se duoc viet o day
                break;
            case 0:
                printf("\nQuay lai menu chinh.\n");
                break;
            default:
                printf("\nLua chon khong hop le. Vui long thu lai!\n");
        }
    } while (choice != 0);
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
