package com.ferit.davor.smarthouse;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import android.content.Context;
import android.text.Html;
import android.text.Spanned;
import org.eclipse.paho.android.service.MqttAndroidClient;


public class Connection {

  /*
   * Basic Information about the client
   */
  private String clientHandle = null;
  private String clientId = null;
  private String host = null;
  private int port = 0;
  private ConnectionStatus status = ConnectionStatus.NONE;
  private ArrayList<String> history = null;
  private MqttAndroidClient client = null;

  private ArrayList<PropertyChangeListener> listeners = new ArrayList<PropertyChangeListener>();

  private Context context = null;

  private MqttConnectOptions conOpt;

  private boolean sslConnection = false;

  private long persistenceId = -1;

  /**
   * Connections status for  a connection
   */
  enum ConnectionStatus {

    /** Client is Connecting **/
    CONNECTING,
    /** Client is Connected **/
    CONNECTED,
    /** Client is Disconnecting **/
    DISCONNECTING,
    /** Client is Disconnected **/
    DISCONNECTED,
    /** Client has encountered an Error **/
    ERROR,
    /** Status is unknown **/
    NONE
  }

  /**
   * Creates a connection from persisted information in the database store, attempting
   * to create a MqttAndroidClient and the client handle.
   */
  public static Connection createConnection(String clientId, String host,
      int port, Context context, boolean sslConnection) {
    String handle = null;
    String uri = null;
    if (sslConnection) {
      uri = "ssl://" + host + ":" + port;
      handle = uri + clientId;
    }
    else {
      uri = "tcp://" + host + ":" + port;
      handle = uri + clientId;
    }
    MqttAndroidClient client = new MqttAndroidClient(context, uri, clientId);
    return new Connection(handle, clientId, host, port, context, client, sslConnection);

  }

  /**
   * Creates a connection object with the server information and the client
   * hand which is the reference used to pass the client around activities
   */
  public Connection(String clientHandle, String clientId, String host,
      int port, Context context, MqttAndroidClient client, boolean sslConnection) {
    //generate the client handle from its hash code
    this.clientHandle = clientHandle;
    this.clientId = clientId;
    this.host = host;
    this.port = port;
    this.context = context;
    this.client = client;
    this.sslConnection = sslConnection;
    history = new ArrayList<String>();
    StringBuffer sb = new StringBuffer();
    sb.append("Client: ");
    sb.append(clientId);
    sb.append(" created");
    addAction(sb.toString());
  }

  /**
   * Add an action to the history of the client
   */
  public void addAction(String action) {

    Object[] args = new String[1];
    SimpleDateFormat sdf = new SimpleDateFormat(context.getString(R.string.dateFormat));
    args[0] = sdf.format(new Date());

    String timestamp = context.getString(R.string.timestamp, args);
    history.add(action + timestamp);

    notifyListeners(new PropertyChangeEvent(this, ActivityConstants.historyProperty, null, null));
  }

  /**
   * Generate an array of Spanned items representing the history of this
   * connection.
   */
  public Spanned[] history() {

    int i = 0;
    Spanned[] array = new Spanned[history.size()];

    for (String s : history) {
      if (s != null) {
        array[i] = Html.fromHtml(s);
        i++;
      }
    }

    return array;

  }

  /**
   * Gets the client handle for this connection
   */
  public String handle() {
    return clientHandle;
  }

  /**
   * Determines if the client is connected
   */
  public boolean isConnected() {
    return status == ConnectionStatus.CONNECTED;
  }

  /**
   * Changes the connection status of the client
   */
  public void changeConnectionStatus(ConnectionStatus connectionStatus) {
    status = connectionStatus;
    notifyListeners((new PropertyChangeEvent(this, ActivityConstants.ConnectionStatusProperty, null, null)));
  }

  /**
   * A string representing the state of the client this connection
   * object represents
   */
  @Override
  public String toString() {
    StringBuffer sb = new StringBuffer();
    sb.append(clientId);
    sb.append("\n ");

    switch (status) {

      case CONNECTED :
        sb.append(context.getString(R.string.connectedto));
        break;
      case DISCONNECTED :
        sb.append(context.getString(R.string.disconnected));
        break;
      case NONE :
        sb.append(context.getString(R.string.no_status));
        break;
      case CONNECTING :
        sb.append(context.getString(R.string.connecting));
        break;
      case DISCONNECTING :
        sb.append(context.getString(R.string.disconnecting));
        break;
      case ERROR :
        sb.append(context.getString(R.string.connectionError));
    }
    sb.append(" ");
    sb.append(host);

    return sb.toString();
  }

  /**
   * Determines if a given handle refers to this client
   */
  public boolean isHandle(String handle) {
    return clientHandle.equals(handle);
  }

  /**
   * Compares two connection objects for equality
   * this only takes account of the client handle
   */
  @Override
  public boolean equals(Object o) {
    if (!(o instanceof Connection)) {
      return false;
    }

    Connection c = (Connection) o;

    return clientHandle.equals(c.clientHandle);

  }

  /**
   * Get the client Id for the client this object represents
   */
  public String getId() {
    return clientId;
  }

  /**
   * Get the host name of the server that this connection object is associated with
   */
  public String getHostName() {

    return host;
  }

  /**
   * Determines if the client is in a state of connecting or connected.
   */
  public boolean isConnectedOrConnecting() {
    return (status == ConnectionStatus.CONNECTED) || (status == ConnectionStatus.CONNECTING);
  }

  /**
   * Client is currently not in an error state
   */
  public boolean noError() {
    return status != ConnectionStatus.ERROR;
  }

  /**
   * Gets the client which communicates with the android service.
   */
  public MqttAndroidClient getClient() {
    return client;
  }

  /**
   * Add the connectOptions used to connect the client to the server
   */
  public void addConnectionOptions(MqttConnectOptions connectOptions) {
    conOpt = connectOptions;

  }

  /**
   * Get the connectOptions used to connect this client to the server
   */
  public MqttConnectOptions getConnectionOptions()
  {
    return conOpt;
  }

  public void registerChangeListener(PropertyChangeListener listener)
  {
    listeners.add(listener);
  }

  public void removeChangeListener(PropertyChangeListener listener)
  {
    if (listener != null) {
      listeners.remove(listener);
    }
  }

  /**
   * Notify objects that the object has been updated
   */
  private void notifyListeners(PropertyChangeEvent propertyChangeEvent)
  {
    for (PropertyChangeListener listener : listeners)
    {
      listener.propertyChange(propertyChangeEvent);
    }
  }

  /**
   * Gets the port that this connection connects to.
   */
  public int getPort() {
    return port;
  }

  /**
   * Determines if the connection is secured using SSL, returning a C style integer value
   */
  public int isSSL() {
    return sslConnection ? 1 : 0;
  }

  /**
   * Assign a persistence ID to this object
   */
  public void assignPersistenceId(long id) {
    persistenceId = id;
  }

  /**
   * Returns the persistence ID assigned to this object
   */
  public long persistenceId() {
    return persistenceId;
  }
}
