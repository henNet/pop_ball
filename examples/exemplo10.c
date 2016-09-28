#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela, inclusive
#include "jhi_text.h"
#include "jhi_keyboard.h"

//****************************************************************************
//*                                                                          *
//*  Exemplo 10: Interagindo com o teclado					     			 *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/


int main()
{

	int i;

	//Estrutura da fonte
	JHI_Font f1;

	//Estrutura de texto
	JHI_Text t1;

	//Esse estrutura contém eventos do teclado e tecla pressionadas
	JHI_KeyboardSt key;

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, BLACK);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 10");

	//A função get_close_window() retorna se foi clicado no X da janela, dessa forma
	// o retorno é igual a CLOSE, então o loop principal deve ser quebrado, indicando
	//que o programa deve ser fechado

	//Carregar em f1 a fonte localizada da pasta font, com tamanho de fonte 40
	//essa fonte não contem os caracteres alguns caracteres utilizados no português
	//outras fontes podem conter
	jhi_load_font(&f1, "../fonts/PonyMaker.ttf", 40);

	//inicializar texto
	jhi_init_text(&t1);

	t1.pos.x = 250;
	t1.pos.y = 300;

	jhi_init_keyboard(&key);

	while (jhi_get_close_window() != JHI_CLOSE)
	{
		//Essas duas funções devem sempre esta no começo do loop
		//update() -> função de atualização das ações feitas dentro do loop
		//clean() -> função para limpar a tela, para desenhar novamente na próxima iteração
		jhi_update();
		jhi_clean();


		for (i = 0; i < jhi_get_number_of_events(); i++)
		{

			//Pega o status do teclado no evento i
			key = jhi_get_keyboard_status(i);

			//Se o teclado foi pressionado
			if (key.key_event == KEYBOARD_DOWN)
			{
				//Se teclado DOWN
				if (key.key == KEY_DOWN)
				{
					jhi_set_text(&f1, &t1, RED, "DOWN");
				}
				//Se teclado UP
				else if (key.key == KEY_UP)
				{
					jhi_set_text(&f1, &t1, RED, "UP");
				}
				//Se teclado RIGHT
				else if (key.key == KEY_RIGHT)
				{
					jhi_set_text(&f1, &t1, RED, "RIGHT");
				}
				//Se teclado LEFT
				else if (key.key == KEY_LEFT)
				{
					jhi_set_text(&f1, &t1, RED, "LEFT");
				}
			}
		}

		//desenha o texto na posição (250,300)
		jhi_draw_text(&t1, t1.pos);
	}

	//desalocar a font que foi carregada
	jhi_free_text(&t1);
	//desalocar o texto que foi carregado
	jhi_free_font(&f1);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
