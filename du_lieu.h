int x_nguoi_choi;
int y_nguoi_choi;
int vi_tri_tang = 11;
int vat_pham_da_co[1000];
int so_luong_vat_pham_da_co = 0;
int so_luong_vat_the = 0;
int so_luong_vat_pham = 0;
int so_luong_vat_pham_trong_ruong[100];
int so_luong_ruong = 0;
int trang_bi = 0;
int huong_nguoi_choi = 4;
int gio = 6;
int phut = 0;
int mau = 100;
int the_luc = 100;
int do_doi = 100;
int do_khat = 100;
int kiem_tra_hien_thi[2] = {-1, -1};
int thoi_gian_hoi_the_luc = 0;
int so_luong_hoi = 0;
char hanh_dong[100] = "Ban dang dung yen";
char tam_nhin[100];
char tay_phai[100] = "Khong";
char hien_thi[100];
char buoi[100] = "Sang";
char thoi_tiet[100] = "Nhieu may";
char nguoi_choi = '>';
int sua_loi_file = 0;
int i, j;

void TextColor(int x) // ham in chu mau trong c
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void gotoxy(int x, int y) // ham di chuyen con tro toi vi tri x y
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

int random(int minN, int maxN) // ham sinh so ngau nhien trong doan tu minN den maxN
{
    return minN + rand() % (maxN + 1 - minN);
}

int so_luong_chu_so(int temp, int count)
{
    while (temp != 0) // nhom lenh tim so luong chu so de xoa cho hop ly
    {
        count++;
        temp = temp / 10;
    }
    return count;
}

FILE *f;
typedef struct trong_trot
{
    int dang_duoc_trong;
    int vat_pham_trong;
} trong_trot;

typedef struct khoi
{
    int id;
    char ten[100];
    char bieu_tuong;
    int do_ben;
    int do_ben_toi_da;
    int kha_nang_tuong_tac;
    int kha_nang_dung_trong_vat_the;
    trong_trot kha_nang_trong_trot;
    int vi_tri_ruong;
    int toa_do_x;
    int toa_do_y;
} khoi;

khoi vat_the[1000];

typedef struct doi_tuong
{
    int id;
    char ten[100];
    int suc_cong_pha;
    int co_the_an;
    int gop;
    int so_luong;
    int the;
} doi_tuong;

doi_tuong vat_pham[1000];
doi_tuong vat_the_ruong[100][100];

typedef struct thoi_gian_hoi
{
    int id;
    int thoi_gian;
    int vi_tri;
    char ten_vat_the[100];
} thoi_gian_hoi;

thoi_gian_hoi thoi_gian_hoi_vat_the[100];

