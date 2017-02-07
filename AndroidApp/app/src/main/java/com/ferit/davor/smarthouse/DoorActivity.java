package com.ferit.davor.smarthouse;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.widget.SeekBar;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class DoorActivity extends Activity {

    private SeekBar barDoor;
    private String clientHandle;
    private MqttAndroidClient client;
    private int doorAngle;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_door);

        barDoor=(SeekBar)findViewById((R.id.doorBar));

        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        Intent i = getIntent();
        clientHandle = i.getStringExtra("host");

        client = new MqttAndroidClient(this,"tcp://"+clientHandle, "door");
        try {
            client.connect();
        } catch (MqttException e) {
            e.printStackTrace();
        }

        barDoor.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener(){

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,
                                          boolean fromUser) {
                // TODO Auto-generated method stub
                doorAngle=progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
                MqttMessage message = new MqttMessage();
                message.setPayload(("d"+String.valueOf(doorAngle)).getBytes());
                try {
                    client.publish("android/control", message);
                } catch (MqttException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    @Override
    protected void onStop(){
        super.onStop();
        try {
            client.disconnect();
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }
}

