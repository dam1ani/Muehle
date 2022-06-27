#include "muehle.h"

/*Funktion um  das Feld in der Kommandozeile auszugeben */
void print_feld(int feld[3][8])
{
    char str1[] = "%s-----------------------%s-----------------------%s\t\t1-----"
                  "------------------2-----------------------3\n";
    char str2[] = "|\t%s---------------%s---------------%s\t|\t\t|\t4------------"
                  "---5---------------6\t|\n";
    char str3[] =
            "|\t|\t%s-------%s-------%s\t|\t|\t\t|\t|\t7-------8-------9\t|\t|\n";
    char str4[] =
            "%s-------%s-------%s\t \t%s-------%s-------%s\t\t10------11------12\t "
            "\t13------14------15\n";
    char str5[] =
            "|\t|\t%s-------%s-------%s\t|\t|\t\t|\t|\t16------17------18\t|\t|\n";
    char str6[] = "|\t%s---------------%s---------------%s\t|\t\t|\t19-----------"
                  "---20--------------21\t|\n";
    char str7[] = "%s-----------------------%s-----------------------%s\t\t22----"
                  "------------------23----------------------24\n\n";
    system("@cls||clear");
    printf("\n\n");

    printf(str1, ntoc(feld[0][0]), ntoc(feld[0][1]), ntoc(feld[0][2]));
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf(str2, ntoc(feld[1][0]), ntoc(feld[1][1]), ntoc(feld[1][2]));
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf(str3, ntoc(feld[2][0]), ntoc(feld[2][1]), ntoc(feld[2][2]));
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");

    printf(str4, ntoc(feld[0][7]), ntoc(feld[1][7]), ntoc(feld[2][7]),
           ntoc(feld[2][3]), ntoc(feld[1][3]), ntoc(feld[0][3]));
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");

    printf(str5, ntoc(feld[2][6]), ntoc(feld[2][5]), ntoc(feld[2][4]));
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf(str6, ntoc(feld[1][6]), ntoc(feld[1][5]), ntoc(feld[1][4]));
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf(str7, ntoc(feld[0][6]), ntoc(feld[0][5]), ntoc(feld[0][4]));
    sleep(1);
}

/*Funktion fuer die Initialisierung des Feldes mit 0 Werten */
void init_feld(int feld[3][8])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 8; j++)
        {
            feld[i][j] = 0;
        }
    }
}

/*Funktion um Steine zu setzen, nimmt als Parameter die Koordinaten des Feldes
 *und den eingegebene Wert eines der Spieler */
int steineSetzen(int feld[3][8], int zahl, int spieler)
{
    int x, y;
    x = coordinate(zahl, 0);
    y = coordinate(zahl, 1);

    if (feld[x][y] != 0)
    {
        return INVALID_MOVEMENT;
    }

    feld[x][y] = spieler;

    return VALID;
}

/*Funktion nimmt die Eingabe vom Benutzer, wie in der Vorlesung*/
int user_input(void)
{
    int input, status;
    status = scanf("%i", &input);

    if (flush_buff() == 0 || status == 0 || input <= 0 ||
        input > 24)
        /*nimmt nur int zwischen 1-24, da ansonsten keine Werte
                        benötigt werden*/
    {
        return INVALID_INPUT;
    }

    return input;
}

/*Wie aus dem Script*/
int flush_buff(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    return c != EOF;
}

/*Wird genutzt, um Steine von einem Feld auf ein Nächstes zu bewegen */
int normal_movement(int feld[3][8], int firstInput, int secondInput)
{
    /*Zuerst werden die Nutzereingaben in die Koordinaten der Matrix
     *umgewandelt(Spielfeld)*/
    int cord_now_1, cord_now_2, cord_then_1, cord_then_2;

    cord_now_1 =
            coordinate(firstInput, 0); /*Feldkoordinate 1 der zu bewegenden Figur*/
    cord_now_2 =
            coordinate(firstInput, 1); /*Feldkoordinate 2 der zu bewegenden Figur*/
    cord_then_1 = coordinate(secondInput, 0); /*Feldkoordinate 1 des Zielfeldes*/
    cord_then_2 = coordinate(secondInput, 1); /*Feldkoordinate 2 des Zielfeldes*/
    /*nun wird geprüft, ob die Bewegung auch korrekt war, indem man die
     *Feldkoordinaten miteinander vergleicht*/
    if (feld[cord_now_1][cord_now_2] == 0)
    {
        printf("Leeres Feld\n");
        return INVALID_INPUT;
    }

    if (feld[cord_then_1][cord_then_2] != 0)
    {
        printf("Das Feld ist bereits besetzt!\n");
        return INVALID_INPUT;
    }

    if (cord_now_1 == cord_then_1)
    {
        if (cord_now_2 == cord_then_2)
        {
            printf("Der Stein muss bewegt werden\n");
            return INVALID_INPUT;
        }

        if ((cord_now_2 + 1) == cord_then_2 || (cord_now_2 - 1) == cord_then_2 ||
            (cord_now_2 + 7) == cord_then_2 || (cord_now_2 - 7) == cord_then_2)
        {
            /*Nachdem die Bewegung als korrekt betrachtet wurde, bekommt das neue Feld
             *den Wert des Spielers(1 oder 2) und das alte Feld wird geleert*/
            feld[cord_then_1][cord_then_2] = feld[cord_now_1][cord_now_2];
            feld[cord_now_1][cord_now_2] = 0;

            return VALID;
        }
        else
        {
            printf("Der Stein kann maximal um 1 verschoben werden\n");
            return INVALID_INPUT;
        }
    }

    if (cord_now_2 == cord_then_2)
    {
        if (cord_now_2 % 2 == 0)
        {
            printf("\nDer Stein darf nicht diagonal bewegt werden\n");
            return INVALID_INPUT;
        }

        if ((cord_now_1 + 1) == cord_then_1 || (cord_now_1 - 1) == cord_then_1)
        {
            /*Nachdem die Bewegung als korrekt betrachtet wurde, bekommt das neue Feld
             *den Wert des Spielers(1 oder 2) und das alte Feld wird geleert*/
            feld[cord_then_1][cord_then_2] = feld[cord_now_1][cord_now_2];
            feld[cord_now_1][cord_now_2] = 0;

            return VALID;
        }
        else
        {
            printf("Der Stein kann maximal um 1 verschoben werden\n");
            return INVALID_INPUT;
        }
    }
    else
    {
        return INVALID_INPUT;
    }
}

/*Funktion zum Uebersetzen einer Zahl in die entsprechende Koordinate im Feld
 */
/*Siehe ReadMe.txt */
int coordinate(int zahl, int xOderY)
{
    int x, y;

    switch (zahl)
    {
        case 1:
            x = 0;
            y = 0;
            break;
        case 2:
            x = 0;
            y = 1;
            break;
        case 3:
            x = 0;
            y = 2;
            break;
        case 4:
            x = 1;
            y = 0;
            break;
        case 5:
            x = 1;
            y = 1;
            break;
        case 6:
            x = 1;
            y = 2;
            break;
        case 7:
            x = 2;
            y = 0;
            break;
        case 8:
            x = 2;
            y = 1;
            break;
        case 9:
            x = 2;
            y = 2;
            break;
        case 10:
            x = 0;
            y = 7;
            break;
        case 11:
            x = 1;
            y = 7;
            break;
        case 12:
            x = 2;
            y = 7;
            break;
        case 13:
            x = 2;
            y = 3;
            break;
        case 14:
            x = 1;
            y = 3;
            break;
        case 15:
            x = 0;
            y = 3;
            break;
        case 16:
            x = 2;
            y = 6;
            break;
        case 17:
            x = 2;
            y = 5;
            break;
        case 18:
            x = 2;
            y = 4;
            break;
        case 19:
            x = 1;
            y = 6;
            break;
        case 20:
            x = 1;
            y = 5;
            break;
        case 21:
            x = 1;
            y = 4;
            break;
        case 22:
            x = 0;
            y = 6;
            break;
        case 23:
            x = 0;
            y = 5;
            break;
        case 24:
            x = 0;
            y = 4;
            break;
        default:
            printf("Die eingegebene Zahl sollte zwischen 1 und 24 sein!\n");
    }

    if (xOderY == 0)
    {
        return x;
    }

    return y;
}

