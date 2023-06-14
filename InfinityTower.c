#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "du_lieu.h"

char lua_chon;
int x_tam, y_tam, i, j, i_tam, do_dai_chuoi[100];
int tiep_tuc = 0;
int menu = 0, kt_menu = 0;
int kt_menu_tui_do = 0;
int hien_thi_lai_vat_the = 0;            // bien kiem tra dieu kien de hien thi lai vat the
char bieu_tuong_tam;                     // bieu tuong cua vat the se hien thi
int fix_dung_tren_vat_the_lien_tiep = 0; // bien sua loi khi dung tren vat the va di chuyen sang vat the dung len duoc

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
int kiem_tra_vat_pham(int id, int so_luong);
void tuong_tac_vat_the();
void xoa_vat_pham_ruong(int vi_tri_xoa);

void game_over() // ket thuc game
{
    system("cls");
    gotoxy(5, 5);
    printf("Game Over!");
    sleep(5);
    exit(1);
}

void them_thong_tin_nhan_vat() // phan thong tin co ban cua nhan vat
{
    gotoxy(56, 5);
    printf("Thong tin nhan vat: ");
    gotoxy(58, 7);
    printf("Doi: %d", do_doi);
    gotoxy(58, 9);
    printf("Khat: %d", do_khat);
    while (1)
    {
        char lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'i':
        {
            return;
            break;
        }
        }
    }
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
    if (do_doi <= 0)
    {
        mau -= 5;
        do_doi = 0;
    }
    if (do_khat <= 0)
    {
        mau -= 5;
        do_khat = 0;
    }

    if (the_luc > 100)
        the_luc = 100;
    if (do_doi > 100)
        do_doi = 100;
    if (do_khat > 100)
        do_khat = 100;

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
    if (vat_pham[trang_bi].so_luong != 0 && vat_pham[trang_bi].gop == 1)
    {
        gotoxy(66 + strlen(tay_phai), 10);
        printf(" x ");
        gotoxy(66 + strlen(tay_phai) + 3, 10);
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

    gotoxy(5, 23);
    puts(hanh_dong);
    do_dai_chuoi[0] = strlen(hanh_dong); // hien thi chuoi hanh dong cua nhan vat

    gotoxy(5, 3);
    puts(tam_nhin);
    do_dai_chuoi[1] = strlen(tam_nhin); // hien thi chuoi tam nhin cua nhan vat
    if (i_tam != -1)
    {
        gotoxy(5 + do_dai_chuoi[1], 3);
        printf(" %d/%d", vat_the[i_tam].do_ben, vat_the[i_tam].do_ben_toi_da);
        do_dai_chuoi[1] += 1 + so_luong_chu_so(vat_the[i_tam].do_ben, 0) + 1 + so_luong_chu_so(vat_the[i_tam].do_ben_toi_da, 0);
    }

    if (phut >= 60)
    {
        gio++;
        phut = 0;
        do_doi -= 5;
        do_khat -= 10;
    }
    if (do_doi <= 60 && do_doi > 30 && kiem_tra_hien_thi[0] == -1)
        kiem_tra_hien_thi[0] = 1;
    if (kiem_tra_hien_thi[0] == 1)
    {
        strcpy(hien_thi, "Ban dang cam thay doi!");
        kiem_tra_hien_thi[0] = 0;
    }
    if (do_doi <= 30 && kiem_tra_hien_thi[0] == 0)
        kiem_tra_hien_thi[0] = 2;
    if (kiem_tra_hien_thi[0] == 2)
    {
        strcpy(hien_thi, "Ban dang cam thay rat doi!!");
        kiem_tra_hien_thi[0] = -2;
    }
    if (do_doi > 60 && (kiem_tra_hien_thi[0] == -2 || kiem_tra_hien_thi[0] == 0))
        kiem_tra_hien_thi[0] = -1;
    if (do_khat <= 60 && do_khat > 30 && kiem_tra_hien_thi[1] == -1)
        kiem_tra_hien_thi[1] = 1;
    if (kiem_tra_hien_thi[1] == 1)
    {
        strcpy(hien_thi, "Ban dang cam thay khat!");
        kiem_tra_hien_thi[1] = 0;
    }
    if (do_khat <= 30 && kiem_tra_hien_thi[1] == 0)
        kiem_tra_hien_thi[1] = 2;
    if (kiem_tra_hien_thi[1] == 2)
    {
        strcpy(hien_thi, "Ban dang cam thay rat khat!!");
        kiem_tra_hien_thi[1] = -2;
    }
    if (do_khat > 60 && (kiem_tra_hien_thi[1] == -2 || kiem_tra_hien_thi[1] == 0))
        kiem_tra_hien_thi[1] = -1;
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
    {
        sleep(5);
        exit(1);
    }
}

int chon_vat_pham = 0;
void chon_so_luong_vat_pham(int vi_tri) // ham cho phep nguoi choi chon so luong vat pham
{
    int so_luong_can = 1;
    char lua_chon_menu;
    int bo_qua = 0;
    gotoxy(56, 5);
    printf("Vui long chon so luong: ");
    while (1)
    {
        gotoxy(58, 7);
        if (chon_vat_pham == 1)
        {
            puts(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten);
            gotoxy(58 + strlen(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten), 7);
            if (so_luong_can > 1)
                printf(" <");
            printf(" %d/", so_luong_can);
            if (so_luong_can > 1)
                gotoxy(58 + strlen(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten) + 4 + so_luong_chu_so(so_luong_can, 0), 7);
            else
                gotoxy(58 + strlen(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten) + 2 + so_luong_chu_so(so_luong_can, 0), 7);
            printf("%d", vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong);
            if (so_luong_can < vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong - 1)
            {
                if (so_luong_can == 1)
                    gotoxy((58 + strlen(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + 2 + so_luong_chu_so(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong, 0)) - 2, 7);
                else
                    gotoxy(58 + strlen(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + 2 + so_luong_chu_so(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong, 0), 7);
                printf(" >");
            }
        }
        if (chon_vat_pham == 2)
        {
            puts(vat_pham[vi_tri].ten);
            gotoxy(58 + strlen(vat_pham[vi_tri].ten), 7);
            if (so_luong_can > 1)
                printf(" <");
            printf(" %d/", so_luong_can);
            if (so_luong_can > 1)
                gotoxy(58 + strlen(vat_pham[vi_tri].ten) + 4 + so_luong_chu_so(so_luong_can, 0), 7);
            else
                gotoxy(58 + strlen(vat_pham[vi_tri].ten) + 2 + so_luong_chu_so(so_luong_can, 0), 7);
            printf("%d", vat_pham[vi_tri].so_luong);
            if (so_luong_can < vat_pham[vi_tri].so_luong - 1)
            {
                if (so_luong_can == 1)
                    gotoxy((58 + strlen(vat_pham[vi_tri].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + 2 + so_luong_chu_so(vat_pham[vi_tri].so_luong, 0)) - 2, 7);
                else
                    gotoxy(58 + strlen(vat_pham[vi_tri].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + 2 + so_luong_chu_so(vat_pham[vi_tri].so_luong, 0), 7);
                printf(" >");
            }
        }
        lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'q':
        {
            return;
            break;
        }
        case 'a':
        {
            if (so_luong_can > 1)
            {
                gotoxy(58, 7);
                if (chon_vat_pham == 1)
                {
                    for (i = 0; i < strlen(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + so_luong_chu_so(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong, 0) + 4; i++)
                        printf(" ");
                }
                if (chon_vat_pham == 2)
                {
                    for (i = 0; i < strlen(vat_pham[vi_tri].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + so_luong_chu_so(vat_pham[vi_tri].so_luong, 0) + 4; i++)
                        printf(" ");
                }
                so_luong_can--;
            }
            break;
        }
        case 'd':
        {
            if (so_luong_can < vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong - 1 || so_luong_can < vat_pham[vi_tri].so_luong - 1)
            {
                gotoxy(58, 7);
                if (chon_vat_pham == 1)
                {
                    for (i = 0; i < strlen(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + so_luong_chu_so(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong, 0) + 4; i++)
                        printf(" ");
                }
                if (chon_vat_pham == 2)
                {
                    for (i = 0; i < strlen(vat_pham[vi_tri].ten) + 2 + so_luong_chu_so(so_luong_can, 0) + so_luong_chu_so(vat_pham[vi_tri].so_luong, 0) + 4; i++)
                        printf(" ");
                }
                so_luong_can++;
            }
            break;
        }
        case 'k':
        {
            if (chon_vat_pham == 1)
            {
                vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong -= so_luong_can;
                them_vat_pham(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].id, so_luong_can);
            }
            if (chon_vat_pham == 2)
            {
                them_vat_pham(vat_pham[vi_tri].id, -so_luong_can);
                for (i = 0; i < so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]; i++)
                {
                    if (vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].id == vat_pham[vi_tri].id)
                    {
                        vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].so_luong += so_luong_can;
                        bo_qua = 1;
                        break;
                    }
                }
                if (bo_qua == 0)
                {
                    vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].id = vat_pham[vi_tri].id;
                    vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].gop = vat_pham[vi_tri].gop;
                    vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].so_luong = so_luong_can;
                    vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].suc_cong_pha = vat_pham[vi_tri].suc_cong_pha;
                    vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].co_the_an = vat_pham[vi_tri].co_the_an;
                    vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].the = vat_pham[vi_tri].the;
                    strcpy(vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].ten, vat_pham[vi_tri].ten);
                    so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]++;
                }
            }
            return;
            break;
        }
        }
    }
}

