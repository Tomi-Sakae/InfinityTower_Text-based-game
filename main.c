#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

char lua_chon;
int x_nguoi_choi;
int y_nguoi_choi;
int x_tam, y_tam, i, j, i_tam, do_dai_chuoi[100];
char hanh_dong[100] = "Ban dang dung yen";
char tam_nhin[100];
char tay_phai[100] = "Khong";
char buoi[100] = "Sang";
char thoi_tiet[100] = "Nhieu may";
int so_luong_vat_the = 0;
int so_luong_vat_pham = 0;
char nguoi_choi = '>';
int huong_nguoi_choi = 4;
int gio = 6;
int phut = 0;
int mau = 100;
int the_luc = 100;

void *thoi_gian(void *vargp) // luong chay thoi gian
{
    while (1)
    {
        sleep(7);
        phut += 10;
        if (phut >= 60)
        {
            gio++;
            phut = 0;
        }
        if (gio >= 24)
            gio = 0;
    }
    return NULL;
}

typedef struct khoi
{
    int id;
    char ten[100];
    int toa_do_x;
    int toa_do_y;
} khoi;

khoi vat_the[1000];

typedef struct doi_tuong
{
    int id;
    char ten[100];
    int so_luong;
    int the;
} doi_tuong;

doi_tuong vat_pham[1000];

int random(int minN, int maxN) // ham sinh so ngau nhien trong doan tu minN den maxN
{
    return minN + rand() % (maxN + 1 - minN);
}

void gotoxy(int x, int y) // ham di chuyen con tro toi vi tri x y
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
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

void thong_tin_nhan_vat()
{
    gotoxy(62, 6);
    for (i = 0; i <= do_dai_chuoi[3]; i++) // xoa mau truoc do
        printf(" ");

    gotoxy(66, 8);
    for (i = 0; i <= do_dai_chuoi[4]; i++) // xoa the luc truoc do
        printf(" ");

    gotoxy(67, 10);
    for (i = 0; i <= do_dai_chuoi[5]; i++) // xoa chuoi tay phai truoc do
        printf(" ");

    gotoxy(56, 6);
    printf("Mau: %d", mau); // hien mau
    do_dai_chuoi[3] = so_luong_chu_so(mau, 0);

    gotoxy(56, 8);
    printf("The luc: %d", the_luc); // hien the luc
    do_dai_chuoi[4] = so_luong_chu_so(the_luc, 0);

    if (vat_pham[0].so_luong != 0)
        strcpy(tay_phai, vat_pham[0].ten);
    else
        strcpy(tay_phai, "Khong");
    gotoxy(56, 10);
    printf("Tay phai: ");
    puts(tay_phai); // hien thi chuoi tay phai
    if (vat_pham[0].so_luong != 0 && vat_pham[0].the == 0)
    {
        gotoxy(66 + strlen(tay_phai), 10);
        printf(" x ");
    }
    if (vat_pham[0].so_luong != 0)
    {
        gotoxy(66 + strlen(tay_phai) + 3, 10);
        printf("%d", vat_pham[0].so_luong);
    }
    do_dai_chuoi[5] = strlen(tay_phai) + so_luong_chu_so(vat_pham[0].so_luong, 0) + 3;
}

void giao_dien_game_chinh() // ham hien thi chuoi va xoa chuoi
{
    gotoxy(5, 23);
    for (i = 0; i <= do_dai_chuoi[0]; i++) // xoa chuoi hanh dong truoc do
        printf(" ");

    gotoxy(5, 3);
    for (i = 0; i <= do_dai_chuoi[1]; i++) // xoa chuoi tam nhin truoc do
        printf(" ");

    gotoxy(7, 0);
    for (i = 0; i <= do_dai_chuoi[2]; i++) // xoa chuoi buoi truoc do
        printf(" ");

    gotoxy(5, 23);
    puts(hanh_dong);
    do_dai_chuoi[0] = strlen(hanh_dong); // hien thi chuoi hanh dong cua nhan vat

    gotoxy(5, 3);
    puts(tam_nhin);
    do_dai_chuoi[1] = strlen(tam_nhin); // hien thi chuoi tam nhin cua nhan vat

    if (gio >= 6 && gio < 11)
        strcpy(buoi, "Sang");
    if (gio >= 11 && gio < 13)
        strcpy(buoi, "Trua");
    if (gio >= 13 && gio < 18)
        strcpy(buoi, "Chieu");
    if (gio >= 18 && gio < 24)
        strcpy(buoi, "Toi");
    if (gio >= 0 && gio < 6)
        strcpy(buoi, "Khuya");
    gotoxy(0, 0);
    printf("Buoi: ");
    puts(buoi);
    do_dai_chuoi[2] = strlen(buoi); // hien thi chuoi buoi

    gotoxy(0, 1);
    printf("Troi: ");
    puts(thoi_tiet);
}

