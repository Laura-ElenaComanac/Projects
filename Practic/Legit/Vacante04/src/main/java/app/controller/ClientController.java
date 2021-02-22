package app.controller;

import app.domain.Hotel;
import app.domain.Location;
import app.domain.SpecialOffer;
import app.service.*;
import app.utils.events.Event;
import app.utils.events.ReservationChangeEvent;
import app.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientController implements Observer<Event>  {
    ClientService clientService;
    HotelService hotelService;
    LocationService locationService;
    ReservationService reservationService;
    SpecialOfferService specialOfferService;

    ObservableList<Hotel> modelHotel= FXCollections.observableArrayList();
    ObservableList<SpecialOfferEntry> modelSpecialOffer = FXCollections.observableArrayList();

    Stage mainStage;

    Long clientId;

    public void setClientId(Long clientId){
        this.clientId = clientId;
    }

    @FXML
    ComboBox<Location> comboLocatie;
    @FXML
    Label labelHobby;

    @FXML
    TableView<Hotel> tableViewHoteluri;
    @FXML
    TableView<SpecialOfferEntry> tableViewOferteSpeciale;

    @FXML
    TableColumn<Hotel, String> tableColumnNumeHotel;
    @FXML
    TableColumn<Hotel, Integer> tableColumnNrCamereHotel;
    @FXML
    TableColumn<Hotel, Double> tableColumnPretHotel;
    @FXML
    TableColumn<Hotel, Hotel.type> tableColumnTipHotel;

    @FXML
    TableColumn<SpecialOfferEntry, String> tableColumnNumeHotelOferta;
    @FXML
    TableColumn<SpecialOfferEntry, String> tableColumnNumeLocatieOferta;
    @FXML
    TableColumn<SpecialOfferEntry, Date> tableColumnStartDateOferta;
    @FXML
    TableColumn<SpecialOfferEntry, Date> tableColumnEndDateOferta;


    public void setClientService(ClientService clientService){
        this.clientService = clientService;
        clientService.addObserver(this);
    }

    public void setHotelService(HotelService hotelService){
        this.hotelService = hotelService;
        hotelService.addObserver(this);
    }

    public void setLocationServicee(LocationService locationService){
        this.locationService = locationService;
        locationService.addObserver(this);
    }

    public void setReservationService(ReservationService reservationService){
        this.reservationService = reservationService;
        reservationService.addObserver(this);
    }

    public void setSpecialOfferService(SpecialOfferService specialOfferService){
        this.specialOfferService = specialOfferService;
        specialOfferService.addObserver(this);
    }

    public void setMainStage(Stage mainStage) {
        this.mainStage = mainStage;
    }

    @FXML
    public void initialize(){
        tableColumnNumeHotel.setCellValueFactory(new PropertyValueFactory<>("hotelName"));
        tableColumnNrCamereHotel.setCellValueFactory(new PropertyValueFactory<>("noRooms"));
        tableColumnPretHotel.setCellValueFactory(new PropertyValueFactory<>("pricePerNight"));
        tableColumnTipHotel.setCellValueFactory(new PropertyValueFactory<>("type"));

        tableColumnNumeHotelOferta.setCellValueFactory(new PropertyValueFactory<>("numeHotel"));
        tableColumnNumeLocatieOferta.setCellValueFactory(new PropertyValueFactory<>("numeLocatie"));
        tableColumnStartDateOferta.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        tableColumnEndDateOferta.setCellValueFactory(new PropertyValueFactory<>("endDate"));
    }

    public void initModel() {
        comboLocatie.getItems().setAll(locationService.getAllEntities());
        Location location = comboLocatie.getSelectionModel().getSelectedItem();

        if(location!=null) {
            Iterable<Hotel> hoteluri = hotelService.getAllEntities();
            List<Hotel> hoteluriList = StreamSupport.stream(hoteluri.spliterator(), false)
                    .filter(h -> h.getLocationId().equals(location.getLocationId()))
                    .collect(Collectors.toList());

            modelHotel.setAll(hoteluriList);
            tableViewHoteluri.setItems(modelHotel);
        }

        SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy");
        Date date = new Date(System.currentTimeMillis());

        Iterable<SpecialOffer> specialOfferEntries = specialOfferService.getAllEntities();
        List<SpecialOfferEntry> specialOfferEntriesList = StreamSupport.stream(specialOfferEntries.spliterator(),false)
                .filter(s -> date.compareTo(s.getStartDate())>0 && date.compareTo(s.getEndDate())<0)
                .filter(s -> clientService.findOne(clientId).getFidelityGrade()>s.getPercents())
                .map(s -> new SpecialOfferEntry(hotelService.findOne(s.getHotelId()).getHotelName(),locationService.findOne(hotelService.findOne(s.getHotelId()).getLocationId()).getLocationName(),s.getStartDate(),s.getEndDate()))
                .collect(Collectors.toList());

        modelSpecialOffer.setAll(specialOfferEntriesList);
        tableViewOferteSpeciale.setItems(modelSpecialOffer);
    }


    @Override
    public void update(Event event) {
        if(event instanceof ReservationChangeEvent)
        {
            if(clientService.findOne(((ReservationChangeEvent) event).getData().getClientId()).getHobby().equals(clientService.findOne(clientId).getHobby())
            && !((ReservationChangeEvent) event).getData().getClientId().equals(clientId))
            {
                Double hotelid = ((ReservationChangeEvent) event).getData().getHotelId();
                Long clientId = ((ReservationChangeEvent) event).getData().getClientId();
                labelHobby.setText("Inca un client la hotelul " + hotelService.findOne(hotelid).getHotelName() + " are hobby " + clientService.findOne(clientId).getHobby());
            }
        }
        initModel();
    }



    @FXML
    public void handleLocatie(ActionEvent event) {
        initModel();
    }

    @FXML
    public void handleClickHotel(MouseEvent mouseEvent) throws IOException {
        Hotel selected = tableViewHoteluri.getSelectionModel().getSelectedItem();

        showRezervareDialog(selected);
    }

    public void showRezervareDialog(Hotel hotel) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/views/ReservareView.fxml"));
        GridPane root = (GridPane) loader.load();

        Stage dialogStage = new Stage();
        dialogStage.setTitle("Rezervare");
        dialogStage.initModality(Modality.WINDOW_MODAL);
        Scene scene = new Scene(root);
        dialogStage.setScene(scene);

        RezervareController rezervareController = loader.getController();
        rezervareController.setReservationService(reservationService,hotel,clientId);

        dialogStage.show();
    }


    public static class SpecialOfferEntry{
        private String numeHotel;
        private String numeLocatie;
        private Date startDate;
        private Date endDate;

        public SpecialOfferEntry(String numeHotel, String numeLocatie, Date startDate, Date endDate) {
            this.numeHotel = numeHotel;
            this.numeLocatie = numeLocatie;
            this.startDate = startDate;
            this.endDate = endDate;
        }

        public String getNumeHotel() {
            return numeHotel;
        }

        public void setNumeHotel(String numeHotel) {
            this.numeHotel = numeHotel;
        }

        public String getNumeLocatie() {
            return numeLocatie;
        }

        public void setNumeLocatie(String numeLocatie) {
            this.numeLocatie = numeLocatie;
        }

        public Date getStartDate() {
            return startDate;
        }

        public void setStartDate(Date startDate) {
            this.startDate = startDate;
        }

        public Date getEndDate() {
            return endDate;
        }

        public void setEndDate(Date endDate) {
            this.endDate = endDate;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            SpecialOfferEntry that = (SpecialOfferEntry) o;
            return numeHotel.equals(that.numeHotel) && numeLocatie.equals(that.numeLocatie) && startDate.equals(that.startDate) && endDate.equals(that.endDate);
        }

        @Override
        public int hashCode() {
            return Objects.hash(numeHotel, numeLocatie, startDate, endDate);
        }
    }
}
