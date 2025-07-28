#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

// this colour coding info has been collected from online source
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[1;33m"      // for options
#define CYAN "\033[0;36m"        // for headings
#define G_BROWN "\033[38;5;136m" // for ascii art
#define RESET "\033[0m"

#define STONE 1
#define PAPER 2
#define SCISSOR 3

int get_valid_int(int min, int max) 
{
    // the idea of this validation function is taken from ChatGPT
    char input[1000000];
    int num;
    while (1) {
        printf("Enter your choice (%d to %d): ", min, max);
        if (fgets(input, sizeof(input), stdin)) {
            if (sscanf(input, "%d", &num) == 1) {
                if (num >= min && num <= max) {
                    return num;
                }
            }
        }
        printf(RED "Invalid input!" RESET " Please enter a valid choice.\n");
    }
}

int check_other_char_than_alphabets(char* str)
{
    // this function returns 1 if there is any character other than A -> Z and a -> z, and returns 0 if correct
    int check = 0;
    for(int i = 0; i < strlen(str) - 1; i++)
    {
        if(str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122);
        else 
        {
            check = 1;
            break;
        }
    }
    if(check == 0) return 0;
    else return 1;
}

void capitalize_first_word(char* str)
{
    // Example: ARJUN -> Arjun; radhika -> Radhika; naVNeet -> Navneet
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
    str[0] = toupper(str[0]);
}

void show_rules()
{
    printf("\n" YELLOW "--- RULES ---\n" RESET);
    printf("Stone 🪨 breaks Scissor ✂️ -> 🪨" GREEN "  STONE wins" RESET "\n");
    printf("Paper 📃 wraps Stone  🪨 -> 📃" GREEN "  PAPER wins" RESET "\n");
    printf("Scissor ✂️ cuts Paper 📃 -> ✂️" GREEN "  SCISSOR wins" RESET "\n");
    printf(YELLOW "Same choice? It's a draw!" RESET "\n\n");
}

void view_scoreboard()
{
    FILE *file = fopen("scoreboard.txt", "r");
    if (file == NULL)
    {
        printf(RED "\nNo Scoreboard found.\n" RESET);
        return;
    }
    char line[256];
    printf("\n" CYAN "--- SCOREBOARD ---\n" RESET);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s\n", line);
    }
    fclose(file);
    printf(CYAN "\n------------------\n" RESET);
}

void reset_scoreboard()
{
    FILE *file = fopen("scoreboard.txt", "w");
    time_t now = time(NULL);
    fprintf(file, "Date: %s", ctime(&now));
    if (file == NULL)
        printf(RED "No game is still played!!\nOr, the scoreboard.txt file you are looking to reset is not found. Play a new game for a scoreboard." RESET);
    else{
        fprintf(file, YELLOW "Scoreboard reset done.\n" RESET);
        fclose(file);
    }
}

void update_scoreboard_1on1(int player1_score, int player2_score, char player1[], char player2[])
{
    FILE *file = fopen("scoreboard.txt", "a");
    time_t now = time(NULL);
    fprintf(file, "Date: %s", ctime(&now));
    if (player1_score > player2_score)
        fprintf(file, "%s: %d | %s: %d | Result: >> %s WON 🏆    >> %s LOST 🤡\n", player1, player1_score, player2, player2_score, player1, player2);
    else if (player1_score < player2_score)
        fprintf(file, "%s: %d | %s: %d | Result: >> %s LOST 🤡    >> %s WON 🏆\n", player1, player1_score, player2, player2_score, player1, player2);
    else
        fprintf(file, "%s: %d | %s: %d | Result: >> DRAW 😑\n", player1, player1_score, player2, player2_score);
    fclose(file);
}

void update_scoreboard(char name[], int player_score, int comp_Score)
{
    FILE *file = fopen("scoreboard.txt", "a");
    time_t now = time(NULL);
    fprintf(file, "Date: %s", ctime(&now));
    if (player_score > comp_Score)
        fprintf(file, "Player: %s | You: %d | Comp: %d | Result: >> WON 🏆\n\n", name, player_score, comp_Score);
    else if (player_score < comp_Score)
        fprintf(file, "Player: %s | You: %d | Comp: %d | Result: >> LOST 🤡\n\n", name, player_score, comp_Score);
    else
        fprintf(file, "Player: %s | You: %d | Comp: %d | Result: >> DRAW 😑\n\n", name, player_score, comp_Score);
    fclose(file);
}

