// List of all the tokens supported by the sqlite query language
/*
** May the force be with you.
** 
*****************************************************************
** An Tokenizer for SQL 
** This file contains C code to split SQL input string up into 
** individual tokens and sends those tokens one-by-one over to 
** the parser for analysis.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum Keywords {

  // The initial keywords tokens of the SQL language
  TOKEN_KEYWORD_SELECT = 10,
  TOKEN_KEYWORD_FROM,
  TOKEN_KEYWORD_WHERE,
  TOKEN_KEYWORD_AND,
  TOKEN_KEYWORD_OR,
  TOKEN_ORDER_BY,
  TOKEN_GROUP_BY,
  TOKEN_KEYWORD_ASC,
  TOKEN_KEYWORD_DESC,
  TOKEN_KEYWORD_LIMIT
};


// The token struct
typedef struct {
  enum Keywords type;
  char* str;
  int len;
} Token;

// The tokenizer struct
typedef struct {
  char* input;
  int pos;
} Tokenizer;

// Get the type of the token
enum Keywords get_keyword_type(char* str, int len) {
  if (len == 6 && strncmp(str, "SELECT", 6) == 0) return TOKEN_KEYWORD_SELECT;
  if (len == 4 && strncmp(str, "FROM", 4) == 0) return TOKEN_KEYWORD_FROM;
  if (len == 5 && strncmp(str, "WHERE", 5) == 0) return TOKEN_KEYWORD_WHERE;
  if (len == 3 && strncmp(str, "AND", 3) == 0) return TOKEN_KEYWORD_AND;
  if (len == 2 && strncmp(str, "OR", 2) == 0) return TOKEN_KEYWORD_OR;
  if (len == 8 && strncmp(str, "ORDER BY", 8) == 0) return TOKEN_ORDER_BY;
  if (len == 8 && strncmp(str, "GROUP BY", 8) == 0) return TOKEN_GROUP_BY;
  if (len == 3 && strncmp(str, "ASC", 3) == 0) return TOKEN_KEYWORD_ASC;
  if (len == 4 && strncmp(str, "DESC", 4) == 0) return TOKEN_KEYWORD_DESC;
  if (len == 5 && strncmp(str, "LIMIT", 5) == 0) return TOKEN_KEYWORD_LIMIT;
  return -1;
}

// Get the next token
Token get_next_token(Tokenizer* tokenizer) {
  Token token;
  token.str = NULL;
  token.len = 0;
  token.type = -1;

  // Skip all the whitespaces
  while (tokenizer->input[tokenizer->pos] == ' ') {
    tokenizer->pos++;
  }

  // Check if we have reached the end of the input
  if (tokenizer->input[tokenizer->pos] == '\0') {
    return token;
  }

  // Check if we have reached a keyword
  if (tokenizer->input[tokenizer->pos] >= 'A' && tokenizer->input[tokenizer->pos] <= 'Z') {
    int start = tokenizer->pos;
    while (tokenizer->input[tokenizer->pos] >= 'A' && tokenizer->input[tokenizer->pos] <= 'Z') {
      tokenizer->pos++;
    }
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = get_keyword_type(token.str, token.len);
    return token;
  }

  // Check if we have reached a number
  if (tokenizer->input[tokenizer->pos] >= '0' && tokenizer->input[tokenizer->pos] <= '9') {
    int start = tokenizer->pos;
    while (tokenizer->input[tokenizer->pos] >= '0' && tokenizer->input[tokenizer->pos] <= '9') {
      tokenizer->pos++;
    }
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Check if we have reached a string
  if (tokenizer->input[tokenizer->pos] == '\'') {
    int start = tokenizer->pos;
    tokenizer->pos++;
    while (tokenizer->input[tokenizer->pos] != '\'') {
      tokenizer->pos++;
    }
    tokenizer->pos++;
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Check if we have reached a comma
  if (tokenizer->input[tokenizer->pos] == ',') {
    int start = tokenizer->pos;
    tokenizer->pos++;
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Check if we have reached a semicolon
  if (tokenizer->input[tokenizer->pos] == ';') {
    int start = tokenizer->pos;
    tokenizer->pos++;
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Check if we have reached a left parenthesis
  if (tokenizer->input[tokenizer->pos] == '(') {
    int start = tokenizer->pos;
    tokenizer->pos++;
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Check if we have reached a right parenthesis
  if (tokenizer->input[tokenizer->pos] == ')') {
    int start = tokenizer->pos;
    tokenizer->pos++;
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Check if we have reached a star
  if (tokenizer->input[tokenizer->pos] == '*') {
    int start = tokenizer->pos;
    tokenizer->pos++;
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Check if we have reached a dot
  if (tokenizer->input[tokenizer->pos] == '.') {
    int start = tokenizer->pos;
    tokenizer->pos++;
    token.str = tokenizer->input + start;
    token.len = tokenizer->pos - start;
    token.type = 0;
    return token;
  }

  // Otherwise we have an unknown token
  // raise en error for illegal token

  
  tokenizer->pos++;
  return token;
}

// Print the token
void printToken( Tokenizer * tokenizer) {

    Token token;
    token = get_next_token(tokenizer);

    while (token.type != -1) {
        printf("Token: %.*s , Type: %d\n", token.len, token.str, token.type);
        token = get_next_token(tokenizer);
    }
}

// main function to test

int main(int argc, char* argv[])
{
    Tokenizer * tokenizer;
    tokenizer = malloc(sizeof(Tokenizer));
    tokenizer->input = malloc(sizeof(char)*100);
    tokenizer->input = "SELECT * FROM table1 WHERE id = 1;";
    tokenizer->pos = 0;

    printToken(tokenizer);
}