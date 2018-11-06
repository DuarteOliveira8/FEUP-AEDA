#ifndef AVIAO_H_
#define AVIAO_H_

#include <iostream>
#include <string>
#include <vector>
#include "passageiro.h"
#include "BST.h"

using namespace std;

/** Class Aviao
 *
 * Estrutura de um aviao, os seus atributos e funcoes.
 *
 */
class Aviao {
	int codAviao; /**< Codigo do aviao. */
	string modelo; /**< modelo do aviao. (cod aviao atual)*/
	unsigned int lotacao; /**< Lotacao do aviao. */
	int precoPorLugar; /**< Preco por lugar do aviao. */
	int periodicidadeManutencao; /**< periodicidade da manutencao. */
	Data dataProxManutencao; /**< data da proxima manutencao. */
public:
	Aviao(); /**< Construtor vazio do aviao. */

	/**
	 * @brief Construtor de um aviao com parametros.
	 *
	 * @param codAviao codigo do aviao.
	 * @param lotacao lotacao do aviao.
	 * @param precoPorLugar preco por lugar do aviao.
	 */
	Aviao(int codAviao, string modelo, unsigned int lotacao, float precoPorLugar, int periodicidadeManutencao, Data dataProxManutencao);

	/**
	 * @brief Funcao que retorna a lotacao do aviao.
	 *
	 * @return lotacao do aviao.
	 */
	unsigned int getLotacao() const;

	/**
	 * @brief Funcao que retorna o codigo do aviao.
	 *
	 * @return codigo do aviao.
	 */
	int getCodAviao() const;

	/**
	 * @brief Funcao que retorna o preco por lugar do aviao.
	 *
	 * @return preco por lugar.
	 */
	int getPrecoPorLugar() const;

	/**
	 * @brief Funcao que retorna o modelo do aviao.
	 *
	 * @return modelo do aviao.
	 */
	string getModelo() const;

	/**
	 * @brief Funcao que retorna a data da proxima manutencao do aviao.
	 *
	 * @return periodicidade de manutencao
	 */
	int getPeriodicidadeManutencao() const;

	/**
	 * @brief Funcao que retorna a periodicidade de manutencao do aviao.
	 *
	 * @return data da proxima manutencao
	 */
	Data getDataProxManutencao() const;

	/**
	 * @brief Overload do operador = para poder atribuir os dados de um aviao a outro.
	 *
	 * @param av objeto da classe Aviao.
	 */
	void operator = (Aviao av);

	/**
	 * @brief Overload do operador < para poder comparar a data da proxima manutencao de dois avioes.
	 *
	 * @param av objeto da classe Aviao.
	 *
	 * @return true se a a data é menor, false se nao.
	 */
	bool operator < (Aviao av);

	/**
	 * @brief Funcao que altera as caracteristicas do aviao de acordo com a escolha do utilizador.
	 *
	 * @param avioes BST de avioes para poder fazer pesquisas.
	 */
	void alteraAviao(BST<Aviao> avioes);
};

#endif /*AVIAO_H_*/