void display_ascii_for_1on1(int player1_choice, int player2_choice, char ply1[], char ply2[])
{
    if (player1_choice == STONE && player2_choice == PAPER)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "           Stone             |              Paper          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)                 |             ____(____   '---\n" RESET);
        printf(G_BROWN "      (_____)                |            (______          \n" RESET);
        printf(G_BROWN "      (_____)                |           (_______          \n" RESET);
        printf(G_BROWN "      (____)                 |            (_______         \n" RESET);
        printf(G_BROWN "---.__(___)                  |              (__________.---\n" RESET);
        printf("\n");
        printf(GREEN "%s win!!\n" RESET, ply2);
    }
    if (player1_choice == STONE && player2_choice == SCISSOR)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "           Stone             |             Scissor         \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)                 |             ____(____   '---\n" RESET);
        printf(G_BROWN "      (_____)                |            (______          \n" RESET);
        printf(G_BROWN "      (_____)                |           (__________       \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(GREEN "%s win!!\n" RESET, ply1);
    }
    if (player1_choice == PAPER && player2_choice == STONE)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "           Paper             |              Stone          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |                 (____   '---\n" RESET);
        printf(G_BROWN "          ______)            |                (_____)      \n" RESET);
        printf(G_BROWN "          _______)           |                (_____)      \n" RESET);
        printf(G_BROWN "         _______)            |                 (____)      \n" RESET);
        printf(G_BROWN "---.__________)              |                  (___)__.---\n" RESET);
        printf("\n");
        printf(GREEN "%s win!!\n" RESET, ply1);
    }
    if (player1_choice == PAPER && player2_choice == SCISSOR)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "           Paper             |             Scissor         \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "          _______)           |           (__________       \n" RESET);
        printf(G_BROWN "         _______)            |                 (____)      \n" RESET);
        printf(G_BROWN "---.__________)              |                  (___)__.---\n" RESET);
        printf("\n");
        printf(GREEN "%s win!!\n" RESET, ply2);
    }
    if (player1_choice == SCISSOR && player2_choice == STONE)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "          Scissor            |              Stone          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |                 (____   '---\n" RESET);
        printf(G_BROWN "          ______)            |                (_____)      \n" RESET);
        printf(G_BROWN "       __________)           |                (_____)      \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(GREEN "%s win!!\n" RESET, ply2);
    }
    if (player1_choice == SCISSOR && player2_choice == PAPER)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "          Scissor            |              Paper          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "       __________)           |           (_______          \n" RESET);
        printf(G_BROWN "      (____)                 |            (_______         \n" RESET);
        printf(G_BROWN "---.__(___)                  |              (__________.---\n" RESET);
        printf("\n");
        printf(GREEN "%s win!!\n" RESET, ply1);
    }
    if (player1_choice == STONE && player2_choice == STONE)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "           Stone             |              Stone          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)                 |                 (____   '---\n" RESET);
        printf(G_BROWN "      (_____)                |                (_____)      \n" RESET);
        printf(G_BROWN "      (_____)                |                (_____)      \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(YELLOW "It's a draw. 😏\n" RESET);
    }
    if (player1_choice == PAPER && player2_choice == PAPER)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "           Paper             |              Paper          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "          _______)           |           (_______          \n" RESET);
        printf(G_BROWN "         _______)            |            (_______         \n" RESET);
        printf(G_BROWN "---.__________)              |              (__________.---\n" RESET);
        printf("\n");
        printf(YELLOW "It's a draw. 😏\n" RESET);
    }
    if (player1_choice == SCISSOR && player2_choice == SCISSOR)
    {
        printf(CYAN    "          PLAYER 1           |             PLAYER 2        \n" RESET);
        printf(CYAN    "          Scissor            |             Scissor         \n");
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "       __________)           |           (__________       \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(YELLOW "It's a draw. 😏\n" RESET);
    }
    printf("\n");
}

