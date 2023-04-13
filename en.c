#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LEN 100
#define MAX_BUFFER_SIZE 1024
#define ENCRYPTION_KEY 3

void encrypt(FILE *input_file, FILE *output_file)
{
    char buffer[MAX_BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, input_file)) > 0)
    {
        for (size_t i = 0; i < bytes_read; i++)
        {
            char encrypted_byte = buffer[i] + ENCRYPTION_KEY;
            fwrite(&encrypted_byte, sizeof(char), 1, output_file);
        }
    }
}

void decrypt(FILE *input_file, FILE *output_file)
{
    char buffer[MAX_BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, input_file)) > 0)
    {
        for (size_t i = 0; i < bytes_read; i++)
        {
            char decrypted_byte = buffer[i] - ENCRYPTION_KEY;
            fwrite(&decrypted_byte, sizeof(char), 1, output_file);
        }
    }
}

int main()
{
    char input_filename[MAX_FILENAME_LEN];
    char output_filename[MAX_FILENAME_LEN];
    printf("Enter input file name: ");
    scanf("%s", input_filename);
    printf("Enter output file name: ");
    scanf("%s", output_filename);
    FILE *input_file = fopen(input_filename, "rb");
    FILE *output_file = fopen(output_filename, "wb");
    if (input_file == NULL || output_file == NULL)
    {
        printf("Error: Failed to open file\n");
        exit(1);
    }
    int choice;
    printf("Enter 1 to encrypt or 2 to decrypt: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        encrypt(input_file, output_file);
        break;
    case 2:
        decrypt(input_file, output_file);
        break;
    default:
        printf("Invalid choice\n");
        exit(1);
    }
    fclose(input_file);
    fclose(output_file);
    printf("Done.\n");
    return 0;
}
