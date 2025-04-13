#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DRINKS 15
#define PRINT_OPTION_VERBOSE 0
#define PRINT_OPTION_DELETE 1
#define PRINT_OPTION_ALPHA 2

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[38;5;227m"
#define BLUE    "\033[34m"
#define MAGENTA1 "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[0m"
#define PINK    "\033[38;5;198m"
#define MAGENTA "\033[38;5;13m"


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

void printDivisionLine () {
    printf("   ______________________________________________________\n");
}
bool scanInt (int* result) {
    char buffer[100], leftover;
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    int parsedCount = sscanf(buffer, "%d %c", result, &leftover);
    if (parsedCount != 1 || strspn(buffer, "-0123456789 \n") != strlen(buffer)) {
        return false;
    }
    return true;
}

bool scanFloat (float* result) {
    char buffer[100], leftover;
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    int parsedCount = sscanf(buffer, "%f %c", result, &leftover);
    if (parsedCount != 1 || strspn(buffer, "-0123456789 .\n") != strlen(buffer)) {
        return false;
    }
    return true;
}

bool scanChar (char* result) {
    char buffer[100], leftover;
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    int parsedCount = sscanf(buffer, "%c %c", result, &leftover);
    if (parsedCount != 1) {
        return false;
    }
    return true;
}

void scanString (char* result) {
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
                printf("%2d: ",index);
            }
            printf("%-25s%10.2f €\t%4.1f/10\n", mocktail.name, mocktail.price, mocktail.rating);
            break;
        case PRINT_OPTION_VERBOSE:
            printf("\time: %s\n", mocktail.name);
            printf("\topis: %s\n", mocktail.description);
            printf("\tcijena: %.2f €\n", mocktail.price);
            printf("\tocjena: %.2f\n", mocktail.rating);
            break;
        // case PRINT_OPTION_PRICE:
        //     printf("\t");
        //     if (index > 0) {
        //         printf("%d:\t", index);
        //     }
        //     printf("%-25s%.2f €\n", mocktail.name, mocktail.price);
        //     break;
        // case PRINT_OPTION_RATING:
        //     printf("\t");
        //     if (index > 0) {
        //         printf("%d:", index);
        //     }
        //     printf("\t%-25s%.1f/10\n", mocktail.name, mocktail.rating);
        //     break;
        case PRINT_OPTION_DELETE:
            printf("\t%d:\t%s\n ",index + 1, mocktail.name);
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
    printf("    Rb      Ime                       Cijena     Ocjena\n");
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
            printf("Nije dozvoljen unos, postoji maksimalan broj recepata (%d).\n", MAX_DRINKS);
            return;
        }
        printf("Unos novog recepta:\n");
        printf("Ime: ");
        scanString(mocktails[numberOfDrinks].name);
        printf("Opis: ");
        scanString(mocktails[numberOfDrinks].description);
        printf("Cijena: ");
        while (!scanFloat(&mocktails[numberOfDrinks].price) || mocktails[numberOfDrinks].price < 0 || mocktails[numberOfDrinks].price >= 10000000.0) {
            printf("Broj mora biti veci ili jednak od nule i razumne vrijednosti.\n");
            printf("Cijena: ");
        };
        printf("Ocjena: ");
        while (!scanFloat(&mocktails[numberOfDrinks].rating) || !(mocktails[numberOfDrinks].rating >= 1 && mocktails[numberOfDrinks].rating <= 10)) {
            printf("Vrijednost mora biti broj u rasponu od jedan do deset.\n");
            printf("Ocjena: ");
        };
        printf("\nUpisi 0 za dodavanje jos jednog recepta: ");
        if (!scanInt(&choice)) {
            choice = 1;
        }
        numberOfDrinks += 1;
    }
    while (choice == 0);
}

void searchByName ()  {
    char seekName[50];
    int recipe = 0;
    int found = 0;
    printf("Upisi naziv moktela koji zelis naci: ");
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
        printf("\tnema recept sa tim imenom.\n");
    }
}

