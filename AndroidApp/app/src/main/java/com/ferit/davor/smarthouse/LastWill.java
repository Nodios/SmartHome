package com.ferit.davor.smarthouse;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioGroup;

/**
 * Activity for setting the last will message for the client
 *
 */
public class LastWill extends Activity {

  private LastWill last = this;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

    setContentView(R.layout.activity_publish);

  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    getMenuInflater().inflate(R.menu.activity_last_will, menu);

    menu.findItem(R.id.publish).setOnMenuItemClickListener(new OnMenuItemClickListener() {

      @Override
      public boolean onMenuItemClick(MenuItem item) {

        Intent result = new Intent();

        String message = ((EditText) findViewById(R.id.lastWill)).getText().toString();
        String topic = ((EditText) findViewById(R.id.lastWillTopic)).getText().toString();

        RadioGroup radio = (RadioGroup) findViewById(R.id.qosRadio);
        int checked = radio.getCheckedRadioButtonId();
        int qos = ActivityConstants.defaultQos;

        //determine which qos value has been selected
        switch (checked)
        {
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

        boolean retained = ((CheckBox) findViewById(R.id.retained)).isChecked();

        //package the data collected into the intent
        result.putExtra(ActivityConstants.message, message);
        result.putExtra(ActivityConstants.topic, topic);
        result.putExtra(ActivityConstants.qos, qos);
        result.putExtra(ActivityConstants.retained, retained);

        //set the result and finish activity
        last.setResult(RESULT_OK, result);
        last.finish();

        return false;
      }

    });
    return true;
  }

}
