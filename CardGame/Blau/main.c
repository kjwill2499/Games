
#include "table.h"
#include <stdio.h>

void Greeting(void);
void GoodBye(void);

void main(void)
{
    Greeting();
    Table * table = InitializeTable();
    while (PlayRoundAndContinue(table)) continue;
    GoodBye();
    ClearTable(table);
}

void Greeting(void)
{
    printf(
        "                         |\\         /|        \n"
        "                         | \\       / |        \n"
        "                         |  \\     /  |        \n"
        "                         |   \\   /   |        \n"
        "                   ----- |    \\ /    | -----  \n"
        "                   \\    \\ \\   | |   / /    /\n"
        "                    \\    \\ \\  | |  / /    / \n"
        "                     \\    \\ \\ | | / /    /  \n"
        "                      \\    \\ \\| |/ /    /   \n"
        "                       -----       -----       \n"
        "                       -----       -----       \n"
        "                      /    / /| |\\ \\    \\   \n"
        "                     /    / / | | \\ \\    \\  \n"
        "                    /    / /  | |  \\ \\    \\ \n"
        "                   /    / /   | |   \\ \\    \\\n"
        "                   ----- |    / \\    | -----  \n"
        "                         |   /   \\   |        \n"
        "                         |  /     \\  |        \n"
        "                         | /       \\ |        \n"
        "                         |/         \\|        \n"
        "                           WELCOME TO \n"
        "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "  ~      |-------\\    |                /\\        |      |        ~\n"
        "  ~      |       /    |               /  \\       |      |        ~\n"
        "  ~      |-------\\    |              /----\\      |      |        ~\n"
        "  ~      |        |   |             /      \\     |      |        ~\n"
        "  ~      |-------/    |______      /        \\    \\------/        ~\n"
        "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "                     Press Enter to Continue                    \n");
    SkipRestOfLine();
}

void GoodBye(void)
{
    printf(
        "\n\n"
        "                          |\\         /|        \n"
        "                          | \\       / |        \n"
        "                          |  \\     /  |        \n"
        "                          |   \\   /   |        \n"
        "                    ----- |    \\ /    | -----  \n"
        "                    \\    \\ \\   | |   / /    /\n"
        "                     \\    \\ \\  | |  / /    / \n"
        "                      \\    \\ \\ | | / /    /  \n"
        "                       \\    \\ \\| |/ /    /   \n"
        "                        -----       -----       \n"
        "                        -----       -----       \n"
        "                       /    / /| |\\ \\    \\   \n"
        "                      /    / / | | \\ \\    \\  \n"
        "                     /    / /  | |  \\ \\    \\ \n"
        "                    /    / /   | |   \\ \\    \\\n"
        "                    ----- |    / \\    | -----  \n"
        "                          |   /   \\   |        \n"
        "                          |  /     \\  |        \n"
        "                          | /       \\ |        \n"
        "                          |/         \\|        \n"
        "                      Thank You For Playing \n"
        "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "  ~      |-------\\    |                /\\        |      |      ~\n"
        "  ~      |       /    |               /  \\       |      |      ~\n"
        "  ~      |-------\\    |              /----\\      |      |      ~\n"
        "  ~      |        |   |             /      \\     |      |      ~\n"
        "  ~      |-------/    |______      /        \\    \\------/      ~\n"
        "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "                       Press Enter to Exit                    \n\n\n");
    SkipRestOfLine();
}

