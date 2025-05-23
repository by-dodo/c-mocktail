#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DRINKS 15
#define PRINT_OPTION_VERBOSE 0
#define PRINT_OPTION_DELETE 1
#define PRINT_OPTION_ALPHA 2

#define RESET       "\033[0m"
#define WHITE       "\033[38;5;15m"
#define GREY        "\033[3;38;5;245m"
#define RED         "\033[38;5;196m"
#define PINK_NEON   "\033[38;5;207m"
#define PINK_DIRTY  "\033[38;5;13m"
#define PINK_MID    "\033[38;5;219m"
#define PINK_LIGHT  "\033[38;5;225m"
#define PINK_PASTEL "\033[38;5;219m"
#define GREEN       "\033[38;5;10m"

struct Drink {
    char name[25];
    char description[100];
    float price;
    float rating;
};

struct Drink mocktails[MAX_DRINKS] = {
    {
        "Ljetni osvjezivac",
        "Mjesavina limete, mente i gazirane vode.",
        3.50,
        7.8
    },
    {
        "Grozdjani bliss",
        "Sok od crnog grozdja, menta i limun.",
        4.00,
        6.3
    },
    {
        "Narandzin snop",
        "Svjezi sok od narandze, malo meda i menta.",
        3.70,
        8.2
    },
    {
        "Tropski raj",
        "Kokosovo mlijeko, ananas i banana bez alkohola.",
        7.50,
        3.7
    },
    {
        "Ledeni caj",
        "Fuzetea breskva, crni caj i hibiskus.",
        3.60,
        9.6
    },
    {
        "Ruzina magla",
        "Sirup od ruze, limunada i svjeze latice.",
        12.00,
        3.4
    },
    {
        "Borovnicki uzitak",
        "Borovnice, lavanda i limun u gaziranoj vodi.",
        5.30,
        1.1
    }
};

int numberOfDrinks = 7;

void printDivisionLine() {
    printf(GREY"   ______________________________________________________\n" RESET);
}

bool scanInt(int* result) {
    char buffer[100], leftover;
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    int parsedCount = sscanf(buffer, "%d %c", result, &leftover);
    if (parsedCount != 1 || strspn(buffer, "-0123456789 \n") != strlen(buffer)) {
        return false;
    }
    return true;
}

bool scanFloat(float* result) {
    char buffer[100], leftover;
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    int parsedCount = sscanf(buffer, "%f %c", result, &leftover);
    if (parsedCount != 1 || strspn(buffer, "-0123456789 .\n") != strlen(buffer)) {
        return false;
    }
    return true;
}

bool scanChar(char* result) {
    char buffer[100], leftover;
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    int parsedCount = sscanf(buffer, "%c %c", result, &leftover);
    if (parsedCount != 1) {
        return false;
    }
    return true;
}

void scanString(char* result) {
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(result, buffer);
}

void printMocktail(struct Drink mocktail, int printOption, int index) {
    switch (printOption) {
        case PRINT_OPTION_ALPHA:
            printf("\t");
            if (index > 0) {
                printf(WHITE "%2d: " RESET,index);
            }
            printf(PINK_PASTEL "%-25s" PINK_MID "%10.2f €\t" PINK_LIGHT "%4.1f/10\n" RESET, mocktail.name, mocktail.price, mocktail.rating);
            break;
        case PRINT_OPTION_VERBOSE:
            printf(PINK_LIGHT "\t%s," RESET " %.2f €, %.1f/10\n", mocktail.name,mocktail.price, mocktail.rating);
            printf( GREY "\t%s\n" RESET, mocktail.description);
            break;
        case PRINT_OPTION_DELETE:
            printf(WHITE "\t%d:\t%s\n " RESET, index + 1, mocktail.name);
            break;
    }
}