/*Funktion, um zu pruefen, ob sich ein Feldeintrag mit den eingegebenen
 *Koordinaten in einer Muehle befindet*/
int obInMuele(int feld[3][8], int input)
{
    int x, y;
    x = coordinate(input, 0);
    y = coordinate(input, 1);

    if (feld[x][y] == 0)
    {
        return INVALID_INPUT;
    }

    if (y % 2 != 0)
    {
        if (x == 0)
        {
            if (feld[x + 1][y] == feld[x][y] && feld[x + 2][y] == feld[x][y])
            {
                return VALID;
            }
        }

        if (x == 1)
        {
            if (feld[x - 1][y] == feld[x][y] && feld[x + 1][y] == feld[x][y])
            {
                return VALID;
            }
        }

        if (feld[x - 1][y] == feld[x][y] && feld[x - 2][y] == feld[x][y])
        {
            return VALID;
        }

        if (y == 7)
        {
            if (feld[x][y - 7] == feld[x][y] && feld[x][y - 1] == feld[x][y])
            {
                return VALID;
            }
        }

        if (feld[x][y + 1] == feld[x][y] && feld[x][y - 1] == feld[x][y])
        {
            return VALID;
        }
    }

    if (y == 0)
    {
        if (feld[x][y + 7] == feld[x][y] && feld[x][y + 6] == feld[x][y])
        {
            return VALID;
        }

        if (feld[x][y + 1] == feld[x][y] && feld[x][y + 2] == feld[x][y])
        {
            return VALID;
        }
    }

    if (y == 2 || y == 4)
    {
        if (feld[x][y + 1] == feld[x][y] && feld[x][y + 2] == feld[x][y])
        {
            return VALID;
        }

        if (feld[x][y - 1] == feld[x][y] && feld[x][y - 2] == feld[x][y])
        {
            return VALID;
        }
    }

    if (y == 6)
    {
        if (feld[x][y + 1] == feld[x][y] && feld[x][y - 6] == feld[x][y])
        {
            return VALID;
        }

        if (feld[x][y - 1] == feld[x][y] && feld[x][y - 2] == feld[x][y])
        {
            return VALID;
        }
    }

    return INVALID_INPUT;
}

/*Funktion zum iterativen Kopieren eines Feldes in ein anderes Feld */
void felder_tauschen(int alteFeld[3][8], int neueFeld[3][8])
{
    int i, j = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 8; j++)
        {
            alteFeld[i][j] = neueFeld[i][j];
        }
    }
}

/*Funktion, die die Anzahl der Muehlen in einem Feld zurueckgibt */
int anzahlVonMuelen(int feld[3][8])
{
    int anzahlVonMuelen = 0;
    /*Erste Quadrat */
    if ((feld[0][0] == feld[0][1]) && (feld[0][0] == feld[0][2]) &&
        feld[0][0] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[0][2] == feld[0][3]) && (feld[0][2] == feld[0][4]) &&
        feld[0][2] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[0][4] == feld[0][5]) && (feld[0][4] == feld[0][6]) &&
        feld[0][4] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[0][6] == feld[0][7]) && (feld[0][6] == feld[0][0]) &&
        feld[0][6] != 0)
    {
        anzahlVonMuelen++;
    }

    /*Zweite Quadrat */

    if ((feld[1][0] == feld[1][1]) && (feld[1][0] == feld[1][2]) &&
        feld[1][0] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[1][2] == feld[1][3]) && (feld[1][2] == feld[1][4]) &&
        feld[1][2] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[1][4] == feld[1][5]) && (feld[1][4] == feld[1][6]) &&
        feld[1][4] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[1][6] == feld[1][7]) && (feld[1][6] == feld[1][0]) &&
        feld[1][6] != 0)
    {
        anzahlVonMuelen++;
    }

    /*Dritte Quadrat */

    if ((feld[2][0] == feld[2][1]) && (feld[2][0] == feld[2][2]) &&
        feld[2][0] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[2][2] == feld[2][3]) && (feld[2][2] == feld[2][4]) &&
        feld[2][2] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[2][4] == feld[2][5]) && (feld[2][4] == feld[2][6]) &&
        feld[2][4] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[2][6] == feld[2][7]) && (feld[2][6] == feld[2][0]) &&
        feld[2][6] != 0)
    {
        anzahlVonMuelen++;
    }

    /*Innere Muelen */

    if ((feld[0][7] == feld[1][7]) && (feld[0][7] == feld[2][7]) &&
        feld[0][7] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[0][1] == feld[1][1]) && (feld[0][1] == feld[2][1]) &&
        feld[0][1] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[0][3] == feld[1][3]) && (feld[0][3] == feld[2][3]) &&
        feld[0][3] != 0)
    {
        anzahlVonMuelen++;
    }

    if ((feld[0][5] == feld[1][5]) && (feld[0][5] == feld[2][5]) &&
        feld[0][5] != 0)
    {
        anzahlVonMuelen++;
    }

    return anzahlVonMuelen;
}

/*Funktion, die den Array-Eintrag gemäß den angegebenen Koordinaten löscht */
int steineLoeschen(int feld[3][8], int input, int welcheSpieler)
{
    if (welcheSpieler == 1)
    {
        if (obAlleInMuele(feld, 2) == VALID)
        {
            if (welcheSpieler != feld[coordinate(input, 0)][coordinate(input, 1)] &&
                feld[coordinate(input, 0)][coordinate(input, 1)] != 0)
            {
                feld[coordinate(input, 0)][coordinate(input, 1)] = 0;
                printf("Stein wurde erfolgreich geloescht\n");
                return VALID;
            }
        }

        if (obInMuele(feld, input) != VALID &&
            welcheSpieler != feld[coordinate(input, 0)][coordinate(input, 1)] &&
            feld[coordinate(input, 0)][coordinate(input, 1)] != 0)
        {
            feld[coordinate(input, 0)][coordinate(input, 1)] = 0;
            printf("Stein wurde erfolgreich geloescht\n");
            return VALID;
        }
    }

    if (obAlleInMuele(feld, 1) == VALID)
    {
        if (welcheSpieler != feld[coordinate(input, 0)][coordinate(input, 1)] &&
            feld[coordinate(input, 0)][coordinate(input, 1)] != 0)
        {
            feld[coordinate(input, 0)][coordinate(input, 1)] = 0;
            printf("Stein wurde erfolgreich geloescht\n");
            return VALID;
        }
    }

    if (obInMuele(feld, input) != VALID &&
        welcheSpieler != feld[coordinate(input, 0)][coordinate(input, 1)] &&
        feld[coordinate(input, 0)][coordinate(input, 1)] != 0)
    {
        feld[coordinate(input, 0)][coordinate(input, 1)] = 0;
        printf("Stein wurde erfolgreich geloescht\n");
        return VALID;
    }

    return INVALID_INPUT;
}

/*Funktion zum Simulieren der Sprungbewegung, erfordert 2 Parameter, einen zur
 *Auswahl des zu bewegenden Steins und einen zur Bestimmung des Ziels*/
int spring_movement(int feld[3][8], int input1, int input2)
{
    if (feld[coordinate(input2, 0)][coordinate(input2, 1)] != 0)
    {
        return INVALID_INPUT;
    }

    feld[coordinate(input2, 0)][coordinate(input2, 1)] =
            feld[(coordinate(input1, 0))][coordinate(input1, 1)];
    feld[coordinate(input1, 0)][coordinate(input1, 1)] = 0;
    return VALID;
}

