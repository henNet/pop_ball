#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela
#include "jhi_sound.h" // -> Esse o arquivo que possui as funções referentes aos sons.


//****************************************************************************
//*                                                                          *
//*  Exemplo 7: Carregando Música e capturando eventos do mouse		     *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#define PAUSE 1
#define STOP 2

int main()
{

	int i;

	//essa estrutura contém os campos x,y atual do mouse e captura algum evento ocorrido
	JHI_MouseSt mouse;

	//Estrutura que irá carregar musica para tocar quando clicado botão esquerdo do mouse
	// o botão direito dará um stop ou pause na música, dependendo da variavel mode
	JHI_Music music;

	int mode = PAUSE;

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, BLACK);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 7");

	//carregando Música

	jhi_load_music(&music, "../sounds/Prelude_in_C_BWV_846.mp3");

	//inicializar mouse

	jhi_init_mouse(&mouse);

	//A função get_close_window() retorna se foi clicado no X da janela, dessa forma
	// o retorno é igual a CLOSE, então o loop principal deve ser quebrado, indicando
	//que o programa deve ser fechado
	while (jhi_get_close_window() != JHI_CLOSE)
	{
		//Essas duas funções devem sempre esta no começo do loop
		//update() -> função de atualização das ações feitas dentro do loop
		//clean() -> função para limpar a tela, para desenhar novamente na próxima iteração
		jhi_update();
		jhi_clean();


		//Esse for captura todos os eventos de mouse e teclado
		//em cada iteração pegamos um evento
		for (i = 0; i < jhi_get_number_of_events(); i++)
		{
			//Pega o status do mouse no evento i
			mouse = jhi_get_mouse_status(i);

			//se foi clicado botão esquerdo do mouse
			if (mouse.mouse_event == ON_CLICK_LEFT)
			{
				//executa a música, -1 indica para música tocar em loop
				// se for passando um numero positivo indica número de repetições
				jhi_play_music(&music, -1);
			}
			//senão se foi clicado botão direito
			else if (mouse.mouse_event == ON_CLICK_RIGHT)
			{
				if (mode == PAUSE)
				{
					jhi_pause_music();
				}
				else if (mode == STOP)
				{
					jhi_stop_music();
				}
			}
		}

	}

	//desalocar a música que foi carregada
	jhi_free_music(&music);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
