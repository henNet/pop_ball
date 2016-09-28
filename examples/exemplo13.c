#include "jhi_window.h" /* Esse o arquivo que possui as funções referentes a janela, inclusive */
#include "jhi_image.h"  /* Esse arquivo é header da estrutura Image */
#include "jhi_sound.h"
#include "jhi_shapes.h"
#include "jhi_font.h"
#include "jhi_text.h"
#include "jhi_rand.h"
#include <math.h>
#include <stdlib.h>

//****************************************************************************
//*                                                                          *
//*  Exemplo 13: Joguinho com seu próprio personagem		                 *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

/* Tamanho da Tela */
#define SCREEN_WIDHT 800
#define SCREEN_HEIGHT 600

/* Largura e altura do personagem na figura */
#define WIDTH_PERSON 64
#define HEIGHT_PERSON 130
#define NUMBER_CLIPS 6

#define ANGLE 45
#define GRAVIDADE 4
#define VEL 20
#define JUMP_VERT 0
#define JUMP_OBLI 1


JHI_Effect jump;
JHI_Effect die;

static void sound_jump()
{
	jhi_play_effect(&jump, 0);
}


static void atualizaY_subindo(int *y, int *vel)
{
	*y = *y - *vel;
	*vel = *vel - GRAVIDADE/2;
}

static void atualizaY_descendo(int *y, int *vel)
{
	*y = *y + *vel;
	*vel = *vel + GRAVIDADE/2;
}

static void atualizaY_subindo_ob(int *y, int *x, int *vel)
{
	*y = *y - *vel * sin(ANGLE);
	*x = *x + 15 * cos(ANGLE);
	*vel = *vel - GRAVIDADE/2;
}

static void atualizaY_descendo_ob(int *y, int *x, int *vel)
{
	*y = *y + *vel * sin(ANGLE);
	*x = *x + 15 * cos(ANGLE);
	*vel = *vel + GRAVIDADE/2;
}


/* Checa a figura atual e a proxima direção e
   move de acordo com o valor */
static void get_next_clip_pos_and_move(int *current_pos, int *current_pos_down, int *direction_down,
								int *end_jump, JHI_Keys next_dir, int *x, int *y, int *not_press)
{
	//if(*not_press == 1)
		//return;

	switch(next_dir)
	{
		case KEY_RIGHT:
			/* Faz o persoangem se mover WIDTH_PERSON/4 para a direita */
			*x += WIDTH_PERSON/4;
			*direction_down = 1;

			/* Faz o personagem voltar a posicao inicial e andar novamente*/
			if(*current_pos >= NUMBER_CLIPS) {
				*current_pos = 0;
			}
			*current_pos = *current_pos + 1;
			break;

		case KEY_LEFT:
			/* Faz o persoangem se mover WIDTH_PERSON/4 para a esquerda */
			*x -= WIDTH_PERSON/4;
			*direction_down = 0;

			/* Faz o personagem voltar a posicao inicial e andar novamente*/
			if(*current_pos <= NUMBER_CLIPS + 1) {
				*current_pos = 2 * NUMBER_CLIPS + 1;
			}
			*current_pos = *current_pos - 1;

			break;

		case KEY_DOWN:
			if(*direction_down == 1) {
				if(*current_pos_down >= 1) {
					*current_pos_down = 1;
				}else
					*current_pos_down = *current_pos_down + 1;

			}else if(*direction_down == 0) {
				if(*current_pos_down <= 2) {
					*current_pos_down = 2;
				}else
					*current_pos_down = *current_pos_down - 1;
			}

			break;

		case KEY_UP:
			if(*not_press == 0)
				sound_jump();
			*end_jump = 0;
			*not_press = 1;
			break;
	}
}

void get_next_clip_pos_to_jump(int *pos_jump, int *vel, int *status, int *control, int *not_press,
							   int *x_jump, int *y_jump, int *end_jump, int *x_vel, int type_jump)
{
	if(*status) {
		if(*vel > 0) {
			if(type_jump == 0)
				atualizaY_subindo(y_jump, vel);
			else
				atualizaY_subindo_ob(y_jump, x_jump, vel);

			if(*control == 1) {
				*pos_jump = *pos_jump + 1;
				*control = 0;
			}else
				*control = 1;


			if(*pos_jump >= NUMBER_CLIPS/2)
				*pos_jump = NUMBER_CLIPS/2;
		}
		else
		{
			*status = 0;
			*control = 0;
		}
	}
	else {
		if (*y_jump < 100 + HEIGHT_PERSON) {
			if(type_jump == 0)
				atualizaY_descendo(y_jump, vel);
			else
				atualizaY_descendo_ob(y_jump, x_jump, vel);

			if(*control == 1) {
				*pos_jump = *pos_jump + 1;
				*control = 0;
			}else
				*control = 1;

			if(*pos_jump > NUMBER_CLIPS)
				*pos_jump = NUMBER_CLIPS;
		}
	}

	if(*pos_jump >= NUMBER_CLIPS) {
		*pos_jump = 0;
		*x_vel += *x_jump;
		*y_jump = 0;
		*x_jump = 0;
		*vel = VEL;
		*status = 1;
		*end_jump = 1;
		*not_press = 0;
	}
}