/*Diese Funktion startet, sobald der 2Spielermodus ausgewählt wurde, sie erzeugt
 *die Phase, in der beide Spieler frei 9 Steine setzen dürfen*/
void start_2_spieler(int feld[3][8])
{
    int i = 0;
    int alteFeld[3][8];
    /*Zur Speicherung des alten Feldzustandes, für weitere
                        Berechnungen*/
    int d;
    int f;
    init_feld(feld);
    print_feld(feld);

    while (i < 18) /*Nutzen der Zaehlvariable für Abbruch der Startphase*/
    {
        if (i % 2 == 0)
            /*Nutzen der Zaehlvariable zur Bestimmung, welcher Spieler
                                  am Zug ist*/
        {
            d = user_input();
            while (
                    d == INVALID_INPUT ||
                    feld[coordinate(d, 0)][coordinate(d, 1)] !=
                    0) /*Bedingung, falls das ausgewaehlte Feld bereits besetzt ist*/
            {
                printf("Ungueltige Eingabe\n");

                d = user_input();
            }

            felder_tauschen(alteFeld, feld);
            steineSetzen(feld, d, 1);
            if (muele(alteFeld, feld, 0) ==
                VALID) /*Ablauf falls eine Muehle zustande gekommen ist*/
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest:\n");
                do /*Funktion zum Entfernen eines Steines des gegnerischen Spielers*/ {
                    f = user_input();
                } while (f == INVALID_INPUT || steineLoeschen(feld, f, 1) != VALID);
            }
        }

        if (i % 2 ==
            1) /*Nutzen der Zählvariable zur Bestimmung, welcher Spieler am Zug ist*/ /*Funktioniert analog zu Spieler 1*/
        {
            d = user_input();
            while (d == INVALID_INPUT ||
                   feld[coordinate(d, 0)][coordinate(d, 1)] != 0)
            {
                printf("Ungueltige Eingabe\n");
                d = user_input();
            }

            felder_tauschen(alteFeld, feld);
            steineSetzen(feld, d, 2);
            if (muele(alteFeld, feld, 0) == VALID)
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest:\n");
                do {
                    f = user_input();
                } while (f == INVALID_INPUT || steineLoeschen(feld, f, 2) != VALID);
            }
        }

        print_feld2(i, feld,
                    1); /*Nach jedem neuen Zug wird das Feld erneut ausgeprintet*/
        i++;
    }
}

/*Funktion um festzustellen, ob es eine neue Muehle entstanden ist. Nimmt als
 *Eingabeparameter 2 Felder und die Koordinaten eines Steines. Vergleicht
 *zuerst die Anzahl von Muehlen in dem und dem voherigen Feld, falls sie
 *gesteigert wurde gibt die Funktion 1 zurueck. Falls die Anzahl von Muehlen
 *gleich geblieben ist, checkt die Funktion ob die Steine noch in einer Muehle
 *stehen, und falls ja gibt die Funktion 1 zurueck */
int muele(int alteFeld[3][8], int neueFeld[3][8], int stein)
{
    if (stein == 0)
    {
        if (anzahlVonMuelen(alteFeld) < anzahlVonMuelen(neueFeld))
        {
            return VALID;
        }

        return 0;
    }

    if (anzahlVonMuelen(alteFeld) < anzahlVonMuelen(neueFeld))
    {
        return VALID;
    }

    if (anzahlVonMuelen(alteFeld) == anzahlVonMuelen(neueFeld))
    {
        if (obInMuele(neueFeld, stein) == VALID)
        {
            return VALID;
        }

        return 0;
    }

    return 0;
}

/*Funktion um zu prüfen ob alle Steine eines Spielers in einer Muehle sind,
 *gibt 1 zurueck falls ja */
int obAlleInMuele(int feld[3][8], int welcherSpieler)
{
    int i, j = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if (feld[i][j] == welcherSpieler)
            {
                if (obInMuele2(feld, i, j) != VALID)
                {
                    return 0;
                }
            }
        }
    }

    return VALID;
}

/*Funktion, um zu pruefen, ob sich ein Feldeintrag mit den eingegebenen
 *Koordinaten in einer Muehle befindet. Nimmt als Koordinaten 2 Integers*/

int obInMuele2(int feld[3][8], int x, int y)
{
    if (feld[x][y] == 0)
    {
        return INVALID_INPUT;
    }

    if (y % 2 != 0)
    {
        if (x == 0)
        {
            if (feld[x + 1][y] == feld[x][y] && feld[x + 2][y] == feld[x][y])
            {
                return VALID;
            }
        }

        if (x == 1)
        {
            if (feld[x - 1][y] == feld[x][y] && feld[x + 1][y] == feld[x][y])
            {
                return VALID;
            }
        }

        if (feld[x - 1][y] == feld[x][y] && feld[x - 2][y] == feld[x][y])
        {
            return VALID;
        }

        if (y == 7)
        {
            if (feld[x][y - 7] == feld[x][y] && feld[x][y - 1] == feld[x][y])
            {
                return VALID;
            }
        }

        if (feld[x][y + 1] == feld[x][y] && feld[x][y - 1] == feld[x][y])
        {
            return VALID;
        }
    }

    if (y == 0)
    {
        if (feld[x][y + 7] == feld[x][y] && feld[x][y + 6] == feld[x][y])
        {
            return VALID;
        }

        if (feld[x][y + 1] == feld[x][y] && feld[x][y + 2] == feld[x][y])
        {
            return VALID;
        }
    }

    if (y == 2 || y == 4)
    {
        if (feld[x][y + 1] == feld[x][y] && feld[x][y + 2] == feld[x][y])
        {
            return VALID;
        }

        if (feld[x][y - 1] == feld[x][y] && feld[x][y - 2] == feld[x][y])
        {
            return VALID;
        }
    }

    if (y == 6)
    {
        if (feld[x][y + 1] == feld[x][y] && feld[x][y - 6] == feld[x][y])
        {
            return VALID;
        }

        if (feld[x][y - 1] == feld[x][y] && feld[x][y - 2] == feld[x][y])
        {
            return VALID;
        }
    }

    return INVALID_INPUT;
}

/*Funktion, um die Anzahl der Steine zu finden, die ein Spieler auf dem Feld
 *hat, gibt die Anzahl der Steine des ausgewaehlten Spielers zurueck*/
int steine_zaehlen(int feld[3][8], int welcheSpieler)
{
    int i, j;
    int eins = 0;
    int zwei = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (feld[i][j] == 1)
            {
                ++eins;
            }

            if (feld[i][j] == 2)
            {
                ++zwei;
            }
        }
    }

    if (welcheSpieler == 1)
    {
        return eins;
    }

    return zwei;
}

