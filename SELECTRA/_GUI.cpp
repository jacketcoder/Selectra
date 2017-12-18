#include "_GUI.h"


GUI::GUI()
{
	buttonPlayX = glm::vec2(/*70, 435*/101,619);
	buttonPlayY = glm::vec2(/*575,590*/630,665);
	buttonQuitX = glm::vec2(/*70, 435 */ 101, 619);
	buttonQuitY = glm::vec2(/*595,635*/668,715);
	 UV = glm::vec4(0, 0, 1, 1);
	 _nextWindow = false;


}
void GUI::init(Bengine::SpriteBatch& gui, int width, int height, Bengine::InputManager* input){
	_UI =& gui;
	_destRect.x = 0;
	_destRect.y = 0;
	_destRect.z = width;
	_destRect.w = height;
	_input = input;
	color.setColor(225, 225, 225, 225);
	_uiTexture = Bengine::ResourceManager::getTexture("UI.png").id;
	
}
void GUI::drawObject(){
	_UI->init();
	_UI->begin();
	_UI->draw(_destRect, UV, _uiTexture, 0.0f, color);
	_UI->end();
}
void GUI::renderUI(){
	_UI->renderBatch();
}

int GUI::getCursorPos(int x,int y){
	//a:

	//int x, y;
	//bool check = true;
		//SDL_GetMouseState(&x, &y);
			std::cout << x << "value" << y << std::endl;

			if (x > buttonPlayX.x && x < buttonPlayX.y&&y>buttonPlayY.x && y<buttonPlayY.y){
				std::cout << "play button clicked";
				return 1;
			}

			else if (x > buttonQuitX.x && x < buttonQuitX.y&&y>buttonQuitY.x && y < buttonQuitY.y){
				std::cout << "quit button clicked";
				return 2;
			}
			else {
				return 3;
			}

		//	goto a;
	}
GUI::~GUI()
{
}
