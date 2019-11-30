#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define ligne 10
#define colone 4
#define VRAI 1
#define FAUX 0
#define ROUGE 3
#define BLEU 4
#define VERT 5
#define JEUN 6
#define NOIR 7
#define BLANC 8
#define FIN 273
#define QUITER -4
#define SAVE 314

SDL_Rect table[ligne][colone];
SDL_Surface *back, *ecran = NULL, *tab = NULL, *boulV = NULL, *boulR = NULL, *boulB = NULL, *boulJ = NULL, *boulBL = NULL, *boulN = NULL;
SDL_Surface *indicateur;
SDL_Event event;
SDL_Surface *table1;
SDL_Rect tab1;
int table_jeux[ligne][colone] = {FAUX}, codee[colone] = {FAUX};

void code_test(int table_jeux[ligne][colone], int code[colone], int *ind_B, int *ind_N, int ligne_actu)
{
    int T[4] = {0, 0, 0, 0}, T1[4] = {0, 0, 0, 0}, i, j;
    *ind_B = 0;
    *ind_N = 0;
    for (i = 0; i < 4; i++)
    {
        if (table_jeux[ligne_actu][i] == code[i])
        {
            (*ind_N) = (*ind_N) + 1;
            T[i] = 1;
            T1[i] = 1;
        }
    }
    for (i = 0; i < 4; i++)
    {
        if (T[i] == 0)
        {
            for (j = 0; j < 4; j++)
            {
                if (T1[j] == 0 && T[i] == 0)
                {
                    if (table_jeux[ligne_actu][j] == code[i])
                    {
                        (*ind_B) = (*ind_B) + 1;
                        T[i] = 1;
                        T1[j] = 1;
                    }
                }
            }
        }
    }
}
void afficher_imag(SDL_Surface *img, int xx, int yy, char *c)
{
    SDL_Rect P;

    P.x = xx;
    P.y = yy;

    img = IMG_Load(c);
    SDL_BlitSurface(img, NULL, ecran, &P);
    SDL_FreeSurface(img);
}
void afficher_boul()
{

    afficher_imag(boulV, 538, 579, "icons/vert.PNG");
    afficher_imag(boulJ, 538, 491, "icons/jeun.PNG");
    afficher_imag(boulB, 538, 405, "icons/bleu.PNG");
    afficher_imag(boulR, 538, 319, "icons/rouge.PNG");
    afficher_imag(boulN, 538, 231, "icons/noir.PNG");
    afficher_imag(boulB, 538, 145, "icons/blanc.PNG");
}
void afficher_indic(int Nbr_ligne, int Ind_N, int Ind_B)
{
    if (Ind_N == 2 && Ind_B == 0)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 0 && Ind_B == 4)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 611 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
    }
    if (Ind_N == 1 && Ind_B == 3)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 2 && Ind_B == 2)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 964, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 3 && Ind_B == 1)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 964, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 4 && Ind_B == 0)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 964, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 0 && Ind_B == 1)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
    }
    if (Ind_N == 0 && Ind_B == 2)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
    }
    if (Ind_N == 0 && Ind_B == 3)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
    }
    if (Ind_N == 1 && Ind_B == 1)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 2 && Ind_B == 1)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 0 && Ind_B == 2)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
    }
    if (Ind_N == 1 && Ind_B == 2)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }

    if (Ind_N == 0 && Ind_B == 3)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
    }
    if (Ind_N == 1 && Ind_B == 0)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
    if (Ind_N == 2 && Ind_B == 1)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_B.PNG");
    }
    if (Ind_N == 3 && Ind_B == 0)
    {
        afficher_imag(table1, 994, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 964, 629 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
        afficher_imag(table1, 994, 611 - (55.5 * Nbr_ligne), "icons/ind_N.PNG");
    }
}
int clic(int xx, int yy, int ww, int hh)
{

    SDL_Event event;
    int cont = 1, B = 0;

    while (cont)
    {

        SDL_WaitEvent(&event);

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if ((event.button.x >= xx && event.button.x <= (xx + ww)) && (event.button.y >= yy && (yy + hh) >= event.button.y))
            {
                B = 1;
            }
            cont = 0;
        }
        else if (event.type == SDL_QUIT)
        {
            cont = 0;
        }
    }
    return B;
}
int clic_boul()
{
    int color = VRAI;
    SDL_Event clic_b;
    while (color == VRAI)

    {

        SDL_WaitEvent(&clic_b);

        if (clic_b.type == SDL_MOUSEBUTTONUP)
        {
            if (clic_b.button.button == SDL_BUTTON_LEFT)
            {

                if (clic_b.button.x >= 541 && clic_b.button.x <= (541 + 32) && (clic_b.button.y >= 147 && (147 + 32) >= clic_b.button.y))
                {
                    color = BLANC;
                }
                if (clic_b.button.x >= 541 && clic_b.button.x <= (541 + 32) && (clic_b.button.y >= 235 && (235 + 32) >= clic_b.button.y))
                {
                    color = NOIR;
                }
                if (clic_b.button.x >= 541 && clic_b.button.x <= (541 + 32) && (clic_b.button.y >= 322 && (322 + 32) >= clic_b.button.y))
                {
                    color = ROUGE;
                }
                if (clic_b.button.x >= 541 && clic_b.button.x <= (541 + 32) && (clic_b.button.y >= 408 && (408 + 32) >= clic_b.button.y))
                {
                    color = BLEU;
                }
                if (clic_b.button.x >= 541 && clic_b.button.x <= (541 + 32) && (clic_b.button.y >= 494 && (494 + 32) >= clic_b.button.y))
                {
                    color = JEUN;
                }
                if (clic_b.button.x >= 541 && clic_b.button.x <= (541 + 32) && (clic_b.button.y >= 582 && (582 + 32) >= clic_b.button.y))
                {
                    color = VERT;
                }
                if (clic_b.button.x >= 0 && clic_b.button.x <= (380) && (clic_b.button.y >= 0 && (185) >= clic_b.button.y))
                {
                    color = FIN;
                }
                if (clic_b.button.x >= 0 && clic_b.button.x <= (380) && (clic_b.button.y >= 186 && (370) >= clic_b.button.y))
                {
                    color = SAVE;
                }
            }
        }
        if (clic_b.type == SDL_QUIT)
        {
            color = QUITER;
        }
    }

    return color;
}
void afficher_Position_ligne(int L, int C, int color)
{
    switch (color)
    {

    case BLANC:

        afficher_imag(boulBL, 642.2 + (69.6 * (C - 1)), 610.7 - (55.6 * (L - 1) - 1), "icons/blanc.PNG");

        SDL_Flip(ecran);

        break;
    case NOIR:

        afficher_imag(boulBL, 642.2 + (69.6 * (C - 1)), 610.7 - (55.6 * (L - 1) - 1), "icons/noir.PNG");
        SDL_Flip(ecran);

        break;
    case ROUGE:

        afficher_imag(boulBL, 642.2 + (69.6 * (C - 1)), 610.7 - (55.6 * (L - 1) - 1), "icons/rouge.PNG");
        SDL_Flip(ecran);

        break;
    case JEUN:

        afficher_imag(boulBL, 642.2 + (69.6 * (C - 1)), 610.7 - (55.6 * (L - 1) - 1), "icons/jeun.PNG");
        SDL_Flip(ecran);

        break;

    case VERT:

        afficher_imag(boulBL, 642.2 + (69.6 * (C - 1)), 610.7 - (55.6 * (L - 1) - 1), "icons/vert.PNG");
        SDL_Flip(ecran);

        break;
    case BLEU:

        afficher_imag(boulBL, 642.2 + (69.6 * (C - 1)), 610.7 - (55.6 * (L - 1) - 1), "icons/bleu.PNG");
        SDL_Flip(ecran);

        break;
    }
}
int afficher_ligne(int nb_ligne, int codee[colone])
{

    FILE *F;
    int i = 0, couleur = FAUX, k, k1;
    int IndisN, IndisB;
    while (i < 4)

    {
        couleur = clic_boul();
        if (couleur != FAUX && couleur != FIN && couleur != QUITER && couleur != SAVE)
        {
            table_jeux[nb_ligne - 1][i] = couleur;
            afficher_Position_ligne(nb_ligne, i + 1, couleur);
            SDL_Flip(ecran);
            i++;
        }
        if (couleur == QUITER)
        {
            return QUITER;
        }
        if (couleur == FIN)
        {
            return FIN;
        }
        if (couleur == SAVE)
        {
            F = fopen("load_game.txt", "w+");
            for (k = 0; k < nb_ligne; k++)
            {
                for (k1 = 0; k1 < 4; k1++)
                {
                    if (table_jeux[k][k1] != SAVE)
                        fprintf(F, "%d ", table_jeux[k][k1]);
                }
            }
            fclose(F);
            F = fopen("load_code.txt", "w+");
            for (k = 0; k < 4; k++)
            {
                fprintf(F, "%d ", codee[k]);
            }
            fclose(F);
        }
    }
    code_test(table_jeux, codee, &IndisB, &IndisN, (nb_ligne - 1));
    afficher_indic(nb_ligne - 1, IndisN, IndisB);
    SDL_Flip(ecran);

    return IndisN;
}
int code(int *codee[colone])
{
    int i = 0, couleur = VRAI;

    while (i < 4 && couleur != QUITER && couleur != FIN)

    {

        couleur = clic_boul();
        codee[i] = couleur;
        switch (couleur)
        {

        case BLANC:
            afficher_imag(boulB, 641 + (69 * (i) + 1), 58, "icons/blanc.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case NOIR:
            afficher_imag(boulBL, 641 + (69 * (i) + 1), 58, "icons/noir.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case ROUGE:
            afficher_imag(boulBL, 642 + (69 * (i) + 1), 58, "icons/rouge.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case JEUN:
            afficher_imag(boulBL, 642 + (69 * (i) + 1), 58, "icons/jeun.PNG");
            SDL_Flip(ecran);
            i++;
            break;

        case VERT:
            afficher_imag(boulBL, 642 + (69 * (i) + 1), 58, "icons/vert.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case BLEU:
            afficher_imag(boulBL, 642 + (69 * (i) + 1), 58, "icons/bleu.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        }
    }

    if (couleur == QUITER)
        return QUITER;
    else if (couleur == FIN)
        return FIN;
    else
    {
        afficher_imag(boulBL, 630, 38, "images/pinkbar.PNG");
        SDL_Flip(ecran);
        return 20;
    }
}
void afficher_code(int codee[colone])
{
    int i = 0, couleur;
    SDL_Delay(1000);
    afficher_imag(boulBL, 632, 40, "images/inputbar.PNG");
    SDL_Flip(ecran);
    while (i < 4)

    {
        couleur = codee[i];
        switch (couleur)
        {

        case BLANC:
            afficher_imag(boulB, 639 + (69 * (i) + 1), 58, "icons/blanc.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case NOIR:
            afficher_imag(boulBL, 639 + (69 * (i) + 1), 58, "icons/noir.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case ROUGE:
            afficher_imag(boulBL, 639 + (69 * (i) + 1), 58, "icons/rouge.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case JEUN:
            afficher_imag(boulBL, 639 + (69 * (i) + 1), 58, "icons/jeun.PNG");
            SDL_Flip(ecran);
            i++;
            break;

        case VERT:
            afficher_imag(boulBL, 639 + (69 * (i) + 1), 58, "icons/vert.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        case BLEU:
            afficher_imag(boulBL, 639 + (69 * (i) + 1), 58, "icons/bleu.PNG");
            SDL_Flip(ecran);
            i++;
            break;
        }
    }
}
void partie()
{

    afficher_imag(tab, 0, 0, "images/splashScreen.PNG");

    SDL_Flip(ecran);
    SDL_Delay(1000);
    int k = 1, ind_noir = 20, nombre_aleatoire, C, VAR_tmp, CN = 0, CN1 = 0, CN2 = 0, CN3 = 0, N = 0, B = 0, color = FAUX;
    FILE *L;

    int continuer = 1;
    SDL_Event event_i;

etiq:
    afficher_imag(tab, 0, 0, "images/tab.PNG");

    CN = 0;
    CN1 = 0;
    CN2 = 0;
    CN3 = 0;
    N = 0;
    B = 0;
    color = FAUX;

    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event_i);

        if (event_i.type == SDL_MOUSEBUTTONUP)
        {
            if (event_i.button.x >= 530 && event_i.button.x <= (800) && (event_i.button.y >= 20 && (100) >= event_i.button.y))
            {
                SDL_Delay(1000);
                afficher_imag(tab, 00, 00, "images/back.JPG");
                afficher_imag(tab, 500, 30, "images/mainScreen.PNG");
                afficher_boul();
                afficher_imag(boulBL, 630, 38, "images/pinkbar.PNG");

                afficher_imag(boulB, 0, 0, "images/fin.PNG");
                afficher_imag(boulB, 0, 186, "images/sauvgarder.PNG");

                SDL_Flip(ecran);
                srand(time(NULL)); // initialisation de rand
                for (C = 0; C < 4; C++)
                {
                    nombre_aleatoire = rand();
                    nombre_aleatoire = nombre_aleatoire % 9;
                    if (nombre_aleatoire < 3)
                    {
                        nombre_aleatoire = nombre_aleatoire + 3;
                    }

                    codee[C] = nombre_aleatoire;
                }

                k = 1;
                while (k <= 10)
                {

                    ind_noir = afficher_ligne(k, codee);
                    if (ind_noir == 4)
                    {

                        afficher_code(codee);
                        afficher_imag(boulB, 00, 00, "images/bravo.PNG");

                        goto etiq;
                    }
                    if (ind_noir == QUITER)
                    {
                        continuer = 0;
                        break;
                    }
                    if (ind_noir == FIN)
                    {
                        goto etiq;
                    }

                    k++;
                }
                if (k == 11)
                {
                    afficher_code(codee);
                    SDL_Delay(5000);

                    goto etiq;
                }
            }

            if (event_i.button.x >= 450 && event_i.button.x <= (900) && (event_i.button.y >= 200 && (300) >= event_i.button.y))
            {

                afficher_imag(tab, 00, 00, "images/back.JPG");
                afficher_imag(tab, 500, 30, "images/mainScreen.PNG");
                afficher_boul();
                afficher_imag(boulB, 0, 0, "images/fin.PNG");
                afficher_imag(boulB, 0, 186, "images/sauvgarder.PNG");
                SDL_Flip(ecran);
                ind_noir = code(&codee);
                if (ind_noir == QUITER)
                {
                    k = 12;
                    continuer = 0;
                }
                else if (ind_noir == FIN)
                {
                    goto etiq;
                }
                else
                    k = 1;

                while (k <= 10)
                {

                    ind_noir = afficher_ligne(k, codee);
                    if (ind_noir == 4)
                    {
                        afficher_code(codee);
                        SDL_Delay(5000);
                        afficher_imag(boulB, 00, 00, "images/bravo.PNG");
                        SDL_Flip(ecran);
                        SDL_Delay(1000);

                        goto etiq;
                    }
                    else if (ind_noir == QUITER)
                    {
                        continuer = 0;
                        break;
                    }
                    if (ind_noir == FIN)
                    {
                        goto etiq;
                    }

                    k++;
                }
                if (k == 11)
                {
                    afficher_code(codee);
                    goto etiq;
                }
            }
            if (event_i.button.x >= 530 && event_i.button.x <= (870) && (event_i.button.y >= 530 && (650) >= event_i.button.y))
            {
                continuer = 0;
            }
            if (event_i.button.x >= 200 && event_i.button.x <= (1140) && (event_i.button.y >= 350 && (440) >= event_i.button.y))
            {
                afficher_imag(tab, 00, 00, "images/back.JPG");
                afficher_imag(tab, 500, 30, "images/mainScreen.PNG");
                afficher_boul();
                afficher_imag(boulB, 0, 0, "images/fin.PNG");
                afficher_imag(boulB, 0, 186, "images/sauvgarder.PNG");
                afficher_imag(boulBL, 630, 38, "images/pinkbar.PNG");
                SDL_Flip(ecran);

                L = fopen("load_game.txt", "r");
                while (fscanf(L, "%d ", &VAR_tmp) != EOF)
                {
                    if (VAR_tmp != FAUX)
                    {
                        if (CN1 == 4)
                        {
                            CN1 = 0;
                            CN++;
                        }
                        afficher_Position_ligne(CN + 1, CN1 + 1, VAR_tmp);
                        table_jeux[CN][CN1] = VAR_tmp;
                        CN1++;
                    }
                }
                fclose(L);

                L = fopen("load_code.txt", "r");
                while (CN2 < 4 && fscanf(L, "%d ", &codee[CN2]) != EOF)
                {
                    CN2++;
                }

                if (CN1 == 4)
                {
                    CN = CN + 2;
                    for (CN2 = 0; CN2 < CN; CN2++)
                    {
                        code_test(table_jeux, codee, &B, &N, CN2);
                        afficher_indic(CN2, N, B);
                        SDL_Flip(ecran);
                    }
                }
                else
                {
                    CN = CN + 1;
                    for (CN2 = 0; (CN2 + 1) < CN; CN2++)
                    {
                        code_test(table_jeux, codee, &B, &N, CN2);
                        afficher_indic(CN2, N, B);
                        SDL_Flip(ecran);
                    }

                    while (CN1 < 4)

                    {
                        color = clic_boul();
                        if (color != FAUX && color != FIN && color != QUITER)
                        {
                            table_jeux[CN - 1][CN1] = color;
                            afficher_Position_ligne(CN, CN1 + 1, color);
                            SDL_Flip(ecran);
                            CN1++;
                        }

                        if (color == QUITER)
                        {

                            break;
                        }
                        if (color == FIN)
                        {
                            goto etiq;
                        }
                        if (color == SAVE)
                        {
                            L = fopen("load_game.txt", "w+");

                            for (CN2 = 0; CN2 < CN; CN2++)
                            {
                                for (CN3 = 0; CN3 < 4; CN3++)
                                {
                                    if (table_jeux[CN2][CN3] != SAVE)
                                        fprintf(L, "%d ", table_jeux[CN2][CN3]);
                                }
                            }
                            fclose(L);
                            L = fopen("load_code.txt", "w+");
                            for (CN2 = 0; CN2 < 4; CN2++)
                            {
                                fprintf(L, "%d ", codee[CN2]);
                            }
                            fclose(L);
                        }
                    }
                    code_test(table_jeux, codee, &B, &N, (CN - 1));
                    afficher_indic(CN - 1, N, B);
                    SDL_Flip(ecran);
                    if (N == 4)
                    {
                        afficher_code(codee);
                        SDL_Delay(5000);
                        afficher_imag(boulB, 00, 00, "images/bravo.PNG");
                        SDL_Flip(ecran);
                        SDL_Delay(1000);
                        goto etiq;
                    }

                    CN++;
                }
                if (color != QUITER)
                {

                    k = CN;

                    while (k <= 10)
                    {

                        ind_noir = afficher_ligne(k, codee);
                        if (ind_noir == 4)
                        {
                            afficher_code(codee);
                            SDL_Delay(5000);
                            afficher_imag(boulB, 00, 00, "images/bravo.PNG");
                            SDL_Flip(ecran);
                            SDL_Delay(1000);

                            goto etiq;
                        }
                        else if (ind_noir == QUITER)
                        {
                            continuer = 0;
                            break;
                        }
                        if (ind_noir == FIN)
                        {
                            goto etiq;
                        }

                        k++;
                    }
                    if (k == 11)
                    {
                        afficher_code(codee);
                        SDL_Delay(1000);
                        goto etiq;
                    }
                }
                else
                    break;
            }
        }

        if (event_i.type == SDL_QUIT)
        {
            continuer = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int i = 0, j = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != -1)
    {
        ecran = SDL_SetVideoMode(1327, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
        partie();

        SDL_Quit();
        return EXIT_SUCCESS;
    }
}
