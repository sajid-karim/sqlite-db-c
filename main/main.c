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

// helper function to print initial prompt
void print_initial_prompt() {
    printf("SQLite version 3.39.3 2022-09-05 11:02:23\n");
    printf("Enter \".help\" for usage hints.\n");
    printf("Connected to a transient in-memory database.\n");
    printf("Use \".open FILENAME\" to reopen on a persistent database.\n");
}
// helper function to execute help command
void print_help() {
    printf(".archive ...             Manage SQL archives\n");
    printf(".auth ON|OFF             Show authorizer callbacks\n");
    printf(".backup ?DB? FILE        Backup DB (default \"main\") to FILE\n");
    printf(".bail on|off             Stop after hitting an error.  Default OFF\n");
    printf(".binary on|off           Turn binary output on or off.  Default OFF\n");
    printf(".cd DIRECTORY            Change the working directory to DIRECTORY\n");
    printf(".changes on|off          Show number of rows changed by SQL\n");
    printf(".check GLOB              Fail if output since .testcase does not match\n");
    printf(".clone NEWDB             Clone data into NEWDB from the existing database\n");
    printf(".connection [close] [#]  Open or close an auxiliary database connection\n");
    printf(".databases               List names and files of attached databases\n");
    printf(".dbconfig ?op? ?val?     List or change sqlite3_db_config() options\n");
    printf(".dbinfo ?DB?             Show status information about the database\n");
    printf(".dump ?OBJECTS?          Render database content as SQL\n");
    printf(".echo on|off             Turn command echo on or off\n");
    printf(".eqp on|off|full|...     Enable or disable automatic EXPLAIN QUERY PLAN\n");
    printf(".excel                   Display the output of the next command in a spreadsheet\n");
    printf(".exit ?CODE?             Exit this program with return-code CODE\n");
    printf(".expert                  EXPERIMENTAL. Suggest indexes for queries\n");
    printf(".explain ?on|off|auto?   Change the EXPLAIN formatting mode. Default: auto\n");
    printf(".filectrl CMD ...        Run various sqlite3_file_control() operations\n");
    printf(".fullschema ?--indent?   Show schema and the content of sqlite_stat tables\n");
    printf(".headers on|off          Turn display of headers on or off\n");
    printf(".help ?-all? ?PATTERN?   Show help text for PATTERN\n");
    printf(".import FILE TABLE       Import data from FILE into TABLE\n");
    printf(".imposter INDEX TABLE    Create an imposter table TABLE on index INDEX\n");
    printf(".indexes ?TABLE?         Show names of indexes\n");
    printf(".limit ?LIMIT? ?VAL?     Display or change the value of an SQLITE_LIMIT\n");
    printf(".lint OPTIONS            Report potential schema issues\n");
    printf(".load FILE ?ENTRY?       Load an extension library\n");
    printf(".log FILE|off            Turn logging on or off. FILE can be stderr/stdout\n");
    printf(".mode MODE ?OPTIONS?     Set output mode\n");
    printf(".nonce STRING            Suspend safe mode for one command if nonce matches\n");
    printf(".nullvalue STRING        Use STRING in place of NULL values\n");
    printf(".once ?OPTIONS? ?FILE?   Output for the next SQL command only to FILE\n");
    printf(".open ?OPTIONS? ?FILE?   Close the existing database and reopen FILE\n");
    printf(".output ?FILE?           Send output to FILE or stdout if FILE is omitted\n");
    printf(".parameter CMD ...       Manage SQL parameter bindings\n");
    printf(".print STRING...         Print literal STRING\n");
    printf(".progress N              Invoke the progress handler after every N opcodes\n");
    printf(".prompt MAIN CONTINUE    Replace the standard prompts\n");
    printf(".quit                    Exit this program\n");
    printf(".read FILE               Read input from FILE or command output\n");
    printf(".recover                 Recover as much data as possible from a corrupt database\n");
    printf(".restore ?DB? FILE       Restore the content of DB (default \"main\") from FILE\n");
    printf(".save ?OPTIONS? FILE     Write the database to FILE (an alias for .backup ...)\n");
    printf(".scanstats on|off        Turn sqlite3_stmt_scanstatus() metrics on or off\n");
    printf(".schema ?PATTERN?        Show the CREATE statements matching PATTERN\n");
    printf(".selftest ?OPTIONS?      Run tests defined in the SELFTEST table\n");
    printf(".separator COL ?ROW?     Change the column and row separators\n");
    printf(".sha3sum ...             Compute a SHA3 hash of database content\n");
    printf(".shell CMD ARGS...       Run CMD ARGS... in a system shell\n");
    printf(".show                    Show the current values for various settings\n");
    printf(".stats ?ARG?             Show stats or turn stats on or off\n");
    printf(".system CMD ARGS...      Run CMD ARGS... in a system shell\n");
    printf(".tables ?TABLE?          List names of tables matching the LIKE pattern TABLE\n");
    printf(".testcase NAME           Begin redirecting output to 'testcase-out.txt'\n");
    printf(".testctrl CMD ...        Run various sqlite3_test_control() operations\n");
    printf(".timeout MS              Try opening locked tables for MS milliseconds\n");
    printf(".timer on|off            Turn the SQL timer on or off\n");
    printf(".trace ?OPTIONS?         Output each SQL statement as it is run\n");
    printf(".vfsinfo ?AUX?           Information about the top-level VFS\n");
    printf(".vfslist                 List all available VFSes\n");
    printf(".vfsname ?AUX?           Print the name of the VFS stack\n");
    printf(".width NUM1 NUM2 ...     Set the minimum column widths for columnar output\n");
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
    } else if(strcmp(input_buffer->buffer, ".help") == 0){
            print_help();
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
    print_initial_prompt();
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
