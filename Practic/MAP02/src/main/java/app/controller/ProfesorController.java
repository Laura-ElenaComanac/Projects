package app.controller;

import app.domain.Raspuns;
import app.domain.Intrebare;
import app.domain.Rezultat;
import app.service.IntrebareService;
import app.service.RezultatService;
import app.utils.events.Event;
import app.utils.events.RaspunsChangeEvent;
import app.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ProfesorController implements Observer<Event>  {
    private IntrebareService intrebareService;
    private RezultatService rezultatService;

    ObservableList<Intrebare> modelIntrebari = FXCollections.observableArrayList();
    ObservableList<Intrebare> modelTest = FXCollections.observableArrayList();
    ObservableList<Raspuns> modelRaspunsuri = FXCollections.observableArrayList();

    Stage mainStage;

    @FXML
    TableView<Intrebare> tableViewIntrebari;
    @FXML
    TableView<Intrebare> tableViewTest;
    @FXML
    TableView<Raspuns> tableViewRaspunsuri;

    @FXML
    TableColumn<Intrebare, Integer> tableColumnNrIntrebare;
    @FXML
    TableColumn<Intrebare, String> tableColumnDescriere;


    @FXML
    TableColumn<Intrebare, Integer> tableColumnNrIntrebareTest;
    @FXML
    TableColumn<Intrebare, String> tableColumnDescriereTest;

    @FXML
    TableColumn<Raspuns, Integer> tableColumnNrIntrebareRaspuns;
    @FXML
    TableColumn<Raspuns, String> tableColumnNumeStudentRaspuns;
    @FXML
    TableColumn<Raspuns, Double> tableColumnPunctajRaspuns;


    public void setRezultatService(RezultatService rezultatService) {
        this.rezultatService = rezultatService;
        rezultatService.addObserver(this);
    }

    public void setIntrebareService(IntrebareService intrebareService){
        this.intrebareService = intrebareService;
        intrebareService.addObserver(this);
    }

    public void setMainStage(Stage mainStage) {
        this.mainStage = mainStage;
    }

    @FXML
    public void initialize(){
        tableColumnNrIntrebare.setCellValueFactory(new PropertyValueFactory<Intrebare,Integer>("nrIntrebare"));
        tableColumnDescriere.setCellValueFactory(new PropertyValueFactory<Intrebare,String>("descriere"));

        tableColumnNrIntrebareTest.setCellValueFactory(new PropertyValueFactory<Intrebare, Integer>("nrIntrebare"));
        tableColumnDescriereTest.setCellValueFactory(new PropertyValueFactory<Intrebare, String>("descriere"));


        tableColumnNrIntrebareRaspuns.setCellValueFactory(new PropertyValueFactory<Raspuns, Integer>("nrIntrebare"));
        tableColumnNumeStudentRaspuns.setCellValueFactory(new PropertyValueFactory<Raspuns, String>("numeStudent"));
        tableColumnPunctajRaspuns.setCellValueFactory(new PropertyValueFactory<Raspuns, Double>("punctaj"));

        tableViewTest.setItems(modelTest);
        tableViewRaspunsuri.setItems(modelRaspunsuri);
    }


    public void initModel() {
        Iterable<Intrebare> intrebari = intrebareService.getAllEntities();
        List<Intrebare> intrebariList = StreamSupport.stream(intrebari.spliterator(), false)
                .filter(i -> !modelTest.contains(i))
                .collect(Collectors.toList());

        modelIntrebari.setAll(intrebariList);
        tableViewIntrebari.setItems(modelIntrebari);
    }


    @Override
    public void update(Event event) {
        if(event instanceof RaspunsChangeEvent)
            modelRaspunsuri.add(((RaspunsChangeEvent) event).getData());
        initModel();
    }


    @FXML
    public void handlePlaseazaIntrebarea(ActionEvent event){
        Intrebare selected = tableViewIntrebari.getSelectionModel().getSelectedItem();

        modelTest.add(selected);

        intrebareService.plaseazaIntrebare(selected);
    }

    @FXML
    public void handleTrimiteRezultatele(ActionEvent event){
        List<Raspuns> raspunsuri = tableViewRaspunsuri.getItems();

        List<Rezultat> rezultate = rezultatService.calculeazaNote(raspunsuri);

        for(Rezultat rezultat : rezultate)
            rezultatService.addEntity(rezultat);
    }

}