int kt_menu_ruong = 0;
int kt_ruong = 0;
int trang = 1;
int so_luong_vat_pham_con_lai = 0; // cac bien toan cuc danh cho ham tui do
int kt_tui_do = 0;
void tui_do() // giao dien tui do
{
    float so_trang;
    int bo_qua = 0;
    int y_chon = 7;
    int y = 7;
    int vi_tri = so_luong_vat_pham_con_lai;
    char lua_chon_menu;
    do
    {
        y = 7;
        kt_menu_tui_do = 0;
        gotoxy(56, 5);
        if (kt_ruong == 0)
            printf("Tui do: ");
        else
            printf("Vui long lua chon vat pham: ");
        for (i = so_luong_vat_pham_con_lai; i < so_luong_vat_pham; i++) // hien thi cac vat pham ma nguoi choi co
        {
            gotoxy(58, y);
            puts(vat_pham[i].ten);
            if (vat_pham[i].so_luong != 0 && vat_pham[i].gop == 1)
            {
                gotoxy(58 + strlen(vat_pham[i].ten), y);
                printf(" x ");
                gotoxy(58 + strlen(vat_pham[i].ten) + 3, y);
                printf("%d", vat_pham[i].so_luong);
            }
            y += 2;
            if (y >= 21)
                break;
        }
        so_trang = (so_luong_vat_pham / 8) + 1;
        if (so_luong_vat_pham >= 8)
        {
            if (trang > 1)
            {
                gotoxy(56, 21);
                printf("<");
            }
            gotoxy(58, 21);
            printf("%d/%.0f", trang, so_trang);
            if (trang < so_trang)
                printf(" >");
        }

        while (1) // vong lap lua chon vat pham
        {
            if (vat_pham[0].so_luong != 0) // fix loi du nut di chuyen khi khong co do
            {
                gotoxy(56, y_chon);
                printf("->");
            }
            if (kt_tui_do == 0)
                lua_chon_menu = getch();
            switch (lua_chon_menu)
            {
            case 'e':
            {
                if (kt_ruong == 0)
                {
                    kt_tui_do = 1;
                    return;
                    break;
                }
            }
            case 'q':
            {
                if (kt_ruong != 0)
                {
                    kt_tui_do = 1;
                    return;
                    break;
                }
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
            case 'a':
            {
                if (trang > 1)
                {
                    chuyen_chuc_nang();
                    so_luong_vat_pham_con_lai -= 7;
                    trang--;
                    tui_do();
                }
                break;
            }
            case 'd':
            {
                if (trang < so_trang)
                {
                    chuyen_chuc_nang();
                    so_luong_vat_pham_con_lai += 7;
                    trang++;
                    tui_do();
                }
                break;
            }
            case 'i':
            {
                if (so_luong_vat_pham > 0)
                {
                    chuyen_chuc_nang();
                    thong_tin_vat_pham(vi_tri);
                    kt_menu_tui_do = 1;
                    chuyen_chuc_nang();
                }
                break;
            }
            case 'k':
            {
                if (so_luong_vat_pham > 0)
                {
                    if (kt_ruong == 0)
                        trang_bi = vi_tri; // du lieu trang bi duoc lay tu lua chon cua nguoi choi
                    else
                    {
                        for (i = 0; i < so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]; i++)
                        {
                            if (vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].id == vat_pham[vi_tri].id)
                            {
                                vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].so_luong += vat_pham[vi_tri].so_luong;
                                bo_qua = 1;
                                break;
                            }
                        }
                        if (bo_qua == 0)
                        {
                            vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].id = vat_pham[vi_tri].id;
                            vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].gop = vat_pham[vi_tri].gop;
                            vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].so_luong = vat_pham[vi_tri].so_luong;
                            vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].suc_cong_pha = vat_pham[vi_tri].suc_cong_pha;
                            vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].co_the_an = vat_pham[vi_tri].co_the_an;
                            vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].the = vat_pham[vi_tri].the;
                            strcpy(vat_the_ruong[so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]][vat_the[i_tam].vi_tri_ruong].ten, vat_pham[vi_tri].ten);
                            so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]++;
                        }
                        xoa_vat_pham(vi_tri);
                    }
                    kt_tui_do = 1;
                    return;
                }
                break;
            }
            case 'p':
            {
                if (so_luong_vat_pham > 0 && vat_pham[vi_tri].so_luong > 1)
                {
                    if (kt_ruong == 1)
                    {
                        chon_vat_pham = 2;
                        chuyen_chuc_nang();
                        chon_so_luong_vat_pham(vi_tri);
                    }
                    kt_tui_do = 1;
                    return;
                }
                break;
            }
            }
            if (kt_tui_do == 1 || kt_menu_tui_do == 1)
                break;
        }
    } while (kt_menu_tui_do == 1);
}

int trang_ruong = 1;
int so_luong_vat_pham_con_lai_ruong = 0; // cac bien toan cuc danh cho ham tui do
int kt_xem_ruong = 0;
void xem_ruong() // ham cho phep nguoi choi xem ruong ben trong co gi
{
    char lua_chon_menu;
    float so_trang;
    char ten_vat_the[100];
    int vi_tri = so_luong_vat_pham_con_lai_ruong;
    int y_chon = 7;
    int y = 7;
    gotoxy(56, 5);
    strcpy(ten_vat_the, vat_the[i_tam].ten);
    ten_vat_the[0] -= 32; // viet hoa chu cai dau
    strcat(ten_vat_the, ":");
    puts(ten_vat_the);
    for (i = so_luong_vat_pham_con_lai_ruong; i < so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]; i++)
    {
        gotoxy(58, y);
        puts(vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].ten);
        if (vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].so_luong != 0 && vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].gop == 1)
        {
            gotoxy(58 + strlen(vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].ten), y);
            printf(" x ");
            gotoxy(58 + strlen(vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].ten) + 3, y);
            printf("%d", vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].so_luong);
        }
        y += 2;
        if (y >= 21)
            break;
    }

    so_trang = (so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong] / 8) + 1;
    if (so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong] >= 8)
    {
        if (trang_ruong > 1)
        {
            gotoxy(56, 21);
            printf("<");
        }
        gotoxy(58, 21);
        printf("%d/%.0f", trang_ruong, so_trang);
        if (trang_ruong < so_trang)
            printf(" >");
    }
    while (1) // vong lap lua chon vat pham
    {
        if (vat_the_ruong[0][vat_the[i_tam].vi_tri_ruong].so_luong != 0 && kt_ruong == 1) // fix loi du nut di chuyen khi khong co do
        {
            gotoxy(56, y_chon);
            printf("->");
        }
        if (kt_xem_ruong == 0)
            lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'q':
        {
            kt_xem_ruong = 1;
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
        case 'a':
        {
            if (trang_ruong > 1)
            {
                chuyen_chuc_nang();
                so_luong_vat_pham_con_lai_ruong -= 7;
                trang_ruong--;
                xem_ruong();
            }
            break;
        }
        case 'd':
        {
            if (trang_ruong < so_trang)
            {
                chuyen_chuc_nang();
                so_luong_vat_pham_con_lai_ruong += 7;
                trang_ruong++;
                xem_ruong();
            }
            break;
        }
        case 'k':
        {
            if (so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong] > 0)
            {
                if (kt_ruong == 1)
                {
                    them_vat_pham(vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].id, vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong);
                    xoa_vat_pham_ruong(vi_tri);
                }
                kt_xem_ruong = 1;
                return;
            }
            break;
        }
        case 'p':
        {
            if (so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong] > 0 && vat_the_ruong[vi_tri][vat_the[i_tam].vi_tri_ruong].so_luong > 1)
            {
                if (kt_ruong == 1)
                {
                    chon_vat_pham = 1;
                    chuyen_chuc_nang();
                    chon_so_luong_vat_pham(vi_tri);
                }
                kt_xem_ruong = 1;
                return;
            }
            break;
        }
        }
        if (kt_xem_ruong == 1)
            break;
    }
}