void display_ascii(int comp_choice, int player_choice)
{
    if (comp_choice == STONE && player_choice == PAPER)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "           Stone             |              Paper          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)                 |             ____(____   '---\n" RESET);
        printf(G_BROWN "      (_____)                |            (______          \n" RESET);
        printf(G_BROWN "      (_____)                |           (_______          \n" RESET);
        printf(G_BROWN "      (____)                 |            (_______         \n" RESET);
        printf(G_BROWN "---.__(___)                  |              (__________.---\n" RESET);
        printf("\n");
        printf(GREEN "You win!! 😃\n" RESET);
    }
    if (comp_choice == STONE && player_choice == SCISSOR)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "           Stone             |             Scissor         \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)                 |             ____(____   '---\n" RESET);
        printf(G_BROWN "      (_____)                |            (______          \n" RESET);
        printf(G_BROWN "      (_____)                |           (__________       \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(RED "Computer win!! 😒\n" RESET);
    }
    if (comp_choice == PAPER && player_choice == STONE)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "           Paper             |              Stone          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |                 (____   '---\n" RESET);
        printf(G_BROWN "          ______)            |                (_____)      \n" RESET);
        printf(G_BROWN "          _______)           |                (_____)      \n" RESET);
        printf(G_BROWN "         _______)            |                 (____)      \n" RESET);
        printf(G_BROWN "---.__________)              |                  (___)__.---\n" RESET);
        printf("\n");
        printf(RED "Computer win!! 😒\n" RESET);
    }
    if (comp_choice == PAPER && player_choice == SCISSOR)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "           Paper             |             Scissor         \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "          _______)           |           (__________       \n" RESET);
        printf(G_BROWN "         _______)            |                 (____)      \n" RESET);
        printf(G_BROWN "---.__________)              |                  (___)__.---\n" RESET);
        printf("\n");
        printf(GREEN "You win!! 😃\n" RESET);
    }
    if (comp_choice == SCISSOR && player_choice == STONE)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "          Scissor            |              Stone          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |                 (____   '---\n" RESET);
        printf(G_BROWN "          ______)            |                (_____)      \n" RESET);
        printf(G_BROWN "       __________)           |                (_____)      \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(GREEN "You win!! 😃\n" RESET);
    }
    if (comp_choice == SCISSOR && player_choice == PAPER)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "          Scissor            |              Paper          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "       __________)           |           (_______          \n" RESET);
        printf(G_BROWN "      (____)                 |            (_______         \n" RESET);
        printf(G_BROWN "---.__(___)                  |              (__________.---\n" RESET);
        printf("\n");
        printf(RED "Computer win!! 😒\n" RESET);
    }
    if (comp_choice == STONE && player_choice == STONE)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "           Stone             |              Stone          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)                 |                 (____   '---\n" RESET);
        printf(G_BROWN "      (_____)                |                (_____)      \n" RESET);
        printf(G_BROWN "      (_____)                |                (_____)      \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(YELLOW "It's a draw. 😏\n" RESET);
    }
    if (comp_choice == PAPER && player_choice == PAPER)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "           Paper             |              Paper          \n" RESET);
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "          _______)           |           (_______          \n" RESET);
        printf(G_BROWN "         _______)            |            (_______         \n" RESET);
        printf(G_BROWN "---.__________)              |              (__________.---\n" RESET);
        printf("\n");
        printf(YELLOW "It's a draw. 😏\n" RESET);
    }
    if (comp_choice == SCISSOR && player_choice == SCISSOR)
    {
        printf(CYAN    "          COMPUTER           |               YOU           \n" RESET);
        printf(CYAN    "          Scissor            |             Scissor         \n");
        printf(G_BROWN "    _______                  |                  _______    \n" RESET);
        printf(G_BROWN "---'   ____)____             |             ____(____   '---\n" RESET);
        printf(G_BROWN "          ______)            |            (______          \n" RESET);
        printf(G_BROWN "       __________)           |           (__________       \n" RESET);
        printf(G_BROWN "      (____)                 |                 (____)      \n" RESET);
        printf(G_BROWN "---.__(___)                  |                  (___)__.---\n" RESET);
        printf("\n");
        printf(YELLOW "It's a draw. 😏\n" RESET);
    }
    printf("\n");
}

