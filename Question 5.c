#include <stdio.h>
#include <string.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);
void toggleBits(char *c);
void reverseString(char str[]);

int main() {
    char message[200];
    int choice;

    do {
        printf("\n========== TCS Secure Message System ==========\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("==============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("\nEnter message to encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0'; // remove newline

                encodeMessage(message);
                printf("Encoded Message: %s\n", message);
                break;

            case 2:
                printf("\nEnter message to decode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';

                decodeMessage(message);
                printf("Decoded Message: %s\n", message);
                break;

            case 3:
                printf("Exiting system... Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}

void toggleBits(char *c) {
    *c = *c ^ (1 << 1); 
    *c = *c ^ (1 << 4);
}

void reverseString(char str[]) {
    int len = strlen(str);
    int i;
    for ( i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void encodeMessage(char message[]) {
    reverseString(message);
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        toggleBits(&message[i]);
    }
}

void decodeMessage(char message[]) {
	int i;
    for ( i = 0; message[i] != '\0'; i++) {
        toggleBits(&message[i]);
    }
    reverseString(message);
}

