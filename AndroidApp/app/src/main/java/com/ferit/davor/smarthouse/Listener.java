package com.ferit.davor.smarthouse;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.logging.LogManager;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;

import android.widget.EditText;
import android.widget.RadioGroup;

import com.ferit.davor.smarthouse.ActionListener.Action;
import com.ferit.davor.smarthouse.Connection.ConnectionStatus;
import org.eclipse.paho.android.service.MqttAndroidClient;


public class Listener implements OnMenuItemClickListener {


  private String clientHandle = null;

  private ConnectionDetails connectionDetails = null;
  private LightsActivity lightsActivity=null;
  private ClientConnections clientConnections = null;
  private Context context = null;
  static boolean logging = false;


  public Listener(ConnectionDetails connectionDetails, String clientHandle)
  {
    this.connectionDetails = connectionDetails;
    this.clientHandle = clientHandle;
    context = connectionDetails;

  }

  public Listener(LightsActivity lightsActivity, String clientHandle)
  {
    this.lightsActivity = lightsActivity;
    this.clientHandle = clientHandle;
    context = connectionDetails;

  }

  public Listener(ClientConnections clientConnections) {
    this.clientConnections = clientConnections;
    context = clientConnections;
  }

  @Override
  public boolean onMenuItemClick(MenuItem item) {

    int id = item.getItemId();

    switch (id)
    {
      case R.id.newConnection :
        createAndConnect();
        break;
      case R.id.disconnect :
        disconnect();
        break;
      case R.id.connectMenuOption :
        reconnect();
        break;
      case R.id.startLogging :
        enablePahoLogging();
        break;
      case R.id.endLogging :
        disablePahoLogging();
        break;
    }

    return false;
  }

  private void reconnect() {

    Connections.getInstance(context).getConnection(clientHandle).changeConnectionStatus(ConnectionStatus.CONNECTING);

    Connection c = Connections.getInstance(context).getConnection(clientHandle);
    try {
      c.getClient().connect(c.getConnectionOptions(), null, new ActionListener(context, Action.CONNECT, clientHandle, null));
    }
    catch (MqttSecurityException e) {
      Log.e(this.getClass().getCanonicalName(), "Failed to reconnect the client with the handle " + clientHandle, e);
      c.addAction("Client failed to connect");
    }
    catch (MqttException e) {
      Log.e(this.getClass().getCanonicalName(), "Failed to reconnect the client with the handle " + clientHandle, e);
      c.addAction("Client failed to connect");
    }

  }

  private void disconnect() {

    Connection c = Connections.getInstance(context).getConnection(clientHandle);

    //if the client is not connected, process the disconnect
    if (!c.isConnected()) {
      return;
    }

    try {
      c.getClient().disconnect(null, new ActionListener(context, Action.DISCONNECT, clientHandle, null));
      c.changeConnectionStatus(ConnectionStatus.DISCONNECTING);
    }
    catch (MqttException e) {
      Log.e(this.getClass().getCanonicalName(), "Failed to disconnect the client with the handle " + clientHandle, e);
      c.addAction("Client failed to disconnect");
    }

  }

  private void subscribe()
  {
    String topic = ((EditText) connectionDetails.findViewById(R.id.topic)).getText().toString();
    ((EditText) connectionDetails.findViewById(R.id.topic)).getText().clear();

    RadioGroup radio = (RadioGroup) connectionDetails.findViewById(R.id.qosSubRadio);
    int checked = radio.getCheckedRadioButtonId();
    int qos = ActivityConstants.defaultQos;

    switch (checked) {
      case R.id.qos0 :
        qos = 0;
        break;
      case R.id.qos1 :
        qos = 1;
        break;
      case R.id.qos2 :
        qos = 2;
        break;
    }

    try {
      String[] topics = new String[1];
      topics[0] = topic;
      Connections.getInstance(context).getConnection(clientHandle).getClient()
          .subscribe(topic, qos, null, new ActionListener(context, Action.SUBSCRIBE, clientHandle, topics));
    }
    catch (MqttSecurityException e) {
      Log.e(this.getClass().getCanonicalName(), "Failed to subscribe to" + topic + " the client with the handle " + clientHandle, e);
    }
    catch (MqttException e) {
      Log.e(this.getClass().getCanonicalName(), "Failed to subscribe to" + topic + " the client with the handle " + clientHandle, e);
    }
  }

