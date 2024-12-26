#include <curses.h>
#include <stdio.h>
#include <stdlib.h>  //pt functia rand
#include <time.h>

#define FOREVER 1
#define INIT_ROW 20
#define INIT_COL 20

void afisareInstructiuni(WINDOW *wnd) {
    // Functie pt afisarea instructiunilor atunci cand suntem in joc
    // Aplicare culoare la text
    wattron(wnd, COLOR_PAIR(2) | A_BOLD);
    // Afisam in partea din dreapta sus a ecranului
    mvwaddstr(wnd, 1, COLS - 36, "Puteti face mutari folosind tastele:");
    mvwaddstr(wnd, 2, COLS - 36, "A/a - stanga                          ");
    mvwaddstr(wnd, 3, COLS - 36, "D/d - dreapta                         ");
    mvwaddstr(wnd, 4, COLS - 36, "W/w - sus                             ");
    mvwaddstr(wnd, 5, COLS - 36, "S/s - jos                             ");
    mvwaddstr(wnd, 6, COLS - 36, "Pentru iesire, apasati tasta Q/q.     ");
    // Dezactivare culoare
    wattroff(wnd, COLOR_PAIR(2) | A_BOLD);
}

void centrare(WINDOW *fereastra) {
    // functie pt a centra o fereastra
    int x, y, z, t,noux,nouy;
    // Aflam dimensiunile ecranului
    getmaxyx(stdscr, x, y);
    // Aflam dimensiunile ferestrei
    getmaxyx(fereastra, z, t);
    // Aflam noile coordonate pentru a centra fereastra
    noux = (x - z) / 2;
    nouy = (y - t) / 2;
    // Mutam fereastra la noile coordonate
    mvwin(fereastra, noux, nouy);
}

void afisare2048(WINDOW *wnd) {
    int coll = 0;
    // functie pt afisarea pe ecran a numarului 2048
    // centram scrisul
    coll = (COLS - INIT_COL) / 2;
    wattron(wnd, COLOR_PAIR(2) | A_BOLD);
    // am cautat coordonate astfel incat sa se vada cat mai bine
    mvwaddch(wnd, 4, coll - 10, '+');
    mvwaddch(wnd, 3, coll - 8, '+');
    mvwaddch(wnd, 3, coll - 5, '+');
    mvwaddch(wnd, 4, coll - 4, '+');
    mvwaddch(wnd, 5, coll - 6, '+');
    mvwaddch(wnd, 6, coll - 8, '+');
    mvwaddch(wnd, 4, coll - 10, '+');
    mvwaddch(wnd, 7, coll - 10, '+');
    mvwaddch(wnd, 7, coll - 6, '+');
    mvwaddch(wnd, 7, coll - 8, '+');
    mvwaddch(wnd, 7, coll - 4, '+');

    mvwaddch(wnd, 3, coll + 3, '*');
    mvwaddch(wnd, 3, coll + 5, '*');
    mvwaddch(wnd, 4, coll + 1, '*');
    mvwaddch(wnd, 4, coll + 7, '*');
    mvwaddch(wnd, 5, coll + 1, '*');
    mvwaddch(wnd, 5, coll + 7, '*');
    mvwaddch(wnd, 6, coll + 1, '*');
    mvwaddch(wnd, 6, coll + 7, '*');
    mvwaddch(wnd, 7, coll + 3, '*');
    mvwaddch(wnd, 7, coll + 5, '*');

    mvwaddch(wnd, 3, coll + 12, '+');
    mvwaddch(wnd, 4, coll + 12, '+');
    mvwaddch(wnd, 5, coll + 12, '+');
    mvwaddch(wnd, 5, coll + 14, '+');
    mvwaddch(wnd, 5, coll + 16, '+');
    mvwaddch(wnd, 5, coll + 18, '+');
    mvwaddch(wnd, 6, coll + 18, '+');
    mvwaddch(wnd, 7, coll + 18, '+');
    mvwaddch(wnd, 5, coll + 18, '+');
    mvwaddch(wnd, 4, coll + 18, '+');
    mvwaddch(wnd, 3, coll + 18, '+');

    mvwaddch(wnd, 3, coll + 27, '*');
    mvwaddch(wnd, 3, coll + 29, '*');
    mvwaddch(wnd, 7, coll + 27, '*');
    mvwaddch(wnd, 7, coll + 29, '*');
    mvwaddch(wnd, 4, coll + 25, '*');
    mvwaddch(wnd, 4, coll + 31, '*');
    mvwaddch(wnd, 6, coll + 25, '*');
    mvwaddch(wnd, 6, coll + 31, '*');
    mvwaddch(wnd, 5, coll + 29, '*');
    mvwaddch(wnd, 5, coll + 27, '*');
    wattroff(wnd, COLOR_PAIR(2) | A_BOLD);
}

