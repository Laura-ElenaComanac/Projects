package app.service;

import app.domain.Intrebare;
import app.repository.Repository;
import app.utils.events.ChangeEventType;
import app.utils.events.IntrebareChangeEvent;


public class IntrebareService extends Service<Integer, Intrebare, IntrebareChangeEvent> {

    public IntrebareService(Repository<Integer, Intrebare> repo) {
        super(repo);
    }

    @Override
    protected IntrebareChangeEvent createNewEvent(ChangeEventType type, Intrebare intrebare) {
        return new IntrebareChangeEvent(type, intrebare);
    }

    public void plaseazaIntrebare(Intrebare intrebare){
        this.notifyObservers(createNewEvent(ChangeEventType.ADD,intrebare));
    }
}
