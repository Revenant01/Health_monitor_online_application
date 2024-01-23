package com.example.khalood
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import androidx.activity.ComponentActivity
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.ValueEventListener
import com.google.firebase.database.ktx.database
import com.google.firebase.ktx.Firebase
class MainActivity : ComponentActivity() {
    private val TAG = "MainActivityMainActivity"
    private lateinit var heartRateEdit: TextView
    private lateinit var temperatureEdit: TextView
    private lateinit var temperatureTypeEdit: TextView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        heartRateEdit = findViewById(R.id.HeartRate)
        temperatureEdit = findViewById(R.id.Temperature)

        temperatureTypeEdit = findViewById(R.id.TemperatureType)
        val database = Firebase.database
        val myRef = database.getReference("INFO")
        Log.d(TAG, "onCreate: $myRef")
        myRef.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                val heartRate= dataSnapshot.child("HeartRate").value
                val temperature= dataSnapshot.child("Temperature").value
                heartRateEdit.setText(heartRate.toString())
                val heartRateInt = heartRate.toString().toInt()
                val temperatureDouble = temperature.toString().toDouble()
                val temperatureInt= temperatureDouble.toInt()
                if(temperatureInt>38){
                    temperatureTypeEdit.setText("High")
                }else if(temperatureInt<36){
                    temperatureTypeEdit.setText("Low")
                }else{
                    temperatureTypeEdit.setText("Normal")
                }
                temperatureEdit.setText(temperatureInt.toString())
            }
            override fun onCancelled(error: DatabaseError) {

            }
        })

    }
}
