package com.ferit.davor.smarthouse;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.concurrent.ExecutionException;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import android.app.Activity;

import com.jjoe64.graphview.DefaultLabelFormatter;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

public class StatusActivity extends Activity {

    private TextView datetime, temperature, humidity, monoxide, gas;
    private String clientHandle;
    private MqttAndroidClient client;
    private GraphView graph;
    private JSONObject obj;

    private SensorClass gasSensor,co2Sensor,tempSensor,humidSensor;

    static int i=0;

    boolean firstRun=true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        setContentView(R.layout.activity_status);

        gasSensor=new SensorClass("Gas","gas","gas1", " ppm");
        co2Sensor=new SensorClass("Monoxide","gas","co", " ppm");
        tempSensor=new SensorClass("Temperature","temperature","measuredTemperature", " °C");
        humidSensor=new SensorClass("Humidity","temperature","humidity", " %RH");

        Intent i = getIntent();
        clientHandle = i.getStringExtra("host");

        client = new MqttAndroidClient(this, "tcp://" + clientHandle, "status");
        try {
            client.connect();
        } catch (MqttException e) {
            e.printStackTrace();
        }

        datetime = (TextView) findViewById(R.id.datetimeText);
        temperature = (TextView) findViewById(R.id.temperatureText);
        humidity=(TextView) findViewById(R.id.humidityText);
        monoxide=(TextView) findViewById(R.id.coText);
        gas=(TextView) findViewById(R.id.gasText);

        GetStatus("values");

        graph = (GraphView) findViewById(R.id.graph);

