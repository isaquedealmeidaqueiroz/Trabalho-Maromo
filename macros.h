#ifndef MACROS 
#define MACROS

#include  <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>


#define MAXUsers 100 // maximo de usuarios 
#define MaxFilmes 200 // maximo de filmes
#define YY 1
#define XX 1
#define ESQUERDA 75
#define DIREITA 77
#define CIMA 72
#define BAIXO 80
#define ESC 27
#define ENTER 13

#define FILMESTXT   "filmes.txt"
#define USUARIOSTXT "usuarios.txt"

int contadorUsers   = 0;
int contadorFilmes  = 0;
int num_me          = 0;

//botões 
bool pressESQ = false;
bool pressDIR = false;
bool pressCIM = false;
bool pressBAI = false;

bool pressA     = false;
bool pressD     = false;
bool pressW     = false;
bool pressS     = false;
bool pressEnter = false;
bool pressEsc   = false;


typedef struct{
    char nome[255];
    char email[255];
    char cpf[15];
    char senha[15];
    char telefone[15];
    char cargo[50];
}Users;

typedef struct{
    int id;
    char titulo[255];
    char diretor[255];
    int anoLancamento;
    int qtd;
}Filmes;

typedef struct{
    int x;
    int y;
    int vx;
    int vy;
}Seta;

typedef enum{
    CADASTRAR   = 0,
    ENTRAR      = 1
}Opc_inicial;

typedef enum{
    REGISTRAR           = 0,
    REMOVER             = 1,
    LISTAR_FILMES       = 2,
    MY_PERFIL           = 3,
    LISTAR_CLIENTES     = 4
}PERFIL_ADM_ESCOLHA;

typedef enum{
    CONSULTAR           = 0,
    PESQUISAR           = 1,
    SELECIONAR          = 2,
    PEDIDO              = 3,
    PERFIL              = 4
}PERFIL_CLT_ESCOLHA;


#pragma region CLIENT
/*========== FUNÇÕES PARA CADASTRAR O CLIENTE ==========*/
void printar_txt_titulo(int *numero);

/**
 * Cadastra um cliente no sistema.
 * @param client - Ponteiro para o struct Users onde serão armazenados os dados do cliente.
 * @return void
 */
void cadastraCliente(Users *client);

/**
 * Exibe o perfil de um cliente com base no CPF.
 * @param clt - Ponteiro para o struct Users contendo os dados do cliente.
 * @param cpf - String contendo o CPF do cliente.
 * @return void
 */
void perfilClientes(Users *clt, const char *cpf);

void editar_usuario(const char* nome_arquivo, const char* cpf_alvo, const char* novo_nome, const char* novo_email, const char* novo_telefone, const char* nova_senha);

void meuPerfil_client( const char *cpf_busca) ;

void consultarFilmes();

void pesquisarFilmes();

void selecionarTitulo(Users *clt,const char *cpf);

void meuPedido(Users *user, const char *cpf) ;

bool buscaTitulo(const char *filename, const char *tituloProcurado);

#pragma endregion




#pragma region  ADM
/*========== FUNÇÕES PARA O ADMINISTRADOR ==========*/

/**
 * Exibe o perfil de um administrador com base no CPF.
 * @param adm - Ponteiro para o struct Users contendo os dados do administrador.
 * @param cpf - String contendo o CPF do administrador.
 * @return void
 */
void perfilAdm(Users *adm, const char *cpf);

/**
 * Registra um novo filme no sistema.
 * @param filme - Ponteiro para o struct Filmes contendo os dados do filme a ser registrado.
 * @return void
 */
void registar_filme(Filmes *filme);

/**
 * Remove um filme do sistema.
 * @param filme - Ponteiro para o struct Filmes contendo os dados do filme a ser removido.
 * @return void
 */
void remover_filme(Filmes *filme);

/**
 * Lista todos os clientes cadastrados no sistema.
 * @param usuarios - Ponteiro para o struct Users contendo a lista de clientes.
 * @return void
 */
void listar_clientes(Users *usuarios);
#pragma endregion



#pragma region GLOBAIS
/*========== FUNÇÕES GLOBAIS ==========*/

/**
 * Verifica se um CPF é válido.
 * @param cpf - String contendo o CPF a ser verificado.
 * @return bool - Retorna true se o CPF for válido, false caso contrário.
 */
bool verificaCpf(char *cpf);

/**
 * Exibe o menu inicial do sistema.
 * @param usuarios - Ponteiro para o struct Users contendo os dados dos usuários.
 * @return void
 */
void menuInicial(Users *usuarios);

/**
 * Verifica se uma string contém números.
 * @param txt - String a ser verificada.
 * @return int - Retorna 1 se houver números, 0 caso contrário.
 */
int haveNumbers(char *txt);

/**
 * Verifica se uma string contém apenas letras.
 * @param txt - String a ser verificada.
 * @return int - Retorna 1 se contiver apenas letras, 0 caso contrário.
 */
