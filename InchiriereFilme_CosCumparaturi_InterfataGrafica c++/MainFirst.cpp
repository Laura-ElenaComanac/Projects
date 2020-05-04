/*#include "UI.h"
#include "Teste.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main() {
	{
		//vector<std::shared_ptr<ActiuneUndo>> actiuniUndo;

		testFilm();
		testRepo();
		testService();
		testStatistica();
		testExceptii();
		//testVectorDinamic();
		string fileName;
		RepositoryFile repoFile{ "Filme.txt", 0.5 };//+0.7 rata de eroare
		Service srv{ repoFile };
		UI ui{ srv };
		ui.run();
		//actiuniUndo.push_back(std::make_shared<UndoAdauga>(repoFile, Film{"a","a",1,"a"}));
	}
	_CrtDumpMemoryLeaks();


	//VectorDinamic<int> v;//doar declarare
	//v.addElem(4);
	//v.addElem(22);

	//VectorDinamic<int> v2 = v;//declarare si initializare

	//v2.addElem(5);
	//v = v.operator=(v2);//copiere

	return 0;
}
*/