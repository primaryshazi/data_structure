#include "Graph.h"

int main()
{
    /**
     *    2  →  3
     *  ↗  ↘  ↗  ↘
     * 1     ×     4
     *  ↖  ↗  ↘  ↙
     *    6     5
     */
    const int64_t VERTEX_SIZE = 6;
    Graph graph;

    for (int64_t i = 0; i < VERTEX_SIZE; i++)
    {
        graph.insertVertex(i + 1);
    }
    /**
     * => vertex : 6 edge : 0
     * =>    0    N    N    N    N    N
     * =>    N    0    N    N    N    N
     * =>    N    N    0    N    N    N
     * =>    N    N    N    0    N    N
     * =>    N    N    N    N    0    N
     * =>    N    N    N    N    N    0
     */
    std::cout << "vertex : " << graph.vertexes() << " edge : " << graph.edges() << std::endl;
    graph.printMatrix();
    std::cout << std::endl;

    graph.insertEdge(1, 2, 10);
    graph.insertEdge(2, 3, 20);
    graph.insertEdge(3, 4, 30);
    graph.insertEdge(4, 5, 40);
    graph.insertEdge(5, 6, 50);
    graph.insertEdge(6, 1, 60);
    graph.insertEdge(2, 5, 70);
    graph.insertEdge(6, 3, 80);
    /**
     * => vertex : 6 edge : 8
     * =>    0   10    N    N    N    N
     * =>    N    0   20    N   70    N
     * =>    N    N    0   30    N    N
     * =>    N    N    N    0   40    N
     * =>    N    N    N    N    0   50
     * =>   60    N   80    N    N    0
     */
    std::cout << "vertex : " << graph.vertexes() << " edge : " << graph.edges() << std::endl;
    graph.printMatrix();
    std::cout << std::endl;

    graph.eraseEdge(2, 5);
    graph.eraseEdge(6, 3);
    /**
     * => vertex : 6 edge : 6
     * =>    0   10    N    N    N    N
     * =>    N    0   20    N    N    N
     * =>    N    N    0   30    N    N
     * =>    N    N    N    0   40    N
     * =>    N    N    N    N    0   50
     * =>   60    N    N    N    N    0
     */
    std::cout << "vertex : " << graph.vertexes() << " edge : " << graph.edges() << std::endl;
    graph.printMatrix();
    std::cout << std::endl;

    graph.eraseVertex(4);
    graph.eraseVertex(5);
    graph.eraseVertex(6);
    /**
     * => vertex : 3 edge : 2
     * =>    0   10    N
     * =>    N    0   20
     * =>    N    N    0
     */
    std::cout << "vertex : " << graph.vertexes() << " edge : " << graph.edges() << std::endl;
    graph.printMatrix();
    std::cout << std::endl;

    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    /**
     * => vertex : 6 edge : 2
     * =>    0   10    N    N    N    N
     * =>    N    0   20    N    N    N
     * =>    N    N    0    N    N    N
     * =>    N    N    N    0    N    N
     * =>    N    N    N    N    0    N
     * =>    N    N    N    N    N    0
     */
    std::cout << "vertex : " << graph.vertexes() << " edge : " << graph.edges() << std::endl;
    graph.printMatrix();
    std::cout << std::endl;

    graph.insertEdge(3, 4, 30);
    graph.insertEdge(4, 5, 40);
    graph.insertEdge(6, 1, 60);
    graph.insertEdge(2, 5, 70);
    graph.insertEdge(6, 3, 80);
    /**
     * => vertex : 6 edge : 7
     * =>    0   10    N    N    N    N
     * =>    N    0   20    N   70    N
     * =>    N    N    0   30    N    N
     * =>    N    N    N    0   40    N
     * =>    N    N    N    N    0    N
     * =>   60    N   80    N    N    0
     */
    std::cout << "vertex : " << graph.vertexes() << " edge : " << graph.edges() << std::endl;
    graph.printMatrix();
    std::cout << std::endl;

    /**
     * => [   1] -> [   1] : [   0]    PATH =>    1    1
     * => [   1] -> [   2] : [  10]    PATH =>    1    2
     * => [   1] -> [   3] : [  30]    PATH =>    1    2    3
     * => [   1] -> [   4] : [  60]    PATH =>    1    2    3    4
     * => [   1] -> [   5] : [  80]    PATH =>    1    2    5
     * => [   1] -> [   6] : [   N]    CAN NOT REACH!
     * => [   2] -> [   1] : [   N]    CAN NOT REACH!
     * => [   2] -> [   2] : [   0]    PATH =>    2    2
     * => [   2] -> [   3] : [  20]    PATH =>    2    3
     * => [   2] -> [   4] : [  50]    PATH =>    2    3    4
     * => [   2] -> [   5] : [  70]    PATH =>    2    5
     * => [   2] -> [   6] : [   N]    CAN NOT REACH!
     * => [   3] -> [   1] : [   N]    CAN NOT REACH!
     * => [   3] -> [   2] : [   N]    CAN NOT REACH!
     * => [   3] -> [   3] : [   0]    PATH =>    3    3
     * => [   3] -> [   4] : [  30]    PATH =>    3    4
     * => [   3] -> [   5] : [  70]    PATH =>    3    4    5
     * => [   3] -> [   6] : [   N]    CAN NOT REACH!
     * => [   4] -> [   1] : [   N]    CAN NOT REACH!
     * => [   4] -> [   2] : [   N]    CAN NOT REACH!
     * => [   4] -> [   3] : [   N]    CAN NOT REACH!
     * => [   4] -> [   4] : [   0]    PATH =>    4    4
     * => [   4] -> [   5] : [  40]    PATH =>    4    5
     * => [   4] -> [   6] : [   N]    CAN NOT REACH!
     * => [   5] -> [   1] : [   N]    CAN NOT REACH!
     * => [   5] -> [   2] : [   N]    CAN NOT REACH!
     * => [   5] -> [   3] : [   N]    CAN NOT REACH!
     * => [   5] -> [   4] : [   N]    CAN NOT REACH!
     * => [   5] -> [   5] : [   0]    PATH =>    5    5
     * => [   5] -> [   6] : [   N]    CAN NOT REACH!
     * => [   6] -> [   1] : [  60]    PATH =>    6    1
     * => [   6] -> [   2] : [  70]    PATH =>    6    1    2
     * => [   6] -> [   3] : [  80]    PATH =>    6    3
     * => [   6] -> [   4] : [ 110]    PATH =>    6    3    4
     * => [   6] -> [   5] : [ 140]    PATH =>    6    1    2    5
     * => [   6] -> [   6] : [   0]    PATH =>    6    6
     */
    for (int64_t i = 0; i < graph.vertexes(); i++)
    {
        for (int64_t j = 0; j < graph.vertexes(); j++)
        {
            graph.dijkstra(i + 1, j + 1, true);
        }
    }
    std::cout << std::endl;

    /**
     * => [   1] [   2] [   3] [   5] [   4]
     * => [   2] [   3] [   5] [   4]
     * => [   3] [   4] [   5]
     * => [   4] [   5]
     * => [   5]
     * => [   6] [   1] [   3] [   2] [   4] [   5]
     */
    for (int64_t i = 0; i < graph.vertexes(); i++)
    {
        graph.breadthFirstSearch(graph.vertexOfIndex(i));
    }
    std::cout << std::endl;

    /**
     * => [   1] [   2] [   3] [   4] [   5]
     * => [   2] [   3] [   4] [   5]
     * => [   3] [   4] [   5]
     * => [   4] [   5]
     * => [   5]
     * => [   6] [   1] [   2] [   3] [   4] [   5]
     */
    for (int64_t i = 0; i < graph.vertexes(); i++)
    {
        graph.depthFirstSearch(graph.vertexOfIndex(i));
    }
    std::cout << std::endl;

    return 0;
}
