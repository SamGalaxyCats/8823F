#include "vex.h"
#include "merb-graph.h"

using namespace vex;

// Date constructor
MerbGraph::MerbGraph(std::string minYLabel, std::string midYLabel, std::string maxYLabel,
      int totalTime) {

    m_totalTime = totalTime;
    initChart(minYLabel, midYLabel, maxYLabel);
}
 
// Date member function
void MerbGraph::initChart(std::string minYLabel, std::string midYLabel, std::string maxYLabel) {
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

private static void cb( void *arg ) {
}

void MerbGraph::go() {
  // Based on total time, fire a callback every x ms to update the chart
  // For the moment, hard-code it to get the speed
  // Should add a callback so the caller tells us what to graph
    vex::timer().event( cb, 1 );

}

