#include <stdio.h>

#define MAX_TRANSACTIONS 5
#define MAX_ATTEMPTS 3

int main() {
    int pin = 1234;
    int enteredPin;
    int attempts = 0;

    int balance = 5000;
    int choice;

    int transactionCount = 0;
    int miniStatement[MAX_TRANSACTIONS];

    printf("=========================================\n");
    printf("         MINI ATM SYSTEM (C)\n");
    printf("=========================================\n");

    /* PIN VERIFICATION */
    while (attempts < MAX_ATTEMPTS) {
        printf("Enter your PIN: ");
        scanf("%d", &enteredPin);

        if (enteredPin == pin) {
            printf("PIN verified successfully.\n");
            break;
        } else {
            attempts++;
            printf("Incorrect PIN. Attempts left: %d\n", MAX_ATTEMPTS - attempts);
        }
    }

    if (attempts == MAX_ATTEMPTS) {
        printf("Account locked due to multiple incorrect attempts.\n");
        return 0;
    }

    /* MAIN MENU */
    while (1) {
        printf("\n=========== ATM MENU ===========\n");
        printf("1. Balance Inquiry\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Change PIN\n");
        printf("5. Mini Statement\n");
        printf("6. Exit\n");
        printf("================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Current Balance: %d\n", balance);
                break;

            case 2: {
                int amount;
                printf("Enter amount to deposit: ");
                scanf("%d", &amount);

                if (amount <= 0) {
                    printf("Invalid amount.\n");
                    break;
                }

                balance += amount;
                miniStatement[transactionCount % MAX_TRANSACTIONS] = amount;
                transactionCount++;

                printf("Deposit successful.\n");
                break;
            }

            case 3: {
                int amount;
                printf("Enter amount to withdraw: ");
                scanf("%d", &amount);

                if (amount <= 0) {
                    printf("Invalid amount.\n");
                    break;
                }

                if (amount > balance) {
                    printf("Insufficient balance.\n");
                    break;
                }

                balance -= amount;
                miniStatement[transactionCount % MAX_TRANSACTIONS] = -amount;
                transactionCount++;

                printf("Withdrawal successful.\n");
                break;
            }

            case 4: {
                int newPin;
                printf("Enter new PIN: ");
                scanf("%d", &newPin);

                if (newPin == pin) {
                    printf("New PIN cannot be the same as old PIN.\n");
                    break;
                }

                pin = newPin;
                printf("PIN changed successfully.\n");
                break;
            }

            case 5: {
                int count, i;

                printf("\nLast Transactions:\n");

                if (transactionCount == 0) {
                    printf("No transactions available.\n");
                    break;
                }

                count = transactionCount < MAX_TRANSACTIONS ?
                        transactionCount : MAX_TRANSACTIONS;

                for (i = 0; i < count; i++) {
                    int index = (transactionCount - 1 - i) % MAX_TRANSACTIONS;
                    if (index < 0)
                        index += MAX_TRANSACTIONS;

                    if (miniStatement[index] > 0)
                        printf("Deposit    : +%d\n", miniStatement[index]);
                    else
                        printf("Withdrawal : %d\n", miniStatement[index]);
                }

                break;
            }

            case 6:
                printf("Thank you for using the ATM system.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
