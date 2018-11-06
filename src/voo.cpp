#include <iostream>
#include <string>
#include <vector>
#include "voo.h"

using namespace std;


//---------------------------------------------------------------------------------------
//                               FUNCOES DE VOOS
//---------------------------------------------------------------------------------------

Voo::Voo(Aviao aviao, unsigned int vagas, Data dataVoo, vector<Passageiro *> passageiros, string destino){
	this->aviao = aviao;
	this->vagas = vagas;
	this->dataVoo = dataVoo;
	this->passageiros = passageiros;
	this->destino = destino;
}

Voo::Voo(Aviao aviao, unsigned int vagas, Data dataVoo, string destino){
	this->aviao = aviao;
	this->dataVoo = dataVoo;
	this->vagas = vagas;
	this->destino = destino;
}

Aviao Voo::getAviao() const{
	return aviao;
}

unsigned int Voo::getVagas() const{
	return vagas;
}

vector<Passageiro *> Voo::getPassageiros() const{
	return passageiros;
}

Data Voo::getDataVoo() const{
	return dataVoo;
}

string Voo::getDestino() const{
	return destino;
}

void Voo::adicionaPassageiro(Passageiro* p){
	passageiros.push_back(p);
}

void Voo::decrementaVagas(){
	vagas--;
}

void Voo::incrementaVagas(){
	vagas++;
}

void Voo::removePassageiro(int id) {
	for (size_t i = 0; i < passageiros.size(); i++)
	{
		if (passageiros.at(i)->getId() == id)
		{
			passageiros.erase(passageiros.begin() + i);
		}
	}
}

void Voo::alteraVoo(){
	int opcao;
	bool valid;
	string dataV;
	Data data;

	do{
		valid = false;
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "| Qual elemento deseja alterar?                                                |\n";
		cout << "| 1) Numero de vagas                                                           |\n";
		cout << "| 2) Data do voo                                            				    |\n";
		cout << "| 3) Destino                                                                   |\n";
		cout << "| 4) Terminar                                                                  |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(4);
		cout << endl;
		switch(opcao)
		{
		case 1:
			cout << "Introduza o novo numero de vagas do voo : ";
			cin >> vagas;
			break;

		case 2:
			cout << "Introduza a nova data do voo : ";
			while(!valid){
				valid = true;
				cin >> dataV;
				try{
					data = Data(dataV);
				}
				catch (DataInvalida &datai){
					valid = false;
					cout << datai;
				}
			}

			dataVoo = data;
			break;

		case 3:
			cout << "Introduza o destino do voo : ";
			getline(cin,destino);
			break;

		case 4:
			break;
		}
	}while(opcao!=4);
}
