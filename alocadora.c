#include "macros.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include <unistd.h>// para utilizar o sleep em segundos




void atualizaSeta(Seta* seta){
  seta->y += seta->vy;
  seta->x += seta->vx;
  if(seta->y < (YY)){ seta->y = (YY);}
}
void atualizaVelocidade(Seta* seta, int vy){
  seta->vy = vy;
}
void atualizaVelocidadeX(Seta* seta, int vx){
  seta->vy = vx;
}
void desenhaOpcao(int xx, int yy,const char txt[]){
  position(xx,yy);
  printf("%s",txt);
}
bool atualizaBotoes(Seta* seta) {
    pressW     = false;
    pressS     = false;
    pressBAI   = false;
    pressCIM   = false;
    pressEnter = false;
    pressEsc   = false;
    int botao = 0;

    if (kbhit() != 0) { 
        botao = getch(); 
        if (botao == -32 || botao == 224) { 
            botao = getch(); 
            switch (botao) {
                case 72: pressCIM = true; break; 
                case 80: pressBAI = true; break; 
            }
        } else {
            switch (botao) {
                case 'w': case 'W': pressW      = true; break;
                case 's': case 'S': pressS      = true; break;
                case 'd': case 'D': pressD      = true; break;
                case 'a': case 'A': pressA      = true; break;
                case ENTER:         pressEnter  = true; break;
                case ESC:           pressEsc    = true; break; 
            }
        }
    } else {
        // Zera velocidade quando nenhuma tecla é pressionada
        seta->vx = 0;
        seta->vy = 0;
    }
    return false; 
}
void desenhaSeta(Seta seta){
  position((XX + 1) + seta.x,YY + seta.y);
  printf("%c", '>');
}
void apagaSeta(Seta seta){
  position(XX + seta.x,YY + seta.y);
  printf(" ");
}
void zeraSeta(Seta* seta){
  seta->x   = 0;
  seta->y   = 0;
  seta->vx  = 0;
  seta->vy  = 0;
}
int haveNumbers(char *txt) {
    int size = strlen(txt);
    for (int i = 0; i < size; i++) {
        if (isdigit(txt[i])) { 
            return 1;
        }
    }
    return 0; 
}
int apenasLetras(char *txt) {
    int size = strlen(txt);
    for (int i = 0; i < size; i++) {
        if (!isalpha(txt[i]) && txt[i] != ' ') { 
            return 0;
        }
    }
    return 1;
}
int apenasNumeros(char *txt) {
    int size = strlen(txt);
    for (int i = 0; i < size; i++) {
        if (!isdigit(txt[i])) { 
            return 0;
        }
    }
    return 1;
}
int validarEmail(char *email) {
    // Domínios válidos com a validação exata para o nome
    const char *dominiosValidos[] = {"@gmail.com", "@hotmail.com", "@outlook.com", NULL};
    int i, j;

    // Verificar se o e-mail contém '@' e se não está no início ou no final
    const char *arroba = strchr(email, '@');
    if (!arroba || arroba == email || arroba[1] == '\0') {
        return 0; // Falha: '@' ausente ou em posição inválida
    }

    // Verificar se o domínio após '@' contém pelo menos um ponto
    const char *ponto = strchr(arroba + 1, '.'); // Procurar o primeiro ponto após o '@'
    if (!ponto || ponto[1] == '\0') {
        return 0; // Falha: domínio inválido (sem ponto ou sem extensão)
    }

    // Verificar se o domínio completo (incluindo @ e .) é um dos domínios válidos
    for (i = 0; dominiosValidos[i] != NULL; i++) {
        if (strstr(email, dominiosValidos[i]) != NULL && strcmp(arroba, strchr(email, '@')) == 0) {
            return 1; // Domínio válido
        }
    }

    return 0; // Falha: domínio inválido (não é @gmail.com, @hotmail.com ou @outlook.com)
}
bool validaCpf(const char cpf[]){
  int size = strlen(cpf);
  if(size != 11) return false;
  return true;
}
bool validaTelefone(const char tel[]){
  int size = strlen(tel);
  if(size != 9) return false;
  return true;
}
bool validaSenha(const char senha[]){
  int size = strlen(senha);
  if(size < 8) return false;
  return true;
}
void cadastraCliente(Users *client) {
    system("cls || clear"); // Limpa a tela
    int xspace = 1;
    // Nome
    do {
        desenhaOpcao(XX + xspace, 1, "Nome:");
        position(XX + xspace, 2);
        fgets(client[contadorUsers].nome, sizeof(client[contadorUsers].nome), stdin);
        client[contadorUsers].nome[strcspn(client[contadorUsers].nome, "\n")] = '\0'; 
        if (!apenasLetras(client[contadorUsers].nome) || strlen(client[contadorUsers].nome) <= 2) {
          position(XX + xspace, 2);
          printf("                                                                          "); 
          position(XX + xspace, 3);
          printf("O nome invalido. Tente novamente.\n");
        } else {
            position(XX + xspace, 3);
            printf("                                                                        "); 
        }
    } while (!apenasLetras(client[contadorUsers].nome) || strlen(client[contadorUsers].nome) <= 2);

    // Email
    do {
        desenhaOpcao(XX + xspace, 3, "Email:");
        position(XX + xspace, 4);
        fgets(client[contadorUsers].email, sizeof(client[contadorUsers].email), stdin);
        client[contadorUsers].email[strcspn(client[contadorUsers].email, "\n")] = '\0'; // Remove o \n da string

        // Validar o e-mail
        if (!validarEmail(client[contadorUsers].email)) {
          position(XX + xspace, 4);
          printf("                                                                         "); 
          position(XX + xspace, 5);
          printf("E-mail invalido!\n");
        } else {
          position(XX + xspace, 5);
          printf("                                                                          "); 
        }
    } while (!validarEmail(client[contadorUsers].email));

    // CPF 
    do {
      desenhaOpcao(XX + xspace, 5, "CPF:");
      position(XX + xspace, 6);
      fgets(client[contadorUsers].cpf, sizeof(client[contadorUsers].cpf), stdin);
      client[contadorUsers].cpf[strcspn(client[contadorUsers].cpf, "\n")] = '\0';

      if (!apenasNumeros(client[contadorUsers].cpf) || !validaCpf(client[contadorUsers].cpf)) {
          position(XX + xspace, 6);
          printf("                                                                          "); 
          position(XX + xspace, 7);
          printf("CPF invalido! Tente novamente.\n");
      } else {
          position(XX + xspace, 7);
          printf("                                                                          "); 
      }
} while (!apenasNumeros(client[contadorUsers].cpf) || !validaCpf(client[contadorUsers].cpf));


    // Telefone 
    do {
      desenhaOpcao(XX + xspace, 7, "Telefone:");
      position(XX + xspace, 8);
      fgets(client[contadorUsers].telefone, sizeof(client[contadorUsers].telefone), stdin);
      client[contadorUsers].telefone[strcspn(client[contadorUsers].telefone, "\n")] = '\0';

        // Validar o telefone
        if (!apenasNumeros(client[contadorUsers].telefone) ||!validaTelefone(client[contadorUsers].telefone)) {
            position(XX + xspace, 8);
            printf("                                                                          "); 
            position(XX + xspace, 9);
            printf("Telefone invalido!\n");
        } else {
            position(XX + xspace, 9);
            printf("                                                                          "); 
        }
    } while (!apenasNumeros(client[contadorUsers].telefone) ||!validaTelefone(client[contadorUsers].telefone));

    // Senha
      do {
        desenhaOpcao(XX + xspace, 9, "Senha:");
        position(XX + xspace, 10);
        fgets(client[contadorUsers].senha, sizeof(client[contadorUsers].senha), stdin);
        client[contadorUsers].senha[strcspn(client[contadorUsers].senha, "\n")] = '\0';

        // Validar a senha
        if (!validaSenha(client[contadorUsers].senha)) {
            position(XX + xspace, 10);
            printf("                                                                          "); 
            position(XX + xspace, 11);
            printf("A senha deve haver ao minino 8 caracteres!\n");
        } else {
            position(XX + xspace, 11);
            printf("                                                                          "); 
        }
    } while (!validaSenha(client[contadorUsers].senha));
    
        Seta set;
        zeraSeta(&set);
        int perfil_user = 1;
        int perfilPosY = YY + 11; // Define a posição Y para as opções de perfil
    do{
        atualizaBotoes(&set);
        if(pressW){if(set.vy !=  1){atualizaVelocidade(&set,-1);}else{atualizaVelocidade(&set,0);}}
        if(pressS){if(set.vy != -1){atualizaVelocidade(&set, 1);}else{atualizaVelocidade(&set,0);}}

        // Desenhando as opções de perfil com altura ajustada
        desenhaOpcao(XX + xspace, perfilPosY,     "|========PERFIL========|\n");
        desenhaOpcao(XX + xspace, perfilPosY + 1, "| 1 - Administrador    |\n");
        desenhaOpcao(XX + xspace, perfilPosY + 2, "| 2 - Cliente          |\n");
        desenhaOpcao(XX + xspace, perfilPosY + 3, "|======================|\n");

        apagaSeta(set);
        atualizaSeta(&set);

        if (set.y > (perfilPosY + 1)) {
            set.y = (perfilPosY + 1);
        }
        if(set.y < perfilPosY){
          set.y = (perfilPosY);
        }

        desenhaSeta(set);

        if (set.y == perfilPosY  && pressEnter) {  // Administrador
            strcpy(client[contadorUsers].cargo, "Administrador");
            perfil_user = 0;
        }
        if (set.y == perfilPosY + 1 && pressEnter) {  // Cliente
            strcpy(client[contadorUsers].cargo, "Cliente");
            perfil_user = 0;
        }
        Sleep(100);
    }while(perfil_user);

    position(1, perfilPosY + 4);
    printf("|== Cadastrado com sucesso ==|");
    contadorUsers++;
    addUsers_profile("usuarios.txt",client,contadorUsers);
    //getchar();
    //sleep(2);

    menuInicial(client); 
}
void addFilmes(const char *nomeArquivo, Filmes *filmes, int quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "w"); // Abrir o arquivo em modo de escrita

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "Lista de Filmes:\n\n");

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "ID: %d\n", filmes[i].id);
        fprintf(arquivo, "Titulo: %s\n", filmes[i].titulo);
        fprintf(arquivo, "Diretor: %s\n", filmes[i].diretor);
        fprintf(arquivo, "Ano de Lancamento: %d\n", filmes[i].anoLancamento);
        fprintf(arquivo, "Quantidade: %d\n", filmes[i].qtd);

        fprintf(arquivo, "----------------------------\n");
    }

    fclose(arquivo); // Fechar o arquivo
    //printf("Dados gravados com sucesso em %s\n", nomeArquivo);
    system("cls");
}
void addUsers_profile(const char *nomeArquivo, Users *usuarios, int quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "w"); // Abrir o arquivo em modo de escrita

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "LISTA DE USUARIOS:\n\n");

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "Cpf: %s\n",     usuarios[i].cpf       );
        fprintf(arquivo, "Nome: %s\n",    usuarios[i].nome      );
        fprintf(arquivo, "Email: %s\n",   usuarios[i].email     );
        fprintf(arquivo, "Senha: %s\n",   usuarios[i].senha     );
        fprintf(arquivo, "Telefone: %s\n",usuarios[i].telefone  );
        fprintf(arquivo, "Cargo: %s\n",   usuarios[i].cargo     );
        fprintf(arquivo, "--------------------------------\n"   );
    }

    fclose(arquivo); // Fechar o arquivo
    system("cls");
}
/*=========perfil do adm ===========*/
void registar_filme(Filmes *filme) {
  system("cls");
    int xspace = 1;

    // Título
    desenhaOpcao(XX + xspace, 1, "Titulo:");
    position(XX + xspace, 2);
    fgets(filme[contadorFilmes].titulo, sizeof(filme[contadorFilmes].titulo), stdin);
    filme[contadorFilmes].titulo[strcspn(filme[contadorFilmes].titulo, "\n")] = '\0';

    // Diretor
    desenhaOpcao(XX + xspace, 3, "Diretor:");
    position(XX + xspace, 4);
    fgets(filme[contadorFilmes].diretor, sizeof(filme[contadorFilmes].diretor), stdin);
    filme[contadorFilmes].diretor[strcspn(filme[contadorFilmes].diretor, "\n")] = '\0';
 
    // Ano de Lançamento
    do {
        desenhaOpcao(XX + xspace, 5, "Ano de Lancamento:");
        position(XX + xspace, 6);
        char anoInput[10];
        fgets(anoInput, sizeof(anoInput), stdin);
        anoInput[strcspn(anoInput, "\n")] = '\0';

        // Validação para verificar se é um número válido
        if (apenasNumeros(anoInput) && strlen(anoInput) == 4) {
            filme[contadorFilmes].anoLancamento = atoi(anoInput);
            break;
        } else {
            position(XX + xspace, 6);
            printf("                                                                          "); 
            position(XX + xspace, 7);
            printf("Ano invalido! Tente novamente.\n");
        }
    } while (1);
    //qtd
    desenhaOpcao(XX + xspace, 7, "Quantidade:");
    position(XX + xspace, 8);
    scanf("%d",&filme->qtd);
    while (getchar() != '\n'); // Limpa o buffer


    filme[contadorFilmes].id = contadorFilmes + 1;

    position(XX + xspace, 10);
    printf("Filme registrado com sucesso! ID: %d\n", filme[contadorFilmes].id);
    sleep(2);
    system("cls");
    contadorFilmes++; // Incrementa o contador de filmes
    addFilmes(FILMESTXT,filme,contadorFilmes);
}
void remover_filme(Filmes *filme){
  system("cls");
  int xspace = 1;
  char filme_remove[255];

  desenhaOpcao(XX + xspace, YY + 0,"Nome do filme que deseja remover:");
  position(XX + xspace, YY + 1);
  fgets(filme_remove,sizeof(filme_remove),stdin);
  filme_remove[strcspn(filme_remove, "\n")] = '\0';

  for(int i = 0; i < contadorFilmes; i++){
    if(strcmp(filme_remove,filme[i].titulo) == 0){
      for (int j = i; j < contadorFilmes - 1; j++) {
        filme[j] = filme[j + 1];
        filme[j].id = j + 1;
      }
      contadorFilmes--;
      printf("Filme \"%s\" removido com sucesso.\n", filme_remove);
      addFilmes("filmes.txt",filme,contadorFilmes);//preciso melhorar isto
      system("cls");
      return;
    }
    sleep(2);
  }
}
void printar_txt_titulo(int *numero){
    FILE *file = fopen(FILMESTXT, "r"); 
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    char line[256]; 
    char titulo[256];
    
    while (fgets(line, sizeof(line), file) != NULL) { 
        // Verifica se a linha contém "Título:"
        if (strstr(line, "Titulo:") != NULL) {
            // Remove "Título: " e copia o título para a variável 'titulo'
            sscanf(line, "Titulo: %[^\n]", titulo); 
            desenhaOpcao(XX + 2, *numero, titulo);  // Chama a função com o título
            (*numero)++;
        }
    }

    fclose(file); 
}
void listarFilme(Filmes *filme){

  system("cls");
  int xspace = 1;
  int num = 2;
    desenhaOpcao(XX + xspace, YY,                 "|==================LISTA DE FILMES=================|");
    printar_txt_titulo(&num);
    desenhaOpcao(XX + xspace, (YY + num) - 1,     "|==================================================|");
    desenhaOpcao(XX + xspace, (YY + num) + 1, "Clique ESC para voltar");
    while (pressEsc != true){
      int botao = 0;
      if (kbhit() != 0) { 
        botao = getch(); 
        switch (botao) {
          case ESC: pressEsc    = true; break; 
        }
      }
        Sleep(100);  // Aguarda, sem travar o fluxo de execução
    }
    system("cls");
}
void listar_clientes(Users *usuarios){
  system("cls");
  int xspace = 1;
  const char *adm = "Administrador";
  do{ 
    int yspace = 0;
    desenhaOpcao(XX + xspace, YY, "Lista de usuarios");
    if(contadorUsers <= 1){
      desenhaOpcao(XX + xspace, YY, "Nao possui nenhum cliente");
      break;
    }
    // Itera sobre os usuários
    for (int i = 0; i < contadorUsers; i++) {
      // Ignora administradores
      if (strcmp(usuarios[i].cargo, adm) == 0) {
        yspace++;
        continue;
      }

    // Exibe o nome do usuário
    desenhaOpcao(XX + xspace, YY + (1 + i - yspace), usuarios[i].nome);
  }

  if (kbhit() != 0)break;

    Sleep(100);
  }while(1);
  Sleep(1000);
  return;
}
void perfilAdm(Users *adm, const char *cpf){
  system("cls");
  int num_me = 0;
  for(int i = 0; i < contadorUsers; i++){
    if(strcmp(adm[i].cpf,cpf) == 0) num_me = i;
  }
        Seta set;
        Filmes filmes[MaxFilmes];
        int xspace = 1;
        zeraSeta(&set);
    do{
        atualizaBotoes(&set);
        if(pressW || pressCIM){if(set.vy !=  1){atualizaVelocidade(&set,-1);}else{atualizaVelocidade(&set,0);}}
        if(pressS || pressBAI){if(set.vy != -1){atualizaVelocidade(&set, 1);}else{atualizaVelocidade(&set,0);}}

        desenhaOpcao(XX + xspace,YY + 0,"|============MENU===============|\n");
        desenhaOpcao(XX + xspace,YY + 1,"| 1 - REGISTRAR FILME           |\n");
        desenhaOpcao(XX + xspace,YY + 2,"| 2 - REMOVER FILME             |\n");
        desenhaOpcao(XX + xspace,YY + 3,"| 3 - LISTAR TODOS FILMES       |\n");
        desenhaOpcao(XX + xspace,YY + 4,"| 4 - VOLTAR                    |\n");
        desenhaOpcao(XX + xspace,YY + 5,"| 5 - LISTAR CLIENTES           |\n");
        desenhaOpcao(XX + xspace,YY + 6,"|===============================|\n");

        position(XX + 50,YY);
        printf("Perfil: %s",adm[num_me].cargo);
        position(XX + 50,YY + 1);
        printf("Nome: %s",adm[num_me].nome);

        apagaSeta(set);
        atualizaSeta(&set);
        if(set.y > (YY + 4)){ set.y = (YY + 4);}
        desenhaSeta(set);

        if(set.y == YY + REGISTRAR && pressEnter){
          registar_filme(filmes);
        }
        if(set.y == YY + REMOVER && pressEnter){
          remover_filme(filmes);
        }
        if(set.y == YY + LISTAR_FILMES && pressEnter){
          listarFilme(filmes);
        }
        if(set.y == YY + MY_PERFIL && pressEnter){
            menuInicial(adm);
        }
        if(set.y == YY + LISTAR_CLIENTES && pressEnter){
            listar_clientes(adm);
        }
            
            

        Sleep(100);
    }while(1);
}

