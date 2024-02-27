#include "../../minirt.h"

int eval_line(char *line)
{
    char **splitted_line;
    int i;

    char **ab = ["A", "C", "L", "sp", "pl" "cy"];

    

    if (!line)
        return 0;
    i = 0;
    splitted_line = ft_split(line, ' ');
    while (splitted_line[i])
    {
        printf("%s \n", splitted_line[i]);
        i++;
    }
    printf("\n");
    return 0;
}



int read_rt(char *filename)
{
    int fd = -1;
    char *line = "";

    if (!ft_strstr(filename, ".rt"))
        return(ft_printf("ERROR AL PROCESAR .RT"), 0);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        ft_printf("Error al abrir %s \n", filename);
    }
    while (line)
    {
        line = get_next_line(fd);
        eval_line(line);
    }
    
    return 0;
}