void afisareReguliJoc(WINDOW *wnd) {
    // functie pentru afisarea regulilor
    int tasta;
    // facem o noua fereastra, pe care o si centram
    WINDOW *reguli = newwin(10, 70, 5, 5);
    centrare(reguli);
    wattron(reguli, COLOR_PAIR(2) | A_BOLD);
    mvwaddstr(
        reguli, 1, 1,
        "                      REGULI JOC:                                  ");
    mvwaddstr(
        reguli, 2, 1,
        "                                                                   ");
    mvwaddstr(
        reguli, 3, 1,
        "1. Utilizati tastele A, D, W, S pentru a face mutari               ");
    mvwaddstr(
        reguli, 4, 1,
        "2. Obiectivul este sa obtineti numarul 2048                        ");
    mvwaddstr(
        reguli, 5, 1,
        "3. Combinati doua blocuri cu acelasi numar pentru a le aduna       ");
    mvwaddstr(
        reguli, 6, 1,
        "4. Blocurile se vor deplasa în directia specificata pana cand      ");
    mvwaddstr(
        reguli, 7, 1,
        "   vor lovi un perete sau se vor imbina cu un bloc de acelasi numar");
    mvwaddstr(
        reguli, 8, 1,
        "5. Apasati 'q' pentru a va intoarce la meniul principal            ");
    wattroff(reguli, COLOR_PAIR(2) | A_BOLD);
    // Actualizam fereastra
    wrefresh(reguli);
    while (FOREVER) {
        tasta = wgetch(reguli);  // Preluam comanda de la utilizator
        if (tasta == 'q') {
            // Daca este apasata tasta q, iesim din fereastra si
            // afisam din nou fereastra initiala cu meniul si scrisul "2048"
            werase(reguli);
            wrefresh(reguli);
            delwin(reguli);
            afisare2048(wnd);
            wrefresh(wnd);
            return;
        }
    }
}

void scormaxim(WINDOW *wnd, int *mx1, int *mx2, int *mx3) {
    // functie pentru afisarea celor mai mari 3 scoruri
    int tasta;
    // facem o noua fereastra, pe care o si centram
    WINDOW *scormax = newwin(12, 27, 6, 6);
    box(scormax, 0, 0);
    centrare(scormax);
    wattron(scormax, COLOR_PAIR(2) | A_BOLD);
    // afisam  cele 3 scoruri, doar daca exista
    mvwprintw(scormax, 3, 5, "Scor 1:  %d", *mx1);
    if (*mx2 > 0) mvwprintw(scormax, 5, 5, "Scor 2:  %d", *mx2);
    if (*mx3 > 0) mvwprintw(scormax, 7, 5, "Scor 3:  %d", *mx3);
    mvwprintw(scormax, 9, 5, "Apasati tasta 'q'");
    mvwprintw(scormax, 10, 5, "pt a reveni la meniu");
    wattroff(scormax, COLOR_PAIR(2) | A_BOLD);
    // actualizam fereastra
    wrefresh(scormax);
    while (FOREVER) {
        tasta = wgetch(scormax);  // Preluam comanda de la utilizator
        if (tasta == 'q') {
            // daca este apasata tasta q, iesim din fereastra
            // si afisam din nou fereastra initiala, cu meniul si scrisul "2048"
            werase(scormax);
            wrefresh(scormax);
            delwin(scormax);
            afisare2048(wnd);
            wrefresh(wnd);
            return;
        }
    }
}

int afismeniu(WINDOW *meniu, int optiunecurenta) {
    // functie pentru afisarea meniului principal
    int alegereoptiune = -1, c = 0;
    // Activam modul keypad pentru fereastra meniului
    keypad(meniu, TRUE);
    while (FOREVER) {
        // afisam meniul
        wattron(meniu, A_BOLD | COLOR_PAIR(2));
        mvwaddstr(meniu, 1, 1, "      MENU        ");
        mvwaddstr(meniu, 2, 1, "                  ");
        mvwaddstr(meniu, 3, 1, " 1. New Game      ");
        mvwaddstr(meniu, 4, 1, " 2. Resume        ");
        mvwaddstr(meniu, 5, 1, " 3. Quit          ");
        mvwaddstr(meniu, 6, 1, " 4. How to play   ");
        mvwaddstr(meniu, 7, 1, " 5. High scores   ");
        wattroff(meniu, A_BOLD | COLOR_PAIR(2));

        // Punem efect de highlight pe opțiunea curentă
        wattron(meniu, A_REVERSE);
        // highlight-ul e pus initial pe cifra 1, adica a 3-a linie
        // highlight-ul o sa fie pus pe cifra corespunzatoare
        // optiunii, adica pe a 2-a coloana
        mvwaddch(meniu, optiunecurenta + 3, 2, ' ');
        wattroff(meniu, A_REVERSE);
        box(meniu, 0, 0);
        // actualizam fereastra
        wrefresh(meniu);

        // Preluam comanda de la utilizator din fereastra meniului
        c = wgetch(meniu);
        switch (c) {
            case KEY_UP:
                // Mergem sus în meniu, dar nu depășim limita superioară
                if (optiunecurenta > 0) {
                    optiunecurenta--;
                }
                break;
            case KEY_DOWN:
                // Mergem jos în meniu, dar nu depășim limita inferioară
                if (optiunecurenta < 4) {
                    optiunecurenta++;
                }
                break;
            case 'q':  // daca e apasata tasta q, inchidem meniul, returnand
                       // optiunea de alegerea 2
                alegereoptiune = 2;
                break;
            case 10:  // Enter
                // Returnăm opțiunea selectată
                alegereoptiune = optiunecurenta;
                break;
            default:
                // Alte taste nu sunt relevante
                break;
        }
        if (alegereoptiune != -1) {
            // Ieșim din while dacă s-a făcut o alegere
            break;
        }
    }
    return alegereoptiune;  // returnam alegerea facuta
}

