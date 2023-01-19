#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[10];
    char status[5];
} Player;
typedef Player *player_poiter;

bool user = true, bot = false;
int type_bot, position, i = 0;
char *position5[25] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15",
                        "16","17", "18", "19", "20", "21", "22", "23", "24"};

char *now(char *dt);

void Save_2_player(player_poiter *player);

void Save_Bot(int type_bot,int Resualt);

int bot3(char *position3, char output[]);

int bot5(char output[], char bot[]);

void table3(char *position3, player_poiter *player);

void table5(player_poiter *player);



int main() {
    printf("\t\tWELCOME TO OX GAME!!");
    printf("\n\n");

    char position3[10] = {"012345678"},A[4];
    int Resualt;
    Player player[2];
    player_poiter pp[2];
    pp[0] = &player[0];
    pp[1] = &player[1];

    srand(time(NULL));

    char ib[2];
    char input[2], BotXO[2];

    printf("Do you want to play with bot? (Yes or No) : ");
    scanf("%s", A);
    //bot
    if (strcasecmp("Yes", A) == 0) {
        choose:
        printf("Do you want X or O ? : ");
        scanf("%s", ib);
        if (strcasecmp(ib, "X") == 0) {
            strcpy(input,"X");
            strcpy(BotXO,"O");
        }
        else if (strcasecmp(ib, "O") == 0) {
            strcpy(input,"O");
            strcpy(BotXO,"X");
        }
        else {
            goto choose;
        }
        bot = true;
    }
    else {
        printf("Enter your name (P1 => X ) : ");
        scanf("%s", player[0].name);
        printf("Enter your name (P2 => O ) : ");
        scanf("%s", player[1].name);
    }

    printf("Select table (3 or 5) : ");
    scanf("%d", &type_bot);
    if (type_bot == 3) {
        if (bot) {
            if (strcasecmp(input,"O")==0) {
                position3[rand() % 10] = 'X';
                i++;
            }
            Resualt = bot3(position3, input);
            Save_Bot(type_bot,Resualt);

        }
        else {
            table3(position3, pp);
            Save_2_player(pp);
        }
    }
    else if (type_bot == 5) {
        if (bot) {
            if (strcasecmp(input,"O")==0) {
                position5[rand() % 26]="X";
                i++;
            }
            Resualt = bot5(input, BotXO);
            Save_Bot(type_bot,Resualt);
        }
        else {
            table5(pp);
            Save_2_player(pp);
        }
    }
}

char *now(char *dt) {
    time_t current = time(NULL);
    struct tm *info = localtime(&current);
    strftime(dt, 40, "%c", info);
    return dt;
}

//ฟังก์ชัน
void Save_2_player(player_poiter *player) {
    char date[40];
    FILE *f = fopen("2_Player.txt", "a");
    fprintf(f,"%20s %10s (%5s) %10s (%5s)\n", now(date), player[0]->name, player[0]->status, player[1]->name,
            player[1]->status);
    fclose(f);
}

void Save_Bot(int type_bot,int Resualt) {
    char date[40],Type[6],resault[5];
    if (type_bot == 3){
        strcpy(Type,"Bot_3");
    } else{
        strcpy(Type,"Bot_5");
    }

    if(Resualt == 0){
        strcpy(resault,"Lost");
    }
    else if(Resualt == 1){
        strcpy(resault,"Win");
    }
    else{
        strcpy(resault,"Draw");
    }

    FILE *f = fopen("Bot.txt", "a");
    fprintf(f,"%20s %5s %5s\n", now(date),Type,resault);
    fclose(f);
}

