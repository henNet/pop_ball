#include "pop_ball.h" 

/*****************************************************************************************/

void init_bolas(int faixa_x, int faixa_y)
{
    int i = 0;
    
    for(; i < game_level; i++)
    {
    	bolas_caindo[i].id_cor_bolas = rand() % 5; /* 7 é a quantidade de cores da lib */
		bolas_caindo[i].pontos.x = rand() % faixa_x;
		bolas_caindo[i].pontos.y = (-1)*(rand() % 100);
    }
}

/*****************************************************************************************/

void set_game_level(int level)
{
    game_level = level;
}

/*****************************************************************************************/

void set_pontuacao(int pontos)
{
    pontuacao = pontos;
}

/*****************************************************************************************/

int get_pontuacao()
{
    return pontuacao;
}

/*****************************************************************************************/

void incrementa_pontuacao(int pontos)
{
    pontuacao += pontos;
}

/*****************************************************************************************/

void set_random_seed()
{
    srand((unsigned int)time(NULL));
}

/*****************************************************************************************/

int gerar_random_number(int faixa)
{
    return (rand() % faixa);
}

/*****************************************************************************************/

int mouse_dentro_bola(int centro_x, int centro_y, int mouse_pos_x, int mouse_pos_y)
{
    double distancia = sqrt( (mouse_pos_x - centro_x) * (mouse_pos_x - centro_x) + 
			     (mouse_pos_y - centro_y) * (mouse_pos_y - centro_y) );
    
    if(distancia < RAIO_BOLA)
		return 1;		/* Mouse dentro da Bola */
    else
		return 0;		/* Mouse não está dentro da Bola */
}

/*****************************************************************************************/

void desenhar_bolas_caindo(int altura_janela)
{
	int i;
	for(i = 0; i < game_level; i++)
	{
	    /* Desenha um circulo */
		jhi_draw_fill_circle(bolas_caindo[i].pontos, RAIO_BOLA, bolas_caindo[i].id_cor_bolas);

		/* Desenhar a borda do circulo. Duas chamadas para a borda ficar mais forte */
		jhi_draw_circle(bolas_caindo[i].pontos, RAIO_BOLA, BLACK);
		jhi_draw_circle(bolas_caindo[i].pontos, RAIO_BOLA + 1, BLACK);
	    
	    /* Anima o circulo até ele encostar na parte debaixo da tela */
	    if(bolas_caindo[i].pontos.y < (altura_janela + 2 * RAIO_BOLA)) {
			bolas_caindo[i].pontos.y += vel_incremento;
		}
	}
}

/*****************************************************************************************/

void verificar_eventos_mouse(JHI_MouseSt *mouse, int largura_janela)
{
	/* Eventos do mouse */
	int j;
    for (j = 0; j < jhi_get_number_of_events(); j++)
    {
		/* Pega o status do mouse no evento j */
		*mouse = jhi_get_mouse_status(j);

		/* se foi clicado botão esquerdo do mouse */
		if (mouse->mouse_event == ON_CLICK_LEFT)
		{
			int k = 0;
		    int status;
		    for(;k < game_level; k++)
		    {
		     	status = mouse_dentro_bola(bolas_caindo[k].pontos.x, bolas_caindo[k].pontos.y, 
										   mouse->x, mouse->y);

		     	if(status)
			    {
			    	bolas_caindo[k].id_cor_bolas = rand() % 5; /* 5 é a quantidade de cores da lib */
					bolas_caindo[k].pontos.x = gerar_random_number(largura_janela);
					bolas_caindo[k].pontos.y = (-1)*gerar_random_number(100);

					incrementa_pontuacao(PONTOS);
					printf("Pontos: %d\n", get_pontuacao());
			    }
		    }
		}
    }
}

/*****************************************************************************************/

void verificar_level_up()
{
	if(game_level <= MAX_GAME_LEVEL) {
		if(get_pontuacao() >= level_up)
		{
			game_level += 5;
			vel_incremento += 2;
			level_up += 500;
		}
	}
}

/*****************************************************************************************/

void verificar_game_over(int altura_janela)
{
	int i;
	for(i = 0; i < game_level; i++)
	{
		if((bolas_caindo[i].pontos.y + RAIO_BOLA) > altura_janela) {
			game_over = 1;
		}
	}
}

/*****************************************************************************************/

void desenhar_pontuacao(JHI_Text *texto, JHI_Font *fonte, int text_pos_x, int text_pos_y)
{
	char pontos_string[20]; /* String que mostra os pontos */

	/* Seta o texto t1 com a fonte f1 configurada, com o texto do quarto parâmetro */
    snprintf(pontos_string, 20, "Pontos: %d", get_pontuacao());
	jhi_set_text(fonte, texto, ORANGE, pontos_string);

	/* desenha o texto em posição */
	texto->pos.x = 250;
	texto->pos.y = 500;
	jhi_draw_text(texto, texto->pos);
}

/*****************************************************************************************/

void desenhar_game_over(JHI_Text *texto, JHI_Font *fonte, int text_pos_x, int text_pos_y)
{
	jhi_set_text(fonte, texto, BLACK, "Game Over");

	/* desenha o texto em posição */
	texto->pos.x = text_pos_x;
	texto->pos.y = text_pos_y;
	jhi_draw_text(texto, texto->pos);
}
