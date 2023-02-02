import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
ArrayList<PVector> circles = new ArrayList<PVector>();

void setup()
{
  fullScreen();
  //size(1200, 900);
  background(0);
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);
}

void draw()
{
  //background(0);
  if ( myPort.available() > 0) 
  {  // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
  } 
  if (val != null) {
      print(val); //print it out in the console
      String[] list = split(val, ',');
      int mode = Integer.parseInt(list[list.length-1].trim());
      int size = (list.length-1)/2;
      for (int i = 0; i < size; i++) {
        float distance = float(list[i])*900/14000;
        float val = float(list[i+size]);
        float brightness = 0;
        if (val > 750) {
          brightness = (val-750)*255/150;
        }
        if (val < 250) {
          brightness = (250-val)*255/250;
        }
        if(distance <= 900 && distance > 180) {
          for (int j = 0; j < 10; j++) {
            float ang = random(-5, 5);
            switch(mode){
              case 0:
                break;
              case 1:
                ang += 7.5;
                break;
              case 2:
                ang += 15;
                break;
              case 3:
                ang += 22.5;
                break;
              case 4:
                ang -= 7.5;
                break;
              case 5:
                ang -= 15;
                break;
              case 6:
                ang -= 22.5;
                break;
              default:
                break;
            }
            ang = radians(ang);
            float x = (distance+random(-10, 10))*sin(ang);
            float y = (distance+random(-10, 10))*cos(ang);
  
            circles.add(new PVector(width/2 + x, 900-y, brightness));
          }
        }
      }
      
      if (circles.size() > 3600) {
        circles = new ArrayList<PVector>(circles.subList(circles.size()-3601, circles.size()-1));
      }
      
      for (PVector p : circles) {
        fill(255,255,255,p.z);
        circle(p.x, p.y, 10);
      }

  }
}
