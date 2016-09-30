#include "pop_ball.h"

#define LARGURA 800
#define ALTURA 600

#define FONT_PATH "../../fonts/emulogic.ttf"


void game_intro_screen()
{
	JHI_Image logo;
	JHI_Font font;
	JHI_Text text;

	jhi_load_image(&logo, "../images/Logotipo.png");
	jhi_init_text(&text);
	jhi_load_font(&font, "../../fonts/Chewy.ttf", 20);
	jhi_set_text(&font, &text , BLACK, "Powered by LIBJHI-SDL");

	logo.pos = jhi_get_central_pos(jhi_get_width_window(), jhi_get_height_window(),
			jhi_get_image_width(&logo), jhi_get_image_height(&logo));

	text.pos.x = logo.pos.x;
	text.pos.y = logo.pos.y + jhi_get_image_height(&logo);

	jhi_set_background_color(WHITE);


	int alpha = JHI_MIN_ALPHA;
	int inc = 3;


	while(jhi_get_close_window() != JHI_CLOSE)
	{
		jhi_timer_start();
		jhi_update();
		jhi_clean();
		jhi_set_alpha_image(&logo, alpha);
		jhi_set_alpha_text(&text, alpha);
		jhi_draw_image(&logo, logo.pos);
		jhi_draw_text(&text, text.pos);

		alpha+=inc;
		if (alpha >= JHI_MAX_ALPHA){
			jhi_transition_square_color(BLACK, DEFAULT_DIST, 15, 0);
			jhi_set_background_color(BLACK);
			jhi_update();
			jhi_clean();
			jhi_delay_mili_seconds(500);
			break;
		}


		jhi_wait_time();

	}
	jhi_set_background_color(WHITE);
	jhi_free_image(&logo);
	jhi_free_text(&text);
	jhi_free_font(&font);
}

void gameplay_screen(JHI_Text *texto_pontos, JHI_MouseSt *mouse,
		JHI_Font *fonte_game_over, JHI_Font *fonte_pontos, JHI_Image *background)
{
    while (jhi_get_close_window() != JHI_CLOSE)
    {
		jhi_timer_start();
		jhi_update();
		jhi_clean();

		/* Desenha a imagem de plano de fundo */
		jhi_draw_image(background, background->pos);

		if(game_over)
		{
			/* Desenha o nome Game Over na Tela */
			desenhar_game_over(texto_pontos, fonte_game_over, 95, 200);

			/* Desenha a pontuação na tela */
			desenhar_pontuacao(texto_pontos, fonte_pontos, 250, 500);

			continue;
		}

		/* Loop para desenhar as bolas caindo */
		desenhar_bolas_caindo(ALTURA);

		/* Verificar eventos do mouse sobre as bolas */
		verificar_eventos_mouse(mouse, LARGURA);

	    /* Desenha a pontuação na tela */
		desenhar_pontuacao(texto_pontos, fonte_pontos, 250, 500);

	    /* Aumenta o nivel do jogo de acordo com a pontuacao */
		verificar_level_up();

	    /* Verifica se alguma bola atingiu a janela inferior */
		verificar_game_over(ALTURA);

		/* Espera tempo necessário para controlar a quantidade de frames por segundo */
		jhi_wait_time();
    }
}

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

	JHI_Image background;

	/* Carrega a fonte e inicializa a variavel texto */
	jhi_load_font(&fonte_game_over, FONT_PATH, 70);
	jhi_load_font(&fonte_pontos, FONT_PATH, 30);
	jhi_init_text(&texto_pontos);
	jhi_load_image(&background, "../images/Background.png");
	background.pos.x = 0;
	background.pos.y = 0;

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
    jhi_load_effect(&explosion, "../audio/explosion.wav");
    jhi_load_music(&psi, "../audio/psicose.mp3");
    jhi_load_music(&normal, "../audio/blast_off.mp3");

    /* Desenha a introducao do jogo. Logo da lib é mostrada */
    game_intro_screen();

    /* Loop principal do jogo é iniciado */
    jhi_play_music(&normal, -1);
    jhi_resize_image(&background, LARGURA, ALTURA);
    gameplay_screen(&texto_pontos, &mouse, &fonte_game_over, &fonte_pontos, &background);
	
    /* desalocar as estruturas carregadas */
	jhi_free_text(&texto_pontos);
	jhi_free_font(&fonte_pontos);
	jhi_free_font(&fonte_game_over);

    jhi_quit_and_free();

    return 0;
}