void sortByPrice () {
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
    printf("Sortirani mokteli po cijeni:\n");
    printf("\t 1 - od vece prema manjoj\n");
    printf("\t 2 - od manje prema vecoj\n");\
    printf("\t 3 - najskuplji\n");
    printf("\t 4 - najjeftiniji\n");
    printf("Unesi opciju: ");
    scanInt(&choice);
    switch (choice) {
        case 1:
            printf("Mokteli sortirani od najvece cijene prema najmanjoj :\n");
            printDivisionLine ();
            for (int i = 0; i < numberOfDrinks; i++) {
                printMocktail(sorted[i],PRINT_OPTION_ALPHA, i + 1);
            }
            printDivisionLine ();
            break;
        case 2:
            printf("Mokteli sortirani od najmanje cijene prema najvecoj :\n");
            printDivisionLine ();
            for (int i = numberOfDrinks - 1; i >= 0; i--) {
                printMocktail(sorted[i], PRINT_OPTION_ALPHA, numberOfDrinks - i);
            }
            printDivisionLine ();
            break;
        case 3:
            printf("Najskuplji moktel:\n");
            printMocktail(sorted[0], PRINT_OPTION_ALPHA, -1);
            printf("\n");
            break;
        case 4:
            printf("Najjeftiniji moktel:\n");
            printMocktail(sorted[numberOfDrinks - 1], PRINT_OPTION_ALPHA, -1);
            printf("\n");
            break;
        default:
            printf("Nije upisana ispravna opcija.\n");
    }
}

void sortByRating () {
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
    printf("Sortirani mokteli po ocjeni:\n");
    printf("\t 1 - silazno\n");
    printf("\t 2 - uzlazno\n");
    printf("Upisi opciju: ");
    scanInt(&choice);
    if (choice == 1) {
        printf("\nMokteli sortirani silazno:\n");
        printDivisionLine ();
        for (int i = 0; i < numberOfDrinks; i++) {
            printMocktail(sorted[i], PRINT_OPTION_ALPHA, i + 1);
        }
        printDivisionLine ();
    }
    else {
        printf("\nMokteli sortirani uzlazno:\n");
        printDivisionLine ();
        for (int i = numberOfDrinks - 1; i >= 0; i--) {
            printMocktail(sorted[i], PRINT_OPTION_ALPHA, numberOfDrinks - i);
        }
        printDivisionLine ();
    }
}

void deleteMocktail () {
    int choice;
    char confrimation;
    printf("Upisi redni broj moktela za brisanje:\n");
    for (int i = 0; i < numberOfDrinks; i++) {
        printMocktail(mocktails[i], PRINT_OPTION_DELETE, i);
    }
    printf("Upisi: ");
    while (!scanInt(&choice) || choice < 1 || choice > numberOfDrinks) {
        printf("Moktel ne postoji.\n");
        printf("Upisi: ");
    }
    printf("Brisanje moktela %d: '%s'\n",choice,mocktails[choice - 1].name);

    printf("Upisi potvrdu [y/n]: ");
    if (!scanChar(&confrimation)) {
        confrimation = 'n';
    }
    if (confrimation == 'y') {
        for (int i = choice - 1; i < numberOfDrinks; i++) {
            mocktails[i] = mocktails[i + 1];
        }
        numberOfDrinks = numberOfDrinks - 1;
        printf("Moktel uspjesno izbrisan.\n");
    }
    else {
        printf("Nije izbrisan.\n");
    }
}

int main() {
    int choice;
    printf("\tDobrodosli u " PINK "MocktailCraft" WHITE" aplikaciju !\n");
    printf( MAGENTA "\t\tby-dora (Dora Hlevnjak)! <3\n");

    do {
        printf(CYAN "\nGlavni izbornik:\n" WHITE);
        printf(GREEN "\t1 - dodavanje\n");
        printf(BLUE "\t2 - lista moktela\n");
        printf(RED "\t3 - ispis po nazivu\n");
        printf(YELLOW "\t4 - ispis po cijeni\n");
        printf(MAGENTA1 "\t5 - ispis po ocjeni\n");
        printf(WHITE "\t6 - brisanje\n");
        printf("\t7 - izlaz\n");
        printf("Upisi opciju: ");

        if (!scanInt(&choice)) {
            choice = 0;
        }
        printf("\n");
        if (numberOfDrinks == 0 && choice != 1 && choice != 7) {
            printf("Trenutno nema upisanih moktela.\n");
            continue;
        }
        switch (choice) {
            case 1:
                addMocktail();
                break;
            case 2:
                listAlphabetically();
                break;
            case 3:
                searchByName();
                break;
            case 4:
                sortByPrice();
                break;
            case 5:
                sortByRating();
                break;
            case 6:
                deleteMocktail();
                break;
            case 7:
                printf("Dovidenja!");
                exit(0);
            default:
                printf("Nije upisana ispravna opcija.\nPokusaj ponovo <3\n");
                break;
        }
    }
    while (true);
    return 0;
}
