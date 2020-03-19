from domain import Jucator
from repository import RepositoryJucator,FileRepositoryJucator
from validare import ValidareJucator
from service import ServiceJucator
from ui import Console
from exceptii import *
from teste import TesteJucator

repo=FileRepositoryJucator("jucatori.txt",Jucator.read,Jucator.write)
valid=ValidareJucator()
srv=ServiceJucator(valid,repo)
ui=Console(srv)
teste=TesteJucator()

teste.ruleaza()
ui.run()
