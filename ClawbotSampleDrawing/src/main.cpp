/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Drawing Shapes                                            */
/*    This program creates a star made of different colored lines, and then a */
/*    large box with a solid filled color.                                    */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "merb-graph.h"

using namespace vex;

void findExtents() {
  // Figure out the extents and how to draw
  // 480 x 272 pixel (X by Y) according to the doc

  Brain.Screen.setPenWidth(3);
  Brain.Screen.setPenColor(red);

  // top
  Brain.Screen.drawLine(0, 0, 100, 0); // Y shows at 0 but not whole thickness.  probably need to go down as thick as pen width.
  Brain.Screen.drawLine(100, 1, 200, 1); // Y shows at 0 but not whole thickness.  probably need to go down as thick as pen width.
  Brain.Screen.drawLine(200, 2, 482, 2); // Y shows at 0 but not whole thickness.  probably need to go down as thick as pen width.

  // Left edge
  Brain.Screen.drawLine(1, 0, 1, 50);
  Brain.Screen.drawLine(2, 50, 2, 130);
  Brain.Screen.drawLine(3, 130, 3, 270); 

  // bottom
  // Maybe header on screen causes limit.  Any way to hide it?
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawLine(0, 238, 100, 238); // lowest you can go to get the full stroke.  
  Brain.Screen.drawLine(100, 239, 200, 239); 
  Brain.Screen.drawLine(200, 240, 482, 240); 

  // Right edge
  Brain.Screen.drawLine(478, 0, 478, 50);
  Brain.Screen.drawLine(479, 50, 479, 130);
  Brain.Screen.drawLine(480, 130, 480, 270); 
}

// TODO make pixel a class
int generatePixelValue(int min, int max) {

  // Examples
  /*
    v1 = rand() % 100;         // v1 in the range 0 to 99
    v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
    v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014
  */

  int generatedValue = rand() % (max-min) + min;
  return generatedValue;
}

void drawGraphLine() {
  // Generate points within the extents with x always greater than previous x

  // Note: cannot get the actual system time to see a rand number generator, always end up with the same value!
  // time_t current_time;
	// current_time = time(NULL);
  // printf("time: %ln", current_time);
  // printf("system time: %ln", vex::timer::system());

  // srand (time(NULL));

  int startX = 0;
  int startY = 238;

  int previousX = startX;
  int previousY = startY;

  while (previousX < 475) {

    int nextX = generatePixelValue(previousX, 478);
    int nextY = generatePixelValue(0, 238);

    // Don't need to draw a circle there but we could.... for now just try a line
    Brain.Screen.drawLine(previousX, previousY, nextX, nextY);

    previousX = nextX;
    previousY = nextY;
  }
}

void initChart(std::string minYLabel, std::string midYLabel, std::string maxYLabel) {
  // Need min/max displayed
  // x-axis time, y-axis speed
  Brain.Screen.setPenWidth(3);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawLine(20, 0, 20, 238); 

  const char *min = minYLabel.c_str();
  const char *mid = midYLabel.c_str();
  const char *max = minYLabel.c_str();

  Brain.Screen.printAt(1, 15, min);
  Brain.Screen.printAt(1, 125, mid);
  Brain.Screen.printAt(1, 235, max);

  // Y-axis
  Brain.Screen.drawLine(1, 238, 480, 238); 

  // Draw a half-way line on the y-axis
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawLine(1, 125, 480, 125); 
}

// Should use a class... apologies, in a hurry
int previousX = 0;
int previousY = 0;
int nextX;
int nextY;

vex::timer       Timer;
void cb( void *arg ) {
   // std::cout << "timer fired sys:" << timer::system() << " timer:" << Timer << "  \n";
   //printf("timer fired sys:: %lu", timer::system());

  Brain.Screen.setPenWidth(3);
  Brain.Screen.setPenColor(yellow);
  nextX = previousX + 1;
  nextY = previousY + 1;

  Brain.Screen.drawLine(previousX, nextX, previousY, nextY); 

  previousX = nextX;
  previousY = nextY;

    // rearm
  vex::timer().event(cb, 1);    
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //findExtents();

  //drawGraphLine();

  initChart("-100", "0", "100");

  // At regular intervals, plot the points.  This version assumes no screen jumps, and that we know maxX.

  // Take max expected run time.  Divide into intervals and establish a callback to do the next plot.
  int maxTime = 1000;  // ms

  // Should cut it off once we hit that to not overwrite the graph
  // fire in 1 seconds time
  printf("setting timer"); 
  vex::timer().event( cb, 1 );

  // TODO create a class for all of this, and need to draw the speed out!!
  // Submit a max time, and divide out to only plot as many pts as will fit.

  // Example
  MerbGraph graph("-100", "0", "100", 5); 

  // Fire timer with a callback to update the chart... the timer callback establishes
  // how often to update the chart and does the drawing, but it needs the variable
  // that we are graphing... unless we call this 'SpeedGraph'
  graph.go();

}
