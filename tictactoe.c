#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0

void fill_table(int** table, int size);
void print_table(int** table, int size);
void fill_position(int** table, int x, int y, int player);
int verify_coord(int** table, int x, int y, int size);
int verify_table(int** table, int size, int player, int row, int col);

int main(void) {
    int size, play_limit, x, y, player = 1, result = -1, count = 1;

    scanf("%d", &size);
    
    // generate table
    int **table = (int**) malloc(sizeof(int*) * (size)); // rows
    for (unsigned int row = 0; row < size; row++) {
        table[row] = (int*) malloc(sizeof(int) * (size)); // cols
    }

    fill_table(table, size);

    play_limit = size * size;

    while(result == -1 && count <= play_limit) {
        print_table(table, size);

        player = count % 2 != 0 ? 1 : 2;

        printf("Coordenadas do jogador %d:\n", player);
        scanf("%d %d", &x, &y);

        if (verify_coord(table, x, y, size)) {
            continue;
        }

        fill_position(table, x, y, player);
        result = verify_table(table, size, player, y, x);

        count++;
    }

    print_table(table, size);
    if (result > 0) printf("Jogador %d ganhou!\n", result);
    else printf("Empate!\n");

    return EXIT_SUCCESS;
}

void fill_table(int** table, int size) {
    for (unsigned int row = 0; row < size; row++) {
        for (unsigned int col = 0; col < size; col++) {
            table[row][col] = 0;
        }
    }
}

void print_table(int** table, int size) {
    for (unsigned int row = 0; row < size; row++) {
        for (unsigned int col = 0; col < size; col++) {
            printf("%d ", table[row][col]);
        }

        printf("\n");
    }
}

int verify_coord(int** table, int x, int y, int size) {
    if ((x < size && x >= 0) && (y < size && y >= 0) && table[y][x] <= 0) return 0; 

    return 1;
}

void fill_position(int** table, int x, int y, int player) {
    table[y][x] = player;
}

int verify_row(int** table, int size, int player) {
    int col;

    for (unsigned int row = 0; row < size; row++) {
        col = 0;

        while (col < size) {
            if (table[row][col] != player) break;
            
            col++;
        }
        
        if (col == size) return player;
    }

    return -1;
}

int verify_col(int** table, int size, int player) {
    int row;
    
    for (unsigned int col = 0; col < size; col++) {
        row = 0;

        while (row < size) {
            if (table[row][col] != player) break;
            
            row++;
        }
        
        if (row == size) return player;
    }

    return -1;
}

int verify_diag(int** table, int size, int player) {
    int index = 0, inverse_index = size - 1;
    while (index < size) {
        if (table[index][index] != player) break;
        
        index++;
    }

    if (index == size) return player;

    index = 0;
    while (index < size) {
        if (table[index][inverse_index] != player) break;

        index++;
        inverse_index--;
    }

    if (index == size) return player;

    return -1;
}

int verify_table(int** table, int size, int player, int row, int col) {
    int index_limit = size - 1;

    // diagonal win condition
    if (((row == 0 && col == index_limit) || (row == index_limit && col == 0) || (row == col)) && (table[row][col] == player)) {
        if (verify_diag(table, size, player) > 0) return verify_diag(table, size, player);
    }

    if (verify_row(table, size, player) > 0) return verify_row(table, size, player);
    if (verify_col(table, size, player) > 0) return verify_col(table, size, player);

    return -1;
}