void stergereinstructiuni(WINDOW *wnd) {
    //functie pentru stergerea instructiunilor din coltul din dreapta sus
    //o folosim atunci cand iesim din joc
    mvwprintw(wnd, 1, COLS - 36, "                                      ");
    mvwprintw(wnd, 2, COLS - 36, "                                      ");
    mvwprintw(wnd, 3, COLS - 36, "                                      ");
    mvwprintw(wnd, 4, COLS - 36, "                                      ");
    mvwprintw(wnd, 5, COLS - 36, "                                      ");
    mvwprintw(wnd, 6, COLS - 36, "                                      ");
    wrefresh(wnd);
}

void generareNumere(int a[2]) { 
     // functie pentru a genera o pozitie random de pe tabla
     //punem in vector pe pozitia 0 indicele coloanei,
     //iar pe pozitia 1 indicele liniei
        a[0] = (rand() % 4) * 5 + 1;  // indice pt coloana 
        a[1] = (rand() % 4) * 2 + 1;  // indice pt linie
}

void afisareNumarPeTabla(WINDOW *tabla, int a[2]) {
    //functie pentru afisarea numerelor pe tabla
    int random=0;
    //generam un numar random dintre 2 si 4 
    random = (rand() % 2 == 0) ? 2 : 4;
    while (mvwinch(tabla, a[1], a[0]) != ' ') {
        // Dacă este ocupată pozitia, se genereaza alta
        generareNumere(a);
    }
    //se afiseaza pe tabla
    mvwprintw(tabla, a[1], a[0], "%d", random);
}

void mutareinsus(WINDOW *tabla, int mat[4][4], int *punctaj) {
    int j, i, nr, prima;
    j = 0;
    while (j < 4) {
        // Variabilă pentru a reține prima poziție liberă în coloană
        prima = 0;
        // Parcurgem fiecare linie în coloana curentă
        for (i = 0; i < 4; i++) {
            if (mat[i][j] != 0) {
                // Mutăm elementul la prima poziție liberă
                mat[prima][j] = mat[i][j];
                nr = 0;
                if (prima > 0 &&
                    mat[prima - 1][j] == mat[prima][j]) {
                    // Combinam elementele și actualizam punctajul
                    mat[prima - 1][j] = mat[prima - 1][j]*2;
                    *punctaj = *punctaj + mat[prima - 1][j];
                    mat[prima][j] = 0;
                    nr++;
                }
                // Ștergem vechea poziție a caracterului
                mvwprintw(tabla, i * 2 + 1, j * 5 + 1, "    ");
                if (nr == 0)
                // Actualizam poziția noului caracter
                {
                    mvwprintw(tabla, prima * 2 + 1, j * 5 + 1, "%d",
                              mat[prima][j]);
                } else {
                    mvwprintw(tabla, (prima - 1) * 2 + 1, j * 5 + 1, "%d",
                              mat[prima - 1][j]);
                    prima--;
                }
                prima++;
            }
        }
        j++;
    }
    wrefresh(tabla);
}

void mutareinjos(WINDOW *tabla, int mat[4][4], int *punctaj) {
    int j, i, nr, ultima;
    j = 3;
    while (j >= 0) {
        // Variabilă pentru a reține ultima poziție liberă în coloana
        ultima = 3;
        // Parcurgem fiecare linie în coloana curentă
        for (i = 3; i >= 0; i--) {
            if (mat[i][j] != 0) {
                // Mutăm elementul la ultima poziție liberă
                mat[ultima][j] = mat[i][j];
                nr = 0;
                if (ultima < 3 &&
                    mat[ultima + 1][j] == mat[ultima][j]) {
                    // Combinam elementele și actualizam punctajul
                    mat[ultima + 1][j] = mat[ultima + 1][j]*2;
                    *punctaj = *punctaj + mat[ultima + 1][j];
                    mat[ultima][j] = 0;
                    nr++;
                }
                // Ștergem vechea poziție a caracterului
                mvwprintw(tabla, i * 2 + 1, j * 5 + 1, "    ");
                if (nr == 0) {
                    // Actualizam poziția noului caracter
                    mvwprintw(tabla, ultima * 2 + 1, j * 5 + 1, "%d",
                              mat[ultima][j]);
                } else {
                    mvwprintw(tabla, (ultima + 1) * 2 + 1, j * 5 + 1, "%d",
                              mat[ultima + 1][j]);
                    ultima++;
                }
                ultima--;
            }
        }
        j--;
    }
    wrefresh(tabla);
}

void mutareindreapta(WINDOW *tabla, int mat[4][4], int *punctaj) {
    int j, i, nr, ultima;
    i = 0;
    while (i < 4) {
        // Variabilă pentru a reține ultima poziție liberă în linie
        ultima = 3;
        // Parcurgem fiecare coloana în linia curentă
        for (j = 3; j >= 0; j--) {
            if (mat[i][j] != 0) {
                // Mutăm elementul la prima poziție liberă
                mat[i][ultima] = mat[i][j];
                nr = 0;
                if (ultima < 3 &&
                    mat[i][ultima + 1] == mat[i][ultima]) {
                    // Combinam elementele și actualizam punctajul
                    mat[i][ultima + 1] = mat[i][ultima + 1] * 2;
                    *punctaj =*punctaj + mat[i][ultima + 1];
                    mat[i][ultima] = 0;
                    nr++;
                }
                // Ștergem vechea poziție a caracterului
                mvwprintw(tabla, i * 2 + 1, j * 5 + 1, "    ");
                if (nr == 0) {
                    // Actualizam poziția noului caracter
                    mvwprintw(tabla, i * 2 + 1, ultima * 5 + 1, "%d",
                              mat[i][ultima]);
                } else {
                    mvwprintw(tabla, i * 2 + 1, (ultima + 1) * 5 + 1, "%d",
                              mat[i][ultima + 1]);
                    ultima++;
                }
                ultima--;
            }
        }
        i++;
    }
    wrefresh(tabla);
}