int moving_2_spieler(int feld[3][8])
{
    int i = 0;
    int alteFeld[3][8];
    int firstInput;
    int secondInput;
    int mueleInput;
    int temp;
    while (1)
        /*Keine Abbruchbedingung, da in diesem Zusand gespielt wird bis
                  jemand gewonnen hat*/
    {
        if (i % 2 == 0)
            /*Durch i%2 iterativ die Zuege wechseln sodass jeder
                          Spieler abwechseln spielen kann*/
        {
            temp = 0; /*Temporaere Integer */

            if (steine_zaehlen(feld, 1)<
                3)
                /*Checkt ob Spieler 1 weniger als 3 Steine auf dem Feld hat,
                   beendet das Spiel falls ja.*/
            {
                printf("Spieler 2 hat gewonnen!\n");
                return VALID;
            }

            if (steine_zaehlen(feld, 1) > 3)
                /*Checkt ob sich Spieler 1 ueberhaupt
                                             bewegen kann, falls nicht wir das Spiel beendet*/
            {
                for (firstInput = 1; firstInput < 25; firstInput++)
                {
                    for (secondInput = 1; secondInput < 25; secondInput++)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            1 &&
                            normal_movement_check(feld, firstInput, secondInput) == VALID)
                        {
                            /*Falls ein Zug moeglich ist kommt man aus der Schleife raus, und
                             *man setzt temp auf 1*/
                            temp = 1;
                            break;
                        }
                    }

                    if (temp == 1)
                    {
                        break;
                    }
                }

                if (temp ==
                    0) /*Checkt ob temp gleich 0 ist ,falls ja wird das Spiel beendet*/
                {
                    printf("Spieler 2 hat gewonnen!\n");
                    return 0;
                }
            }

            printf("Waehle einen Stein den du bewegen moechtest:\n");
            firstInput = user_input();
            printf("Wohin moechtest du den Stein bewegen?:\n");
            secondInput = user_input();
            felder_tauschen(alteFeld,
                            feld); /*Vor jedem Zug wird die alteFeld aktualisiert*/
            if (steine_zaehlen(feld, 1) >
                3)
                /*Falls man mehr als 3 Steine hat bewegt man die Steine durch die
                   normal_movement Funktion */
            {
                while (
                        firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                        feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 1 ||
                        feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] != 0)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du den Stein bewegen?:\n");
                    secondInput = user_input();
                }

                normal_movement(feld, firstInput, secondInput);
            }
            else if (steine_zaehlen(feld, 1) ==
                     3)
                /*Falls man 3 Steine hat bewegt man die Steine durch die
                          spring_movement Funktion */
            {
                while (
                        firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                        feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 1 ||
                        feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] != 0)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du mit dem Stein springen?:\n");
                    secondInput = user_input();
                }

                spring_movement(feld, firstInput, secondInput);
            }

            if (muele(alteFeld, feld, secondInput) ==
                VALID)
                /*Falls nach der Zug ein Muehle entstanden ist, kann man ein
                       Stein loeschen */
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest\n");
                do {
                    mueleInput = user_input();
                } while (mueleInput == INVALID_INPUT ||
                         steineLoeschen(feld, mueleInput, 1) != VALID);
            }
        }

        if (i % 2 == 1) /*Analoge if-Bedingung fuer Spieler 2*/
        {
            temp = 0;
            if (steine_zaehlen(feld, 2) < 3)
            {
                printf("Spieler 1 hat gewonnen!\n");
                return VALID;
            }

            if (steine_zaehlen(feld, 1) > 3)
            {
                for (firstInput = 1; firstInput < 25; firstInput++)
                {
                    for (secondInput = 1; secondInput < 25; secondInput++)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            2 &&
                            normal_movement_check(feld, firstInput, secondInput) == VALID)
                        {
                            temp = 1;
                            break;
                        }
                    }

                    if (temp == 1)
                    {
                        break;
                    }
                }

                if (temp == 0)
                {
                    printf("Spieler 2 hat gewonnen!\n");
                    return 0;
                }
            }

            printf("Waehle einen Stein den du bewegen moechtest:\n");
            firstInput = user_input();
            printf("Wohin moechtest du den Stein bewegen?:\n");
            secondInput = user_input();
            felder_tauschen(alteFeld, feld);
            if (steine_zaehlen(feld, 2) > 3)
            {
                while (
                        firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                        feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 2 ||
                        feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] != 0)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du den Stein bewegen?:\n");
                    secondInput = user_input();
                }

                normal_movement(feld, firstInput, secondInput);
            }
            else if (steine_zaehlen(feld, 2) == 3)
            {
                while (
                        firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                        feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 2 ||
                        feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] != 0)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du mit dem Stein springen?:\n");
                    secondInput = user_input();
                }

                spring_movement(feld, firstInput, secondInput);
            }

            if (muele(alteFeld, feld, secondInput) == VALID)
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest\n");
                do {
                    mueleInput = user_input();
                } while (mueleInput == INVALID_INPUT ||
                         steineLoeschen(feld, mueleInput, 2) != VALID);
            }
        }

        print_feld(
                feld); /*Nach jedem abgeschlossen Zug wird das Feld neu ausgegeben*/
        i++; /*Nach jedem abgeschlossen Zug wird i um eins erhoeht*/
    }
}

/*Diese Funktion startet, sobald die Startphase abgeschlossen ist. Sie laesst
 *die Spieler abwechselnd Steine bewegen*/
