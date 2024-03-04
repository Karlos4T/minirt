#include "../../minirt.h"
/*
int add_asset(char **l, t_scene **sc)
{
    int i;

    i = -1;
    if (l[0] == "A")
        i = 1;
    //    if (ft_matrix_len(l) != 3)
    //        ft_printf("Invalid n of arguments in \"A\" (ambient light) line\n");
    //else if (l[0] == "C")
    //    if (ft_matrix_len(l) != 4)
    //        ft_printf("Invalid n of arguments in \"C\" (camera) line\n");
    //else if (l[0] == "L")
    //    if (ft_matrix_len(l) != 4)
    //        ft_printf("Invalid n of arguments in \"C\" (camera) line\n");
    //else if (ft_strstr(l[0], "sp"))
    //    if (ft_matrix_len(l) != 4)
    //        ft_printf("Invalid n of arguments in \"C\" (camera) line\n");
    //else if (ft_strstr(l[0], "cy"))
    //    if (ft_matrix_len(l) != 4)
    //        ft_printf("Invalid n of arguments in \"C\" (camera) line\n");
    //else if (ft_strstr(l[0], "pl"))

    return 1;
}
*/


int eval_line(char *line)
{
    char **s_line;
    char *str;
    int i;

    if (!line)
        return 0;
    i = 0;
    s_line = ft_split(line, ' ');
    while (s_line[i])
    {
        str = ft_strjoin(s_line[i], " ");
        //if (ft_strstr(ASSETS, str) > 0)
            //add_asset(s_line, &sc);
        free(str);
        i++;
    }
    printf("%s\n", line);
    return 0;
}


int read_rt(char *filename, t_scene *sc)
{
    int fd = -1;
    char *line = "";
    (void) sc;
    if (!ft_strstr(filename, ".rt"))
        return(ft_printf("ERROR AL PROCESAR .RT"), 0);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        ft_printf("Error al abrir %s \n", filename);
    while (line)
    {
        line = get_next_line(fd);
        eval_line(line);
    }
    
    return 0;
}