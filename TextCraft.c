#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "du_lieu.h"

char lua_chon;
int x_tam, y_tam, i, j, i_tam, do_dai_chuoi[100];
int tiep_tuc = 0;

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

void game_over() // ket thuc game
{
    system("cls");
    printf("Game Over!");
    exit(1);
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

    if (the_luc <= 0) // khi het the luc moi lan di chuyen tru 5 mau
    {
        mau -= 5;
        the_luc = 0;
    }

    if (the_luc > 100)
        the_luc = 100;

    if (mau <= 0) // het mau thi ket thuc game
        game_over();

    gotoxy(56, 6);
    printf("Mau: %d", mau); // hien mau
    do_dai_chuoi[3] = so_luong_chu_so(mau, 0);

    gotoxy(56, 8);
    printf("The luc: %d", the_luc); // hien the luc
    do_dai_chuoi[4] = so_luong_chu_so(the_luc, 0);

    if (vat_pham[trang_bi].so_luong != 0) // bien trang bi cho biet vat pham nao nguoi choi da trang bi
        strcpy(tay_phai, vat_pham[trang_bi].ten);
    else
        strcpy(tay_phai, "Khong");
    gotoxy(56, 10);
    printf("Tay phai: ");
    puts(tay_phai); // hien thi chuoi tay phai
    if (vat_pham[trang_bi].so_luong != 0)
    {
        gotoxy(66 + strlen(tay_phai), 10);
        if (sua_loi_file == 0) // sua loi tai du lieu bi du ra \n
            printf(" x ");
        else
            printf("x ");
        if (sua_loi_file == 0)
            gotoxy(66 + strlen(tay_phai) + 3, 10);
        else
            gotoxy((66 + strlen(tay_phai) + 3) - 1, 10);
        printf("%d", vat_pham[trang_bi].so_luong);
    }
    do_dai_chuoi[5] = strlen(tay_phai) + so_luong_chu_so(vat_pham[trang_bi].so_luong, 0) + 3;
}

void giao_dien_game_chinh() // ham hien thi chuoi va xoa chuoi
{
    gotoxy(5, 23);
    for (i = 0; i <= do_dai_chuoi[0]; i++) // xoa chuoi hanh dong truoc do
        printf(" ");

    gotoxy(5, 3);
    for (i = 0; i <= do_dai_chuoi[1]; i++) // xoa chuoi tam nhin truoc do
        printf(" ");

    if (gio >= 10)
        gotoxy(20, 0);
    else
        gotoxy(19, 0);
    for (i = 0; i <= do_dai_chuoi[2]; i++) // xoa chuoi buoi truoc do
        printf(" ");

    gotoxy(20, 2);
    for (i = 0; i <= do_dai_chuoi[6]; i++) // xoa chuoi hien thi truoc do
        printf(" ");
    if (do_dai_chuoi[6] > 1)
        strcpy(hien_thi, " ");

    gotoxy(5, 23);
    puts(hanh_dong);
    do_dai_chuoi[0] = strlen(hanh_dong); // hien thi chuoi hanh dong cua nhan vat

    gotoxy(5, 3);
    puts(tam_nhin);
    do_dai_chuoi[1] = strlen(tam_nhin); // hien thi chuoi tam nhin cua nhan vat
    if (i_tam != 0)
    {
        gotoxy(5 + do_dai_chuoi[1], 3);
        printf(" %d/%d", vat_the[i_tam].do_ben, vat_the[i_tam].do_ben_toi_da);
        do_dai_chuoi[1] += 1 + so_luong_chu_so(vat_the[i_tam].do_ben, 0) + 1 + so_luong_chu_so(vat_the[i_tam].do_ben_toi_da, 0);
    }

    if (phut >= 60)
    {
        gio++;
        phut = 0;
    }
    if (gio >= 24)
        gio = 0;
    if (gio >= 3 && gio < 11)
        strcpy(buoi, "Sang");
    if (gio >= 11 && gio < 13)
        strcpy(buoi, "Trua");
    if (gio >= 13 && gio < 18)
        strcpy(buoi, "Chieu");
    if (gio >= 18 && gio < 24)
        strcpy(buoi, "Toi");
    if (gio >= 0 && gio < 3)
        strcpy(buoi, "Khuya");
    gotoxy(0, 0);
    printf("Thoi gian: ");
    printf("%d:", gio);
    if (phut >= 10)
        printf("%d", phut);
    else
        printf("0%d", phut);
    printf(" - ");
    puts(buoi);
    do_dai_chuoi[2] = strlen(buoi); // hien thi chuoi buoi
    phut += 1;

    gotoxy(0, 1);
    printf("Thoi tiet: ");
    puts(thoi_tiet);

    gotoxy(20, 2);
    puts(hien_thi); // hien chuoi hien thi
    do_dai_chuoi[6] = strlen(hien_thi);

    if (strcmp(hien_thi, "Xoa du lieu thanh cong! - Vui long thoat ra de choi lai") == 0)
        exit(1);
}

