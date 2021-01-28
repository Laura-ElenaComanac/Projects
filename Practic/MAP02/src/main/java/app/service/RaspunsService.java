package app.service;

import app.domain.Raspuns;
import app.repository.Repository;
import app.utils.events.ChangeEventType;
import app.utils.events.RaspunsChangeEvent;

public class RaspunsService extends Service<Integer, Raspuns, RaspunsChangeEvent> {

    public RaspunsService(Repository<Integer, Raspuns> repo) {
        super(repo);
    }

    @Override
    protected RaspunsChangeEvent createNewEvent(ChangeEventType type, Raspuns raspuns) {
        return new RaspunsChangeEvent(type, raspuns);
    }
}
