#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARROS 30
#define MAX_CLIENTE 100

typedef struct Carro {
	int carroExiste;
	char placa[7];
	char modelo[35];
	int ano;
	int estado; //0 - livre, 1 - locado
	int estadoTraducao;
	int quilometragem;
	int estaLocado;
	int locadoPara;
} TCarro;

typedef struct Cliente {
	int clienteExiste;
	char primeiroNome[20];  // var[x] == x define a quantidade de caracteres na string
	char ultimoNome[20];
	char nomeCompleto[40];
	char cpf[12];
	char senha[6];
	char endereco[100];
	int carroLocado;
} TCliente;


int main(){
	int i;

	TCarro carrosLocacao[MAX_CARROS];
	for(i=0; i < MAX_CARROS; i++)
		carrosLocacao[i].carroExiste = 0;	

	carrosLocacao[0].ano = 2003;

	TCliente clienteCadastro[MAX_CLIENTE];
	for(i=0; i < MAX_CLIENTE; i++)
		clienteCadastro[i].clienteExiste = 0;

	int programaRodando = 1;
	while(programaRodando){
		int opcaoMenu = 0;

		printf("\n*************************");
		printf("\n* BEM VINDO AO PROGRAMA *");
		printf("\n*************************");

		printf("\n SELECIONE UMA OPÇÃO");
		printf("\n 1- Cadastrar carro");
		printf("\n 2- Listar todos os carros ");
		printf("\n 3- Excluir carro");
		printf("\n 4- Cadastrar cliente");
		printf("\n 5- Listar todos os clientes");
		printf("\n 6- Excluir cliente");
		printf("\n 7- Locação do carro");
		printf("\n 9- Desligar");

		printf("\nSua opção: ");
		scanf("%d", &opcaoMenu);

		switch (opcaoMenu){

			//OPÇÃO: Cadastrar
			case 1: {

				int vaiSerEsse = -1;
				for (i=0; i < MAX_CARROS; i++){
					if (carrosLocacao[i].carroExiste == 0){ //Significa que este índice do vetor não está em uso.
						vaiSerEsse = i;
						i = MAX_CARROS+1;
					}
				}
				if (vaiSerEsse == -1){ //Vetor está cheio
					printf("\n ERRO: O vetor está cheio. Tente remover alguns carros.\n");
					break;
				} 

				printf("\nInsira a placa [XXX1234]: ");
				scanf("%s", carrosLocacao[vaiSerEsse].placa);
				
				printf("Insira o modelo: ");
				scanf("%s", carrosLocacao[vaiSerEsse].modelo);
				getchar();
				
				printf("Insira o ano: ");
				scanf("%d", &carrosLocacao[vaiSerEsse].ano);
				
				printf("Insira a quilometragem: ");
				scanf("%d", &carrosLocacao[vaiSerEsse].quilometragem);
				carrosLocacao[vaiSerEsse].carroExiste = 1;
				
				// Define carro como livre para ser locado	
				carrosLocacao[vaiSerEsse].estado = 0;

				printf("Carro cadastrado com sucesso no 'banco de dados'.\n");
				break;
			}


			//OPÇÃO: Listar todos os carros
			case 2: {

				printf("\n LISTA DE VEÍCULOS: \n");

				for (i=0; i < MAX_CARROS; i++){
					if (carrosLocacao[i].carroExiste == 1){ //Significa que este índice do vetor está em uso.
						printf("\n**********[ VEÍCULO %d ]**********", i);
						printf("\nPlaca: %c%c%c-%c%c%c%c", carrosLocacao[i].placa[0], carrosLocacao[i].placa[1], carrosLocacao[i].placa[2],carrosLocacao[i].placa[3],carrosLocacao[i].placa[4],carrosLocacao[i].placa[5],carrosLocacao[i].placa[6]);
						printf("\nModelo: %s", carrosLocacao[i].modelo);
						carrosLocacao[i].modelo[strlen(carrosLocacao[i].modelo) - 1] = '\0';
						printf("\nAno: %d ", carrosLocacao[i].ano);
						printf("\nEstado: %d ", carrosLocacao[i].estado);
						printf("\nQuilometragem: %d ", carrosLocacao[i].quilometragem);
						if(carrosLocacao[i].estaLocado){
							int traducaoCliente = carrosLocacao[i].locadoPara;
							char clienteTraduzido[41];
							
							// Dizer para qual cliente esse carro está locado
							for(int j = 0; j < sizeof(clienteCadastro); j++){
								if(i == traducaoCliente){
									clienteTraduzido = strcat(clienteCadastro[i].primeiroNome, clienteCadastro[i].ultimoNome);
								}
							}
							printf("\nEstado: Locado para %s", clienteTraduzido);
						}else{
							printf("\nEstado: Livre");
						}
						printf("\n*********************************\n");
					}
				}

				break;
			}

			// OPÇÃO: Deletar carros
			case 3: {

				int idDeletarCarro;
				printf("\n Qual o ID do carro que você quer deletar? (999 cancela): \n");
				scanf("%d", &idDeletarCarro);
				if (idDeletarCarro >= 0 && idDeletarCarro < MAX_CARROS){
					carrosLocacao[idDeletarCarro].carroExiste = 0;
				} else {
					printf("\nERRO: ID [%d] não existe. Operação cancelada.\n", idDeletarCarro);
				}

				break;
			}
			
			case 4: {
				
				int vaiSerEssa = -1;
				for (i=0; i < MAX_CLIENTE; i++){
					if (clienteCadastro[i].clienteExiste == 0){ //Significa que este índice do vetor não está em uso.
						vaiSerEssa = i;
						i = MAX_CLIENTE + 1;
					}
				}
				if (vaiSerEssa == -1){ //Vetor está cheio
					printf("\n ERRO: O vetor está cheio. Tente remover alguns clientes.\n");
					break;
				} 

				printf("\nInsira o primeiro nome: ");
				scanf("%s", clienteCadastro[vaiSerEssa].primeiroNome);
				getchar();
				
				printf("Insira o ultimo nome: ");
				scanf("%s", clienteCadastro[vaiSerEssa].ultimoNome);
				getchar();
				
				strcpy(clienteCadastro[vaiSerEssa].nomeCompleto, clienteCadastro[vaiSerEssa].primeiroNome);
				strcat(clienteCadastro[vaiSerEssa].nomeCompleto, ' '); 
				strcat(clienteCadastro[vaiSerEssa].nomeCompleto, clienteCadastro[vaiSerEssa].ultimoNome);

				printf("Insira o CPF (somente números): ");
				scanf("%s", clienteCadastro[vaiSerEssa].cpf);
				getchar();
				if(strlen(clienteCadastro[vaiSerEssa].cpf) != 11){
					printf("\nEntrada inválida, insira o CPF novamente: ");

				}

				printf("Crie uma senha de 6 dígitos: ");
				scanf("%s", clienteCadastro[vaiSerEssa].senha);
				getchar();
				
				printf("Insira seu endereço: ");
				scanf("%s", clienteCadastro[vaiSerEssa].endereco);
				getchar();
				
				clienteCadastro[vaiSerEssa].clienteExiste = 1;

				printf("Cliente cadastrado com sucesso no banco de dados.");
				break;

			}

			//OPÇÃO: Listar todos os clientes
			case 5: {

				printf("\n LISTA DE CLIENTES: \n");

				for (i=0; i < MAX_CLIENTE; i++){
					if (clienteCadastro[i].clienteExiste == 1){ //Significa que este índice do vetor está em uso.
						printf("\n**********[ CLIENTE %d ]**********", i);
						printf("\nPrimeiro nome: %s", clienteCadastro[i].primeiroNome);
						printf("Último nome: %s", clienteCadastro[i].ultimoNome);
						printf("CPF: %s ", clienteCadastro[i].cpf);
						printf("\nSenha: %c%c%c-%c%c%c", clienteCadastro[i].senha[0], clienteCadastro[i].senha[1], clienteCadastro[i].senha[2],clienteCadastro[i].senha[3],clienteCadastro[i].senha[4],clienteCadastro[i].senha[5]);
						printf("\nEndereço: %s ", clienteCadastro[i].endereco);
						printf("\n*********************************\n");
					}
				}

				break;
			}

			case 6: {

				int idDeletarCliente;
				printf("\n Qual o ID do cliente que você quer deletar? (999 cancela): \n");
				scanf("%d", &idDeletarCliente);
				if (idDeletarCliente >= 0 && idDeletarCliente < MAX_CLIENTE){
					clienteCadastro[idDeletarCliente].clienteExiste = 0;
				} else {
					printf("\nERRO: ID [%d] não existe. Operação cancelada.\n", idDeletarCliente);
				}

				break;
			}

			case 7: {

				int idCliente, idCarro;

				printf("\nInsira o ID do cliente: ");
				scanf("%d", &idCliente);
				if(clienteCadastro[idCliente].carroLocado == 1){
					printf("\nERRO: O cliente %s %s já tem um carro locado. Operação cancelada.\n", clienteCadastro[idCliente].primeiroNome, clienteCadastro[idCliente].ultimoNome);
					break;
				}
				clienteCadastro[idCliente].carroLocado = 1;
				printf("\nInsira o ID do carro: ");
				scanf("%d", &idCarro);
				if (idCarro >= 0 && idCarro < MAX_CARROS){
					if(carrosLocacao[idCarro].estaLocado == 0){
						carrosLocacao[idCarro].locadoPara = idCliente;
						carrosLocacao[idCarro].estaLocado = 1;
					}else{
						printf("\nERRO: Carro %s ID: [%d] já está locado. Operação cancelada.\n", carrosLocacao[idCarro].modelo, carrosLocacao[idCarro]);
						break;
					}
				} else {
					printf("\nERRO: ID [%d] não existe. Operação cancelada.\n", idCarro);
				}
				break;
			}

			case 9: {
				programaRodando = 0;
				break;
			}

			default: {
				printf("\n Opção do menu não existe! Selecione outra. \n");
			}
		}
	}

	printf("\n HASTA LA VISTA BABY \n");


	return 1;
}

