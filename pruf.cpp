#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
// Объявляем функции `pruferCode` и `pruferDecode`,
// которые будут использоваться в главной функции.
std::vector<int> pruferCode(std::vector<std::pair<int, int>> edges);
std::vector<std::pair<int, int>> pruferDecode(std::vector<int> c);

int main()
{
    /* Создаём вектор `edges`, который содержит набор рёбер графа.*/
    std::vector<std::pair<int, int>> edges = {{1, 2}, {1, 7}, {1, 8}, {2, 6}, {3, 5}, {4, 5}, {5, 6}, {5, 9}};

    /* Вызываем функцию `pruferCode` с `edges` в качестве аргумента,
     * чтобы получить код Прюфера для этого графа.
     */
    std::vector<int> code = pruferCode(edges);

    /* Вызываем функцию `pruferDecode` с `code` в качестве аргумента,
     * чтобы расшифровать код Прюфера и получить вектор пар вершин.
     */
    std::vector<std::pair<int, int>> nodes = pruferDecode(code);
    
    // Выводим на экран результат.
    std::cout << "Prufer's code: ";
    for (int i = 0; i < code.size(); i++)
    {
        std::cout << code[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Nodes: ";
    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << "(" << nodes[i].first << ", " << nodes[i].second << ") ";
    }
    std::cout << std::endl;

    // Возвращаем 0, чтобы показать, что программа завершилась без ошибок.
    return 0;
}

// Объявляем функцию `pruferCode`, которая будет принимать вектор пар целых чисел `edges`
// и возвращать вектор целых чисел `pruf_code` - код Прюфера.
std::vector<int> pruferCode(std::vector<std::pair<int, int>> edges)
{
    // Создаём пустой вектор `pruf_code`, который будет хранить код Прюфера.
    std::vector<int> pruf_code;

    // Запускаем цикл while, который будет выполняться до тех пор,
    // пока в векторе `edges` не останется только одна пара.
    while (edges.size() > 1)
    {
        // Создаём хеш-таблицу `counts`, которая будет содержать
        // количество вхождений каждого числа в `edges`.
        std::unordered_map<int, int> counts;
        for (const auto &edge : edges)
        {
            counts[edge.first]++;
            counts[edge.second]++;
        }

        // Создаём пустой вектор `leaf`, в который добавляются все уникальные числа из `counts`,
        // которые встречаются только один раз в `edges`.
        std::vector<int> leaf;
        for (const auto &[number, count] : counts)
        {
            if (count == 1)
            {
                leaf.push_back(number);
            }
        }

        // Находим минимальное число в векторе `leaf` с помощью функции `min_element`.
        int min_leaf = *min_element(leaf.begin(), leaf.end());

        // Находим пару в `edges`, в которой содержится минимальное число, и добавляем в `pruf_code` сосед этого числа.
        int index_to_remove = -1;
        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i].first == min_leaf)
            {
                pruf_code.push_back(edges[i].second);
                index_to_remove = i;
                break;
            }
            if (edges[i].second == min_leaf)
            {
                pruf_code.push_back(edges[i].first);
                index_to_remove = i;
                break;
            }
        }

        // Пара, найденная на предыдущем шаге, удаляется из `edges`.
        if (index_to_remove != -1)
        {
            edges.erase(edges.begin() + index_to_remove);
        }
    }

    // Функция возвращает вектор `pruf_code`.
    return pruf_code;
}

// Объявляем функцию `pruferDecode`, которая будет принимать вектор целых чисел `c`
// и возвращать вектор пар целых чисел `nodes` - расшифрованный код Прюфера.
std::vector<std::pair<int, int>> pruferDecode(std::vector<int> c)
{
    // Создаём пустой вектор `nodes`, который будет хранить расшифрованный код Прюфера.
    std::vector<std::pair<int, int>> nodes;
    // Создаем вектор v, который будет хранить степени вершин графа
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Запускаем цикл while, который будет выполняться до тех пор,
    // пока в векторе `c` не останется элементов.
    while (!c.empty())
    {

        // Создаем пустой вектор `remain_elements`, в который добавляются элементы из `v`,
        // которые не содержатся в векторе `c`.
        std::vector<int> remain_elements;
        int min_element;
        for (int i = 0; i < v.size(); i++)
        {
            // Если элемент не найден в векторе `c`, добавляем его в `remain_elements`.
            if (std::find(c.begin(), c.end(), v[i]) == c.end())
            {
                remain_elements.push_back(v[i]);
            }
        }

        // Находим минимальный элемент в векторе `remain_elements`.
        min_element = *std::min_element(remain_elements.begin(), remain_elements.end());

        // Получаем первый элемент из вектора `c` и добавляем пару (min_element, first_c_element) в `nodes`.
        int first_c_element = c.front();
        nodes.push_back(std::make_pair(min_element, first_c_element));
        c.erase(c.begin());                                             // Удаляем первый элемент из вектора `c`.
        v.erase(std::remove(v.begin(), v.end(), min_element), v.end()); // Удаляем минимальный элемент из вектора `v`.
        remain_elements.clear();                                        // Очищаем вектор `remain_elements`.
    }

    // Добавляем еще одну пару в `nodes` из оставшихся элементов в векторе `v`.
    nodes.push_back({v[0], v[1]});

    // Функция возвращает вектор `nodes`.
    return nodes;
}
