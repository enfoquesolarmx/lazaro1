long randamp;
long randvolt;

uint32_t lastSample = 0;

unsigned long 
currentRoutineMillis  = 0,           //SYSTEM PARAMETER -
prevRoutineMillis     = 0,           //SYSTEM PARAMETER -
secondsElapsed        = 0;           //SYSTEM PARAMETER - 

int 
powerInput            = 0.0000,      // SYSTEM PARAMETER - Input power (solar power) in Watts
millisRoutineInterval   = 250,       //  USER PARAMETER - Time Interval Refresh Rate For Routine Functions (ms)
maxval = 0;

float 
daysRunning           = 0.0000,      // SYSTEM PARAMETER - Stores the total number of days the MPPT device has been running since last powered
Wh                    = 0.0000,      // SYSTEM PARAMETER - Stores the accumulated energy harvested (Watt-Hours)
kWh                   = 0.0000,      // SYSTEM PARAMETER - Stores the accumulated energy harvested (Kiliowatt-Hours)
MWh                   = 0.0000,      // SYSTEM PARAMETER - Stores the accumulated energy harvested (Megawatt-Hours)
energySavings         = 0.0000,      // SYSTEM PARAMETER - Energy savings in fiat currency (Peso, USD, Euros or etc...)
electricalPrice       = 3.5000,      //   USER PARAMETER - Input electrical price per kWh (Dollar/kWh,Euro/kWh,Peso/kWh)
vmax                  = 0.0,      //   USER PARAMETER - Voltaje Maximo detectado
vmaxn                = 0.0,      //   USER PARAMETER - Amperaje Maximo detectado
amax                  = 0.0;      //   USER PARAMETER - Amperaje Maximo detectado

static int dispCnt;

unsigned long
timeOn                = 0;           //SYSTEM PARAMETER -

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); 

}

void loop() {
  // put your main code here, to run repeatedly:

  randamp = random(40, 100);
  randvolt = random(0,100);
powerInput = (randamp*randvolt);

  if (millis() - lastSample > 100) { // Every 100ms:
        lastSample = millis();
     //   Serial.println(maxVal);
        maxval = 0;
    }
 int reading = randvolt;
    if (reading > maxval) {
        maxval = reading;
    }

  //TIME DEPENDENT SENSOR DATA COMPUTATION
  currentRoutineMillis = millis();
  if(currentRoutineMillis-prevRoutineMillis>=millisRoutineInterval){   //Run routine every millisRoutineInterval (ms)
  prevRoutineMillis = currentRoutineMillis;                          //Store previous time
  Wh = Wh+(powerInput/(3600.000*(1000.000/millisRoutineInterval)));  //Accumulate and compute energy harvested (3600s*(1000/interval))
  kWh = Wh/1000.000;
  MWh = Wh/1000000.000;
  daysRunning = timeOn/(86400.000*(1000.000/millisRoutineInterval)); //Compute for days running (86400s*(1000/interval))
  timeOn++;   //Increment time counter

  secondsElapsed = millis()/1000;                                      //Gets the time in seconds since the was turned on  and active
  energySavings  = electricalPrice*(Wh/1000.0000);                     //Computes the solar energy saving in terms of money (electricity flag rate) 

 
  
  if (dispCnt >= 10) {        // display updated every 50 cycle to avoid flickering
     dispCnt = 0;
  Serial.println("---------------------");

  Serial.print("Voltaje:");
  Serial.println(randvolt);

  Serial.print("Amp:");
  Serial.println(randamp);
  
  Serial.print("Potencia:");
  Serial.println(randamp*randvolt);
  
  Serial.print("Watts Hora:");
  Serial.println(Wh);
  
  Serial.print("tiempo min = ");
  Serial.println(secondsElapsed/60);

  Serial.print("Costo Pesos = ");
  Serial.println(energySavings);

 Serial.print("voltaje Maximo = ");
  Serial.println(maxval);
  
  }
  dispCnt++;
  
  
  } 



  
}
