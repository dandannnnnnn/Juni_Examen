//Encrypteren / decrypteren mbv freq.analyse

#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h> // Voor INT_MIN

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

// FREQUENTIEANALYSE
// Functie om letterfrequenties te tellen (case-insensitief)
void calculate_frequencies(const char *text, int frequencies[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = 0;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            frequencies[toupper(text[i]) - 'A']++;
        }
    }
}

int main() {
    char ciphertext[MAX_TEXT_LEN];
    char decrypted_text[MAX_TEXT_LEN];
    int frequencies[ALPHABET_SIZE];
    int max_freq = INT_MIN;
    int most_frequent_char_index = -1; // Index in alfabet (0=A, 1=B, ...)
    int probable_key;

    // Meest voorkomende letter in Engels (0-gebaseerde index: 'E' - 'A')
    const int MOST_COMMON_ENGLISH_LETTER_INDEX = 'E' - 'A';
    // Voor Nederlands zou je dit kunnen aanpassen of een lijst proberen
    // const int MOST_COMMON_DUTCH_LETTER_INDEX_E = 'E' - 'A';
    // const int MOST_COMMON_DUTCH_LETTER_INDEX_N = 'N' - 'A';


    printf("Voer de versleutelde tekst (Caesar cipher) in voor frequentieanalyse: ");
    if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) {
        fprintf(stderr, "Fout bij lezen van tekst.\n");
        return 1;
    }
    remove_newline(ciphertext);

    calculate_frequencies(ciphertext, frequencies);

    printf("\nLetterfrequenties in ciphertext:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] > 0) {
            printf("%c: %d\n", 'A' + i, frequencies[i]);
        }
        if (frequencies[i] > max_freq) {
            max_freq = frequencies[i];
            most_frequent_char_index = i;
        }
    }

    if (most_frequent_char_index == -1) {
        printf("Geen letters gevonden in de tekst.\n");
        return 1;
    }

    printf("\nMeest voorkomende letter in ciphertext: %c\n", 'A' + most_frequent_char_index);

    // Bereken de waarschijnlijke sleutel, aannemend dat de meest voorkomende
    // ciphertext letter overeenkomt met MOST_COMMON_ENGLISH_LETTER_INDEX ('E')
    probable_key = (most_frequent_char_index - MOST_COMMON_ENGLISH_LETTER_INDEX + ALPHABET_SIZE) % ALPHABET_SIZE;

    printf("Aangenomen sleutel (gebaseerd op '%c' -> 'E'): %d\n", 'A' + most_frequent_char_index, probable_key);

    caesar_decrypt(ciphertext, probable_key, decrypted_text);
    printf("Poging tot decryptie met deze sleutel: %s\n", decrypted_text);

    printf("\nOpmerking: Als dit niet de juiste tekst is, probeer dan aan te nemen dat\n");
    printf("de meest voorkomende letter overeenkomt met een andere vaak voorkomende letter\n");
    printf("(bijv. T, A, O, N, I, S, H, R) of gebruik brute-force.\n");

    return 0;
}