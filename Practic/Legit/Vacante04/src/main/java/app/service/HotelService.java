package app.service;

import app.domain.Hotel;
import app.domain.Location;
import app.repository.Repository;
import app.utils.events.ChangeEventType;
import app.utils.events.HotelChangeEvent;
import app.utils.events.LocationChangeEvent;

public class HotelService  extends Service<Double, Hotel, HotelChangeEvent>{
    public HotelService(Repository<Double, Hotel> repo) {
        super(repo);
    }

    @Override
    protected HotelChangeEvent createNewEvent(ChangeEventType type, Hotel hotel) {
        return new HotelChangeEvent(type,hotel);
    }
}