void tui_do() // giao dien tui do
{
    int y_chon = 7;
    int y = 7;
    char lua_chon_menu;
    gotoxy(56, 5);
    printf("Tui do: ");
    for (i = 0; i < so_luong_vat_pham; i++) // hien thi cac vat pham ma nguoi choi co
    {
        if (vat_pham[i].so_luong != 0)
        {
            gotoxy(58, y);
            puts(vat_pham[i].ten);
            gotoxy(58 + strlen(vat_pham[i].ten), y);
            printf(" x ");
            gotoxy(58 + strlen(vat_pham[i].ten) + 3, y);
            printf("%d", vat_pham[i].so_luong);
            y += 2;
        }
    }
    while (1) // vong lap lua chon vat pham
    {
        gotoxy(56, y_chon);
        printf("->");
        lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'e':
        {
            return;
            break;
        }
        case 'w':
        {
            if (y_chon > 7)
            {
                gotoxy(56, y_chon);
                printf("  ");
                y_chon -= 2;
            }
            break;
        }
        case 's':
        {
            if (y_chon < y - 2)
            {
                gotoxy(56, y_chon);
                printf("  ");
                y_chon += 2;
            }
            break;
        }
        case 'k':
        {
            
            break;
        }
        }
    }
}

void di_chuyen_va_hanh_dong();
void va_cham();
void thuc_hien_hanh_dong();
int kiem_tra_vat_the();
void thuc_hien_dat_khoi();
int kiem_tra_vi_tri_vat_the(int x, int y);
void bo_lo();
void chuyen_chuc_nang();
void them_vat_pham(int id, int so_luong);
void tao_moi_vat_pham(int id, int so_luong);
void xoa_vat_pham(int vi_tri_xoa);

int main()
{
    srand((int)time(0));
    so_luong_vat_the = random(25, 50);

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
        int vat_the_ban_dau = random(1, 3);
        if (vat_the_ban_dau == 1)
        {
            strcpy(vat_the[i].ten, "cai cay");
            vat_the[i].id = 1;
            printf("C"); // cai cay
        }
        if (vat_the_ban_dau == 2)
        {
            strcpy(vat_the[i].ten, "cuc da");
            vat_the[i].id = 2;
            printf("D"); // cuc da
        }
        if (vat_the_ban_dau == 3)
        {
            strcpy(vat_the[i].ten, "bui nho");
            vat_the[i].id = 3;
            printf("N"); // bui nho
        }
    }

    // thiet ke khung tro choi chinh
    int y = 6;
    gotoxy(5, 5);
    for (i = 1; i <= 50; i++)
        printf("=");
    for (i = 1; i <= 15; i++)
    {
        gotoxy(53, y);
        printf("||");
        y++;
    }
    y = 6;
    gotoxy(5, 21);
    for (i = 1; i <= 50; i++)
        printf("=");
    for (i = 1; i <= 15; i++)
    {
        gotoxy(5, y);
        printf("||");
        y++;
    }
    // ket thuc thiet ke khung tro choi chinh
    kiem_tra_vat_the();

    pthread_t thread_id; // chay tien trinh thoi gian
    pthread_create(&thread_id, NULL, thoi_gian, NULL);

    while (1)
    {
        gotoxy(x_nguoi_choi, y_nguoi_choi); // toa do nguoi choi
        printf("%c", nguoi_choi);           // nguoi choi

        giao_dien_game_chinh();
        thong_tin_nhan_vat();

        x_tam = x_nguoi_choi; // luu toa do cua nguoi choi de xoa nguoi choi khi di chuyen
        y_tam = y_nguoi_choi;

        di_chuyen_va_hanh_dong();

        gotoxy(x_tam, y_tam);
        printf(" "); // xoa nguoi choi o vi tri cu
    }

    return 0;
}

