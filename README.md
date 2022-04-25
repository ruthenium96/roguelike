# roguelike

Разработчики:
* Евгений Кадиленко
* Эдгар Макаров
* Александр Пертовский

## Зависимости:

protobuf, googletest (optional)

## Сборка

В корневой папке проекта:
```shell
mkdir build
cd build
cmake ..
cmake --build .
```

## Запуск игры

В папке `build`:
```shell
./src/main
```

## Управление

WASD - движение по карте, E - взаимодействие, Q - выход из игры.

## Запуск тестов:

В папке `build`:
```shell
./tests/unit/unit_tests
```
