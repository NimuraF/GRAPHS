<h2>Основная информация</h2>
<ul>
  <li><p>Все программы должны быть независимы друг от друга и зависимы от NativeClasses, т.е. все функции, которые применяются в нескольких программах и при этом не принадлежат классам Native, должны быть реализованы в каждом таске по отдельности.</p>
  </li>
  <li><p>Для всех нативных классов обязан быть реализован основной перечень функций (однако допустимо вводить технические методы и парсеры внутрь класса)</p>
    <ol type="1">
      <li>
        weight(Vertex vi, Vertex vj) – весовая функция, принимает номера вершин, возвращает вес ребра, связывающего их;
      </li>
      <li>
        is_edge(Vertex vi, Vertex vj) – функция, принимающая номера вершин и возвращает True, если в графе есть соответствующее ребро/дуга, False, если ребра нет;
      </li>
      <li>
        adjacency_matrix() – функция, возвращающая матрицу смежности графа/орграфа;
      </li>
      <li>
        adjacency_list(Vertex v) – функция, возвращающая список вершин, смежных вершине v;
      </li>
      <li>
        list_of_edges() – функция, возвращающая список всех рёбер графа;
      </li>
      <li>
        is_directed() – функция возвращающая True, если граф ориентированный, False, если граф простой;
      </li>
    </ol>
  </li>
  <li>
    Каждый таск поддерживает свой собственный перечень флагов и содержит в себе обязательные флаги для чтения из файла и справку, ознакомиться со словарём для каждого таска можно в переопределённом методе keys();
  </li>
</ul>


<h2>TASK 1</h2>
<p>Программа, рассчитывающая следующие характеристики графа/орграфа: вектор степеней вершин, матрицу расстояний, диаметр, радиус, множество центральных вершин (для графа), множество периферийных вершин (для графа). Расчёт производится алгоритмом Флойда-Уоршелла. Входные данные для работы программы задаются следующими ключами с параметрами:
</p>
<ul>
  <li>
    -e "edges_list_file_path"
  </li>
  <li>
    -m "adjacency_matrix_file_path"
  </li>
  <li>
    -l "adjacency_list_file_path"
  </li>
</ul>
<p>Одновременно может указываться только один из этих ключей. Если указано более одного – выдать сообщение об ошибке. Результаты работы выводятся на экран, либо в файл при указании следующего ключа: -o "output_file_path". Также должна быть доступна справка, в которой указывается: автор работы, группа, список ключей с кратким описанием. Справка вызывается при помощи ключа -h. При этом, если указаны остальные ключи, они игнорируются.
</p>


<h2>TASK 2</h2>
<p>Программа, определяющая связность. Для графа – связность, а также количество и состав компонент связности. Для орграфа – сильную, слабую связность, или несвязность. А также количество и состав компонент связности и сильной связности. Для определения используется поиск в ширину.
</p>


<h2>TASK 3</h2>
<p>Программа, находящая мосты и шарниры в графе. Для орграфа находятся мосты и шарниры в соотнесённом графе.
</p>


<h2>TASK 4</h2>
<p>Программа, находящая остовное дерево графа. Для орграфа находится остовное дерево соотнесённого графа. Результатом является список рёбер графа, входящих в остовное дерево и суммарный вес дерева. Алгоритм для расчёта задаётся следующими ключами:
</p>
<ul>
  <li>
    -k – алгоритм Крускала
  </li>
  <li>
    -p – алгоритм Прима
  </li>
  <li>
    -b – алгоритм Борувки
  </li>
  <li>
    -s – расчёт производится тремя алгоритмами поочерёдно
  </li>
</ul>
<p>Результатом в первых трёх случаях является список рёбер, составляющих остовное дерево. В четвёртом случае дополнительно выводится время работы алгоритма в мс.</p>


