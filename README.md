# semester_first
my_make:
Проект на плюсах, есть следующие файлы:

string.h (там реализован класс строк)

tests.h (не зависит от string.h)

tests.cpp 

tester.cpp (зависит только от tests.h)

main.cpp (зависит только от string.h)

В файле tests.h объявлена одна функция: bool runAllTests()

В файле tests.cpp эта функция реализована и вызывает подряд несколько тестов(простых) для моей строки. Если все тесты прошли успешно, она возвращает true, а если хоть один тест провлился,то false.

tester.cpp вызывает runAllTests и если тесты выполнились успешно, то возвращает 0 и завершается, иначе возвращает 1

main.cpp считывает строку из консоли и выводит обратно

К этому есть Makefile, который умеет собирать весь проект(каждый из двух исполняемых файлов), причём tester собирается с санитайзерами, а main без них, прогонять тесты, очищать директорию от сгенерированных файлов (.o, исполняемые)

Algoritms:

   Sort:
   
     1.k-th_ordinal_statistics
     
     2.LSD
     
     3.quick_sort
     
   Trees:
   
     Binary trees and heap:
     
        1.AVL
        
        2.binary_heap
        
        3.Splay-tree
        
      Other trees:
      
        1. dekart-tree
        
        2.fenwick_tree
        
        3.implicit dekart_tree
        
        4.implicit_segtree
        
        5.rectangle_combining (площадь объединения прямоугольников)
        
        6.three-dimensional_segtree
        
        7.two-dimensional segtree
    
    1.histogram
    
    2.sparse_table
    
    3.stack (реализация стека через указатели)
        
       
      
    
