#include "Graph.h"

int Graph::insertVertex(int64_t vertex)
{
    if (!isValidVertex(vertex))
    {
        return -1;
    }

    decltype(_vertexMap)::iterator verIt = _vertexMap.find(vertex);

    if (_vertexMap.end() != verIt)
    {
        return -1;
    }

    // 原顶点数量作为新顶点索引
    _vertexMap.insert(std::make_pair(vertex, _vertexes));
    _indexVec.emplace_back(vertex);

    for (int64_t i = 0; i < _vertexes; i++)
    {
        _matrix[i].emplace_back(GRAPH_MAX_WEIGHT);
    }
    _matrix.emplace_back(std::vector<int64_t>(_vertexes + 1, GRAPH_MAX_WEIGHT));
    _matrix[_vertexes][_vertexes] = 0;
    _vertexes++;

    return 0;
}

int Graph::eraseVertex(int64_t vertex)
{
    if (!isValidVertex(vertex))
    {
        return -1;
    }

    decltype(_vertexMap)::iterator verIt = _vertexMap.find(vertex);

    if (_vertexMap.end() == verIt)
    {
        return -1;
    }

    int64_t index = verIt->second;

    // 删除矩阵中关联的列
    for (int64_t i = 0; i < _vertexes; i++)
    {
        if (_matrix[i][index] > 0 && _matrix[i][index] < GRAPH_MAX_WEIGHT)
        {
            _edges--;
        }

        _matrix[i].erase(_matrix[i].begin() + index);
    }
    // 矩阵减少一列
    _vertexes--;

    // 删除矩阵中关联的行
    for (int64_t i = 0; i < _vertexes; i++)
    {
        if (_matrix[index][i] > 0 && _matrix[index][i] < GRAPH_MAX_WEIGHT)
        {
            _edges--;
        }
    }
    // 矩阵删除一行
    _matrix.erase(_matrix.begin() + index);

    // 顶点大于删除顶点索引的顶点的索引减一
    _vertexMap.erase(verIt);
    for (PairIntKV &kv : _vertexMap)
    {
        if (kv.second > index)
        {
            kv.second--;
        }
    }

    // 将后者的vertex赋予前者，并删除最后一个元素
    for (int64_t i = index; i < _vertexes; i++)
    {
        _indexVec[i] = _indexVec[i + 1];
    }
    _indexVec.pop_back();

    return 0;
}

int Graph::insertEdge(int64_t start, int64_t end, int64_t weight)
{
    if (start == end)
    {
        return -1;
    }
    if (!isValidVertex(start) || !isValidVertex(end))
    {
        return -1;
    }
    if (!isExistVertex(start) || !isExistVertex(end))
    {
        return -1;
    }

    _matrix[_vertexMap.at(start)][_vertexMap.at(end)] = weight;
    _edges++;

    return 0;
}

int Graph::eraseEdge(int64_t start, int64_t end)
{
    if (start == end)
    {
        return -1;
    }
    if (!isValidVertex(start) || !isValidVertex(end))
    {
        return -1;
    }
    if (!isExistVertex(start) || !isExistVertex(end))
    {
        return -1;
    }

    _matrix[_vertexMap.at(start)][_vertexMap.at(end)] = GRAPH_MAX_WEIGHT;
    _edges--;

    return 0;
}

int64_t Graph::vertexes() const
{
    return _vertexes;
}

int64_t Graph::edges() const
{
    return _edges;
}

bool Graph::isExistVertex(int64_t vertex) const
{
    return _vertexMap.find(vertex) != _vertexMap.end();
}

bool Graph::isExistIndex(int64_t index) const
{
    return index >= 0 && index < _vertexes;
}

bool Graph::isExistEdge(int64_t start, int64_t end) const
{
    return isExistVertex(start) && isExistVertex(end) && _matrix[_vertexMap.at(start)][_vertexMap.at(end)] < GRAPH_MAX_WEIGHT;
}

int64_t Graph::indexOfVertex(int64_t vertex) const
{
    if (!isExistVertex(vertex))
    {
        return -1;
    }

    return _vertexMap.at(vertex);
}

int64_t Graph::vertexOfIndex(int64_t index) const
{
    if (!isExistIndex(index))
    {
        return -1;
    }

    return _indexVec.at(index);
}

void Graph::breadthFirstSearch(int64_t vertex) const
{
    if (!isValidVertex(vertex))
    {
        return;
    }
    if (!isExistVertex(vertex))
    {
        return;
    }

    std::queue<int64_t> indexQue;                   // 储存顶点索引
    std::vector<bool> visitor(_vertexes, false);    // 记录访问节点
    int64_t vertexCount = 0;                        // 记录访问节点数量

    indexQue.emplace(_vertexMap.at(vertex));
    visitor[indexQue.front()] = true;
    while (!indexQue.empty())
    {
        int64_t index = indexQue.front();

        indexQue.pop();
        vertexCount++;
        printf("[%4ld] ", _indexVec[index]);

        // 当遍历完所有元素则退出
        if (vertexCount == _vertexes)
        {
            break;
        }

        for (int64_t i = 0; i < _vertexes; i++)
        {
            if (!visitor[i] && _matrix[index][i] > 0 && _matrix[index][i] < GRAPH_MAX_WEIGHT)
            {
                indexQue.emplace(i);
                visitor[i] = true;
            }
        }
    }
    printf("\n");
}

