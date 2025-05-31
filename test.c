#include <stdio.h>

void draw_philosopher_table(void)
{
    printf("\033[1;33m"); // Yellow color

    printf("                    🧑‍🎓 (P1)                   \n");
    printf("                     🍴                 \n");
    printf("                                     \n");
    printf("                    \n");
    printf("  (P5) 🧑‍🎓 🍴           🍝          🍴 🧑‍🎓(P2) \n");
    printf("                                     \n");
    printf("                                        \n");
    printf("                                     \n");
    printf("     (P3)  🧑‍🎓  🍴         🍴 🧑‍🎓 (P4)\n");
    printf("             |\n");

    printf("\033[0m"); // Reset color
}

int main()
{
    draw_philosopher_table();
    return 0;
}