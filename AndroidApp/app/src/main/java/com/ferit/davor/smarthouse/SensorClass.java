package com.ferit.davor.smarthouse;

public class SensorClass {
    public String sensorID;
    public String sensorType;
    public String tableAttribute;
    public String measureUnit;

    SensorClass(String ID, String type, String attr, String measure){
        this.sensorID=ID;
        this.sensorType=type;
        this.tableAttribute=attr;
        this.measureUnit=measure;
    }
}
