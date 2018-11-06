#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "aviao.h"
#include "companhia.h"

using namespace std;


//---------------------------------------------------------------------------------------
//                              FUNCOES DE COMPANHIA
//---------------------------------------------------------------------------------------

Companhia::Companhia(): avioes(Aviao()){

}



//---------------------------------------------------------------------------------------
//                                 FUNCOES DE AVIOES
//---------------------------------------------------------------------------------------

void Companhia::adicionaAviao(){
	int codAviao;
	string modelo;
	char resposta;
	bool existe = true, valid = false, modeloExiste = false;
	int lot;
	int preco;
	int periodManutencao;
	string dataProxManutencao;
	Data data;

	while(true){
		cout << "Introduza o modelo do aviao : ";
		cin >> modelo;

		if(modelo.length() == 4){

			if( isalpha(modelo[0]) ){
				int substring = stoi(modelo.substr(1));

				if( substring >= 0 && substring <= 999){
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

					BSTItrIn<Aviao> it(avioes);
					while(!it.isAtEnd()){
						existe = false;

						if(it.retrieve().getCodAviao() == codAviao){
							existe = true;
							cout << "Esse aviao ja existe!\n" << "Pretende voltar atras? (S/N)\n";

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
						if(existe)
							break;
						if((modelo == it.retrieve().getModelo()) && (!modeloExiste))
						{
							lot = it.retrieve().getLotacao();
							periodManutencao = it.retrieve().getPeriodicidadeManutencao();
							preco = it.retrieve().getPrecoPorLugar();
							modeloExiste = true;
						}

						it.advance();
					}
					if(!existe){
						if (!modeloExiste)
						{
							cout << "Introduza a lotacao do aviao : ";
							lot = Valid_Cin();
							cout << "Introduza o preco do bilhete do aviao : ";
							preco = Valid_Cin();
							cout << "Introduza a periodicidade de manutencao : ";
							periodManutencao = Valid_Cin();
						}
						else
						{
							cout << "Modelo ja existe.\n";
							cout << "Lotacao do aviao : " << lot << endl;
							cout << "Preco do bilhete do aviao : " << preco << endl;
							cout << "Periodicidade de manutencao : " << periodManutencao << endl;
						}
						while(!valid){
							valid = true;
							cout << "Introduza a data da proxima manutencao : ";
							cin >> dataProxManutencao;
							try{
								data = Data(dataProxManutencao);
							}
							catch (DataInvalida &datai){
								valid = false;
								cout << datai;
							}
						}
						Aviao aviao(codAviao,modelo,lot,preco, periodManutencao, dataProxManutencao);
						avioes.insert(aviao);
						cout << "O aviao foi adicionado.\n";
						cout << "Carregue no enter para continuar...\n";
						cin.ignore(10000, '\n');
						cin.get();
						return;
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

}

void Companhia::alteraAviao(){
	int codAviao;
	char resposta;

	while(1)
	{
		BSTItrIn<Aviao> it(avioes);
		if (it.isAtEnd())
		{
			cout << "Nao ha avioes disponiveis para alugar. Carregue no enter para continuar...\n";
			cin.get();
			return;
		}

		cout << "Os avioes disponiveis sao:\n";
		cout << setw(10) << "Modelo" << setw(10) << "Codigo" << setw(20) << "Lotacao" << setw(20) << "Preco por lugar" << setw(30) << "Periodicidade de manutencao" << setw(30) << "Data da proxima manutencao"  << endl;

		while (!it.isAtEnd()){
			cout << setw(9) << it.retrieve().getModelo() << setw(10) << it.retrieve().getCodAviao() << setw(19) << it.retrieve().getLotacao() << setw(16) << it.retrieve().getPrecoPorLugar() << setw(23) << it.retrieve().getPeriodicidadeManutencao() << setw(33) << it.retrieve().getDataProxManutencao().getData() << endl;
			it.advance();
		}

		cout << "introduza o codigo do aviao que deseja alterar: ";
		codAviao = Valid_Cin();

		BSTItrIn<Aviao> it1(avioes);
		while (!it1.isAtEnd()){
			if (it1.retrieve().getCodAviao() == codAviao)
			{
				it1.retrieve().alteraAviao(avioes);
				cout << "O aviao foi alterado.\n";
				cout << "Carregue no enter para continuar...\n";
				cin.ignore();
				cin.get();
				return;
			}

			it1.advance();
		}

		cout << "Esse aviao nao existe!\n" << "Pretende voltar atras? (S/N)\n";
		while(true){
			cin >> resposta;

			if(resposta == 'S'){
				cout << "Nenhum aviao foi alterado.\n";
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

void Companhia::removeAviao(){
	int codigo;
	char resposta;

	while(true){
		cout << "Introduza o codigo do aviao a remover : ";
		cin >> codigo;

		if( codigo >= 1000 && codigo <= 9999){

			BSTItrIn<Aviao> it(avioes);
			while (!it.isAtEnd()){

				if(it.retrieve().getCodAviao() == codigo){
					for (size_t k = 0; k < voos.size(); k++)
					{
						if (codigo == voos.at(k)->getAviao().getCodAviao())
						{
							delete voos.at(k);
							voos.erase(voos.begin() + k);
						}
					}
					avioes.remove(it.retrieve());
					cout << "O aviao foi removido.\n";
					cout << "Carregue no enter para continuar...\n";
					cin.ignore();
					cin.get();
					return;
				}

				it.advance();
			}
			cout << "Esse aviao nao existe!\n" << "Pretende voltar atras? (S/N)\n";
			while(true){
				cin >> resposta;

				if(resposta == 'S'){
					cout << "Nenhum aviao foi removido.\n";
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
		else{
			cout << "Codigo de aviao invalido! ";
		}

	}

}

void Companhia::visualizaAvioes(){
	BSTItrIn<Aviao> it(avioes);
	if (it.isAtEnd())
	{
		cout << "Nao ha avioes disponiveis para alugar. Carregue no enter para continuar...\n";
		cin.get();
		return;
	}

	cout << setw(10) << "Modelo" << setw(10) << "Codigo" << setw(20) << "Lotacao" << setw(20) << "Preco por lugar" << setw(30) << "Periodicidade de manutencao" << setw(30) << "Data da proxima manutencao"  << endl;

	while (!it.isAtEnd()){
		cout << setw(9) << it.retrieve().getModelo() << setw(10) << it.retrieve().getCodAviao() << setw(19) << it.retrieve().getLotacao() << setw(16) << it.retrieve().getPrecoPorLugar() << setw(23) << it.retrieve().getPeriodicidadeManutencao() << setw(33) << it.retrieve().getDataProxManutencao().getData() << endl;
		it.advance();
	}

	cout << "Carregue no enter para continuar...\n";
	cin.get();
}

void Companhia::visualizaProximasManutencoes(){
	BSTItrIn<Aviao> it(avioes);
	if (it.isAtEnd())
	{
		cout << "Nao ha avioes disponiveis para alugar. Carregue no enter para continuar...\n";
		cin.get();
		return;
	}

	cout << "Os avioes disponiveis sao:\n";
	cout << setw(10) << "Modelo" << setw(10) << "Codigo" << setw(20) << setw(30) << "Data da proxima manutencao"  << endl;

	while (!it.isAtEnd()){
		cout << setw(9) << it.retrieve().getModelo() << setw(10) << it.retrieve().getCodAviao() << setw(22) << it.retrieve().getDataProxManutencao().getData() << endl;
		it.advance();
	}

	cout << "Carregue no enter para continuar...\n";
	cin.get();
}



//---------------------------------------------------------------------------------------
//                         FUNCOES DE PASSAGEIROS COM CARTAO
//---------------------------------------------------------------------------------------

void Companhia::adicionaPassageiroCartao(){
	string nomeP, profissaoP;
	int idP;
	string dataNasc;
	bool existe = true, valid = false;
	char resposta;
	Data data;

	while(true){
		cout << "Introduza o id do passageiro (8 digitos): \n";
		idP = Valid_Cin();
		if(idP < 10000000 || idP > 99999999){
			cout << "O id do passageiro nao e valido.\n";
			continue;
		}

		for(unsigned int i = 0; i < passageirosCartao.size(); i++){
			existe = false;

			if(idP == passageirosCartao.at(i)->getId()){
				existe = true;
				cout << "Esse passageiro ja existe!\n" << "Pretende voltar atras? (S/N)\n";

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
			if(existe)
				break;
		}
		if(!existe){
			cout << "Introduza o nome do passageiro : \n";
			getline(cin, nomeP);
			cout << "Introduza a profissao do passageiro : \n";
			getline(cin, profissaoP);
			while (!valid)
			{
				valid = true;
				cout << "Introduza a data de nascimento do passageiro no formato DD/MM/AAAA : \n";
				cin >> dataNasc;
				try{
					data = Data(dataNasc);
				}
				catch (DataInvalida &datai){
					valid = false;
					cout << datai;
				}
			}
			PassageiroCartao *passageiroC = new PassageiroCartao(nomeP,profissaoP,data,0,idP,Data());
			passageirosInativos.insert(passageiroC);
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			return;
		}
	}
}

void Companhia::alteraPassageiroCartao(){
	int idP;
	bool existe = true;
	char resposta;

	while(true){
		cout << "Introduza o id do passageiro (8 digitos): \n";
		idP = Valid_Cin();
		if(idP < 10000000 || idP > 99999999){
			cout << "O id do passageiro nao e valido.\n";
			continue;
		}

		for(unsigned int i = 0; i < passageirosCartao.size(); i++){
			existe = false;

			if(idP == passageirosCartao.at(i)->getId()){
				existe = true;
				passageirosCartao.at(i)->alteraPassageiroCartao();
				cout << "O passageiro foi alterado.\n";
				cout << "Carregue no enter para continuar...\n";
				cin.get();
				return;
			}

		}
		cout << "Esse passageiro nao existe!\n" << "Pretende voltar atras? (S/N)\n";
		while(true){
			cin >> resposta;

			if(resposta == 'S'){
				cout << "Nenhum passageiro foi alterado.\n";
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

void Companhia::removePassageiroCartao(){
	int idP = 0;
	bool existe = true;
	char resposta;

	while(true){
		cout << "Introduza o id do passageiro (8 digitos): \n";
		idP = Valid_Cin();
		if(idP < 10000000 || idP > 99999999){
			cout << "O id do passageiro nao e valido.\n" << "Pretende voltar atras? (S/N)\n";
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
			continue;
		}
		for(unsigned int i = 0; i < passageirosCartao.size(); i++){
			existe = false;

			if(idP == passageirosCartao.at(i)->getId()){
				existe = true;
				delete passageirosCartao.at(i);
				passageirosCartao.erase(passageirosCartao.begin() + i);
				cout << "O passageiro foi removido.\n";
				break;
			}
		}
		if(existe){
			break;
		}
		else{
			cout << "O passageiro nao existe\n" << "Pretende voltar atras? (S/N)\n";
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
}

void Companhia::visualizaPassageirosCartao(){
	cout << setw(15) << "Nome" << setw(39) << "Id" << setw(30) << "Profissao" << setw(30) << "Data Nascimento" << setw(25) << "N Med Viagens" << endl;

	for(unsigned int i = 0; i < passageirosCartao.size(); i++){
		cout << setw(20) << passageirosCartao.at(i)->getNome() << setw(38) << passageirosCartao.at(i)->getId();
		cout << setw(29) << passageirosCartao.at(i)->getProfissao() << setw(17) << passageirosCartao.at(i)->getDataNascimento();
		cout << setw(23) << passageirosCartao.at(i)->getNMedAno() << endl;
	}

	cout << "Carregue no enter para continuar...\n";
	cin.get();
}


void Companhia::alteraPassageiroInativo(){
	int idP;
	char resposta;
	bool existe = true;

	while(true){
		cout << "Introduza o id do passageiro (8 digitos): \n";
		idP = Valid_Cin();

		unordered_set<PassageiroCartao *,hstr,eqstr>::iterator it = passageirosInativos.begin();
		while (it != passageirosInativos.end()){
			existe = false;
			if((*it)->getId() == idP){
				existe = true;
				(*it)->alteraPassageiroCartao();
				break;
			}
			it++;
		}
		if(existe){
			cout << "O passageiro inativo foi alterado.\n";
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			return;
		}
		else{
			cout << "Esse passageiro nao existe!\n" << "Pretende voltar atras? (S/N)\n";
			while(true){
				cin >> resposta;

				if(resposta == 'S'){
					cout << "Nenhum passageiro inativo foi alterado.\n";
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
}

void Companhia::removePassageiroInativo(){
	int idP;
	char resposta;
	bool existe = true;


	while(true){
		cout << "Introduza o id do passageiro (8 digitos): \n";
		idP = Valid_Cin();
		if(idP < 10000000 || idP > 99999999){
			cout << "O id do passageiro nao e valido.\n" << "Pretende voltar atras? (S/N)\n";
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
			continue;
		}
		unordered_set<PassageiroCartao *,hstr,eqstr>::iterator it = passageirosInativos.begin();
		while (it != passageirosInativos.end()){
			existe = false;
			if((*it)->getId() == idP){
				existe = true;
				passageirosInativos.erase(it);
				break;
			}
			it++;
		}
		if(existe){
			cout << "O passageiro inativo foi removido. \n";
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			break;
		}
		else{
			cout << "O passageiro nao existe\n" << "Pretende voltar atras? (S/N)\n";
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

}

void Companhia::visualizaPassageirosInativos(){
	cout << setw(15) << "Nome" << setw(39) << "Id" << setw(30) << "Profissao" << setw(30) << "Data Nascimento" << setw(25) << "N Med Viagens" << endl;

	unordered_set<PassageiroCartao *,hstr,eqstr>::iterator it = passageirosInativos.begin();
	while (it != passageirosInativos.end()){
		cout << setw(20) << (*it)->getNome() << setw(38) << (*it)->getId();
		cout << setw(29) << (*it)->getProfissao() << setw(17) << (*it)->getDataNascimento();
		cout << setw(23) << (*it)->getNMedAno() << endl;

		it++;
	}

	cout << "Carregue no enter para continuar...\n";
	cin.get();
}



//---------------------------------------------------------------------------------------
//                                 FUNCOES DE VOOS
//---------------------------------------------------------------------------------------

void Companhia::adicionaVoo(){
	int codigo;
	bool disponivel = false;
	vector<Aviao> avioesDisponiveis;
	unsigned int lotacao = 0;
	string dataVoo;
	string destino;
	Data data;
	stringstream frase;
	char resposta;
	bool valid = false;

	while (!valid)
	{
		valid = true;
		cout << "Introduza a data do voo: ";
		cin >> dataVoo;
		try{
			data = Data(dataVoo);
		}
		catch (DataInvalida &datai){
			valid = false;
			cout << datai;
		}
	}

	BSTItrIn<Aviao> it(avioes);
	while (!it.isAtEnd())
	{
		disponivel = true;
		for (size_t k = 0; k < voos.size(); k++)
		{
			if (it.retrieve().getCodAviao() == voos.at(k)->getAviao().getCodAviao())
			{
				if(data == voos.at(k)->getDataVoo()){
					disponivel = false;
					break;
				}
				disponivel = true;
			}
		}
		if (disponivel)
		{
			avioesDisponiveis.push_back(it.retrieve());
		}

		it.advance();
	}

	if (avioesDisponiveis.size() == 0)
	{
		cout << "Nao ha avioes disponiveis para alugar. Carregue no enter para continuar...\n";
		cin.get();
		return;
	}

	cout << "Os avioes disponiveis sao:\n";
	cout << setw(10) << "Codigo" << setw(20) << "Lotacao" << setw(20) << "Preco por lugar" << endl;

	for(unsigned int i = 0; i< avioesDisponiveis.size(); i++){
		cout << setw(9) << avioesDisponiveis.at(i).getCodAviao() << setw(19) << avioesDisponiveis.at(i).getLotacao() << setw(16) << avioesDisponiveis.at(i).getPrecoPorLugar() <<endl;
	}


	while(true){
		cout << "Introduza o codigo do aviao : ";
		cin >> codigo;

		for(size_t i = 0; i < avioesDisponiveis.size(); i++){
			if(codigo == avioesDisponiveis.at(i).getCodAviao()){
				Aviao aviao = avioesDisponiveis.at(i);
				lotacao = aviao.getLotacao();

				cout << "Introduza o destino do voo : \n";
				cin >> destino;

				Voo* voo = new Voo(aviao,lotacao,data,destino);
				voos.push_back(voo);
				cout << "Carregue no enter para continuar...\n";
				cin.get();
				return;
			}

		}
		cout << "O aviao nao esta na lista. Deseja voltar atras? (S/N)\n";
		frase.str("");
		frase << "Deseja voltar atras? (S/N)\n";
		resposta = respostaSN(frase.str());
		if (resposta == 'S')
		{
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			return;
		}
	}
	return;
}

void Companhia::alteraVoo(){
	bool valid = false;
	string dataV;
	Data data;
	int codigo;
	char resposta;

	while(true){
		while(!valid){
			valid = true;
			cout << "Introduza a data do voo: ";
			cin >> dataV;
			try{
				data = Data(dataV);
			}
			catch (DataInvalida &datai){
				valid = false;
				cout << datai;
			}
		}

		cout << "Introduza o codigo do aviao: ";
		cin >> codigo;

		for (size_t i = 0;  i < voos.size(); i++)
		{
			if (codigo == voos.at(i)->getAviao().getCodAviao())
			{
				if(data == voos.at(i)->getDataVoo()){
					voos.at(i)->alteraVoo();
					cout << "O voo foi alterado com sucesso. Carregue no enter para continuar...\n";
					cin.get();
					return;
				}
			}
		}
		cout << "Esse voo nao existe!\n" << "Pretende voltar atras? (S/N)\n";
		while(true){
			cin >> resposta;

			if(resposta == 'S'){
				cout << "Nenhum voo foi alterado.\n";
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

void Companhia::removeVoo(){
	int codigo;
	string dataVoo;
	Data data;
	char resposta;
	stringstream frase;
	bool valid = false;

	while(true){
		while (!valid)
		{
			valid = true;
			cout << "Introduza a data do voo: ";
			cin >> dataVoo;
			try{
				data = Data(dataVoo);
			}
			catch (DataInvalida &datai){
				valid = false;
				cout << datai;
			}
		}

		cout << "Introduza o codigo do aviao : ";
		cin >> codigo;


		for (size_t i = 0;  i < voos.size(); i++)
		{
			if (codigo == voos.at(i)->getAviao().getCodAviao())
			{
				if(data == voos.at(i)->getDataVoo()){
					delete voos.at(i);
					voos.erase(voos.begin() + i);
					cout << "O voo foi eliminado com sucesso. Carregue no enter para continuar...\n";
					cin.ignore();
					cin.get();
					return;
				}
			}
		}
		cout << "O voo nao existe. Deseja voltar atras? (S/N)\n";
		frase.str("");
		frase << "Deseja voltar atras? (S/N)\n";
		resposta = respostaSN(frase.str());
		if (resposta == 'S')
		{
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			return;
		}

	}

}

void Companhia::visualizaVoos(){
	for(unsigned int i = 0; i< voos.size(); i++){
		cout << "Codigo: " << voos.at(i)->getAviao().getCodAviao() << endl;
		cout << "Vagas: " << voos.at(i)->getVagas() << endl;
		cout << "Data do voo: " << voos.at(i)->getDataVoo() << endl;
		cout << "Destino: " << voos.at(i)->getDestino() << endl;
		cout << "Passageiros:\n";
		for (size_t j = 0; j < voos.at(i)->getPassageiros().size(); j++)
		{
			cout << "ID: " << voos.at(i)->getPassageiros().at(j)->getId() << setw(20) << "Nome: " << voos.at(i)->getPassageiros().at(j)->getNome() << endl;
		}
		cout << endl;
	}
	cout << "Carregue no enter para continuar...\n";
	cin.get();
}



//---------------------------------------------------------------------------------------
//                               FUNCOES DE RESERVAS
//---------------------------------------------------------------------------------------

void Companhia::reservaComercial(){
	string nome, destino, data;
	int id;
	bool novo = false, valid = false;
	char resposta;
	stringstream frase;
	Data dataVoo;
	vector<Voo*> voosDisponiveis;

	for (size_t i = 0;  i < voos.size(); i++)
	{
		if (voos.at(i)->getVagas() > 0)
		{
			voosDisponiveis.push_back(voos.at(i));
		}
	}
	if (voosDisponiveis.size() == 0)
	{
		cout << "Nao ha voos com vagas disponiveis\n";
		cout << "Carregue no enter para continuar...\n";
		cin.get();
		return;
	}

	cout << "Os voos disponiveis sao:\n";
	cout << setw(10) << "Codigo" << setw(20) << "Vagas" << setw(20) << "Data Voo" << setw(20) << "Destino" << endl;

	for(unsigned int i = 0; i< voosDisponiveis.size(); i++){
		cout << setw(9) << voosDisponiveis.at(i)->getAviao().getCodAviao() << setw(19) << voosDisponiveis.at(i)->getVagas() << setw(19) << voosDisponiveis.at(i)->getDataVoo() << setw(19) << voosDisponiveis.at(i)->getDestino() <<endl;
	}

	while (!novo)
	{
		cout << "Introduza o destino do voo: ";
		getline(cin, destino);

		while (!valid)
		{
			valid = true;
			cout << "Introduza a data do voo: ";
			cin >> data;
			try{
				dataVoo = Data(data);
			}
			catch (DataInvalida &datai){
				valid = false;
				cout << datai;
			}
		}

		for (size_t i = 0; i < voosDisponiveis.size(); i++)
		{
			if ((voosDisponiveis.at(i)->getDestino() == destino) && (dataVoo == voosDisponiveis.at(i)->getDataVoo()))
			{
				while (!novo)
				{
					cin.ignore(10000, '\n');
					cout << "Introduza o nome do passageiro: ";
					getline(cin, nome);

					cout << "Introduza o ID do passageiro (8 digitos): ";
					id = Valid_Cin();
					while ((id < 10000000) || (id > 99999999))
					{
						cout << "ID invalido. O numero tem de ter 8 digitos. Introduza de novo: ";
						id = Valid_Cin();
					}

					novo = true;
					//verificar se ja esta no voo
					for (size_t j = 0; j < voosDisponiveis.at(i)->getPassageiros().size(); j++)
					{
						if (voosDisponiveis.at(i)->getPassageiros().at(j)->getId() == id)
						{
							cout << "O passageiro " << nome << " com o id " << id << " ja esta presente no aviao! Deseja voltar atras? (S/N)\n";
							frase.str("");
							frase << "Deseja voltar atras? (S/N)\n";
							resposta = respostaSN(frase.str());
							if (resposta == 'S')
							{
								cout << "Carregue no enter para continuar...\n";
								cin.get();
								return;
							}
							else
							{
								novo = false;
								break;
							}
						}
					}
					if (!novo)
					{
						cin.ignore(10000, '\n');
						continue;
					}

					for (size_t k = 0; k < passageirosCartao.size(); k++)
					{
						if (passageirosCartao.at(k)->getId() == id)
						{
							if (passageirosCartao.at(k)->getNome() != nome)
							{
								frase.str("");
								frase << "Queria escrever " << passageirosCartao.at(k)->getNome() << "? (S/N)\n";
								cout << "O id fornecido nao corresponde com o nome na nossa base de dados. Queria escrever " << passageirosCartao.at(k)->getNome() << "? (S/N)\n";
								resposta = respostaSN(frase.str());
								if (resposta == 'S')
								{
									novo = false;
								}
								else
								{
									cout << "Deseja voltar atras? (S/N)\n";
									frase.str("");
									frase << "Deseja voltar atras? (S/N)\n";
									resposta = respostaSN(frase.str());
									if (resposta == 'S')
									{
										cout << "Carregue no enter para continuar...\n";
										cin.get();
										return;
									}
									else
									{
										novo = false;
										break;
									}
								}
							}

							//push back passageiro cartao
							passageirosCartao.at(k)->incrementaNMedAno();
							voosDisponiveis.at(i)->adicionaPassageiro(passageirosCartao.at(k));
							voosDisponiveis.at(i)->decrementaVagas();
							if (verify2dias(dataVoo))
							{
								cout << "Preco do lugar (10% desconto): " << passageirosCartao.at(k)->calculaPreco(voos.at(i)->getAviao().getPrecoPorLugar())*10/100 << endl;
							}
							else
							{
								cout << "Preco do lugar: " << passageirosCartao.at(k)->calculaPreco(voos.at(i)->getAviao().getPrecoPorLugar()) << endl;
							}
							cout << "Carregue no enter para continuar...\n";
							cin.get();
							return;
						}
					}

					unordered_set<PassageiroCartao *,hstr,eqstr>::iterator it = passageirosInativos.begin();
					while(it != passageirosInativos.end())
					{
						if ((*it)->getId() == id)
						{
							if ((*it)->getNome() != nome)
							{
								frase.str("");
								frase << "Queria escrever " << (*it)->getNome() << "? (S/N)\n";
								cout << "O id fornecido nao corresponde com o nome na nossa base de dados. Queria escrever " << (*it)->getNome() << "? (S/N)\n";
								resposta = respostaSN(frase.str());
								if (resposta == 'S')
								{
									novo = false;
								}
								else
								{
									cout << "Deseja voltar atras? (S/N)\n";
									frase.str("");
									frase << "Deseja voltar atras? (S/N)\n";
									resposta = respostaSN(frase.str());
									if (resposta == 'S')
									{
										cout << "Carregue no enter para continuar...\n";
										cin.get();
										return;
									}
									else
									{
										novo = false;
										break;
									}
								}
							}

							//push back passageiro cartao
							(*it)->incrementaNMedAno();
							voosDisponiveis.at(i)->adicionaPassageiro(*it);
							voosDisponiveis.at(i)->decrementaVagas();
							passageirosCartao.push_back(*it);
							passageirosInativos.erase(it);

							if (verify2dias(dataVoo))
							{
								cout << "Preco do lugar (10% desconto): " << (*it)->calculaPreco(voos.at(i)->getAviao().getPrecoPorLugar())*10/100 << endl;
							}
							else
							{
								cout << "Preco do lugar: " << (*it)->calculaPreco(voos.at(i)->getAviao().getPrecoPorLugar()) << endl;
							}
							cout << "Carregue no enter para continuar...\n";
							cin.get();
							return;
						}

						it++;
					}

					//criaçao passageiro normal e push back
					if (novo)
					{
						Passageiro *p = new Passageiro(nome, id);
						voosDisponiveis.at(i)->adicionaPassageiro(p);
						voosDisponiveis.at(i)->decrementaVagas();
						if (verify2dias(dataVoo))
						{
							cout << "Preco do lugar (10% desconto): " << voosDisponiveis.at(i)->getAviao().getPrecoPorLugar() - voosDisponiveis.at(i)->getAviao().getPrecoPorLugar()*10/100 << endl;
						}
						else
						{
							cout << "Preco do lugar: " << voosDisponiveis.at(i)->getAviao().getPrecoPorLugar() << endl;
						}
						cout << "Carregue no enter para continuar...\n";
						cin.get();
						return;
					}
				}
			}
		}

		if(novo)
		{
			novo = false;
			cin.ignore(10000, '\n');
			continue;
		}

		cout << "Nao temos voos para esse destino. Deseja voltar atras? (S/N)\n";
		frase.str("");
		frase << "Deseja voltar atras? (S/N)\n";
		resposta = respostaSN(frase.str());
		if (resposta == 'S')
		{
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			return;
		}
		else
		{
			novo = false;
		}
		cin.ignore(10000, '\n');
	}
}

void Companhia::alugaVoo(){
	string nome, destino, dataVoo;
	int id, codAviao;
	bool disponivel = false, novo = false, valid = false;
	char resposta;
	stringstream frase;
	vector<Aviao> avioesDisponiveis;
	Data data;

	while (!valid)
	{
		valid = true;
		cout << "Introduza a data do voo: ";
		cin >> dataVoo;
		try{
			data = Data(dataVoo);
		}
		catch (DataInvalida &data){
			valid = false;
			cout << data;
		}
	}

	BSTItrIn<Aviao> it(avioes);
	while(!it.isAtEnd())
	{
		disponivel = true;
		for (size_t k = 0; k < voos.size(); k++)
		{
			if (it.retrieve().getCodAviao() == voos.at(k)->getAviao().getCodAviao())
			{
				if(data == voos.at(k)->getDataVoo()){
					disponivel = false;
					break;
				}
				disponivel = true;
			}
		}
		if (disponivel)
		{
			avioesDisponiveis.push_back(it.retrieve());
		}

		it.advance();
	}

	if (avioesDisponiveis.size() == 0)
	{
		cout << "Nao ha avioes disponiveis para alugar. Carregue no enter para continuar...\n";
		cin.get();
		return;
	}

	cout << "Os avioes disponiveis sao:\n";
	cout << setw(10) << "Codigo" << setw(20) << "Lotacao" << setw(20) << "Preco por lugar" << endl;

	for(unsigned int i = 0; i< avioesDisponiveis.size(); i++){
		cout << setw(9) << avioesDisponiveis.at(i).getCodAviao() << setw(19) << avioesDisponiveis.at(i).getLotacao() << setw(16) << avioesDisponiveis.at(i).getPrecoPorLugar() <<endl;
	}

	while (!novo)
	{
		cout << "Introduza o codigo de um aviao da lista: ";
		codAviao = Valid_Cin();

		for (size_t i = 0; i < avioesDisponiveis.size(); i++)
		{
			if (codAviao == avioesDisponiveis.at(i).getCodAviao())
			{
				while (!novo)
				{
					cin.ignore(10000, '\n');
					cout << "Introduza o nome do passageiro: ";
					getline(cin, nome);

					cout << "Introduza o ID do passageiro (8 digitos): ";
					id = Valid_Cin();
					while ((id < 10000000) || (id > 99999999))
					{
						cout << "ID invalido. O numero tem de ter 8 digitos. Introduza de novo: ";
						id = Valid_Cin();
					}

					novo = true;
					for (size_t k = 0; k < passageirosCartao.size(); k++)
					{
						if (passageirosCartao.at(k)->getId() == id)
						{
							if (passageirosCartao.at(k)->getNome() != nome)
							{
								frase.str("");
								frase << "Queria escrever " << passageirosCartao.at(k)->getNome() << "? (S/N)\n";
								cout << "O id fornecido nao corresponde com o nome na nossa base de dados. Queria escrever " << passageirosCartao.at(k)->getNome() << "? (S/N)\n";
								resposta = respostaSN(frase.str());
								if (resposta == 'S')
								{
									novo = false;
								}
								else
								{
									cout << "Deseja voltar atras? (S/N)\n";
									frase.str("");
									frase << "Deseja voltar atras? (S/N)\n";
									resposta = respostaSN(frase.str());
									if (resposta == 'S')
									{
										cout << "Carregue no enter para continuar...\n";
										cin.get();
										return;
									}
									else
									{
										novo = false;
										break;
									}
								}
							}

							cin.ignore(10000, '\n');
							cout << "Introduza o destino do voo: ";
							getline(cin, destino);

							Voo *v = new Voo(avioesDisponiveis.at(i), 0, data, destino);

							//push back passageiro cartao
							passageirosCartao.at(k)->incrementaNMedAno();
							v->adicionaPassageiro(passageirosCartao.at(k));
							voos.push_back(v);
							cout << "Preco do aluguer: " << passageirosCartao.at(k)->calculaPreco(v->getAviao().getPrecoPorLugar())*v->getAviao().getLotacao() << endl;
							cout << "Carregue no enter para continuar...\n";
							cin.ignore(10000, '\n');
							cin.get();
							return;
						}
					}

					unordered_set<PassageiroCartao *,hstr,eqstr>::iterator it = passageirosInativos.begin();
					while(it != passageirosInativos.end())
					{
						if ((*it)->getId() == id)
						{
							if ((*it)->getNome() != nome)
							{
								frase.str("");
								frase << "Queria escrever " << (*it)->getNome() << "? (S/N)\n";
								cout << "O id fornecido nao corresponde com o nome na nossa base de dados. Queria escrever " << (*it)->getNome() << "? (S/N)\n";
								resposta = respostaSN(frase.str());
								if (resposta == 'S')
								{
									novo = false;
								}
								else
								{
									cout << "Deseja voltar atras? (S/N)\n";
									frase.str("");
									frase << "Deseja voltar atras? (S/N)\n";
									resposta = respostaSN(frase.str());
									if (resposta == 'S')
									{
										cout << "Carregue no enter para continuar...\n";
										cin.get();
										return;
									}
									else
									{
										novo = false;
										break;
									}
								}
							}

							cin.ignore(10000, '\n');
							cout << "Introduza o destino do voo: ";
							getline(cin, destino);

							Voo *v = new Voo(avioesDisponiveis.at(i), 0, data, destino);

							//push back passageiro cartao
							(*it)->incrementaNMedAno();
							v->adicionaPassageiro(*it);
							voos.push_back(v);
							passageirosCartao.push_back(*it);
							passageirosInativos.erase(it);
							cout << "Preco do aluguer: " << (*it)->calculaPreco(v->getAviao().getPrecoPorLugar())*v->getAviao().getLotacao() << endl;
							cout << "Carregue no enter para continuar...\n";
							cin.ignore(10000, '\n');
							cin.get();
							return;
						}

						it++;
					}

					//criaçao passageiro normal e push back
					if (novo)
					{
						cout << "Introduza o destino do voo: ";
						getline(cin, destino);

						Voo *v = new Voo(avioesDisponiveis.at(i), 0, data, destino);

						Passageiro *p = new Passageiro(nome, id);
						v->adicionaPassageiro(p);
						voos.push_back(v);
						cout << "Preco do alguer: " << v->getAviao().getPrecoPorLugar()*v->getAviao().getLotacao() << endl;
						cout << "Carregue no enter para continuar...\n";
						cin.ignore(10000, '\n');
						cin.get();
						return;
					}
				}
			}
		}
		cout << "Esse aviao nao esta na lista! ";
		cout << "Deseja voltar atras? (S/N)\n";
		frase.str("");
		frase << "Deseja voltar atras? (S/N)\n";
		resposta = respostaSN(frase.str());
		if (resposta == 'S')
		{
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			return;
		}
		else
		{
			novo = false;
		}
	}
}

void Companhia::devolucao(){
	string destino, nome, data;
	Data dataVoo;
	int id;
	bool valid = false, existe = false;
	stringstream frase;
	char resposta;

	if (voos.size() == 0)
	{
		cout << "Nao ha voos marcados.\n";
		cout << "Carregue no enter para continuar...\n";
		cin.ignore(10000, '\n');
		cin.get();
		return;
	}

	cout << "Lista de voos:\n";
	cout << setw(10) << "Codigo" << setw(20) << "Vagas" << setw(18) << "Data Voo" << setw(20) << "Destino" << endl;

	for(unsigned int i = 0; i< voos.size(); i++){
		cout << setw(9) << voos.at(i)->getAviao().getCodAviao() << setw(19) << voos.at(i)->getVagas() << setw(15) << voos.at(i)->getDataVoo() << setw(17) << voos.at(i)->getDestino() <<endl;
	}

	while (!valid)
	{
		existe = false;

		cout << "Introduza o destino do voo: ";
		getline(cin, destino);

		while (!valid)
		{
			valid = true;
			cout << "Introduza a data do voo: ";
			cin >> data;
			try{
				dataVoo = Data(data);
			}
			catch (DataInvalida &datai){
				valid = false;
				cout << datai;
			}
		}

		valid = false;
		while (!valid)
		{
			//introduzir info do passageiro
			cout << "Introduza o ID do passageiro (8 digitos): ";
			id = Valid_Cin();
			while ((id < 10000000) || (id > 99999999))
			{
				cout << "ID invalido. O numero tem de ter 8 digitos. Introduza de novo: ";
				id = Valid_Cin();
			}

			for (size_t i = 0; i < voos.size(); i++)
			{
				if ((voos.at(i)->getDestino() == destino) && (voos.at(i)->getDataVoo() == dataVoo))
				{
					existe = true;
					for (size_t k = 0; k < voos.at(i)->getPassageiros().size(); k++)
					{
						if (voos.at(i)->getPassageiros().at(k)->getId() == id)
						{
							// caso voo alugado
							if ((voos.at(i)->getPassageiros().size() == 1) && (voos.at(i)->getVagas() == 0))
							{
								for (size_t j = 0; j < passageirosCartao.size(); j++)
								{
									if (id == passageirosCartao.at(j)->getId())
									{
										cout << "O voo alugado pelo passageiro " << passageirosCartao.at(j)->getNome() << " com o id " << passageirosCartao.at(j)->getId() << " foi eliminado!\n";
										passageirosCartao.at(j)->decrementaNMedAno();
										cout << "Valor a devolver: " << passageirosCartao.at(j)->calculaPreco(voos.at(i)->getAviao().getPrecoPorLugar())*voos.at(i)->getAviao().getLotacao() << endl;
										voos.erase(voos.begin() + i);
										if (verifyInativo(passageirosCartao.at(j)->getDataUltimoVoo()))
										{
											passageirosInativos.insert(passageirosCartao.at(j));
											delete passageirosCartao.at(j);
											passageirosCartao.erase(passageirosCartao.begin() + j);
										}
										cout << "Carregue no enter para continuar...\n";
										cin.get();
										return;
									}
								}
								cout << "O voo alugado pelo passageiro " << voos.at(i)->getPassageiros().at(k)->getNome() << " com o id " << voos.at(i)->getPassageiros().at(k)->getId() << " foi eliminado!\n";
								cout << "Valor a devolver: " << voos.at(i)->getAviao().getPrecoPorLugar()*voos.at(i)->getAviao().getLotacao() << endl;
								voos.erase(voos.begin() + i);
								cout << "Carregue no enter para continuar...\n";
								cin.get();
								return;
							}

							// caso voo comercial
							for (size_t j = 0; j < passageirosCartao.size(); j++)
							{
								if (id == passageirosCartao.at(j)->getId())
								{
									cout << "O passageiro " << passageirosCartao.at(j)->getNome() << " com o id " << passageirosCartao.at(j)->getId() << " foi eliminado!\n";
									voos.at(i)->removePassageiro(id);
									voos.at(i)->incrementaVagas();
									passageirosCartao.at(j)->decrementaNMedAno();
									cout << "Valor a devolver: " << passageirosCartao.at(j)->calculaPreco(voos.at(i)->getAviao().getPrecoPorLugar()) << endl;
									if (verifyInativo(passageirosCartao.at(j)->getDataUltimoVoo()))
									{
										passageirosInativos.insert(passageirosCartao.at(j));
										delete passageirosCartao.at(j);
										passageirosCartao.erase(passageirosCartao.begin() + j);
									}
									cout << "Carregue no enter para continuar...\n";
									cin.get();
									return;
								}
							}
							cout << "O passageiro " << voos.at(i)->getPassageiros().at(k)->getNome() << " com o id " << voos.at(i)->getPassageiros().at(k)->getId() << " foi eliminado!\n";
							voos.at(i)->removePassageiro(id);
							voos.at(i)->incrementaVagas();
							cout << "Valor a devolver: " << voos.at(i)->getAviao().getPrecoPorLugar() << endl;
							cout << "Carregue no enter para continuar...\n";
							cin.get();
							return;
						}
					}

					cout << "Esse passageiro nao esta incluido na lista de passageiros de nenhum voo. Deseja voltar atras? (S/N)\n";
					frase.str("");
					frase << "Deseja voltar atras? (S/N)\n";
					resposta = respostaSN(frase.str());
					if (resposta == 'S')
					{
						cout << "Carregue no enter para continuar...\n";
						cin.get();
						return;
					}
					else
					{
						valid = false;
					}
				}
			}

			if (!existe)
			{
				cout << "Esse voo nao existe. Deseja voltar atras? (S/N)\n";
				frase.str("");
				frase << "Deseja voltar atras? (S/N)\n";
				resposta = respostaSN(frase.str());
				if (resposta == 'S')
				{
					cout << "Carregue no enter para continuar...\n";
					cin.ignore(10000, '\n');
					cin.get();
					return;
				}
				else
				{
					valid = false;
					break;
				}
			}
		}
		cin.ignore(10000, '\n');
	}
}



//---------------------------------------------------------------------------------------
//                               FUNCOES DOS TECNICOS
//---------------------------------------------------------------------------------------

void Companhia::adicionaTecnico(){
	Data dataProximaManutencao;
	Aviao aviao;
	string data;
	int id;
	int codAviao;
	bool existe = true, valid = false;
	char resposta;
	vector<Tecnico> tecnicosTemp;
	string especialidade;
	vector<string> especialidades;

	while(!tecnicos.empty())
	{
		tecnicosTemp.push_back(tecnicos.top());
		tecnicos.pop();
	}

	while(true){
		cout << "Introduza o id do tecnico (6 digitos): \n";
		id = Valid_Cin();
		if(id < 100000 || id > 999999){
			cout << "O id do passageiro nao e valido.\n";
			continue;
		}

		for(unsigned int i = 0; i < tecnicosTemp.size(); i++){
			existe = false;

			if(id == tecnicosTemp.at(i).getId()){
				existe = true;
				cout << "Esse tecnico ja existe!\n" << "Pretende voltar atras? (S/N)\n";

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
			if(existe)
				break;
		}
		if(!existe){
			cout << "Introduza a lista das especialidades do tecnico (0 para terminar): \n";
			while(true)
			{
				cin >> especialidade;
				if (especialidade == "0")
					break;

				if(especialidade.length() == 4){

					if( isalpha(especialidade[0]) ){
						int substring = stoi(especialidade.substr(1));

						if( substring >= 0 && substring <= 999){
							especialidades.push_back(especialidade);
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
					cout << "O codigo do aviao introduzido ja foi atribuido a outro tecnico.";
				}
			}

			Tecnico tecnico(especialidades, id, aviao);
			tecnicosTemp.push_back(tecnico);
			for(unsigned int j = 0; j < tecnicosTemp.size(); j++){
				tecnicos.push(tecnicosTemp.at(j));
			}
			cout << "Carregue no enter para continuar...\n";
			cin.get();
			return;
		}
	}
}

void Companhia::alteraTecnico(){
	Data dataProximaManutencao;
	Aviao aviao;
	string data;
	int id;
	bool existe = true, valid = false;
	char resposta;
	vector<Tecnico> tecnicosTemp;
	string especialidade;
	vector<string> especialidades;

	while(!tecnicos.empty())
	{
		tecnicosTemp.push_back(tecnicos.top());
		tecnicos.pop();
	}

	while(true){
		cout << "Introduza o id do tecnico (6 digitos): \n";
		id = Valid_Cin();
		if(id < 100000 || id > 999999){
			cout << "O id do tecnico nao e valido.\n";
			continue;
		}

		for(unsigned int i = 0; i < tecnicosTemp.size(); i++){
			existe = false;

			if(id == tecnicosTemp.at(i).getId()){
				existe = true;

				tecnicosTemp.at(i).alteraTecnico(avioes, tecnicosTemp);
			}
			if(existe){
				for(unsigned int j = 0; j < tecnicosTemp.size(); j++){
					tecnicos.push(tecnicosTemp.at(j));
				}
				cout << "O tecnico foi alterado com sucesso. \n";
				cout << "Carregue no enter para continuar...\n";
				cin.get();
				return;
			}

		}
		if(!existe){
			cout << "Esse tecnico nao existe!\n" << "Pretende voltar atras? (S/N)\n";

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


}

void Companhia::removeTecnico(){
	int id;
	vector<Tecnico> tecnicosTemp;
	bool existe = false;

	while(!tecnicos.empty())
	{
		tecnicosTemp.push_back(tecnicos.top());
		tecnicos.pop();
	}

	while(true)
	{
		cout << "Introduza o ID do passageiro: ";
		id = Valid_Cin();

		for (size_t i = 0; i < tecnicosTemp.size(); i++)
		{
			if (tecnicosTemp.at(i).getId() == id)
			{
				existe = true;
				tecnicosTemp.erase(tecnicosTemp.begin() + i);
				for(unsigned int j = 0; j < tecnicosTemp.size(); j++){
					tecnicos.push(tecnicosTemp.at(j));
				}
				cout << "O tecnico foi eliminado com sucesso. Carregue no enter para continuar...\n";
				cin.ignore();
				cin.get();
				return;
			}
		}
		if(!existe)
		{
			cout << "O id do passageiro introduzido nao existe. ";
		}
	}
}

void Companhia::visualizaTecnicos(){
	vector<Tecnico> tecnicosTemp;

	while(!tecnicos.empty())
	{
		tecnicosTemp.push_back(tecnicos.top());
		tecnicos.pop();
	}

	for(unsigned int i = 0; i< tecnicosTemp.size(); i++){
		cout << "ID: " << tecnicosTemp.at(i).getId() << endl;
		cout << "Data da proxima manutencao: " << tecnicosTemp.at(i).getProxManutencao().getData() << endl;
		cout << "Especialidades:\n";
		for (size_t j = 0; j < tecnicosTemp.at(i).getEspecialidades().size(); j++)
		{
			cout << tecnicosTemp.at(i).getEspecialidades().at(j) << endl;
		}
		cout << endl;
	}

	for(unsigned int i = 0; i< tecnicosTemp.size(); i++){
		tecnicos.push(tecnicosTemp.at(i));
	}

	cout << "Carregue no enter para continuar...\n";
	cin.get();
}
