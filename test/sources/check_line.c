// #include <test.h>

// enum type
// {
//   FILENAME,
//   PATH,
// };

// typedef struct s_token
// {
//   char *value;
//   short type;
//   struct s_token *next; 
// } t_token;

// int verify_token(t_token *token, char *value, short type)
// {
//   if (token == NULL)
//     return (0);
//   if (token->value == NULL)
//     return (0);
//   if (strcmp(token->value, value) != 0)
//     return (0);
//   if (token->type != type)
//     return (0);
//   return (1);
// }