void ruong() // giao dien va tinh nang cua ruong
{
    char lua_chon_menu;
    char ten_vat_the[100];
    int y_chon = 7;
    do
    {
        kt_menu_ruong = 0;
        gotoxy(56, 5);
        strcpy(ten_vat_the, vat_the[i_tam].ten);
        ten_vat_the[0] -= 32; // viet hoa chu cai dau
        strcat(ten_vat_the, ":");
        puts(ten_vat_the);
        gotoxy(58, 7);
        printf("Xem vat pham");
        gotoxy(58, 9);
        printf("Lay vat pham ra");
        gotoxy(58, 11);
        printf("Dua vat pham vao");
        while (1)
        {
            gotoxy(56, y_chon);
            printf("->");
            lua_chon_menu = getch();
            switch (lua_chon_menu)
            {
            case 'q':
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
                if (y_chon < 11)
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
                    trang_ruong = 1;
                    so_luong_vat_pham_con_lai_ruong = 0;
                    kt_xem_ruong = 0;
                    chuyen_chuc_nang();
                    xem_ruong();
                    kt_menu_ruong = 1;
                }
                if (y_chon == 9)
                {
                    kt_ruong = 1; // cho ham xem ruong biet nguoi choi se lay do ra khoi ruong
                    trang_ruong = 1;
                    so_luong_vat_pham_con_lai_ruong = 0;
                    kt_xem_ruong = 0;
                    chuyen_chuc_nang();
                    xem_ruong();
                    kt_ruong = 0;
                    kt_menu_ruong = 1;
                }
                if (y_chon == 11)
                {
                    trang = 1;
                    so_luong_vat_pham_con_lai = 0; // reset lai cac bien dung cho tui do
                    kt_tui_do = 0;
                    kt_ruong = 1; // cho ham tui do biet nguoi choi se bo do vo ruong
                    chuyen_chuc_nang();
                    tui_do();
                    kt_ruong = 0;
                    kt_menu_ruong = 1;
                }
                break;
            }
            }
            if (kt_menu_ruong == 1)
            {
                chuyen_chuc_nang();
                break;
            }
        }
    } while (kt_menu_ruong == 1);
}

void kiem_tra_che_tao(int kt, int mau) // kiem tra vi tri xuat hien cua cac vat pham che tao. Ham nay chi co the dung cho ham tui do
{
    if (mau == 4)
        TextColor(4); // 4: mau do la khong che duoc
    if (mau == 7)
        TextColor(7); // 7: mau trang la che duoc
    if (kt == 1)
        printf("Riu go x 1 | Ton 5 khoi go");
    if (kt == 2)
        printf("Cup go x 1 | Ton 5 khoi go");
    if (kt == 3)
        printf("Lo nung x 1 | Ton 6 cuc da");
    if (kt == 4)
        printf("Ruong go x 1 | Ton 10 khoi go");
    if (kt == 5)
        printf("Xeng go x 1 | Ton 5 khoi go");
    if (kt == 6)
        printf("Cuoc go x 1 | Ton 5 khoi go");
    if (kt == 7)
        printf("Bot mi x 1 | Ton 1 lua mi");
}

