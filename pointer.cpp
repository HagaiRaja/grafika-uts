#include "map/control.h"
#include <pthread.h>
using namespace std;

int main(int argc, char const *argv[])
{
	bool running = true;
	init();

	// setting up backgroung color to black
	color black = {0,0,0,0};
	set_background(&black);

	while (running) {
		
		running = getCommand();
	}
	close_buffer_without_read();
	return 0;
}