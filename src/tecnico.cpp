#include <iostream>
#include <string>
#include <vector>
#include "tecnico.h"

using namespace std;

Tecnico::Tecnico(){

}

Tecnico::Tecnico(vector<string> especialidades, int id, Aviao aviao){
	this->especialidades = especialidades;
	this->id = id;
	this->aviao = aviao;
}

vector<string> Tecnico::getEspecialidades() const{
	return especialidades;
}

int Tecnico::getId() const{
	return id;
}

Data Tecnico::getProxManutencao() const{
	return aviao.getDataProxManutencao();
}

Aviao Tecnico::getAviao() const{
	return aviao;
}

void Tecnico::alteraTecnico(BST<Aviao> avioes, vector<Tecnico> tecnicosTemp){
	int opcao;
	bool valid;
	string especialidade;
	bool espExiste;
	char resposta;
	int novoID;
	Data dataProximaManutencao;
	string data;
	int codAviao;

	do{
		valid = false;
		espExiste = true;
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "| Qual elemento deseja alterar?                                                |\n";
		cout << "| 1) Especialidades                                                            |\n";
		cout << "| 2) ID                                                                        |\n";
		cout << "| 3) Aviao atribuido                                                           |\n";
		cout << "| 4) Terminar                                                                  |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(4);
		cout << endl;
		switch(opcao)
		{
		case 1:
			for(size_t i = 0; i < especialidades.size(); i++){
				cout << "Especialidade : " << especialidades.at(i) << endl;
			}

			while(true){
				cout << "Qual especialidade deseja alterar? \n";
				getline(cin,especialidade);

				for(size_t j = 0; j < especialidades.size(); j++){
					espExiste = false;
					if(especialidades.at(j) == especialidade){
						espExiste = true;
						cout << "Para que especialidade quer alterar? \n";
						cin >> especialidade;
						especialidades.at(j) = especialidade;
						break;
					}
				}
				if(espExiste){
					break;
				}
				else{
					cout << "A especialidade introduzida nao existe! \n";
					cout << "Deseja voltar atras? (S/N) \n";
					while(true){
						cin >> resposta;

						if(resposta == 'S'){
							cout << "Carregue no enter para continuar...\n";
							cin.get();
							return;
						}
						else if(resposta == 'N')
							break;
						else
							cout << "Input invalido!\n" << "Pretende voltar atras? (S/N)\n";
					}
				}

			}
			break;

		case 2:
			while(true){
				cout << "Introduza o novo ID do tecnico: \n";
				cin >> novoID;
				if(novoID < 100000 || novoID > 999999){
					cout << "O id do tecnico nao e valido.\n";
					continue;
				}
				id = novoID;
			}
			break;

		case 3:
			while (!valid)
			{
				while(true)
				{
					cout << "Introduza o codigo do aviao (1000-9999) : ";
					codAviao = Valid_Cin();

					if( codAviao >= 1000 && codAviao <= 9999){
						break;
					}
					else{
						cout << "Codigo de aviao invalido! ";
					}
				}

				valid = false;
				BSTItrIn<Aviao> it(avioes);
				while(!it.isAtEnd())
				{
					for (size_t j = 0; j < especialidades.size(); j++)
					{
						if (it.retrieve().getModelo() == especialidades.at(j))
						{
							if (it.retrieve().getCodAviao() == codAviao)
							{
								valid = true;
								for (size_t i = 0; i < tecnicosTemp.size(); i++)
								{
									if (tecnicosTemp.at(i).getAviao().getCodAviao() == it.retrieve().getCodAviao())
									{
										valid = false;
										break;
									}
								}
								if (valid)
								{
									aviao = it.retrieve();
									break;
								}
							}
						}
					}
					if(valid)
						break;

					it.advance();
				}
				if(!valid)
				{
					cout << "O codigo do aviao introduzido ja foi atribuido a outro tecnico ou nao faz parte das especialidades do tecnico. ";
				}
			}
			break;

		case 4:
			break;
		}

	}while (opcao != 4);
}

bool Tecnico::operator < (const Tecnico t) const{
	return aviao.getDataProxManutencao() < t.getProxManutencao();
}

void Tecnico::operator = (Tecnico t){
	id = t.getId();
	aviao = t.getAviao();
	especialidades = t.getEspecialidades();
}
