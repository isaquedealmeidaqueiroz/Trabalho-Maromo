
# Projeto: Alocadora de Filmes

Este é um projeto de um sistema para gerenciar uma locadora de filmes. Ele foi desenvolvido em C e implementa funcionalidades básicas para manipulação de dados de filmes, usuários e aluguéis, com uma interface baseada em terminal.

## Funcionalidades

- Cadastro de filmes e usuários.
- Registro de aluguéis e devoluções.
- Navegação pelo sistema utilizando setas do teclado.
- Gerenciamento básico de arquivos para persistência de dados.

## Estrutura do Projeto

- **`alocadora.c`**: Arquivo principal que implementa a lógica do sistema.
- **`macros.h`**: Arquivo de cabeçalho com definições e macros usadas no projeto.
- **`output/`**: Diretório contendo executáveis e arquivos gerados durante a execução, como `filmes.txt` e `usuarios.txt`.
- **`.vscode/`**: Configurações para o ambiente de desenvolvimento no VS Code.

## Pré-requisitos

- Compilador C (como GCC ou MinGW no Windows).
- Sistema operacional Windows (devido ao uso de bibliotecas específicas, como `windows.h`).

## Como Compilar e Executar

1. Certifique-se de ter um compilador C instalado.
2. Compile o programa com o comando:
   ```sh
   gcc -o alocadora alocadora.c -lconio
./alocadora

Observações
Os dados de filmes e usuários são salvos em arquivos no diretório output.
O sistema utiliza uma interface baseada em terminal e requer teclado para interação.
Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.

Licença
Este projeto está sob a licença MIT. Consulte o arquivo LICENSE para mais detalhes. """

Salvar o conteúdo em um arquivo README.md no diretório do projeto
readme_file_path = os.path.join(extracted_folder_path, 'alocadora_filmes/README.md')

with open(readme_file_path, 'w', encoding='utf-8') as readme_file: readme_file.write(readme_content)

readme_file_path # Retornar o caminho do arquivo criado
