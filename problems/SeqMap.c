/*
 Description
For a sequence of single digits, a mapping exists for 1->'a', 2->'b', ...,
26->'z'. Map such a sequence into its string counterparts. In a case that two
possible interpretations exist, for example, 12 can both be 'ab' and 'l',
present both as an answer. If, however, it cannot be represented such as 39, 42,
86, that interpreted mapping shall not exist and be given as an answer.

   Explanation to the solution
   For the first digit, there are two possible choices the program can make.
Consume one or consume two digits (this is under the assumption that every
interpretation exists with no invalid combinations (e.g., no adjacent numbers
like 89, 27, etc.)) This applies on and on, the subsequent mappings can be fed
one or two digits. It is evident that for the first choice, we have f(n-1) +
f(n-2) possibilities that can be explored We can also conclude that, from this,
there are (f(n-2) + f(n-3)) + (f(n-3) + f(n-4)) possibilities that can be
explored This can be applied recursively until f(0) and f(1) which must be 1, a
string of length 0 and 1 only has one possibility (itself).

   We can conclude that there are, in total, fib(n) possible combinations.
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char table[] = {
    0,   'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z', [27 ... 99] = 0,
};

int __attribute__((pure)) fib(int n) {
  int f[] = {0, 1};
  int i = 0;
  for (; i < n; ++i) {
    f[i & 1] += f[(i + 1) & 1];
  }
  return f[i & 1];
}

void _populate(char **wordlist, const char *s, int woffset, int term,
               int wdepth) {
  if (term > 0) {
    for (int i = woffset; i < woffset + fib(term); ++i) {
      wordlist[i][wdepth] = table[*s - '0'];
    }
    if (term != 1) {
      if (table[(*s - '0') * 10 + (s[1] - '0')] == 0) {
        for (int i = woffset + fib(term); i < woffset + fib(term + 1); ++i) {
          wordlist[i][0] = 0;
        }
      }
      for (int i = woffset + fib(term); i < woffset + fib(term + 1); ++i) {
        wordlist[i][wdepth] = table[(*s - '0') * 10 + (s[1] - '0')];
      }
    }
  }
  if (term <= 0) {
    return;
  }
  _populate(wordlist, s + 1, woffset, term - 1, wdepth + 1);
  _populate(wordlist, s + 2, woffset + fib(term), term - 2, wdepth + 1);
}

char **populate(const char *s) {
  char **wordlist = calloc(fib(strlen(s) + 1), sizeof *wordlist);
  for (int i = 0; i < fib(strlen(s) + 1); ++i) {
    wordlist[i] = malloc(strlen(s));
  }

  _populate(wordlist, s, 0, strlen(s), 0);
  return wordlist;
}

int main() {
  char **thing = populate("11111111111111");
  for (int i = 0; i < fib(strlen("11111111111111") + 1); ++i) {
    printf("%s\n", thing[i]);
  }
  return fib(4);
}
