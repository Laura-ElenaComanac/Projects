#include "UI.h"

int main() {
	{
		testFilm();//domain
		testRepo();//repo
		testFilmService();//service
		Repository repo;
		Service srv{ repo };
		UI ui{ srv };
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}