void sleep_half_second() 
{
    #ifdef _WIN32
        Sleep(500); // milliseconds
    #else
        usleep(500000); // microseconds
    #endif
}

void dramatic_countdown() 
{
    // Dramatic countdown inspired by ChatGPT to enhance game UX
    printf(" Stone...");
    fflush(stdout);
    sleep_half_second();

    printf(" Paper...");
    fflush(stdout);
    sleep_half_second();

    printf(" Scissor...\n");
    fflush(stdout);
    sleep_half_second();

    printf("SHOOT!\a\n"); // \a rings a bell (if enabled on terminal)
    fflush(stdout); 
}

int comp_Choice(int difficulty, int last_move)
{
    static int chance, stone_freq = 0, paper_freq = 0, scissor_freq = 0;

    if (difficulty == 1) // for easy game mode
    {
        // in easy mode it just return random move
        return (rand() % 3) + 1; // (rand() % max - min + 1) + min
    }
    else if (difficulty == 2) // for medium game mode
    {
        // in medium difficulty it returns random move which has a chance of 35% otherwise chance of 65% the computer will analyze
        // player's last move, and think it will do the same move again and thus return a move to counter it
        // if there is no last move then computer plays random
        // like: Played stone last time -> player might play stone this time also -> computer palys paper to counter it
        chance = (rand() % 100) + 1;
        if (chance < 36)
        {
            return (rand() % 3) + 1;
        }
        else
        {
            if (last_move == STONE)
            {
                return PAPER;
            }
            else if (last_move == PAPER)
            {
                return SCISSOR;
            }
            else if (last_move == SCISSOR)
            {
                return STONE;
            }
            else
            {
                return (rand() % 3) + 1;
            }
        }
    }
    else // for hard game mode
    {
        // in hard difficulty computer analyzes the move frequency of each stone, paper, scissor of the player for the whole game dynamically
        // and thiks that if player has played stone many times then it will might play stone agin for the next move, so computer chooses
        // paper to counter it, the probabilty of the computer to play like this is 90% and 10% chance it it to play randomly, and if all move
        // frequencies are 0 it will play randomly and if all move frequencies are not 0 but same then the computer will play by analyzing the
        // move of the player
        if (last_move == STONE)
        {
            stone_freq++;
        }
        else if (last_move == PAPER)
        {
            paper_freq++;
        }
        else if (last_move == SCISSOR)
        {
            scissor_freq++;
        }
        else;

        if (stone_freq > paper_freq && stone_freq > scissor_freq)
        {
            return PAPER;
        }
        else if (paper_freq > stone_freq && paper_freq > scissor_freq)
        {
            return SCISSOR;
        }
        else if (scissor_freq > stone_freq && scissor_freq > paper_freq)
        {
            return STONE;
        }
        else if (stone_freq == paper_freq && stone_freq != scissor_freq)
        {
            chance = (rand() % 100) + 1;
            if (chance < 6)
            {
                return (rand() % 3) + 1;
            }
            else
            {
                if (last_move == STONE)
                {
                    return PAPER;
                }
                else
                {
                    return SCISSOR;
                }
            }
        }
        else if (stone_freq == scissor_freq && stone_freq != paper_freq)
        {
            chance = (rand() % 100) + 1;
            if (chance < 6)
            {
                return (rand() % 3) + 1;
            }
            else
            {
                if (last_move == STONE)
                {
                    return PAPER;
                }
                else
                {
                    return STONE;
                }
            }
        }
        else if (paper_freq == scissor_freq && paper_freq != stone_freq)
        {
            chance = (rand() % 100) + 1;
            if (chance < 6)
            {
                return (rand() % 3) + 1;
            }
            else
            {
                if (last_move == 2)
                {
                    return SCISSOR;
                }
                else
                {
                    return STONE;
                }
            }
        }
        else
        {
            chance = (rand() % 100) + 1;
            if (chance < 11)
            {
                return (rand() % 3) + 1;
            }
            else
            {
                if (last_move == STONE)
                {
                    return PAPER;
                }
                else if (last_move == PAPER)
                {
                    return SCISSOR;
                }
                else if (last_move == SCISSOR)
                {
                    return STONE;
                }
                else
                {
                    return (rand() % 3) + 1;
                }
            }
        }
    }
}

