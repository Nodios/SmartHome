package com.ferit.davor.smarthouse;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;


public class LightsActivity extends Activity{

    String clientHandle;
    static MqttAndroidClient client;
    Connection connection;

    private ImageButton light1;
    private ImageButton light2;
    private ImageButton light3;
    private ImageButton light4;
    private ImageButton light5;

    boolean bLight1=false;
    boolean bLight2=false;
    boolean bLight3=false;
    boolean bLight4=false;
    boolean bLight5=false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lights);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        Intent i = getIntent();
        clientHandle = i.getStringExtra("host");

        client = new MqttAndroidClient(this,"tcp://"+clientHandle, "lights");
        try {
            client.connect();
        } catch (MqttException e) {
            e.printStackTrace();
        }

        light1 = (ImageButton) findViewById(R.id.light1);
        light2 = (ImageButton) findViewById(R.id.light2);
        light3 = (ImageButton) findViewById(R.id.light3);
        light4 = (ImageButton) findViewById(R.id.light4);
        light5 = (ImageButton) findViewById(R.id.light5);

        light1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bLight1=!bLight1;
                MqttMessage message = new MqttMessage();
                message.setPayload(("001").getBytes());
                try {
                    client.publish("android/control", message);
                } catch (MqttException e) {
                    e.printStackTrace();
                }

            }
        });

        light2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bLight2=!bLight2;
                MqttMessage message = new MqttMessage();
                message.setPayload(("010").getBytes());
                try {
                    client.publish("android/control", message);
                } catch (MqttException e) {
                    e.printStackTrace();
                }

            }
        });

        light3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bLight3=!bLight3;
                MqttMessage message = new MqttMessage();
                message.setPayload(("011").getBytes());
                try {
                    client.publish("android/control", message);
                } catch (MqttException e) {
                    e.printStackTrace();
                }

            }
        });

        light4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bLight4=!bLight4;
                MqttMessage message = new MqttMessage();
                message.setPayload(("100").getBytes());
                try {
                    client.publish("android/control", message);
                } catch (MqttException e) {
                    e.printStackTrace();
                }

            }
        });

        light5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bLight5=!bLight5;
                MqttMessage message = new MqttMessage();
                message.setPayload(("101").getBytes());
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
