#include "pop_ball.h"

#define LARGURA 800
#define ALTURA 600

#define FONT_PATH "/home/neto/Documentos/Grupo_Jogos/pop_ball/fonts/emulogic.ttf"

int main()
{	
    jhi_initialize_window(LARGURA, ALTURA, 32, WHITE);
    jhi_choice_window_name("Pop-Ball");
    
    /* Essa estrutura contém os campos x,y atual do mouse e captura algum evento ocorrido */
    JHI_MouseSt mouse;
    jhi_init_mouse(&mouse);	/* inicializar mouse */

    /* Estrutura da fonte */
	JHI_Font fonte_game_over, fonte_pontos;

	/* Estrutura de texto */
	JHI_Text texto_pontos;

	/* Carrega a fonte e inicializa a variavel texto */
	jhi_load_font(&fonte_game_over, FONT_PATH, 70);
	jhi_load_font(&fonte_pontos, FONT_PATH, 30);
	jhi_init_text(&texto_pontos);

    /* Seta a quantidade de frames por segundo na tela */
    jhi_set_fps_timer(32);
    
    /* Incia Variaveis e Parametros do Jogo */
    set_random_seed();
    set_game_level(5);
    set_pontuacao(0);
    level_up = 200;
    game_over = 0;
    init_bolas(LARGURA, ALTURA);
    vel_incremento = 2;

    while (jhi_get_close_window() != JHI_CLOSE)
    {
		jhi_timer_start();
		jhi_update();
		jhi_clean();

		if(game_over)
		{
			/* Desenha o nome Game Over na Tela */
			desenhar_game_over(&texto_pontos, &fonte_game_over, 95, 200);

			/* Desenha a pontuação na tela */
			desenhar_pontuacao(&texto_pontos, &fonte_pontos, 250, 500);

			continue;
		}

		/* Loop para desenhar as bolas caindo */
		desenhar_bolas_caindo(ALTURA);

		/* Verificar eventos do mouse sobre as bolas */
		verificar_eventos_mouse(&mouse, LARGURA);

	    /* Desenha a pontuação na tela */
		desenhar_pontuacao(&texto_pontos, &fonte_pontos, 250, 500);

	    /* Aumenta o nivel do jogo de acordo com a pontuacao */
		verificar_level_up();

	    /* Verifica se alguma bola atingiu a janela inferior */
		verificar_game_over(ALTURA);

		/* Espera tempo necessário para controlar a quantidade de frames por segundo */
		jhi_wait_time();
    }

    /* desalocar as estruturas carregadas */
	jhi_free_text(&texto_pontos);
	jhi_free_font(&fonte_pontos);
	jhi_free_font(&fonte_game_over);

    jhi_quit_and_free();

    return 0;
}
