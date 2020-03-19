from domain import Produs
from repository import RepositoryProdus, FileRepositoryProdus
from validare import ValidMagazin
from service import ServiceMagazin
from ui import Console
from teste import TesteMagazin
from exceptii import *

repo=FileRepositoryProdus("produse.txt",Produs.read,Produs.write)
valid=ValidMagazin()
srv=ServiceMagazin(repo,valid)
ui=Console(srv)

teste=TesteMagazin()

teste.ruleaza()
ui.run()