int moving_2_spieler_variant(int feld[3][8])
{
    int i = 0;
    int steine_spieler1 = 10;
    int steine_spieler2 = 10;

    int alteFeld[3][8];
    int firstInput;
    int secondInput;
    int mueleInput;
    int temp;
    int temp2;
    int temp3;
    init_feld(feld);
    print_feld(feld);
    while (1)
        /*Keine Abbruchbedingung, da in diesem Zusand gespielt wird bis
                      jemand gewonnen hat*/
    {
        if (i % 2 == 0)
            /*Durch i%2 iterativ die Zuege wechseln sodass jeder
                                  Spieler abwechseln spielen kann*/
        {
            temp = 0;
            temp2 = 0; /*Temporaere Integer */
            temp3 = 0;

            if (steine_zaehlen(feld, 1) < 3 &&
                steine_spieler1 == 0)
                /*Checkt ob Spieler 1 weniger als 3 Steine auf
                                                  dem Feld hat, beendet das Spiel falls ja.*/
            {
                printf("Spieler 2 hat gewonnen!\n");
                return VALID;
            }

            if (steine_zaehlen(feld, 1) > 3 &&
                steine_spieler1 == 0)
                /*Checkt ob sich Spieler 1 ueberhaupt bewegen
                                                  kann, falls nicht wir das Spiel beendet*/
            {
                for (firstInput = 1; firstInput < 25; firstInput++)
                {
                    for (secondInput = 1; secondInput < 25; secondInput++)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            1 &&
                            normal_movement_check(feld, firstInput, secondInput) == VALID)
                        {
                            /*Falls ein Zug moeglich ist kommt man aus der Schleife raus, und
                             *man setzt temp auf 1*/
                            temp = 1;
                            break;
                        }
                    }

                    if (temp == 1)
                    {
                        break;
                    }
                }

                if (steine_spieler1 != 0)
                {
                    temp = 1;
                }

                if (temp ==
                    0) /*Checkt ob temp gleich 0 ist ,falls ja wird das Spiel beendet*/
                {
                    printf("Spieler 2 hat gewonnen!\n");
                    return 0;
                }
            }

            printf("Waehle oder Setze einen Stein :\n");
            firstInput = user_input();

            if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 0)
            {
                printf("Wohin moechtest du den Stein bewegen?:\n");
                secondInput = user_input();
                temp3 = 1;
            }

            felder_tauschen(alteFeld, feld);
            if (steine_zaehlen(feld, 1) + steine_spieler1 >
                3)
                /*Falls man mehr als 3 Steine hat bewegt man die Steine durch die
                               normal_movement Funktion */
            {
                if (temp3 == 0 ||
                    normal_movement_check(feld, firstInput, secondInput) ==
                    INVALID_INPUT ||
                    feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 1)
                {
                    while (1)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            0 &&
                            steine_spieler1 > 0)
                        {
                            steineSetzen(feld, firstInput, 1);
                            --steine_spieler1;
                            temp2 = 1;
                            break;
                        }

                        printf("Die Eingabe war falsch, versuche es erneut\n");
                        printf("Waehle einen Stein den du bewegen moechtest:\n");
                        firstInput = user_input();
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] !=
                            0)
                        {
                            printf("Wohin moechtest du den Stein bewegen?:\n");
                            secondInput = user_input();
                            if (normal_movement_check(feld, firstInput, secondInput) !=
                                INVALID_INPUT &&
                                feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                                1)
                            {
                                break;
                            }
                        }
                    }
                }

                if (temp2 != 1)
                {
                    normal_movement(feld, firstInput, secondInput);
                }
            }
            else if (steine_zaehlen(feld, 1) == 3 &&
                     steine_spieler1 ==
                     0)
                /*Falls man 3 Steine hat bewegt man die Steine durch
                                          die spring_movement Funktion */
            {
                while (
                        firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                        feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 1 ||
                        feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] != 0)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du mit dem Stein springen?:\n");
                    secondInput = user_input();
                }

                spring_movement(feld, firstInput, secondInput);
            }

            if (temp2 == 1)
            {
                secondInput = 0;
            }

            if (muele(alteFeld, feld, secondInput) ==
                VALID)
                /*Falls nach der Zug ein Muehle entstanden ist, kann man ein
                                   Stein loeschen */
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest\n");
                do {
                    mueleInput = user_input();
                } while (mueleInput == INVALID_INPUT ||
                         steineLoeschen(feld, mueleInput, 1) != VALID);
            }
        }

        if (i % 2 == 1) /*Analoge if-Bedingung fuer Spieler 2*/
        {
            temp = 0;
            temp2 = 0;
            temp3 = 0;
            if (steine_zaehlen(feld, 2) < 3 && steine_spieler2 == 0)
            {
                printf("Spieler 1 hat gewonnen!\n");
                return VALID;
            }

            if (steine_zaehlen(feld, 1) > 3 && steine_spieler2 == 0)
            {
                for (firstInput = 1; firstInput < 25; firstInput++)
                {
                    for (secondInput = 1; secondInput < 25; secondInput++)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            2 &&
                            normal_movement_check(feld, firstInput, secondInput) == VALID)
                        {
                            temp = 1;
                            break;
                        }
                    }

                    if (temp == 1)
                    {
                        break;
                    }
                }

                if (steine_spieler2 != 0)
                {
                    temp = 1;
                }

                if (temp == 0)
                {
                    printf("Spieler 2 hat gewonnen!\n");
                    return 0;
                }
            }

            printf("Waehle oder Setze einen Stein :\n");
            firstInput = user_input();
            if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 0)
            {
                printf("Wohin moechtest du den Stein bewegen?:\n");
                secondInput = user_input();
                temp3 = 1;
            }

            felder_tauschen(alteFeld, feld);
            if (steine_zaehlen(feld, 2) + steine_spieler2 >
                3)
                /*Falls man mehr als 3 Steine hat bewegt man die Steine durch die
                               normal_movement Funktion */
            {
                if (temp3 == 0 ||
                    normal_movement_check(feld, firstInput, secondInput) ==
                    INVALID_INPUT ||
                    feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 2)
                {
                    while (1)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            0 &&
                            steine_spieler2 > 0)
                        {
                            steineSetzen(feld, firstInput, 2);
                            --steine_spieler2;
                            temp2 = 1;
                            break;
                        }

                        printf("Die Eingabe war falsch, versuche es erneut\n");
                        printf("Waehle einen Stein den du bewegen moechtest:\n");
                        firstInput = user_input();
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] !=
                            0)
                        {
                            printf("Wohin moechtest du den Stein bewegen?:\n");
                            secondInput = user_input();
                            if (normal_movement_check(feld, firstInput, secondInput) !=
                                INVALID_INPUT &&
                                feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                                2)
                            {
                                break;
                            }
                        }
                    }
                }

                if (temp2 != 1)
                {
                    normal_movement(feld, firstInput, secondInput);
                }
            }
            else if (steine_zaehlen(feld, 2) == 3)
            {
                while (
                        firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                        feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 2 ||
                        feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] != 0)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du mit dem Stein springen?:\n");
                    secondInput = user_input();
                }

                spring_movement(feld, firstInput, secondInput);
            }

            if (temp2 == 1)
            {
                secondInput = 0;
            }

            if (muele(alteFeld, feld, secondInput) == VALID)
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest\n");
                do {
                    mueleInput = user_input();
                } while (mueleInput == INVALID_INPUT ||
                         steineLoeschen(feld, mueleInput, 2) != VALID);
            }
        }

        print_feld3(feld, steine_spieler1,
                    steine_spieler2);
        /*Nach jedem abgeschlossen Zug wird das Feld
                                            neu ausgegeben*/
        i++; /*Nach jedem abgeschlossen Zug wird i um eins erhoeht*/
    }
}

/*Diese Funktion startet, sobald der 1Spielermodus ausgewählt wurde, sie erzeugt
 *die Phase, in der man selbst und der Computer frei 9Steine setzt*/
void start_ai_spieler(int feld[3][8])
{
    /*User beginnt*/
    int i = 0;
    int alteFeld[3][8];
    /*Zur Speicherung des alten Feldzustandes, für weitere
                        Berechnungen*/
    int d;
    int f;
    init_feld(feld);
    print_feld(feld);
    while (i < 18) /*Nutzen der Zählvariable für Abbruch der Startphase*/
    {
        if (i % 2 ==
            0) /*Nutzen der Zählvariable zur Bestimmung, welcher Spieler am Zug ist*/ /*Funktioniert analog zu start_2_spieler*/
        {
            d = user_input();
            while (d == INVALID_INPUT ||
                   feld[coordinate(d, 0)][coordinate(d, 1)] != 0)
            {
                printf("Ungueltige Eingabe\n");
                d = user_input();
            }

            felder_tauschen(alteFeld, feld);
            steineSetzen(feld, d, 1);
            if (muele(alteFeld, feld, 0) == VALID)
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest\n");
                do {
                    f = user_input();
                } while (f == INVALID_INPUT || steineLoeschen(feld, f, 1) != VALID);
            }
        }

        if (i % 2 == 1) /*Nutzen der Zählvariable zur Bestimmung, welcher Spieler am Zug ist*/ /*Zug des Computers*/
        {
            time_t t; /*Variable zum Erzeugen eines zufällig ausgewählten Feldes*/
            felder_tauschen(alteFeld, feld);

            srand((int) time(&t));
            d = (rand() % 24) +
                1; /*Anpassung der Variablen, damit sie zwischen 1-24 liegen*/
            f = (rand() % 24) + 1;
            while (steineSetzen(feld, d, 2) !=
                   VALID)
                /*Falls das ausgewählte Feld bereits besetzt ist, wird von
                          dort ausgehend jedes weitere Feld getestet, bis ein
                          Freies gefunden wird*/
            {
                if (d >= 24)
                {
                    d = 1;
                }

                ++d;
            }

            if (muele(alteFeld, feld, 0) == VALID)
                /*Falls eine Mühle entstanden ist,
                                                   wird die zweite Zufallsvariable genutzt, um
                                                   nach o.g. Prinzip einen Stein zu loeschen*/
            {
                felder_tauschen(alteFeld, feld);
                while (steineLoeschen(feld, f, 2) != VALID)
                {
                    if (f >= 24)
                    {
                        f = 1;
                    }

                    ++f;
                }
            }
        }

        print_feld2(
                i, feld,
                2); /*Nach jedem abgeschlossen Zug wird das Feld neu ausgegeben*/
        i++;
    }
}

/*Diese Funktion startet, sobald die Startphase abgeschlossen ist. Sie laesst
 *den Spieler und den Computer abwechselnd Steine bewegen*/