void mutareinstanga(WINDOW *tabla, int mat[4][4], int *punctaj) {
    int j, i, nr, prima;
    i = 3;
    while (i >= 0) {
        // Variabilă pentru a reține prima poziție liberă în linie
         prima = 0;
        // Parcurgem fiecare coloana în linia curentă
        for (j = 0; j < 4; j++) {
            if (mat[i][j] != 0) {
                // Mutăm elementul la prima poziție liberă
                mat[i][prima] = mat[i][j];
                nr = 0;
                if (prima > 0 &&
                    mat[i][prima - 1] == mat[i][prima]) {
                    // Combinam elementele și actualizam punctajul
                    mat[i][prima - 1] = mat[i][prima - 1]  *2;
                    *punctaj = *punctaj + mat[i][prima - 1];
                    mat[i][prima] = 0;
                    nr++;
                }
                // Ștergem vechea poziție a caracterului
                mvwprintw(tabla, i * 2 + 1, j * 5 + 1, "    ");
                if (nr == 0) {
                    // Actualizam poziția noului caracter
                    mvwprintw(tabla, i * 2 + 1, prima * 5 + 1, "%d",
                              mat[i][prima]);
                } else {
                    mvwprintw(tabla, i * 2 + 1, (prima - 1) * 5 + 1, "%d",
                              mat[i][prima - 1]);
                    prima--;
                }
                prima++;
            }
        }
        i--;
    }
    wrefresh(tabla);
}

int matricelafel(int b[4][4], int c[4][4]) {
    //functie pentru a verifica daca doua matrici sunt la fel
    int i, j, nr = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (b[i][j] != c[i][j]) nr++;
    if (nr == 0)
        return 1;  // sunt egale
    else
        return 0;  // sunt diferite
}

void copieremat(int b[4][4], int c[4][4]) {
    //functie pentru copierea matricei c peste b
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) b[i][j] = c[i][j];
}

void updateMatrice(WINDOW *tabla, int mat[4][4]) {
    int i, j,valoare=0;
    // Actualizare matrice mat cu valorile de pe tabla de joc
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            wmove(tabla, i * 2 + 1, j * 5 + 1);  // Setarea poziției cursorului
            valoare = winch(tabla);
            // Citirea caracterului de la coordonatele curente
            // Ignoră spațiile și alte caractere non-numerice
            if (valoare >= '0' && valoare <= '9') mat[i][j] = valoare - '0';
            // Actualizare matrice cu valoarea citită
            else
                mat[i][j] = 0;  // Setează la 0 pentru caractere nevalide
            wmove(tabla, i * 2 + 1, j * 5 + 2);  // daca are 2 cifre
            valoare = winch(tabla);
            if (valoare >= '0' && valoare <= '9')
                mat[i][j] = mat[i][j] * 10 + (valoare - '0');
            else
                mat[i][j] = mat[i][j];
            wmove(tabla, i * 2 + 1, j * 5 + 3);  // daca are 3 cifre
            valoare = winch(tabla);
            if (valoare >= '0' && valoare <= '9')
                mat[i][j] = mat[i][j] * 10 + (valoare - '0');
            else
                mat[i][j] = mat[i][j];
            wmove(tabla, i * 2 + 1, j * 5 + 4);  // daca are 4 cifre
            valoare = winch(tabla);
            if (valoare >= '0' && valoare <= '9')
                mat[i][j] = mat[i][j] * 10 + (valoare - '0');
            else
                mat[i][j] = mat[i][j];
        }
    }
}

int jocpierdut(int mat[4][4]) {
    //functie pentru a verifica daca un joc e pierdut
    //adica s a umplut toata tabla de joc si nu mai sunt
    //mutari valide
    int i, j, mutari = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            if (mat[i][j + 1] == mat[i][j]) mutari++; //mai exista mutari valide
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            if (mat[i][j] == mat[i + 1][j]) mutari++; //mai exista mutari valide
    if (mutari > 0) return 1;  //mai exista mutari valide
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (mat[i][j] == 0) return 1;
    return 0; //jocul e pierdut
}

