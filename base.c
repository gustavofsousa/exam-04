#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Função para imprimir erros
void print_error(char *str)
{
    while (*str)
        write(2, str++, 1);
}

// Função para lidar com o comando "cd"
int cd(char **argv, int i)
{
    // Verifica se o número de argumentos é diferente de 2
    if (i != 2)
        return (print_error("error: cd: bad arguments"), 1); // Imprime erro e retorna 1
    
    // Tenta mudar para o diretório especificado em argv[1]
    else if (chdir(argv[1]) == -1)
        return (print_error("bla bla"), 1);
    
    return 0;
}

// Função para executar comandos externos
int exec(char **argv, char **envp, int i)
{
    int status;
    int fds[2];
    int has_pipe = (argv[i] && !strcmp(argv[i], "|")); // Verifica se há um pipe no comando

    // Verifica se há pipe e cria o pipe
    if (has_pipe && pipe(fds) == -1)
        return (print_error("pipe error"), 1);
    
    int pid = fork();

    if (pid = == 0) // Se o pid for 0, é o processo filho
    {
        argv[i] = 0; // Define o último argumento como NULL para indicar o fim dos argumentos
        
        if (has_pipe && (dup2(fds[1], 1) == -1 || close(fds[0]) == -1 || close(fds[1]) == -1))
            return (print_error("pipe setup error"), 1)
        
        execve(*argv, argv, envp);
        
        return (print_error("execve error"), 1); // Imprime erro e retorna 1 se execve falhar
    }

    waitpid(pid, &status, 0);

    if (has_pipe && (dup2(fds[0], 0) == -1 || close(fds[0]) == -1 || close(fds[1]) == -1))
        return (print_error("pipe cleanup error"), 1);
    
    return WIFEXITED(status) && WEXITSTATUS(status); // Retorna o status de saída do processo filho
}

int main(int argc, char **argv, char **envp)
{
    int status = 0;
    int i;

    if (argc > 1)
    {
        argv++; // Incrementa o ponteiro para ignorar o nome do programa
        
        while (*argv && *(argv + 1))
        {
            argv++;
            i = 0;

            // Procura pelo próximo ponto-e-vírgula ou pipe no comando
            while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
                i++;

            if (!strcmp(*argv, "cd")) // executar um comando.
                status = cd(argv, i);
            else if (i) // Se houver argumentos no comando
                status = exec(argv, envp, i); // Executa o comando externo

            argv += i; // Incrementa o ponteiro para pular para o próximo comando
        }
    }

    return status;
}

