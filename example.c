#include <stdio.h>

int main() {
   char *lineptr = NULL;
   size_t n;
   FILE *file = fopen("small.csv", "r");

   char *line1 = NULL;
   char *line2 = NULL;
   char *line3 = NULL;

   printf("lineptr=%p, n=%d\n", lineptr, n);
   getline(&lineptr, &n, file);
   printf("line1 (first)=%s\n", lineptr);
   printf("lineptr=%p, n=%d\n", lineptr, n);
   line1 = lineptr;
   getline(&lineptr, &n, file);
   printf("line2 (first)=%s\n", lineptr);
   printf("lineptr=%p, n=%d\n", lineptr, n);
   line2 = lineptr;
   getline(&lineptr, &n, file);
   printf("line3 (first)=%s\n", lineptr);
   printf("lineptr=%p, n=%d\n", lineptr, n);
   line3 = lineptr;

   printf("line1=%s\n", line1);
   printf("line2=%s\n", line2);
   printf("line3=%s\n", line3);
}