int bot3(char *position3, char output[]) {
    srand(time(NULL));
    char player,bot;
    int p=0,r=0;
    for (;;) {
        system("cls");
        printf("\t\t%c | %c | %c\n", position3[6], position3[7], position3[8]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[3], position3[4], position3[5]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[0], position3[1], position3[2]);

        if (strcasecmp(output,"X")==0){
            player = 'X';
            bot = 'O';
        } else{
            player = 'O';
            bot = 'X';
        }

        if (user) {
            printf("Enter position : ");
            scanf("%d", &position);
            if (position3[position] == 'X' || position3[position] == 'O') {
            }
            else{
                position3[position] = player;
                user = false;
                i++;
            }
        }
        else {
                do {
                    p = rand() % 9;
                }
                while (position3[p] == 'X' || position3[p] == 'O');

                position3[p] = bot;
                user = true;
                i++;

        }

        system("cls");
        printf("\t\t%c | %c | %c\n", position3[6], position3[7], position3[8]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[3], position3[4], position3[5]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[0], position3[1], position3[2]);

        bool check = position3[0] == position3[1] && position3[1] == position3[2] ||
                     position3[3] == position3[4] && position3[4] == position3[5] ||
                     position3[6] == position3[7] && position3[7] == position3[8] ||
                     position3[0] == position3[3] && position3[3] == position3[6] ||
                     position3[1] == position3[4] && position3[4] == position3[7] ||
                     position3[2] == position3[5] && position3[5] == position3[8] ||
                     position3[0] == position3[4] && position3[4] == position3[8] ||
                     position3[2] == position3[4] && position3[4] == position3[6];

        if (check) {
            if (user) {
                printf("\nLost");
                return 0;
            } else {
                printf("\nWin");
                return 1;
            }
        }
        if (i == 9) {
            printf("Draw");
            return 2;
        }
    }
}

int bot5(char output[], char bot[]) {

    for (;;) {
        system("cls");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[20], position5[21], position5[22], position5[23],
               position5[24]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[15], position5[16], position5[17], position5[18],
               position5[19]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[10], position5[11], position5[12], position5[13],
               position5[14]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[5], position5[6], position5[7], position5[8],
               position5[9]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[0], position5[1], position5[2], position5[3],
               position5[4]);

        if (user) {
            printf("Enter position : ");
            scanf("%d", &position);
            if (strcasecmp(position5[position],"X")==0 || strcasecmp(position5[position],"O") == 0) {
            }
            else{
                position5[position]=output;
                user = false;
                i++;
            }
        }
        else {
            do {
                position = rand() % 26;
            }
            while (strcasecmp(position5[position],"X")==0 || strcasecmp(position5[position],"O")==0);
            position5[position]=bot;
            user = true;
            i++;

        }

        system("cls");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[20], position5[21], position5[22], position5[23],
               position5[24]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[15], position5[16], position5[17], position5[18],
               position5[19]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[10], position5[11], position5[12], position5[13],
               position5[14]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[5], position5[6], position5[7], position5[8],
               position5[9]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[0], position5[1], position5[2], position5[3],
               position5[4]);


        bool check = strcmp(position5[0], position5[1]) == 0 && strcmp(position5[1], position5[2]) == 0 &&
                     strcmp(position5[2], position5[3]) == 0 && strcmp(position5[3], position5[4]) == 0 ||
                     strcmp(position5[5], position5[6]) == 0 && strcmp(position5[6], position5[7]) == 0 &&
                     strcmp(position5[7], position5[8]) == 0 && strcmp(position5[8], position5[9]) == 0 ||
                     strcmp(position5[10], position5[11]) == 0 && strcmp(position5[11], position5[12]) == 0 &&
                     strcmp(position5[12], position5[13]) == 0 && strcmp(position5[13], position5[14]) == 0 ||
                     strcmp(position5[15], position5[16]) == 0 && strcmp(position5[16], position5[17]) == 0 &&
                     strcmp(position5[17], position5[18]) == 0 && strcmp(position5[18], position5[19]) == 0 ||
                     strcmp(position5[20], position5[21]) == 0 && strcmp(position5[21], position5[22]) == 0 &&
                     strcmp(position5[22], position5[23]) == 0 && strcmp(position5[23], position5[24]) == 0 ||
                     strcmp(position5[0], position5[5]) == 0 && strcmp(position5[5], position5[10]) == 0 &&
                     strcmp(position5[10], position5[15]) == 0 && strcmp(position5[15], position5[20]) == 0 ||
                     strcmp(position5[1], position5[6]) == 0 && strcmp(position5[6], position5[11]) == 0 &&
                     strcmp(position5[11], position5[16]) == 0 && strcmp(position5[16], position5[21]) == 0 ||
                     strcmp(position5[2], position5[7]) == 0 && strcmp(position5[7], position5[12]) == 0 &&
                     strcmp(position5[12], position5[17]) == 0 && strcmp(position5[17], position5[22]) == 0 ||
                     strcmp(position5[3], position5[8]) == 0 && strcmp(position5[8], position5[13]) == 0 &&
                     strcmp(position5[13], position5[18]) == 0 && strcmp(position5[18], position5[23]) == 0 ||
                     strcmp(position5[4], position5[9]) == 0 && strcmp(position5[9], position5[14]) == 0 &&
                     strcmp(position5[14], position5[19]) == 0 && strcmp(position5[19], position5[24]) == 0 ||
                     strcmp(position5[0], position5[6]) == 0 && strcmp(position5[6], position5[12]) == 0 &&
                     strcmp(position5[12], position5[18]) == 0 && strcmp(position5[18], position5[24]) == 0 ||
                     strcmp(position5[4], position5[8]) == 0 && strcmp(position5[8], position5[12]) == 0 &&
                     strcmp(position5[12], position5[16]) == 0 && strcmp(position5[16], position5[20]) == 0;

        if (check) {
            if (user) {
                printf("\nLost");
                return 0;
            }
            else {
                printf("\nWin");
                return 1;
            }
            break;
        }
        if (i == 25) {
            printf("Draw");
            return 2 ;
        }
    }

}


