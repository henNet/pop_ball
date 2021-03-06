#include "pop_ball.h"
#include "button.h"



#define FONT_PATH "../../fonts/emulogic.ttf"

static int is_menu = 1;
static int is_exit = 0;

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

	is_exit = 1;
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
			is_exit = 0;
			break;
		}


		jhi_wait_time();

	}
	jhi_set_background_color(WHITE);
	jhi_free_image(&logo);
	jhi_free_text(&text);
	jhi_free_font(&font);
}

int game_menu_screen(JHI_Image *background, JHI_MouseSt *mouse)
{
	Button vet_buttons[2];
	JHI_Image menu_img, menu_img2;
	int pos=-1,j;
	JHI_Font font_text, font_button;
	JHI_Text pop, ball;

	JHI_Font font_borda;
	JHI_Text pop_borda, ball_borda;

	//jhi_load_font(&font_text, "../../fonts/Chewy.ttf", 50);
	jhi_load_font(&font_text, "../../fonts/ChalkItUp.ttf", 100);
	jhi_load_font(&font_borda, "../../fonts/ChalkItUp.ttf", 105);
	jhi_load_font(&font_button, FONT_PATH, 20);
	jhi_load_image_with_transparent_color(&menu_img, "../images/balao.png", BLACK);
	jhi_load_image_with_transparent_color(&menu_img2, "../images/balao.png", BLACK);

	jhi_resize_image(&menu_img, 250, 200);
	jhi_resize_image(&menu_img2, 250, 200);

	jhi_init_text(&pop);
	jhi_init_text(&ball);

	jhi_init_text(&pop_borda);
	jhi_init_text(&ball_borda);

	pop.pos.x = 190;
	pop.pos.y = 220;

	pop_borda.pos.x = 190;
	pop_borda.pos.y = 219;

	jhi_set_text(&font_text, &pop, RED, "POP");
	jhi_set_text(&font_text, &ball, BLUE, "BALL");

	jhi_set_text(&font_borda, &pop_borda, BLACK, "POP");
	jhi_set_text(&font_borda, &ball_borda, BLACK, "BALL");

	ball.pos.x = 420;
	ball.pos.y = 250;

	ball_borda.pos.x = 418;
	ball_borda.pos.y = 250;

	menu_img.pos.x = 400;
	menu_img.pos.y = 60;

	menu_img2.pos.x = 140;
	menu_img2.pos.y = 30;

	init_button(&vet_buttons[0], &font_button, "Iniciar Jogo", BUTTON_TYPE_1);
	init_button(&vet_buttons[1], &font_button, "Sair do Jogo", BUTTON_TYPE_1);

	set_button_size(&vet_buttons[0], 250, 50);
	set_button_size(&vet_buttons[1], 250, 50);


    while (jhi_get_close_window() != JHI_CLOSE && pos == -1)
    {
    	jhi_update();
    	jhi_clean();
    	jhi_draw_image(background, background->pos);
    	draw_button(&vet_buttons[0], jhi_get_point(jhi_get_central_pos(LARGURA, ALTURA, 250, 50).x, 400));
    	draw_button(&vet_buttons[1], jhi_get_point(jhi_get_central_pos(LARGURA, ALTURA, 250, 50).x, 500));

    	jhi_draw_text(&pop_borda, pop_borda.pos);
    	jhi_draw_text(&ball_borda, ball_borda.pos);

    	jhi_draw_text(&pop, pop.pos);
    	jhi_draw_text(&ball, ball.pos);

    	jhi_draw_image(&menu_img, menu_img.pos);
    	jhi_draw_image(&menu_img2, menu_img2.pos);

        for (j = 0; j < jhi_get_number_of_events(); j++)
        {
    		/* Pega o status do mouse no evento j */
    		*mouse = jhi_get_mouse_status(j);
    			//pos = 0 indica inciar jogo
    			//pos = 1 indica sair do jogo
    			//pos = -1 nenhum botão clicado, o loop continua
    		pos = check_buttons(*mouse, vet_buttons, 2);
        }
    }

    jhi_free_font(&font_text);
    jhi_free_font(&font_borda);
    jhi_free_font(&font_button);
    jhi_free_text(&pop);
    jhi_free_text(&ball);
    jhi_free_text(&pop_borda);
    jhi_free_text(&ball_borda);
    jhi_free_image(&menu_img);
    jhi_free_image(&menu_img2);
    free_button(&vet_buttons[0]);
    free_button(&vet_buttons[1]);

    if (pos == -1 || pos == 1)
    {
    	is_exit = 1;
    }


}