void kiem_tra_tieu_hao_vat_pham_che_tao(int kt) // ham kiem tra vat pham tai vi tri che tao do la vat pham nao
{
    if (kt == 1)
    {
        if (kiem_tra_vat_pham(1, 5) == 1)
        {
            them_vat_pham(7, 1);
            them_vat_pham(1, -5);
            strcpy(hien_thi, "Ban nhan duoc 1 riu go");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
    if (kt == 2)
    {
        if (kiem_tra_vat_pham(1, 5) == 1)
        {
            them_vat_pham(8, 1);
            them_vat_pham(1, -5);
            strcpy(hien_thi, "Ban nhan duoc 1 cup go");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
    if (kt == 3)
    {
        if (kiem_tra_vat_pham(2, 6) == 1)
        {
            them_vat_pham(9, 1);
            them_vat_pham(2, -6);
            strcpy(hien_thi, "Ban nhan duoc 1 lo nung");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
    if (kt == 4)
    {
        if (kiem_tra_vat_pham(1, 10) == 1)
        {
            them_vat_pham(10, 1);
            them_vat_pham(1, -10);
            strcpy(hien_thi, "Ban nhan duoc 1 ruong go");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
    if (kt == 5)
    {
        if (kiem_tra_vat_pham(1, 5) == 1)
        {
            them_vat_pham(13, 1);
            them_vat_pham(1, -5);
            strcpy(hien_thi, "Ban nhan duoc 1 xeng go");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
    if (kt == 6)
    {
        if (kiem_tra_vat_pham(1, 5) == 1)
        {
            them_vat_pham(14, 1);
            them_vat_pham(1, -5);
            strcpy(hien_thi, "Ban nhan duoc 1 cuoc go");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
    if (kt == 7)
    {
        if (kiem_tra_vat_pham(17, 1) == 1)
        {
            them_vat_pham(18, 1);
            them_vat_pham(17, -1);
            strcpy(hien_thi, "Ban nhan duoc 1 bot mi");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
}

void che_tao() // giao dien che tao
{
    // chuoi lenh kiem tra vi tri xuat hien cua cac vat pham che tao, neu che duoc thi se duoc uu tien de o vi tri phia tren cung
    typedef struct kiem_tra
    {
        int vi_tri;
        int mau;
        int id;
    } kiem_tra;

    int vi_tri_dau, vi_tri_cuoi, vi_tri_che_tao;
    kiem_tra kt[7];
    vi_tri_dau = 0;
    vi_tri_cuoi = 6;
    vi_tri_che_tao = 1;
    if (kiem_tra_vat_pham(1, 5) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 1;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 1;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    if (kiem_tra_vat_pham(1, 5) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 2;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 2;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    if (kiem_tra_vat_pham(2, 6) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 3;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 3;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    if (kiem_tra_vat_pham(1, 10) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 4;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 4;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    if (kiem_tra_vat_pham(1, 5) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 5;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 5;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    if (kiem_tra_vat_pham(1, 5) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 6;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 6;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    if (kiem_tra_vat_pham(17, 1) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 7;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 7;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    // ket thuc chuoi lenh kiem tra

    gotoxy(56, 5);
    printf("Che tao: ");
    gotoxy(58, 7);
    kiem_tra_che_tao(kt[0].vi_tri, kt[0].mau);
    gotoxy(58, 9);
    kiem_tra_che_tao(kt[1].vi_tri, kt[1].mau);
    gotoxy(58, 11);
    kiem_tra_che_tao(kt[2].vi_tri, kt[2].mau);
    gotoxy(58, 13);
    kiem_tra_che_tao(kt[3].vi_tri, kt[3].mau);
    gotoxy(58, 15);
    kiem_tra_che_tao(kt[4].vi_tri, kt[4].mau);
    gotoxy(58, 17);
    kiem_tra_che_tao(kt[5].vi_tri, kt[5].mau);
    gotoxy(58, 19);
    kiem_tra_che_tao(kt[6].vi_tri, kt[6].mau);
    TextColor(7);
    int y_chon = 7;
    while (1)
    {
        gotoxy(56, y_chon);
        printf("->");
        char lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'c':
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
            if (y_chon < 19)
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
                kiem_tra_tieu_hao_vat_pham_che_tao(kt[0].id);
                return;
            }
            if (y_chon == 9)
            {
                kiem_tra_tieu_hao_vat_pham_che_tao(kt[1].id);
                return;
            }
            if (y_chon == 11)
            {
                kiem_tra_tieu_hao_vat_pham_che_tao(kt[2].id);
                return;
            }
            if (y_chon == 13)
            {
                kiem_tra_tieu_hao_vat_pham_che_tao(kt[3].id);
                return;
            }
            if (y_chon == 15)
            {
                kiem_tra_tieu_hao_vat_pham_che_tao(kt[4].id);
                return;
            }
            if (y_chon == 17)
            {
                kiem_tra_tieu_hao_vat_pham_che_tao(kt[5].id);
                return;
            }
            if (y_chon == 19)
            {
                kiem_tra_tieu_hao_vat_pham_che_tao(kt[6].id);
                return;
            }
            break;
        }
        }
    }
}

void kiem_tra_lo_nung(int kt, int mau) // kiem tra vi tri xuat hien cua cac vat pham lo nung. Ham nay chi co the dung cho ham lo nung
{
    if (mau == 4)
        TextColor(4); // 4: mau do la khong che duoc
    if (mau == 7)
        TextColor(7); // 7: mau trang la che duoc
    if (kt == 1)
        printf("Banh mi x 1 | Ton 1 bot mi");
}

void kiem_tra_tieu_hao_vat_pham_lo_nung(int kt) // ham kiem tra vat pham tai vi tri che tao do la vat pham nao
{
    if (kt == 1)
    {
        if (kiem_tra_vat_pham(18, 1) == 1)
        {
            them_vat_pham(19, 1);
            them_vat_pham(18, -1);
            strcpy(hien_thi, "Ban nhan duoc 1 banh mi");
        }
        else
            strcpy(hien_thi, "Ban khong du tai nguyen!");
    }
}

void lo_nung() // giao dien lo nung
{
    // chuoi lenh kiem tra vi tri xuat hien cua cac vat pham lo nung, neu che duoc thi se duoc uu tien de o vi tri phia tren cung
    typedef struct kiem_tra
    {
        int vi_tri;
        int mau;
        int id;
    } kiem_tra;

    int vi_tri_dau, vi_tri_cuoi, vi_tri_che_tao;
    kiem_tra kt[1];
    vi_tri_dau = 0;
    vi_tri_cuoi = 0;
    vi_tri_che_tao = 1;
    if (kiem_tra_vat_pham(18, 1) == 1)
    {
        kt[vi_tri_dau].vi_tri = vi_tri_che_tao;
        kt[vi_tri_dau].mau = 7;
        kt[vi_tri_dau].id = 1;
        vi_tri_che_tao++;
        vi_tri_dau++;
    }
    else
    {
        kt[vi_tri_cuoi].vi_tri = vi_tri_che_tao;
        kt[vi_tri_cuoi].mau = 4;
        kt[vi_tri_cuoi].id = 1;
        vi_tri_che_tao++;
        vi_tri_cuoi--;
    }
    // ket thuc chuoi lenh kiem tra

    gotoxy(56, 5);
    printf("Che tao: ");
    gotoxy(58, 7);
    kiem_tra_lo_nung(kt[0].vi_tri, kt[0].mau);
    TextColor(7);
    int y_chon = 7;
    while (1)
    {
        gotoxy(56, y_chon);
        printf("->");
        char lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'q':
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
            if (y_chon < 7)
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
                kiem_tra_tieu_hao_vat_pham_lo_nung(kt[0].id);
                return;
            }
            break;
        }
        }
    }
}

void vat_pham_1_1() // ham hien thi vat pham ma nguoi choi tung so huu
{
    gotoxy(56, 5);
    printf("Ban luu vat pham: ");
    gotoxy(58, 7);
    if (vat_pham_da_co[0] == 1)
        printf("Khoi go");
    else
        printf("???");
    gotoxy(58, 9);
    if (vat_pham_da_co[1] == 1)
        printf("Cuc da");
    else
        printf("???");
    gotoxy(58, 11);
    if (vat_pham_da_co[2] == 1)
        printf("Chum nho");
    else
        printf("???");
    gotoxy(58, 13);
    if (vat_pham_da_co[3] == 1)
        printf("Mam cay");
    else
        printf("???");
    while (1)
    {
        char lua_chon_menu = getch();
        if (lua_chon_menu == 'q')
            return;
    }
}

void thong_tin() // phan thong tin cua game
{
    int y_chon = 7;
    while (1)
    {
        gotoxy(56, 5);
        printf("Ban luu vat pham: ");
        gotoxy(58, 7);
        printf("Tang 1");
        gotoxy(58, 9);
        printf("Tang 2");
        gotoxy(58, 11);
        printf("Tang 3");
        gotoxy(56, y_chon);
        printf("->");
        char lua_chon_menu = getch();
        switch (lua_chon_menu)
        {
        case 'q':
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
            if (y_chon < 11)
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
                int y_chon_chon = 7;
                int kt_thoat = 0;
                chuyen_chuc_nang();
                gotoxy(56, 5);
                printf("Ban luu vat pham: ");
                gotoxy(58, 7);
                printf("Tang 1-1");
                gotoxy(58, 9);
                printf("Tang 1-2");
                gotoxy(58, 11);
                printf("Tang 1-3");
                while (1)
                {
                    gotoxy(56, y_chon_chon);
                    printf("->");
                    char lua_chon_menu = getch();
                    switch (lua_chon_menu)
                    {
                    case 'q':
                    {
                        kt_thoat = 1;
                        break;
                    }
                    case 'w':
                    {
                        if (y_chon_chon > 7)
                        {
                            gotoxy(56, y_chon_chon);
                            printf("  ");
                            y_chon_chon -= 2;
                        }
                        break;
                    }
                    case 's':
                    {
                        if (y_chon_chon < 11)
                        {
                            gotoxy(56, y_chon_chon);
                            printf("  ");
                            y_chon_chon += 2;
                        }
                        break;
                    }
                    case 'k':
                    {
                        if (y_chon_chon == 7)
                        {
                            chuyen_chuc_nang();
                            vat_pham_1_1();
                            return;
                        }
                        if (y_chon_chon == 9)
                        {

                            return;
                        }
                        if (y_chon_chon == 11)
                        {

                            return;
                        }
                    }
                    }
                    if (kt_thoat == 1)
                    {
                        chuyen_chuc_nang();
                        break;
                    }
                }
            }
            if (y_chon == 9)
            {

                return;
            }
            if (y_chon == 11)
            {

                return;
            }
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
    printf("Ban luu vat pham");
    gotoxy(58, 11);
    TextColor(4); // them mau do cho dong chu
    printf("Xoa du lieu");
    TextColor(7);

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
            if (y_chon < 11)
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
                chuyen_chuc_nang();
                thong_tin();
                return;
            }
            if (y_chon == 11)
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
    char kt_tam;
    f = fopen("save.txt", "r");
    kt_tam = fgetc(f);
    while (1)
    {
        gotoxy(5, 5);
        printf("Infinity Tower Beta V0.3");
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
                int kt_quay_lai = 0;
                if (kt_tam != ' ')
                {
                    int y_chon_chon = 7;
                    system("cls");
                    gotoxy(5, 5);
                    printf("Du lieu cua ban se bi xoa!");
                    gotoxy(7, 7);
                    printf("Tiep tuc");
                    gotoxy(7, 9);
                    printf("Quay lai");
                    while (1)
                    {
                        int kt_thoat = 0;
                        gotoxy(5, y_chon_chon);
                        printf("->");
                        lua_chon_menu = getch();
                        switch (lua_chon_menu)
                        {
                        case 'w':
                        {
                            if (y_chon_chon > 7)
                            {
                                gotoxy(5, y_chon_chon);
                                printf("  ");
                                y_chon_chon -= 2;
                            }
                            break;
                        }
                        case 's':
                        {
                            if (y_chon_chon < 9)
                            {
                                gotoxy(5, y_chon_chon);
                                printf("  ");
                                y_chon_chon += 2;
                            }
                            break;
                        }
                        case 'k':
                        {
                            if (y_chon_chon == 7)
                                kt_thoat = 1;
                            if (y_chon_chon == 9)
                            {
                                kt_quay_lai = 1;
                                kt_thoat = 1;
                            }
                            break;
                        }
                        }
                        if (kt_thoat == 1)
                            break;
                    }
                }
                if (kt_quay_lai == 0)
                {
                    tiep_tuc = 0;
                    xoa_du_lieu();
                    system("cls");
                    return;
                }
                else
                    system("cls");
            }
            if (y_chon == 9)
            {
                system("cls");
                if (kt_tam == ' ') // kiem tra du lieu cua game co rong hay khong
                {
                    gotoxy(5, 5);
                    printf("Khong co du lieu da luu truoc do...");
                }
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
                huong_dan();
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

void tro_ra_menu() // ham hien thi nguoi choi co muon tro lai menu game khong
{
    int y_chon = 7;
    gotoxy(5, 5);
    printf("Ban se quay tro lai menu (Du lieu se tu dong luu lai): ");
    gotoxy(7, 7);
    printf("Tiep tuc");
    gotoxy(7, 9);
    printf("Quay lai");
    while (1)
    {
        gotoxy(5, y_chon);
        printf("->");
        char lua_chon = getch();
        switch (lua_chon)
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
            if (y_chon < 9)
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
                luu_du_lieu();
                system("cls");
                man_hinh_tieu_de();
                return;
            }
            if (y_chon == 9)
            {
                luu_du_lieu();
                tiep_tuc = 1;
                tai_du_lieu();
                kt_menu = 1;
                system("cls");
                return;
            }
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
        printf("%c", vat_the[i].bieu_tuong);
    }
}

void tai_thoi_gian_hoi() // tai thoi gian hoi phuc cua cac vat the
{
    if (so_luong_hoi > 0)
    {
        int tam = so_luong_hoi;
        for (i = 0; i < tam; i++)
        {
            thoi_gian_hoi_vat_the[i].thoi_gian--;
            if (thoi_gian_hoi_vat_the[i].thoi_gian == 0)
            {
                if (thoi_gian_hoi_vat_the[i].id == 1)
                {
                    gotoxy(vat_the[thoi_gian_hoi_vat_the[i].vi_tri].toa_do_x, vat_the[thoi_gian_hoi_vat_the[i].vi_tri].toa_do_y);
                    printf(" ");
                    gotoxy(vat_the[thoi_gian_hoi_vat_the[i].vi_tri].toa_do_x, vat_the[thoi_gian_hoi_vat_the[i].vi_tri].toa_do_y);
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].bieu_tuong = 'C';
                    printf("%c", vat_the[thoi_gian_hoi_vat_the[i].vi_tri].bieu_tuong);
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].id = 1;
                    strcpy(vat_the[thoi_gian_hoi_vat_the[i].vi_tri].ten, "cai cay");
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].do_ben_toi_da = 10;
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].do_ben = vat_the[thoi_gian_hoi_vat_the[i].vi_tri].do_ben_toi_da;
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].kha_nang_tuong_tac = 0;
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].kha_nang_dung_trong_vat_the = 0;
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].kha_nang_trong_trot.dang_duoc_trong = 0;
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].kha_nang_trong_trot.vat_pham_trong = -1;
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].vi_tri_ruong = -1;
                }
                if (thoi_gian_hoi_vat_the[i].id == 2)
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].do_ben++;
                if (thoi_gian_hoi_vat_the[i].id == 3)
                {
                    strcpy(vat_the[thoi_gian_hoi_vat_the[i].vi_tri].ten, thoi_gian_hoi_vat_the[i].ten_vat_the);
                    strcat(vat_the[thoi_gian_hoi_vat_the[i].vi_tri].ten, " dang trong ");
                    if (vat_the[thoi_gian_hoi_vat_the[i].vi_tri].kha_nang_trong_trot.vat_pham_trong == 12)
                        strcat(vat_the[thoi_gian_hoi_vat_the[i].vi_tri].ten, "lua mi");
                    vat_the[thoi_gian_hoi_vat_the[i].vi_tri].kha_nang_trong_trot.dang_duoc_trong = 2;
                }
                for (j = i; j < tam; j++)
                {
                    thoi_gian_hoi_vat_the[j].id = thoi_gian_hoi_vat_the[j + 1].id;
                    thoi_gian_hoi_vat_the[j].thoi_gian = thoi_gian_hoi_vat_the[j + 1].thoi_gian;
                    thoi_gian_hoi_vat_the[j].vi_tri = thoi_gian_hoi_vat_the[j + 1].vi_tri;
                    strcpy(thoi_gian_hoi_vat_the[j].ten_vat_the, thoi_gian_hoi_vat_the[j + 1].ten_vat_the);
                }
                tam--;
                i--;
            }
        }
        so_luong_hoi = tam;
    }
}

/*-------------------------------------------------------------------------------------------------------*/

int main()
{
    man_hinh_tieu_de();
    do
    {
        menu = 0;
        if (tiep_tuc == 0)
        {
            du_lieu_tang_1_1();
            them_vat_pham(5, 1);  // tang riu cho nguoi choi khi moi vao game
            them_vat_pham(6, 1);  // tang cup cho nguoi choi khi moi vao game
            them_vat_pham(11, 1); // tang the khong gian cho nguoi choi khi moi vao game
        }
        if (tiep_tuc == 1)
            tai_vat_the();
        // thiet ke khung tro choi chinh
        int y = 6;
        char ten_tang[100];
        if (vi_tri_tang == 11)
            strcpy(ten_tang, "|Tang 1-1: Khu Vuc Khoi Dau|");
        int vi_tri_ten_tang = (50 - strlen(ten_tang)) / 2;
        gotoxy(5, 5);
        for (i = 1; i <= vi_tri_ten_tang; i++)
            printf("=");
        puts(ten_tang);
        gotoxy(5 + vi_tri_ten_tang + strlen(ten_tang), 5); // chuoi lenh can giua ten tang
        for (i = 1; i <= vi_tri_ten_tang; i++)
            printf("=");
        if (vi_tri_ten_tang + strlen(ten_tang) + vi_tri_ten_tang == 49)
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

        if (kt_menu == 1)
        {
            strcpy(hien_thi, "Luu du lieu thanh cong!");
            kt_menu = 0;
        }

        while (1)
        {
            gotoxy(x_nguoi_choi, y_nguoi_choi); // toa do nguoi choi
            printf("%c", nguoi_choi);           // nguoi choi

            giao_dien_game_chinh();
            thong_tin_nhan_vat();

            x_tam = x_nguoi_choi; // luu toa do cua nguoi choi de xoa nguoi choi khi di chuyen
            y_tam = y_nguoi_choi;

            strcpy(hien_thi, " "); // xoa chuoi hien thi
            di_chuyen_va_hanh_dong();

            if (fix_dung_tren_vat_the_lien_tiep == 0)
            {
                gotoxy(x_tam, y_tam);
                printf(" "); // xoa nguoi choi o vi tri cu
            }

            fix_dung_tren_vat_the_lien_tiep = 0;
            if (hien_thi_lai_vat_the == 2)
            {
                gotoxy(x_tam, y_tam);
                printf("%c", bieu_tuong_tam); // khi nguoi choi ra khoi vat the co the dung ben trong duoc thi hien thi lai vat the o vi tri cu
                hien_thi_lai_vat_the = 0;
            }
            if (menu == 1)
                break;
        }
    } while (menu == 1);
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
        if (hien_thi_lai_vat_the == 1)
            hien_thi_lai_vat_the = 2;
        nguoi_choi = '^';
        break;
    }
    case 'a':
    {
        x_nguoi_choi--;
        strcpy(hanh_dong, "Ban vua sang trai");
        huong_nguoi_choi = 2;
        if (hien_thi_lai_vat_the == 1)
            hien_thi_lai_vat_the = 2;
        nguoi_choi = '<';
        break;
    }
    case 's':
    {
        y_nguoi_choi++;
        strcpy(hanh_dong, "Ban vua di xuong");
        huong_nguoi_choi = 3;
        if (hien_thi_lai_vat_the == 1)
            hien_thi_lai_vat_the = 2;
        nguoi_choi = 'v';
        break;
    }
    case 'd':
    {
        x_nguoi_choi++;
        strcpy(hanh_dong, "Ban vua sang phai");
        huong_nguoi_choi = 4;
        if (hien_thi_lai_vat_the == 1)
            hien_thi_lai_vat_the = 2;
        nguoi_choi = '>';
        break;
    }
    case 'k':
    {
        if (huong_nguoi_choi == kiem_tra_vat_the() || vat_pham[trang_bi].the == 4 || vat_pham[trang_bi].the == 5)
        {
            thuc_hien_hanh_dong();
            break;
        }
        if (vat_pham[trang_bi].co_the_an == 1 && vat_pham[trang_bi].the == 1)
            thuc_hien_dat_khoi();
        break;
    }
    case 'p':
    {
        if (vat_pham[trang_bi].co_the_an == 1 && do_doi < 100)
        {
            an_thuc_an();
            break;
        }
        if (huong_nguoi_choi == kiem_tra_vat_the() && vat_the[i_tam].kha_nang_tuong_tac == 1)
        {
            tuong_tac_vat_the();
            break;
        }
        if (vat_pham[trang_bi].the == 1 && vat_pham[trang_bi].co_the_an == 0)
            thuc_hien_dat_khoi();
        break;
    }
    case 'e':
    {
        chuyen_chuc_nang();
        trang = 1;
        so_luong_vat_pham_con_lai = 0; // reset lai cac bien dung cho tui do
        kt_tui_do = 0;
        tui_do();
        chuyen_chuc_nang();
        break;
    }
    case 'c':
    {
        chuyen_chuc_nang();
        che_tao();
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
    case 'i':
    {
        chuyen_chuc_nang();
        them_thong_tin_nhan_vat();
        chuyen_chuc_nang();
        break;
    }
    case 'q':
    {
        system("cls");
        menu = 1;
        tro_ra_menu();
        break;
    }
    case 'n':
    {
        strcpy(hanh_dong, "Ban dang dung yen");
        if (the_luc < 100)
            thoi_gian_hoi_the_luc++; // khi dung yen du 10 phut thi hoi 1 the luc
        if (thoi_gian_hoi_the_luc == 10)
        {
            the_luc++;
            thoi_gian_hoi_the_luc = 0;
            strcat(hanh_dong, " | + 1 the luc");
        }

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
    if (lua_chon != 'n')
        thoi_gian_hoi_the_luc = 0; // khi khong nhan n lien tuc thi reset thoi gian hoi the luc
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
            if (vat_the[i].kha_nang_dung_trong_vat_the != 1)
            {
                x_nguoi_choi = x_tam;
                y_nguoi_choi = y_tam;
            }
            else
            {
                if (hien_thi_lai_vat_the == 2)
                {
                    gotoxy(x_tam, y_tam);
                    printf("%c", bieu_tuong_tam); // khi nguoi choi ra khoi vat the co the dung ben trong duoc thi hien thi lai vat the o vi tri cu
                    hien_thi_lai_vat_the = 0;
                    fix_dung_tren_vat_the_lien_tiep = 1;
                }
                hien_thi_lai_vat_the = 1;
                bieu_tuong_tam = vat_the[i].bieu_tuong;
                strcpy(hanh_dong, "Ban dang dung tren ");
                strcat(hanh_dong, vat_the[i].ten);
            }
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
    char so_thanh_chuoi[100][100];                                       // bien chuyen so thanh chuoi
    sprintf(so_thanh_chuoi[0], " %d ", vat_pham[trang_bi].suc_cong_pha); // lenh chuyen so thanh chuoi
    if (vat_the[i_tam].id == 1)
    {
        if (vat_pham[trang_bi].the != 2 || strcmp(tay_phai, "Khong") == 0)
        {
            strcpy(hien_thi, "Ban can co riu de chat cay nay!");
            return;
        }
        the_luc -= 5;
        if (vat_pham_da_co[0] != 1)
            so_luong_vat_pham_da_co++;
        vat_pham_da_co[0] = 1;
        strcpy(hanh_dong, "Ban vua chat cay | +");
        strcat(hanh_dong, so_thanh_chuoi[0]); // hien thi suc cong pha cua trang bi hien tai
        strcat(hanh_dong, "khoi go");
        vat_the[i_tam].do_ben -= vat_pham[trang_bi].suc_cong_pha;
        if (vat_the[i_tam].do_ben <= 0)
        {
            int mam_cay = random(0, 4); // bien tao mam cay ngau nhien khi chat het cay
            sprintf(so_thanh_chuoi[0], " %d ", mam_cay);
            int khoi_go = 10 + (vat_pham[trang_bi].suc_cong_pha + vat_the[i_tam].do_ben); // fix loi suc cong pha vuot qua do ben cua vat the
            sprintf(so_thanh_chuoi[1], " %d ", khoi_go);
            strcpy(hanh_dong, "Ban vua chat gay ca cay | +");
            strcat(hanh_dong, so_thanh_chuoi[1]);
            strcat(hanh_dong, "khoi go");
            if (mam_cay != 0)
            {
                if (vat_pham_da_co[3] != 1)
                    so_luong_vat_pham_da_co++;
                vat_pham_da_co[3] = 1;
                strcat(hanh_dong, " | +");
                strcat(hanh_dong, so_thanh_chuoi[0]);
                strcat(hanh_dong, "mam cay");
                them_vat_pham(4, mam_cay);
            }
            xoa_vat_the();
            them_vat_pham(1, khoi_go);
            return;
        }
        them_vat_pham(1, vat_pham[trang_bi].suc_cong_pha);
        return;
    }

    if (vat_the[i_tam].id == 2)
    {
        if (vat_pham[trang_bi].the != 3 || strcmp(tay_phai, "Khong") == 0)
        {
            strcpy(hien_thi, "Ban can co cup de dao tang da nay!");
            return;
        }
        the_luc -= 10;
        if (vat_pham_da_co[1] != 1)
            so_luong_vat_pham_da_co++;
        vat_pham_da_co[1] = 1;
        strcpy(hanh_dong, "Ban vua dao da | +");
        strcat(hanh_dong, so_thanh_chuoi[0]);
        strcat(hanh_dong, "cuc da");
        vat_the[i_tam].do_ben -= vat_pham[trang_bi].suc_cong_pha;
        if (vat_the[i_tam].do_ben <= 0)
        {
            int cuc_da = 5 + (vat_pham[trang_bi].suc_cong_pha + vat_the[i_tam].do_ben); // fix loi suc cong pha vuot qua do ben cua vat the
            sprintf(so_thanh_chuoi[1], " %d ", cuc_da);
            strcpy(hanh_dong, "Ban vua dao be ca tang da | +");
            strcat(hanh_dong, so_thanh_chuoi[1]);
            strcat(hanh_dong, "cuc da");
            xoa_vat_the();
            them_vat_pham(2, cuc_da);
            return;
        }
        them_vat_pham(2, vat_pham[trang_bi].suc_cong_pha);
        return;
    }

    if (vat_the[i_tam].id == 3)
    {
        strcpy(hanh_dong, "Ban vua pha ca bui nho");
        if (vat_the[i_tam].do_ben != 0)
        {
            if (vat_pham_da_co[2] != 1)
                so_luong_vat_pham_da_co++;
            vat_pham_da_co[2] = 1;
            strcat(hanh_dong, " | +");
            sprintf(so_thanh_chuoi[0], " %d ", vat_the[i_tam].do_ben);
            strcat(hanh_dong, so_thanh_chuoi[0]);
            strcat(hanh_dong, "chum nho");
        }
        xoa_vat_the();
        if (vat_the[i_tam].do_ben != 0)
            them_vat_pham(3, vat_the[i_tam].do_ben);
        return;
    }

    if (vat_the[i_tam].id == 4)
    {
        strcpy(hanh_dong, "Ban vua nho mam cay | + 1 mam cay");
        xoa_vat_the();
        them_vat_pham(4, 1);
        int tam = so_luong_hoi;
        for (i = 0; i < tam; i++)
        {
            if (thoi_gian_hoi_vat_the[i].vi_tri == i_tam)
            {
                for (j = i; j < tam; j++)
                {
                    thoi_gian_hoi_vat_the[j].id = thoi_gian_hoi_vat_the[j + 1].id;
                    thoi_gian_hoi_vat_the[j].thoi_gian = thoi_gian_hoi_vat_the[j + 1].thoi_gian;
                    thoi_gian_hoi_vat_the[j].vi_tri = thoi_gian_hoi_vat_the[j + 1].vi_tri;
                }
                i--;
                tam--;
            }
        }
        so_luong_hoi = tam;
        return;
    }

    if (vat_the[i_tam].id == 5)
    {
        if (vat_pham[trang_bi].the != 3 || strcmp(tay_phai, "Khong") == 0)
        {
            strcpy(hien_thi, "Ban can co cup de dap be lo nung nay!");
            return;
        }
        strcpy(hanh_dong, "Ban vua dap be lo nung | + 1 lo nung");
        xoa_vat_the();
        them_vat_pham(9, 1);
        return;
    }
    if (vat_the[i_tam].id == 6)
    {
        if (vat_pham[trang_bi].the != 2 || strcmp(tay_phai, "Khong") == 0)
        {
            strcpy(hien_thi, "Ban can co riu de dap nat ruong go nay!");
            return;
        }
        strcpy(hanh_dong, "Ban vua dap nat ruong go | + 1 ruong go");
        xoa_vat_the();
        them_vat_pham(10, 1);
        if (so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong] != 0)
        {
            for (i = 0; i < so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]; i++)
            {
                strcat(hanh_dong, " | +");
                sprintf(so_thanh_chuoi[0], " %d ", vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].so_luong);
                strcat(hanh_dong, so_thanh_chuoi[0]);
                char ten_vat_pham_tam[100];
                strcpy(ten_vat_pham_tam, vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].ten);
                ten_vat_pham_tam[0] += 32;
                strcat(hanh_dong, ten_vat_pham_tam);
                them_vat_pham(vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].id, vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].so_luong);
            }
        }
        so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong] = -1;
        return;
    }
    if (vat_the[i_tam].id == 7)
    {
        int hat_giong = random(1, 4);
        strcpy(hanh_dong, "Ban vua pha bui co");
        if (hat_giong == 1)
        {
            strcat(hanh_dong, " | + 1 hat giong");
            them_vat_pham(12, 1);
        }
        xoa_vat_the();
        return;
    }
    if (vat_the[i_tam].id == 8)
    {
        if (vat_pham[trang_bi].the != 4 || strcmp(tay_phai, "Khong") == 0)
        {
            strcpy(hien_thi, "Ban can co xeng de dao cuc dat nay len!");
            return;
        }
        strcpy(hanh_dong, "Ban vua dao dat da duoc xoi | + 1 cuc dat da duoc xoi");
        them_vat_pham(16, 1);
        if (vat_the[i_tam].kha_nang_trong_trot.dang_duoc_trong == 1)
        {
            strcat(hanh_dong, " | + 1 hat giong");
            them_vat_pham(12, 1);
        }
        if (vat_the[i_tam].kha_nang_trong_trot.dang_duoc_trong == 2)
        {
            strcat(hanh_dong, " | + 1 lua mi | + 1 hat giong");
            them_vat_pham(12, 1);
            them_vat_pham(17, 1);
        }
        xoa_vat_the();
        return;
    }
    if (vat_pham[trang_bi].the == 4)
    {
        strcpy(hanh_dong, "Ban vua dao dat | + 1 cuc dat");
        them_vat_pham(15, 1);
        return;
    }
    if (vat_pham[trang_bi].the == 5)
    {
        strcpy(hanh_dong, "Ban vua xoi dat");
        thuc_hien_dat_khoi();
        return;
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
    i_tam = -1;
    return 0;
}

int vat_the_hoi = 0; // bien kiem tra vat the co la mam cay hay khong
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
        strcpy(hanh_dong, "Ban vua dat mam cay");
        strcpy(vat_the[so_luong_vat_the].ten, "mam cay");
        vat_the[so_luong_vat_the].bieu_tuong = 'M';
        printf("%c", vat_the[so_luong_vat_the].bieu_tuong);
        vat_the[so_luong_vat_the].id = 4;
        vat_the[so_luong_vat_the].do_ben_toi_da = 1;
        vat_the[so_luong_vat_the].do_ben = vat_the[so_luong_vat_the].do_ben_toi_da;
        vat_the[so_luong_vat_the].kha_nang_tuong_tac = 0;
        vat_the[so_luong_vat_the].kha_nang_dung_trong_vat_the = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.dang_duoc_trong = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.vat_pham_trong = -1;
        vat_the[so_luong_vat_the].vi_tri_ruong = -1;
        them_vat_pham(4, -1);
        thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian = random(5, 10); // tao thoi gian hoi cho vat the
        thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian *= 30;           // chuyen gio thanh phut
        thoi_gian_hoi_vat_the[so_luong_hoi].id = 1;
        thoi_gian_hoi_vat_the[so_luong_hoi].vi_tri = so_luong_vat_the;
        strcpy(thoi_gian_hoi_vat_the[so_luong_hoi].ten_vat_the, vat_the[i_tam].ten);
        vat_the_hoi = 1;
        so_luong_vat_the++;
        bo_lo();
        so_luong_hoi++;
    }
    if (vat_pham[trang_bi].id == 9)
    {
        strcpy(hanh_dong, "Ban vua dat lo nung");
        strcpy(vat_the[so_luong_vat_the].ten, "lo nung");
        vat_the[so_luong_vat_the].bieu_tuong = 'L';
        printf("%c", vat_the[so_luong_vat_the].bieu_tuong);
        vat_the[so_luong_vat_the].id = 5;
        vat_the[so_luong_vat_the].do_ben_toi_da = 1;
        vat_the[so_luong_vat_the].do_ben = vat_the[so_luong_vat_the].do_ben_toi_da;
        vat_the[so_luong_vat_the].kha_nang_tuong_tac = 1;
        vat_the[so_luong_vat_the].kha_nang_dung_trong_vat_the = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.dang_duoc_trong = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.vat_pham_trong = -1;
        vat_the[so_luong_vat_the].vi_tri_ruong = -1;
        them_vat_pham(9, -1);
        so_luong_vat_the++;
        bo_lo();
    }
    if (vat_pham[trang_bi].id == 10)
    {
        strcpy(hanh_dong, "Ban vua dat ruong go");
        strcpy(vat_the[so_luong_vat_the].ten, "ruong go");
        vat_the[so_luong_vat_the].bieu_tuong = 'R';
        printf("%c", vat_the[so_luong_vat_the].bieu_tuong);
        vat_the[so_luong_vat_the].id = 6;
        vat_the[so_luong_vat_the].do_ben_toi_da = 1;
        vat_the[so_luong_vat_the].do_ben = vat_the[so_luong_vat_the].do_ben_toi_da;
        vat_the[so_luong_vat_the].kha_nang_tuong_tac = 1;
        vat_the[so_luong_vat_the].kha_nang_dung_trong_vat_the = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.dang_duoc_trong = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.vat_pham_trong = -1;
        vat_the[so_luong_vat_the].vi_tri_ruong = so_luong_ruong;
        so_luong_ruong++;
        for (i = 0; i < so_luong_ruong - 1; i++)
        {
            if (so_luong_vat_pham_trong_ruong[i] == -1)
            {
                vat_the[so_luong_vat_the].vi_tri_ruong = i;
                so_luong_vat_pham_trong_ruong[i] = 0;
                so_luong_ruong--;
                break;
            }
        }
        them_vat_pham(10, -1);
        so_luong_vat_the++;
        bo_lo();
    }
    if (vat_pham[trang_bi].id == 3)
    {
        strcpy(hanh_dong, "Ban vua dat nho");
        strcpy(vat_the[so_luong_vat_the].ten, "bui nho");
        vat_the[so_luong_vat_the].bieu_tuong = 'N';
        printf("%c", vat_the[so_luong_vat_the].bieu_tuong);
        vat_the[so_luong_vat_the].id = 3;
        vat_the[so_luong_vat_the].do_ben_toi_da = 4;
        vat_the[so_luong_vat_the].do_ben = 0;
        vat_the[so_luong_vat_the].kha_nang_tuong_tac = 1;
        vat_the[so_luong_vat_the].kha_nang_dung_trong_vat_the = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.dang_duoc_trong = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.vat_pham_trong = -1;
        vat_the[so_luong_vat_the].vi_tri_ruong = -1;
        them_vat_pham(3, -1);
        int vi_tri_tam = so_luong_vat_the;
        vat_the_hoi = 1;
        so_luong_vat_the++;
        bo_lo();
        for (i = 0; i < 4; i++)
        {
            thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian = random(2, 3); // tao thoi gian hoi cho vat the
            thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian *= 30;          // chuyen gio thanh phut
            thoi_gian_hoi_vat_the[so_luong_hoi].id = 2;
            thoi_gian_hoi_vat_the[so_luong_hoi].vi_tri = vi_tri_tam;
            strcpy(thoi_gian_hoi_vat_the[so_luong_hoi].ten_vat_the, vat_the[i_tam].ten);
            so_luong_hoi++;
        }
    }
    if (vat_pham[trang_bi].id == 15)
        them_vat_pham(15, -1);
    if (vat_pham[trang_bi].the == 5 || vat_pham[trang_bi].id == 16)
    {
        strcpy(vat_the[so_luong_vat_the].ten, "dat da duoc xoi");
        vat_the[so_luong_vat_the].bieu_tuong = 'd';
        printf("%c", vat_the[so_luong_vat_the].bieu_tuong);
        vat_the[so_luong_vat_the].id = 8;
        vat_the[so_luong_vat_the].do_ben_toi_da = 1;
        vat_the[so_luong_vat_the].do_ben = vat_the[so_luong_vat_the].do_ben_toi_da;
        vat_the[so_luong_vat_the].kha_nang_tuong_tac = 1;
        vat_the[so_luong_vat_the].kha_nang_dung_trong_vat_the = 1;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.dang_duoc_trong = 0;
        vat_the[so_luong_vat_the].kha_nang_trong_trot.vat_pham_trong = -1;
        vat_the[so_luong_vat_the].vi_tri_ruong = -1;
        if (vat_pham[trang_bi].id == 16)
            them_vat_pham(16, -1);
        so_luong_vat_the++;
        bo_lo();
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
            vat_the[i].bieu_tuong = vat_the[so_luong_vat_the].bieu_tuong;
            vat_the[i].id = vat_the[so_luong_vat_the].id;
            vat_the[i].do_ben = vat_the[so_luong_vat_the].do_ben;
            vat_the[i].do_ben_toi_da = vat_the[so_luong_vat_the].do_ben_toi_da;
            vat_the[i].kha_nang_tuong_tac = vat_the[so_luong_vat_the].kha_nang_tuong_tac;
            vat_the[i].kha_nang_dung_trong_vat_the = vat_the[so_luong_vat_the].kha_nang_dung_trong_vat_the;
            vat_the[i].kha_nang_trong_trot.dang_duoc_trong = vat_the[so_luong_vat_the].kha_nang_trong_trot.dang_duoc_trong;
            vat_the[i].kha_nang_trong_trot.vat_pham_trong = vat_the[so_luong_vat_the].kha_nang_trong_trot.vat_pham_trong;
            vat_the[i].vi_tri_ruong = vat_the[so_luong_vat_the].vi_tri_ruong;
            if (vat_the_hoi == 1)
                thoi_gian_hoi_vat_the[so_luong_hoi].vi_tri = i; // cap nhat vi tri moi neu dung ham bo_lo
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
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0; // 0 la vat pham khong the an duoc
        vat_pham[so_luong_vat_pham].gop = 1;       // 1 la vat pham co the gop lai
        strcpy(vat_pham[so_luong_vat_pham].ten, "Khoi go");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0; // 0 la vat pham khong co chuc nang gi
    }
    if (id == 2)
    {
        vat_pham[so_luong_vat_pham].id = 2;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
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
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 1;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Chum nho");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 1; // 1 la vat pham co the dat duoc
    }
    if (id == 4)
    {
        vat_pham[so_luong_vat_pham].id = 4;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Mam cay");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 1;
    }
    if (id == 5)
    {
        vat_pham[so_luong_vat_pham].id = 5;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 0; // 0 la vat pham khong the gop duoc
        strcpy(vat_pham[so_luong_vat_pham].ten, "Riu ri set");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 2; // 2 la vat pham thuoc loai riu
    }
    if (id == 6)
    {
        vat_pham[so_luong_vat_pham].id = 6;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 0;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Cup ri set");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 3; // 3 la vat pham thuoc loai cup
    }
    if (id == 7)
    {
        vat_pham[so_luong_vat_pham].id = 7;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 2;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 0;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Riu go");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 2;
    }
    if (id == 8)
    {
        vat_pham[so_luong_vat_pham].id = 8;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 2;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 0;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Cup go");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 3;
    }
    if (id == 9)
    {
        vat_pham[so_luong_vat_pham].id = 9;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Lo nung");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 1;
    }
    if (id == 10)
    {
        vat_pham[so_luong_vat_pham].id = 10;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Ruong go");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 1;
    }
    if (id == 11)
    {
        vat_pham[so_luong_vat_pham].id = 11;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 0;
        strcpy(vat_pham[so_luong_vat_pham].ten, "The khong gian");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = -1; // -1 la vat pham dac biet
    }
    if (id == 12)
    {
        vat_pham[so_luong_vat_pham].id = 12;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Hat giong");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 6; // vat pham co the trong duoc
    }
    if (id == 13)
    {
        vat_pham[so_luong_vat_pham].id = 13;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 0;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Xeng go");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 4; // vat pham thuoc loai xeng
    }
    if (id == 14)
    {
        vat_pham[so_luong_vat_pham].id = 14;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 0;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Cuoc go");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 5; // vat pham thuoc loai cuoc
    }
    if (id == 15)
    {
        vat_pham[so_luong_vat_pham].id = 15;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Cuc dat");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 1;
    }
    if (id == 16)
    {
        vat_pham[so_luong_vat_pham].id = 16;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Cuc dat da duoc xoi");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 1;
    }
    if (id == 17)
    {
        vat_pham[so_luong_vat_pham].id = 17;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Lua mi");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0;
    }
    if (id == 18)
    {
        vat_pham[so_luong_vat_pham].id = 18;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 0;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Bot mi");
        if (so_luong_vat_pham == 0)
            vat_pham[so_luong_vat_pham].so_luong = 0 + so_luong;
        else
            vat_pham[so_luong_vat_pham].so_luong += so_luong;
        vat_pham[so_luong_vat_pham].the = 0;
    }
    if (id == 19)
    {
        vat_pham[so_luong_vat_pham].id = 19;
        vat_pham[so_luong_vat_pham].suc_cong_pha = 1;
        vat_pham[so_luong_vat_pham].co_the_an = 1;
        vat_pham[so_luong_vat_pham].gop = 1;
        strcpy(vat_pham[so_luong_vat_pham].ten, "Banh mi");
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
                if (vat_pham[i].gop == 0) // neu vat pham khong gop duoc thi tao vat pham moi
                    break;
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
        vat_pham[i].gop = vat_pham[i + 1].gop;
        vat_pham[i].suc_cong_pha = vat_pham[i + 1].suc_cong_pha;
        vat_pham[i].co_the_an = vat_pham[i + 1].co_the_an;
    }
    so_luong_vat_pham--;
    trang_bi = so_luong_vat_pham;
}

