//Encrypteren en Decrypteren mbv CaesarCijfer
//compile manual on vscode terminal: gcc CaesarCijfer.c -o CaesarCijfer
//runnen na manuele compile: ./Caesarcijfer

#include <stdio.h>
#include <string.h>
#include <ctype.h> // Voor isalpha(), isupper(), islower()

#define MAX_TEXT_LEN 256

// Functie om de newline karakter van fgets input te verwijderen
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// Functie voor Caesar encryptie
void caesar_encrypt(char *plaintext, int key, char *ciphertext) {
    int i;
    char ch;

    for (i = 0; plaintext[i] != '\0'; ++i) {
        ch = plaintext[i];

        if (isalpha(ch)) { // Controleer of het een alfabetisch teken is
            char base = isupper(ch) ? 'A' : 'a'; // Bepaal basis: 'A' voor hoofdletters, 'a' voor kleine letters
            // Verschuif en zorg voor "wrap-around" (Z -> A, etc.)
            ciphertext[i] = (ch - base + key) % 26 + base;
        } else {
            ciphertext[i] = ch; // Niet-alfabetische tekens blijven ongewijzigd
        }
    }
    ciphertext[i] = '\0'; // Null-terminator toevoegen
}

// Functie voor Caesar decryptie
void caesar_decrypt(char *ciphertext, int key, char *decrypted_text) {
    int i;
    char ch;

    for (i = 0; ciphertext[i] != '\0'; ++i) {
        ch = ciphertext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            // Verschuif terug en zorg voor "wrap-around" (A -> Z, etc.)
            // De +26 is om te zorgen dat het resultaat positief is voordat modulo wordt toegepast
            decrypted_text[i] = (ch - base - key + 26) % 26 + base;
        } else {
            decrypted_text[i] = ch;
        }
    }
    decrypted_text[i] = '\0';
}

int main() {
    char plaintext[MAX_TEXT_LEN];
    char ciphertext[MAX_TEXT_LEN];
    char decrypted_text[MAX_TEXT_LEN];
    int key;

    // 1. Vraag om de te versleutelen tekst
    printf("Voer de tekst in om te versleutelen: ");
    if (fgets(plaintext, sizeof(plaintext), stdin) == NULL) {
        fprintf(stderr, "Fout bij lezen van tekst.\n");
        return 1;
    }
    remove_newline(plaintext);

    // 2. Vraag om de sleutel (verschuiving)
    printf("Voer de sleutel in (een getal, bijv. 3): ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Ongeldige sleutel ingevoerd.\n");
        // Verbruik resterende input om problemen met volgende fgets te voorkomen
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    // Verbruik de newline die scanf achterlaat
    int c;
    while ((c = getchar()) != '\n' && c != EOF);


    // Normaliseer de sleutel om binnen het bereik 0-25 te vallen
    // Hoewel de modulo operator in encrypt/decrypt dit al aan zou kunnen,
    // is het expliciet maken soms duidelijker.
    key = key % 26;
    if (key < 0) { // Zorg voor positieve sleutel voor consistentie
        key += 26;
    }

    printf("Originele tekst: %s\n", plaintext);
    printf("Gebruikte sleutel: %d\n", key);

    // 3. Encrypteer de tekst
    caesar_encrypt(plaintext, key, ciphertext);
    printf("Versleutelde tekst: %s\n", ciphertext);

    // 4. Decrypteer de tekst
    caesar_decrypt(ciphertext, key, decrypted_text);
    printf("Ontsleutelde tekst: %s\n", decrypted_text);

    return 0;
}