<h2>TASK 5</h2>
<p>Программа, находящая геодезическую цепь между двумя вершинами в графе. Поиск производится алгоритмом Дейкстры. Результатом работы является маршрут между вершинами, заданный списком рёбер, и длина маршрута. Начальная вершина задаётся следующим ключом: -n begin_vertex_number. Данный ключ является обязательным. Конечная вершина задаётся следующим ключом: -d end_vertex_number. Данный ключ является обязательным.
</p>


<h2>TASK 6</h2>
<p>Программа, рассчитывающая расстояние от указанной вершины до всех остальных вершин в графе. Результатом работы является перечисление пар вершин, и соответствующих расстояний между ними. Алгоритм для расчёта задаётся следующими ключами:
</p>
<ul>
  <li>
    -d – алгоритм Дейкстры
  </li>
  <li>
    -b – алгоритм Беллмана-Форда-Мура
  </li>
  <li>
    -t – алгоритм Левита
  </li>
</ul>
<p>Если граф/орграф не удовлетворяет требованиям алгоритма к входным данным, выдать пользователю соответствующее предупреждение. Начальная вершина задаётся следующим ключом: -n begin_vertex_number. Данный ключ является обязательным.
</p>


<h2>TASK 7</h2>
<p>Программа, рассчитывающая расстояние между всеми парами вершин в графе. Поиск производится алгоритмом Джонсона. Результатом работы является перечисление пар вершин, и соответствующих расстояний между ними.
</p>


<h2>TASK 8</h2>
<p>Программа, рассчитывающая расстояние между двумя точками на карте. Поиск производится алгоритмом 𝐴∗. Результатом работы является маршрут между вершинами, заданный списком пройденных точек. Карта представляет собой прямоугольную матрицу, где 𝑖-я строка и 𝑗-й столбец задают «клетку» на карте. Значение представляет собой высоту местности в данной точке. Переход возможен только между соседними «клетками» по вертикали или горизонтали. Расстояние между клетками выражается следующей функцией: ℎ(𝑖𝑗, 𝑘𝑙) = 𝑎𝑏𝑠(𝑘 − 𝑖) + 𝑎𝑏𝑠(𝑙 − 𝑗) + 𝑎𝑏𝑠(𝑎𝑘𝑙 − 𝑎𝑖𝑗), где 𝑖𝑗 – координаты текущей «клетки», 𝑘𝑙 – координаты соседней клетки, 𝑎𝑖𝑗 – значение в текущей «клетке», обозначающее высоту в этой точке, 𝑎𝑘𝑙 – значение высоты в «клетке» с координатами 𝑘𝑙. Эвристики задаются следующими функциями (𝑠𝑝 – координаты конечной точки маршрута):
</p>
<ul type="A">
  <li>
    Манхэттенское расстояние 𝑑(𝑖𝑗, 𝑠𝑝) = 𝑎𝑏𝑠(𝑠 − 𝑖) + 𝑎𝑏𝑠(𝑝 − 𝑗).
  </li>
  <li>
    Расстояние Чебышева 𝑑(𝑖𝑗, 𝑠𝑝) = max(𝑎𝑏𝑠(𝑠 − 𝑖), 𝑎𝑏𝑠(𝑝 − 𝑗)).
  </li>
  <li>
    Евклидово расстояние 𝑑(𝑖𝑗, 𝑠𝑝) = sqrt((𝑠 − 𝑖)^2 + (𝑝 − 𝑗)^2)
  </li>
  <li>
    Эвристика отсутствует (алгоритм Дейкстры) 𝑑(𝑖𝑗, 𝑠𝑝) = 0.
  </li>
</ul>
<p>Входной файл для работы программы задаётся следующим ключом: -m "map_file_path". Начальная вершина задаётся следующим ключом c параметрами: -n begin_vertex_x begin_vertex_y. Данный ключ является обязательным. Конечная вершина задаётся следующим ключом: -d end_vertex_x end_vertex_y. Данный ключ является обязательным. Алгоритм запускается поочерёдно со всеми эвристиками. Для каждой эвристики выводится найденный маршрут, его длина и процент просмотренных алгоритмом клеток от общего их числа.
</p>
