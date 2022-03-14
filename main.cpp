#include "base.h"

TS Engine;
bool rodando=true, inp=false;

class TelaPrinc : public TS_Tela
{
	private:
	int sans, tela=0;
	void input()
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
					if (botoes[0]->Sobre())
						tela=1;
					else if (botoes[1]->Sobre())
							tela=2;
						else if (botoes[2]->Sobre())
								tela=3;
							else if (botoes[3]->Sobre())
									tela=4;
				break;
			}
			asc=Engine.HaInput();
		}
	}
	
	public:
	TelaPrinc()
	{
		sans=Engine.AbrirFonte("Sans.ttf", 15);
	
		botoes.emplace_back(new TS_Botao); //botao de funcionarios
		Engine.CriarBtn(botoes[0].get(),"./res/funcionarios.png", 0, 0, 300, 100);
		botoes[0]->setDest(200, 150, 150, 50);
		
		botoesInv.emplace_back(new TS_Botao); //botao de funcionarios invisivel
		Engine.CriarBtn(botoesInv[0].get(),"./res/funcionarios1.png", 0, 0, 300, 100);
		botoesInv[0]->setDest(200, 150, 150, 50);
		
		botoes.emplace_back(new TS_Botao); //botao de estoque
		Engine.CriarBtn(botoes[1].get(),"./res/estoque.png", 0, 0, 300, 100);
		botoes[1]->setDest(200, 250, 150, 50);
		
		botoesInv.emplace_back(new TS_Botao); //botao de estoque invisivel
		Engine.CriarBtn(botoesInv[1].get(),"./res/estoque1.png", 0, 0, 300, 100);
		botoesInv[1]->setDest(200, 250, 150, 50);
		
		botoes.emplace_back(new TS_Botao); //botao de vendas
		Engine.CriarBtn(botoes[2].get(),"./res/vendas.png", 0, 0, 300, 100);
		botoes[2]->setDest(200, 350, 150, 50);
		
		botoesInv.emplace_back(new TS_Botao); //botao de vendas invisivel
		Engine.CriarBtn(botoesInv[2].get(),"./res/vendas1.png", 0, 0, 300, 100);
		botoesInv[2]->setDest(200, 350, 150, 50);
		
		botoes.emplace_back(new TS_Botao); //botao extra
		Engine.CriarBtn(botoes[3].get(),"./res/extrab.png", 0, 0, 300, 100);
		botoes[3]->setDest(200, 450, 150, 50);
		
		botoesInv.emplace_back(new TS_Botao); //botao extra invisivel
		Engine.CriarBtn(botoesInv[3].get(),"./res/extrab1.png", 0, 0, 300, 100);
		botoesInv[3]->setDest(200, 450, 150, 50);
	}
	
	void MenuPrinc() override
	{
		int x, y, a=botoes.size();
		unique_ptr<TS_Objeto> bk(new TS_Objeto);//imagem do background
		Engine.CriarObj(bk.get(), "./res/logo.jpg", 0, 0, 740, 740);
		
		while(rodando)
		{
			Engine.SetBackground(255, 255, 255, 255, bk.get());
			SDL_GetMouseState(&x, &y);//para mostrar a posição do mouse a cada clique
			Engine.Desenhar(to_string(x)+", "+to_string(y), sans, 3, 3, 255, 0, 0);
			Desenhar(&Engine);//desenha tudo na tela
			switch (tela)//para trocar de tela
			{
				case 1:
					{
						TelaFunc a;
						a.MenuPrinc();
					}
					break;
				case 2:
					{
						TelaEst a;
						a.MenuPrinc();
					}
					break;
				case 3:
					{
						TelaVendas a;
						a.MenuPrinc();
					}
					break;
				case 4:
					{
						TelaExtra a;
						a.MenuPrinc();
					}
					break;
			}
			tela=0;
			
			while(!inp&&rodando)
			{
				Engine.Limite(60);
				input();
				
				for(int i=0; i<a; i++)
				{
					if (!botoes[i]->Sobre()&&botoes[i]->Getclick())//para mudar a imagem dos botoes de volta ao normal
					{
						botoes.pop_back();
						botoes[i]->Setclick(false);
						inp=true;
						break;
					}
					else if (botoes[i]->Sobre()&&!botoes[i]->Getclick())//para mudar a imagem dos botoes para a "pressionada"
					{
						botoes.push_back(botoesInv[i]);
						botoes[i]->Setclick(true);
						inp=true;
						break;
					}
				}
			}
			inp=false;
		}
	}
};

int main()
{
	Engine.CriarJanela(1366, 680, "Lorem Ipsum");
	TelaPrinc a;
	a.MenuPrinc();
	return 0;
}
