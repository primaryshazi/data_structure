#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <limits>
#include <functional>

const int64_t GRAPH_MAX_WEIGHT = std::numeric_limits<int32_t>::max();   // 不可到达距离

struct GTable
{
    int64_t _target;     // 目标顶点的索引
    int64_t _weight;     // 源顶点至目标顶点的最小权
    int64_t _previous;   // 目标索引的权最小的前驱索引

    GTable() : GTable(0, 0, 0) {}
    GTable(int64_t t, int64_t w, int64_t p) : _target(t), _weight(w), _previous(p) {}
    ~GTable() {}
};

class Graph
{
public:
    Graph() : _vertexes(0), _edges(0) {}
    ~Graph() {}

    /**
     * @brief 添加顶点
     *
     * @param vertex
     * @return int
     */
    int insertVertex(int64_t vertex);

    /**
     * @brief 移除顶点
     *
     * @param vertex
     * @return int
     */
    int eraseVertex(int64_t vertex);

    /**
     * @brief 添加边
     *
     * @param start
     * @param end
     * @param weight
     * @return int
     */
    int insertEdge(int64_t start, int64_t end, int64_t weight);

    /**
     * @brief 移除边
     *
     * @param start
     * @param end
     * @return int
     */
    int eraseEdge(int64_t start, int64_t end);

    /**
     * @brief 顶点数量
     *
     * @return int64_t
     */
    int64_t vertexes() const;

    /**
     * @brief 边数量
     *
     * @return int64_t
     */
    int64_t edges() const;

    /**
     * @brief 顶点是否存在
     *
     * @param vertex
     * @return bool
     */
    bool isExistVertex(int64_t vertex) const;

    /**
     * @brief 索引是否存在
     *
     * @param vertex
     * @return bool
     */
    bool isExistIndex(int64_t index) const;

    /**
     * @brief 边是否存在
     *
     * @param start
     * @param end
     * @return bool
     */
    bool isExistEdge(int64_t start, int64_t end) const;

    /**
     * @bried 获取顶点映射的索引
     *
     * @param vertex
     * @return int64_t
     */
    int64_t indexOfVertex(int64_t vertex) const;

    /**
     * @brief 获取索引映射的顶点
     * 
     * @param index
     * @return int64_t
     */
    int64_t vertexOfIndex(int64_t index) const;

    /**
     * @brief 广度优先遍历
     *
     * @param vertex
     */
    void breadthFirstSearch(int64_t vertex) const;

    /**
     * @brief 深度优先遍历
     *
     * @param vertex
     */
    void depthFirstSearch(int64_t vertex) const;

    /**
     * @brief 打印邻接矩阵
     */
    void printMatrix() const;

    /**
     * @brief 计算顶点最短路径
     *
     * @param start
     * @param end
     * @param isPrint
     * @return int64_t
     */
    int64_t dijkstra(int64_t start, int64_t end, bool isPrint64_t = false) const;

    /**
     * @brief 顶点ID是否有效
     *
     * @param vertex
     * @param bool
     */
    static bool isValidVertex(int64_t vertex);

    /**
     * @brief 边起终是否有效
     *
     * @param start
     * @param end
     * @return bool
     */
    static bool isValidEdge(int64_t start, int64_t end);

    /**
     * @brief 顶点索引是否有效
     *
     * @param index
     * @param bool
     */
    static bool isValidIndex(int64_t index);

protected:

    /**
     * @brief 打印最短路径
     *
     * @param table
     * @param start
     * @param end
     */
    void printDijkstra(const std::vector<GTable> &table, int64_t start, int64_t end) const;

private:
    typedef std::pair<const int64_t, int64_t> PairIntKV;
    typedef const std::pair<const int64_t, int64_t> ConstPairIntKV;

    int64_t _vertexes;                          // 顶点的数量
    int64_t _edges;                             // 边的数量
    std::vector<std::vector<int64_t>> _matrix;  // 邻接矩阵
    std::map<int64_t, int64_t> _vertexMap;      // 顶点 -> 索引
    std::vector<int64_t> _indexVec;             // 索引 -> 顶点
};

#endif  // GRAPH_H_