static int colision(int x1, int y1, int x2, int y2)
{
	if(x1 >= x2 && x1 <= (x2 + WIDTH_PERSON) &&
	   y1 >= y2	&& y1 <= (y2 + HEIGHT_PERSON)){

		return 1;
	}

	return 0;
}

static int colision_down(int x1, int y1, int x2, int y2)
{
	if(x1 >= x2 && x1 <= (x2 + WIDTH_PERSON) &&
	   y1 >= y2	&& y1 <= (y2 + HEIGHT_PERSON/6)){

		return 1;
	}

	return 0;
}

static int colision_up(int x1, int y1, int radio, int x2, int y2)
{

	if (y2 + HEIGHT_PERSON - 20 <= y1)
	{
		return 0;
	}

	if (y2 >= y1 + radio)
	{
		return 0;
	}

	if (x2 + WIDTH_PERSON <= x1)
	{
		return 0;
	}

	if (x2 - WIDTH_PERSON >= x1 + radio)
	{
		return 0;
	}

	return 1;
}

int main()
{
	/* Cada posição do vetor representa a posição x do personagem na imagem
	   são 14 figuras do personagem, logo 14 posições (x,y); */
	JHI_Point2d vet_move[]  = { {0,0}, {WIDTH_PERSON,0}, {WIDTH_PERSON*2,0}, {WIDTH_PERSON*3,0}, {WIDTH_PERSON*4,0},
			{WIDTH_PERSON*5,0}, {WIDTH_PERSON*6,0},{0,HEIGHT_PERSON}, {WIDTH_PERSON,HEIGHT_PERSON}, {WIDTH_PERSON*2,HEIGHT_PERSON},
	{WIDTH_PERSON*3,HEIGHT_PERSON}, {WIDTH_PERSON*4,HEIGHT_PERSON}, {WIDTH_PERSON*5,HEIGHT_PERSON}, {WIDTH_PERSON*6,HEIGHT_PERSON}

	};

	JHI_Point2d vet_down[] = {{0,0}, {WIDTH_PERSON,0}, {2*WIDTH_PERSON,0}, {3*WIDTH_PERSON,0},
			{4*WIDTH_PERSON,0}, {5*WIDTH_PERSON,0}
	};

	JHI_Point2d vet_jump[] = { {0,0}, {WIDTH_PERSON,0}, {2*WIDTH_PERSON,0}, {3*WIDTH_PERSON,0},
			{4*WIDTH_PERSON,0}, {5*WIDTH_PERSON,0}, {6*WIDTH_PERSON,0}, {0,HEIGHT_PERSON}, {WIDTH_PERSON,HEIGHT_PERSON},
			{2*WIDTH_PERSON,HEIGHT_PERSON}, {3*WIDTH_PERSON,HEIGHT_PERSON},
			{4*WIDTH_PERSON,HEIGHT_PERSON}, {5*WIDTH_PERSON,HEIGHT_PERSON}, {6*WIDTH_PERSON,HEIGHT_PERSON}
	};


	JHI_Point2d ball[] = {{900,200 + HEIGHT_PERSON/4}, {900, 200 + HEIGHT_PERSON/2 + 5}
		};


	/* Esse estrutura contém eventos do teclado e tecla pressionadas */
	JHI_KeyboardSt key;

	/* Estrutura da fonte */
	JHI_Font f1;

	/* Estrutura de texto */
	JHI_Text t1;

	/* Imagem com todos as posições do personagem */
	JHI_Image img_person_walk;
	JHI_Image img_person_down_die;
	JHI_Image img_person_jump;

	/* Imagem com o scenario do jogo */
	JHI_Image scenario;

	/* Variaveis de controle do personagem e elementos do jogo */
	int pos_walk = 0;
	int pos_down = -1;
	int pos_jump = 0;
	int pos_die = 4;
	int direction_down = 1; /* 0 - Esquerda. 1 - Direita */
	int i;
	int x = 200;
	int y = 200;
	int x_vel = 0;
	int y_vel = 0;
	int x_center = 900;
	int move = 0;
	int person_die = 0;
	int status_die = 1;
	int index_ball = 0;
	int play_die = 1;
	float limit = 0.5000000000;
	JHI_Point2d point;
	JHI_Keys cur_key;
	JHI_Keys last_key_press;

	int status_jump = 1;	/* 1 - Subindo, 0 - Descendo */
	int vel = VEL;
	int y_jump = 0;
	int x_jump = 0;
	int control = 0; 	/* Genrencia os frames do JUMP */
	int end_jump = 0; 	/* 0 - Começa do JUMP, 1 - Fim do JUMP */
	int not_press = 0;

	/* Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte, ... */
	jhi_initialize_window(SCREEN_WIDHT, SCREEN_HEIGHT, 32, WHITE);

	/* Nessa função escolhemos o nome da janela, que ficará no topo da tela */
	jhi_choice_window_name("Exemplo 13");

	/* A cor de fundo do personagem é o preto de valores (0, 0, 0) do modelo RGB
	   a cor BLACK contém esses valores, logo esse cor de fundo fica transparente */
	jhi_load_image(&scenario, "../images/game_cenario.png");
	jhi_load_image_with_transparent_color(&img_person_walk, "../images/person_walk.png", BLACK);
	jhi_load_image_with_transparent_color(&img_person_down_die, "../images/person_down_die.png", BLACK);
	jhi_load_image_with_transparent_color(&img_person_jump, "../images/person_jump.png", BLACK);

	//Carregar em f1 a fonte localizada da pasta font, com tamanho de fonte 40
	//essa fonte não contem os caracteres alguns caracteres utilizados no português
	//outras fontes podem conter
	jhi_load_font(&f1, "../fonts/PonyMaker.ttf", 40);

	jhi_load_effect(&jump, "../sounds/Jump-SoundBible.com-1007297584.wav");
	jhi_load_effect(&die, "../sounds/Sad_Trombone-Joe_Lamb-665429450.wav");

	jhi_set_fps_timer(20);

	jhi_init_text(&t1);

	jhi_init_keyboard(&key);

	/* A função get_close_window() retorna se foi clicado no X da janela, dessa forma
	   o retorno é igual a CLOSE, então o loop principal deve ser quebrado, indicando
	   que o programa deve ser fechado */
	while (jhi_get_close_window() != JHI_CLOSE)
	{
		/* Essas duas funções devem sempre esta no começo do loop
		   - update() -> função de atualização das ações feitas dentro do loop
		   - clean() -> função para limpar a tela, para desenhar novamente na próxima iteração
		   Antes de qualquer ação dentro deve ser inicializado o temporizador para ser calculado a quantidade
		   de tempo necessária para executar cada iteração do loop */
		jhi_timer_start();
		jhi_update();
		jhi_clean();

		/* Desenha o scenario */
		point.x = 0;
		point.y = 0;
		jhi_draw_image(&scenario, point);

		/* Verifica se o personagem morreu para encerrar o jogo */
		if(person_die) {

			if (play_die)
			{
				jhi_play_effect(&die, 0);
				play_die = 0;
			}

			/* Desenha a morte do personagem na posição(x, y) corrente e com o movimento adequado*/

			point.x = x + x_vel;
			point.y = y + y_vel;

			jhi_draw_image_with_clip(&img_person_down_die, point,vet_down[pos_die],
									  WIDTH_PERSON,  HEIGHT_PERSON);

			/* Altenar entre os Clips de morte */
			if(pos_die == 4)
				pos_die = 5;
			else
				pos_die = 4;

			/* Calcula a trajetoria da morte do personagem */
			if(status_die) {
				if(vel > 0) {
					atualizaY_subindo(&y_vel, &vel);
				}
				else
				{
					status_die = 0;
				}
			}
			else {
				if (y < 570) {
					atualizaY_descendo(&y_vel, &vel);
					if (y_vel > 570){y_vel = 600;}
				}
			}

			/* Desenha Fim na tela */
			jhi_set_text(&f1, &t1, BLACK, "FIM");
			t1.pos.x = SCREEN_WIDHT/2 - 45;
			t1.pos.y = SCREEN_HEIGHT/3;
			jhi_draw_text(&t1, t1.pos);

			/* Espera tempo necessário para controlar a quantidade de frames por segundo */
			jhi_wait_time();

			continue;
		}

		/* Esse for captura todos os eventos de mouse e teclado
		   em cada iteração pegamos um evento */
		for (i = 0; i < jhi_get_number_of_events(); i++)
		{
			/* Pega o status do teclado no evento i */
			key = jhi_get_keyboard_status(i);

			if (jhi_is_key_arrow(key.key))
			{
				/* se o teclado foi pressionado com a direção não atual
				   ative o movimento e atualize a direção atual */
				if (key.key_event == KEYBOARD_DOWN && key.key != cur_key)
				{
					move = 1;
					cur_key = key.key;

				}
				/* se o teclado foi soltado com a direção atual
				   então desative o movimento */
				else if (key.key_event == KEYBOARD_UP && key.key == cur_key)
				{
					move = 0;
					cur_key = NO_KEY;
				}
			}
		}

		if (move)
		{
			get_next_clip_pos_and_move(&pos_walk, &pos_down, &direction_down,
									   &end_jump, cur_key, &x_vel, &y_vel, &not_press);
			if(not_press == 1)
				last_key_press = KEY_UP;
			else
				last_key_press = cur_key;


		}else if(last_key_press == KEY_RIGHT) {
			/* Faz o personagem voltar a posição direita inicial quando ultima tecla pressionada foi RIGHT */
			pos_walk = 0;
			pos_down = -1;
			pos_jump = 0;
			y_jump = 0;
			vel = VEL;
			status_jump = 1;
		}
		else if(last_key_press == KEY_LEFT) {
			/* Faz o personagem voltar a posição esquerda inicial quando ultima tecla pressionada foi LEFT */
			pos_walk = 2 * NUMBER_CLIPS + 1;
			pos_down = 4;
			pos_jump = 0;
			y_jump = 0;
			vel = VEL;
			status_jump = 1;
		}
		else if(last_key_press == KEY_DOWN) {
			if(direction_down == 1) {
				pos_walk = 0;
				pos_down = -1; /* 1 a menos para que o 1-frame-rigth do DOWN seja exibido */
				pos_jump = 0;
				y_jump = 0;
				vel = VEL;
				status_jump = 1;
			}else{
				pos_walk = 2 * NUMBER_CLIPS + 1;
				pos_down = 4; /* 1 a mais para que o 1-frame-left do DOWN seja exibido */
			}
		}else if(last_key_press == KEY_UP){
			if(direction_down == 1) {
				pos_walk = 0;
				pos_down = -1; /* 1 a menos para que o 1-frame-rigth do DOWN seja exibido */
			}else{
				//pos_walk = 2 * NUMBER_CLIPS + 1;
				pos_walk = 0;
				pos_down = 4; /* 1 a mais para que o 1-frame-left do DOWN seja exibido */
			}
		}

		if(cur_key == KEY_DOWN && not_press != 1) {
			/* Desenha o personagem na posição(x, y) corrente e com o movimento adequado */
			point.x = x + x_vel;
			point.y = y;
			jhi_draw_image_with_clip(&img_person_down_die, point,
									  	  vet_down[pos_down],
									  WIDTH_PERSON,  HEIGHT_PERSON);

		}else if(last_key_press == KEY_UP && end_jump == 0){

			/* Calcula as coordenadas e posições para desenhar o personagem pulando verticalmente */

			get_next_clip_pos_to_jump(&pos_jump, &vel, &status_jump, &control, &not_press,
									  &x_jump, &y_jump, &end_jump, &x_vel, JUMP_OBLI);

			point.x = x + x_vel + x_jump;
			point.y = y + y_jump;

			/* Desenha o personagem na posição(x, y) corrente e com o movimento adequado */
			jhi_draw_image_with_clip(&img_person_jump, point,
									  	  vet_jump[pos_jump],
									  WIDTH_PERSON,  HEIGHT_PERSON);

		}else if(not_press != 1) {
			/* Desenha o personagem na posição(x, y) corrente e com o movimento adequado*/
			point.x = x + x_vel;
			point.y = y;
			jhi_draw_image_with_clip(&img_person_walk, point,
									  vet_move[pos_walk], WIDTH_PERSON,  HEIGHT_PERSON);
		}

		/* Desenha um bola para atingir o personagem */
		jhi_draw_fill_rect(ball[index_ball], 10, 10, RED);

		/* Controla Animação da bola */
		if(ball[index_ball].x > 0)
			ball[index_ball].x -= 15;
		else{
			ball[index_ball].x = 800;

			if(RAND_01 > limit)
				index_ball = 1;
			else
				index_ball = 0;
		}

		if(cur_key == KEY_DOWN){
			if( colision_down(ball[index_ball].x, ball[index_ball].y, x + x_vel, y + y_vel) ) {
				person_die = 1;
			}

		}else if(not_press == 1) { /* Quando not_pess é 1, indica que o personagem esta no ar */
			if( colision_up(ball[index_ball].x, ball[index_ball].y, 10, x + x_vel + x_jump, y + y_vel + y_jump) ) {
						person_die = 1;
			}
		}else{
			if( colision(ball[index_ball].x, ball[index_ball].y, x + x_vel, y + y_vel) ) {
				person_die = 1;
			}
		}

		/* Espera tempo necessário para controlar a quantidade de frames por segundo */
		jhi_wait_time();
	}

	/* desalocar a imagem que foi carregada */
	jhi_free_image(&scenario);
	jhi_free_image(&img_person_walk);
	jhi_free_image(&img_person_down_die);
	jhi_free_image(&img_person_jump);

	/* Limpar alocações feitas pela biblioteca */
	jhi_quit_and_free();

	return 0;
}
