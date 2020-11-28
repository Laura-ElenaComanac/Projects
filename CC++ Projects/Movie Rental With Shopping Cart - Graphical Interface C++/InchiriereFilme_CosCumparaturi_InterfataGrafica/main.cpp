#include "InchiriereFilme_CosCumparaturi_InterfataGrafica.h"
#include "CosGUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	RepositoryFile repoFile{ "Filme.txt", 0 };
	Service srv{ repoFile };
	UI ui{ srv };
	FilmeGUI gui{ srv , ui};
	//CosGUI guiCos{ srv };

	gui.show();

	return a.exec();
}
