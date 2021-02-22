package app.domain;

import java.time.LocalDateTime;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;

public class Reservation extends Entity<Double>{
    Long clientId;
    Double hotelId;
    LocalDateTime startDate;
    Integer noNights;

    static AtomicInteger identity = new AtomicInteger(0);

    public Reservation(Double reservationId, Long clientId, Double hotelId, LocalDateTime startDate, Integer noNights) {
        this.clientId = clientId;
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.noNights = noNights;

        this.setId(reservationId);
    }


    public Long getClientId() {
        return clientId;
    }

    public void setClientId(Long clientId) {
        this.clientId = clientId;
    }

    public Double getHotelId() {
        return hotelId;
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDateTime startDate) {
        this.startDate = startDate;
    }

    public Integer getNoNights() {
        return noNights;
    }

    public void setNoNights(Integer noNights) {
        this.noNights = noNights;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Reservation that = (Reservation) o;
        return this.getId().equals(that.getId()) && clientId.equals(that.clientId) && hotelId.equals(that.hotelId) && startDate.equals(that.startDate) && noNights.equals(that.noNights);
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId(), clientId, hotelId, startDate, noNights);
    }
}
