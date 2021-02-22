package app.controller;

import app.domain.Hotel;
import app.domain.Reservation;
import app.service.ReservationService;
import app.utils.events.Event;
import app.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class RezervareController implements Observer<Event>  {
    private ReservationService reservationService;

    Stage mainStage;

    Hotel hotel;
    Long clientId;

    @FXML
    DatePicker datePickerStart;
    @FXML
    DatePicker datePickerEnd;


    public void setReservationService(ReservationService reservationService, Hotel hotel, Long clientId){
        this.reservationService = reservationService;
        this.hotel = hotel;
        this.clientId = clientId;
        reservationService.addObserver(this);
    }

    public void setMainStage(Stage mainStage) {
        this.mainStage = mainStage;
    }

    @FXML
    public void initialize(){
    }

    public void initModel(){

    }

    @Override
    public void update(Event event) {
        initModel();
    }


    @FXML
    public void handleRezerva(ActionEvent event) {
        Reservation rezervare = new Reservation(reservationService.maxim()+1,clientId,hotel.getHotelId(),datePickerStart.getValue().atStartOfDay(),datePickerStart.getValue().getDayOfMonth()-datePickerEnd.getValue().getDayOfMonth());
        reservationService.addEntity(rezervare);
    }
}
