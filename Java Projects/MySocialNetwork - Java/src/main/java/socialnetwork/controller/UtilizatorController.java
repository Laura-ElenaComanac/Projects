package socialnetwork.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TableView;
import javafx.scene.control.TableColumn;

import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import socialnetwork.domain.Prietenie;
import socialnetwork.domain.Utilizator;
import socialnetwork.service.PrietenieService;
import socialnetwork.service.UtilizatorService;

import javafx.event.ActionEvent;
import socialnetwork.utils.events.UtilizatorChangeEvent;
import socialnetwork.utils.observer.Observer;

import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UtilizatorController implements Observer<UtilizatorChangeEvent> {
    private UtilizatorService serviceUtilizator;
    private PrietenieService servicePrietenie;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();

    @FXML
    TableView<Utilizator> tableView;

    @FXML
    TextField textFieldNume;
    @FXML
    TextField textFieldPrenume;
    @FXML
    TableColumn<Utilizator, String> tableColumnNume;
    @FXML
    TableColumn<Utilizator, String> tableColumnPrenume;

    public void setUtilizatorService(UtilizatorService utilizatorService){
        serviceUtilizator = utilizatorService;
        //Utilizator utilizator = new Utilizator(textFieldNume.getText(), textFieldPrenume.getText());

        serviceUtilizator.addObserver(this);
        //initModel(utilizator);
    }

    public void setPrietenieService(PrietenieService prietenieService){
        servicePrietenie = prietenieService;
        //Utilizator utilizator = new Utilizator(textFieldNume.getText(), textFieldPrenume.getText());

        servicePrietenie.addObserver(this);
        //initModel(utilizator);
    }

    @FXML
    public void initialize(){
        tableColumnNume.setCellValueFactory(new PropertyValueFactory<Utilizator,String>("firstName"));
        tableColumnPrenume.setCellValueFactory(new PropertyValueFactory<Utilizator,String>("lastName"));
        tableView.setItems(model);
    }

    public void initModel(Utilizator utilizator){
        Iterable<Utilizator> prieteni = utilizator.getFriends();
        List<Utilizator> prieteniList = StreamSupport.stream(prieteni.spliterator(), false).collect(Collectors.toList());

        model.setAll(prieteniList);
        //model.clear();
        //model.addAll(prieteniList);
    }

    @Override
    public void update(UtilizatorChangeEvent utilizatorChangeEvent) {
        initModel(utilizatorChangeEvent.getData());
    }

    @FXML
    public void handleLoadFriends(ActionEvent actionEvent) {
        try {
            initModel(serviceUtilizator.getUserByName(textFieldNume.getText(),textFieldPrenume.getText()));
        }
        catch (NoSuchElementException e){
            model.clear();
            MessageAlert.showErrorMessage(null, "Nu exista utilizatorul in retea!");
        }
    }

    @FXML
    public void handleDeleteUtilizator(ActionEvent actionEvent){
        Utilizator selected = (Utilizator) tableView.getSelectionModel().getSelectedItem();
        Utilizator utilizator1 = serviceUtilizator.getUserByName(selected.getFirstName(),selected.getLastName());
        Utilizator utilizator2 = serviceUtilizator.getUserByName(textFieldNume.getText(),textFieldPrenume.getText());

        if(selected!=null){
            Prietenie prietenie = servicePrietenie.getFriendshipByUsers(utilizator1,utilizator2);
            Prietenie deleted = servicePrietenie.deletePrietenie(utilizator1,utilizator2,prietenie.getDate()).get();
            if(deleted!=null){
                MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Stergere", "Prieten sters cu suces!");
                initModel(utilizator2);
            }
        }
        else{
            MessageAlert.showErrorMessage(null, "Nu s-a selectat niciun prieten!");
        }
    }

    @FXML
    public void handleAddMessage(ActionEvent actionEvent) {
        showUtilizatorEditDialog(null);
    }

    public void showUtilizatorEditDialog(Utilizator utilizator){
        try{
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/views/editUtilizatorView.fxml"));
            AnchorPane root = (AnchorPane) loader.load();
            // stage
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Adauga un nou prieten");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            EditUtilizatorController e = loader.getController();
            //e.setSe



        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
