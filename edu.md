# I. Переменные и циклы

- даём печать матрицы из чисел без заготовки, смотрим может ли ученик решить задачу

## Печать матрицы из чисел

- заготовка содержит многое из решения
- задача решить любой ценой
- показать после решения другие виды решения этой задачи (например одним циклом)

```
n = 3

1 2 3
4 5 6
7 8 9
```

```
n = 5

1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
```

Заготовка:

```cpp
int main() {

  int n = 3;
  
  for (int i = 0; i < n; ++i) {
  
    for (int j = 0; j < n; ++j) {
    
      std::cout << n << std::endl;
    }
  }
  
  return 0;
}
```

## Печать фигур

- давать дополнительные фигуры до тех пор пока нет ощущения, 
  что человек полностью понял тему (например: заливка половины, вертикальные полосы)

Пустая фигура:

```
.....
.....
.....
.....
.....

```

Фигура с обводкой:

```
n = 1

#

```

```
n = 3

###
#.#
###

```

```
n = 5

#####
#...#
#...#
#...#
#####

```

Фигура крест:

```
n = 3

.#.
###
.#.

```

```
n = 5

..#..
..#..
#####
..#..
..#..

```

Фигура крест (ещё):


```
n = 5

#...#
.#.#.
..#..
.#.#.
#...#

```

Фигура прямоугольный треугольник:

```
n = 5

#....
##...
###..
####.
#####

```

Шахматная доска:

```
n = 5

#.#.#
.#.#.
#.#.#
.#.#.
#.#.#

```

## Печать треугольника

- ширина основания треугольника вычисляется алгоритмически
- показать как это рекуррентно можно понять закономерность w

```
h = 1

#

```


```
h = 2

.#.
###

```


```
h = 3

..#..
.###.
#####
```

```
h = 4

...#...
..###..
.#####.
#######
```


# II. Функции

- работаем с типом данных int, плавный переход к size_t будет по возможности
- не вникаем в устройство работы class matrix, но и не работаем на сырых массивах


Минимальный шаблон для данного раздела:

- в функции fill_index показывается пример работы с матрицей

```cpp
#include <iostream>
#include <vector>


// прячется в заголовочный файл или говорится, что не нужно изучать данный код

class Matrix {
public:
  Matrix(int m, int n) 
  : m_rows(m)
  , m_cols(n) {
  	
  	m_data.reserve(m);
  	
    for (size_t i = 0; i < m; ++i) {
    	
    	std::vector<char> row;
    	row.reserve(n);
    	
    	for (size_t j = 0; j < n; j++) {
    		
    	  row.push_back('.');
    	}
    	
    	m_data.push_back(row);
    }
  }
  
  int rows() const {
  	return m_rows;
  }
  
  int cols() const {
  	return m_cols;
  }
  
  std::vector<char>& operator[](int index) {
  	return m_data[index];
  }
  
  const std::vector<char>& operator[](int index) const {
  	
  	return m_data[index];
  }  
  
private:
  int m_rows;
  int m_cols;
  std::vector<std::vector<char>> m_data;
  
};

Matrix create_matrix(int m, int n) {
	return Matrix(m, n);
}

// ученик может смотреть код ниже ---
//                                 |
//                                 v


Matrix fill_index(const Matrix& matrix, int i, int j) {
	
  Matrix result = matrix;
  
  result[i][j] = '#';
  
  return result;
}

void  print(const Matrix& matrix) {
	
  for (int i = 0; i < matrix.rows(); ++i) {
  	
  	for (int j = 0; j < matrix.cols(); ++j) {
  		
  	  std::cout << matrix[i][j] << std::endl;
  	}
  }
}

int main() {
	
	Matrix m1 = create_matrix(4, 4);
	Matrix m2 = fill_index(m1, m1.rows() - 1, m1.cols() - 1);
	print(m2);
	
	return 0;
}
```

## Трафарет

```

Matrix fill_border(const Matrix& matrix);
Matrix fill_half(const Matrix& matrix);
Matrix fill_cross(const Matrix& matrix);
Matrix invert(const Matrix& matrix);

```

## Параметризация трафарета

- Все символы которые заполняет трафарет можно подставить

```cpp
Matrix m1 = create_matrix(5, 5);
Matrix m2 = fill_border(m1, '#');
Matrix m3 = fill_cross(m1, 'x');
print(m3);
```

Выдаст такой результат:

```
x###x
#x.x#
#.x.#
#x.x#
x###x
```

## Дизайн интерфейса функции

- количество знаков в числе
- сколько знаков данного значения встречается в числе
- есть список чисел, найти число в котором максимальное число знаков с заданным значением
- строка в число
- число в строку

```cpp
  int digits_in(int n);
  int find_digit(int n, int d);
  
```
