#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <Button.h>

extern Button UpBtn;
extern  Button EnterBtn;
extern Button DownBtn;

class KeyBoard
{
	private:
		long UpBtnCpt;
		long EnterBtnCpt;
		long DownBtnCpt;
	public:
		KeyBoard();
		void Compute();
};

extern KeyBoard Clavier;
#endif