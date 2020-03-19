from domain import Contact
from repository import RepositoryContact, FileRepositoryContact
from validare import ValidareContact
from service import ServiceContact
from ui import Console
from teste import TesteContact
from exceptii import ExceptiiContact

repo=FileRepositoryContact("contacte.txt",Contact.read,Contact.write)
valid=ValidareContact()
srv=ServiceContact(valid,repo)
ui=Console(srv)
teste=TesteContact()

teste.ruleaza()
ui.run()