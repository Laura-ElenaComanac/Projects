package app.domain;

import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;

public class Hotel extends Entity<Double>{
    Double hotelId;
    Double locationId;
    String hotelName;
    Integer noRooms;
    Double pricePerNight;
    public enum type{family, teenagers, oldpeople};
    type type;

    static AtomicInteger identity = new AtomicInteger(0);

    public Hotel(Double hotelId, Double locationId, String hotelName, Integer noRooms, Double pricePerNight, type type) {
        this.hotelId = hotelId;
        this.locationId = locationId;
        this.hotelName = hotelName;
        this.noRooms = noRooms;
        this.pricePerNight = pricePerNight;
        this.type = type;

        this.setId(identity.incrementAndGet()+0.0);
    }

    public Double getHotelId() {
        return hotelId;
    }

    public Double getLocationId() {
        return locationId;
    }

    public String getHotelName() {
        return hotelName;
    }

    public Integer getNoRooms() {
        return noRooms;
    }

    public Double getPricePerNight() {
        return pricePerNight;
    }

    public Hotel.type getType() {
        return type;
    }

    public void setType(Hotel.type type) {
        this.type = type;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Hotel hotel = (Hotel) o;
        return hotelId.equals(hotel.hotelId) && locationId.equals(hotel.locationId) && hotelName.equals(hotel.hotelName) && noRooms.equals(hotel.noRooms) && pricePerNight.equals(hotel.pricePerNight);
    }

    @Override
    public int hashCode() {
        return Objects.hash(hotelId, locationId, hotelName, noRooms, pricePerNight);
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public void setLocationId(Double locationId) {
        this.locationId = locationId;
    }

    public void setHotelName(String hotelName) {
        this.hotelName = hotelName;
    }

    public void setNoRooms(Integer noRooms) {
        this.noRooms = noRooms;
    }

    public void setPricePerNight(Double pricePerNight) {
        this.pricePerNight = pricePerNight;
    }

    public static void setIdentity(AtomicInteger identity) {
        Hotel.identity = identity;
    }
}
