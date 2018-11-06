#ifndef AUXILIARES_H_
#define AUXILIARES_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;


/** Class Data
 *
 * Estrutura da Data, os seus atributos (dia mes ano) e as suas funcoes.
 * Utilizado tanto para datas de nascimento como para datas de voos.
 *
 */
class Data{
public:
	int dia; /**< dia da data */
	int mes; /**< mes da data */
	int ano; /**< ano da data */

	/**
	 * @brief Construtor de uma Data (recebendo uma string).
	 *
	 * @param data string que contem dia mes e ano separados por "/".
	 */
	Data(string data);

	/**
	 * @brief Construtor de uma Data (recebendo dia mes e ano).
	 *
	 * @param dia
	 * @param mes
	 * @param ano
	 */
	Data(int dia, int mes, int ano);

	/**
	 * @brief Construtor vazio de uma Data.
	 */
	Data();

	/**
	 * @brief Funcao que retorna a Data em string.
	 *
	 * @return string da data DD/MM/AAAA.
	 */
	string getData();

	/**
	 *  @brief Overload do operador << para conseguir imprimir os elementos da Data.
	 */
	friend std::ostream& operator<<(std::ostream &out, const Data &data)
	{out << data.dia << "/" << data.mes << "/" << data.ano; return out;}

	/**
	 * @brief Overload do operador = para atribuir uma Data.
	 *
	 * @param data objeto da classe data para igualar.
	 */
	void operator = (Data data);

	/**
	 * @brief Overload do operador == para poder comparar igualdade de duas datas.
	 *
	 * @param data objeto da classe Data para verifcar a igualdade.
	 *
	 * @return bool true caso seja igual, false se nao.
	 */
	bool operator == (Data data);

	/**
	 * @brief Overload do operador < para poder comparar se uma data e menor que a outra.
	 *
	 * @param data objeto da classe Data para verifcar a igualdade.
	 *
	 * @return bool true caso seja menor, false se nao.
	 */
	bool operator < (const Data data) const;
};

/** Class DataInvalida - Excecao para "apanhar" datas introduzidas erradamente.
 *
 */
class DataInvalida{
public:
	string data; /**< String da data introduzida. */

	/**
	 * @brief Construtor da DataInvalida a partir da string da data.
	 *
	 * @param data data invalida introduzida pelo utilizador.
	 */
	DataInvalida(string data){
		this->data = data;
	}

	/**
	 * @brief Overload do operador << para poder imprimir a data invalida.
	 *
	 * @param out output stream.
	 * @param data classe do tipo DataInvalida introudzida pelo utilizador.
	 */
	friend std::ostream& operator<<(std::ostream &out, const DataInvalida &data)
	{ out << "Data invalida: " << data.data << endl; return out; }

};

/**
 * @brief Funcao que verifica o input de ints.
 *
 * @return int input correto do utilizador
 */
int Valid_Cin();

/**
 * @brief Funcao auxiliar que permite escolher so numeros entre um certo range de opcoes.
 *
 * @param opcoes numero de opcoes do menu.
 *
 * @return int opcao correta do utilizador do menu.
 */
int opcaoMenu(int opcoes);

/**
 * @brief Funcao auxiliar que so permite introduzir 'S' ou 'N' para respostas do utilizador.
 *
 * @param frase frase a ser repetida se o input for errado.
 *
 * @return 'S' caso a resposta seja sim ou 'N' caso seja nao.
 */
char respostaSN(string frase);

/**
 * @brief Funcao auxiliar para verificar se a data do voo esta a menos de 48h da data de hoje.
 *
 * @param dataVoo data do voo.
 *
 * @return bool true caso verdadeiro, false se nao.
 */
bool verify2dias(Data dataVoo);

/**
 * @brief funçao que verifica se o passageiro esta inativo.
 *
 * @param dataUltimoVoo data do ultimo voo do passageiro.
 *
 * @return bool true caso verdadeiro, false se nao.
 */
bool verifyInativo(Data dataUltimoVoo);

/**
 * @brief funcao que coloca varis endlines para simular um clear screen.
 */
void clearScreen();

#endif /*AUXILIARES_H_*/
