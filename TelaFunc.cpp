#include "base.h"

void TelaFunc::input()
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
				if (botoes[1]->Sobre())//inserir na tabela
					botoes[1]->Setclick(true);
				else for(int i=2; i<botoes.size(); i++)//deletar
				{
					if (botoes[i]->Sobre())
					{
						textoSimples.erase(textoSimples.begin()+i*2+i-2, textoSimples.begin()+i*2+3+i-2);
						botoes.erase(botoes.begin()+i);
						dados.erase(dados.begin()+i-2);
					}
				}
				for(int i=0; i<caixastxtInv.size(); i++)//ativar/desativar caixas de texto
				{
					if (caixastxtInv[i]->Sobre()&&!caixastxtInv[i]->Getativ())
						caixastxtInv[i]->Ativar();
					else if (!caixastxtInv[i]->Sobre()&&caixastxtInv[i]->Getativ())
						caixastxtInv[i]->Ativar();
				}
				break;
			case 4://caso especial (texto)
				inp=true;
				for(int i=0; i<caixastxtInv.size(); i++)
					if (caixastxtInv[i]->Getativ())
						caixastxtInv[i]->Texto(Engine.buftxt);
				break;
		}
		asc=Engine.HaInput();
	}
}

TelaFunc::TelaFunc()
{	
	sans1=Engine.AbrirFonte("Sans.ttf", 20);
	
	ifstream data;//lendo arquivo txt
	data.open("funcionarios.txt");
	string t;
	while (getline(data, t))
		dados.push_back(t);
	data.close();
	
	textoSimples.push_back(Engine.CriarTexto("Nome", sans1, 180, 150, 255, 0, 0));//topo da tabela
	textoSimples.push_back(Engine.CriarTexto("CPF", sans1, 480, 150, 255, 0, 0));
	textoSimples.push_back(Engine.CriarTexto("Contato", sans1, 780, 150, 255, 0, 0));
	textoSimples.push_back(Engine.CriarTexto("Adicionar Funcionario", sans1, 1020, 120, 255, 0, 0));
	
	int in, me;	
	for(int i=0; i<dados.size();i++)//informações da tabela
	{
		in=dados[i].find(' ', 0);
		me=dados[i].find(' ', in+1);
		textoSimples.push_back(Engine.CriarTexto(dados[i].substr(0, in), sans1, 180, 180+(50*i), 0, 0, 0));//nome
		textoSimples.push_back(Engine.CriarTexto(dados[i].substr(in, me-in), sans1, 480, 180+(50*i), 0, 0, 0));//CPF
		textoSimples.push_back(Engine.CriarTexto(dados[i].substr(me, string::npos), sans1, 780, 180+(50*i), 0, 0, 0));//contato
	}
	
	retangulos.push_back(Engine.CriarRect(true, 150, 145, 405, 785, 255, 255, 255, 200));//fundo transparente da tabela
	
	conteudo.emplace_back(new TS_Objeto); //caixa de inserir novo func
	Engine.CriarObj(conteudo[0].get(), "./res/caixaadd.png", 0, 0, 500, 190);
	conteudo[0]->setDest(950, 150, 400, 130);
	
	botoes.emplace_back(new TS_Botao); //botao de voltar
	Engine.CriarBtn(botoes[0].get(),"./res/voltar.png", 0, 0, 225, 255);
	botoes[0]->setDest(50, 70, 50, 50);
	
	botoes.emplace_back(new TS_Botao);//botao de inserir 
	Engine.CriarBtn(botoes[1].get(),"./res/confirmar.png", 0, 0, 720, 720);
	botoes[1]->setDest(1118, 280, 50, 50);
	
	for(int i=2; i<=dados.size()+1;i++)
	{
		botoes.emplace_back(new TS_Botao); //botoes de remover
		Engine.CriarBtn(botoes[i].get(),"./res/deletar.png", 0, 0, 225, 255);
		botoes[i]->setDest(915, 182+((50*i)-100), 25, 25);
	}
	
	caixastxtInv.emplace_back(new TS_CaixaTxt);//caixa de inserir nome
	Engine.CriarCaixaTxt(caixastxtInv[0].get(), sans1, 0, 0, 0, 300, 20);
	caixastxtInv[0]->TS_Objeto::setDest(1044, 158);
	caixastxtInv[0]->SetAj(0, -5);
	
	caixastxtInv.emplace_back(new TS_CaixaTxt);//caixa de inserir CPF
	Engine.CriarCaixaTxt(caixastxtInv[1].get(), sans1, 0, 0, 0, 300, 20);
	caixastxtInv[1]->TS_Objeto::setDest(1044, 206);
	caixastxtInv[1]->SetAj(0, -5);
	
	caixastxtInv.emplace_back(new TS_CaixaTxt);//caixa de inserir contato
	Engine.CriarCaixaTxt(caixastxtInv[2].get(), sans1, 0, 0, 0, 300, 20);
	caixastxtInv[2]->TS_Objeto::setDest(1044, 252);
	caixastxtInv[2]->SetAj(0, -5);
}

TelaFunc::~TelaFunc()
{
	ofstream of;//atualizando arquivo txt
	of.open("funcionarios.txt");
	for(int i=0; i<dados.size(); i++)
		of<<dados[i]+'\n';
	of.close();
}

void TelaFunc::MenuPrinc()
{
	int x, y;
	unique_ptr<TS_Objeto> bk(new TS_Objeto);
	Engine.CriarObj(bk.get(), "./res/logo.jpg", 0, 0, 740, 740);
	while(rodando&&volt)
	{
		Engine.SetBackground(255, 255, 255, 255, bk.get());
		SDL_GetMouseState(&x, &y);
		Engine.Desenhar(to_string(x)+", "+to_string(y), sans1, 3, 3, 255, 0, 0);
		Desenhar(&Engine);
		
		while(!inp)
		{
			Engine.Limite(60);
			input();
		}
		inp=false;
		
		if (botoes[1]->Getclick())//para adicionar informação à tabela
		{
			botoes[1]->Setclick(false);
			dados.push_back(caixastxtInv[0]->Gettxt()+' '+caixastxtInv[1]->Gettxt()+' '+caixastxtInv[2]->Gettxt());
			textoSimples.push_back(Engine.CriarTexto(caixastxtInv[0]->Gettxt(), sans1, 180, 180+(50*(textoSimples.size()-4)/3), 0, 0, 0));//nome
			textoSimples.push_back(Engine.CriarTexto(caixastxtInv[1]->Gettxt(), sans1, 480, 180+(50*(textoSimples.size()-5)/3), 0, 0, 0));//CPF
			textoSimples.push_back(Engine.CriarTexto(caixastxtInv[2]->Gettxt(), sans1, 780, 180+(50*(textoSimples.size()-6)/3), 0, 0, 0));//contato
			caixastxtInv[0]->Limpar();
			caixastxtInv[1]->Limpar();
			caixastxtInv[2]->Limpar();
			
			botoes.emplace_back(new TS_Botao); //botão de remover
			Engine.CriarBtn(botoes[botoes.size()-1].get(),"./res/deletar.png", 0, 0, 225, 255);
			botoes[botoes.size()-1]->setDest(915, 182+((50*(botoes.size()-1))-100), 25, 25);
		}
	}
}
