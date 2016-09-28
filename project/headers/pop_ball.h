#ifndef _POP_BALL_H_
#define _POP_BALL_H_

/* C Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h>

/* JHI Includes */
#include "jhi_window.h" /* Esse header está no diretório da biblioteca */
#include "jhi_timer.h"  /* Temporização para animação */
#include "jhi_font.h"   /* Esse arquivo é header da estrutura Font */
#include "jhi_text.h"   /* Esse arquivo é header da estrutura Text */
#include "jhi_shapes.h"

#define RAIO_BOLA 50
#define PONTOS 10
#define MAX_GAME_LEVEL 20

struct Bolas{
	int id_cor_bolas;
    JHI_Point2d pontos;
} bolas_caindo[20];

/* Variáveis Globais  */
int game_level;
int level_up;
int pontuacao;
int game_over;
int vel_incremento;		/* velocidade da bola caindo */

/* Funções do Jogo */
void init_bolas(int faixa_x, int faixa_y);
void set_game_level(int level);
void set_pontuacao(int pontos);
int get_pontuacao();
void incrementa_pontuacao(int pontos);
void set_random_seed();
int gerar_random_number(int faixa);
int mouse_dentro_bola(int centro_x, int centro_y, int mouse_pos_x, int mouse_pos_y);
void desenhar_bolas_caindo(int altura_janela);
void verificar_eventos_mouse(JHI_MouseSt *mouse, int largura_janela);
void verificar_level_up();
void verificar_game_over(int altura_janela);
void desenhar_pontuacao(JHI_Text *texto, JHI_Font *fonte, int text_pos_x, int text_pos_y);
void desenhar_game_over(JHI_Text *texto, JHI_Font *fonte, int text_pos_x, int text_pos_y);

#endif