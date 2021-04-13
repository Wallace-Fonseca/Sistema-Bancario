#include<stdio.h>
#include<stdlib.h>
#include<string.h.>
#include<windows.h> //#include <unistd.h> para linux
#include<time.h>
#include<locale.h>

typedef struct {
    int codigo;
    char nome[50];
    char email[50];
    char cpf[12];
    char dataNascimento[11];
    char dataCadastro[11];
} Cliente;

typedef struct {
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldoTotal; // Saldo + Limite
} Conta;

void menu();
void infoCliente(Cliente cliente);
void infoConta(Conta conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarContas();
float atualizaSaldoTotal(Conta conta);
Conta buscarContaPorNumero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta conta_origem, Conta conta_destino, float valor);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;

int main(){

	system("cls");

    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);

    menu();

    // Retorna codificação padrão do Windows
    SetConsoleOutputCP(CPAGE_DEFAULT);
    return 0;
}

void menu(){
    int opcao = 0;

    printf("###############################################\n");
    printf("##################### ATM #####################\n");
    printf("################## Geek Bank ##################\n");
    printf("###############################################\n\n");


    //printf("Localidade corrente: %s\n", setlocale(LC_ALL,NULL));

    printf("-------------------- MENU --------------------\n\n");
    printf("(1) - Criar Conta: \n");
    printf("(2) - Efetuar Saque:\n");
    printf("(3) - Efetuar Deposito\n");
    printf("(4) - Efetuar Transferencia:\n");
    printf("(5) - Listar Contas:\n");
    printf("(6) - Sair do Sistema:\n\n");

    printf("Selecione uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao){
        case 1:
        criarConta();
        break;
        case 2:
        efetuarSaque();
        break;
        case 3:
        efetuarDeposito();
        break;
        case 4:
        efetuarTransferencia();
        break;
        case 5:
        system("cls");
        listarContas();
        break;
        case 6:
        system("cls");
        printf("Obrigado por Utilizar a ATM GEEK BANK.\n\n");
        printf("Até a próxima.");
        sleep(4);
        system("cls");
        exit(0);
        default:
        printf("Opção Inválida!");
        sleep(3);
        menu();
        break;

    }



}
void infoCliente(Cliente cliente){
    system("cls");
    printf("--------------- Informações do Cliente ----------------\n\n");
    printf("Código: %d\nNome: %s\nData de Nascimento: %s\nCadastro: %s\n\n",
    cliente.codigo,
        strtok(cliente.nome, "\n"),
        strtok(cliente.dataNascimento, "\n"),
        strtok(cliente.dataCadastro, "\n"));
    system("pause");

}
void infoConta(Conta conta){
    
    printf("---------------- Informações da Conta -----------------\n\n");
    printf("Numero da Conta: %d\nCliente: %s\nData de Nascimento: %s\nData de Cadastro: %s\nSaldo Total: %.2f\n\n",
        conta.numero,
        strtok(conta.cliente.nome, "\n"),
        strtok(conta.cliente.dataNascimento, "\n"),
        strtok(conta.cliente.dataCadastro, "\n"),
        conta.saldoTotal);
}
void criarConta(){

	system("cls");
	printf("###############################################\n");
    printf("##################### ATM #####################\n");
    printf("################## Geek Bank ##################\n");
    printf("###############################################\n\n");

	printf("-------------- Criação de Conta --------------\n\n");

    Cliente cliente;

    //Data de Cadastro:
    char dia[3];
    char mes[3];
    char ano[5];
    char data_cadastro[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //dia:
    if(tm.tm_mday < 10){
        sprintf(dia, "0%d", tm.tm_mday); //Se o dia for de 0 a 9 o prograama ira colocar o 0 na frente.
    } else{
        sprintf(dia, "%d", tm.tm_mday);
    }

    //mes:
    if((tm.tm_mon + 1) < 10){
        sprintf(mes, "0%d", tm.tm_mon + 1); //Se o mes for de 0 a 9 o prograama ira colocar o 0 na frente.
    } else {
        sprintf(mes, "%d", tm.tm_mon + 1);
    }

    //ano:
    sprintf(ano, "%d", tm.tm_year + 1900);

    strcpy(data_cadastro, "");
    strcat(data_cadastro, dia); //Strcat = concatenação. Ex: 22
    strcat(data_cadastro, "/"); // 22/
    strcat(data_cadastro, mes); // 22/09
    strcat(data_cadastro, "/"); // 22/09/
    strcat(data_cadastro, ano); // 22/09/2020
    strcat(data_cadastro, "\0"); //Finalizou a string.
    strcpy(cliente.dataCadastro, data_cadastro); //Copia a data_cadastro para Cliente.dataCadastro.

    //Criar o Cliente:
    printf("Informe os dados do Cliente:\n\n");

    cliente.codigo = contador_clientes + 1;

    printf("Nome do Cliente: ");
    fgets(cliente.nome, 50, stdin);
	fflush(stdin);
    printf("\n");

    printf("E-mail do Cliente: ");
    fgets(cliente.email,50, stdin);
	fflush(stdin);
    printf("\n");

    printf("CPF do Cliente: ");
    fgets(cliente.cpf, 12, stdin);
	fflush(stdin);
    printf("\n");

    printf("Data de Nascimento do Cliente: ");
    fgets(cliente.dataNascimento, 11, stdin);
	fflush(stdin);
    printf("\n\n");

    contador_clientes++;

    //Criar Contas:
    contas[contador_contas].numero = contador_contas + 1;
    contas[contador_contas].cliente = cliente;
    contas[contador_contas].saldo = 0.0;
    contas[contador_contas].limite = 0.0;
    contas[contador_contas].saldoTotal = atualizaSaldoTotal(contas[contador_contas]);

    printf("Conta criada com sucesso!\n\n");

    infoConta(contas[contador_contas]);

    contador_contas++;

    system("pause");
    menu();
}

void efetuarSaque(){

    system("cls");
	printf("###############################################\n");
    printf("##################### ATM #####################\n");
    printf("################## Geek Bank ##################\n");
    printf("###############################################\n\n");

	printf("------------------- Saque -------------------\n\n");

    if(contador_contas > 0){
        int numero;
        printf("Informe o Numero da Conta: ");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);

        if(conta.numero == numero){
            float valor;
            printf("\nInforme o valor do saque: ");
            scanf("%f", &valor);
            sacar(conta, valor);
        } else {
            printf("\nNão foi encontrado esta conta: %d.", numero);
        }

    } else {
        printf("\nAinda não existe contas cadastradas no sistema.\n\n");
    }

    sleep(4);
    system("cls");
    menu();
}
void efetuarDeposito(){

    system("cls");
	printf("###############################################\n");
    printf("##################### ATM #####################\n");
    printf("################## Geek Bank ##################\n");
    printf("###############################################\n\n");

	printf("----------------- Deposito -----------------\n\n");

    if(contador_contas > 0){
        int numero;
        printf("Informe o Numero da Conta: ");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);

        if(conta.numero == numero){
            float valor;
            printf("\nInforme o valor do deposito: ");
            scanf("%f", &valor);
            depositar(conta, valor);
        } else {
            printf("\nNão foi encontrado esta conta: %d.", numero);
        }

    } else {
        printf("\nAinda não existe contas cadastradas no sistema.\n");
    }

    sleep(3);
	system("cls");
    menu();
}
void efetuarTransferencia(){
    if(contador_contas > 0){
        int numero_o, numero_d;
        printf("Informe o numero da sua conta: ");
        scanf("%d", &numero_o);

        Conta conta_o = buscarContaPorNumero(numero_o);

        if(conta_o.numero == numero_o){
            printf("Informe o numero da conta destino: ");
            scanf("%d", &numero_d);

            Conta conta_d = buscarContaPorNumero(numero_d);

            if(conta_d.numero == numero_d){
                float valor;
                printf("Informe o valor para tranferencia: ");
                scanf("%f", &valor);

                transferir(conta_o, conta_d, valor);
            } else {
                printf("\nA conta de destino informado: %d. Não foi encontrada!\n", numero_d);
            }

        } else {
            printf("A conta informada: %d. Não foi encontrada!\n", numero_o);
        }

    } else {
        printf("\nAinda não existem contas cadastradas.\n");
    }

    sleep(3);
	system("cls");
    menu();

}
void listarContas(){
    if(contador_contas > 0){
        for(int i = 0; i < contador_contas; i++){
            infoConta(contas[i]);
            printf("\n");
        }
    } else {
        printf("\nNão há contas cadastradas!\n");
    }
    system("pause");
	system("cls");
    menu();
}
float atualizaSaldoTotal(Conta conta){
    return conta.saldo + conta.limite;
}
Conta buscarContaPorNumero(int numero){
    Conta c;
    if(contador_contas > 0){
        for(int i = 0; i < contador_contas; i++){
            if(contas[i].numero == numero){
                c = contas[i];
            }
        }
    } else{
        printf("Não há nenhuma conta cadastrada.\n\n");
    }
    return c;
}