void luu_du_lieu()
{
    f = fopen("save.txt", "w");
    fprintf(f, "%d ", x_nguoi_choi);
    fprintf(f, "%d ", y_nguoi_choi);
    fprintf(f, "%d ", vi_tri_tang);
    fprintf(f, "%d ", so_luong_vat_pham);
    fprintf(f, "%d ", so_luong_vat_the);
    fprintf(f, "%d ", so_luong_ruong);
    fprintf(f, "%d ", trang_bi);
    fprintf(f, "%d ", huong_nguoi_choi);
    fprintf(f, "%d ", gio);
    fprintf(f, "%d ", phut);
    fprintf(f, "%d ", mau);
    fprintf(f, "%d ", the_luc);
    fprintf(f, "%d ", do_doi);
    fprintf(f, "%d ", do_khat);
    for (i = 0; i < 2; i++)
        fprintf(f, "%d ", kiem_tra_hien_thi[i]);
    fprintf(f, "%d ", thoi_gian_hoi_the_luc);
    fprintf(f, "\n");
    fputs(hanh_dong, f);
    fprintf(f, "\n");
    fputs(tam_nhin, f);
    fprintf(f, "\n");
    fputs(tay_phai, f);
    if (sua_loi_file == 0) // dieu chinh khoang cach luu game thich hop
        fprintf(f, "\n");
    if (sua_loi_file == 1 && strcmp(tay_phai, "Khong") == 0)
        fprintf(f, "\n");
    fputs(buoi, f);
    fprintf(f, "\n");
    fputs(thoi_tiet, f);
    fprintf(f, "\n");
    fputc(nguoi_choi, f);
    fprintf(f, "\n");
    for (i = 0; i < so_luong_vat_the; i++)
    {
        fprintf(f, "%d ", vat_the[i].id);
        fprintf(f, "%d ", vat_the[i].do_ben);
        fprintf(f, "%d ", vat_the[i].do_ben_toi_da);
        fprintf(f, "%d ", vat_the[i].kha_nang_tuong_tac);
        fprintf(f, "%d ", vat_the[i].kha_nang_dung_trong_vat_the);
        fprintf(f, "%d ", vat_the[i].kha_nang_trong_trot.dang_duoc_trong);
        fprintf(f, "%d ", vat_the[i].kha_nang_trong_trot.vat_pham_trong);
        fprintf(f, "%d ", vat_the[i].vi_tri_ruong);
        fprintf(f, "%d ", vat_the[i].toa_do_x);
        fprintf(f, "%d ", vat_the[i].toa_do_y);
    }
    fprintf(f, "\n");
    for (i = 0; i < so_luong_vat_the; i++)
    {
        fputs(vat_the[i].ten, f);
        fprintf(f, "\n");
    }
    for (i = 0; i < so_luong_vat_the; i++)
        fputc(vat_the[i].bieu_tuong, f);
    for (i = 0; i < so_luong_vat_pham; i++)
    {
        fprintf(f, "%d ", vat_pham[i].id);
        fprintf(f, "%d ", vat_pham[i].gop);
        fprintf(f, "%d ", vat_pham[i].suc_cong_pha);
        fprintf(f, "%d ", vat_pham[i].co_the_an);
        fprintf(f, "%d ", vat_pham[i].so_luong);
        fprintf(f, "%d ", vat_pham[i].the);
    }
    fprintf(f, "\n");
    for (i = 0; i < so_luong_vat_pham; i++)
    {
        fputs(vat_pham[i].ten, f);
        if (sua_loi_file == 0)
            fprintf(f, "\n");
    }
    fprintf(f, "%d ", so_luong_hoi);
    for (i = 0; i < so_luong_hoi; i++)
    {
        fprintf(f, "%d ", thoi_gian_hoi_vat_the[i].id);
        fprintf(f, "%d ", thoi_gian_hoi_vat_the[i].thoi_gian);
        fprintf(f, "%d ", thoi_gian_hoi_vat_the[i].vi_tri);
    }
    fprintf(f, "\n");
    for (i = 0; i < so_luong_hoi; i++)
    {
        fputs(thoi_gian_hoi_vat_the[i].ten_vat_the, f);
        if (sua_loi_file == 0)
            fprintf(f, "\n");
    }
    for (i = 0; i < so_luong_ruong; i++)
        fprintf(f, "%d ", so_luong_vat_pham_trong_ruong[i]);
    fprintf(f, "\n");
    for (i = 0; i < so_luong_ruong; i++)
    {
        for (j = 0; j < so_luong_vat_pham_trong_ruong[i]; j++)
        {
            fprintf(f, "%d ", vat_the_ruong[j][i].id);
            fprintf(f, "%d ", vat_the_ruong[j][i].gop);
            fprintf(f, "%d ", vat_the_ruong[j][i].suc_cong_pha);
            fprintf(f, "%d ", vat_the_ruong[j][i].co_the_an);
            fprintf(f, "%d ", vat_the_ruong[j][i].so_luong);
            fprintf(f, "%d ", vat_the_ruong[j][i].the);
        }
        fprintf(f, "\n");
        for (j = 0; j < so_luong_vat_pham_trong_ruong[i]; j++)
        {
            fputs(vat_the_ruong[j][i].ten, f);
            if (sua_loi_file == 0)
                fprintf(f, "\n");
        }
    }
    fprintf(f, "%d ", so_luong_vat_pham_da_co);
    for (i = 0; i < so_luong_vat_pham_da_co; i++)
        fprintf(f, "%d ", vat_pham_da_co[i]);
    fclose(f);
}

void xoa_du_lieu()
{
    f = fopen("save.txt", "w");
    fputc(' ', f);
    fclose(f);
}

