<h1 align="center">exam-04 — microshell</h1>

<p align="center">
  <img src="https://img.shields.io/badge/linguagem-C-blue.svg" alt="Linguagem">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-completo-brightgreen.svg" alt="Status">
</p>

<p align="center">
  Uma implementação mínima de shell — escrita sob condições de exame, de memória, em menos de 3 horas.
</p>

<p align="center">
  <a href="README.md">🇺🇸 Read in English</a>
</p>

---

## Por que este projeto importa

> "Este projeto me ensinou como shells funcionam no nível do sistema operacional — como fork e execve criam processos, como pipes conectam o stdout de um processo ao stdin de outro, e como file descriptors são duplicados e fechados com dup2. Esses são os mecanismos exatos por trás de todo pipeline de CI/CD, todo shell script e todo container runtime."

A capacidade de implementar `fork`, `execve`, `pipe` e `dup2` sob pressão de tempo — sem documentação — prova um entendimento sólido de gerenciamento de processos UNIX.

---

## O que foi construído

Um shell mínimo (`microshell`) que:

- Analisa argumentos de linha de comando passados diretamente via `argv`
- Executa **comandos externos** via `execve`
- Suporta o **built-in `cd`** com relatório de erros adequado
- Suporta **pipes** (`|`) entre comandos
- Suporta **sequências de comandos** (`;`) em uma única invocação
- Reporta todos os erros para `stderr`

### Exemplo de uso

```bash
./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo pronto
```

---

## Um detalhe técnico que se destaca

A função `question_has_pipe()` realiza uma varredura lookahead na lista de argumentos antes de fazer fork — determinando antecipadamente se um pipe é necessário para o grupo de comandos atual. Isso evita criação desnecessária de file descriptors e espelha como shells em produção otimizam seu modelo de execução.

---

## Como funciona

```
argv[] = { "cmd1", "|", "cmd2", ";", "cmd3", NULL }
          └─ fork+pipe ─┘           └─ fork ─┘
```

1. Varre os args até `;` ou `NULL` — essa é uma "sentença"
2. Verifica se existe algum `|` na sentença
3. Se sim: `pipe()` → `fork()` → filho usa `dup2` para conectar stdout ao write-end do pipe
4. Pai lê do read-end do pipe e continua para o próximo comando
5. Se não há pipe: apenas `fork()` + `execve()`

---

## Como usar

```bash
git clone https://github.com/gustavofsousa/exam-04.git
cd exam-04
gcc microshell.c -o microshell
```

### Executando

```bash
./microshell /bin/echo "olá" "|" /usr/bin/tr 'a-z' 'A-Z'
# Saída: OLÁ
```

---

## Estrutura do projeto

```
exam-04/
├── microshell.c    # Implementação completa
├── microshell.h    # Header
└── base.c          # Arquivos de prática/exploração
```

---

## Habilidades demonstradas

- Criação de processos (`fork`, `execve`, `waitpid`)
- Pipes e manipulação de file descriptors (`pipe`, `dup2`, `close`)
- Tratamento de sinais e erros UNIX
- Parsing de shell e processamento de argumentos
- Escrita de C correto e mínimo sob restrição de tempo

---

## Licença

Este projeto foi desenvolvido como parte do currículo da [42 School](https://42.fr).

---

<p align="center">Feito com ☕ na 42 Rio de Janeiro</p>
