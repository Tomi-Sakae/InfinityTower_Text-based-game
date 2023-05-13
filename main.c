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
int x_tam, y_tam, i, huong_nguoi_choi, do_dai_chuoi_hanh_dong, do_dai_chuoi_tam_nhin;
int do_dai_chuoi_tay_phai;
char hanh_dong[100] = "Ban dang dung yen";
char tam_nhin[100];
char tay_phai[100] = "Tay phai: Go x ";
int so_luong_vat_the = 0;
int so_luong_go = 0;
char nguoi_choi = '>';
// int gio = 6;
// int phut = 0;

/*
void *thoi_gian(void *vargp)
{
    while (1)
    {

    }
    return NULL;
}
*/

typedef struct doi_tuong
{
    char ten[100];
    int toa_do_x;
    int toa_do_y;
} doi_tuong;

doi_tuong vat_the[1000];

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

void di_chuyen_va_hanh_dong();
void va_cham();
void thuc_hien_hanh_dong();
int kiem_tra_vat_the();
void thuc_hien_dat_khoi();
int kiem_tra_vi_tri_vat_the(int x, int y);

int main()
{
    srand((int)time(0));
    so_luong_vat_the = random(5, 10);

    x_nguoi_choi = random(7, 52);
    y_nguoi_choi = random(6, 20);

    for (i = 0; i < so_luong_vat_the; i++)
    {
        vat_the[i].toa_do_x = random(7, 52);
        vat_the[i].toa_do_y = random(6, 20);

        if (vat_the[i].toa_do_x == x_nguoi_choi && vat_the[i].toa_do_y == y_nguoi_choi)
            x_nguoi_choi--; // sua loi cay xuat hien ngay vi tri nguoi choi

        strcpy(vat_the[i].ten, "cai cay");
        gotoxy(vat_the[i].toa_do_x, vat_the[i].toa_do_y); // tao cay o vi tri ngau nhien
        printf("C");                                      // cai cay
    }

    int y = 6;
    // thiet ke khung tro choi chinh
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
    
    while (1)
    {

        /*
        gotoxy(0, 0);
        if (phut >= 10)
            printf("%d:%d", gio, phut);
        else
            printf("%d:0%d", gio, phut);
        */
        // pthread_t thread_id;
        // pthread_create(&thread_id, NULL, thoi_gian, NULL);

        gotoxy(x_nguoi_choi, y_nguoi_choi); // toa do nguoi choi
        printf("%c", nguoi_choi);           // nguoi choi

        gotoxy(5, 23);
        for (i = 0; i <= do_dai_chuoi_hanh_dong; i++) // xoa chuoi hanh dong truoc do
            printf(" ");

        gotoxy(5, 3);
        for (i = 0; i <= do_dai_chuoi_tam_nhin; i++) // xoa chuoi tam nhin truoc do
            printf(" ");

        gotoxy(56, 6);
        for (i = 0; i <= do_dai_chuoi_tay_phai; i++) // xoa chuoi tay phai truoc do
            printf(" ");

        gotoxy(5, 3);
        puts(tam_nhin);
        do_dai_chuoi_tam_nhin = strlen(tam_nhin); // hien thi chuoi tam nhin cua nhan vat

        gotoxy(5, 23);
        puts(hanh_dong);
        do_dai_chuoi_hanh_dong = strlen(hanh_dong); // hien thi chuoi hanh dong cua nhan vat

        gotoxy(56, 6);
        puts(tay_phai); // hien thi chuoi tay phai
        gotoxy(71, 6);
        printf("%d", so_luong_go);

        int temp, count = 0;
        temp = so_luong_go;
        while (temp != 0) // nhom lenh tim so luong chu so de xoa cho hop ly
        {
            count++;
            temp = temp / 10;
        }

        do_dai_chuoi_tay_phai = strlen(tay_phai) + count;

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
        if (so_luong_go != 0)
            thuc_hien_dat_khoi();
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
    gotoxy(vat_the[i].toa_do_x, vat_the[i].toa_do_y); // xoa cay o vi tri vua chat
    printf(" ");

    vat_the[i].toa_do_x = NULL;
    vat_the[i].toa_do_y = NULL;

    if (strcmp(vat_the[i].ten, "cai cay") == 0)
    {
        strcpy(hanh_dong, "Ban vua chat cay");
        so_luong_go += 4;
    }

    if (strcmp(vat_the[i].ten, "go") == 0)
    {
        strcpy(hanh_dong, "Ban vua chat go");
        so_luong_go++;
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
                return 4; // tra ve huong cua vat the so voi nguoi choi
            }
        }
        if (huong_nguoi_choi == 2)
        {
            if (vat_the[i].toa_do_x == x_nguoi_choi - 1 && vat_the[i].toa_do_y == y_nguoi_choi)
            {
                strcat(tam_nhin, vat_the[i].ten);
                return 2;
            }
        }
        if (huong_nguoi_choi == 3)
        {
            if (vat_the[i].toa_do_x == x_nguoi_choi && vat_the[i].toa_do_y == y_nguoi_choi + 1)
            {
                strcat(tam_nhin, vat_the[i].ten);
                return 3;
            }
        }
        if (huong_nguoi_choi == 1)
        {
            if (vat_the[i].toa_do_x == x_nguoi_choi && vat_the[i].toa_do_y == y_nguoi_choi - 1)
            {
                strcat(tam_nhin, vat_the[i].ten);
                return 1;
            }
        }
    }
    strcpy(tam_nhin, " "); // nguoi choi khong o gan bat ky vat the nao
    return 0;
}

void thuc_hien_dat_khoi()
{
    if ((x_nguoi_choi < 52 && x_nguoi_choi > 7) && (y_nguoi_choi < 20 && y_nguoi_choi > 6)) // kiem tra vi tri dat khoi cua nguoi choi
    {
        if (huong_nguoi_choi == 1 && kiem_tra_vi_tri_vat_the(x_nguoi_choi, y_nguoi_choi - 1) != 1) // kiem tra vi tri dat khoi co trung voi khoi da co hay khong
        {
            gotoxy(x_nguoi_choi, y_nguoi_choi - 1);
            vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi; // dua vat_the moi vao mang
            vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi - 1;
        }
        else if (huong_nguoi_choi == 2 && kiem_tra_vi_tri_vat_the(x_nguoi_choi - 1, y_nguoi_choi) != 1)
        {
            gotoxy(x_nguoi_choi - 1, y_nguoi_choi);
            vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi - 1;
            vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi;
        }
        else if (huong_nguoi_choi == 3 && kiem_tra_vi_tri_vat_the(x_nguoi_choi, y_nguoi_choi + 1) != 1)
        {
            gotoxy(x_nguoi_choi, y_nguoi_choi + 1);
            vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi;
            vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi + 1;
        }
        else if (huong_nguoi_choi == 4 && kiem_tra_vi_tri_vat_the(x_nguoi_choi + 1, y_nguoi_choi) != 1)
        {
            gotoxy(x_nguoi_choi + 1, y_nguoi_choi);
            vat_the[so_luong_vat_the].toa_do_x = x_nguoi_choi + 1;
            vat_the[so_luong_vat_the].toa_do_y = y_nguoi_choi;
        }
        else
            return 0;

        printf("G");
        strcpy(hanh_dong, "Ban vua dat go");
        strcpy(vat_the[so_luong_vat_the].ten, "go");
        so_luong_vat_the++;
        so_luong_go--;
    }
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