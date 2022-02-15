package com.mycompany.mavenproject4;

import java.io.File;
import java.io.FileWriter;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

/**
 * JavaFX App
 * @author Paweł Jończyk
 */
public class App extends Application {

    private static Scene scene;
    
    private static Vehicles vehicles;

    /**
     *
     * @param stage
     * @throws IOException
     */
    @Override
    public void start(Stage stage) throws IOException {
        scene = new Scene(loadFXML("primary"), 640, 480);
        stage.setScene(scene);
        stage.show();
    }

    static void setRoot(String fxml) throws IOException {
        scene.setRoot(loadFXML(fxml));
    }

    private static Parent loadFXML(String fxml) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(fxml + ".fxml"));
         fxmlLoader.setControllerFactory( p -> { return new PrimaryController(vehicles);} );
        return fxmlLoader.load();
    }

    /**
     * main function 
     * @param args
     */
    public static void main(String[] args) {
        vehicles = new Vehicles();
        launch();
        //save data to file
        SaveData(vehicles.getmodels());
    }
    
 /**
     * save the data to file
     * @param vehicles - list of motorcycles' catalog
     */
    static void SaveData(List <Vehicle> vehicles){
        try {
            File Data = new File("plik.txt");
            //checks if file doesn't exist create new file
            if(Data.exists()==false)
            {
                Data.createNewFile();
            }
           
      FileWriter SaveD = new FileWriter("plik.txt");
      //checks if list of motorcycles isn't empty
      if(vehicles.isEmpty()==false)
      {
          //writes information to the file
          for (int i = 0 ; i < vehicles.size() ; i++) {
              Vehicle l = vehicles.get(i);
              SaveD.write("\n" + l.getName() + "\n" + l.getModel() + "\n"
              + l.getHorse_Power() + "\n" + l.getPrize() + "\n" + l.getColor());
          }     
      }
      // closes the file
      SaveD.close();
      // the problem with file was caught
    } catch (IOException ex) {
    }
    }
}