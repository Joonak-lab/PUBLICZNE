/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.mycompany.mavenproject4;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.util.converter.IntegerStringConverter;

/**
 * FXML Controller class
 *
 * @author Paweł Jończyk
 */
public class PrimaryController implements Initializable {

    @FXML
    private Button dodaj;
    @FXML
    private Button usun;
    @FXML
    private TableView tabela;
    @FXML
    private TableColumn marka;
    @FXML
    private TableColumn model;
    @FXML
    private TableColumn km;
    @FXML
    private TableColumn kolor;
    @FXML
    private TableColumn cena;
    @FXML
    private Label label;
    @FXML
    private TextField name_T;
    @FXML
    private TextField model_T;
    @FXML
    private TextField HP_T;
    @FXML
    private TextField color_T;
    @FXML
    private TextField Prize_T;
     @FXML
    private Label warning;
    
    private final ObservableList <Vehicle> data;  
    private final Vehicles list;
   
    
    
    /**
     * Initializes the controller class.
     * @param list the list of motorcycle
     */
    public PrimaryController(Vehicles list) {
        this.list = list;
        data = FXCollections.observableArrayList(list.getmodels());
        data.addListener(new ListChangeListener<Vehicle>(){
            @Override
            public void onChanged(ListChangeListener.Change<? extends Vehicle> change) {
                while (change.next()) {
                    if (!change.wasPermutated()) {
                     
                        for (var remitem : change.getRemoved()) {
                            list.getmodels().remove(remitem);
                        }
                        for (var additem : change.getAddedSubList()) {
                            list.getmodels().add(additem);
                        }
                    }
                }
            }
        });
    }
    
    /**
     * initializing the table
     * @param url
     * @param rb
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        tabela.setItems(data);
        marka.setCellValueFactory(new PropertyValueFactory<Vehicle, String>("name"));
        model.setCellValueFactory(new PropertyValueFactory<Vehicle, String>("model"));
        km.setCellValueFactory(new PropertyValueFactory<Vehicle, Integer>("Horse_Power"));
        kolor.setCellValueFactory(new PropertyValueFactory<Vehicle, String>("color"));
        cena.setCellValueFactory(new PropertyValueFactory<Vehicle, Integer>("prize"));
        
        tabela.setEditable(true);
        marka.setCellFactory(TextFieldTableCell.forTableColumn());	
        model.setCellFactory(TextFieldTableCell.forTableColumn());
        km.setCellFactory(TextFieldTableCell.forTableColumn(new IntegerStringConverter(){
            @Override
            public Integer fromString(String value)
                {
                    try{
                        return super.fromString(value);
                    }
                    catch(NumberFormatException e)
                {
                    return null;
                }
                }
        }));
        kolor.setCellFactory(TextFieldTableCell.forTableColumn());
        cena.setCellFactory(TextFieldTableCell.forTableColumn(new IntegerStringConverter(){
        @Override
            public Integer fromString(String value)
                {
                    try{
                        return super.fromString(value);
                    }
                    catch(NumberFormatException e)
                {
                    return null;
                }
                }
        }));
        marka.setOnEditCommit(new EventHandler<TableColumn.CellEditEvent<Vehicle, String>>() {
            @Override
            public void handle(TableColumn.CellEditEvent<Vehicle, String> t) {
                warning.setText("");
                if(t.getNewValue()!=null)
                {
                ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setName(t.getOldValue());
                warning.setText("Wprowadzono błędną wartość");
                }
                else
                {
                   ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setName(t.getNewValue()); 
                }
                
            }
        });
       model.setOnEditCommit(new EventHandler<TableColumn.CellEditEvent<Vehicle, String>>() {
            @Override
            public void handle(TableColumn.CellEditEvent<Vehicle, String> t) {
                warning.setText("");
                if(t.getNewValue()!=null)
               {
                ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setModel(t.getOldValue());
                 warning.setText("Wprowadzono błędną wartość");
               }
                else
                {
                   ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setModel(t.getNewValue()); 
                }
            }
        });
        km.setOnEditCommit(new EventHandler<TableColumn.CellEditEvent<Vehicle,Integer>>()  {
            @Override
            public void handle(TableColumn.CellEditEvent<Vehicle, Integer> t) {
                warning.setText("");
                if(t.getNewValue()==null || t.getNewValue()<1)
                {
                    ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setHorse_Power(t.getOldValue());
                    warning.setText("Wprowadzono błędną wartość");
                }
                else
                {
                 ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setHorse_Power(t.getNewValue());
                }
            }
        });
        cena.setOnEditCommit(new EventHandler<TableColumn.CellEditEvent<Vehicle,Integer>>() {
            @Override
            public void handle(TableColumn.CellEditEvent<Vehicle, Integer> t) {
                warning.setText("");
                if(t.getNewValue()==null || t.getNewValue()<1)
                {
                    ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setPrize(t.getOldValue());
                    warning.setText("Wprowadzono błędną wartość");
                }
                else
                {
                 ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setPrize(t.getNewValue());
                }
            }
        });
        kolor.setOnEditCommit(new EventHandler<TableColumn.CellEditEvent<Vehicle, String>>() {
            @Override
            public void handle(TableColumn.CellEditEvent<Vehicle, String> t) {
                warning.setText("");
                if(t.getNewValue()!=null || (t.getNewValue().matches("\\d+(\\d+)?")))
                {
                ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setColor(t.getOldValue());
                 warning.setText("Wprowadzono błędną wartość");
                }
                else
                {
                   ((Vehicle) t.getTableView().getItems().get(t.getTablePosition().getRow())).setColor(t.getNewValue()); 
                }
            }
        });
        
    }    
  
    @FXML
    private void remove(ActionEvent evenr) {
        warning.setText("");
        int index = tabela.getSelectionModel().getSelectedIndex();
        if(index != -1) data.remove(index);
    }
    
    @FXML
    private void add(ActionEvent evenr) {
        warning.setText("");
        try{
            if(name_T.getText().isBlank()||model_T.getText().isBlank()||color_T.getText().isBlank())
            {
                warning.setText("Wpisz wszystkie informacje");
            }
            else if(color_T.getText().matches("\\d+(\\d+)?"))
            {
                warning.setText("Kolor nie może zawierać liczb");
            }
            else
            {
                data.add(new Vehicle(name_T.getText(),model_T.getText(),Integer.parseInt(HP_T.getText()),Integer.parseInt(Prize_T.getText()),color_T.getText()));
                name_T.clear();
                model_T.clear();
                HP_T.clear();
                Prize_T.clear();
                color_T.clear();
            }
         
        }
        catch(NumberFormatException e)
        {
            warning.setText("Popraw wpisane dane!");
        }  
    }
}
