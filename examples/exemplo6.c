#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela, inclusive
#include "jhi_sound.h" // -> Esse o arquivo que possui as funções referentes aos sons.
#include "jhi_mouse.h" // -> Esse o arquivo que possui as funções referentes ao mouse.

//****************************************************************************
//*                                                                          *
//*  Exemplo 6: Carregando efeitos de som e capturando eventos do mouse	     *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/


int main()
{

	int i;

	//essa estrutura contém os campos x,y atual do mouse e captura algum evento ocorrido
	JHI_MouseSt mouse;

	//Estrutura que irá carregar efeito1 para tocar quando clicado botão esquerdo do mouse
	JHI_Effect effect1;

	//Estrutura que irá carregar efeito1 para tocar quando clicado botão direito do mouse
	JHI_Effect effect2;

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, BLACK);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 6");

	//carregar efeitos

	jhi_load_effect(&effect1, "../sounds/efect1.wav");

	jhi_load_effect(&effect2, "../sounds/efect2.wav");

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
				//executa o efeito com 0 segundos de delay
				jhi_play_effect(&effect1, 0);
			}
			//senão se foi clicado botão direito
			else if (mouse.mouse_event == ON_CLICK_RIGHT)
			{
				//executa o efeito com 0 segundos de delay
				jhi_play_effect(&effect2, 0);
			}
		}

	}

	//desalocar o efeito que foi carregado
	jhi_free_effect(&effect1);

	//desalocar o efeito que foi carregado
	jhi_free_effect(&effect2);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
