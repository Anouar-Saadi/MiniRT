#include <stdio.h>
#include <math.h>

// typedef struct s_lt
// {
//     int nb;
//     struct s_light *next;
// } t_l;
// typedef struct s_light
// {
//     int nb;
//     struct s_light *next;
// } t_light;

// t_light *add_head(t_light *l, int x)
// {
//     t_light *new;

//     new = malloc(sizeof(t_light));
//     new->nb = x;
//     new->next = l;
//     return (new);
// }

// int main()
// {
//     t_light *l;

//     l = malloc(sizeof(t_light));
//     l->nb = 0;
//     l->next = NULL;
//     l = add_head(l, 1);
//     l = add_head(l, 2);
//     while (l)
//     {
//         printf("%d\n", l->nb);
//         l = l->next;
//     }
// }

int main()
{
    printf("|%f|\n", __DBL_EPSILON__);
}