void Graph::depthFirstSearch(int64_t vertex) const
{
    if (!isValidVertex(vertex))
    {
        return;
    }
    if (!isExistVertex(vertex))
    {
        return;
    }

    std::vector<bool> visitor(_vertexes, false);    // 记录访问节点
    int64_t vertexCount = 0;                        // 记录访问节点数量

    std::function<void(int64_t)> dfs = [&](int64_t ver) {
        int64_t index = _vertexMap.at(ver);

        visitor[index] = true;
        vertexCount++;
        printf("[%4ld] ", ver);

        // 所有顶点均已遍历完成则退出
        if (_vertexes == vertexCount)
        {
            return;
        }

        for (int64_t i = 0; i < _vertexes; i++)
        {
            if (!visitor[i] && _matrix[index][i] > 0 && _matrix[index][i] < GRAPH_MAX_WEIGHT)
            {
                dfs(_indexVec[i]);
            }
        }
    };

    dfs(vertex);
    printf("\n");
}

void Graph::printMatrix() const
{
    for (int64_t i = 0; i < _vertexes; i++)
    {
        for (int64_t j = 0; j < _vertexes; j++)
        {
            if (GRAPH_MAX_WEIGHT == _matrix[i][j])
            {
                printf("%4s ", "N");
            }
            else
            {
                printf("%4ld ", _matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int64_t Graph::dijkstra(int64_t start, int64_t end, bool isPrint) const
{
    if (!isExistVertex(start) || !isExistVertex(end))
    {
        return GRAPH_MAX_WEIGHT;
    }

    int64_t startIndex = _vertexMap.at(start);
    int64_t endIndex = _vertexMap.at(end);

    std::vector<GTable> table(_vertexes);        // 顶点权表
    std::vector<bool> visitor(_vertexes, false); // 标记顶点

    // 初始化顶点权表，源顶点可达则将其前驱顶点置为源顶点
    for (ConstPairIntKV &kv : _vertexMap)
    {
        // 目标顶点索引
        table[kv.second]._target = kv.second;

        /**
         * 起始索引与目标索引一致则前驱索引为-1
         * 起始顶点与目标顶点不可达则前驱索引为-1
         * 二者不相等且可达则将前驱索引置为起始索引
         */
        if (startIndex != kv.second && _matrix[startIndex][kv.second] < GRAPH_MAX_WEIGHT)
        {
            table[kv.second]._previous = startIndex;
        }
        else
        {
            table[kv.second]._previous = -1;
        }

        table[kv.second]._weight = _matrix[startIndex][kv.second];
    }

    visitor[startIndex] = true;

    // 源顶点不必再查，减少一次循环
    for (int64_t loopSize = 1; loopSize < _vertexes; loopSize++)
    {
        int64_t nearIndex = -1;                 // 源顶点至权最小顶点的索引
        int64_t minWeight = GRAPH_MAX_WEIGHT;   // 源顶点到该顶点的最小权

        // 获取未访问过且源顶点可达的顶点索引和权
        for (ConstPairIntKV &kv : _vertexMap)
        {
            if (!visitor[kv.second] && table[kv.second]._weight < minWeight)
            {
                nearIndex = kv.second;
                minWeight = table[kv.second]._weight;
            }
        }
        // 若没有找到最小顶点则已查找完毕
        if (nearIndex < 0)
        {
            break;
        }
        visitor[nearIndex] = true;

        // 当前可访问顶点出发，为每一个可达顶点赋予权及前驱顶点
        for (ConstPairIntKV &kv : _vertexMap)
        {
            // 最近顶点与其权 + 源顶点到最近顶点的权 < 顶点权表中当前权
            if (!visitor[kv.second] && _matrix[nearIndex][kv.second] + minWeight < table[kv.second]._weight)
            {
                table[kv.second]._weight = _matrix[nearIndex][kv.second] + minWeight;
                table[kv.second]._previous = nearIndex;
            }
        }
    }

    if (isPrint)
    {
        printDijkstra(table, start, end);
    }

    return table[endIndex]._weight;
}

bool Graph::isValidVertex(int64_t vertex)
{
    return vertex >= 0;
}

bool Graph::isValidEdge(int64_t start, int64_t end)
{
    return isValidVertex(start) && isValidVertex(end);
}

bool Graph::isValidIndex(int64_t index)
{
    return index >= 0;
}

void Graph::printDijkstra(const std::vector<GTable> &table, int64_t start, int64_t end) const
{
    if (!isExistVertex(start) || !isExistVertex(end))
    {
        return;
    }

    int64_t startIndex = _vertexMap.at(start);
    int64_t endIndex = _vertexMap.at(end);

    std::stack<int64_t> path;        // 记录路径
    int64_t previous = endIndex;     // 追溯最近的前驱顶点

    if (table[endIndex]._weight < GRAPH_MAX_WEIGHT)
    {
        if (startIndex == endIndex)
        {
            path.emplace(endIndex);
            path.emplace(startIndex);
        }
        else
        {
            while (previous >= 0)
            {
                path.emplace(previous);
                previous = table[previous]._previous;
            }
        }
    }

    if (path.empty())
    {
        printf("[%4ld] -> [%4ld] : [%4s]    CAN NOT REACH!\n", _indexVec.at(startIndex), _indexVec.at(endIndex), "N");
    }
    else
    {
        printf("[%4ld] -> [%4ld] : [%4ld]    PATH => ", _indexVec.at(startIndex), _indexVec.at(endIndex), table[endIndex]._weight);
        while (!path.empty())
        {
            printf("%4ld ", _indexVec.at(path.top()));
            path.pop();
        }
        printf("\n");
    }
}
