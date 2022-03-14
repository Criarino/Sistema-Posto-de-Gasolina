#include"base.h"

class Entidade : public TS_Objeto//classe de animação copiada
{
	private:
	struct cycle //informações da animação
	{
		int row;
		int w;
		int h;
		int amount;
		int speed;
		int tick;
	};
	vector<cycle> animations;//vector que guarda todas as animações
	int curAnim;//animação atual
	int begin;//frame da animação
	bool rev, nAb;//para reverter animação
	int newAnim;//para mudar uma animação

	public:
	Entidade(){rev=0;}
	//getter e setters
	void setCurAnimation(int c) {begin=0;curAnim=c;}
	int getCurAnimation() const {return curAnim;}
	void reverse(bool r) {rev=r;}//para inverter a animação

	int createCycle(int r, int w, int h, int amount, int speed);//cria uma animação(linha da imagem original, tamanho wxh, quantos frames, velocidade [quanto menor o número maior a velocidade]), retorna o código desta animação
	void updateAnimation();//atualiza o estado da animação atual
	void reverse(bool r, int nA){rev=r; nAb=1; nA=newAnim;}//inverte a animação e seta uma nova (booleana, codigo da nova animaçao)
};

int Entidade::createCycle(int r, int w, int h, int amount, int speed) //funcoes de animação
{
	cycle tmp;
	tmp.row=r-1;
	tmp.w=w;
	tmp.h=h;
	tmp.amount=amount;
	tmp.speed=speed;
	tmp.tick=1;
	animations.push_back(tmp);
	return animations.size()-1;
}

void Entidade::updateAnimation()
{
	setSource(animations[curAnim].w*animations[curAnim].tick, animations[curAnim].row*animations[curAnim].h, animations[curAnim].w, animations[curAnim].h);//setando o frame atual
	if(begin>animations[curAnim].speed)//se uma animação já tiver começado
	{
		if(!rev)//para reverter animações
			animations[curAnim].tick++;
		if (rev)
			animations[curAnim].tick--;
		begin=0;
	}
	begin++;
	if(animations[curAnim].tick>=animations[curAnim].amount)//resetando
		animations[curAnim].tick=1;
	if(animations[curAnim].tick<=0)//setando nova animação
	{
		if(nAb)
		{
			curAnim=newAnim;
			nAb=0;
			rev=0;
		}
		else
			animations[curAnim].tick=0;
	}
}

void TelaExtra::input()
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
				break;
		}
		asc=Engine.HaInput();
	}
}

void TelaExtra::MenuPrinc()
{
	unique_ptr<TS_Objeto> bk(new TS_Objeto);//imagem do background
	Engine.CriarObj(bk.get(), "./res/logo.jpg", 0, 0, 740, 740);
	Entidade player;
	player.setSource(0, 0, 150, 150);
	player.setDest(500, 100, 250, 250);
	player.setImage("./res/extra.png", Engine.getRende());
	player.setCurAnimation(player.createCycle(1, 150, 150, 94, 5));
	
	botoes.emplace_back(new TS_Botao); //botao de voltar
	Engine.CriarBtn(botoes[0].get(),"./res/voltar.png", 0, 0, 225, 255);
	botoes[0]->setDest(50, 70, 50, 50);
	
	while(rodando&&volt)
	{
		while(!inp)
		{
			Engine.Limite(60);
			Engine.SetBackground(255, 255, 255, 255, bk.get());
			Engine.Desenhar(&player);
			Engine.Desenhar(botoes[0].get());
			Engine.Commit();
			input();
			player.updateAnimation();
		}
		inp=false;
	}
	
}