void play_Game_1on1()
{
    int rounds; // stores the number of rounds user wants to play
    int player1_choice, player2_choice; // stores the choice of player 1 and player 2 respectively
    int player1_score = 0, player2_score = 0; // stores the scores of player 1 and player 2 respectively
    int input_buffer_clearer;
    char name1[20], name2[20]; // stores the name of the player 1 and player 2 respectively

    printf("Enter nickname of Player 1: ");
    scanf("%s", name1);
    while((input_buffer_clearer = getchar()) != '\n' && input_buffer_clearer != '\0');
    while(check_other_char_than_alphabets(name1))
    {
        printf(RED "Invalid name!" RESET " Enter name containing characters only from A to Z or a to z: ");
        scanf("%s", name1);
        while((input_buffer_clearer = getchar()) != '\n' && input_buffer_clearer != '\0');
    }

    printf("Enter nickname of Player 2: ");
    scanf("%s", name2);
    while((input_buffer_clearer = getchar()) != '\n' && input_buffer_clearer != '\0');
    while(check_other_char_than_alphabets(name2))
    {
        printf(RED "Invalid name!" RESET " Enter name containing characters only from A to Z or a to z: ");
        scanf("%s", name2);
        while((input_buffer_clearer = getchar()) != '\n' && input_buffer_clearer != '\0');
    }

    capitalize_first_word(name1);
    capitalize_first_word(name2);

    printf("How many rounds? ");
    rounds = get_valid_int(1, 100);

    // clears the terminal
    #ifdef _WIN32 // in windows os
        system("cls"); 
    #else // in os other than windows
        system("clear");
    #endif
    
    for (int i = 1; i <= rounds; i++)
    {
        printf("\n" CYAN "Round %d" RESET "\n", i);
        printf("\n1. STONE 🪨  2. PAPER 📃  3. SCISSOR ✂️\n%s's move...\n", name1);
        player1_choice = get_valid_int(1, 3);
        
        printf("\n1. STONE 🪨  2. PAPER 📃  3. SCISSOR ✂️\n%s's move...\n", name2);
        player2_choice = get_valid_int(1, 3);

        display_ascii_for_1on1(player1_choice, player2_choice, name1, name2);

        if (player1_choice == player2_choice); // no score is added to either in draw moves
        // there are only three possible winning move combination for player 1 to win other than that player 2 will win
        else if (player1_choice == STONE && player2_choice == SCISSOR) player1_score++;
        else if (player1_choice == PAPER && player2_choice == STONE) player1_score++;
        else if (player1_choice == SCISSOR && player2_choice == PAPER) player1_score++;
        else player2_score++;
    }

    update_scoreboard_1on1(player1_score, player2_score, name1, name2);

    printf("\n" CYAN ">>> GAME OVER <<<" RESET);
    if (player1_score > player2_score)
    {
        printf(GREEN "\n>> %s WON\n" RESET, name1);
        printf(RED "\n>> %s LOSE\n" RESET, name2);
        printf("Final Score - " GREEN "%s: %d" RESET " | " RED "%s: %d" RESET "\n", name1, player1_score, name2, player2_score);
    }
    else if (player1_score < player2_score)
    {
        printf(RED "\n>> %s LOSE\n" RESET, name1);
        printf(GREEN "\n>> %s WON\n" RESET, name2);
        printf("Final Score - " RED "%s: %d" RESET " | " GREEN "%s: %d" RESET "\n", name1, player1_score, name2, player2_score);
    }
    else
    {
        printf(YELLOW "\n>> DRAW\n" RESET);
        printf("Final Score - " YELLOW "%s: %d" RESET " | " YELLOW "%s: %d" RESET "\n", name1, player1_score, name2, player2_score);
    }
}