void tui_do() // giao dien tui do
{
    int y_chon = 7;
    int y = 7;
    int vi_tri = 0;
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
            if (sua_loi_file == 0)
                printf(" x ");
            else
                printf("x ");
            if (sua_loi_file == 0)
                gotoxy(58 + strlen(vat_pham[i].ten) + 3, y);
            else
                gotoxy((58 + strlen(vat_pham[i].ten) + 3) - 1, y);
            printf("%d", vat_pham[i].so_luong);
            y += 2;
        }
    }
    while (1) // vong lap lua chon vat pham
    {
        if (vat_pham[0].so_luong != 0) // fix loi du nut di chuyen khi khong co do
        {
            gotoxy(56, y_chon);
            printf("->");
        }
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
                vi_tri--;
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
                vi_tri++;
            }
            break;
        }
        case 'k':
        {
            trang_bi = y_chon - (7 + vi_tri); // du lieu trang bi duoc lay tu lua chon cua nguoi choi
            return;
            break;
        }
        }
    }
}

void cai_dat() // phan cai dat cua game
{
    gotoxy(56, 5);
    printf("Cai dat: ");
    gotoxy(58, 7);
    printf("Luu du lieu");
    gotoxy(58, 9);
    printf("Xoa du lieu");

    int y_chon = 7;
    while (1)
    {
        gotoxy(56, y_chon);
        printf("->");
        char lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 't':
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
            if (y_chon < 9)
            {
                gotoxy(56, y_chon);
                printf("  ");
                y_chon += 2;
            }
            break;
        }
        case 'k':
        {
            if (y_chon == 7)
            {
                luu_du_lieu();
                strcpy(hien_thi, "Luu du lieu thanh cong!");
                return;
            }
            if (y_chon == 9)
            {
                xoa_du_lieu();
                strcpy(hien_thi, "Xoa du lieu thanh cong! - Vui long thoat ra de choi lai");
                return;
            }
            break;
        }
        }
    }
}