void gameplay_screen(JHI_Text *texto_pontos, JHI_MouseSt *mouse,
		JHI_Font *fonte_game_over, JHI_Font *fonte_pontos, JHI_Image *background)
{

	Button vet_buttons[2];
	int pos = -1,j;
	JHI_Font font_button;


	jhi_load_font(&font_button, FONT_PATH, 20);

	init_button(&vet_buttons[0], &font_button, "Jogar Novamente", BUTTON_TYPE_1);
	init_button(&vet_buttons[1], &font_button, "Menu Principal", BUTTON_TYPE_1);

	set_button_size(&vet_buttons[0], 300, 50);
	set_button_size(&vet_buttons[1], 300, 50);

    while (jhi_get_close_window() != JHI_CLOSE)
    {
		jhi_timer_start();
		jhi_update();
		jhi_clean();

		/* Desenha a imagem de plano de fundo */
		jhi_draw_image(background, background->pos);

		if(game_over)
		{
		    for (j = 0; j < jhi_get_number_of_events(); j++)
		    {
				/* Pega o status do mouse no evento j */
				*mouse = jhi_get_mouse_status(j);
				pos = check_buttons(*mouse, vet_buttons, 2);
		    }

				/* Desenha o nome Game Over na Tela */
				desenhar_game_over(texto_pontos, fonte_game_over, 95, 200);

				/* Desenha a pontuação na tela */
				desenhar_pontuacao(texto_pontos, fonte_pontos, 250, 100);

				draw_button(&vet_buttons[0], jhi_get_point(jhi_get_central_pos(LARGURA, ALTURA, 250, 50).x, 400));
				draw_button(&vet_buttons[1], jhi_get_point(jhi_get_central_pos(LARGURA, ALTURA, 250, 50).x, 500));



				if (pos == 0) break;
				else if (pos == 1) {is_menu = 1; break;}



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

    inicialiar_jogo();
    if (pos == -1) is_exit = 1;

    free_button(&vet_buttons[0]);
    free_button(&vet_buttons[1]);
    jhi_free_font(&font_button);
}

int main()
{
	int i;	
    jhi_initialize_window(LARGURA, ALTURA, 32, WHITE);
    jhi_choice_window_name("Pop-Ball");
    
    /* Essa estrutura contém os campos x,y atual do mouse e captura algum evento ocorrido */
    JHI_MouseSt mouse;
    jhi_init_mouse(&mouse);	/* inicializar mouse */

    /* Estrutura da fonte */
	JHI_Font fonte_game_over, fonte_pontos;

	/* Estrutura de texto */
	JHI_Text texto_pontos;

	/* Estrutura de Imagem */
	JHI_Image background;

	/* Carrega a fonte e inicializa a variavel texto */
	jhi_load_font(&fonte_game_over, FONT_PATH, 70);
	jhi_load_font(&fonte_pontos, FONT_PATH, 30);
	jhi_init_text(&texto_pontos);
	jhi_load_image(&background, "../images/Background.png");

	jhi_load_image_with_transparent_color(&cara_bola[0], "../images/b1.png", BLACK);
	jhi_load_image_with_transparent_color(&cara_bola[1], "../images/b2.png", BLACK);
	jhi_load_image_with_transparent_color(&cara_bola[2], "../images/b3.png", BLACK);
	jhi_load_image_with_transparent_color(&cara_bola[3], "../images/b4.png", BLACK);
	jhi_load_image_with_transparent_color(&cara_bola[4], "../images/b5.png", BLACK);
	jhi_load_image_with_transparent_color(&cara_bola[5], "../images/b6.png", BLACK);
	jhi_load_image_with_transparent_color(&cara_bola[6], "../images/b7.png", BLACK);
	//jhi_load_image_with_transparent_color(&cara_bola, "../images/smile.png", BLACK);
	background.pos.x = 0;
	background.pos.y = 0;
	jhi_resize_image(&background, LARGURA, ALTURA);

	for (i = 0; i < 7; i++)
	{
		jhi_resize_image(&cara_bola[i], 2*RAIO_BOLA, 2*RAIO_BOLA);
	}

    /* Seta a quantidade de frames por segundo na tela */
    jhi_set_fps_timer(32);
    
    /* Incia Variaveis e Parametros do Jogo */
    inicialiar_jogo();


    jhi_load_effect(&explosion, "../audio/explosion.wav");
    jhi_load_music(&psi, "../audio/psicose.mp3");
    jhi_load_music(&normal, "../audio/blast_off.mp3");

    /* Desenha a introducao do jogo. Logo da lib é mostrada */
    game_intro_screen();

    while(1) 
    {
	    if(is_exit) break;

	    jhi_replay_music(&normal, -1);

	    if (is_menu)
	    {
	    	game_menu_screen(&background, &mouse);
	    	is_menu = 0;
	    }

	    if(is_exit) break;
	    
	    gameplay_screen(&texto_pontos, &mouse, &fonte_game_over, &fonte_pontos, &background);


	}
	
    /* desalocar as estruturas carregadas */
	jhi_free_text(&texto_pontos);
	jhi_free_font(&fonte_pontos);
	jhi_free_font(&fonte_game_over);

    jhi_quit_and_free();

    return 0;
}
