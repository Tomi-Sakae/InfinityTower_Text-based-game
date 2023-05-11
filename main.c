#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

char lua_chon;
int x_nguoi_choi = 10;
int y_nguoi_choi = 10;
int x_tam, y_tam, i, do_dai_chuoi_hanh_dong, do_dai_chuoi_tam_nhin;
int cay_toa_do_x[100];
int cay_toa_do_y[100];
char hanh_dong[100] = "Ban dang dung yen";
char tam_nhin[100];
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

int main()
{
    srand((int)time(0));
    for (i = 0; i < 3; i++)
    {
        cay_toa_do_x[i] = random(7, 52);
        cay_toa_do_y[i] = random(6, 20);
        gotoxy(cay_toa_do_x[i], cay_toa_do_y[i]); // tao cay o vi tri ngau nhien
        printf("C");                              // cai cay
    }

    while (1)
    {
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
        printf("@");                        // nguoi choi

        gotoxy(5, 23);
        for (i = 0; i <= do_dai_chuoi_hanh_dong; i++) // xoa chuoi hanh dong truoc do
            printf(" ");
        
        gotoxy(5, 3);
        for (i = 0; i <= do_dai_chuoi_tam_nhin; i++) // xoa chuoi tam nhin truoc do
            printf(" ");

        gotoxy(5, 3);
        puts(tam_nhin);
        do_dai_chuoi_tam_nhin = strlen(tam_nhin); // hien thi chuoi tam nhin cua nhan vat

        gotoxy(5, 23);
        puts(hanh_dong);
        do_dai_chuoi_hanh_dong = strlen(hanh_dong); // hien thi chuoi hanh dong cua nhan vat

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
        break;
    }
    case 'a':
    {
        x_nguoi_choi--;
        strcpy(hanh_dong, "Ban vua sang trai");
        break;
    }
    case 's':
    {
        y_nguoi_choi++;
        strcpy(hanh_dong, "Ban vua di xuong");
        break;
    }
    case 'd':
    {
        x_nguoi_choi++;
        strcpy(hanh_dong, "Ban vua sang phai");
        break;
    }
    case 'k':
    {
        if (kiem_tra_vat_the() == 1)
            thuc_hien_hanh_dong();
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
    for (i = 0; i < 3; i++)
    {
        if (x_nguoi_choi == cay_toa_do_x[i] && y_nguoi_choi == cay_toa_do_y[i])
        {
            x_nguoi_choi = x_tam;
            y_nguoi_choi = y_tam;
        }
    }
}

void thuc_hien_hanh_dong()
{
    gotoxy(cay_toa_do_x[i], cay_toa_do_y[i]); // xoa cay o vi tri vua chat
    printf(" ");
    cay_toa_do_x[i] = NULL;
    cay_toa_do_y[i] = NULL;
    strcpy(hanh_dong, "Ban vua chat cay");
}

int kiem_tra_vat_the() // kiem tra vat the o gan nguoi choi
{
    for (i = 0; i < 3; i++)
    {
        if (cay_toa_do_x[i] == x_nguoi_choi + 1 && cay_toa_do_y[i] == y_nguoi_choi)
        {
            strcpy(tam_nhin, "Ben phai ban la cai cay"); // vi tri cua vat the so voi nguoi choi
            return 1;
        }
        if (cay_toa_do_x[i] == x_nguoi_choi - 1 && cay_toa_do_y[i] == y_nguoi_choi)
        {
            strcpy(tam_nhin, "Ben trai ban la cai cay");
            return 1;
        }
        if (cay_toa_do_x[i] == x_nguoi_choi && cay_toa_do_y[i] == y_nguoi_choi + 1)
        {
            strcpy(tam_nhin, "Ben duoi ban la cai cay");
            return 1;
        }
        if (cay_toa_do_x[i] == x_nguoi_choi && cay_toa_do_y[i] == y_nguoi_choi - 1)
        {
            strcpy(tam_nhin, "Ben tren ban la cai cay");
            return 1;
        }
    }
    strcpy(tam_nhin, " "); // nguoi choi khong o gan bat ky vat the nao
    return 0;
}