void play_Game_Comp(int difficulty)
{
    int rounds; // stores the number of rounds user wants to play
    int comp; // stores the choice of the computer
    int player_choice; //stores the choice of the player
    int player_score = 0, comp_Score = 0; // stores the score secured by player and computer respectively in every round
    int last_move = 0; // stores the player's last move
    int input_buffer_clearer;
    char name[20]; // stores the name of the player

    printf("Enter your nick name: ");
    scanf("%s", name);
    while((input_buffer_clearer = getchar()) != '\n' && input_buffer_clearer != '\0');

    while(check_other_char_than_alphabets(name))
    {
        printf(RED "Invalid name!" RESET " Enter name containing charcters from A to Z or a to z only: ");
        scanf("%s", name);
        while((input_buffer_clearer = getchar()) != '\n' && input_buffer_clearer != '\0');
    }

    capitalize_first_word(name);

    printf("How many rounds? ");
    rounds = get_valid_int(1, 100);

    // clears the terminal, this clearing code snippet is being taken from ChatGPT
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    for (int i = 1; i <= rounds; i++)
    {
        printf("\n" CYAN "Round %d" RESET "\n", i);
        printf("1. STONE 🪨  2. PAPER 📃  3. SCISSOR ✂️\n");
        player_choice = get_valid_int(1, 3);

        comp = comp_Choice(difficulty, last_move); // computer choses it moves as per the game's difficulty and previous player choice
        last_move = player_choice;

        dramatic_countdown(); // the code snippet of this function is takn from ChatGPT, to enhance the look of the code
        display_ascii(comp, player_choice);

        if (player_choice == comp); // in case of draw no score is given
        // in case where player selected the winning move, player's score is increased by 1
        else if (player_choice == STONE && comp == SCISSOR) player_score++;
        else if (player_choice == PAPER && comp == STONE) player_score++;
        else if (player_choice == SCISSOR && comp == PAPER) player_score++;
        // else is used becuse only three move is possible where where player can win and the draw moes are also considered thus other move 
        // must be move in which computer wins
        else comp_Score++;
    }

    printf("\n" CYAN ">>> GAME OVER <<<" RESET);
    if (player_score > comp_Score)
    {
        printf(GREEN "\n>> YOU WON\n" RESET);
        printf("Final Score - " GREEN "You: %d" RESET " | " RED "Computer: %d" RESET "\n", player_score, comp_Score);
    }
    else if (player_score < comp_Score)
    {
        printf(RED "\n>> YOU LOSE\n" RESET);
        printf("Final Score - " RED "You: %d" RESET " | " GREEN "Computer: %d" RESET "\n", player_score, comp_Score);
    }
    else
    {
        printf(YELLOW "\n>> DRAW\n" RESET);
        printf("Final Score - " YELLOW "You: %d" RESET " | " YELLOW "Computer: %d" RESET "\n", player_score, comp_Score);
    }
    update_scoreboard(name, player_score, comp_Score);
}

int main()
{
    srand(time(NULL)); // seeds the random to time of the system

    int main_menu_Choice; // stores the main menu choice
    int game_mode_Choice; // stores the game mode choice
    int difficulty_Choice; // stores the difficulty level choice

    do
    {
        printf("\n" CYAN "--- MAIN MENU ---\n" RESET);
        printf("1. Play Game\n2. View Rules\n3. View Scoreboard\n4. Reset Scoreboard\n5. Exit Game\n");
        main_menu_Choice = get_valid_int(1, 5);

        // switch case is used for th e user to navigate between different menus
        switch (main_menu_Choice)
        {
        case 1:
            printf("\n" CYAN "-- GAME MODE --\n" RESET);
            printf("1. 🆚 Computer\n2. 🆚 other Player\n");
            game_mode_Choice = get_valid_int(1, 2);
            
            if (game_mode_Choice == 1) // menu to play aginst the computer
            {
                printf("\n" CYAN "-- DIFFICULTY --\n" RESET);
                printf("1. Easy\n2. Medium\n3. Hard\n");
                difficulty_Choice = get_valid_int(1, 3);

                play_Game_Comp(difficulty_Choice);
            }

            else // menu to play against another
            {
                play_Game_1on1();
            }
            break;

        case 2:
            show_rules();
            break;

        case 3:
            view_scoreboard();
            break;

        case 4:
            reset_scoreboard();
            break;

        case 5:
            printf(YELLOW "\nGoodbye !!\n\n" RESET);
            break;
        }
    } while (main_menu_Choice != 5); // this statement will repeat the loop again and again until or unless user enters 5 to exit from the game

    return 0;
}