void listAlphabetically() {
    struct Drink sorted[numberOfDrinks];
    for (int i = 0; i < numberOfDrinks; i++) {
        sorted[i] = mocktails[i];
    }
    for (int i = 0; i < numberOfDrinks; i++) {
        for (int j = 0; j < numberOfDrinks - 1 - i; j++) {
            if (tolower(sorted[j].name[0]) > tolower(sorted[j + 1].name[0])) {
                struct Drink temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
            else if (tolower(sorted[j].name[0]) == tolower(sorted[j + 1].name[0])) {
                for (int k = 0; k < abs(strlen(sorted[j].name) - strlen(sorted[j+1].name)); k++) {
                    if (tolower(sorted[j].name[k]) > tolower(sorted[j + 1].name[k])) {
                        struct Drink temp = sorted[j];
                        sorted[j] = sorted[j+1];
                        sorted[j+1] = temp;
                    }
                }
            }
        }
    }
    printf("    Rb  Ime                           Cijena     Ocjena\n");
    printDivisionLine();
    for (int i = 0; i < numberOfDrinks; i++) {
        printMocktail(sorted[i], PRINT_OPTION_ALPHA, i + 1);
    }
    printDivisionLine();
}

void addMocktail() {
    int choice = 0;
    do {
        if (numberOfDrinks >= MAX_DRINKS) {
            printf(RED "Nije dozvoljen unos, postoji maksimalan broj recepata (%d).\n" RESET, MAX_DRINKS);
            return;
        }
        printf(PINK_PASTEL "Unos novog recepta:\n" RESET);
        printf(WHITE "Ime: ");
        scanString(mocktails[numberOfDrinks].name);
        printf("Opis: ");
        scanString(mocktails[numberOfDrinks].description);
        printf("Cijena: " RESET);
        while (!scanFloat(&mocktails[numberOfDrinks].price) || mocktails[numberOfDrinks].price < 0 || mocktails[numberOfDrinks].price >= 10000000.0) {
            printf(RED "Broj mora biti veci ili jednak od nule i razumne vrijednosti.\n" RESET);
            printf(WHITE "Cijena: " RESET);
        };
        printf(WHITE "Ocjena: " RESET);
        while (!scanFloat(&mocktails[numberOfDrinks].rating) || !(mocktails[numberOfDrinks].rating >= 1 && mocktails[numberOfDrinks].rating <= 10)) {
            printf(RED "Vrijednost mora biti broj u rasponu od jedan do deset.\n" RESET);
            printf(WHITE "Ocjena: " RESET);
        };
        printf("\nUpisi " PINK_LIGHT "0" RESET " za dodavanje jos jednog recepta: ");
        if (!scanInt(&choice)) {
            choice = 1;
        }
        numberOfDrinks += 1;
    }
    while (choice == 0);
}

void searchByName()  {
    char seekName[50];
    int recipe = 0;
    int found = 0;
    printf(PINK_PASTEL "Upisi naziv moktela koji zelis naci: " RESET);
    scanString(seekName);
    int lengthOfName = strlen(seekName);
    printf("\nMokteli sa tim imenom:\n");
    for (int i = 0; i < numberOfDrinks; i++) {
        int length = 0;
        int lengthOfMocktailName = strlen(mocktails[i].name);
        for (int j = 0; j < lengthOfMocktailName; j++) {
            if (tolower(mocktails[i].name[j]) == tolower(seekName[length])) {
                for (int k = j; k < j + lengthOfName; k++) {
                    if (tolower(mocktails[i].name[k]) == tolower(seekName[length])) {
                        length++;
                    }
                    else {
                        length = 0;
                        break;
                    }
                    if (length == lengthOfName) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
        if (found) {
            recipe++;
            printMocktail(mocktails[i],PRINT_OPTION_VERBOSE,-1);
            printf("\n");
        }
        found = 0;
    }
    if (recipe == 0) {
        printf(RED "\tNema recept sa tim imenom.\n" RESET);
    }
}

void sortByPrice() {
    struct Drink sorted[numberOfDrinks];
    for (int i = 0; i < numberOfDrinks; i++) {
        sorted[i] = mocktails[i];
    }
    for (int i = 0; i < numberOfDrinks; i++) {
        for (int j = 0; j < numberOfDrinks - 1 - i; j++) {
            if (sorted[j].price < sorted[j+1].price) {
                struct Drink temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    int choice;
    printf(PINK_PASTEL "Sortirani mokteli po cijeni:\n" RESET);
    printf(WHITE "\t 1 - silazno\n");
    printf("\t 2 - uzlazno\n");\
    printf("\t 3 - najskuplji\n");
    printf("\t 4 - najjeftiniji\n" RESET);
    printf("Upisi opciju: ");
    scanInt(&choice);
    printf("\n");
    switch (choice) {
        case 1:
            printf( PINK_LIGHT "Mokteli sortirani silazno:\n" RESET);
            printDivisionLine ();
            for (int i = 0; i < numberOfDrinks; i++) {
                printMocktail(sorted[i],PRINT_OPTION_ALPHA, i + 1);
            }
            printDivisionLine ();
            break;
        case 2:
            printf(PINK_LIGHT "Mokteli sortirani uzlazno:\n" RESET);
            printDivisionLine ();
            for (int i = numberOfDrinks - 1; i >= 0; i--) {
                printMocktail(sorted[i], PRINT_OPTION_ALPHA, numberOfDrinks - i);
            }
            printDivisionLine ();
            break;
        case 3:
            printf(PINK_LIGHT "Najskuplji moktel:\n" RESET);
            printMocktail(sorted[0], PRINT_OPTION_ALPHA, -1);
            printf("\n");
            break;
        case 4:
            printf(PINK_LIGHT"Najjeftiniji moktel:\n" RESET);
            printMocktail(sorted[numberOfDrinks - 1], PRINT_OPTION_ALPHA, -1);
            printf("\n");
            break;
        default:
            printf(RED "Nije upisana ispravna opcija.\n" RESET);
    }
}

void sortByRating() {
    struct Drink sorted[numberOfDrinks];
    for (int i = 0; i < numberOfDrinks; i++) {
        sorted[i] = mocktails[i];
    }
    for (int i = 0; i < numberOfDrinks; i++) {
        for (int j = 0; j < numberOfDrinks - 1 - i; j++) {
            if (sorted[j].rating < sorted[j+1].rating) {
                struct Drink temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    int choice;
    printf(PINK_PASTEL "Sortirani mokteli po ocjeni:\n" RESET);
    printf(WHITE "\t 1 - silazno\n");
    printf("\t 2 - uzlazno\n" RESET);
    printf("Upisi opciju: ");
    scanInt(&choice);
    if (choice == 1) {
        printf(PINK_LIGHT "\nMokteli sortirani silazno:\n" RESET);
        printDivisionLine ();
        for (int i = 0; i < numberOfDrinks; i++) {
            printMocktail(sorted[i], PRINT_OPTION_ALPHA, i + 1);
        }
        printDivisionLine ();
    }
    else {
        printf(PINK_LIGHT"\nMokteli sortirani uzlazno:\n" RESET);
        printDivisionLine ();
        for (int i = numberOfDrinks - 1; i >= 0; i--) {
            printMocktail(sorted[i], PRINT_OPTION_ALPHA, numberOfDrinks - i);
        }
        printDivisionLine ();
    }
}

void deleteMocktail() {
    int choice;
    char confirmation;
    printf(PINK_PASTEL "Upisi redni broj moktela za brisanje:\n" RESET);
    for (int i = 0; i < numberOfDrinks; i++) {
        printMocktail(mocktails[i], PRINT_OPTION_DELETE, i);
    }
    printf("Upisi: ");
    while (!scanInt(&choice) || choice < 1 || choice > numberOfDrinks) {
        printf(RED "Moktel ne postoji.\n" RESET);
        printf("Upisi: ");
    }
    printf(PINK_LIGHT "Brisanje moktela %d:" PINK_DIRTY " %s\n" RESET,choice,mocktails[choice - 1].name);
    printf("Upisi potvrdu [" PINK_NEON "y" RESET "/" PINK_NEON "n" RESET "]: ");
    if (!scanChar(&confirmation)) {
        confirmation = 'n';
    }
    if (tolower(confirmation) == 'y') {
        for (int i = choice - 1; i < numberOfDrinks; i++) {
            mocktails[i] = mocktails[i + 1];
        }
        numberOfDrinks = numberOfDrinks - 1;
        printf(GREEN "Moktel uspjesno izbrisan.\n" RESET);
    }
    else {
        printf(RED "Nije izbrisan.\n");
    }
}

int main() {
    int choice;
    printf(WHITE "\tDobrodosli u " PINK_NEON "MocktailCraft" WHITE" aplikaciju !\n");
    printf(PINK_DIRTY "\t\tby-dodo (Dora Hlevnjak)! <3\n");
    do {
        printf(PINK_PASTEL "\nGlavni izbornik:\n" WHITE);
        printf(WHITE "\t1 - listaj moktele\n");
        printf("\t2 - dodaj\n");
        printf("\t3 - obrisi\n");
        printf("\t4 - ispis po nazivu\n");
        printf("\t5 - ispis po cijeni\n");
        printf("\t6 - ispis po ocjeni\n");
        printf("\t7 - izlaz\n" RESET);
        printf("Upisi opciju: ");

        if (!scanInt(&choice)) {
            choice = 0;
        }
        printf("\n");
        if (numberOfDrinks == 0 && choice != 2 && choice != 7) {
            printf(RED "Trenutno nema upisanih moktela.\n" RESET);
            continue;
        }
        switch (choice) {
            case 1:
                listAlphabetically();
                break;
            case 2:
                addMocktail();
                break;
            case 3:
                deleteMocktail();
                break;
            case 4:
                searchByName();
                break;
            case 5:
                sortByPrice();
                break;
            case 6:
                sortByRating();
                break;
            case 7:
                printf(PINK_NEON "Dovidenja!" RESET);
                exit(0);
            default:
                printf(RED "Nije upisana ispravna opcija.\n" PINK_PASTEL "Pokusaj ponovo <3\n");
                break;
        }
    }
    while (true);
    return 0;
}
