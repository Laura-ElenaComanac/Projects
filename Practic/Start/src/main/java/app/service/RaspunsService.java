package app.service;

import app.domain.Raspuns;
import app.repository.file.RaspunsFile;
import app.utils.events.ChangeEventType;
import app.utils.events.RaspunsChangeEvent;

public class RaspunsService extends Service<Integer, Raspuns, RaspunsChangeEvent> {

    public RaspunsService(RaspunsFile repo) {
        super(repo);
    }

    public void appendNumber(Integer nr){
        ((RaspunsFile)repo).appendNumber(nr);
    }

    @Override
    protected RaspunsChangeEvent createNewEvent(ChangeEventType type, Raspuns raspuns) {
        return new RaspunsChangeEvent(type,raspuns);
    }
}
