#include <test.h>


int ft_is_special(char c)
{
  if (c == '>' || c == '<' || c == '|')
    return (1);
  return (0);
}

int counter_string(char *str)
{
  int count = 0;
  int index = 0;

  while (str[index])
  {
    if (ft_is_special(str[index]))
      count += 2;
    count++;
    index++;
  }
  return (count);
}

char *add_spaces(char *str)
{
  int index;
  int new_index;
  char *new_str;

  index = 0;
  new_index = 0;
  new_str = calloc(counter_string(str) + 1, sizeof(char));
  while (str[index])
  {
    if (ft_is_special(str[index]))
    {
      new_str[new_index++] = INVISIBLE_CHAR;
      new_str[new_index++] = str[index];
      if (ft_is_special(str[index]))
        new_str[new_index++] = str[++index];
      new_str[new_index++] = INVISIBLE_CHAR;
    }
    else
      new_str[new_index++] = str[index];
    index++;
  }
  new_str[new_index] = '\0';
  return (new_str);
}

char *mapping_space(char *line)
{
  int index = 0;
  int active_quote;
  char *new_line;

  new_line = add_spaces(line);
  active_quote = 1;
  while (new_line[index])
  {
    if (new_line[index] == '\'' || new_line[index] == '\"')
      active_quote = !active_quote;
    else if (new_line[index] == ' ' && active_quote)
      new_line[index] = INVISIBLE_CHAR;
    index++;
  }

  return (new_line);
}

char **lexer(char *line)
{
  int index;
  char *temp;
  char **tokens;

  index = 0;
  temp = mapping_space(line);
  tokens = ft_split(temp, INVISIBLE_CHAR);
  while (tokens[index])
  {
    tokens[index] = ft_strtrim(tokens[index], "\"");
    tokens[index] = ft_strtrim(tokens[index], "\'");
    index++;
  }
  return (tokens);
}
