#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include <iostream>
#include <string>
#include <vector>
#include "auxiliares.h"

using namespace std;


/** Class Passageiro
 *
 * Estrutura de um passageiro (sem cartao), os seus atributos (nome id) e as suas funcoes.
 *
 */
class Passageiro {
protected:
	string nome; /**< Nome do passageiro. */
	int id; /**< ID do passageiro. */
public:
	Passageiro(); /**< Construtor vazio de um passageiro. */

	/**
	 * @brief Construtor de um passageiro.
	 *
	 * \param nome do passageiro.
	 * \param id do passageiro.
	 */
	Passageiro(string nome, int id);
	string getNome() const; /**< Funcao que retorna o nome de um passageiro. */
	int getId() const; /**< Funcao que retorna o ID de um passageiro. */

	/**
	 * @brief Funcao que calcula o preco do bilhete de um passageiro e retorna-o.
	 *
	 * \param preco calculado.
	 */
	virtual float calculaPreco(int preco) const;
	void operator = (Passageiro p); /**< Overload do operador = que permite atribuir os dados de um passageiro a outro. */
};

/** Class PassageiroCartao
 *
 * Estrutura de Passageiro com Cartao, os seus atributos derivados (nome e id derivados da classe mae, Passageiro) e os novos,
 * alem das suas funcoes.
 */
class PassageiroCartao : public Passageiro {
	string profissao; /**< Profissao do passageiro com cartao. */
	Data dataNascimento; /**< Data de nascimento do passageiro com cartao. */
	int nMedAno; /**< Numero medio de viagens por ano do passageiro com cartao. */
	Data ultimoVoo; /**< Data do ultimo voo efetuado por este passageiro com cartao */
public:

	/**
	 * @brief Construtor do Passageiro com Cartao
	 *
	 * \param nome do passageiro com cartao.
	 * \param profissao do passageiro com cartao.
	 * \param dataNascimento do passageiro com cartao.
	 * \param nMedAno - numero medio de viagens por ano do passageiro com cartao.
	 * \param id do passageiro com cartao.
	 */
	PassageiroCartao(string nome, string profissao, Data dataNascimento, float nMedAno, int id, Data ultimoVoo);
	string getProfissao() const; /**< Funcao que retorna a profissao do passageiro com cartao. */
	Data getDataNascimento() const; /**< Funcao que retorna a data de nascimento do passageiro com cartao. */
	int getNMedAno() const; /**< Funcao que retorna o numero medio de viagens por ano do passageiro com cartao. */
	Data getDataUltimoVoo() const; /**< Funcao que retorna a data do ultimo voo do passageiro com cartao. */
	void alteraPassageiroCartao();

	/**
	 * @brief Funcao que calcula e retorna o preco do bilhete para o passageiro com cartao.
	 * Tem maior desconto consoante o numero medio de viagens por ano.
	 *
	 * \param preco calculado do bilhete.
	 */
	float calculaPreco(int preco) const;
	void incrementaNMedAno(); /**< Funcao que incrementa (em 1) o numero medio de viagens por ano do passageiro com cartao. */
	void decrementaNMedAno(); /**< Funcao que decrementa (em 1) o numero medio de viagens por ano do passageiro com cartao. */
	void operator = (PassageiroCartao p); /**< Overload do operator = para atribuir os dados de um passageiro com cartao a outro. */
};

/**
 * @brief Funcao de hash
 */
struct hstr
{
	int operator()(const PassageiroCartao* pc) const
	{
		string f1 = pc->getDataUltimoVoo().getData();
		int v = 0;
		for (unsigned int i = 0; i < f1.size(); i++)
			v = 37 * v + f1[i];
		return v;
	}
};

/**
 * @brief Funcao de igualdade para hash table
 */
struct eqstr{
	bool operator() (const PassageiroCartao* pc1, const PassageiroCartao* pc2) const
	{
		return pc1->getDataUltimoVoo() == pc2->getDataUltimoVoo();
	}
};

#endif /*PASSAGEIRO_H_*/
