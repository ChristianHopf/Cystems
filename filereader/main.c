#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *read_line(FILE *file){
  // Initialize buffer
  size_t capacity = 128;
  char *buffer = malloc(capacity);
  if (!buffer){
    perror("Error: malloc failed\n");
    return NULL;
  }

  size_t total_length = 0;
  char *temp;

  while (1){
    // Read into buffer from current position (start (buffer) + total_size)
    if (fgets(buffer + total_length, capacity - total_length, file) == NULL){
      if (total_length == 0){
        free(buffer);
        return NULL;
      }
      break;
    }

    // Update total_size
    total_length += strlen(buffer + total_length);

    // If last char isn't \n, there's more to read in that line
    if (total_length > 0 && buffer[total_length - 1] != '\n'){
      capacity *= 2;
      temp = realloc(buffer, capacity);
      if (!temp){
        perror("Error: realloc failed\n");
        free(buffer);
        return NULL;
      }
      buffer = temp;
    } else {
      break;
    }
  }
  return buffer;
}

int main(int argc, char *argv[]){
  if (argc != 2){
    perror("Usage: ./main <filename>");
    exit(1);
  }
  // Open file
  FILE *file = fopen(argv[1], "r");
  // file = fopen(argv[1], "r");
  if (!file){
    perror("Error: failed to open file (ensure file exists)");
    exit(1);
  }

  // Read lines from the file and print them until the end of the file
  char *line;
  while ((line = read_line(file)) != NULL){
    printf("%s", line);
    free(line);
  }

  fclose(file);
  return 0;
}