void man_hinh_tieu_de() // man hinh xuat hien khi moi vao game
{
    int y_chon = 7;
    while (1)
    {
        gotoxy(5, 5);
        printf("TextCraft Beta V0.2");
        gotoxy(7, 7);
        printf("Choi moi");
        gotoxy(7, 9);
        printf("Tiep tuc");
        gotoxy(7, 11);
        printf("Huong dan");
        gotoxy(7, 13);
        printf("Thoat");
        gotoxy(5, y_chon);
        printf("->");
        char lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'w':
        {
            if (y_chon > 7)
            {
                gotoxy(5, y_chon);
                printf("  ");
                y_chon -= 2;
            }
            break;
        }
        case 's':
        {
            if (y_chon < 13)
            {
                gotoxy(5, y_chon);
                printf("  ");
                y_chon += 2;
            }
            break;
        }
        case 'k':
        {
            if (y_chon == 7)
            {
                xoa_du_lieu();
                system("cls");
                return;
            }
            if (y_chon == 9)
            {
                system("cls");
                char kt_tam;
                f = fopen("save.txt", "r");
                kt_tam = fgetc(f);
                if (kt_tam == 'n') // kiem tra du lieu cua game co rong hay khong
                    printf("Khong co du lieu da luu truoc do...");
                else
                {
                    tiep_tuc = 1;
                    tai_du_lieu();
                    system("cls");
                    return;
                }

                getch();
                system("cls");
            }
            if (y_chon == 11)
            {
                system("cls");
                gotoxy(5, 5);
                printf("Huong dan: ");
                gotoxy(7, 7);
                printf("Dung cac nut w - a - s - d de di chuyen nhan vat.");
                gotoxy(7, 9);
                printf("Dung cac phim mui ten de dieu chinh huong cua nhan vat.");
                gotoxy(7, 11);
                printf("Dung nut k de tuong tac voi vat the.");
                gotoxy(7, 13);
                printf("Dung nut p de dung vat pham.");
                gotoxy(7, 15);
                printf("Dung nut e de mo tui do");
                gotoxy(7, 17);
                printf("Tai cac giao dien menu dung w - s hoac a - d de di chuyen mui ten");
                gotoxy(7, 18);
                printf("va dung nut k de lua chon tinh nang ma mui ten chi vao.");
                getch();
                system("cls");
            }
            if (y_chon == 13)
                exit(1);
            break;
        }
        }
    }
}

void tai_vat_the() // tai hien thi vat the khi tai ban do
{
    for (i = 0; i < so_luong_vat_the; i++)
    {
        gotoxy(vat_the[i].toa_do_x, vat_the[i].toa_do_y);
        if (vat_the[i].id == 1)
            printf("C");
        if (vat_the[i].id == 2)
            printf("D");
        if (vat_the[i].id == 3)
            printf("N");
        if (vat_the[i].id == 4)
            printf("M");
    }
}