void pierdut(int mat[4][4], WINDOW *wnd, WINDOW *tabla, WINDOW *panou) {
    //functie pentru afisarea mesajului ,,joc pierdut"
    int c = 0;
    stergereinstructiuni(wnd);
    //facem o noua fereastra, pe care o si centram
    WINDOW *mesajJocPierdut = newwin(10, 40, 5, 20);
    centrare(mesajJocPierdut);
    box(mesajJocPierdut, 0, 0);
    start_color();
    init_pair(2, COLOR_RED, COLOR_BLACK);
    // Aplicare culoare la text
    wattron(mesajJocPierdut, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(mesajJocPierdut, 4, 7, "      JOC PIERDUT!");
    mvwprintw(mesajJocPierdut, 7, 17, "apasati tasta 'q' pt");
    mvwprintw(mesajJocPierdut, 8, 17, "a reveni la meniu");
    wattroff(mesajJocPierdut, COLOR_PAIR(2) | A_BOLD);
    //stergem tabla si panoul
    wclear(tabla);
    wrefresh(tabla);
    wclear(panou);
    wrefresh(panou);
    c = wgetch(mesajJocPierdut);  //preluare tasta de la utilizator
    while (c != 'q') c = wgetch(mesajJocPierdut); //nu se intampla nimic daca apasam alte taste
    if (c == 'q') {  //iesim din fereastra si afisam scrisul ,,2048" si meniul
        afisare2048(wnd);
        wclear(mesajJocPierdut);
        wrefresh(mesajJocPierdut);
        delwin(mesajJocPierdut);
        wrefresh(wnd);
    }
}

int joccastigat(int mat[4][4]) {
    //functie pentru a verifica daca un joc s-a castigat
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (mat[i][j] == 2048) return 1; //joc castigat
    return 0;
}

void castigat(int mat[4][4], WINDOW *wnd, WINDOW *tabla, WINDOW *panou) {
    //functie pentru afisarea mesajului ,,joc castigat"
    int c = 0;
    stergereinstructiuni(wnd);
    //facem o noua fereastra, pe care o si centram
    WINDOW *mesajJocCastigat = newwin(10, 40, 5, 20);
    centrare(mesajJocCastigat);
    box(mesajJocCastigat, 0, 0);
    start_color();
    init_pair(2, COLOR_RED, COLOR_BLACK);
    // Aplicare culoare la text
    wattron(mesajJocCastigat, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(mesajJocCastigat, 4, 7, "      JOC CASTIGAT!");
    mvwprintw(mesajJocCastigat, 7, 17, "apasati tasta 'q' pt");
    mvwprintw(mesajJocCastigat, 8, 17, "a reveni la meniu");
    wattroff(mesajJocCastigat, COLOR_PAIR(2) | A_BOLD);
    //stergem panoul si tabla
    wclear(tabla);
    wrefresh(tabla);
    wclear(panou);
    wrefresh(panou);
    c = wgetch(mesajJocCastigat); //preluare tasta de la utilizator
    while (c != 'q') c = wgetch(mesajJocCastigat); //daca se apasa alta tasta nu conteaza
    if (c == 'q') { //iesim din fereastra si afisam scrisul ,,2048" si meniul
        afisare2048(wnd);
        wclear(mesajJocCastigat);
        wrefresh(mesajJocCastigat);
        delwin(mesajJocCastigat);
        wrefresh(wnd);
    }
}

int poatemutainsus(int mut[4][4], int mat[4][4]) {
    //functie pentru a verifica daca mutarea in sus e valida
    int j, i, nr, prima, copia[4][4];
    //mut si copia vor contine elementele lui mat
    copieremat(mut, mat);
    copieremat(copia, mat);
    //vom face mutarea in sus pt mut
    j = 0;
    while (j < 4) {
        // Variabilă pentru a reține prima poziție liberă în coloană
        prima = 0;
        // Parcurgem fiecare linie în coloana curentă
        for (i = 0; i < 4; i++) {
            if (mut[i][j] != 0) {
                // Mutăm elementul la prima poziție liberă
                mut[prima][j] = mut[i][j];
                nr = 0;
                if (prima > 0 &&
                    mut[prima - 1][j] == mut[prima][j]) {
                    // Combinam elementele 
                    mut[prima - 1][j] = mut[prima - 1][j] *2;
                    mut[prima][j] = 0;
                    nr++;
                }
                if (nr != 0) prima--;
                prima++;
            }
        }
        j++;
    }
    //daca mut si copia sunt la fel, inseamna ca mutarea n-a fost valida
    if (matricelafel(mut, copia) == 1) return 0;  // nu e mutare valida
    return 1;
}

int poatemutainjos(int mut[4][4], int mat[4][4]) {
    //functie pt a verifica daca mutarea in jos e valida
    int j, i, nr, ultima, copia[4][4];
    //mut si copia vor avea valorile lui mat
    copieremat(mut, mat);
    copieremat(copia, mat);
    //facem mutarea in joc pentru mut
    j = 3;
    while (j >= 0) {
        // Variabilă pentru a reține ultima poziție liberă în coloană
        ultima = 3;
        // Parcurgem fiecare linie în coloana curentă
        for (i = 3; i >= 0; i--) {
            if (mut[i][j] != 0) {
                // Mutăm elementul la prima poziție liberă
                mut[ultima][j] = mut[i][j];
                nr = 0;
                if (ultima < 3 &&
                    mut[ultima + 1][j] == mut[ultima][j]) {
                    // Combinam elementele 
                    mut[ultima + 1][j] *= 2;
                    mut[ultima][j] = 0;
                    nr++;
                }
                if (nr != 0) ultima++;
                ultima--;
            }
        }
        j--;
    }
    //daca mut si copia sunt la fel, mutarea nu a fost valida
    if (matricelafel(mut, copia) == 1) return 0;  // nu e mutare valida
    return 1;
}

int poatemutaindreapta(int mut[4][4], int mat[4][4]) {
    //functie pt a verifica daca mutarea in dreapta e valida
    int j, i, nr, ultima, copia[4][4];
    //mut si copia vor avea valorile lui mat
    copieremat(mut, mat);
    copieremat(copia, mat);
    //facem mutarea in dreapta pentru mut
    i = 0;
    while (i < 4) {
        // Variabilă pentru a reține ultima poziție liberă în linie
        ultima = 3;
        // Parcurgem fiecare coloana în linia curentă
        for (j = 3; j >= 0; j--) {
            if (mut[i][j] != 0) {
                // Mutăm elementul la ultima poziție liberă
                mut[i][ultima] = mut[i][j];
                nr = 0;
                if (ultima < 3 &&
                    mut[i][ultima + 1] == mut[i][ultima]) {
                    // Combinam elementele
                    mut[i][ultima + 1] = mut[i][ultima + 1] *2;
                    mut[i][ultima] = 0;
                    nr++;
                }
                if (nr != 0) ultima++;
                ultima--;
            }
        }
        i++;
    }
    //daca mut si copia sunt la fel, mutarea a fost invalida
    if (matricelafel(mut, copia) == 1) return 0;  // nu e mutare valida
    return 1;
}

int poatemutainstanga(int mut[4][4], int mat[4][4]) {
    //functie pentru a verifica daca mutarea in stanga e valida
    int j, i, nr, prima, copia[4][4];
    //mut si copia vor avea valorile lui mat
    copieremat(mut, mat);
    copieremat(copia, mat);
    //facem mutarea in stanga pentru mut
    i = 3;
    while (i >= 0) {
        // Variabilă pentru a reține prima poziție liberă în linie
        prima = 0;
        // Parcurge fiecare coloana în linia curentă
        for (j = 0; j < 4; j++) {
            if (mut[i][j] != 0) {
                // Mutăm elementul la prima poziție liberă
                mut[i][prima] = mut[i][j];
                nr = 0;
                if (prima > 0 &&
                    mut[i][prima - 1] == mut[i][prima]) {
                    // Combinam elementele 
                    mut[i][prima - 1] = mut[i][prima - 1]*2;
                    mut[i][prima] = 0;
                    nr++;
                }
                if (nr != 0) prima--;
                prima++;
            }
        }
        i--;
    }
    //daca mut si copia sunt la fel, mutarea a fost invalida
    if (matricelafel(mut, copia) == 1) return 0;  // nu e mutare valida
    return 1;
}

void resume(WINDOW *wnd, int matresume[4][4], int *punctaje, int *mx1, int *mx2,
            int *mx3, int *nuescor) {
    //functie pentru optiunea resume
    int a[2], c = 0, i, j, copie[4][4], mut[4][4];
    //facem o fereastra pentru tabla de joc si o centram
    WINDOW *tabla = newwin(9, 21, 3, 40);
    centrare(tabla);
    // Desenează un box în jurul ferestrei de joc
    box(tabla, 0, 0);
    // Adaugare linii verticale
    for (i = 1; i <= 8; i += 2) {
        for (j = 0; j <= 16; j += 5) {
            mvwaddch(tabla, i, j, ACS_VLINE);
        }
    }
    // Adăugare liniile orizontale
    for (i = 0; i <= 6; i += 2) {
        for (j = 1; j <= 19; j++) {
            mvwaddch(tabla, i, j, ACS_HLINE);
        }
    }
    keypad(tabla, TRUE);
    //facem o fereastra pentru panou si o centram
    WINDOW *panou = newwin(10, 40, 0, 0);
    keypad(panou, TRUE);
    wattron(panou, COLOR_PAIR(2) | A_BOLD);
    //punem valorile din matresume pe tabla(daca sunt numere)
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (matresume[i][j] >= 2 && matresume[i][j] <= 2048)
                mvwprintw(tabla, i * 2 + 1, j * 5 + 1, "%d", matresume[i][j]);

    wrefresh(tabla);
    while (FOREVER) {
        //punem in matresume valorile de pe tabla
        updateMatrice(tabla, matresume);
        //facem o copie, pentru a verifica dupa daca mutarile au fost valide si se genereaza un numar random pe tabla
        copieremat(copie, matresume);
        // Afișează data și ora curentă în panoul de control
        time_t t;
        struct tm *area;
        t = time(NULL);
        area = localtime(&t);
        // Curățăm și actualizăm fereastra de control
        wclear(panou);
        mvwprintw(panou, 1, 1, "Data si ora: %s", asctime(area));
        wrefresh(panou);
        wrefresh(tabla);
        mvwprintw(panou, 2, 1, "Punctaj: %d", *punctaje);
        mvwprintw(panou, 3, 1, "Comenzi valide:");
        //verificam faca mutarile sunt valide, si le afisam in caz afirmativ
        if (poatemutainstanga(mut, matresume) == 1)
            mvwprintw(panou, 6, 18, "A/a - stanga");
        if (poatemutaindreapta(mut, matresume) == 1)
            mvwprintw(panou, 5, 18, "D/d - dreapta");
        if (poatemutainsus(mut, matresume) == 1)
            mvwprintw(panou, 3, 18, "W/W - sus");
        if (poatemutainjos(mut, matresume) == 1)
            mvwprintw(panou, 4, 18, "S/s - jos");
        // Afișează conținutul ferestrei de control
        wrefresh(panou);
        // Afișează conținutul ferestrei de joc
        wrefresh(tabla);
        // Preluarea unei comenzi de la utilizator din fereastra de joc
        c = wgetch(tabla);
        // Verificăm dacă tasta apăsată este 'q' pentru a afișa meniul
        if (c == 'q' || c == 'Q') {
            // Șterge conținutul ferestrei de joc
            afisare2048(wnd);
            wclear(panou);
            wclear(tabla);
            stergereinstructiuni(wnd);
            wrefresh(wnd);
            // Refresh ferestrele șterse pentru a aplica modificările
            wrefresh(panou);
            wrefresh(tabla);
            break;
        } else if (c == 'w' || c == 'W') { //daca e mutare in sus
            mutareinsus(tabla, matresume, punctaje);
            wrefresh(tabla);
            if (matricelafel(matresume, copie) == 0) { //daca mutarea e valida
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }
        } else if (c == 's' || c == 'S') { //daca e mutare in jos
            mutareinjos(tabla, matresume, punctaje);
            wrefresh(tabla);
            if (matricelafel(matresume, copie) == 0) { //daca mutarea e valida
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }
        } else if (c == 'd' || c == 'D') {  //daca e muare in dreapta
            mutareindreapta(tabla, matresume, punctaje);
            wrefresh(tabla);
            if (matricelafel(matresume, copie) == 0) { //daca mutarea e valia
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }
        } else if (c == 'a' || c == 'A') { //daca e mutare in stanga
            mutareinstanga(tabla, matresume, punctaje);
            wrefresh(tabla);
            if (matricelafel(matresume, copie) == 0) { //daca mutarea e valida
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }
        }
        updateMatrice(tabla, matresume);//punem in matresume noile valori de pe tabla
        if (jocpierdut(matresume) == 0) { //daca am pierdut jocul se deschide fereastra cu mesajul ,,joc pierdut"
            *nuescor = 1; //pentru a verifica daca exista un scor
            pierdut(matresume, wnd, tabla, panou);
            break;  // Ieși din bucla while pentru a încheia jocul
        }
        if (joccastigat(matresume) == 1) {//daca am castigat jocul se deschide fereastra cu mesajul ,,joc castigat"
            *nuescor = 1; //pentru a verifica daca exista un scor
            castigat(matresume, wnd, tabla, panou);
            break;
        }
    }
    wattroff(panou, COLOR_PAIR(2) | A_BOLD);
    //verificare daca un joc a fost castigat sau pierdut (exista un scor),
    //pentru a face cele mai mari 3 scoruri
    if (joccastigat(matresume) == 1 || jocpierdut(matresume) == 0) {
        if (*punctaje > *mx1) {
            *mx3 = *mx2;
            *mx2 = *mx1;
            *mx1 = *punctaje;
        } else if (*punctaje > *mx2) {
            *mx3 = *mx2;
            *mx2 = *punctaje;
        } else if (*punctaje > *mx3)
            *mx3 = *punctaje;
    }
}

void startjoc(WINDOW *wnd, int matresume[4][4], int *punctaje, int *mx1,
              int *mx2, int *mx3, int *nuescor) {
                //functie pentru optiunea new game
    int a[2], c = 0, punctaj = 0, mat[4][4], i, j, copie[4][4], mut[4][4];
    // Creare fereastră nouă pentru tabla de joc si centrare
    WINDOW *tabla = newwin(9, 21, 3, 40);
    centrare(tabla);
    box(tabla, 0, 0);
    // Adaugare linii verticale
    for (i = 1; i <= 8; i = i+ 2) {
        for (j = 0; j <= 16; j =j+ 5) {
            mvwaddch(tabla, i, j, ACS_VLINE);
        }
    }
    // Adăugare liniile orizontale
    for (i = 0; i <= 6; i =i+2) {
        for (j = 1; j <= 19; j++) {
            mvwaddch(tabla, i, j, ACS_HLINE);
        }
    }
    keypad(tabla, TRUE);
    //creare fereaastra pentru panou 
    WINDOW *panou = newwin(10, 40, 0, 0);
    // Activează modul keypad în fereastra de control
    keypad(panou, TRUE);
    wattron(panou, COLOR_PAIR(2) | A_BOLD);
    //afisare doua numere pe tabla la inceputul jocului
    generareNumere(a);
    afisareNumarPeTabla(tabla, a);
    afisareNumarPeTabla(tabla, a);
    while (FOREVER) {
        //punem in mat elementele generate pe tabla
        updateMatrice(tabla, mat);
        //facem o copie pentru a verifica dupa daca emutarile sunt valide si trebuie generat un numar pe tabla
        copieremat(copie, mat);
        //  Afișează data și ora curentă în panoul de control
        time_t t;
        struct tm *area;
        t = time(NULL);
        area = localtime(&t);
        // Curățăm și actualizăm fereastra de control
        wclear(panou);
        mvwprintw(panou, 1, 1, "Data si ora: %s", asctime(area));
        wrefresh(panou);
        wrefresh(tabla);
        mvwprintw(panou, 2, 1, "Punctaj: %d", punctaj);
        mvwprintw(panou, 3, 1, "Comenzi valide:");
        //verificare comenzi valide si afisarea lor in panou
        if (poatemutainstanga(mut, mat) == 1)
            mvwprintw(panou, 6, 18, "A/a - stanga");
        if (poatemutaindreapta(mut, mat) == 1)
            mvwprintw(panou, 5, 18, "D/d - dreapta");
        if (poatemutainsus(mut, mat) == 1) mvwprintw(panou, 3, 18, "W/W - sus");
        if (poatemutainjos(mut, mat) == 1) mvwprintw(panou, 4, 18, "S/s - jos");
        wrefresh(panou);
        wrefresh(tabla);
        // Preluarea unei comenzi de la utilizator din fereastra de joc
        c = wgetch(tabla);
        // Verificăm dacă tasta apăsată este 'q' pentru a afișa meniul
        if (c == 'q' || c == 'Q') {
            // Șterge conținutul ferestrei de joc
            afisare2048(wnd);
            wclear(panou);
            wclear(tabla);
            stergereinstructiuni(wnd);
            wrefresh(wnd);
            // Refresh ferestrele șterse pentru a aplica modificările
            wrefresh(panou);
            wrefresh(tabla);
            break;
        } else if (c == 'w' || c == 'W') { //daca e mutare in sus
            mutareinsus(tabla, mat, &punctaj);
            wrefresh(tabla);
            if (matricelafel(mat, copie) == 0) { //daca e mutare valida
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }

        } else if (c == 's' || c == 'S') { //daca e mutare in jos
            mutareinjos(tabla, mat, &punctaj);
            wrefresh(tabla);
            if (matricelafel(mat, copie) == 0) { //daca e mutare valida
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }
        } else if (c == 'd' || c == 'D') {  //daca e mutare in dreapta
            mutareindreapta(tabla, mat, &punctaj);
            wrefresh(tabla);
            if (matricelafel(mat, copie) == 0) { //daca e mutare valida
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }
        } else if (c == 'a' || c == 'A') {
            mutareinstanga(tabla, mat, &punctaj); //daca e mutare in stanga
            wrefresh(tabla);
            if (matricelafel(mat, copie) == 0) {  // daca e mutare valida
                generareNumere(a);
                afisareNumarPeTabla(tabla, a);
                wrefresh(tabla);
            }
        }
        //punem in mat noile valori de pe tabla
        updateMatrice(tabla, mat);
        if (jocpierdut(mat) == 0) { //daca am pierdut jocul se deschide fereastra cu mesajul ,,joc pierdut"
            *nuescor = 1; //verificare daca exista scor
            pierdut(mat, wnd, tabla, panou);
            break;  // Ieșire din while pentru a încheia jocul
        }
        if (joccastigat(mat) == 1) {    //daca am castigat jocul se deschide fereastra cu mesajul ,,joc castigat"
            *nuescor = 1;  //daca exista un scor
            castigat(mat, wnd, tabla, panou);
            break;
        }
    }
    wattroff(panou, COLOR_PAIR(2) | A_BOLD);
    //punem in matresume elementele din mat,
    //pentru a putea continua jocul la optiunea resume
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) matresume[i][j] = mat[i][j];
    //actualizam punctajul pentru a ne folosi de el la optiunea resume
    *punctaje = punctaj;
    //daca am pierdut sau castigat un joc (exista un scor), facem scorurile maxime
    if (joccastigat(matresume) == 1 || jocpierdut(matresume) == 0) {
        if (punctaj > *mx1) {
            *mx3 = *mx2;
            *mx2 = *mx1;
            *mx1 = punctaj;
        } else if (punctaj > *mx2) {
            *mx3 = *mx2;
            *mx2 = punctaj;
        } else if (punctaj > *mx3)
            *mx3 = punctaj;
    }
}

int main() {
    int matresume[4][4], deschidresume = 0, punctaje = 0, mx1 = 0, mx2 = 0,
                         mx3 = 0, nuescor = 0, menuChoice;
    // Se inițializează ecranul
    WINDOW *wnd = initscr();
    // Configurare pentru a accepta intrările imediate și taste speciale
    keypad(stdscr, TRUE);
    start_color();
    // Inițializarea perechii de culori
    init_pair(2, COLOR_RED, COLOR_BLACK);
    timeout(0);
    // Se va reține în nrows și ncols numărul maxim de linii și coloane
    afisare2048(wnd);
    wrefresh(wnd);
    // Se inhibă afișarea caracterelor introduse de la tastatură
    noecho();
    // Caracterele introduse sunt citite imediat - fără 'buffering'
    cbreak();
    // Se ascunde cursorul
    curs_set(0);
    // Se creează fereastra meniului si o centram
    WINDOW *meniu = newwin(9, 21, 1, 1);
    box(meniu, 0, 0);
    centrare(meniu);
    menuChoice = 0;
    while (menuChoice != 2)
    // Continuăm să afișăm meniul până când se selectează Quit
    {
        // Afișarea meniului și preluarea opțiunii selectate
        menuChoice = afismeniu(meniu, menuChoice);
        switch (menuChoice) {
            case 0:  
               //optiune new game
                wclear(wnd);
                deschidresume = 1; //daca variabila e 1, putem avea acces la optiunea resume
                afisareInstructiuni(wnd);
                refresh();
                werase(meniu);
                wrefresh(meniu);
                // Deschide fereastra pentru noul joc
                startjoc(wnd, matresume, &punctaje, &mx1, &mx2, &mx3, &nuescor);
                break;
            case 1:
                // Opțiunea Resume
                if (jocpierdut(matresume) == 0) deschidresume = 0;  //daca nu mai e un joc inceput, nu mai avem acces la optiunea resume
                wclear(wnd);
                if (deschidresume == 1) { //avem acces la optiunea resume
                    afisareInstructiuni(wnd);
                    refresh();
                    resume(wnd, matresume, &punctaje, &mx1, &mx2, &mx3,
                           &nuescor);
                }
                break;
            case 2: // optiune Quit
                break;
                endwin();
            case 3:
                // Opțiunea Reguli joc
                wclear(wnd);
                wrefresh(wnd);
                afisareReguliJoc(wnd);
                cbreak();
                break;
            case 4:
                // Optiune scoruri maxime
                if (nuescor == 1) {  // se deschide fereastra doar daca exista
                                     // cel putin un scor obtinut
                    wclear(wnd);
                    wrefresh(wnd);
                    scormaxim(wnd, &mx1, &mx2, &mx3);
                }
        }
    }
    // Închiderea ferestrelor ncurses
    refresh();
    getch();
    delwin(meniu);
    endwin();
    return 0;
}