void table3(char *position3, player_poiter *player) {
    char op;
    for (;;) {
        system("cls");
        printf("\t\t%c | %c | %c\n", position3[6], position3[7], position3[8]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[3], position3[4], position3[5]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[0], position3[1], position3[2]);

        if (user) {
            op = 'X';
            printf("\n%s's Round\n ", player[0]->name);
        }
        else {
            op = 'O';
            printf("\n%s's Round\n ", player[1]->name);
        }
        printf("Enter position (%c) : ", op);
        scanf("%d", &position);
        if (position3[position] == 'X' || position3[position] == 'O') {

        }
        else {
            if (user) {
                position3[position] = 'X';
                user = false;
            }
            else {
                position3[position] = 'O';
                user = true;
            }
            i++;
        }

        system("cls");
        printf("\t\t%c | %c | %c\n", position3[6], position3[7], position3[8]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[3], position3[4], position3[5]);
        printf("\t\t----------\n");
        printf("\t\t%c | %c | %c\n", position3[0], position3[1], position3[2]);

        bool check = position3[0] == position3[1] && position3[1] == position3[2] ||
                     position3[3] == position3[4] && position3[4] == position3[5] ||
                     position3[6] == position3[7] && position3[7] == position3[8] ||
                     position3[0] == position3[3] && position3[3] == position3[6] ||
                     position3[1] == position3[4] && position3[4] == position3[7] ||
                     position3[2] == position3[5] && position3[5] == position3[8] ||
                     position3[0] == position3[4] && position3[4] == position3[8] ||
                     position3[2] == position3[4] && position3[4] == position3[6];

        if (check) {
            if (user) {
                printf("Player 2 (%s) Win!", player[1]->name);
                strcpy(player[0]->status, "Lost");
                strcpy(player[1]->status, "Win");
            }
            else {
                printf("Player 1 (%s) Win!", player[0]->name);
                strcpy(player[0]->status, "Win");
                strcpy(player[1]->status, "Lost");
            }
            break;
        }
        if (i == 9) {
            printf("Draw");
            strcpy(player[0]->status, "Draw");
            strcpy(player[1]->status, "Draw");
            break;
        }
    }
}

