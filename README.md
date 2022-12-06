# Splay и AA деревья
### Курпас Артём Викторович / ДВФУ АИСД-2022 / Б9121-09.03.03ПИКД

### Отчёт - docs/report.html 

Запуск автоматического тестирование (25 тестов).

```
cd splay-aa-tree
g++ -o run_tests.exe run_tests.cpp
./run_tests [aa/splay]
```

Тесты состоят из следующих блоков:
    **I** (1-5). Тестирование корректности алгоритмов при помощи тестовых файлов.
    **II** (6-10). Тестирование времени вставки на случайных элементах.
    **III** (11-15). Тестирование времени удаления на случайных элементах.
    **IV** (16-20). Тестирование времени доступа на случайных элементах.
    **V** (16-20). Тестирование времени доступа к недавним элементам.

Запись результатов тестов **II-V** блоков производится в файлы *aa_log.out* для АА-дерева и *splay_log.out* для Splay-дерева соответственно.
