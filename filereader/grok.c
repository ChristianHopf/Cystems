#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(FILE *stream) {
    size_t capacity = 128;
    char *buffer = malloc(capacity);
    if (!buffer) {
        perror("malloc failed");
        return NULL;
    }

    size_t total_size = 0;
    char *temp;

    while (1) {
        if (fgets(buffer + total_size, capacity - total_size, stream) == NULL) {
            if (total_size == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        total_size += strlen(buffer + total_size);

        if (total_size > 0 && buffer[total_size - 1] != '\n') {
            capacity *= 2;
            temp = realloc(buffer, capacity);
            if (!temp) {
                perror("realloc failed");
                free(buffer);
                return NULL;
            }
            buffer = temp;
        } else {
            break;
        }
    }

    temp = realloc(buffer, total_size + 1);
    if (temp) {
        buffer = temp;
    }

    return buffer;
}

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen failed");
        return 1;
    }

    char *line;
    while ((line = read_line(file)) != NULL) {
        printf("%s", line);
        free(line);
    }

    fclose(file);
    return 0;
}