void tai_du_lieu()
{
    sua_loi_file = 1;
    f = fopen("save.txt", "r");
    fscanf(f, "%d ", &x_nguoi_choi);
    fscanf(f, "%d ", &y_nguoi_choi);
    fscanf(f, "%d ", &vi_tri_tang);
    fscanf(f, "%d ", &so_luong_vat_pham);
    fscanf(f, "%d ", &so_luong_vat_the);
    fscanf(f, "%d ", &so_luong_ruong);
    fscanf(f, "%d ", &trang_bi);
    fscanf(f, "%d ", &huong_nguoi_choi);
    fscanf(f, "%d ", &gio);
    fscanf(f, "%d ", &phut);
    fscanf(f, "%d ", &mau);
    fscanf(f, "%d ", &the_luc);
    fscanf(f, "%d ", &do_doi);
    fscanf(f, "%d ", &do_khat);
    for (i = 0; i < 2; i++)
        fscanf(f, "%d ", &kiem_tra_hien_thi[i]);
    fscanf(f, "%d ", &thoi_gian_hoi_the_luc);
    fgets(hanh_dong, sizeof hanh_dong, f);
    hanh_dong[strcspn(hanh_dong, "\n")] = 0; // sua loi du dau \n khi dung fgets
    fgets(tam_nhin, sizeof tam_nhin, f);
    tam_nhin[strcspn(tam_nhin, "\n")] = 0;
    fgets(tay_phai, sizeof tay_phai, f);
    tay_phai[strcspn(tay_phai, "\n")] = 0;
    fgets(buoi, sizeof buoi, f);
    buoi[strcspn(buoi, "\n")] = 0;
    fgets(thoi_tiet, sizeof thoi_tiet, f);
    thoi_tiet[strcspn(thoi_tiet, "\n")] = 0;
    nguoi_choi = fgetc(f);
    for (i = 0; i < so_luong_vat_the; i++)
    {
        fscanf(f, "%d ", &vat_the[i].id);
        fscanf(f, "%d ", &vat_the[i].do_ben);
        fscanf(f, "%d ", &vat_the[i].do_ben_toi_da);
        fscanf(f, "%d ", &vat_the[i].kha_nang_tuong_tac);
        fscanf(f, "%d ", &vat_the[i].kha_nang_dung_trong_vat_the);
        fscanf(f, "%d ", &vat_the[i].kha_nang_trong_trot.dang_duoc_trong);
        fscanf(f, "%d ", &vat_the[i].kha_nang_trong_trot.vat_pham_trong);
        fscanf(f, "%d ", &vat_the[i].vi_tri_ruong);
        fscanf(f, "%d ", &vat_the[i].toa_do_x);
        fscanf(f, "%d ", &vat_the[i].toa_do_y);
    }
    for (i = 0; i < so_luong_vat_the; i++)
    {
        fgets(vat_the[i].ten, sizeof vat_the[i].ten, f);
        vat_the[i].ten[strcspn(vat_the[i].ten, "\n")] = 0;
    }
    for (i = 0; i < so_luong_vat_the; i++)
        vat_the[i].bieu_tuong = fgetc(f);
    for (i = 0; i < so_luong_vat_pham; i++)
    {
        fscanf(f, "%d ", &vat_pham[i].id);
        fscanf(f, "%d ", &vat_pham[i].gop);
        fscanf(f, "%d ", &vat_pham[i].suc_cong_pha);
        fscanf(f, "%d ", &vat_pham[i].co_the_an);
        fscanf(f, "%d ", &vat_pham[i].so_luong);
        fscanf(f, "%d ", &vat_pham[i].the);
    }
    for (i = 0; i < so_luong_vat_pham; i++)
        fgets(vat_pham[i].ten, sizeof vat_pham[i].ten, f);
    fscanf(f, "%d ", &so_luong_hoi);
    for (i = 0; i < so_luong_hoi; i++)
    {
        fscanf(f, "%d ", &thoi_gian_hoi_vat_the[i].id);
        fscanf(f, "%d ", &thoi_gian_hoi_vat_the[i].thoi_gian);
        fscanf(f, "%d ", &thoi_gian_hoi_vat_the[i].vi_tri);
    }
    for (i = 0; i < so_luong_hoi; i++)
    {
        fgets(thoi_gian_hoi_vat_the[i].ten_vat_the, sizeof thoi_gian_hoi_vat_the[i].ten_vat_the, f);
        thoi_gian_hoi_vat_the[i].ten_vat_the[strcspn(thoi_gian_hoi_vat_the[i].ten_vat_the, "\n")] = 0;
    }
    for (i = 0; i < so_luong_ruong; i++)
        fscanf(f, "%d ", &so_luong_vat_pham_trong_ruong[i]);
    for (i = 0; i < so_luong_ruong; i++)
    {
        for (j = 0; j < so_luong_vat_pham_trong_ruong[i]; j++)
        {
            fscanf(f, "%d ", &vat_the_ruong[j][i].id);
            fscanf(f, "%d ", &vat_the_ruong[j][i].gop);
            fscanf(f, "%d ", &vat_the_ruong[j][i].suc_cong_pha);
            fscanf(f, "%d ", &vat_the_ruong[j][i].co_the_an);
            fscanf(f, "%d ", &vat_the_ruong[j][i].so_luong);
            fscanf(f, "%d ", &vat_the_ruong[j][i].the);
        }
        for (j = 0; j < so_luong_vat_pham_trong_ruong[i]; j++)
            fgets(vat_the_ruong[j][i].ten, sizeof vat_the_ruong[j][i].ten, f);
    }
    fscanf(f, "%d ", &so_luong_vat_pham_da_co);
    for (i = 0; i < so_luong_vat_pham_da_co; i++)
        fscanf(f, "%d ", &vat_pham_da_co[i]);
    fclose(f);
}

