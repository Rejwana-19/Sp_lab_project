#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUIZZES 10
#define MAX_QUESTIONS 10
#define MAX_USERS 100
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

// Structure definitions
typedef struct {
    char question[100];
    char options[4][50];
    int correct_option;
} Question;

typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

typedef struct {
    char quiz_name[MAX_NAME_LENGTH];
    Question questions[MAX_QUESTIONS];
    int num_questions;
} Quiz;

Quiz quizzes[MAX_QUIZZES];
int num_quizzes = 0;
User users[MAX_USERS];
int num_users = 0;

// Function prototypes
void adminMenu();
void userMenu();
void createQuiz();
void addUser();
void attemptQuiz(int quizIndex);
void loginAndAttemptQuiz();

int main() {
    int choice;
    do {
        printf("\nWelcome to Quiz Application\n");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);

    return 0;
}

void adminMenu() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("\nEnter Admin Username: ");
    scanf("%s", username);
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        int choice;
        do {
            printf("\nAdmin Menu\n");
            printf("1. Create Quiz\n");
            printf("2. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch(choice) {
                case 1:
                    createQuiz();
                    break;
                case 2:
                    printf("Logging out...\n");
                    break;
                default:
                    printf("Invalid choice! Please try again.\n");
            }
        } while(choice != 2);
    } else {
        printf("Authentication failed! Invalid username or password.\n");
    }
}

void userMenu() {
    int choice;
    do {
        printf("\nUser Menu\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addUser();
                break;
            case 2:
                loginAndAttemptQuiz();
                break;
            case 3:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
}

void createQuiz() {
    if (num_quizzes >= MAX_QUIZZES) {
        printf("Cannot create more quizzes. Maximum limit reached.\n");
        return;
    }

    Quiz newQuiz;
    printf("\nEnter Quiz Name: ");
    scanf("%s", newQuiz.quiz_name);

    int num_questions;
    printf("Enter number of questions for this quiz (max %d): ", MAX_QUESTIONS);
    scanf("%d", &num_questions);

    for (int i = 0; i < num_questions; i++) {
        printf("\nEnter Question %d: ", i+1);
        scanf("%s", newQuiz.questions[i].question);

        printf("Enter Option A: ");
        scanf("%s", newQuiz.questions[i].options[0]);

        printf("Enter Option B: ");
        scanf("%s", newQuiz.questions[i].options[1]);

        printf("Enter Option C: ");
        scanf("%s", newQuiz.questions[i].options[2]);

        printf("Enter Option D: ");
        scanf("%s", newQuiz.questions[i].options[3]);

        printf("Enter Correct Option (1 for A, 2 for B, 3 for C, 4 for D): ");
        scanf("%d", &newQuiz.questions[i].correct_option);
    }

    newQuiz.num_questions = num_questions;
    quizzes[num_quizzes] = newQuiz;
    num_quizzes++;

    printf("Quiz created successfully!\n");
}

void addUser() {
    if (num_users >= MAX_USERS) {
        printf("Cannot add more users. Maximum limit reached.\n");
        return;
    }

    printf("\nEnter Username: ");
    scanf("%s", users[num_users].username);

    printf("Enter Password: ");
    scanf("%s", users[num_users].password);

    num_users++;
    printf("User registered successfully!\n");
}

void attemptQuiz(int quizIndex) {
    if (quizIndex < 0 || quizIndex >= num_quizzes) {
        printf("Invalid quiz index.\n");
        return;
    }

    Quiz quiz = quizzes[quizIndex];
    int score = 0;

    printf("\n=== %s ===\n", quiz.quiz_name);

    for (int i = 0; i < quiz.num_questions; i++) {
        Question question = quiz.questions[i];

        printf("\nQuestion %d: %s\n", i + 1, question.question);
        printf("Options:\n");
        for (int j = 0; j < 4; j++) {
            printf("%c. %s\n", 'A' + j, question.options[j]);
        }

        char userAnswer;
        printf("Enter your answer (A/B/C/D): ");
        scanf(" %c", &userAnswer);  // Note the space before %c to consume the newline character

        int userOption = userAnswer - 'A' + 1;
        if (userOption >= 1 && userOption <= 4 && userOption == question.correct_option) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. Correct answer is %c.\n", 'A' + question.correct_option - 1);
        }
    }

    printf("\nQuiz completed!\n");
    printf("Your score: %d out of %d\n", score, quiz.num_questions);
}

void loginAndAttemptQuiz() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("\nEnter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    // Authentication
    int authenticated = 0;
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            authenticated = 1;
            break;
        }
    }

    if (authenticated) {
        printf("Login successful!\n");

        // After successful login, user can attempt a quiz
        int quizChoice;
        do {
            printf("\nAvailable Quizzes:\n");
            for (int i = 0; i < num_quizzes; i++) {
                printf("%d. %s\n", i + 1, quizzes[i].quiz_name);
            }
            printf("Enter the quiz number you want to attempt (or 0 to go back to main menu): ");
            scanf("%d", &quizChoice);

            if (quizChoice >= 1 && quizChoice <= num_quizzes) {
                attemptQuiz(quizChoice - 1); // Adjust index to match array indexing
            } else if (quizChoice != 0) {
                printf("Invalid quiz number. Please try again.\n");
            }
        } while (quizChoice != 0);
    } else {
        printf("Login failed! Invalid username or password.\n");
    }
}
