# CLearn
 Learning C Programming Language

Всё таки пришёл к тому, что Си надо знать ибо программирование микроконтроллеров и Linux прям располагают к обучению. А по скольку я программировать в целом умею, то тут просто прорешаю задачки на разные темы, нам потребуется:

В качестве IDE буду использовать qtcreator с проектом из CMakeFile, в главной ветке основной шаблон проектов. 

## Модуль 0. Учим 
* Руденко Т.В. - Сборник задач и упражнений по языку Си.
* Брайан Керниган, Деннис Ритчи - Язык программирования Си 

## Модуль 1. Введение

* Ознакомление со спецификой сборки ПО в GNU/Linux
* Ознакомление с консольными текстовыми редакторами (vi,nano,mcedit)
* Ручная и автоматическая сборка ПО (Makefile)
* Модель Клиент-Интерфейс-Сервер (КИС)
* Статическая сборка библиотек
* Совместно используемые библиотеки
* Работа с переменными окружения 

## Модуль 2. Низкоуровневый ввод-вывод и файловые операции

* Обзор механизмов ввода-вывода в Linux (Ubuntu)
* Файловые дескрипторы
* Системные вызовы: open, close, write, read и lseek
* Типы файлов
* Индексные дескрипторы и жесткие ссылки
* Права доступа к файлу
* Файловая система proc
* Два способа прочесть содержимое директории
* Разреженные файлы и специфика их применения
* Блокировка областей файла 3 

## Модуль 3. Межпроцессное взаимодействие

* Механизмы межпроцессного взаимодействия Linux (Ubuntu)
* Неименованные каналы (pipes)
* Именованные каналы (named pipes)
* Сообщения (message queue)
* Разделяемая память (shared memory)
* Семафоры (semaphores)

## Модуль 4. Сокеты

* Сокеты в файловом пространстве имен (UNIX-сокеты)
* Парные сокеты (pair sockets)
* Сетевые сокеты (sockets)

## Модуль 5. Сигналы

* Знакомство с сигналами (signals)
* Отличие сигналов от других механизмов межпроцессного взаимодействия
* Специфика обработки сигналов (signal handling)

## Модуль 6. Процессы

* Клонирование процессов — fork()
* Замена исполняемого процесса — exec()
* Зомби (zombies) — причины возникновения и способы их устранения

## Модуль 7. Потоки

* Потоки и процессы
* Специфика построения многопоточных приложений (multithreading)
* Досрочное завершение потока

## Модуль 8. Потоки (продолжение)

* Создание обработчика завершения потока
* Средства синхронизации потоков (synchronize primitives)
* Атрибуты потоков

## Модуль 9. Демоны (службы)

* Отличие демона от консольной утилиты
* Специфика разработки демонов (daemons)
* Создание демона использующего сетевые сокеты 

## Модуль 10. Консольный ввод-вывод

* Специфика разработки консольных приложений
* Предотвращение перенаправления вывода
* Управление терминалом
* Сокрытие пароля пользователя при аутентификации

## Модуль 11. Отображаемая память

* Отображение обычного файла
* Совместный доступ к файлу
* Частные отображения
* Другие применения mmap

## Модуль 12. Домашнее задание

* Специфика разработки 64-битных приложений
* Использование библиотеки ncurses
