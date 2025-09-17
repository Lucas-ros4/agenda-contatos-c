//
// Created by lucas on 17/09/2025.
//
#include <stdio.h>
#include <string.h>

typedef struct agendaContatos {
    int numIdentificador;
    char nome[50];
    long numTelefone;
    char email[50];
}Agenda;

//funcao para iniciar a agenda inteira com 0 e nulo
void inicializaAgenda() {
    FILE *arq = fopen("agenda.dat", "wb");

    Agenda agendaNula = {0, "", 0, ""};
    for (int i = 0; i < 100; i++) {
        fwrite(&agendaNula, sizeof(Agenda), 1, arq);
    }
    fclose(arq);
}

void removerContato(int id) {
    FILE *arq = fopen("agenda.dat", "rb+");
    Agenda agendaNula = {0, "", 0, ""};

    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    fseek(arq, (id - 1) * sizeof(Agenda), SEEK_SET);
    fwrite(&agendaNula, sizeof(Agenda), 1, arq);
    fclose(arq);
    printf("Contato removido!.\n");
}

void editarContato(int id) {
    FILE *arq = fopen("agenda.dat", "rb+");
    Agenda agenda;
    fseek(arq, (id - 1) * sizeof(Agenda), SEEK_SET);
    fread(&agenda, sizeof(Agenda), 1, arq);

    if (agenda.numIdentificador == 0) {
        printf("Nenhum contato encontrada com esse ID.\n");
        fclose(arq);
        return;
    }
    printf("Nome atual: %s\nNovo Nome: ", agenda.nome);
    getchar();
    fgets(agenda.nome, 50, stdin);
    agenda.nome[strcspn(agenda.nome, "\n")] = '\0';

    printf("Telefone atual: %ld\nNovo telefone: ", agenda.numTelefone);
    scanf("%ld", &agenda.numTelefone);

    printf("Email atual: %s\nNovo email: ", agenda.email);
    scanf("%s", agenda.email);

    fseek(arq, (id - 1) * sizeof(Agenda), SEEK_SET);
    fwrite(&agenda, sizeof(Agenda), 1, arq);

    fclose(arq);
    printf("Contato editado com sucesso!\n");
}

void adicionarContato(int cont) {
    FILE *arq = fopen("agenda.dat", "rb+"); //nao usar wb pq vai apagar a agenda inteira
    Agenda agenda;
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    agenda.numIdentificador = cont;
    printf("Digite o nome e sobrenome do contato %d: ", cont);
    getchar(); //limpa o enter
    fgets(agenda.nome, 50, stdin);
    agenda.nome[strcspn(agenda.nome, "\n")] = '\0'; //remova o '\n' do final lido pelo fgets
    printf("\nDigite o numero de telefone do contato: ");
    scanf("%ld", &agenda.numTelefone);
    printf("\nDigite o email do contato: ");
    scanf("%s", agenda.email);

    fseek(arq, (cont - 1) * sizeof(Agenda), SEEK_SET);
    fwrite(&agenda, sizeof(Agenda), 1, arq);
    fclose(arq);
    printf("Contato adicionado com sucesso!\n");
}

void listarContatos() {
    FILE *arq = fopen("agenda.dat", "rb");
    Agenda agenda;
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    while (fread(&agenda, sizeof(Agenda), 1, arq)) {
        if (agenda.numIdentificador != 0) {
            printf("ID: %d\n", agenda.numIdentificador);
            printf("Nome: %s\n", agenda.nome);
            printf("Telefone: %ld\n", agenda.numTelefone);
            printf("Email: %s\n", agenda.email);
            printf("\n");
        }

    }
    fclose(arq);
}

void consultaEspecifica(int consult) {
    FILE *arq = fopen("agenda.dat", "rb");
    Agenda agenda;
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
    }
    fseek(arq, (consult - 1) * sizeof(Agenda), SEEK_SET);
    if (fread(&agenda, sizeof(Agenda), 1, arq) == 1) {
        if (agenda.numIdentificador != 0) {
            printf("\n--- Contato encontrado ---\n");
            printf("ID: %d\n", agenda.numIdentificador);
            printf("Nome: %s\n", agenda.nome);
            printf("Telefone: %ld\n", agenda.numTelefone);
            printf("Email: %s\n", agenda.email);
        }
        else {
            printf("Nenhum contato cadastrado com esse ID.\n");
        }
    }
    fclose(arq);

}

int main() {
    int opcao, cont = 0, id;

    do {
        printf("\n1 - Inicializar agenda\n"
               "2 - Adicionar contato\n"
               "3 - Listar contatos\n"
               "4 - Buscar contato especifico\n"
               "5 - Editar contato\n"
               "6 - Remover contato\n"
               "0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inicializaAgenda();
                break;
            case 2:
                cont++;
                adicionarContato(cont);
                break;
            case 3:
                listarContatos();
                break;
            case 4:
                printf("Digite o ID do contato: ");
                scanf("%d", &id);
                consultaEspecifica(id);
                break;
            case 5:
                printf("Digite o ID do contato para editar: ");
                scanf("%d", &id);
                editarContato(id);
                break;
            case 6:
                printf("Digite o ID do contato para remover: ");
                scanf("%d", &id);
                removerContato(id);
                break;
            case 0:
                printf("Termino do programa.\n");
                break;
        }
    }while (opcao != 0);
    return 0;
}
