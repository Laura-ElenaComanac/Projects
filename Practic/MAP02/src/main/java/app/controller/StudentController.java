package app.controller;

import app.domain.Raspuns;
import app.domain.Intrebare;
import app.domain.Rezultat;
import app.service.RaspunsService;
import app.service.IntrebareService;
import app.service.RezultatService;
import app.utils.events.*;
import app.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class StudentController implements Observer<Event>  {
    private RaspunsService raspunsService;
    private RezultatService rezultatService;

    ObservableList<Intrebare> modelIntrebari = FXCollections.observableArrayList();
    ObservableList<Rezultat> modelRezultate = FXCollections.observableArrayList();

    Stage mainStage;

    @FXML
    RadioButton v1;
    @FXML
    RadioButton v2;
    @FXML
    RadioButton v3;

    @FXML
    TableView<Intrebare> tableViewIntrebari;
    @FXML
    TableView<Rezultat> tableViewRezultate;

    @FXML
    TableColumn<Intrebare, Integer> tableColumnNrIntrebare;
    @FXML
    TableColumn<Intrebare, String> tableColumnDescriereIntrebare;

    @FXML
    TableColumn<Rezultat, String> tableColumnNumeRezultat;
    @FXML
    TableColumn<Rezultat, Double> tableColumnNotaRezultat;


    public void setRaspunsService(RaspunsService raspunsService) {
        this.raspunsService = raspunsService;
        raspunsService.addObserver(this);
    }

    public void setRezultatService(RezultatService rezultatService){
        this.rezultatService = rezultatService;
        rezultatService.addObserver(this);
    }


    public void setMainStage(Stage mainStage) {
        this.mainStage = mainStage;
    }

    @FXML
    public void initialize(){
        tableColumnNrIntrebare.setCellValueFactory(new PropertyValueFactory<Intrebare,Integer>("nrIntrebare"));
        tableColumnDescriereIntrebare.setCellValueFactory(new PropertyValueFactory<Intrebare,String>("descriere"));

        tableColumnNumeRezultat.setCellValueFactory(new PropertyValueFactory<Rezultat, String>("numeStudent"));
        tableColumnNotaRezultat.setCellValueFactory(new PropertyValueFactory<Rezultat, Double>("nota"));

        tableViewIntrebari.setItems(modelIntrebari);
    }

    public void initModel(Event event){
        Iterable<Rezultat> rezultate = rezultatService.getAllEntities();
        List<Rezultat> rezultateList = StreamSupport.stream(rezultate.spliterator(), false).collect(Collectors.toList());

        modelRezultate.setAll(rezultateList);
        tableViewRezultate.setItems(modelRezultate);
    }

    @Override
    public void update(Event event) {
        if(event instanceof IntrebareChangeEvent)
            modelIntrebari.add(((IntrebareChangeEvent) event).getData());
        initModel(event);
    }


    @FXML
    public void handleTrimiteRaspuns(ActionEvent event){
        Intrebare selected = tableViewIntrebari.getSelectionModel().getSelectedItem();
        Double punctaj = 0.0;

        if(this.v1.isSelected() && this.v1.getText().equals(selected.getRaspunsCorect()))
            punctaj = selected.getPunctaj();
        if(this.v2.isSelected() && this.v2.getText().equals(selected.getRaspunsCorect()))
            punctaj = selected.getPunctaj();
        if(this.v3.isSelected() && this.v3.getText().equals(selected.getRaspunsCorect()))
            punctaj = selected.getPunctaj();

        Raspuns raspuns = new Raspuns(selected.getNrIntrebare(),mainStage.getTitle(), punctaj);

        raspunsService.addEntity(raspuns);
        modelIntrebari.remove(selected);
    }

    @FXML
    public void handlev1(ActionEvent event) {
        this.v2.setSelected(false);
        this.v3.setSelected(false);
    }

    @FXML
    public void handlev2(ActionEvent event) {
        this.v1.setSelected(false);
        this.v3.setSelected(false);
    }

    @FXML
    public void handlev3(ActionEvent event) {
        this.v1.setSelected(false);
        this.v2.setSelected(false);
    }

    public void handleSelected(MouseEvent mouseEvent) {
        Intrebare selected = tableViewIntrebari.getSelectionModel().getSelectedItem();

        this.v1.setText(selected.getV1());
        this.v2.setText(selected.getV2());
        this.v3.setText(selected.getV3());
    }
}
