package app.service;

import app.domain.Entity;
import app.domain.Location;
import app.domain.Reservation;
import app.repository.Repository;
import app.utils.events.ChangeEventType;
import app.utils.events.LocationChangeEvent;
import app.utils.events.ReservationChangeEvent;

import java.util.Comparator;
import java.util.stream.StreamSupport;

public class ReservationService extends Service<Double, Reservation, ReservationChangeEvent>{
    public ReservationService(Repository<Double, Reservation> repo) {
        super(repo);
    }

    @Override
    protected ReservationChangeEvent createNewEvent(ChangeEventType type, Reservation reservation) {
        return new ReservationChangeEvent(type,reservation);
    }

    public Double maxim(){
        if(repo.size() == 0)
            return 0.0;
        return StreamSupport.stream(repo.findAll().spliterator(),false)
                .max(Comparator.comparing(Entity::getId)).get().getId();
    }
}
