#include "cheats.h"

/*
BY : FYH
TIME : 2020.7.16
*/

int main(int argc, char* argv[])
{
	gtav_cheats* g = new gtav_cheats();
	g->initialize_gtav();
	g->start_cheats();
	return 0;
}