/*Du lieu the gioi*/
void du_lieu_tang_1_1()
{
    srand((int)time(0));
    so_luong_vat_the = random(50, 100);

    x_nguoi_choi = random(7, 52);
    y_nguoi_choi = random(6, 20);

    while (1)
    {
        for (i = 0; i < so_luong_vat_the; i++) // nhom lenh tao cay o toa do ngau nhien
        {
            vat_the[i].toa_do_x = random(8, 52);
            vat_the[i].toa_do_y = random(6, 20);

            if (vat_the[i].toa_do_x == x_nguoi_choi && vat_the[i].toa_do_y == y_nguoi_choi)
                x_nguoi_choi--; // sua loi cay xuat hien ngay vi tri nguoi choi
        }

        int kiem_tra_so_luong = 0;
        for (i = 0; i < so_luong_vat_the; i++) // nhom lenh kiem tra cac cay chong len nhau
        {
            int kt = 0;
            for (j = 0; j < so_luong_vat_the; j++)
            {
                if (vat_the[j].toa_do_x == vat_the[i].toa_do_x && vat_the[j].toa_do_y == vat_the[i].toa_do_y)
                    kt++;
            }
            if (kt >= 2)
                break;
            kiem_tra_so_luong++;
        }
        if (kiem_tra_so_luong == so_luong_vat_the)
            break;
    }
    for (i = 0; i < so_luong_vat_the; i++) // tao vat the
    {
        gotoxy(vat_the[i].toa_do_x, vat_the[i].toa_do_y); // tao vat the o vi tri ngau nhien
        int vat_the_ban_dau = random(1, 5);
        if (vat_the_ban_dau == 1)
        {
            strcpy(vat_the[i].ten, "cai cay");
            vat_the[i].bieu_tuong = 'C';
            vat_the[i].id = 1;
            vat_the[i].do_ben_toi_da = 10;
            vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
            vat_the[i].kha_nang_tuong_tac = 0;
            vat_the[i].kha_nang_dung_trong_vat_the = 0;
            vat_the[i].kha_nang_trong_trot.dang_duoc_trong = 0;
            vat_the[i].kha_nang_trong_trot.vat_pham_trong = -1;
            vat_the[i].vi_tri_ruong = -1;
            printf("%c", vat_the[i].bieu_tuong); // cai cay
        }
        if (vat_the_ban_dau == 2)
        {
            strcpy(vat_the[i].ten, "tang da");
            vat_the[i].bieu_tuong = 'D';
            vat_the[i].id = 2;
            vat_the[i].do_ben_toi_da = 10;
            vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
            vat_the[i].kha_nang_tuong_tac = 0;
            vat_the[i].kha_nang_dung_trong_vat_the = 0;
            vat_the[i].kha_nang_trong_trot.dang_duoc_trong = 0;
            vat_the[i].kha_nang_trong_trot.vat_pham_trong = -1;
            vat_the[i].vi_tri_ruong = -1;
            printf("%c", vat_the[i].bieu_tuong); // tang da
        }
        if (vat_the_ban_dau == 3)
        {
            strcpy(vat_the[i].ten, "bui nho");
            vat_the[i].bieu_tuong = 'N';
            vat_the[i].id = 3;
            vat_the[i].do_ben_toi_da = 4;
            vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
            vat_the[i].kha_nang_tuong_tac = 1;
            vat_the[i].kha_nang_dung_trong_vat_the = 0;
            vat_the[i].kha_nang_trong_trot.dang_duoc_trong = 0;
            vat_the[i].kha_nang_trong_trot.vat_pham_trong = -1;
            vat_the[i].vi_tri_ruong = -1;
            printf("%c", vat_the[i].bieu_tuong); // bui nho
        }
        if (vat_the_ban_dau == 4)
        {
            strcpy(vat_the[i].ten, "bui co");
            vat_the[i].bieu_tuong = 'c';
            vat_the[i].id = 7;
            vat_the[i].do_ben_toi_da = 1;
            vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
            vat_the[i].kha_nang_tuong_tac = 0;
            vat_the[i].kha_nang_dung_trong_vat_the = 1;
            vat_the[i].kha_nang_trong_trot.dang_duoc_trong = 0;
            vat_the[i].kha_nang_trong_trot.vat_pham_trong = -1;
            vat_the[i].vi_tri_ruong = -1;
            printf("%c", vat_the[i].bieu_tuong); // bui co
        }
        if (vat_the_ban_dau == 5)
        {
            strcpy(vat_the[i].ten, "vung nuoc");
            vat_the[i].bieu_tuong = 'v';
            vat_the[i].id = 9;
            vat_the[i].do_ben_toi_da = 1;
            vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
            vat_the[i].kha_nang_tuong_tac = 1;
            vat_the[i].kha_nang_dung_trong_vat_the = 1;
            vat_the[i].kha_nang_trong_trot.dang_duoc_trong = 0;
            vat_the[i].kha_nang_trong_trot.vat_pham_trong = -1;
            vat_the[i].vi_tri_ruong = -1;
            printf("%c", vat_the[i].bieu_tuong); // vung nuoc
        }
    }
}

