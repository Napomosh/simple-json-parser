Документация была сделана с помощью Doxygen. Ее можно посмотреть открыв файл index.html из папки html. Либо собрать ее с помощью файла doc_file и команды doxygen doc_file.


Сборку выполнял командой с помощью g++ командой: g++ -o test test_parser.cpp parser.cpp

Запустить можно командой ./test test.json

Где ./test имя исполняемого файла, а test.json файл с json информацией. Файлов можно указать сколько угодно (минимум один), но рассмотрен будет только первый.


Теперь немного о парсере. 
Изначально планировал сделать в unordered_multimap, с помощью которой можно было проводить поиск по записям. Ключом должна была быть строка, а значением список строк (легко добавлять, а доступ нам не нужен, только вывод. А сложность вывода у всех одинакова). Но посмтрев более сложные примеры json, я понял, что нужно брать дерево. С одной стороны очевидно, с другой я о нем не думал, т.к. выбирал из контейнеров stl. Сейчас уже понятно, что неплохо было бы написать его самому, выглядит не сложно (для этой задачи). Но в итоге пришлось все быстро переписывать и сохранять результат в обычную строку, чтобы хоть что-то работало, так как время я расчитал не слишком точно.