  public void publish()
  {
    String topic = ((EditText) connectionDetails.findViewById(R.id.lastWillTopic))
            .getText().toString();

    ((EditText) connectionDetails.findViewById(R.id.lastWillTopic)).getText().clear();

    String message = ((EditText) connectionDetails.findViewById(R.id.lastWill)).getText()
            .toString();

    ((EditText) connectionDetails.findViewById(R.id.lastWill)).getText().clear();

    RadioGroup radio = (RadioGroup) connectionDetails.findViewById(R.id.qosRadio);
    int checked = radio.getCheckedRadioButtonId();
    int qos = ActivityConstants.defaultQos;

    switch (checked) {
      case R.id.qos0 :
        qos = 0;
        break;
      case R.id.qos1 :
        qos = 1;
        break;
      case R.id.qos2 :
        qos = 2;
        break;
    }

    boolean retained = false;

    String[] args = new String[2];
    args[0] = message;
    args[1] = topic+";qos:"+qos+";retained:"+retained;

    try {
      Connections.getInstance(context).getConnection(clientHandle).getClient()
          .publish(topic, message.getBytes(), qos, retained, null, new ActionListener(context, Action.PUBLISH, clientHandle, args));
    }
    catch (MqttSecurityException e) {
      Log.e(this.getClass().getCanonicalName(), "Failed to publish a messged from the client with the handle " + clientHandle, e);
    }
    catch (MqttException e) {
      Log.e(this.getClass().getCanonicalName(), "Failed to publish a messged from the client with the handle " + clientHandle, e);
    }

  }

  private void createAndConnect()
  {
    Intent createConnection;

    //start a new activity to gather information for a new connection
    createConnection = new Intent();
    createConnection.setClassName(
        clientConnections.getApplicationContext(),
        "com.ferit.davor.smarthouse.NewConnection");

    clientConnections.startActivityForResult(createConnection,
        ActivityConstants.connect);
  }

  private void enablePahoLogging() {

    try {
      InputStream logPropStream = context.getResources().openRawResource(R.raw.jsr47android);
      LogManager.getLogManager().readConfiguration(logPropStream);
      logging = true;
         
      HashMap<String, Connection> connections = (HashMap<String,Connection>)Connections.getInstance(context).getConnections();
      if(!connections.isEmpty()){
    	  Entry<String, Connection> entry = connections.entrySet().iterator().next();
    	  Connection connection = (Connection)entry.getValue();
    	  connection.getClient().setTraceEnabled(true);
    	  //change menu state.
    	  clientConnections.invalidateOptionsMenu();
    	  //Connections.getInstance(context).getConnection(clientHandle).getClient().setTraceEnabled(true);
      }else{
    	  Log.i("SampleListener","No connection to enable log in service");
      }
    }
    catch (IOException e) {
      Log.e("MqttAndroidClient",
          "Error reading logging parameters", e);
    }

  }

  private void disablePahoLogging() {
    LogManager.getLogManager().reset();
    logging = false;
    
    HashMap<String, Connection> connections = (HashMap<String,Connection>)Connections.getInstance(context).getConnections();
    if(!connections.isEmpty()){
  	  Entry<String, Connection> entry = connections.entrySet().iterator().next();
  	  Connection connection = (Connection)entry.getValue();
  	  connection.getClient().setTraceEnabled(false);
  	  //change menu state.
  	  clientConnections.invalidateOptionsMenu();
    }else{
  	  Log.i("SampleListener","No connection to disable log in service");
    }
    clientConnections.invalidateOptionsMenu();
  }

}