int moving_ai_spieler(int feld[3][8])
{
    int i = 0;
    int alteFeld[3][8];
    int firstInput;
    int secondInput;
    int mueleInput;
    int temp;
    while (1)
        /*Keine Abbruchbedingung, da in diesem Zusand gespielt wird bis
                  jemand gewonnen hat*/
    {
        if (i % 2 ==
            0) /*Spieler 1 ist am Zug, Prinzip identisch zu moving_2_spieler*/
        {
            temp = 0;
            if (steine_zaehlen(feld, 1) < 3)
            {
                printf("Spieler 2 hat gewonnen!\n");
                return VALID;
            }

            if (steine_zaehlen(feld, 1) > 3)
            {
                for (firstInput = 1; firstInput < 25; firstInput++)
                {
                    for (secondInput = 1; secondInput < 25; secondInput++)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            1 &&
                            normal_movement_check(feld, firstInput, secondInput) == VALID)
                        {
                            temp = 1;
                            break;
                        }
                    }

                    if (temp == 1)
                    {
                        break;
                    }
                }

                if (temp == 0)
                {
                    printf("Spieler 2 hat gewonnen!\n");
                    return 0;
                }
            }

            printf("Waehle einen Stein den du bewegen moechtest:\n");
            firstInput = user_input();
            printf("Wohin moechtest du den Stein bewegen?:\n");
            secondInput = user_input();
            felder_tauschen(alteFeld, feld);
            if (steine_zaehlen(feld, 1) > 3)
            {
                while (firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                       normal_movement_check(feld, firstInput, secondInput) != VALID)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du den Stein bewegen?:\n");
                    secondInput = user_input();
                }

                normal_movement(feld, firstInput, secondInput);
            }
            else if (steine_zaehlen(feld, 1) == 3)
            {
                while (
                        firstInput == INVALID_INPUT || secondInput == INVALID_INPUT ||
                        feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] != 1 ||
                        feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] != 0)
                {
                    printf("Die Eingabe war falsch, versuche es erneut\n");
                    printf("Waehle einen Stein den du bewegen moechtest:\n");
                    firstInput = user_input();
                    printf("Wohin moechtest du mit dem Stein springen?:\n");
                    secondInput = user_input();
                }

                spring_movement(feld, firstInput, secondInput);
            }

            if (muele(alteFeld, feld, secondInput) == VALID)
            {
                felder_tauschen(alteFeld, feld);
                print_feld(feld);
                printf("Es gab eine Muehle, waehle einen Stein den du vom Gegner "
                       "loeschen moechtest\n");
                do {
                    mueleInput = user_input();
                } while (mueleInput == INVALID_INPUT ||
                         steineLoeschen(feld, mueleInput, 1) != VALID);
            }
        }

        if (i % 2 == 1) /*Computer ist am Zug. */
        {
            temp = 0;
            if (steine_zaehlen(feld, 2) < 3)
            {
                printf("Spieler 1 hat gewonnen!\n");
                return VALID;
            }

            felder_tauschen(alteFeld, feld);
            if (steine_zaehlen(feld, 2) >
                3)
                /*Falls der Computer mehr als 3 verbleibende Steine hat, testet er
                   iterativ jede Möglichkeit der Bewegung, beginnend von 1nach1*/
            {
                for (firstInput = 1; firstInput < 25; firstInput++)
                {
                    for (secondInput = 1; secondInput < 25; secondInput++)
                    {
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            2 &&
                            normal_movement_check(feld, firstInput, secondInput) == VALID)
                        {
                            /*Sobald eine Mögliche Bewegung gefunden wurde, wird die Bewegung
                             *beibehalten indem man temp auf 1 erhöht*/
                            temp = 1;
                            break;
                        }
                    }

                    if (temp == 1) /*Abbruchbedingung für temp*/
                    {
                        break;
                    }
                }

                if (temp == 0)
                    /*Falls nämlich jede Position durchgegangen wurde und
                             keine mögliche Bewegung esxistiert, verliert der Spieler*/
                {
                    printf("Verloren\n");
                    return 0;
                }

                normal_movement(feld, firstInput,
                                secondInput);
                /*Erst nach diesen Schritten wird die
                                        Bewegung ausgeführt*/
            }
            else if (steine_zaehlen(feld, 2) ==
                     3)
                /*Falls er nur noch 3Steine besitzt, darf gesprungen werden,
                          dies funktioniert wieder iterativ*/
            {
                for (firstInput = 1; firstInput < 25; firstInput++)
                {
                    for (secondInput = 1; secondInput < 25; secondInput++)
                    {
                        /*Man überprüft diesmal nur, ob der 1. ausgewählte Platz einen Stein
                         *des Computers enthält und der 2. leer ist*/
                        if (feld[coordinate(firstInput, 0)][coordinate(firstInput, 1)] ==
                            2 &&
                            feld[coordinate(secondInput, 0)][coordinate(secondInput, 1)] ==
                            0)
                        {
                            /*Sobald eine Mögliche bewegung gefunden wurde, wird die Bewegung
                             *beibehalten indem man temp auf 1 erhöht*/
                            temp = 1;
                            break;
                        }
                    }

                    if (temp == 1)
                    {
                        break;
                    }
                }

                spring_movement(feld, firstInput,
                                secondInput); /*Ausführung des Sprungs*/
            }

            if (muele(alteFeld, feld, secondInput) == VALID)
            {
                mueleInput = 1;
                felder_tauschen(alteFeld, feld);
                while (steineLoeschen(feld, mueleInput, 2) !=
                       VALID)
                    /*Falls eine Mühle entstanden ist, wird iterativ getest
                            und sobald ein gegnerische Stein gefunden wurde, dieser
                            gelöscht*/
                {
                    ++mueleInput;
                }
            }
        }

        print_feld(feld);
        i++;
    }
}

/*Funktioniert wie normal_movement, jedoch wird nur getestet, ob die eingegebene
 *Bewegung korrekt ist, diese wird jedoch nicht ausgeführt*/
int normal_movement_check(int feld[3][8], int firstInput, int secondInput)
{
    int cord_now_1, cord_now_2, cord_then_1, cord_then_2;

    cord_now_1 = coordinate(firstInput, 0);
    cord_now_2 = coordinate(firstInput, 1);
    cord_then_1 = coordinate(secondInput, 0);
    cord_then_2 = coordinate(secondInput, 1);
    if (feld[cord_now_1][cord_now_2] == 0)
    {
        return INVALID_INPUT;
    }

    if (feld[cord_then_1][cord_then_2] != 0)
    {
        return INVALID_INPUT;
    }

    if (cord_now_1 == cord_then_1)
    {
        if (cord_now_2 == cord_then_2)
        {
            return INVALID_INPUT;
        }

        if ((cord_now_2 + 1) == cord_then_2 || (cord_now_2 - 1) == cord_then_2 ||
            (cord_now_2 + 7) == cord_then_2 || (cord_now_2 - 7) == cord_then_2)
        {
            return VALID;
        }
        else
        {
            return INVALID_INPUT;
        }
    }

    if (cord_now_2 == cord_then_2)
    {
        if (cord_now_2 % 2 == 0)
        {
            return INVALID_INPUT;
        }

        if ((cord_now_1 + 1) == cord_then_1 || (cord_now_1 - 1) == cord_then_1)
        {
            return VALID;
        }
        else
        {
            return INVALID_INPUT;
        }
    }
    else
    {
        return INVALID_INPUT;
    }

    return INVALID_INPUT;
}

/*Funktion, die eine Zeichenfolge gemäß dem angegebenen Parameter zurueckgibt,
 *rot 1 wenn 1, blau 2, wenn 2 und 0 als Standardfall*/
const char *ntoc(int n)
{
    switch (n)
    {
        case 1:
            return RED1;
        case 2:
            return BLUE2;
        default:
            return "0";
    }
}

/*Funktion zum Starten des Spiels und Praesentieren des Spielmenues fuer den
 *Spieler */
