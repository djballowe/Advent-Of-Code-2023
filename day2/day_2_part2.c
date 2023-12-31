#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int convert(char* p, int l);

int main(void) {
    char* buffer;
    long file_size;
    FILE* file = fopen("input.txt", "rb");

    char holder;

    int total = 0;

    int red = 0;
    int green = 0;
    int blue = 0;
    int min_red = 0;
    int min_green = 0;
    int min_blue = 0;
    int power = 0;
    char v[2] = { 0, 0 };
    int v_count = 1;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char*)malloc(file_size + 1);
    
    fread(buffer, 1, file_size, file);

    buffer[file_size] = '\0';
    fclose(file);

    for (int i = 0; i < file_size; i++) {
        if ((buffer[i] == 'r' && buffer[i - 1] != 'g') || buffer[i] == 'g' || buffer[i] == 'b') {
            int j = i - 2;
            holder = buffer[j];
            while(isdigit(holder)) {
                v[v_count] = holder;
                v_count--;
                j--;
                holder = buffer[j];
            }
            buffer[i] == 'r' ? red = convert(v, 2) : buffer[i] == 'g' ? green = convert(v, 2) : buffer[i] == 'b' ? blue = convert(v, 2) : 0;
            v_count = 1;
        } 

        if (buffer[i] == ';') {
            min_red = red > min_red ? red : min_red;
            min_blue = blue > min_blue ? blue : min_blue;
            min_green = green > min_green ? green : min_green;
            red = 0;
            blue = 0;
            green = 0;
        }
        
        if (buffer[i] == '\n') {
            min_red = red > min_red ? red : min_red;
            min_blue = blue > min_blue ? blue : min_blue;
            min_green = green > min_green ? green : min_green;
            power = min_red * min_green * min_blue;
            total += power;
            red = 0;
            blue = 0;
            green = 0;
            min_red = 0;
            min_green = 0;
            min_blue = 0;
        }
    } 
    printf("%d\n", total);
    free(buffer);
}

int convert(char* p, int l) {
    int result = 0;
    for (int i = 0; i < l; i++) {
        if (p[i] - '0' >= 0) {
            result = result * 10 + (p[i] - '0');
        }
        p[i] = 0;
    }
    return result;
}