void di_chuyen_va_hanh_dong() // ham di chuyen vi tri va thuc hien hanh dong cua nguoi choi
{
    lua_chon = getch();
    switch (lua_chon)
    {
    case 'w':
    {
        y_nguoi_choi--;
        strcpy(hanh_dong, "Ban vua di len");
        huong_nguoi_choi = 1;
        nguoi_choi = '^';
        break;
    }
    case 'a':
    {
        x_nguoi_choi--;
        strcpy(hanh_dong, "Ban vua sang trai");
        huong_nguoi_choi = 2;
        nguoi_choi = '<';
        break;
    }
    case 's':
    {
        y_nguoi_choi++;
        strcpy(hanh_dong, "Ban vua di xuong");
        huong_nguoi_choi = 3;
        nguoi_choi = 'v';
        break;
    }
    case 'd':
    {
        x_nguoi_choi++;
        strcpy(hanh_dong, "Ban vua sang phai");
        huong_nguoi_choi = 4;
        nguoi_choi = '>';
        break;
    }
    case 'k':
    {
        if (huong_nguoi_choi == kiem_tra_vat_the())
            thuc_hien_hanh_dong();
        break;
    }
    case 'p':
    {
        if (vat_pham[0].so_luong != 0)
            thuc_hien_dat_khoi();
        break;
    }
    case 'e':
    {
        chuyen_chuc_nang();
        tui_do();
        chuyen_chuc_nang();
        break;
    }
    case 75:
    {
        nguoi_choi = '<'; // doi huong cua nguoi choi bang cac phim mui ten
        huong_nguoi_choi = 2;
        break;
    }
    case 72:
    {
        nguoi_choi = '^';
        huong_nguoi_choi = 1;
        break;
    }
    case 77:
    {
        nguoi_choi = '>';
        huong_nguoi_choi = 4;
        break;
    }
    case 80:
    {
        nguoi_choi = 'v';
        huong_nguoi_choi = 3;
        break;
    }
    }
    va_cham();
    kiem_tra_vat_the();
}

void va_cham() // ham kiem tra khi nguoi choi tien vao nhung noi khong duoc phep di chuyen
{
    // kiem tra va cham tuong thanh
    if (x_nguoi_choi >= 52)
        x_nguoi_choi = 52;
    if (x_nguoi_choi <= 7)
        x_nguoi_choi = 7;
    if (y_nguoi_choi >= 20)
        y_nguoi_choi = 20;
    if (y_nguoi_choi <= 6)
        y_nguoi_choi = 6;

    // kiem tra va cham vat the
    for (i = 0; i < so_luong_vat_the; i++)
    {
        if (x_nguoi_choi == vat_the[i].toa_do_x && y_nguoi_choi == vat_the[i].toa_do_y)
        {
            x_nguoi_choi = x_tam;
            y_nguoi_choi = y_tam;
        }
    }
}

void thuc_hien_hanh_dong()
{
    gotoxy(vat_the[i_tam].toa_do_x, vat_the[i_tam].toa_do_y); // bien i tam duoc lay tu ham kiem tra vat the
    printf(" ");                                              // xoa cay o vi tri vua chat

    vat_the[i_tam].toa_do_x = NULL;
    vat_the[i_tam].toa_do_y = NULL;

    if (vat_the[i_tam].id == 1)
    {
        strcpy(hanh_dong, "Ban vua chat cay | + 4 khoi go");
        them_vat_pham(1, 4);
    }

    if (strcmp(vat_the[i_tam].ten, "khoi go") == 0)
    {
        strcpy(hanh_dong, "Ban vua chat go | + 1 khoi go");
        them_vat_pham(1, 1);
    }

    if (vat_the[i_tam].id == 2)
    {
        strcpy(hanh_dong, "Ban vua dao da | + 1 cuc da");
        them_vat_pham(2, 1);
    }

    if (vat_the[i_tam].id == 3)
    {
        strcpy(hanh_dong, "Ban vua nhat nho | + 1 trai nho");
        them_vat_pham(3, 1);
    }
}

int kiem_tra_vat_the() // kiem tra vat the o gan nguoi choi
{
    strcpy(tam_nhin, "Do la ");
    for (i = 0; i < so_luong_vat_the; i++)
    {
        if (huong_nguoi_choi == 4) // fix loi cac phim mui ten
        {
            if (vat_the[i].toa_do_x == x_nguoi_choi + 1 && vat_the[i].toa_do_y == y_nguoi_choi)
            {
                strcat(tam_nhin, vat_the[i].ten);
                i_tam = i; // gan i tam de kiem tra vat the va id vat the
                return 4;  // tra ve huong cua vat the so voi nguoi choi
            }
        }
        if (huong_nguoi_choi == 2)
        {
            if (vat_the[i].toa_do_x == x_nguoi_choi - 1 && vat_the[i].toa_do_y == y_nguoi_choi)
            {
                strcat(tam_nhin, vat_the[i].ten);
                i_tam = i;
                return 2;
            }
        }
        if (huong_nguoi_choi == 3)
        {
            if (vat_the[i].toa_do_x == x_nguoi_choi && vat_the[i].toa_do_y == y_nguoi_choi + 1)
            {
                strcat(tam_nhin, vat_the[i].ten);
                i_tam = i;
                return 3;
            }
        }
        if (huong_nguoi_choi == 1)
        {
            if (vat_the[i].toa_do_x == x_nguoi_choi && vat_the[i].toa_do_y == y_nguoi_choi - 1)
            {
                strcat(tam_nhin, vat_the[i].ten);
                i_tam = i;
                return 1;
            }
        }
    }
    strcpy(tam_nhin, " "); // nguoi choi khong o gan bat ky vat the nao
    return 0;
}

