package com.ferit.davor.smarthouse;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.ArrayList;
import android.app.ActionBar;
import android.app.FragmentTransaction;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.Menu;

/**
 * The connection details activity operates the fragments that make up the
 * connection details screen.
 */
public class ConnectionDetails extends FragmentActivity implements
    ActionBar.TabListener {

  SectionsPagerAdapter sectionsPagerAdapter;

  ViewPager viewPager;

  /** The currently selected tab **/
  private int selected = 0;


  private String clientHandle = null;

  private final ConnectionDetails connectionDetails = this;

  private Connection connection = null;

  private ChangeListener changeListener = null;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

    clientHandle = getIntent().getStringExtra("handle");

    setContentView(R.layout.activity_connection_details);
    // Create the adapter that will return a fragment for each of the pages
    sectionsPagerAdapter = new SectionsPagerAdapter(
        getSupportFragmentManager());

    // Set up the action bar for tab navigation
    final ActionBar actionBar = getActionBar();
    actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

    // add the sectionsPagerAdapter
    viewPager = (ViewPager) findViewById(R.id.pager);
    viewPager.setAdapter(sectionsPagerAdapter);

    viewPager
        .setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {

          @Override
          public void onPageSelected(int position) {
            // select the tab that represents the current page
            actionBar.setSelectedNavigationItem(position);

          }
        });

    // Create the tabs for the screen
    for (int i = 0; i < sectionsPagerAdapter.getCount(); i++) {
      ActionBar.Tab tab = actionBar.newTab();
      tab.setText(sectionsPagerAdapter.getPageTitle(i));
      tab.setTabListener(this);
      actionBar.addTab(tab);
    }

    connection = Connections.getInstance(this).getConnection(clientHandle);
    changeListener = new ChangeListener();
    connection.registerChangeListener(changeListener);
  }

  @Override
  protected void onDestroy() {
    connection.removeChangeListener(null);
    super.onDestroy();
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    int menuID;
    Integer button = null;
    boolean connected = Connections.getInstance(this)
        .getConnection(clientHandle).isConnected();

    // Select the correct action bar menu to display based on the
    // connectionStatus and which tab is selected
    if (connected) {

      switch (selected) {
        case 0 : // history view
          menuID = R.menu.activity_connection_details;
          break;
        case 1 : // subscribe view
          menuID = R.menu.activity_subscribe;
          button = R.id.subscribe;
          break;
        case 2 : // publish view
          menuID = R.menu.activity_publish;
          button = R.id.publish;
          break;
        default :
          menuID = R.menu.activity_connection_details;
          break;
      }
    }
    else {
      switch (selected) {
        case 0 : // history view
          menuID = R.menu.activity_connection_details_disconnected;
          break;
        case 1 : // subscribe view
          menuID = R.menu.activity_subscribe_disconnected;
          button = R.id.subscribe;
          break;
        case 2 : // publish view
          menuID = R.menu.activity_publish_disconnected;
          button = R.id.publish;
          break;
        default :
          menuID = R.menu.activity_connection_details_disconnected;
          break;
      }
    }
    // inflate the menu selected
    getMenuInflater().inflate(menuID, menu);
    Listener listener = new Listener(this, clientHandle);
    // add listeners
    if (button != null) {
      // add listeners
      menu.findItem(button).setOnMenuItemClickListener(listener);
      if (!Connections.getInstance(this).getConnection(clientHandle)
          .isConnected()) {
        menu.findItem(button).setEnabled(false);
      }
    }
    // add the listener to the disconnect or connect menu option
    if (connected) {
      menu.findItem(R.id.disconnect).setOnMenuItemClickListener(listener);
    }
    else {
      menu.findItem(R.id.connectMenuOption).setOnMenuItemClickListener(
          listener);
    }

    return true;
  }

  @Override
  public void onTabUnselected(ActionBar.Tab tab,
      FragmentTransaction fragmentTransaction) {
    // Don't need to do anything when a tab is unselected
  }

  @Override
  public void onTabSelected(ActionBar.Tab tab,
      FragmentTransaction fragmentTransaction) {
    // When the given tab is selected, switch to the corresponding page in
    // the ViewPager.
    viewPager.setCurrentItem(tab.getPosition());
    selected = tab.getPosition();
    // invalidate the options menu so it can be updated
    invalidateOptionsMenu();
    // history fragment is at position zero so get this then refresh its
    // view
    ((HistoryFragment) sectionsPagerAdapter.getItem(0)).refresh();
  }

  @Override
  public void onTabReselected(ActionBar.Tab tab,
      FragmentTransaction fragmentTransaction) {
    // Don't need to do anything when the tab is reselected
  }

  /**
   * Provides the Activity with the pages to display for each tab
   * 
   */
  public class SectionsPagerAdapter extends FragmentPagerAdapter {

    // Stores the instances of the pages
    private ArrayList<Fragment> fragments = null;


    public SectionsPagerAdapter(FragmentManager fragmentManager) {
      super(fragmentManager);
      fragments = new ArrayList<Fragment>();
      // create the history view, passes the client handle as an argument
      // through a bundle
      Fragment fragment = new HistoryFragment();
      Bundle args = new Bundle();
      args.putString("handle", getIntent().getStringExtra("handle"));
      fragment.setArguments(args);
      // add all the fragments for the display to the fragments list
      fragments.add(fragment);
      //fragments.add(new SubscribeFragment());
      //fragments.add(new PublishFragment());

    }

    @Override
    public Fragment getItem(int position) {
      return fragments.get(position);
    }

    @Override
    public int getCount() {
      return fragments.size();
    }

    @Override
    public CharSequence getPageTitle(int position) {
      switch (position) {
        case 0 :
          return getString(R.string.history).toUpperCase();
        case 1 :
          return getString(R.string.subscribe).toUpperCase();
        case 2 :
          return getString(R.string.publish).toUpperCase();
      }
      // return null if there is no title matching the position
      return null;
    }

  }

  private class ChangeListener implements PropertyChangeListener {

    @Override
    public void propertyChange(PropertyChangeEvent event) {
      // connection object has change refresh the UI

      connectionDetails.runOnUiThread(new Runnable() {

        @Override
        public void run() {
          connectionDetails.invalidateOptionsMenu();
          ((HistoryFragment) connectionDetails.sectionsPagerAdapter
              .getItem(0)).refresh();

        }
      });

    }
  }
}
