package app.repository.file;

import app.domain.Client;
import app.domain.Hotel;
import app.domain.SpecialOffer;

import java.text.ParseException;
import java.util.List;

public class ClientFile extends AbstractFileRepository<Long, Client>{
    public ClientFile(String fileName) {
        super(fileName);
    }

    @Override
    public Client extractEntity(List<String> attributes) throws ParseException {
        Client client = new Client(Long.parseLong(attributes.get(0)),attributes.get(1), Integer.parseInt(attributes.get(2)), Integer.parseInt(attributes.get(3)), Client.hobby.valueOf(attributes.get(4)));
        return client;
    }

    @Override
    protected String createEntityAsString(Client entity) {
        return entity.getId() + ";" + entity.getName() + ";" + entity.getFidelityGrade() + ";" + entity.getVarsta() + ";" + entity.getHobby() ;
    }
}
