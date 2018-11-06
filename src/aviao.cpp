#include <iostream>
#include <string>
#include <vector>
#include <cctype> //para o std::isalpha
#include <iomanip>
#include "aviao.h"

using namespace std;
Aviao::Aviao(){}


Aviao::Aviao(int codAviao, string modelo, unsigned int lotacao, float precoPorLugar, int periodicidadeManutencao, Data dataProxManutencao) {
	this->codAviao = codAviao;
	this->modelo = modelo;
	this->precoPorLugar = precoPorLugar;
	this->lotacao = lotacao;
	this->periodicidadeManutencao = periodicidadeManutencao;
	this->dataProxManutencao = dataProxManutencao;
}

unsigned int Aviao::getLotacao() const{
	return lotacao;
}

int Aviao::getCodAviao() const{
	return codAviao;
}

int Aviao::getPrecoPorLugar() const{
	return precoPorLugar;
}

string Aviao::getModelo() const{
	return  modelo;
}

int Aviao::getPeriodicidadeManutencao() const{
	return periodicidadeManutencao;
}

Data Aviao::getDataProxManutencao() const{
	return dataProxManutencao;
}

void Aviao::operator = (Aviao av) {
	codAviao = av.getCodAviao();
	modelo = av.getModelo();
	lotacao = av.getLotacao();
	precoPorLugar = av.getPrecoPorLugar();
	periodicidadeManutencao = av.getPeriodicidadeManutencao();
	dataProxManutencao = av.getDataProxManutencao();
}

bool Aviao::operator < (Aviao av){
	return dataProxManutencao < av.getDataProxManutencao();
}

void Aviao::alteraAviao(BST<Aviao> avioes){
	int opcao;
	bool valid, modeloExiste;
	string dataProximaManutencao;
	Data data;

	do{
		valid = false;
		modeloExiste = false;
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "| Qual elemento deseja alterar?                                                |\n";
		cout << "| 1) Codigo do aviao                                                           |\n";
		cout << "| 2) Modelo                                                                    |\n";
		cout << "| 3) Data da proxima manutencao                                                |\n";
		cout << "| 4) Terminar                                                                  |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(4);
		cout << endl;
		switch (opcao)
		{
		case 1:
			while(true){
				cout << "Introduza o codigo do aviao (1000-9999) : ";
				codAviao = Valid_Cin();

				if( codAviao >= 1000 && codAviao <= 9999){
					break;
				}
				else{
					cout << "Codigo de aviao invalido! ";
				}
			}
			break;
		case 2:
			while (1)
			{
				cout << "Introduza o modelo do aviao : ";
				cin >> modelo;

				if(modelo.length() == 4){

					if( isalpha(modelo[0]) ){
						int substring = stoi(modelo.substr(1));

						if( substring >= 0 && substring <= 999){
							BSTItrIn<Aviao> it(avioes);
							while (!it.isAtEnd())
							{
								if (it.retrieve().getModelo() == modelo)
								{
									lotacao = it.retrieve().getLotacao();
									periodicidadeManutencao = it.retrieve().getPeriodicidadeManutencao();
									precoPorLugar = it.retrieve().getPrecoPorLugar();
									modeloExiste = true;
									break;
								}

								it.advance();
							}

							if (!modeloExiste)
							{
								cout << "Introduza a lotacao do aviao : ";
								lotacao = Valid_Cin();
								cout << "Introduza o preco do bilhete do aviao : ";
								precoPorLugar = Valid_Cin();
								cout << "Introduza a periodicidade de manutencao : ";
								periodicidadeManutencao = Valid_Cin();
								break;
							}
							else
							{
								cout << "Modelo ja existe.\n";
								cout << "Lotacao do aviao : " << lotacao << endl;
								cout << "Preco do bilhete do aviao : " << precoPorLugar << endl;
								cout << "Periodicidade de manutencao : " << periodicidadeManutencao << endl;
								break;
							}
						}
						else
							cout << "O numero deve estar entre 0 e 999!\n";
					}
					else
						cout << "O codigo do aviao deve comecar por uma letra!\n";
				}
				else
					cout << "O codigo do aviao deve ter 1 letra e 3 digitos!\n";
			}
			break;

		case 3:
			while(!valid){
				valid = true;
				cout << "Introduza a data da proxima manutencao : ";
				cin >> dataProximaManutencao;
				try{
					data = Data(dataProximaManutencao);
				}
				catch (DataInvalida &datai){
					valid = false;
					cout << datai;
				}
			}

			dataProxManutencao = data;
			break;

		case 4:
			break;
		}
	}while (opcao != 4);
}
