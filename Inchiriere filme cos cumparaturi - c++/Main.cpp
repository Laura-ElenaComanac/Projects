#include "UI.h"
#include "Teste.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main() {
	{
		testFilm();
		testRepo();
		testService();
		testStatistica();
		//testVectorDinamic();
		Repository repo;
		Service srv{ repo };
		UI ui{ srv };
		ui.run();
	}
	_CrtDumpMemoryLeaks();

	/*
	VectorDinamic<int> v;//doar declarare
	v.addElem(4);
	v.addElem(22);

	VectorDinamic<int> v2 = v;//declarare si initializare

	v2.addElem(5);
	v = v.operator=(v2);//copiere
	*/
	return 0;
}