int start_game(int feld[3][8])
{
    int d;
    system("@cls||clear");
    printf("    :::       :::       :::::::::::       :::        :::        :::  "
           "  :::       ::::::::         :::   :::         :::   :::       "
           "::::::::::       ::::    ::: \n"
           "   :+:       :+:           :+:           :+:        :+:        :+:   "
           ":+:       :+:    :+:       :+:+: :+:+:       :+:+: :+:+:      :+:    "
           "          :+:+:   :+:  \n"
           "  +:+       +:+           +:+           +:+        +:+        +:+  "
           "+:+        +:+    +:+      +:+ +:+:+ +:+     +:+ +:+:+ +:+     +:+   "
           "           :+:+:+  +:+   \n");
    printf(" +#+  +:+  +#+           +#+           +#+        +#+        +#++:++ "
           "        +#+    +:+      +#+  +:+  +#+     +#+  +:+  +#+     +#++:++# "
           "        +#+ +:+ +#+    \n"
           "+#+ +#+#+ +#+           +#+           +#+        +#+        +#+  +#+ "
           "       +#+    +#+      +#+       +#+     +#+       +#+     +#+       "
           "       +#+  +#+#+#     \n");
    printf("#+#+# #+#+#            #+#           #+#        #+#        #+#   #+# "
           "      #+#    #+#      #+#       #+#     #+#       #+#     #+#        "
           "      #+#   #+#+#      \n"
           "###   ###         ###########       ########## ########## ###    ### "
           "      ########       ###       ###     ###       ###     ##########  "
           "     ###    ####    \n\n");
    sleep(1);
    printf("      :::::::::       ::::::::::       ::::::::::: \n"
           "     :+:    :+:      :+:                  :+:      \n"
           "    +:+    +:+      +:+                  +:+       \n"
           "   +#++:++#+       +#++:++#             +#+        \n"
           "  +#+    +#+      +#+                  +#+         \n"
           " #+#    #+#      #+#                  #+#          \n"
           "#########       ##########       ###########    \n\n");
    sleep(1);
    printf("        :::   :::      :::    :::       ::::::::::       :::    :::  "
           "     :::        ::::::::::       ::: \n"
           "      :+:+: :+:+:     :+:    :+:       :+:              :+:    :+:   "
           "    :+:        :+:              :+:  \n"
           "    +:+ +:+:+ +:+    +:+    +:+       +:+              +:+    +:+    "
           "   +:+        +:+              +:+   \n");
    printf("   +#+  +:+  +#+    +#+    +:+       +#++:++#         +#++:++#++     "
           "  +#+        +#++:++#         +#+    \n"
           "  +#+       +#+    +#+    +#+       +#+              +#+    +#+      "
           " +#+        +#+              +#+     \n"
           " #+#       #+#    #+#    #+#       #+#              #+#    #+#       "
           "#+#        #+#                       \n"
           "###       ###     ########        ##########       ###    ###       "
           "########## ##########       ###       \n\n");

    printf("Druecke 1 fuer den Zweispielermodus:\nDruecke 2 fuer den "
           "Einzelspielermodus:\nDruecke 3 um die Lasker-Variante zu spielen\n"
           "Druecke 4 um dir die Regeln anzeigen zu lassen: \n");

    d = user_input();
    while (d != 1 && d != 2 && d != 3)
    {
        if (d == 4)
        {
            system("@cls||clear"); /*Regeln des Muehlespiels*/
            printf("Ziel und Grundlagen des Spiels:\nSorge dafuer, dass dein Gegner "
                   "weniger als 3 Steine uebrig hat oder dass er nicht mehr ziehen "
                   "kann.\nDas Spiel besteht aus 3 Phasen: Einsetzen, Versetzen und "
                   "Endspiel.\n");
            printf("\nIn jeder Phase kannst du Steine deines Gegners vom Brett "
                   "entfernen, wenn du 3 Steine in eine Reihe setzt (horizontal oder "
                   "vertikal) - diese drei Steine werden auch Muehle genannt.\nJedes "
                   "Mal, wenn du eine Muehle bildest, musst du einen Stein deines "
                   "Gegners entfernen, wenn nicht alle seine Steine Teile von seinen "
                   "Muehlen sind - diese sind geschuetzt.\nAllerdings nur solange "
                   "der andere Spieler mehr als 3 Steine hat!\n");
            printf("\nSonderfall: Seit dem Jahr 2010 regeln die offiziellen "
                   "Muehleregeln den Fall neu, dass eine Muehle geschlossen wird "
                   "aber alle Steine des Gegners in eine Muehle verbaut sind.\nIn "
                   "diesem Sonderfall darf ausnahmsweise auch ein geschuetzter Stein "
                   "des Gegners entfernt werden! ");
            printf(
                    "\n\nPhase 1: Das Einsetzen der Steine\nZuerst muessen die Spieler "
                    "jedes Mal, wenn sie am Zug sind, einen ihrer Steine auf dem Brett "
                    "auf eine der Kreuzungen der horizontalen und vertikalen Linien "
                    "setzen\n(kenntlich am Punkt).\nDiese Phase ist zu Ende, wenn jeder "
                    "der Spieler seine 9 Steine eingesetzt hat.\n");
            printf("\nPhase 2: Das Versetzen der Steine\nWenn jeder Spieler seine 9 "
                   "Steine platziert hat, beginnt die 2. Phase. In jedem Zug muss "
                   "der Spieler einen seiner Steine auf einen angrenzenden freien "
                   "Platz versetzen.\nAuch hier gilt wieder, dass er, wenn dabei "
                   "eine Muehle entsteht, einen ungeschuetzten Stein seines Gegners "
                   "vom Brett nehmen muss\n(also einen Stein, der nicht an einer "
                   "gegnerischen Mühle beteiligt ist).\n");
            printf("Phase 3: Das Versetzen der Steine bei weniger als 4 eigenen "
                   "Steinen\nDie 3. Phase beginnt, wenn einer der Spieler nur noch 3 "
                   "Steine übrig hat.\nEr darf seinen Stein, den er im Zug bewegt, "
                   "nun nicht nur auf einen angrenzenden Platz versetzen, sondern "
                   "auf einen beliebigen freien Platz.\nEr darf also beliebig mit "
                   "dem Stein springen.\nDas gilt auch für den anderen Spieler, "
                   "sobald dieser weniger als 4 eigene Steine hat.\n");
            printf("\nEnde des Spiels:\nDas Spiel endet, wenn eine der folgenden "
                   "Bedingungen erfuellt ist:\n-Ein Spieler kann keinen guetigen Zug "
                   "mehr machen.\n-Ein Spieler hat nur noch drei Steine auf dem "
                   "Brett - egal ob verteilt oder in einer Muehle - und der andere "
                   "Spieler schließt eine Muehle.\nIn beiden Faellen hat der andere "
                   "Spieler gewonnen. ");
            printf(
                    "\n\nStrategie:\nAus der deutschen Wikipedia: Insbesondere waehrend "
                    "der Anfangsphase des Spieles ist es weniger wichtig, fruehzeitig "
                    "Muehlen zu bilden,\nals vielmehr eine große Beweglichkeit seiner "
                    "Steine sicherzustellen.\nSo sind die vier zentralen Kreuzungspunkte "
                    "des Muehlebretts bevorzugt zu besetzen, waehrend die Eckpunkte zu "
                    "meiden sind. \nAußerdem ist es beim Schlagen eines Steines meistens "
                    "besser, eine zusaetzliche eigene Mühle zu oeffnen, als eine ");
            printf(
                    "gegnerische Muehle zu verhindern.\nEine gaengige Strategie ist die "
                    "Zentrumsmuehle. Sie besteht darin, als anziehender Spieler zuegig "
                    "eine Muehle auf dem mittleren Ring anzustreben.\nWeiß versucht, "
                    "zwei der zentralen Kreuzungspunkte und anschließend die Ecke ");
            printf(
                    "zwischen diesen Kreuzungspunkten zu besetzen.\nDamit droht er mit "
                    "zwei offenen Muehlen gleichzeitig. Erfahrene Schwarz-Spieler "
                    "kontern, indem sie ebenfalls mit den ersten beiden Steinen "
                    "Kreuzungen besetzen.\nDiese Strategie fuehrt bei optimalem Spiel "
                    "beider Kontrahenten zu Remis.\nDa ein solches Spiel jedoch schwer "
                    "zu durchschauen ist und beide Spieler deshalb anfaellig für Fehler "
                    "sind,\nendet das Spiel in der Praxis vergleichsweise haeufig mit "
                    "dem Sieg des einen oder anderen Spielers.\n");
            printf("\nRegeln für Unentschieden:\nEinige Parteien enden "
                   "unentschieden. Das heißt, dass keiner der beiden Spieler mehr "
                   "gewinnen kann, es sei denn der Gegner macht einen schweren "
                   "Fehler.\nIhr seid dann nicht gezwungen, endlos weiterzuspielen "
                   "und auf den Fehler des Gegenspielers zu lauern...\nOffiziell ist "
                   "ein Spiel unentschieden, wenn:\n-beide Spieler dem "
                   "zustimmen.\n-3 Mal dieselbe Stellung erreicht wird.\n-nach 50 "
                   "aufeinanderfolgenden Zügen keine Muehle geschlossen wurde.\n");
            printf(
                    "\nLasker-Muehle:\n es gibt zwei Regelaenderungen: Die beiden Phasen "
                    "werden nicht voneinander getrennt, d. h. es steht den Spielern "
                    "frei, einen Stein zu ziehen oder einen Stein zu setzen. Es "
                    "wird mit je zehn Steinen gespielt.\n");
            printf(
                    "\nQuelle: https://www.brettspielnetz.de/spielregeln/muehle.php  \n"
                    "\thttps://de.wikipedia.org/wiki/Muehle_(Spiel)\n\n");
            printf(
                    "Druecke 1 fuer den Zweispielermodus:\nDruecke 2 fuer den "
                    "Einzelspielermodus:\nDruecke 3 um die Lasker-Variante zu spielen\n"
                    "Druecke 4 um dir die Regeln anzeigen zu lassen: \n");
            d = user_input();
            continue;
        }

        printf("Falsche Eingabe\n");
        d = user_input();
    }

    if (d == 1)
    {
        start_2_spieler(feld);
        moving_2_spieler(feld);
        return 1;
    }
    else if (d == 2)
    {
        start_ai_spieler(feld);
        moving_ai_spieler(feld);
        return 1;
    }
    else if (d == 3)
    {
        moving_2_spieler_variant(feld);

        return 1;
    }

    return -1;
}

