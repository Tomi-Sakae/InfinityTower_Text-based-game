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
int so_luong_hoi = 0;
char hanh_dong[100] = "Ban dang dung yen";
char tam_nhin[100];
char tay_phai[100] = "Khong";
char hien_thi[100];
char buoi[100] = "Sang";
char thoi_tiet[100] = "Nhieu may";
char nguoi_choi = '>';
int sua_loi_file = 0;

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

typedef struct khoi
{
    int id;
    char ten[100];
    int do_ben;
    int do_ben_toi_da;
    int kha_nang_tuong_tac;
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
} thoi_gian_hoi;

thoi_gian_hoi thoi_gian_hoi_vat_the[100];

void luu_du_lieu()
{
    int i, j;
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
    for (i = 0; i < so_luong_vat_pham; i++)
    {
        fprintf(f, "%d ", vat_pham[i].id);
        fprintf(f, "%d ", vat_pham[i].gop);
        fprintf(f, "%d ", vat_pham[i].suc_cong_pha);
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
    int i, j;
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
        fscanf(f, "%d ", &vat_the[i].vi_tri_ruong);
        fscanf(f, "%d ", &vat_the[i].toa_do_x);
        fscanf(f, "%d ", &vat_the[i].toa_do_y);
    }
    for (i = 0; i < so_luong_vat_the; i++)
    {
        fgets(vat_the[i].ten, sizeof vat_the[i].ten, f);
        vat_the[i].ten[strcspn(vat_the[i].ten, "\n")] = 0;
    }

    for (i = 0; i < so_luong_vat_pham; i++)
    {
        fscanf(f, "%d ", &vat_pham[i].id);
        fscanf(f, "%d ", &vat_pham[i].gop);
        fscanf(f, "%d ", &vat_pham[i].suc_cong_pha);
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
    for (i = 0; i < so_luong_ruong; i++)
        fscanf(f, "%d ", &so_luong_vat_pham_trong_ruong[i]);
    for (i = 0; i < so_luong_ruong; i++)
    {
        for (j = 0; j < so_luong_vat_pham_trong_ruong[i]; j++)
        {
            fscanf(f, "%d ", &vat_the_ruong[j][i].id);
            fscanf(f, "%d ", &vat_the_ruong[j][i].gop);
            fscanf(f, "%d ", &vat_the_ruong[j][i].suc_cong_pha);
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
    gotoxy(56,5);
    printf("Thong tin vat pham: ");
    gotoxy(58,7);
    puts(vat_pham[vi_tri].ten);
    gotoxy(58+strlen(vat_pham[vi_tri].ten), 7);
    printf(":");
    getch();
}