int apenasLetras(char *txt);

/**
 * Verifica se uma string contém apenas números.
 * @param txt - String a ser verificada.
 * @return int - Retorna 1 se contiver apenas números, 0 caso contrário.
 */
int apenasNumeros(char *txt);

/**
 * Valida se o formato de um e-mail é correto.
 * @param email - String contendo o e-mail a ser validado.
 * @return int - Retorna 1 se o e-mail for válido, 0 caso contrário.
 */
int validarEmail(char *email);

/**
 * Valida o formato de um CPF.
 * @param cpf - String contendo o CPF a ser validado.
 * @return bool - Retorna true se o CPF for válido, false caso contrário.
 */
bool validaCpf(const char cpf[]);

/**
 * Valida o formato de um número de telefone.
 * @param tel - String contendo o telefone a ser validado.
 * @return bool - Retorna true se o telefone for válido, false caso contrário.
 */
bool validaTelefone(const char tel[]);

/**
 * Valida o formato de uma senha.
 * @param senha - String contendo a senha a ser validada.
 * @return bool - Retorna true se a senha for válida, false caso contrário.
 */
bool validaSenha(const char senha[]);

/**
 * Permite o acesso ao perfil do usuário.
 * @param usuario - Ponteiro para o struct Users contendo os dados do usuário.
 * @return void
 */
void entarWhatPerfil(Users *usuario);

/**
 * Valida os dados de um usuário conforme o tipo especificado.
 * @param user - Ponteiro para o struct Users contendo os dados do usuário.
 * @param type - String especificando o tipo de validação (ex: "admin" ou "cliente").
 * @return void
 */
void validaUser(Users *user, const char *type);

/**
 * Adiciona filmes ao sistema a partir de um arquivo.
 * @param nomeArquivo - String contendo o nome do arquivo.
 * @param filmes - Ponteiro para o struct Filmes contendo os filmes a serem adicionados.
 * @param quantidade - Número de filmes a serem adicionados.
 * @return void
 */
void addFilmes(const char *nomeArquivo, Filmes *filmes, int quantidade);

/**
 * Adiciona perfis de usuários ao sistema a partir de um arquivo.
 * @param nomeArquivo - String contendo o nome do arquivo.
 * @param usuarios - Ponteiro para o struct Users contendo os usuários a serem adicionados.
 * @param quantidade - Número de usuários a serem adicionados.
 * @return void
 */
void addUsers_profile(const char *nomeArquivo, Users *usuarios, int quantidade);

/**
 * Lista os filmes cadastrados no sistema.
 * @param filme - Ponteiro para o struct Filmes contendo os dados dos filmes.
 * @return void
 */
void listarFilme(Filmes *filme);

void printarFilmesTxt();

void printarTxt(const char *falename,int *numero);
#pragma endregion



#pragma region SETAS
/*========== FUNÇÕES DA SETA ==========*/

/**
 * Define a posição do cursor no terminal.
 * @param x - Coordenada X da posição.
 * @param y - Coordenada Y da posição.
 * @return void
 */
void position(int x, int y);

/**
 * Desenha uma seta na posição especificada.
 * @param seta - Struct contendo as informações da seta.
 * @return void
 */
void desenhaSeta(Seta seta);

/**
 * Apaga uma seta da posição especificada.
 * @param seta - Struct contendo as informações da seta.
 * @return void
 */
void apagaSeta(Seta seta);

/**
 * Atualiza a posição de uma seta.
 * @param seta - Ponteiro para a struct contendo as informações da seta.
 * @return void
 */
void atualizaSeta(Seta *seta);

/**
 * Atualiza a velocidade vertical da seta.
 * @param seta - Ponteiro para a struct contendo as informações da seta.
 * @param vy - Nova velocidade vertical.
 * @return void
 */
void atualizaVelocidade(Seta *seta, int vy);

/**
 * Atualiza a velocidade horizontal da seta.
 * @param seta - Ponteiro para a struct contendo as informações da seta.
 * @param vx - Nova velocidade horizontal.
 * @return void
 */
void atualizaVelocidadeX(Seta *seta, int vx);

/**
 * Redefine a posição e a velocidade da seta para o estado inicial.
 * @param seta - Ponteiro para a struct contendo as informações da seta.
 * @return void
 */
void zeraSeta(Seta *seta);

/**
 * Atualiza o estado dos botões controlados pela seta.
 * @param seta - Ponteiro para a struct contendo as informações da seta.
 * @return bool - Retorna true se a atualização for bem-sucedida, false caso contrário.
 */
bool atualizaBotoes(Seta *seta);

/**
 * Desenha uma opção no menu.
 * @param xx - Coordenada X para a opção.
 * @param yy - Coordenada Y para a opção.
 * @param txt - String contendo o texto da opção.
 * @return void
 */
void desenhaOpcao(int xx, int yy, const char txt[]);

#pragma endregion


void position(int x, int y){
    COORD cor = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cor);
}









#endif