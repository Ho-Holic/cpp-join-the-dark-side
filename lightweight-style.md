# Именование
Создание нового концепта требует хорошего имени. Необходимо проверить наличие в коде схожих концептов, чтобы уменьшит поисковую выдачу. Хорошая идея использовать
[thesaurus](http://www.thesaurus.com/) для таких целей. Для глаголов можно удобно подобрать симметричные антонимы. 
При желании сделать API где все имена имеют одинаковую длину некоторые тезарусы позволяют ограничить слова по числу символов.

Если вы пытаетесь привести стиль проекта к CamelCase или snake_case, то стоить бросить эту затею. В С++ такой хаос в именовании, что рано или поздно
часть библиотек подключенных в проект всё равно будет в снейке (с учётом STL на старте), а другая часть в кемеле. 
Вместо этого лучше определить разным стилям свою семантику

При реализации хака стоит выбрать худшее и очень длинное имя которое сразу бросаетя вам в глаза и должно вызывать боль, привлекать внимание

# Контрольные суммы
С осторожностью относитесь к макросам TIME, DATE и тд. Макросы TIME и DATE меняются от компиляции к компиляции, 
следовательно при получении контрольной суммы для бинарника или библиотеки собранной из одних и тех же исходных кодов возникнут проблемы

# Удобные концепты
Guidelines.hpp - для инструментов позволяющих поддерживать стиль в проекте, напримре макрос UNUSED и схожий функционал

# TODO/HACK/NOTE Hell

Тудушки имеют тенденция к бесконтрольному росту, чтобы это ограничить необходимо писать детальное описание проблемы с возможными вариантами решения
или вариантами которые были опробованы, но не сработали

```cpp
//
// TODO: Заголовок
//
// Описание проблематики и какие варианты были проверены. Текст того, что нужно сделать
//
```

# Merge

Используйте clang-format чтобы избежать болезненные мерджей

# Стилёк

## Forward declaration for nested class
```cpp
struct Cat {
    void action();
    struct Paw; // forward declaration of a inner class
};

struct Cat::Paw {
  void attack();
};

void Cat::Paw::attack() { 
    // some code
}

void Cat::action() { 
    Paw p;
    p.attack();
}
```
