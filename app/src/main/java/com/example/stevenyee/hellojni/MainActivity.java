package com.example.stevenyee.hellojni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
//
public class MainActivity extends AppCompatActivity {
    static int rows;
    static int cols;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("helloJNI");
        System.loadLibrary("acquisition");
    }
//    public native String helloJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final EditText rowNum = (EditText) findViewById(R.id.RowField);
        final EditText colNum = (EditText) findViewById(R.id.ColField);

        Button startBtn = (Button) findViewById(R.id.StartButton);
        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                try{
                    rows = Integer.parseInt(rowNum.getText().toString());
                    cols = Integer.parseInt(colNum.getText().toString());
                    TextView view = (TextView) findViewById(R.id.EnterText);
                    if(rowsColumns(rows, cols) == cols){
                        int temp = rowsColumns(rows, cols);
                        String str = String.valueOf(temp);
                        view.setText(str);
                    } else {
                        view.setText("Failures");
                    }
                } catch (Exception e){
                    e.printStackTrace();
                    Toast.makeText(MainActivity.this, "Please fill in both fields", Toast.LENGTH_LONG).show();
                }

            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
    public native int rowsColumns(int rows, int cols);

}
