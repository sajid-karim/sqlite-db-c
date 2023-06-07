// writing initial REPL for the sqlite clone

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// now i want to create a input buffer struct
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;
// helper function to print the prompt
InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}
// helper function to print the prompt
void print_prompt(){
    printf("db > ");
}
// helper function to read the input
void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if(bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    // ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}
// helper function to close the input buffer
void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}
// helper function to execute the command
void execute_command(InputBuffer* input_buffer){
    if(strcmp(input_buffer->buffer, ".exit") == 0){
        exit(EXIT_SUCCESS);
    } else {
        printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
}
// helper function to execute the statement
void execute_statement(InputBuffer* input_buffer){
    switch(input_buffer->buffer[0]){
        case '.': 
            execute_command(input_buffer);
            break;
        default:
            printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
            break;
    }
}
// main function
int main(int argc, char* argv[]){
    InputBuffer* input_buffer = new_input_buffer();
    while(true){
        print_prompt();
        read_input(input_buffer);
        if(input_buffer->buffer[0] == '.'){
            execute_command(input_buffer);
        } else {
            execute_statement(input_buffer);
        }
    }
}