/*Diese Funktion dient nur als Huelle für das eigentliche Spiel, um nach
 *Abschluss, die Moeglichkeit zu bekommen, das Spiel erneut zu starten*/
void Muehle(int feld[3][8])
{
    int i = 1;
    int d = 0;
    while (i)
    {
        if (start_game(feld) == 1)
        {
            printf("Druecke 1 um das Spiel erneut starten zu koennen\n");
            d = user_input();
        }

        if (d == 1)
        {
            continue;
        }
        else
        {
            break;
        }
    }
}

/*Funktioniert wie print_feld, nur, dass hier die Anzahl der verbleibenden
 *Steine in der Startphase mitgezaehlt werden*/
void print_feld2(int i, int feld[3][8], int modus)
{
    char str1[] = "%s-----------------------%s-----------------------%s\t\t1-----"
                  "------------------2-----------------------3\n";
    char str2[] = "|\t%s---------------%s---------------%s\t|\t\t|\t4------------"
                  "---5---------------6\t|\n";
    char str3[] =
            "|\t|\t%s-------%s-------%s\t|\t|\t\t|\t|\t7-------8-------9\t|\t|\n";
    char str4[] =
            "%s-------%s-------%s\t \t%s-------%s-------%s\t\t10------11------12\t "
            "\t13------14------15\n";
    char str5[] =
            "|\t|\t%s-------%s-------%s\t|\t|\t\t|\t|\t16------17------18\t|\t|\n";
    char str6[] = "|\t%s---------------%s---------------%s\t|\t\t|\t19-----------"
                  "---20--------------21\t|\n";
    char str7[] = "%s-----------------------%s-----------------------%s\t\t22----"
                  "------------------23----------------------24\n\n";
    system("@cls||clear");
    printf("\n\n");

    printf(str1, ntoc(feld[0][0]), ntoc(feld[0][1]), ntoc(feld[0][2]));
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf(str2, ntoc(feld[1][0]), ntoc(feld[1][1]), ntoc(feld[1][2]));
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf(str3, ntoc(feld[2][0]), ntoc(feld[2][1]), ntoc(feld[2][2]));
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");

    printf(str4, ntoc(feld[0][7]), ntoc(feld[1][7]), ntoc(feld[2][7]),
           ntoc(feld[2][3]), ntoc(feld[1][3]), ntoc(feld[0][3]));
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");

    printf(str5, ntoc(feld[2][6]), ntoc(feld[2][5]), ntoc(feld[2][4]));
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf(str6, ntoc(feld[1][6]), ntoc(feld[1][5]), ntoc(feld[1][4]));
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf(str7, ntoc(feld[0][6]), ntoc(feld[0][5]), ntoc(feld[0][4]));

    if (modus ==
        1)
    { /*2Spielermodus, zaehlt die verbleibenden Steine von 9 ab herunter*/
        if (i % 2 == 0)
        {
            printf("Spieler 1 hat noch %i Steine uebrig\n", (8 - (i / 2)));
            printf("Spieler 2 hat noch %i Steine uebrig\n", (8 - (i / 2 - 1)));
        }
        else
        {
            printf("Spieler 1 hat noch %i Steine uebrig\n", (8 - (i / 2)));
            printf("Spieler 2 hat noch %i Steine uebrig\n", (8 - (i / 2)));
        }
    }
    else
    { /*1Spielermodus, dort wird nur für den Spieler mitgezählt*/
        printf("Spieler 1 hat noch %i Steine uebrig\n", (8 - (i / 2)));
    }

    sleep(1);
}

void print_feld3(int feld[3][8], int spieler1, int spieler2)
{
    char str1[] = "%s-----------------------%s-----------------------%s\t\t1-----"
                  "------------------2-----------------------3\n";
    char str2[] = "|\t%s---------------%s---------------%s\t|\t\t|\t4------------"
                  "---5---------------6\t|\n";
    char str3[] =
            "|\t|\t%s-------%s-------%s\t|\t|\t\t|\t|\t7-------8-------9\t|\t|\n";
    char str4[] =
            "%s-------%s-------%s\t \t%s-------%s-------%s\t\t10------11------12\t "
            "\t13------14------15\n";
    char str5[] =
            "|\t|\t%s-------%s-------%s\t|\t|\t\t|\t|\t16------17------18\t|\t|\n";
    char str6[] = "|\t%s---------------%s---------------%s\t|\t\t|\t19-----------"
                  "---20--------------21\t|\n";
    char str7[] = "%s-----------------------%s-----------------------%s\t\t22----"
                  "------------------23----------------------24\n\n";
    system("@cls||clear");
    printf("\n\n");

    printf(str1, ntoc(feld[0][0]), ntoc(feld[0][1]), ntoc(feld[0][2]));
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf(str2, ntoc(feld[1][0]), ntoc(feld[1][1]), ntoc(feld[1][2]));
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf(str3, ntoc(feld[2][0]), ntoc(feld[2][1]), ntoc(feld[2][2]));
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");

    printf(str4, ntoc(feld[0][7]), ntoc(feld[1][7]), ntoc(feld[2][7]),
           ntoc(feld[2][3]), ntoc(feld[1][3]), ntoc(feld[0][3]));
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");
    printf("|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\t\t|\t|\t|\n");

    printf(str5, ntoc(feld[2][6]), ntoc(feld[2][5]), ntoc(feld[2][4]));
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf("|\t|\t \t|\t \t|\t|\t\t|\t|\t \t|\t \t|\t|\n");
    printf(str6, ntoc(feld[1][6]), ntoc(feld[1][5]), ntoc(feld[1][4]));
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf("| \t \t \t|\t \t \t|\t\t|\t \t \t|\t \t \t|\n");
    printf(str7, ntoc(feld[0][6]), ntoc(feld[0][5]), ntoc(feld[0][4]));

    printf("Spieler 1 hat noch %i Steine uebrig\n", spieler1);
    printf("Spieler 2 hat noch %i Steine uebrig\n", spieler2);

    sleep(1);
}