/*=========perfil do client===========*/
void printarFilmesTxt(int *numero){
    FILE *file = fopen(FILMESTXT, "r"); 
    if (file == NULL) {
        perror("Erro ");
        return;
    }
    char line[256]; 
    while (fgets(line, sizeof(line), file) != NULL) { 
        //printf("%s", line); 
        desenhaOpcao(XX + 1,*numero,line);
        (*numero)++;
    }

    fclose(file); 
}
void printarTxt(const char *falename,int *numero){
    FILE *file = fopen(falename, "r"); 
    if (file == NULL) {
        perror("Erro ");
        return;
    }
    char line[256]; 
    while (fgets(line, sizeof(line), file) != NULL) { 
        //printf("%s", line); 
        desenhaOpcao(XX + 1,*numero,line);
        (*numero)++;
    }

    fclose(file); 
}
void consultarFilmes(){
  system("cls");
  int xspace = 1;
  int num = 1;

    desenhaOpcao(XX + xspace, YY + 0, "Filmes Disponiveis: ");
    printarFilmesTxt(&num);
    desenhaOpcao(XX + 1, (YY + num) + 1, "Clique ESC para voltar");
    Sleep(100);
    while (pressEsc != true){
      int botao = 0;
      if (kbhit() != 0) { 
        botao = getch(); 
        switch (botao) {
          case ESC: pressEsc    = true; break; 
        }
      }
        Sleep(100);  // Aguarda, sem travar o fluxo de execução
    }
    system("cls");
}
void buscar_filme(const char *nome_arquivo, const char *valor_busca, const char *criterio) {
    system("cls"); // Limpa a tela
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char linha[256];
    char titulo[100] = "", diretor[100] = "", ano[10] = "", quantidade[10] = "";
    int encontrou = 0;
    int xspace = 2;

    // Exibe a borda inicial
    position(XX + 1, YY + 0);
    printf("|===================FILME DESEJADO===================|");

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Identifica início de um novo filme
        if (strncmp(linha, "ID:", 3) == 0) {
            // Reseta os dados do filme
            memset(titulo, 0, sizeof(titulo));
            memset(diretor, 0, sizeof(diretor));
            memset(ano, 0, sizeof(ano));
            memset(quantidade, 0, sizeof(quantidade));

            // Carrega os dados do filme até a próxima linha separadora ou EOF
            while (fgets(linha, sizeof(linha), arquivo) && strncmp(linha, "----------------------------", 28) != 0) {
                if (strncmp(linha, "Titulo:", 7) == 0) {
                    strcpy(titulo, linha + 8);
                    titulo[strcspn(titulo, "\n")] = '\0'; // Remove o \n
                } else if (strncmp(linha, "Diretor:", 8) == 0) {
                    strcpy(diretor, linha + 9);
                    diretor[strcspn(diretor, "\n")] = '\0'; // Remove o \n
                } else if (strncmp(linha, "Ano de Lancamento:", 18) == 0) {
                    strcpy(ano, linha + 19);
                    ano[strcspn(ano, "\n")] = '\0'; // Remove o \n
                } else if (strncmp(linha, "Quantidade:", 11) == 0) {
                    strcpy(quantidade, linha + 12);
                    quantidade[strcspn(quantidade, "\n")] = '\0'; // Remove o \n
                }
            }

            // Verifica se o filme corresponde ao critério de busca
            if ((strncmp(criterio, "titulo", 6) == 0 && strcmp(titulo, valor_busca) == 0) ||
                (strncmp(criterio, "ano", 3) == 0 && strcmp(ano, valor_busca) == 0) ||
                (strncmp(criterio, "diretor", 7) == 0 && strcmp(diretor, valor_busca) == 0)) {

                // Exibe as informações do filme encontrado
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "Titulo: %s", titulo);
                desenhaOpcao(XX + xspace, YY + 1, buffer);

                snprintf(buffer, sizeof(buffer), "Diretor: %s", diretor);
                desenhaOpcao(XX + xspace, YY + 2, buffer);

                snprintf(buffer, sizeof(buffer), "Ano de Lancamento: %s", ano);
                desenhaOpcao(XX + xspace, YY + 3, buffer);

                snprintf(buffer, sizeof(buffer), "Quantidade: %s", quantidade);
                desenhaOpcao(XX + xspace, YY + 4, buffer);

                desenhaOpcao(XX + xspace, YY + 6, "Clique ESC para voltar");
                encontrou = 1;
               // break; // Encerra a busca após encontrar o filme
            }
        }
    }

    if (!encontrou) {
        position(3, 1);
        printf("Nada foi encontrado");
        desenhaOpcao(XX + xspace, YY + 3, "Clique ESC para voltar");
    }

    fclose(arquivo);
     while (pressEsc != true){
      int botao = 0;
      if (kbhit() != 0) { 
        botao = getch(); 
        switch (botao) {
          case ESC: pressEsc    = true; break; 
        }
      }
        Sleep(100);  // Aguarda, sem travar o fluxo de execução
    }
    system("cls");
}
void pesquisarFilmes(){ // preciso arrumar;
  system("cls");
  char valor_busca[100];
  char criterio[10];

  printf("Digite o Modo da sua busca (titulo/ano/diretor): ");
  fgets(criterio, sizeof(criterio), stdin);
  criterio[strcspn(criterio, "\n")] = '\0'; 

  printf("Digite oque voce esta procurando: ");
  fgets(valor_busca, sizeof(valor_busca), stdin);
  valor_busca[strcspn(valor_busca, "\n")] = '\0'; 

  buscar_filme("filmes.txt", valor_busca, criterio);
  
  while (pressEsc != true){
      int botao = 0;
      if (kbhit() != 0) { 
        botao = getch(); 
        switch (botao) {
          case ESC: pressEsc    = true; break; 
        }
      }
        Sleep(100);  // Aguarda, sem travar o fluxo de execução
    }
    system("cls");
}
//edita os dados do user
void editar_usuario(const char* nome_arquivo, const char* cpf_alvo, const char* novo_nome, const char* novo_email, const char* novo_telefone, const char* nova_senha) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Criar um arquivo temporário para armazenar as alterações
    FILE *arquivo_temp = fopen("temp.txt", "w");
    if (arquivo_temp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int encontrou = 0;  // Flag para verificar se encontramos o CPF correto

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Se encontramos o CPF alvo, alteramos os dados desse usuário
        if (strstr(linha, cpf_alvo) && !encontrou) {
            fprintf(arquivo_temp, "%s", linha);  // Escreve a linha do CPF alvo

            // Agora alteramos as informações desse usuário
            while (fgets(linha, sizeof(linha), arquivo)) {
                if (strstr(linha, "Nome: ")) {
                    fprintf(arquivo_temp, "Nome: %s\n", novo_nome);  // Altera o nome
                } else if (strstr(linha, "Email: ")) {
                    fprintf(arquivo_temp, "Email: %s\n", novo_email);  // Altera o email
                } else if (strstr(linha, "Telefone: ")) {
                    fprintf(arquivo_temp, "Telefone: %s\n", novo_telefone);  // Altera o telefone
                } else if (strstr(linha, "Senha: ")) {
                    fprintf(arquivo_temp, "Senha: %s\n", nova_senha);  // Altera a senha
                } else {
                    fprintf(arquivo_temp, "%s", linha);  // Mantém as outras linhas do usuário
                }
                if (strstr(linha, "Cargo: ")) {
                    break;  // Sai do loop após o fim dos dados desse usuário
                }
            }
            encontrou = 1;
        } else {
            // Se não for o CPF alvo, apenas escreve a linha como está
            fprintf(arquivo_temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(arquivo_temp);

    // Se o CPF foi encontrado e modificado, substituímos o arquivo original pelo temporário
    if (encontrou) {
        remove(nome_arquivo);  // Remove o arquivo original
        rename("temp.txt", nome_arquivo);  // Renomeia o temporário para o original
        //printf("Alteração realizada com sucesso.\n");
    } else {
        printf("CPF nao encontrado para alteracao.\n");
        remove("temp.txt");  // Apaga o arquivo temporário se nada foi alterado
    }
}
// Função para editar informações diretamente no arquivo
void meuPerfil_client(const char *cpf_busca) {
    system("cls");
    Users usuario;  
    int  xspace = 5; 

    // Nome
    do {
        desenhaOpcao(XX + xspace, 1, "Digite o nome:");
        position(XX + xspace, 2);
        fgets(usuario.nome, sizeof(usuario.nome), stdin);  
        usuario.nome[strcspn(usuario.nome, "\n")] = '\0';  

        if (!apenasLetras(usuario.nome) || strlen(usuario.nome) <= 2) {
            position(XX + xspace, 2);
            printf("                                                                          "); 
            position(XX + xspace, 3);
            printf("Nome inválido. Tente novamente.\n");
        } else {
            position(XX + xspace, 3);
            printf("                                                                          ");
        }
    } while (!apenasLetras(usuario.nome) || strlen(usuario.nome) <= 2);

    // Email
    do {
        desenhaOpcao(XX + xspace, 3, "Digite o email:");
        position(XX + xspace, 4);
        fgets(usuario.email, sizeof(usuario.email), stdin);  
        usuario.email[strcspn(usuario.email, "\n")] = '\0';  

        if (!validarEmail(usuario.email)) {
            position(XX + xspace, 4);
            printf("                                                                         "); 
            position(XX + xspace, 5);
            printf("E-mail inválido! Tente novamente.\n");
        } else {
            position(XX + xspace, 5);
            printf("                                                                          ");
        }
    } while (!validarEmail(usuario.email));

    // Senha
    do {
        desenhaOpcao(XX + xspace, 5, "Digite a senha:");
        position(XX + xspace, 6);
        fgets(usuario.senha, sizeof(usuario.senha), stdin);  
        usuario.senha[strcspn(usuario.senha, "\n")] = '\0';  

        if (!validaSenha(usuario.senha)) {
            position(XX + xspace, 6);
            printf("                                                                          "); 
            position(XX + xspace, 7);
            printf("A senha deve ter ao mínimo 8 caracteres! Tente novamente.\n");
        } else {
            position(XX + xspace, 7);
            printf("                                                                          ");
        }
    } while (!validaSenha(usuario.senha));

    // Telefone
    do {
        desenhaOpcao(XX + xspace, 7, "Digite o telefone:");
        position(XX + xspace, 8);
        fgets(usuario.telefone, sizeof(usuario.telefone), stdin);  
        usuario.telefone[strcspn(usuario.telefone, "\n")] = '\0';  

        if (!apenasNumeros(usuario.telefone) || !validaTelefone(usuario.telefone)) {
            position(XX + xspace, 8);
            printf("                                                                          "); 
            position(XX + xspace, 9);
            printf("Telefone inválido! Tente novamente.\n");
        } else {
            position(XX + xspace, 9);
            printf("                                                                          ");
        }
    } while (!apenasNumeros(usuario.telefone) || !validaTelefone(usuario.telefone));

    // Chama a função para editar o usuário
    editar_usuario("usuarios.txt", cpf_busca, usuario.nome, usuario.email, usuario.telefone, usuario.senha);

    system("cls");
}

bool buscaTitulo(const char *filename, const char *tituloProcurado) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo original");
        return false;
    }

    FILE *tempFile = fopen("temp_filmes.txt", "w");
    if (tempFile == NULL) {
        perror("Erro ao criar o arquivo temporário");
        fclose(file);
        return false;
    }

    FILE *alugadoFile = fopen("alugado.txt", "a"); // Append ao arquivo alugado
    if (alugadoFile == NULL) {
        perror("Erro ao criar o arquivo de alugados");
        fclose(file);
        fclose(tempFile);
        return false;
    }

    char line[256];
    bool tituloEncontrado = false;
    bool quantidadeAtualizada = false;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Titulo:") != NULL) {
            char *tituloAtual = strchr(line, ':');
            if (tituloAtual != NULL) {
                tituloAtual = tituloAtual + 1; // Pula o ':'
                while (*tituloAtual == ' ') tituloAtual++; // Ignora espaços extras
                tituloAtual[strcspn(tituloAtual, "\n")] = '\0'; // Remove '\n'

                if (strcmp(tituloAtual, tituloProcurado) == 0) {
                    tituloEncontrado = true;
                    fprintf(alugadoFile, "%s\n", tituloProcurado); // Escreve no arquivo alugado
                }
            }
        }

        if (tituloEncontrado && strstr(line, "Quantidade:") != NULL) {
            int quantidadeAtual = atoi(strchr(line, ':') + 1);
            if (quantidadeAtual > 0) {
                quantidadeAtual--; // Reduz a quantidade
                quantidadeAtualizada = true;
            }
            fprintf(tempFile, "Quantidade: %d\n", quantidadeAtual); // Atualiza a quantidade no temp
            tituloEncontrado = false; // Reseta o flag após processar
        } else {
            // Corrige linhas que podem estar concatenadas
            if (strstr(line, "Diretor:") != NULL) {
                fprintf(tempFile, "\n%s", line); // Adiciona nova linha antes de "Diretor"
            } else {
                fputs(line, tempFile); // Copia outras linhas diretamente para o arquivo temporário
            }
        }
    }

    fclose(file);
    fclose(tempFile);
    fclose(alugadoFile);

    // Substituir o arquivo original pelo temporário
    if (quantidadeAtualizada) {
        if (remove(filename) != 0) {
            perror("Erro ao remover o arquivo original");
            return false;
        }
        if (rename("temp_filmes.txt", filename) != 0) {
            perror("Erro ao renomear o arquivo temporário");
            return false;
        }
        return true;
    } else {
        remove("temp_filmes.txt"); // Limpa arquivo temporário
        return false;
    }
}
void meuPedido(Users *user, const char *cpf) {
    system("cls");
    int num = 2;
    FILE *file = fopen("alugado.txt", "r"); 

    if (file == NULL) {
        desenhaOpcao(XX, YY + 0, "|===========VOCE NAO POSSUI NENHUM PEDIDO=========|");
    } else {
        desenhaOpcao(XX, YY + 0, "|=============MEUS PEDIDOS=============|");
        
        // Verifique se o arquivo está vazio
        fseek(file, 0, SEEK_END); 
        long tamanho = ftell(file); 
        if (tamanho == 0) {
            desenhaOpcao(XX, YY + 1, "|======= SEU ARQUIVO ESTA VAZIO =======|");
        } else {
            fseek(file, 0, SEEK_SET); 
            printarTxt("alugado.txt", &num);
        }

        desenhaOpcao(XX + 1, (YY + num) + 1, "Clique ESC para voltar");
    }

    while (pressEsc != true) {
        int botao = 0;
        if (kbhit() != 0) { 
            botao = getch(); 
            switch (botao) {
                case ESC: pressEsc = true; break; 
            }
        }
        Sleep(100);  
    }
    perfilClientes(user,cpf);
    system("cls");

}
void selecionarTitulo(Users *clt,const char *cpf){
  system("cls");
  char title[255];
  position(2,1);
  printf("Digite o titulo do filmes que deseja comprar: ");
  fgets(title, sizeof(title), stdin);
  title[strcspn(title, "\n")] = '\0'; 
  system("cls");
  if(buscaTitulo("filmes.txt",title)){
        Seta set;
        int xspace = 1;
        zeraSeta(&set);
    do{
        atualizaBotoes(&set);
        if(pressW || pressCIM){if(set.vy !=  1){atualizaVelocidade(&set,-1);}else{atualizaVelocidade(&set,0);}}
        if(pressS || pressBAI){if(set.vy != -1){atualizaVelocidade(&set, 1);}else{atualizaVelocidade(&set,0);}}
        fflush(stdin);
        desenhaOpcao(XX + xspace,YY + 0,"|========MENU========|\n");
        desenhaOpcao(XX + xspace,YY + 1,"| 1 - Alugar         |\n");
        desenhaOpcao(XX + xspace,YY + 2,"| 2 - Cancelar       |\n");
        desenhaOpcao(XX + xspace,YY + 3,"|====================|\n");

        apagaSeta(set);
        atualizaSeta(&set);
        if(set.y > (YY + 1)){ set.y = (YY + 1);}
        desenhaSeta(set);

        if(set.y == YY + 0 && pressEnter){  // cadastrar usuario
            meuPedido(clt,cpf);
        }
        if(set.y == YY + 1 && pressEnter){  // entrar usuario
            remove("alugado.txt");
            return;
        }

        Sleep(100);
    }while(1);
  }else{
    position(2,3);
    printf("Nao possui filmes ou quantidade insulficiente");
  }

}
void perfilClientes(Users *clt,const char *cpf){
  system("cls");
  
  for(int i = 0; i < contadorUsers; i++){
    if(strcmp(clt[i].cpf,cpf) == 0) num_me = i;
  }
        Seta set;
        Filmes filmes[MaxFilmes];
        int xspace = 1;
        zeraSeta(&set);
    do{
        atualizaBotoes(&set);
        if(pressW || pressCIM){if(set.vy !=  1){atualizaVelocidade(&set,-1);}else{atualizaVelocidade(&set,0);}}
        if(pressS || pressBAI){if(set.vy != -1){atualizaVelocidade(&set, 1);}else{atualizaVelocidade(&set,0);}}

        desenhaOpcao(XX + xspace,YY + 0,"|============MENU===============|\n");
        desenhaOpcao(XX + xspace,YY + 1,"| 1 - CONSULTAR FILMES          |\n");
        desenhaOpcao(XX + xspace,YY + 2,"| 2 - PESQUISAR FILMES          |\n");
        desenhaOpcao(XX + xspace,YY + 3,"| 3 - SELECIONAR TITULO         |\n");
        desenhaOpcao(XX + xspace,YY + 4,"| 4 - MEU PEDIDO                |\n");
        desenhaOpcao(XX + xspace,YY + 5,"| 5 - EDITAR PERFIL             |\n");
        desenhaOpcao(XX + xspace,YY + 6,"| 6 - VOLTAR                    |\n");
        desenhaOpcao(XX + xspace,YY + 7,"|===============================|\n");

        position(XX + 50,YY);
        printf("Perfil: %s",clt[num_me].cargo);
        position(XX + 50,YY + 1);
        printf("Nome: %s",clt[num_me].nome);

        apagaSeta(set);
        atualizaSeta(&set);
        if(set.y > (YY + 5)){ set.y = (YY + 5);}
        desenhaSeta(set);

        if(set.y == YY + CONSULTAR  && pressEnter){
          consultarFilmes();
        }
        if(set.y == YY + PESQUISAR  && pressEnter){
          pesquisarFilmes();   
        }
        if(set.y == YY + SELECIONAR && pressEnter){
          selecionarTitulo(clt,cpf);
        }
        if(set.y == YY + PEDIDO     && pressEnter){
          meuPedido(clt,cpf);
        }
        if(set.y == YY + PERFIL     && pressEnter){
            meuPerfil_client(cpf);
        }
        if(set.y == YY + PERFIL + 1 && pressEnter){
            menuInicial(clt);
        }
        Sleep(100);
    }while(1);
}
//valida user
void validaUser(Users *user, const char *type){
  system("cls");
  Users myself;
  const char *adm = "Administrador";
  const char *clt = "Cliente";
  //cpf
  do {
        desenhaOpcao(1, 1, "Digite seu cpf:");

        position(1, 2);
        fgets( myself.cpf, sizeof( myself.cpf), stdin);
        myself.cpf[strcspn( myself.cpf, "\n")] = '\0'; 

        if (!apenasNumeros(myself.cpf) || !validaCpf(myself.cpf)) {
          position(1, 2);
          printf("                                                                          "); 
          position(1, 3);
          printf("O nome deve conter apenas letras. Tente novamente.\n");
        } else {
            position(1, 3);
            printf("                                                                        "); 
        }
    } while (!apenasNumeros(myself.cpf) || !validaCpf(myself.cpf));

  while(1){
    /*================ADM================*/
    if(strcmp(adm,type)== 0){//aqui vai levar pro adm
      for(int i = 0; i <= contadorUsers; i++){
        if(strcmp(user[i].cpf,myself.cpf) == 0){
          if(strcmp(user[i].cargo, type) == 0){//foi bateu a informação
            perfilAdm(user, myself.cpf);
          }
          else{//não foi
            desenhaOpcao(1, 3, "Voce nao e um adiministrador...Clique qualquer tecla");
            if(kbhit() != 0){
              getchar();
              Sleep(200);
              entarWhatPerfil(user);
            }
          }
        }else{
            desenhaOpcao(1, 3, "CPF invalido...Clique qualquer tecla");
            if(kbhit() != 0){
              getchar();
              Sleep(200);
              entarWhatPerfil(user);
          }
        }
      }
    }
    /*================CLIENTE================*/
    if(strcmp(clt,type)== 0){//aqui vai levar pro cliente
      for(int i = 0; i <= contadorUsers; i++){
        if(strcmp(user[i].cpf,myself.cpf) == 0){
          if(strcmp(user[i].cargo, type) == 0){//foi bateu a informação
            perfilClientes(user,myself.cpf);
          }
          else{//não foi
            desenhaOpcao(1, 3, "Voce nao esta cadastrado como cliente...Clique qualquer tecla..Cadastre");
            if(kbhit() != 0){
              getchar();
              Sleep(200);
              entarWhatPerfil(user);
            }
          }
        }else{
           desenhaOpcao(1, 3, "CPF invalido...Clique qualquer tecla");
            if(kbhit() != 0){
             getchar();
              Sleep(200);
              entarWhatPerfil(user);
          }
        }
      }
    }
    Sleep(100);
  }
}
//menu para saber qual usuario sera 
void entarWhatPerfil(Users *usuario){
        fflush(stdin);
        system("cls");
        Seta set;
        int xspace = 1;
        zeraSeta(&set);
        const char *adm = "Administrador";
        const char *clt = "Cliente";
    do{
        atualizaBotoes(&set);
        if(pressW){if(set.vy !=  1){atualizaVelocidade(&set,-1);}else{atualizaVelocidade(&set,0);}}
        if(pressS){if(set.vy != -1){atualizaVelocidade(&set, 1);}else{atualizaVelocidade(&set,0);}}

        desenhaOpcao(XX + xspace,YY + 0,"|=======Seu peril=======|\n");
        desenhaOpcao(XX + xspace,YY + 1,"| 1 - Administrador     |\n");
        desenhaOpcao(XX + xspace,YY + 2,"| 2 - Cliente           |\n");
        desenhaOpcao(XX + xspace,YY + 3,"|=======================|\n");

        apagaSeta(set);
        atualizaSeta(&set);
        if(set.y > (YY + 1)){ set.y = (YY + 1);}
        desenhaSeta(set);

        if(set.y == YY + CADASTRAR && pressEnter){  // entra como adm
          validaUser(usuario, adm);
        }
        if(set.y == YY + ENTRAR && pressEnter){  // entrar como client
          validaUser(usuario, clt);
        }

        Sleep(100);
    }while(1);

}
void menuInicial(Users *usuarios){
        system("cls");
        Seta set;
        int xspace = 1;
        zeraSeta(&set);
    do{
        atualizaBotoes(&set);
        if(pressW || pressCIM){if(set.vy !=  1){atualizaVelocidade(&set,-1);}else{atualizaVelocidade(&set,0);}}
        if(pressS || pressBAI){if(set.vy != -1){atualizaVelocidade(&set, 1);}else{atualizaVelocidade(&set,0);}}
        fflush(stdin);
        desenhaOpcao(XX + xspace,YY + 0,"|========MENU========|\n");
        desenhaOpcao(XX + xspace,YY + 1,"| 1 - Cadastrar      |\n");
        desenhaOpcao(XX + xspace,YY + 2,"| 2 - Entrar         |\n");
        desenhaOpcao(XX + xspace,YY + 3,"|====================|\n");

        apagaSeta(set);
        atualizaSeta(&set);
        if(set.y > (YY + 1)){ set.y = (YY + 1);}
        desenhaSeta(set);

        if(set.y == YY + CADASTRAR && pressEnter){  // cadastrar usuario
          if(contadorUsers < MAXUsers){
            cadastraCliente(usuarios);
          }
        }
        if(set.y == YY + ENTRAR && pressEnter){  // entrar usuario
          if(contadorUsers > 0){ entarWhatPerfil(usuarios);}
          else{
            desenhaOpcao(XX + xspace,YY + 4,"Nao a ninguem cadastrado tente novamente\n");
          }
        }

        Sleep(100);
    }while(1);
}



int main(){
        system("cls");
        Users usuarios[MAXUsers];
        memset(usuarios, 0, sizeof(usuarios));
        menuInicial(usuarios);

    return 0;
}