void an_thuc_an() // ham an thuc an
{
    if (vat_pham[trang_bi].id == 3)
    {
        do_doi += 10;
        vat_pham[trang_bi].so_luong--;
        if (vat_pham[trang_bi].so_luong == 0)
            xoa_vat_pham(trang_bi);
        strcpy(hanh_dong, "Ban vua an nho | + 10 do doi");
    }
    if (vat_pham[trang_bi].id == 19)
    {
        do_doi += 50;
        vat_pham[trang_bi].so_luong--;
        if (vat_pham[trang_bi].so_luong == 0)
            xoa_vat_pham(trang_bi);
        strcpy(hanh_dong, "Ban vua an banh mi | + 50 do doi");
    }
}

int kiem_tra_vat_pham(int id, int so_luong) // ham kiem tra vat pham co du so luong can thiet hay khong
{
    for (i = 0; i < so_luong_vat_pham; i++)
    {
        if (id == vat_pham[i].id)
        {
            if (vat_pham[i].so_luong >= so_luong)
                return 1;
        }
    }
    return 0;
}

void tuong_tac_vat_the() // ham kiem tra vat the co the tuong tac la gi
{
    if (vat_the[i_tam].id == 5)
    {
        chuyen_chuc_nang();
        lo_nung();
        chuyen_chuc_nang();
    }
    if (vat_the[i_tam].id == 6)
    {
        chuyen_chuc_nang();
        ruong();
        chuyen_chuc_nang();
    }
    if (vat_the[i_tam].id == 3) // tuong tac lay chum nho tu bui nho
    {
        if (vat_the[i_tam].do_ben != 0)
        {
            if (vat_pham_da_co[2] != 1)
                so_luong_vat_pham_da_co++;
            vat_pham_da_co[2] = 1;
            strcpy(hanh_dong, "Ban vua nhat nho | + 1 chum nho");
            vat_the[i_tam].do_ben--;
            them_vat_pham(3, 1);

            thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian = random(2, 3); // tao thoi gian hoi cho vat the
            thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian *= 30;          // chuyen gio thanh phut
            thoi_gian_hoi_vat_the[so_luong_hoi].id = 2;
            thoi_gian_hoi_vat_the[so_luong_hoi].vi_tri = i_tam;
            strcpy(thoi_gian_hoi_vat_the[so_luong_hoi].ten_vat_the, vat_the[i_tam].ten);
            so_luong_hoi++;
        }
    }
    if (vat_the[i_tam].id == 8 && vat_the[i_tam].kha_nang_trong_trot.dang_duoc_trong == 0 && vat_pham[trang_bi].the == 6)
    {
        strcpy(hanh_dong, "Ban vua trong hat giong");
        strcpy(thoi_gian_hoi_vat_the[so_luong_hoi].ten_vat_the, vat_the[i_tam].ten);
        char ten_vat_pham_tam[100];
        strcpy(ten_vat_pham_tam, vat_pham[trang_bi].ten);
        ten_vat_pham_tam[0] += 32;
        strcat(vat_the[i_tam].ten, " dang trong ");
        strcat(vat_the[i_tam].ten, ten_vat_pham_tam);
        vat_the[i_tam].kha_nang_trong_trot.dang_duoc_trong = 1;
        vat_the[i_tam].kha_nang_trong_trot.vat_pham_trong = vat_pham[trang_bi].id;
        them_vat_pham(12, -1);
        thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian = random(8, 10); // tao thoi gian hoi cho vat the
        thoi_gian_hoi_vat_the[so_luong_hoi].thoi_gian *= 30;           // chuyen gio thanh phut
        thoi_gian_hoi_vat_the[so_luong_hoi].id = 3;
        thoi_gian_hoi_vat_the[so_luong_hoi].vi_tri = i_tam;

        so_luong_hoi++;
    }
    if (vat_the[i_tam].id == 8 && vat_the[i_tam].kha_nang_trong_trot.dang_duoc_trong == 2)
    {
        if (vat_the[i_tam].kha_nang_trong_trot.vat_pham_trong == 12)
        {
            strcpy(hanh_dong, "Ban vua thu hoach lua mi | + 1 lua mi | + 1 hat giong");
            them_vat_pham(12, 1);
            them_vat_pham(17, 1);
            strcpy(vat_the[i_tam].ten, "dat da duoc xoi");
            vat_the[i_tam].kha_nang_trong_trot.dang_duoc_trong = 0;
        }
    }
    if (vat_the[i_tam].id == 9 && do_khat < 100)
    {
        strcpy(hanh_dong, "Ban vua uong nuoc | + 5 do khat");
        do_khat += 5;
    }
}

void xoa_vat_pham_ruong(int vi_tri_xoa) // ham xoa vat pham trong ruong
{
    for (i = vi_tri_xoa; i < so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]; i++)
    {
        vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].id = vat_the_ruong[i + 1][vat_the[i_tam].vi_tri_ruong].id;
        strcpy(vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].ten, vat_the_ruong[i + 1][vat_the[i_tam].vi_tri_ruong].ten);
        vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].so_luong = vat_the_ruong[i + 1][vat_the[i_tam].vi_tri_ruong].so_luong;
        vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].the = vat_the_ruong[i + 1][vat_the[i_tam].vi_tri_ruong].the;
        vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].gop = vat_the_ruong[i + 1][vat_the[i_tam].vi_tri_ruong].gop;
        vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].suc_cong_pha = vat_the_ruong[i + 1][vat_the[i_tam].vi_tri_ruong].suc_cong_pha;
        vat_the_ruong[i][vat_the[i_tam].vi_tri_ruong].co_the_an = vat_the_ruong[i + 1][vat_the[i_tam].vi_tri_ruong].co_the_an;
    }
    so_luong_vat_pham_trong_ruong[vat_the[i_tam].vi_tri_ruong]--;
}