void sacar(Conta conta, float valor){
    if(valor > 0 && conta.saldoTotal >= valor){ //Verifica se o saldo na conta é maior que 0 e se tem saldo disponivel no valor desejado do saque.
        for(int i = 0; i < contador_contas; i++){ //Varre todas as contas para descobrir qual conta deseja sacar.
            if(contas[i].numero == conta.numero){ //Achando a conta pedida.
                if(contas[i].saldo >= valor){ //Verifica se a conta tem o Saldo para poder fazer o saque, sem utilizar o limite.
                    contas[i].saldo = contas[i].saldo - valor; //Retira o valor da conta.
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]); //Atualiza a conta com o valor que foi sacado.
                    printf("\nSaque feito com sucesso.\n\n");
                } else{
                    float restante = contas[i].saldo - valor; //Cria a variavel restante para receber "restante = saldo - valor". Logo o restante vai ser negativo.
                    contas[i].limite = contas[i].limite + restante; //Atualiza o valor do "contas[i]limite = conta[i].limite + restante"
                    contas[i].saldo = 0.0; //Saldo da conta será zero pois foi utilizado todo o valor que tinha lá.
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]); //Atualiza o saldo total.
                    printf("\nSaque efetuado usando o limite com sucesso!\n");
                }
            }
        }

    } else {
        printf("\nValor insuficiente para saque. Tente Novamente.\n\n");
        sleep(2);
    }
}
void depositar(Conta conta, float valor){
    if(contador_contas > 0){
        if(valor > 0){
            for(int i = 0; i < contador_contas; i++){
                if(contas[i].numero == conta.numero){
                    contas[i].saldo = contas[i].saldo + valor;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("\nDepósito efetuado com sucesso.\n\n");
                    sleep(3);
                }
            }
        } else {
            printf("\nErro ao efetuar depósito. Tente novamente.\n\n");
            sleep(3);
        }
    } else{
        printf("\nNão exixte contas cadastradas. Tente Novamente\n\n");
        sleep(3);
    }
}

