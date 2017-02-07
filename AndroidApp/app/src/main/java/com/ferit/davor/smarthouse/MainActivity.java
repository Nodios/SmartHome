package com.ferit.davor.smarthouse;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class MainActivity extends Activity {

    private ImageButton lightsBtn;
    private ImageButton doorBtn;
    private ImageButton windowBtn;
    private ImageButton ventilationBtn;
    private ImageButton statusBtn;
    private ImageButton quitBtn;

    String host;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        lightsBtn=(ImageButton)findViewById(R.id.btn_lights);
        doorBtn=(ImageButton)findViewById(R.id.btn_door);
        windowBtn=(ImageButton)findViewById(R.id.btn_window);
        ventilationBtn=(ImageButton)findViewById(R.id.btn_vent);
        statusBtn=(ImageButton)findViewById(R.id.btn_stats);
        quitBtn=(ImageButton)findViewById(R.id.btn_quit);

        Intent i = getIntent();
        host = i.getStringExtra("host");

        lightsBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), LightsActivity.class);
                intent.putExtra("host",host);
                startActivity(intent);
            }
        });

        doorBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), DoorActivity.class);
                intent.putExtra("host",host);
                startActivity(intent);
            }
        });

        windowBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), WindowActivity.class);
                intent.putExtra("host",host);
                startActivity(intent);
            }
        });

        ventilationBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), VentilationActivity.class);
                intent.putExtra("host",host);
                startActivity(intent);
            }
        });

        statusBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), StatusActivity.class);
                intent.putExtra("host",host);
                setContentView(R.layout.splash_layout);
                startActivity(intent);
            }
        });

        quitBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public  void onClick(View v){
                Intent intent = new Intent(getApplicationContext(), ClientConnections.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                intent.putExtra("Exit me", true);
                startActivity(intent);
                finish();
            }
        });

    }

    // This method creates the menu on the app
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }


    // Called when a options menu item is selected
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        // We check what menu item was clicked and show a Toast
        if (id == R.id.action_settings) {

            Intent intent = new Intent(getApplicationContext(), NewConnection.class);
            startActivity(intent);

            return true;

            // If exit was clicked close the app
        }
        else if(id==R.id.action_connections){
            Intent intent = new Intent(getApplicationContext(), ClientConnections.class);
            startActivity(intent);

            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if (resultCode == RESULT_CANCELED) {
            return;
        }

        Bundle dataBundle = data.getExtras();

        // perform connection create and connect
        connectAction(dataBundle);

    }

    private void connectAction(Bundle data) {
        MqttConnectOptions conOpt = new MqttConnectOptions();

        // The basic client information
        String server = (String) data.get(ActivityConstants.server);
        String clientId = (String) data.get(ActivityConstants.clientId);
        int port = Integer.parseInt((String) data.get(ActivityConstants.port));
        boolean cleanSession = (Boolean) data.get(ActivityConstants.cleanSession);

        boolean ssl = (Boolean) data.get(ActivityConstants.ssl);
        String ssl_key = (String) data.get(ActivityConstants.ssl_key);
        String uri = null;
        if (ssl) {
            Log.e("SSLConnection", "Doing an SSL Connect");
            uri = "ssl://";

        }
        else {
            uri = "tcp://";
        }

        uri = uri + server + ":" + port;

        MqttAndroidClient client;
        client = Connections.getInstance(this).createClient(this, uri, clientId);

        if (ssl){
            try {
                if(ssl_key != null && !ssl_key.equalsIgnoreCase(""))
                {
                    FileInputStream key = new FileInputStream(ssl_key);
                    conOpt.setSocketFactory(client.getSSLSocketFactory(key,
                            "mqtttest"));
                }

            } catch (MqttSecurityException e) {
                Log.e(this.getClass().getCanonicalName(),
                        "MqttException Occured: ", e);
            } catch (FileNotFoundException e) {
                Log.e(this.getClass().getCanonicalName(),
                        "MqttException Occured: SSL Key file not found", e);
            }
        }

        // create a client handle
        String clientHandle = uri + clientId;

        // last will message
        String message = (String) data.get(ActivityConstants.message);
        String topic = (String) data.get(ActivityConstants.topic);
        Integer qos = (Integer) data.get(ActivityConstants.qos);
        Boolean retained = (Boolean) data.get(ActivityConstants.retained);

        // connection options

        String username = (String) data.get(ActivityConstants.username);

        String password = (String) data.get(ActivityConstants.password);

        int timeout = (Integer) data.get(ActivityConstants.timeout);
        int keepalive = (Integer) data.get(ActivityConstants.keepalive);

        Connection connection = new Connection(clientHandle, clientId, server, port,
                this, client, ssl);

        // connect client

        String[] actionArgs = new String[1];
        actionArgs[0] = clientId;
        connection.changeConnectionStatus(Connection.ConnectionStatus.CONNECTING);

        conOpt.setCleanSession(cleanSession);
        conOpt.setConnectionTimeout(timeout);
        conOpt.setKeepAliveInterval(keepalive);
        if (!username.equals(ActivityConstants.empty)) {
            conOpt.setUserName(username);
        }
        if (!password.equals(ActivityConstants.empty)) {
            conOpt.setPassword(password.toCharArray());
        }

        final ActionListener callback = new ActionListener(this,
                ActionListener.Action.CONNECT, clientHandle, actionArgs);

        boolean doConnect = true;

        if ((!message.equals(ActivityConstants.empty))
                || (!topic.equals(ActivityConstants.empty))) {
            // need to make a message since last will is set
            try {
                conOpt.setWill(topic, message.getBytes(), qos.intValue(),
                        retained.booleanValue());
            }
            catch (Exception e) {
                Log.e(this.getClass().getCanonicalName(), "Exception Occured", e);
                doConnect = false;
                callback.onFailure(null, e);
            }
        }
        client.setCallback(new MqttCallbackHandler(this, clientHandle));


        //set traceCallback
        client.setTraceCallback(new MqttTraceCallback());

        connection.addConnectionOptions(conOpt);
        Connections.getInstance(this).addConnection(connection);
        if (doConnect) {
            try {
                client.connect(conOpt, null, callback);
            }
            catch (MqttException e) {
                Log.e(this.getClass().getCanonicalName(),
                        "MqttException Occured", e);
            }
        }

    }

}
