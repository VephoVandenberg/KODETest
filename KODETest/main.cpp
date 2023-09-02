#include "src/app.h"

int main(int argc, char** argv)
{
	Base::App* app = new Base::App();
	app->run();
	delete app;

	return 0;
}