void transferir(Conta conta_origem, Conta conta_destino, float valor){
    if(contador_contas > 0){
        if(valor > 0 && conta_origem.saldoTotal >= valor){ //Verifica se o valor é maior que 0 e a conta de origem tem saldo total do valor que deseja tranferir
            for(int co = 0; co < contador_contas; co++){ //Procura a conta de origem com as contas ja cadastradas
                if(contas[co].numero == conta_origem.numero){ //Verifica se a conta origem é igual a conta informada.
                    for(int cd = 0; cd < contador_contas; cd++){ //Procura a conta destino com as contas ja cadastradas.
                        if(contas[cd].numero == conta_destino.numero){ //Verifica se as contas de destinos é igual a conta informada.
                            if(contas[co].saldo >= valor){ //Verifica se a conta tem saldo do valor desejado
                                contas[co].saldo = contas[co].saldo - valor; //Atualiza o saldo da conta origem menos o valor que sera transferido
                                contas[cd].saldo = contas[cd].saldo + valor; //Atualiza o sado da conta destino mais o valor que foi transferido
                                contas[co].saldoTotal = atualizaSaldoTotal(contas[co]); //Atualiza saldo total da conta origem
                                contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]); //Atualiza saldo total da conta destino
                                printf("Transferencia realizada com sucesso.\n\n");
                                sleep(3);
                            } else{
                                float restante = contas[co].saldo - valor; //Cria uma variavel restante para receber "restante = contas[co].saldo - valor"
                                contas[co].limite = contas[co].limite + restante; //Atualiza o "contas[co].limite" igual "contas[co".limite + restante]. Lembrando que restante assumira um valor negativo pois o valor do "contas[co].saldo" é inferior ao "valor".
                                contas[co].saldo = 0.0; //Atualiza o valor do saldo da conta.
                                contas[cd].saldo = contas[cd].saldo + valor; //Atualiza o sado da conta destino mais o valor que foi transferido
                                contas[co].saldoTotal = atualizaSaldoTotal(contas[co]); //Atualiza saldo total da conta origem
                                contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]); //Atualiza saldo total da conta destino
                                printf("Transferência realizada com sucesso.\n\n");
                                sleep(3);
                            }
                        }
                    }
                }
            }
        } else{
            printf("Erro ao efetuar a transferencia. Tente Novamente\n\n");
            sleep(3);
        }
    } else{
        printf("Não exixte contas cadastradas. Tente Novamente\n\n");
        sleep(3);
    }
}
