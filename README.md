# Vector-Matrix
Realization of classes Vector and Matrix

Задача

1. Создать класс Vector вещественных векторов, реализующий следующие операции:


1) конструктор, принимающий размер вектора и начальное значение элементов (по умолчанию принять 0);
2) копирующий конструктор;
3) деструктор;
4) операторы: =, +=, -=, + (бинарный и унарный), - (бинарный и унарный), * (произведение вектора на число, на вектор (скалярно), на матрицу, а также произведение числа на вектор), [], <<, >>, оператор приведения типа к указателю на double;
5) метод вычисления длины вектора;
6) метод, возвращающий размерность вектора.


2. Создать класс вещественных матриц:

Симметричные разреженные матрицы, формат хранения CSLR (класс CSLRMatrix):

1) конструктор, принимающий необходимые массивы (данные необходимо скопировать во внутренние массивы);
2) деструктор;
3) операторы умножения * матрицы на число и вектор [1], а также числа на матрицу;
4) операторы считывания из потока (>>) для инициализации внутренних массивов и форматированного вывода в поток (<<);
методы, возвращающие размерность матрицы и количество ненулевых элементов;


Для классов вектора и матрицы создать класс исключения OutOfRangeException, который наследуется от стандартного класса std::exception (располагается в файле exception.h), переопределяет метод what() и выводит сообщение, описывающее суть ошибки. Аналогично, создать класс исключения IncompatibleDimException для обработки ошибок, связанных с выполнением операций над матрицами и векторами с некорректными размерностями.
