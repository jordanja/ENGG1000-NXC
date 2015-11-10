task main() {
     int color;
     int turn;
     int threshold;
     int power = 90;
     int min = 999;
     int max = -1;
     unsigned long end_time;
     
     SetSensorColorRed(IN_3);
     Wait(200);
     
     // calibration: turn left

     end_time = CurrentTick() + 500;
     OnFwd(OUT_C, 50);
     OnRev(OUT_A, 50);
     while (CurrentTick() < end_time) {
         color = Sensor(IN_3);
         if (color > max) {
             max = color;
         } else if (color < min) {
             min = color;
         }
     }

     // calibration: turn right

     end_time = CurrentTick() + 1000;
     OnFwd(OUT_C, 50);
     OnRev(OUT_B, 50);
     while (CurrentTick() < end_time) {
         color = Sensor(IN_3);
         if (color > max) {
             max = color;
         } else if (color < min) {
             min = color;
         }
     }

     threshold = (min+max)/2;

     ClearLine(LCD_LINE3);
     NumOut(40, LCD_LINE3, threshold);

     // calibration done, find the edge of the line

     OnFwd(OUT_C, 50);
     OnRev(OUT_B, 50);
     while (Sensor(IN_3) > threshold) {
     }
     Off(OUT_BC);

     // and follow it
     
     while (true) {
         color = Sensor(IN_3);

         turn = power+200*(threshold-color)/(max-min);
         if (turn > 100)
            turn = 100;
         if (turn < 0)
            turn = 0;
         OnFwd(OUT_C, turn);
         turn = power-200*(threshold-color)/(max-min);
         if (turn > 100)
            turn = 100;
         if (turn < 0)
            turn = 0;
         OnFwd(OUT_C, turn);
     }
}