void thuc_hien_dat_khoi()
{
    if (huong_nguoi_choi == 1 && kiem_tra_vi_tri_vat_the(x_nguoi_choi, y_nguoi_choi - 1) != 1 && y_nguoi_choi != 6) // kiem tra vi tri dat khoi co trung voi khoi da co va tuong thanh hay khong
    {
        gotoxy(x_nguoi_choi, y_nguoi_choi - 1);
        vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi; // dua vat_the moi vao mang
        vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi - 1;
    }
    else if (huong_nguoi_choi == 2 && kiem_tra_vi_tri_vat_the(x_nguoi_choi - 1, y_nguoi_choi) != 1 && x_nguoi_choi != 7)
    {
        gotoxy(x_nguoi_choi - 1, y_nguoi_choi);
        vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi - 1;
        vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi;
    }
    else if (huong_nguoi_choi == 3 && kiem_tra_vi_tri_vat_the(x_nguoi_choi, y_nguoi_choi + 1) != 1 && y_nguoi_choi != 20)
    {
        gotoxy(x_nguoi_choi, y_nguoi_choi + 1);
        vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi;
        vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi + 1;
    }
    else if (huong_nguoi_choi == 4 && kiem_tra_vi_tri_vat_the(x_nguoi_choi + 1, y_nguoi_choi) != 1 && x_nguoi_choi != 52)
    {
        gotoxy(x_nguoi_choi + 1, y_nguoi_choi);
        vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi + 1;
        vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi;
    }
    else
        return;

    printf("G");
    strcpy(hanh_dong, "Ban vua dat go");
    strcpy(vat_the[so_luong_vat_the].ten, "khoi go");
    so_luong_vat_the++;
    them_vat_pham(1, -1);
    bo_lo();
}

int kiem_tra_vi_tri_vat_the(int x, int y) // kiem tra vi tri x y co vat the hay khong
{
    for (i = 0; i < so_luong_vat_the; i++)
    {
        if (x == vat_the[i].toa_do_x && y == vat_the[i].toa_do_y)
            return 1;
    }
    return 0;
}

void bo_lo() // ham kiem tra toa do cua mang vat_the co rong hay khong
{
    so_luong_vat_the--;
    for (i = 0; i < so_luong_vat_the; i++)
    {
        if (vat_the[i].toa_do_x == NULL && vat_the[i].toa_do_y == NULL)
        {
            vat_the[i].toa_do_x = vat_the[so_luong_vat_the].toa_do_x;
            vat_the[i].toa_do_y = vat_the[so_luong_vat_the].toa_do_y;
            strcpy(vat_the[i].ten, vat_the[so_luong_vat_the].ten);
            return;
        }
    }
    so_luong_vat_the++;
}

void chuyen_chuc_nang() // xoa man hinh de hien thi menu khac cua game
{
    for (j = 5; j <= 21; j++)
    {
        gotoxy(56, j);
        for (i = 1; i <= 55; i++)
            printf(" ");
    }
}

void tao_moi_vat_pham(int id, int so_luong) // tao mot vat pham ma nguoi choi chua co
{
    if (id == 1)
    {
        vat_pham[so_luong_vat_pham].id = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Khoi go");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0;
    }
    if (id == 2)
    {
        vat_pham[so_luong_vat_pham].id = 2;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Cuc da");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0;
    }
    if (id == 3)
    {
        vat_pham[so_luong_vat_pham].id = 3;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Trai nho");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0;
    }
    so_luong_vat_pham++;
}

void them_vat_pham(int id, int so_luong) // them vat pham vua nhan vao nguoi choi
{
    if (so_luong_vat_pham == 0)
    {
        tao_moi_vat_pham(id, so_luong);
        return;
    }
    else
    {
        for (i = 0; i < so_luong_vat_pham; i++)
        {
            if (id == vat_pham[i].id) // kiem tra vat pham nay nguoi choi co so huu chua
            {
                vat_pham[i].so_luong += so_luong;
                if (vat_pham[i].so_luong == 0)
                    xoa_vat_pham(i);
                return;
            }
        }
    }

    tao_moi_vat_pham(id, so_luong);
}

void xoa_vat_pham(int vi_tri_xoa) // xoa vat pham da het va dua cac vat pham phia sau len
{
    for (i = vi_tri_xoa; i < so_luong_vat_pham; i++)
    {
        vat_pham[i].id = vat_pham[i + 1].id;
        strcpy(vat_pham[i].ten, vat_pham[i + 1].ten);
        vat_pham[i].so_luong = vat_pham[i + 1].so_luong;
        vat_pham[i].the = vat_pham[i + 1].the;
    }
    so_luong_vat_pham--;
}