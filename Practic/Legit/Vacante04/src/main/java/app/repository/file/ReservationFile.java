package app.repository.file;

import app.domain.Hotel;
import app.domain.Reservation;

import java.text.ParseException;
import java.time.LocalDateTime;
import java.util.List;

public class ReservationFile extends AbstractFileRepository<Double, Reservation> {
    public ReservationFile(String fileName) {
        super(fileName);
    }

    @Override
    public Reservation extractEntity(List<String> attributes) throws ParseException {
        Reservation reservation = new Reservation(Double.parseDouble(attributes.get(0)), Long.parseLong(attributes.get(1)), Double.parseDouble(attributes.get(2)), LocalDateTime.parse(attributes.get(3)),Integer.parseInt(attributes.get(4)));
        return reservation;
    }

    @Override
    protected String createEntityAsString(Reservation entity) {
        return entity.getId() + ";" + entity.getClientId() + ";" + entity.getHotelId() + ";" + entity.getStartDate() + ";" + entity.getNoNights();
    }
}
