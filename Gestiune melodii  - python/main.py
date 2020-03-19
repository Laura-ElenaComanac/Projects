from domain import Melodie
from repository import RepositoryMelodie,FileRepositoryMelodie
from valid import *
from service import ServiceMelodie
from ui import Console

repo=FileRepositoryMelodie("melodii.txt",Melodie.read,Melodie.write)
valid=Validator()
service=ServiceMelodie(repo,valid)
ui=Console(service)

ui.run()