void tai_thoi_gian_hoi() // tai thoi gian hoi phuc cua cac vat the
{
    if (so_luong_hoi > 0)
    {
        int tam = so_luong_hoi;
        for (i = 0; i < tam; i++)
        {
            tg_hoi_vat_the[i].thoi_gian--;
            if (tg_hoi_vat_the[i].thoi_gian == 0)
            {
                gotoxy(vat_the[tg_hoi_vat_the[i].vi_tri].toa_do_x, vat_the[tg_hoi_vat_the[i].vi_tri].toa_do_y);
                printf(" ");
                if (tg_hoi_vat_the[i].id == 1)
                {
                    gotoxy(vat_the[tg_hoi_vat_the[i].vi_tri].toa_do_x, vat_the[tg_hoi_vat_the[i].vi_tri].toa_do_y);
                    printf("C");
                    vat_the[tg_hoi_vat_the[i].vi_tri].id = 1;
                    strcpy(vat_the[tg_hoi_vat_the[i].vi_tri].ten, "cai cay");
                    vat_the[tg_hoi_vat_the[i].vi_tri].do_ben_toi_da = 10;
                    vat_the[tg_hoi_vat_the[i].vi_tri].do_ben = vat_the[tg_hoi_vat_the[i].vi_tri].do_ben_toi_da;
                }
                for (j = i; j < tam; j++)
                {
                    tg_hoi_vat_the[j].id = tg_hoi_vat_the[j + 1].id;
                    tg_hoi_vat_the[j].thoi_gian = tg_hoi_vat_the[j + 1].thoi_gian;
                    tg_hoi_vat_the[j].vi_tri = tg_hoi_vat_the[j + 1].vi_tri;
                }
                tam--;
                i--;
            }
        }
        so_luong_hoi = tam;
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
void an_thuc_an();
void xoa_vat_the();

int main()
{
    man_hinh_tieu_de();
    if (tiep_tuc == 0)
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
                vat_the[i].do_ben_toi_da = 10;
                vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
                printf("C"); // cai cay
            }
            if (vat_the_ban_dau == 2)
            {
                strcpy(vat_the[i].ten, "cuc da");
                vat_the[i].id = 2;
                vat_the[i].do_ben_toi_da = 10;
                vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
                printf("D"); // cuc da
            }
            if (vat_the_ban_dau == 3)
            {
                strcpy(vat_the[i].ten, "bui nho");
                vat_the[i].id = 3;
                vat_the[i].do_ben_toi_da = 4;
                vat_the[i].do_ben = vat_the[i].do_ben_toi_da;
                printf("N"); // bui nho
            }
        }
    }
    if (tiep_tuc == 1)
        tai_vat_the();
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
        if (vat_pham[trang_bi].the == 2)
            thuc_hien_dat_khoi();
        if (vat_pham[trang_bi].the == 1 && the_luc < 100)
            an_thuc_an();
        break;
    }
    case 'e':
    {
        chuyen_chuc_nang();
        tui_do();
        chuyen_chuc_nang();
        break;
    }
    case 't':
    {
        chuyen_chuc_nang();
        cai_dat();
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
    tai_thoi_gian_hoi();
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

void xoa_vat_the()
{
    gotoxy(vat_the[i_tam].toa_do_x, vat_the[i_tam].toa_do_y); // bien i tam duoc lay tu ham kiem tra vat the
    printf(" ");                                              // xoa cay o vi tri vua chat

    vat_the[i_tam].toa_do_x = 0;
    vat_the[i_tam].toa_do_y = 0;
}

void thuc_hien_hanh_dong()
{
    if (vat_the[i_tam].id == 1)
    {
        the_luc -= 5;
        strcpy(hanh_dong, "Ban vua chat cay | + 1 khoi go");
        vat_the[i_tam].do_ben--;
        if (vat_the[i_tam].do_ben == 0)
        {
            strcpy(hanh_dong, "Ban vua chat gay ca cay | + 11 khoi go | + 4 mam cay");
            xoa_vat_the();
            them_vat_pham(1, 11);
            them_vat_pham(4, 4);
            return;
        }
        them_vat_pham(1, 1);
    }

    if (vat_the[i_tam].id == 4)
    {
        strcpy(hanh_dong, "Ban vua nho mam cay | + 1 mam cay");
        them_vat_pham(4, 1);
        int tam = so_luong_hoi;
        for (i = 0; i < tam; i++)
        {
            if (tg_hoi_vat_the[i].vi_tri == i_tam)
            {
                for (j = i; j < tam; j++)
                {
                    tg_hoi_vat_the[j].id = tg_hoi_vat_the[j + 1].id;
                    tg_hoi_vat_the[j].thoi_gian = tg_hoi_vat_the[j + 1].thoi_gian;
                    tg_hoi_vat_the[j].vi_tri = tg_hoi_vat_the[j + 1].vi_tri;
                }
                i--;
                tam--;
            }
        }
        so_luong_hoi = tam;
    }

    if (vat_the[i_tam].id == 2)
    {
        the_luc -= 10;
        strcpy(hanh_dong, "Ban vua dao da | + 1 cuc da");
        vat_the[i_tam].do_ben--;
        if (vat_the[i_tam].do_ben == 0)
        {
            strcpy(hanh_dong, "Ban vua dao be cuc da | + 5 cuc da");
            xoa_vat_the();
            them_vat_pham(2, 5);
            return;
        }
        them_vat_pham(2, 1);
    }

    if (vat_the[i_tam].id == 3)
    {
        strcpy(hanh_dong, "Ban vua nhat nho | + 1 chum nho");
        vat_the[i_tam].do_ben--;
        if (vat_the[i_tam].do_ben == 0)
        {
            strcpy(hanh_dong, "Ban vua pha ca bui nho");
            xoa_vat_the();
        }
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
    i_tam = 0;
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

    if (vat_pham[trang_bi].id == 4)
    {
        printf("M");
        strcpy(hanh_dong, "Ban vua dat mam cay");
        strcpy(vat_the[so_luong_vat_the].ten, "mam cay");
        vat_the[so_luong_vat_the].id = 4;
        vat_the[so_luong_vat_the].do_ben_toi_da = 1;
        vat_the[so_luong_vat_the].do_ben = vat_the[so_luong_vat_the].do_ben_toi_da;
        so_luong_vat_the++;
        them_vat_pham(4, -1);
        tg_hoi_vat_the[so_luong_hoi].thoi_gian = random(5, 10); // tao thoi gian hoi cho vat the
        tg_hoi_vat_the[so_luong_hoi].thoi_gian *= 30;           // chuyen gio thanh phut
        tg_hoi_vat_the[so_luong_hoi].id = 1;
        tg_hoi_vat_the[so_luong_hoi].vi_tri = so_luong_vat_the;
        bo_lo();
        so_luong_hoi++;
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

void bo_lo() // ham kiem tra toa do cua mang vat_the co rong hay khong
{
    so_luong_vat_the--;
    for (i = 0; i < so_luong_vat_the; i++)
    {
        if (vat_the[i].toa_do_x == 0 && vat_the[i].toa_do_y == 0)
        {
            vat_the[i].toa_do_x = vat_the[so_luong_vat_the].toa_do_x;
            vat_the[i].toa_do_y = vat_the[so_luong_vat_the].toa_do_y;
            strcpy(vat_the[i].ten, vat_the[so_luong_vat_the].ten);
            vat_the[i].id = vat_the[so_luong_vat_the].id;
            vat_the[i].do_ben = vat_the[so_luong_vat_the].do_ben;
            vat_the[i].do_ben_toi_da = vat_the[so_luong_vat_the].do_ben_toi_da;
            tg_hoi_vat_the[so_luong_hoi].vi_tri = i; // cap nhat vi tri moi neu dung ham bo_lo
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
        if (sua_loi_file == 0) // sua loi vat pham moi dua vao khi tai du lieu xung dot voi sua loi file thieu \n
            strcpy(vat_pham[so_luong_vat_pham].ten, "Khoi go");
        else
            strcpy(vat_pham[so_luong_vat_pham].ten, "Khoi go\n");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0;
    }
    if (id == 2)
    {
        vat_pham[so_luong_vat_pham].id = 2;
        if (sua_loi_file == 0)
            strcpy(vat_pham[so_luong_vat_pham].ten, "Cuc da");
        else
            strcpy(vat_pham[so_luong_vat_pham].ten, "Cuc da\n");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0;
    }
    if (id == 3)
    {
        vat_pham[so_luong_vat_pham].id = 3;
        if (sua_loi_file == 0)
            strcpy(vat_pham[so_luong_vat_pham].ten, "Chum nho");
        else
            strcpy(vat_pham[so_luong_vat_pham].ten, "Chum nho\n");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 1;
    }
    if (id == 4)
    {
        vat_pham[so_luong_vat_pham].id = 4;
        if (sua_loi_file == 0)
            strcpy(vat_pham[so_luong_vat_pham].ten, "Mam cay");
        else
            strcpy(vat_pham[so_luong_vat_pham].ten, "Mam cay\n");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 2;
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
    trang_bi = so_luong_vat_pham;
}

void an_thuc_an() // ham an thuc an
{
    if (vat_pham[trang_bi].id == 3)
    {
        the_luc += 10;
        vat_pham[trang_bi].so_luong--;
        if (vat_pham[trang_bi].so_luong == 0)
            xoa_vat_pham(trang_bi);
        strcpy(hanh_dong, "Ban vua an nho");
    }
}