#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela,
#include "jhi_image.h" //-> Esse arquivo é header da estrutura Image
#include "jhi_sound.h"
#include "jhi_joystick.h"
#include "jhi_timer.h"


//****************************************************************************
//*                                                                          *
//*  Exemplo 12: Pac Man com Joystick					     			 	 *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

//largura e altura de cada pac_man na figura
#define WIDHT_PAC_MAN 32
#define HEIGHT_PAC_MAN 32
#define NUMBER_CLIPS 8



//checa a figura atual e a proxima direção e
//move de acordo com o valor
static int get_next_clip_pos_and_move(int current_pos, JHI_JOY_DIR_ next_dir, int *x, int *y)
{
	if (current_pos % 2)
	{
		switch(next_dir)
		{
			case JOY_RIGHT:
				*x += WIDHT_PAC_MAN/4;
				return 0;
			case JOY_DOWN:
				*y += HEIGHT_PAC_MAN/4;
				return 2;
			case JOY_LEFT:
				*x -= WIDHT_PAC_MAN/4;
				return 4;
			case JOY_UP:
				*y -= HEIGHT_PAC_MAN/4;
				return 6;
		}
	}
	else
	{
		switch(next_dir)
		{
			case JOY_RIGHT:
				*x += WIDHT_PAC_MAN/4;
				return 1;
			case JOY_DOWN:
				*y += HEIGHT_PAC_MAN/4;
				return 3;
			case JOY_LEFT:
				*x -= WIDHT_PAC_MAN/4;
				return 5;
			case JOY_UP:
				*y -= HEIGHT_PAC_MAN/4;
				return 7;
		}
	}

	return current_pos;
}


int main()
{

	//Cada posição do vetor representa a posição x do pac_man na imagem
	//como são 8 pac_man's são 8 posições (x,y);
	JHI_Point2d vet_pos[]  = {
	{0,0}, {WIDHT_PAC_MAN,0}, {0, HEIGHT_PAC_MAN}, {WIDHT_PAC_MAN, HEIGHT_PAC_MAN},
	{0, HEIGHT_PAC_MAN*2}, {WIDHT_PAC_MAN, HEIGHT_PAC_MAN*2}, {0, HEIGHT_PAC_MAN*3}, {WIDHT_PAC_MAN,HEIGHT_PAC_MAN*3}
	};

	//Esse estrutura contém eventos do joystick
	JHI_JoystickSt joy;

	//imagem com todos as posições do pac_man
	JHI_Image img_pac_man;

	JHI_Effect pac_sound;

	JHI_Music pac_intro;

	//posição de qual clip será desenhado, os valores assumidos vai de 0 a 7
	int pos = 0;
	int i;
	JHI_Point2d point;
	int x = 100;
	int y = 100;
	int x_vel = 0;
	int y_vel = 0;
	int res_pos;
	int axis_index;
	int control_efect = 10;

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, BLACK);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 12");

	//A cor de fundo do pac_man é o azul de valores (0, 0, 255) do modelo RGB
	// a cor BLUE contém esses valores, logo esse cor de fundo fica transparente
	jhi_load_image_with_transparent_color(&img_pac_man, "../images/pac_man.png", BLUE);

	jhi_set_fps_timer(24);

	jhi_load_effect(&pac_sound, "../sounds/waka.wav");
	jhi_load_music(&pac_intro, "../sounds/pacman_intro.mp3");

	//Tocar a Música
	jhi_play_music(&pac_intro, 1);

	//Espera 5 segundos para música tocar
	jhi_delay_seconds(5);


	//ativa o joystick 1
	jhi_open_joystick_index(0);


	//inicializar a estrutura do joystick
	jhi_init_joystick(&joy);


	//A função get_close_window() retorna se foi clicado no X da janela, dessa forma
	// o retorno é igual a CLOSE, então o loop principal deve ser quebrado, indicando
	//que o programa deve ser fechado
	while (jhi_get_close_window() != JHI_CLOSE)
	{
		//Essas duas funções devem sempre esta no começo do loop
		//update() -> função de atualização das ações feitas dentro do loop
		//clean() -> função para limpar a tela, para desenhar novamente na próxima iteração
		//Antes de qualquer ação dentro deve ser inicializado o temporizador para ser calculado a quantidade
		//de tempo necessária para executar cada iteração do loop
		jhi_timer_start();
		jhi_update();
		jhi_clean();

		//Esse for captura todos os eventos de mouse e teclado
		//em cada iteração pegamos um evento

		for (i = 0; i < jhi_get_number_of_events(); i++)
		{
			//Pega o status do joystick no evento i
			axis_index = jhi_get_joystick_status(i).axis_index;

			//Se houve movimento nos eixos
			if (jhi_get_joystick_status(i).joy_event == JHI_JOY_AXIS_MOTION)
			{
				joy.axis_value[axis_index] = jhi_get_joystick_status(i).axis_value[axis_index];
			}
		}


		// Se os dois eixos pressionados movimento na diagonal

		if (joy.axis_value[0] && joy.axis_value[1])
		{
			res_pos = get_next_clip_pos_and_move(pos, jhi_get_joystick_dir(&joy, 1), &x_vel, &y_vel);
			pos = get_next_clip_pos_and_move(pos, jhi_get_joystick_dir(&joy, 0), &x_vel, &y_vel);

			//controla o efeito wakawaka do pac_man
			if(control_efect == 10)
			{
				jhi_play_effect(&pac_sound, 0);
				control_efect = 0;
			}
			else
			{
				control_efect++;
			}
		}

		//Se um dos eixos foi pressionado
		else if (joy.axis_value[0] || joy.axis_value[1])
		{
			//tenta mover no eixo 0 direita-esquerda do controle
			res_pos = get_next_clip_pos_and_move(pos, jhi_get_joystick_dir(&joy, 0), &x_vel, &y_vel);
			
			//Senao moveu o eixo 0, então mova o eixo 1
			if (res_pos == pos)
			{
				pos = get_next_clip_pos_and_move(pos, jhi_get_joystick_dir(&joy, 1), &x_vel, &y_vel);
			}
			// se res_pos != pos é por que o movimento já fo no eixo 0, entçao pos = res_pos
			else
			{
				pos = res_pos;
			}

			//controla o efeito wakawaka do pac_man
			if(control_efect == 10)
			{
				jhi_play_effect(&pac_sound, 0);
				control_efect = 0;
			}
			else
			{
				control_efect++;
			}
		}

		point.x = x + x_vel;
		point.y = y + y_vel;
		
		//Desenha o sprite correto do pacman
		jhi_draw_image_with_clip(&img_pac_man, point, vet_pos[pos], WIDHT_PAC_MAN,  HEIGHT_PAC_MAN);

		//Espera tempo necessário para controlar a quantidade de frames por segundo
		jhi_wait_time();
	}

	//desalocar a imagem que foi carregada
	jhi_free_image(&img_pac_man);

	jhi_free_music(&pac_intro);

	jhi_free_effect(&pac_sound);

	jhi_free_joystick_index(0);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
