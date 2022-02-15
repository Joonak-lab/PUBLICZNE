/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.mavenproject4;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author Paweł Jończyk
 */
public class Vehicles {
     private List<Vehicle> models;
    
    /**
     *  Constructor of class
     */
    public Vehicles()
    {
       models =  new ArrayList<Vehicle>();   
        try {
      File Data = new File("plik.txt");
      Scanner Reader = new Scanner(Data);     
      Reader.nextLine();
      //Read information from the file until the end 
      while (Reader.hasNextLine()) {
         Vehicle motorcycle = new Vehicle(Reader.next(),Reader.next(),Reader.nextInt(),Reader.nextInt(),Reader.next()); 
          //adds motorcycle to the catalog
       models.add(motorcycle);      
      }
      //Closes the file
      Reader.close();
  

      // the given file wasn't found
    } catch (FileNotFoundException ex) {
      }
      // if the file was corrupted 
      catch(Exception e)
      {
      }
      
           
    }
   
/**
 * getter
 * @return the list of motorcycles 
 */
    public List<Vehicle> getmodels() {
        return models;
    }
 
 
}
