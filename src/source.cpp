#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "aviao.h"
#include "companhia.h"
#include "menu.h"
#include "passageiro.h"
#include "voo.h"

using namespace std;


int main()
{
	Menu menu;

	menu.leitura_ficheiroAvioes();
	menu.leitura_ficheiroPassageirosCartao();
	menu.leitura_ficheiroVoos();
	menu.leitura_ficheiroTecnicos();

	menu.menu_principal();

	menu.escrita_ficheiroAvioes();
	menu.escrita_ficheiroPassageirosCartao();
	menu.escrita_ficheiroVoos();
	menu.escrita_ficheiroTecnicos();

    return 0;
}
