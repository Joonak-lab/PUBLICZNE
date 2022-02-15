/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.mavenproject4;

/**
 *
 * @author Paweł Jończyk
 */
public class Vehicle {
      ///name of motorcycle
   private String name; 
   ///model of motorcycle
   private String model; 
   ///number of horse power
   private int Horse_Power;
   ///number of prize
   private int prize;
   ///color of motorcycle
   private String color; 
   

    /**
     * Constructor of Vehicle class
     * @param name manufacture of motorcycle
     * @param model model of motorcycle
     * @param Horse_Power amount of horse power
     * @param prize prize of a motorcycle
     * @param color color of a motorcycle
     */

   public Vehicle(String name, String model, int Horse_Power, int prize, String color)
   {
       this.name = name;
       this.color = color;
       this.model = model;
       this.prize = prize;
       this.Horse_Power = Horse_Power;
   }
     /**
      * getter
      * @return horse power
      */
    public int getHorse_Power() {
        return Horse_Power;
    }
/**
      * getter
      * @return color
      */
    public String getColor() {
        return color;
    }
/**
      * getter
      * @return model
      */
    public String getModel() {
        return model;
    }
/**
      * getter
      * @return name
      */
    public String getName() {
        return name;
    }
/**
      * getter
      * @return prize
      */
    public int getPrize() {
        return prize;
    }
/**
 * setter of name
 * @param name - name of motorcycle 
 */
    public void setName(String name) {
            this.name = name;  
    }
/**
 * setter of model
 * @param model - model of motorcycle 
 */
    public void setModel(String model) {
            this.model = model;
    }
/**
 * setter of horse power
 * @param Horse_Power - amount of horse power
 */
    public void setHorse_Power(int Horse_Power) {
        this.Horse_Power = Horse_Power;
    }
/**
 * setter of prize
 * @param prize - prize of motorcycle
 */
    public void setPrize(int prize) {
        
        this.prize = prize;
    }
/**
 * setter of color
 * @param color - color of motorcycle
 */
    public void setColor(String color) {
     
             this.color = color;
      
    }
    
   
}
