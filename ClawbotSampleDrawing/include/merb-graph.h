#ifndef MERB_GRAPH_H
#define MERB_GRAPH_H
 
class MerbGraph
{
private:
    int m_totalTime;

    void initChart(std::string minYLabel, std::string midYLabel, std::string maxYLabel);
 
public:
    MerbGraph(std::string minYLabel, std::string midYLabel, std::string maxYLabel,
      int totalTime);

    void go();
};
 
#endif