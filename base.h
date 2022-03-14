//g++ *.cpp -o t -lSDL2 -lSDL2_ttf -lSDL2_image
/*
todo:
-Lista de funcionários (adicionar/remover)
-Estoque do posto e loja de conveniência (submenu)
Vendas totais (mesmo sistema de lista de funcionários)
"Extra"
(desenhar telas/botoes fora)
*/
#pragma once

#include "TSSGE.h"
#include <iostream>
#include <fstream>

using namespace std;

extern TS Engine;
extern bool rodando, inp;

/*class TelaPrinc : public TS_Tela //tela principal
{
	private:
	int sans, tela=0;
	void input();
	
	public:
	TelaPrinc();
	void MenuPrinc() override;
};*/

class TelaFunc : public TS_Tela //tela de funcionários
{
	private:
	int sans1;
	void input();
	vector<string> dados;//string que guarda os dados da tabela
	bool volt=true;
	
	public:
	TelaFunc();
	~TelaFunc();
	void MenuPrinc() override;
};

class TelaEst : public TS_Tela //tela de estoque
{
	private:
	int sans1;
	void input();
	bool volt=true;
	
	public:
	TelaEst();
	void MenuPrinc() override;
};

class TelaVendas : public TS_Tela//tela de vendas
{
	private:
	int sans1;
	void input();
	vector<string> dados;
	bool volt=true;
	
	public:
	TelaVendas();
	void MenuPrinc() override;
};

class TelaExtra : public TS_Tela
{
	private:
	void input();
	bool volt=true;
	
	public:
	void MenuPrinc() override;
};
