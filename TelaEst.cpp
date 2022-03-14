#include "base.h"

void TelaEst::input()
{
	vector<int>asc;
	asc=Engine.HaInput();
	while(asc[0]!=0)
	{
		switch(asc[0])//qual o tipo de evento
		{
			case -1://caso seja fechar
				rodando=false;
				inp=true;
				break;
			case 3://caso seja clique
				inp=true;
				if (botoes[0]->Sobre())//voltar
					volt=false;
				else if(botoes[1]->Sobre())//para aumentar ou diminuir o conteúdo
				{
					retangulos[1].r.w=retangulos[1].r.w+10;
					retangulos[1].r.y=retangulos[1].r.y-10;
				}
					else if(botoes[2]->Sobre())
					{
						retangulos[1].r.w=retangulos[1].r.w-10;
						retangulos[1].r.y=retangulos[1].r.y+10;
					}
						else if(botoes[3]->Sobre())
						{
							retangulos[2].r.w=retangulos[2].r.w+10;
							retangulos[2].r.y=retangulos[2].r.y-10;
						}
							else if(botoes[4]->Sobre())
							{
								retangulos[2].r.w=retangulos[2].r.w-10;
								retangulos[2].r.y=retangulos[2].r.y+10;
							}
				break;
			case 4://caso especial (texto)
				inp=true;
				break;
		}
		asc=Engine.HaInput();
	}
}

TelaEst::TelaEst()
{
	sans1=Engine.AbrirFonte("Sans.ttf", 20);
	
	retangulos.push_back(Engine.CriarRect(true, 150, 145, 405, 785, 255, 255, 255, 200));//fundo transparente da tabela
	retangulos.push_back(Engine.CriarRect(true, 582, 201, 100, 100, 255, 0, 0, 255));//conteúdo da esquerda
	retangulos.push_back(Engine.CriarRect(true, 684, 201, 100, 100, 0, 0, 255, 255));//conteúdo da direita
	
	textoSimples.push_back(Engine.CriarTexto("Gasolina", sans1, 590, 130, 0, 0, 0));//texto acima
	textoSimples.push_back(Engine.CriarTexto("Alcool", sans1, 710, 130, 0, 0, 0));
	textoSimples.push_back(Engine.CriarTexto(to_string(retangulos[1].r.w)+"%", sans1, 500, 200, 0, 0, 0));//porcentagem do conteúdo
	textoSimples.push_back(Engine.CriarTexto(to_string(retangulos[2].r.w)+"%", sans1, 800, 200, 0, 0, 0));
	
	botoes.emplace_back(new TS_Botao); //botao de voltar
	Engine.CriarBtn(botoes[0].get(),"./res/voltar.png", 0, 0, 225, 255);
	botoes[0]->setDest(50, 70, 50, 50);
	
	botoes.emplace_back(new TS_Botao); //botao de adicionar
	Engine.CriarBtn(botoes[1].get(),"./res/adicionar.png", 0, 0, 512, 512);
	botoes[1]->setDest(618, 160, 25, 25);
	
	botoes.emplace_back(new TS_Botao); //botao de reduzir
	Engine.CriarBtn(botoes[2].get(),"./res/reduzir.png", 0, 0, 225, 255);
	botoes[2]->setDest(618, 325, 25, 25);
	
	botoes.emplace_back(new TS_Botao); //botao de adicionar 2
	Engine.CriarBtn(botoes[3].get(),"./res/adicionar.png", 0, 0, 512, 512);
	botoes[3]->setDest(722, 160, 25, 25);
	
	botoes.emplace_back(new TS_Botao); //botao de reduzir 2
	Engine.CriarBtn(botoes[4].get(),"./res/reduzir.png", 0, 0, 225, 255);
	botoes[4]->setDest(722, 325, 25, 25);
	
	conteudo.emplace_back(new TS_Objeto); //desenho do tanque
	Engine.CriarObj(conteudo[0].get(), "./res/estoqueposto.png", 0, 0, 203, 101);
	conteudo[0]->setDest(1366/2-203/2, 200);
}

void TelaEst::MenuPrinc()
{
	int x, y;
	unique_ptr<TS_Objeto> bk(new TS_Objeto);
	Engine.CriarObj(bk.get(), "./res/logo.jpg", 0, 0, 740, 740);
	while(rodando&&volt)
	{
		Engine.SetBackground(255, 255, 255, 255, bk.get());
		SDL_GetMouseState(&x, &y);
		Engine.Desenhar(to_string(x)+", "+to_string(y), 1, 3, 3, 255, 0, 0);
		
		if(retangulos[1].r.w>100)//para limitar o tamanho dos conteúdos
		{
			retangulos[1].r.w=100;
			retangulos[1].r.y=201;
		}
		else if(retangulos[1].r.w<0)
		{
			retangulos[1].r.w=0;
			retangulos[1].r.y=301;
		}
		if(retangulos[2].r.w>100)
		{
			retangulos[2].r.w=100;
			retangulos[2].r.y=201;
		}
		else if(retangulos[2].r.w<0)
		{
			retangulos[2].r.w=0;
			retangulos[2].r.y=301;
		}
		
		textoSimples[2].msg=to_string(retangulos[1].r.w)+"%";//atualizando porcentagem do conteúdo
		textoSimples[3].msg=to_string(retangulos[2].r.w)+"%";
		
		Desenhar(&Engine);
		
		while(!inp)
		{
			Engine.Limite(60);
			input();
		}
		inp=false;
	}
}
