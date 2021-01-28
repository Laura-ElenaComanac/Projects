package app.repository.file;

import app.domain.Raspuns;


import java.util.List;

public class RaspunsFile extends AbstractFileRepository<Integer, Raspuns> {
    public RaspunsFile(String fileName){
        super(fileName);
    }

    @Override
    public Raspuns extractEntity(List<String> attributes) {
        Raspuns raspuns = new Raspuns(Integer.parseInt(attributes.get(0)), attributes.get(1), Double.parseDouble(attributes.get(2)));
        raspuns.setId(Integer.parseInt(attributes.get(0)));
        return raspuns;
    }

    @Override
    protected String createEntityAsString(Raspuns entity) {
        return entity.getNrIntrebare() + ";" + entity.getNumeStudent() + ";" + entity.getPunctaj();
    }
}