/* Danh sach id cua vat the:
    1: Cai cay.
    2: Tang da.
    3: Bui nho.
    4: Mam cay.
    5: Lo nung.
    6: Ruong go.
    7: Bui co.
    8: Dat da duoc xoi.
    9: Vung nuoc.

*/

/*Du lieu van ban cua game*/
void huong_dan()
{
    gotoxy(5, 5);
    printf("Huong dan: ");
    gotoxy(7, 7);
    printf("Doc huong dan cac nut tai: https://github.com/Tomi-Sakae/InfinityTower_Text-based-game");
}

void thong_tin_vat_pham(int vi_tri)
{
    gotoxy(56, 5);
    printf("Thong tin vat pham: ");
    gotoxy(58, 7);
    puts(vat_pham[vi_tri].ten);
    gotoxy(58 + strlen(vat_pham[vi_tri].ten), 7);
    printf(": ");
    if (vat_pham[vi_tri].id == 1)
    {
        printf("Mot khoi go san sui thu duoc khi chat");
        gotoxy(58, 8);
        printf("cay.");
    }
    if (vat_pham[vi_tri].id == 2)
        printf("Mot cuc da nho thu duoc khi dap da.");
    if (vat_pham[vi_tri].id == 3)
    {
        printf("Mot chum nhung hat nho voi huong vi");
        gotoxy(58, 8);
        printf("hoang da.");
    }
    if (vat_pham[vi_tri].id == 4)
    {
        printf("Mam cay nay se lon thanh cay neu ban");
        gotoxy(58, 8);
        printf("trong no!.");
    }
    if (vat_pham[vi_tri].id == 5)
    {
        printf("Mot cay riu bang sat da bi ri set duoc");
        gotoxy(58, 8);
        printf("che tao cach day rat lau.");
    }
    if (vat_pham[vi_tri].id == 6)
    {
        printf("Mot cay cup bang sat da bi ri set duoc");
        gotoxy(58, 8);
        printf("che tao cach day rat lau.");
    }
    if (vat_pham[vi_tri].id == 7)
    {
        printf("Mot cay riu bang go don so nhung hieu");
        gotoxy(58, 8);
        printf("qua.");
    }
    if (vat_pham[vi_tri].id == 8)
    {
        printf("Mot cay cup bang go gian di nhung chat");
        gotoxy(58, 8);
        printf("luong.");
    }
    if (vat_pham[vi_tri].id == 9)
    {
        printf("Lo nung nay co the nau nhung thu co");
        gotoxy(58, 8);
        printf("ban.");
    }
    if (vat_pham[vi_tri].id == 10)
    {
        printf("Cai ruong chua duoc moi thu tren the");
        gotoxy(58, 8);
        printf("gioi nay!.");
    }
    if (vat_pham[vi_tri].id == 11)
    {
        printf("Tam the duoc cho la mot manh vo cua");
        gotoxy(58, 8);
        printf("vet nut khong gian khi the gioi bat dau bi phan chia");
        gotoxy(58, 9);
        printf("ra cac tang lop khong gian khep kin.");
    }
    getch();
}