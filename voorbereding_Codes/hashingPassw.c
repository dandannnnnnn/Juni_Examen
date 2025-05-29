//Code vraagt username en wachtwoord. 
//Wachtwoord hashen met SHA-256
//Gegevens worden opgeslagen in log file.
//SSL install Ubuntu (al geïnstalleerd): sudo apt-get install libssl-dev

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h> // Voor SHA256

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define LOG_FILE_NAME "credentials.log"

// Functie om de newline karakter van fgets input te verwijderen
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    unsigned char hash_binary[SHA256_DIGEST_LENGTH]; // SHA256 produceert 32 bytes
    char hash_hex_string[SHA256_DIGEST_LENGTH * 2 + 1]; // 2 hex chars per byte + null terminator
    FILE *log_file;

    // 1. Vraag gebruikersnaam
    printf("Gebruikersnaam: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Fout bij lezen gebruikersnaam.\n");
        return 1;
    }
    remove_newline(username);

// 2. Vraag wachtwoord
    // LET OP: Wachtwoord wordt hier ge-echood naar het scherm.
    // In een echte applicatie zou je dit moeten verbergen.
    printf("Wachtwoord: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Fout bij lezen wachtwoord.\n");
        return 1;
    }
    remove_newline(password);

    // 3. Hash het wachtwoord met SHA256
    SHA256_CTX sha256_context;
    SHA256_Init(&sha256_context);
    SHA256_Update(&sha256_context, password, strlen(password));
    SHA256_Final(hash_binary, &sha256_context);

    // Converteer binaire hash naar hexadecimale string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_hex_string[i * 2], "%02x", hash_binary[i]);
    }
    hash_hex_string[SHA256_DIGEST_LENGTH * 2] = '\0'; // Null-terminator

    printf("Gehasht wachtwoord (SHA256): %s\n", hash_hex_string);

    // 4. Sla gebruikersnaam en gehasht wachtwoord op in log file
    log_file = fopen(LOG_FILE_NAME, "a"); // "a" voor append (toevoegen aan einde)
    if (log_file == NULL) {
        perror("Fout bij openen logbestand");
        return 1;
    }

    fprintf(log_file, "Gebruiker: %s, Gehasht Wachtwoord (SHA256): %s\n", username, hash_hex_string);
    fclose(log_file);

    printf("Gegevens opgeslagen in %s\n", LOG_FILE_NAME);

    return 0;
}

//Voorbeeld output: 
// Gebruiker: testuser, Gehasht Wachtwoord (SHA256): 9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08
// Gebruiker: alice, Gehasht Wachtwoord (SHA256): 4b2a1a31b2372cde45df9751783a6915624e1e9cdef09507789e9f40311f2319