        Spinner spinner = (Spinner) findViewById(R.id.dropdown);
        // Create an ArrayAdapter using the string array and a default spinner layout
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.status_array, android.R.layout.simple_spinner_item);
        // Specify the layout to use when the list of choices appears
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // Apply the adapter to the spinner
        spinner.setAdapter(adapter);



        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
                // An item was selected. You can retrieve the selected item using
                // parent.getItemAtPosition(pos)
                switch(pos){
                    case 0:
                        RefreshGraph(tempSensor);
                        break;
                    case 1:
                        RefreshGraph(humidSensor);
                        break;
                    case 2:
                        RefreshGraph(co2Sensor);
                        break;
                    case 3:
                        RefreshGraph(gasSensor);
                        break;
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
                // your code here
            }

        });

    }

    // This method creates the menu on the app
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_status, menu);
        return true;
    }

    // Called when a options menu item is selected
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.

        for(int i=1;i<5;i++){
            MqttMessage message = new MqttMessage();
            message.setPayload(("s"+String.valueOf(i)).getBytes());
            try {
                client.publish("android/control", message);
            } catch (MqttException e) {
                e.printStackTrace();
            }
        }

        Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            public void run() {
                GetStatus("values");
            }
        }, 1000);


        return super.onOptionsItemSelected(item);
    }

    private void GetStatus(String sensor) {

        // call AsynTask to perform network operation on separate thread
        try {
            String str_result= new HttpAsyncTask().execute("http://smart-home-tkr.azurewebsites.net/api/" + sensor).get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }

    }

    public static String GET(String url) {
        InputStream inputStream = null;
        String result = "";
        try {

            // create HttpClient
            HttpClient httpclient = new DefaultHttpClient();

            // make GET request to the given URL
            HttpResponse httpResponse = httpclient.execute(new HttpGet(url));

            // receive response as inputStream
            inputStream = httpResponse.getEntity().getContent();

            // convert inputstream to string
            if (inputStream != null)
                result = convertInputStreamToString(inputStream);
            else
                result = "Did not work!";

        } catch (Exception e) {
            Log.d("InputStream", e.getLocalizedMessage());
        }

        return result;
    }

    private static String convertInputStreamToString(InputStream inputStream) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
        String line = "";
        String result = "";
        while ((line = bufferedReader.readLine()) != null)
            result += line;

        inputStream.close();
        return result;

    }

    public boolean isConnected() {
        ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Activity.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
        if (networkInfo != null && networkInfo.isConnected())
            return true;
        else
            return false;
    }

    private class HttpAsyncTask extends AsyncTask<String, Void, String> {
        @Override
        protected String doInBackground(String... urls) {

            return GET(urls[0]);
        }

        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
            //Toast.makeText(getBaseContext(), "Received!", Toast.LENGTH_LONG).show();
            try {
                obj = new JSONObject(result);
                JSONArray array = obj.getJSONArray("temperature");
                JSONObject outputObj = array.getJSONObject(0);
                String output = outputObj.getString("measuredAt");
                output = output.replace('T', ' ');
                output = output.substring(0, output.indexOf(':') + 3);
                datetime.setText(" "+output);

                String outputString[]=getData("temperature");
                temperature.setText(outputString[0]+" °C");
                humidity.setText(outputString[1]+" %RH");
                outputString=getData("gas");

                monoxide.setText(outputString[2]+" ppm");
                gas.setText(outputString[0]+" ppm");

            } catch (JSONException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    private String[] getData(String value){
        JSONArray array = null;
        String output[]=new String[4];
        try {
            array = obj.getJSONArray(value);
            JSONObject outputObj = array.getJSONObject(0);
            switch (value){
                case "temperature":
                    output[0]=outputObj.getString("measuredTemperature");
                    output[1]=outputObj.getString("humidity");
                    break;
                case "gas":
                    output[0]=outputObj.getString("gas1");
                    output[1]=outputObj.getString("co2");
                    output[2]=outputObj.getString("co");
                    break;
            }
            return output;
        } catch (JSONException e) {
            e.printStackTrace();
        }
            return null;
    }

    private void RefreshGraph(SensorClass sensor){
        i=0;
        String temp;
        JSONArray array;
        String yLabel="";
        try {
            array = obj.getJSONArray(sensor.sensorType);
            int data[] = new int[5];
            final int hours[] = new int[12];
            final int minutes[] = new int[12];
            int j;
            if(firstRun==true)
                j=10;
            else
                j=4;
            for (int i = 0; i < 5; i++) {
                JSONObject dataObj = array.getJSONObject(i);
                data[i] = dataObj.getInt(sensor.tableAttribute);
                temp = dataObj.getString("measuredAt");
                temp = temp.substring(temp.indexOf('T') + 1, temp.indexOf(':'));
                hours[j] = Integer.parseInt(temp);
                temp = dataObj.getString("measuredAt");
                temp = temp.substring(temp.indexOf(':') + 1, temp.indexOf(':')+3);
                minutes[j--]=Integer.parseInt(temp);
                yLabel=sensor.measureUnit;
            }
            firstRun=false;
            try{
                graph.removeAllSeries();
            }
            catch (Exception e){

            }

            //Graph
            LineGraphSeries<DataPoint> series = new LineGraphSeries<>(new DataPoint[]{
                    new DataPoint(0, data[4]),
                    new DataPoint(1, data[3]),
                    new DataPoint(2, data[2]),
                    new DataPoint(3, data[1]),
                    new DataPoint(4, data[0])
            });
            graph.addSeries(series);
            final String finalYLabel = yLabel;
            graph.getGridLabelRenderer().setLabelFormatter(new DefaultLabelFormatter() {
                @Override
                public String formatLabel(double value, boolean isValueX) {
                    if (isValueX) {
                            return super.formatLabel(hours[i], isValueX)+ ":"+String.valueOf(minutes[i++]);
                    } else {
                        return super.formatLabel(value, isValueX) + finalYLabel;
                    }
                }
            });
        } catch (JSONException e) {
            e.printStackTrace();
        }

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

    @Override
    public void onBackPressed() {
        Intent backPressedIntent = new Intent();
        backPressedIntent .setClass(getApplicationContext(), MainActivity.class);
        startActivity(backPressedIntent );
        finish();
    }
}