#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h> 

void titulo();

struct Venda {
    int codigo;
    char nome_produto[100];
    char marca[100];
    int qtd_itens;
    int preco_unitario;
    float preco_total;
    float desconto;
};

enum Operacoes {
    REGISTRAR_VENDA = 1,
    GERAR_RELATORIO,
    FINALIZAR
};

void imprimirVenda(struct Venda venda);
float calcular_preco_total_com_desconto(struct Venda venda); 

// Função titulo
void titulo() {
    printf("|-----------------------------------|\n");
    printf("|          Programa de Vendas       |\n");
    printf("|         Autores:                  |\n");
    printf("|---------------------------------- |\n");
    printf("| Carolina de Jesus Menezes         |\n");
    printf("| Leonardo Henrique Santos Zonta    |\n");
    printf("| Iris da Silva Reis                |\n");
    printf("| Matheus Vitor Ferreira            |\n");
    printf("| Lucas Suares da Silva             |\n");
    printf("|-----------------------------------|\n\n");
}

void registrar_Vendas(struct Venda *vendas, int *num_vendas) {
    struct Venda nova_venda;

    printf("Registrar Venda:\n\n");

    printf("Codigo: ");
    scanf("%d", &nova_venda.codigo);

    printf("Nome: ");
    getchar();
    fgets(nova_venda.nome_produto, sizeof(nova_venda.nome_produto), stdin);

    printf("Marca: ");
    fgets(nova_venda.marca, sizeof(nova_venda.marca), stdin);

    printf("Quantidade de Itens: ");
    scanf("%d", &nova_venda.qtd_itens);

    printf("Preço Unitário: ");
    scanf("%d", &nova_venda.preco_unitario);

    nova_venda.preco_total = (float) (nova_venda.qtd_itens * nova_venda.preco_unitario);
    printf("\nPreço total: %.2f\n", nova_venda.preco_total);
    
    printf("\n");
    system("CLS");
    imprimirVenda(nova_venda);
    char resposta[10];
    printf("Deseja confirmar a venda? (sim/nao): ");
    scanf("%s", resposta);

    if (strcmp(resposta, "sim") == 0) {
        imprimirVenda(nova_venda);
        vendas[*num_vendas] = nova_venda;
        (*num_vendas)++; 
        printf("Venda registrada com sucesso!\n");
    } else {
        printf("Venda cancelada. Retornando ao menu.\n");
    }
}

void imprimirVenda(struct Venda venda) {
    printf("\n");
    printf("Código: %d\n", venda.codigo);
    printf("Nome do Produto: %s\n", venda.nome_produto);
    printf("Marca: %s\n", venda.marca);
    printf("Quantidade de Itens: %d\n", venda.qtd_itens);
    printf("Preço Unitário: %d\n", venda.preco_unitario);
    float preco_total_com_desconto = calcular_preco_total_com_desconto(venda);
    printf("Preço Total com Desconto: %.2f\n", preco_total_com_desconto);
    printf("Desconto: %.2f\n", venda.preco_total - preco_total_com_desconto);
}

float calcular_preco_total_com_desconto(struct Venda venda) {
    float preco_total = venda.preco_unitario * venda.qtd_itens;

    if (venda.qtd_itens >= 3) {
        preco_total *= 0.9; 
    }

    return preco_total;
}

void gerar_relatorio(struct Venda* vendas, int num_vendas) {
    printf("\nRelatório de Vendas:\n\n");
    printf("%-10s%-20s%-15s%-15s%-15s%-15s\n", "Código", "Nome do Produto", "Marca", "Qtd. Itens", "Preço (U)", "Preço Total");
    
    for (int i = 0; i < num_vendas; ++i) {
        printf("%-10d%-20s%-15s%-15d%-15d%-15.2f\n", vendas[i].codigo, vendas[i].nome_produto, vendas[i].marca, vendas[i].qtd_itens, vendas[i].preco_unitario, vendas[i].preco_total);
    }
    printf("\nPressione qualquer tecla para voltar ao menu...\n");
    getchar(); // Limpa o buffer de entrada
    getchar(); // Aguarda a entrada de uma tecla
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    titulo();

    struct Venda vendas[100]; 
    int num_vendas = 0;

    enum Operacoes operacoes;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar nova venda\n");
        printf("2. Gerar relatórios\n");
        // printf("3. Calcular preços\n");
        printf("3. Finalizar venda\n");
        printf("Escolha uma opção: ");
        scanf("%u", &operacoes);

        switch (operacoes) {
            case 1:
                system("CLS");
                registrar_Vendas(vendas, &num_vendas);
                system("CLS");
                break;

            case 2:
                system("CLS");
                gerar_relatorio(vendas, num_vendas);
                system("CLS");

            case 3:
                printf("\nFinalizando o programa.\n");
                break;
            default:
                printf("\nOpção inválida. Escolha novamente.\n");
        }
    } while (operacoes != 3);

    return 0;
}
