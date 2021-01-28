package app.ui;

import app.config.ApplicationContext;
import app.controller.StudentController;
import app.controller.ProfesorController;
import app.repository.file.RaspunsFile;
import app.repository.file.RezultatFile;
import app.service.RaspunsService;
import app.service.RezultatService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import app.repository.file.IntrebareFile;
import app.service.IntrebareService;

import java.io.IOException;

public class MainApp extends Application {
    IntrebareFile intrebareRepo;
    IntrebareService intrebareService;
    RaspunsFile raspunsRepo;
    RaspunsService raspunsService;
    RezultatFile rezultatRepo;
    RezultatService rezultatService;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        String fileNameIntrebari = ApplicationContext.getPROPERTIES().getProperty("data.app.quizes");
        intrebareRepo = new IntrebareFile(fileNameIntrebari);
        intrebareService = new IntrebareService(intrebareRepo);

        String fileNammeRaspuns = ApplicationContext.getPROPERTIES().getProperty("data.app.raspunsuri");
        raspunsRepo = new RaspunsFile(fileNammeRaspuns);
        raspunsService = new RaspunsService(raspunsRepo);

        String fileNammeRezultat = ApplicationContext.getPROPERTIES().getProperty("data.app.rezultate");
        rezultatRepo = new RezultatFile(fileNammeRezultat);
        rezultatService = new RezultatService(rezultatRepo);

        initView(primaryStage);

        primaryStage.setTitle("Profesor");
        primaryStage.show();
    }

    private void initView(Stage profesorStage) throws IOException {
        FXMLLoader profesorLoader = new FXMLLoader();
        profesorLoader.setLocation(getClass().getResource("/views/ProfesorView.fxml"));
        GridPane profesorLayout = profesorLoader.load();
        profesorStage.setScene(new Scene(profesorLayout));

        ProfesorController profesorController = profesorLoader.getController();
        profesorController.setMainStage(profesorStage);
        profesorController.setIntrebareService(intrebareService);
        profesorController.setRezultatService(rezultatService);
        profesorController.initModel();

        raspunsService.addObserver(profesorController);

        getParameters().getRaw().forEach(this::createStudent);
    }

    private void createStudent(String nume)
    {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/views/StudentView.fxml"));

            GridPane root =  loader.load();

            // stage
            Stage studentStage = new Stage();
            studentStage.setTitle(nume);
            studentStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            studentStage.setScene(scene);

            StudentController studentController = loader.getController();
            studentController.setRezultatService(rezultatService);
            studentController.setRaspunsService(raspunsService);

            intrebareService.addObserver(studentController);
            rezultatService.addObserver(studentController);

            studentController.setMainStage(studentStage);
            studentStage.show();
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
