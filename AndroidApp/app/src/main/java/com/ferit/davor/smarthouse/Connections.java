package com.ferit.davor.smarthouse;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.content.Context;

import org.eclipse.paho.android.service.MqttAndroidClient;

/**
 * Connections is a singleton class which stores all the connection objects
 * in one central place so they can be passed between activities using a client
 * handle
 */
public class Connections {

  private static Connections instance = null;

  private HashMap<String, Connection> connections = null;

  private Persistence persistence = null;

  private Connections(Context context)
  {
    connections = new HashMap<String, Connection>();

    //attempt to restore state
    persistence = new Persistence(context);
    try {
      List<Connection> l = persistence.restoreConnections(context);
      for (Connection c : l) {
        connections.put(c.handle(), c);
      }
    }
    catch (PersistenceException e) {
      e.printStackTrace();
    }

  }

  public synchronized static Connections getInstance(Context context)
  {
    if (instance == null) {
      instance = new Connections(context);
    }

    return instance;
  }

  public Connection getConnection(String handle)
  {

    return connections.get(handle);
  }

  public void addConnection(Connection connection)
  {
    connections.put(connection.handle(), connection);
    try {
      persistence.persistConnection(connection);
    }
    catch (PersistenceException e)
    {
      //error persisting well lets just swallow this
      e.printStackTrace();
    }
  }

  /**
   * Create a fully initialised MqttAndroidClient for the parameters given

   */
  public MqttAndroidClient createClient(Context context, String serverURI, String clientId)
  {
    MqttAndroidClient client = new MqttAndroidClient(context, serverURI, clientId);
    return client;
  }


  public Map<String, Connection> getConnections()
  {
    return connections;
  }

  public void removeConnection(Connection connection) {
    connections.remove(connection.handle());
    persistence.deleteConnection(connection);
  }

}