void table5(player_poiter *player) {
    char op;
    for (;;) {
        system("cls");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[20], position5[21], position5[22], position5[23],
               position5[24]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[15], position5[16], position5[17], position5[18],
               position5[19]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[10], position5[11], position5[12], position5[13],
               position5[14]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[5], position5[6], position5[7], position5[8],
               position5[9]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[0], position5[1], position5[2], position5[3],
               position5[4]);

        if (user) {
            op = 'X';
            printf("\n%s's Round\n ", player[0]->name);
        }
        else {
            op = 'O';
            printf("\n%s's Round\n ", player[1]->name);
        }

        printf("Enter position (%c) : ", op);
        scanf("%d", &position);
        if (strcmp(position5[position], "X") == 0 || strcmp(position5[position], "O") == 0) {
        }
        else {
            if (user) {
                position5[position]="X";
                user = false;
            }
            else {
                position5[position]="O";
                user = true;
            }
            i++;
        }

        system("cls");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[20], position5[21], position5[22], position5[23],
               position5[24]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[15], position5[16], position5[17], position5[18],
               position5[19]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[10], position5[11], position5[12], position5[13],
               position5[14]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[5], position5[6], position5[7], position5[8],
               position5[9]);
        printf("\t\t------------------\n");
        printf("\t\t%2s | %2s | %2s | %2s | %2s\n", position5[0], position5[1], position5[2], position5[3],
               position5[4]);


        bool check = strcmp(position5[0], position5[1]) == 0 && strcmp(position5[1], position5[2]) == 0 &&
                     strcmp(position5[2], position5[3]) == 0 && strcmp(position5[3], position5[4]) == 0 ||
                     strcmp(position5[5], position5[6]) == 0 && strcmp(position5[6], position5[7]) == 0 &&
                     strcmp(position5[7], position5[8]) == 0 && strcmp(position5[8], position5[9]) == 0 ||
                     strcmp(position5[10], position5[11]) == 0 && strcmp(position5[11], position5[12]) == 0 &&
                     strcmp(position5[12], position5[13]) == 0 && strcmp(position5[13], position5[14]) == 0 ||
                     strcmp(position5[15], position5[16]) == 0 && strcmp(position5[16], position5[17]) == 0 &&
                     strcmp(position5[17], position5[18]) == 0 && strcmp(position5[18], position5[19]) == 0 ||
                     strcmp(position5[20], position5[21]) == 0 && strcmp(position5[21], position5[22]) == 0 &&
                     strcmp(position5[22], position5[23]) == 0 && strcmp(position5[23], position5[24]) == 0 ||
                     strcmp(position5[0], position5[5]) == 0 && strcmp(position5[5], position5[10]) == 0 &&
                     strcmp(position5[10], position5[15]) == 0 && strcmp(position5[15], position5[20]) == 0 ||
                     strcmp(position5[1], position5[6]) == 0 && strcmp(position5[6], position5[11]) == 0 &&
                     strcmp(position5[11], position5[16]) == 0 && strcmp(position5[16], position5[21]) == 0 ||
                     strcmp(position5[2], position5[7]) == 0 && strcmp(position5[7], position5[12]) == 0 &&
                     strcmp(position5[12], position5[17]) == 0 && strcmp(position5[17], position5[22]) == 0 ||
                     strcmp(position5[3], position5[8]) == 0 && strcmp(position5[8], position5[13]) == 0 &&
                     strcmp(position5[13], position5[18]) == 0 && strcmp(position5[18], position5[23]) == 0 ||
                     strcmp(position5[4], position5[9]) == 0 && strcmp(position5[9], position5[14]) == 0 &&
                     strcmp(position5[14], position5[19]) == 0 && strcmp(position5[19], position5[24]) == 0 ||
                     strcmp(position5[0], position5[6]) == 0 && strcmp(position5[6], position5[12]) == 0 &&
                     strcmp(position5[12], position5[18]) == 0 && strcmp(position5[18], position5[24]) == 0 ||
                     strcmp(position5[4], position5[8]) == 0 && strcmp(position5[8], position5[12]) == 0 &&
                     strcmp(position5[12], position5[16]) == 0 && strcmp(position5[16], position5[20]) == 0;

        if (check) {
            if (user) {
                printf("Player 2 (%s) Win!", player[1]->name);
                strcpy(player[0]->status, "Lost");
                strcpy(player[1]->status, "Win");
            }
            else {
                printf("Player 1 (%s) Win!", player[0]->name);
                strcpy(player[0]->status, "Win");
                strcpy(player[1]->status, "Lost");
            }
            break;
        }
        if (i == 25) {
            printf("Draw");
            strcpy(player[0]->status, "Draw");
            strcpy(player[1]->status, "Draw");
            break;
        }
    }
}
