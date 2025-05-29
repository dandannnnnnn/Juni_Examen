//Encrypt/Decrypt mbv brute force

#include <ctype.h> // Voor isalpha(), isupper(), islower()
#include <stdio.h>
#include <string.h>

// Functie voor Caesar decryptie (uit vorig voorbeeld)
void caesar_decrypt(const char *ciphertext, int key, char *decrypted_text) {
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
            decrypted_text[i] = ch; // Niet-alfabetische tekens blijven ongewijzigd
        }
    }
    decrypted_text[i] = '\0';
}

// Functie om de newline karakter van fgets input te verwijderen (handig)
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}
//BRUTE  FORCE VANAF HIER
void caesar_decrypt(const char *ciphertext, int key, char *decrypted_text) {
    int i;
    char ch;

    for (i = 0; ciphertext[i] != '\0'; ++i) {
        ch = ciphertext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            decrypted_text[i] = (ch - base - key + 26) % 26 + base;
        } else {
            decrypted_text[i] = ch;
        }
    }
    decrypted_text[i] = '\0';
}

void remove_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}
// --- Einde gekopieerde functies ---


int main() {
    char ciphertext[MAX_TEXT_LEN];
    char attempt[MAX_TEXT_LEN];
    int key;

    printf("Voer de versleutelde tekst (Caesar cipher) in: ");
    if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) {
        fprintf(stderr, "Fout bij lezen van tekst.\n");
        return 1;
    }
    remove_newline(ciphertext);

    printf("\nBrute-force pogingen:\n");
    for (key = 0; key < 26; key++) {
        caesar_decrypt(ciphertext, key, attempt);
        printf("Sleutel %2d: %s\n", key, attempt);
    }

    printf("\nZoek in de bovenstaande lijst naar de leesbare tekst.\n");

    return 0;
}