#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define drinkLimit 15

struct Drink {
    char name[50];
    char description[100];
    float price;
    int rating;
};

struct Drink mocktails[drinkLimit] = {
    {
        "Citrus Burst",
        "A zesty mix of orange, lime, and soda water.",
        4.99,
        5
    },
    {
        "Berry Breeze",
        "A refreshing blend of strawberries, blueberries, and mint.",
        5.49,
        4
    },
    {
        "Tropical Twist",
        "Pineapple, coconut milk, and mango for a beachy vibe.",
        5.99,
        5
    },
    {
        "Minty Melon",
        "Watermelon juice with a hint of mint and lemon.",
        4.79,
        4
    },
    {
        "Ginger Glow",
        "Spicy ginger beer with lime and cucumber slices.",
        5.25,
        5
    }
};

int numberOfDrinks = 5;

void addMocktail() {
    int choice = 0;
    do {
        if (numberOfDrinks >= drinkLimit) {
            printf("Postoji maksimalan broj recepata moktela.\n");
            return;
        }
        gets(mocktails[numberOfDrinks].name);
        printf("Upisi naziv novog moktela: \n");
        gets(mocktails[numberOfDrinks].name);
        printf("Upisi opis novog moktela: \n");
        gets(mocktails[numberOfDrinks].description);
        printf("Upisi cijenu novog moktela: \n");
        scanf("%f",&mocktails[numberOfDrinks].price);
        printf("Upisi ocjenu novog moktela: \n");
        scanf("%d",&mocktails[numberOfDrinks].rating);
        printf("Upisi 0 za dodavanje novog recepta: ");
        scanf("%d",&choice);
        numberOfDrinks += 1;
    } while (choice == 0);
}

void listByName ()  {
    char seekName[50];
    int recipe = 0;
    int found = 0;
    gets(seekName);  // cleara enter od proslog scanfa, bez ovog ne radi :3
    printf("Upisi naziv moktela koji zelis naci: \n");
    gets(seekName);  // zapravo uzima string
    int lengthOfName = strlen(seekName);
    printf("Mokteli sa tim imenom:\n");
    for (int i = 0; i < numberOfDrinks; i++) {
        int length = 0;
        int lengthOfMocktailName = strlen(mocktails[i].name);
        for (int j = 0; j < lengthOfMocktailName; j++) {
            if (tolower(mocktails[i].name[j]) == tolower(seekName[length])) {
                for (int k = j; k < j + lengthOfName; k++) {
                    if (tolower(mocktails[i].name[k]) == tolower(seekName[length])) {
                        length++;
                    }else {
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
            printf("\time: %s\n", mocktails[i].name);
            printf("\topis: %s\n", mocktails[i].description);
            printf("\tcijena: %.2f €\n", mocktails[i].price);
            printf("\tocjena: %d\n", mocktails[i].rating);
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
    printf("\t 2 - od manje prema vecoj\n");
    scanf("%d", &choice);
    if (choice == 1) {
        for (int i = 0; i < numberOfDrinks; i++) {
            printf("\time: %s\n", sorted[i].name);
            printf("\topis: %s\n", sorted[i].description);
            printf("\tcijena: %.2f €\n", sorted[i].price);
            printf("\tocjena: %d\n", sorted[i].rating);
            printf("\n");
        }
    }else {
        for (int i = numberOfDrinks - 1; i >= 0; i--) {
            printf("\time: %s\n", sorted[i].name);
            printf("\topis: %s\n", sorted[i].description);
            printf("\tcijena: %.2f €\n", sorted[i].price);
            printf("\tocjena: %d\n", sorted[i].rating);
            printf("\n");
        }
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
    scanf("%d", &choice);
    if (choice == 1) {
        for (int i = 0; i < numberOfDrinks; i++) {
            printf("\time: %s\n", sorted[i].name);
            printf("\topis: %s\n", sorted[i].description);
            printf("\tcijena: %.2f €\n", sorted[i].price);
            printf("\tocjena: %d\n", sorted[i].rating);
            printf("\n");
        }
    }else {
        for (int i = numberOfDrinks - 1; i >= 0; i--) {
            printf("\time: %s\n", sorted[i].name);
            printf("\topis: %s\n", sorted[i].description);
            printf("\tcijena: %.2f €\n", sorted[i].price);
            printf("\tocjena: %d\n", sorted[i].rating);
            printf("\n");
        }
    }

}

int main() {
    int choice;
    printf("\t\tDobrodosli u MocktailCraft aplikaciju !\n");
    do {
        printf("Izaberi opciju:\n");
        printf("\t1 - dodavanje\n");
        printf("\t2 - ispis po nazivu\n");
        printf("\t3 - ispis po cijeni\n");
        printf("\t4 - ispis po ocjeni\n");
        printf("\t5 - izlaz\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addMocktail();
                break;
            case 2:
                listByName();
                break;
            case 3:
                sortByPrice();
                break;
            case 4:
                sortByRating();
                break;
            case 5:
                printf("Dovidenja!");
                exit(1);
            default:
                printf("Nije upisana ispravna opcija.\nPokusajte ponovo <3\n");
                break;
        }
    }while (choice != 5);
    return 0;
}
