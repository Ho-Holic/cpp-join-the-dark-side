# Coding Standart for C++ language
*Document 0001*

# 1. Проект

## 1.1. Выучите префиксы используемые в проекте.

## 1.2. Держите пути подключаемых файлов в чистоте

### 1.2.1. Не используйте относительные пути поднимающиеся выше директории вашего проекта

## 1.3. Используйте thesaurus для того чтобы подобрать правильные имена для предметной области

Сервис Google Translate плохо подходит для подбора синонимов и антонимов, используйте более профессиональный ресурс. 

Дополнительно: [thesaurus](http://www.thesaurus.com/)

## 1.4. С осторожностью относитесь к макросам __TIME__, __DATE__ и тд

Макросы __TIME__ и __DATE__ меняются от компиляции к компиляции, следовательно если вам нужно получить
одинаковые контрольные суммы для shared library собранной из одних и тех же исходных кодов, то стоит избежать
использование макросов такого типа. А так же большинства средств которые позволяют получить какие то значения в момент компиляции с использованием макросов. Например случайное число.

## 1.5. Собирайте макросы в специальный файлы

Для проекта определён особый порядок хранения макросов. Общепринятые в С++ сообществе макросы должны помещаться
в macro.h

Остальные макросы должны быть в файлах заканчивающихся на *macro.h, т.е. logmacro.h, gismacro.h, modulemacro.h

Исключением являются макросы которые делают нестандартуню работу. Например, отключают и включают предупреждения
для сторонних заголовочных файлов, а так же исправляют баги в заголовочных файлах, такие как переопределение стандартных
функций min/max.
Такие макросы должны заканчиваться на fix.h Например prepanoramafix.h, postpanoramafix.h

## 1.6. Создайте файл который поддерживает рекомендации *Guidelines.h*

Каждый проект содержит множество конвенций которые предлагается соблюдать, стоит вынести это в отдельный файл.
TODO: Примеры REQUIRE, INVARIANT, UNUSED, loop, forever и тд

## 1.7. Выберите между h и hpp

Зависит от используемых библиотек

## 1.8. Внимательно отнеситесь к файлам содержащим дефис some-file.h

Некоторые трюки задействуют имена файлов в качестве идентификаторов и это может сломать сборк проекта

## 1.9. Структура проектов

### 1.9.1 Тесты? (Дублирубщая ветка или там же)
### 1.9.2 Отчёты статического анализа, сборки
### 1.9.3 Документация (отдельные файлы)
### 1.9.4 Бинарные файлы
### 1.9.5 Временные файлы

## 1.10. Todo

Оформляйте TODO как отчёты

```cpp
/*
 * TODO: Исправить функцию округления
 * Функция округления недоступна в этой версии NDK
 * Возможный фикс будет в r17
 * (23.01.2017) Сысоев Игорь */
 ```

## 2. Библиотека Qt

### 2.1. Используйте функцию at()

В случае записи за конец массива, программа может продолжить работу, но упасть в совершенно другом месте.
Вызов at() в таком случае сгенерирует исключение и ошибка будет найдена сразу же.
 	
Хорошо
```cpp
collection.at(3);
```

Плохо	
```cpp
collection[3];
```

### 2.2. Используйте reserve при работе с коллекциями основанными на массивах

TODO: описать проблему. Например, возьмём QVector - динамический расширяемый контейнер. Когда количество элементов в векторе достигает максимума, происходит создание нового вектора с в два раза большей памятью и копирование туда элементов из старого вектора. А с помощью reserve, если мы знаем количество элементов заранее, расширение и копирование можно избежать. Зачем тратить на эти операции время и память? Используйте reserve()

### 2.3. Определяйте инварианты с помошью Q_ASSERT и Q_ASSERT_X

TODO: описать что такое инвариант и пару примеров, и перенести это в Guidelines
описать проблемы с платформами типа android где не работает assert и подвести к REQUIRE

### 3. Язык С++

## 3.1. Используйте правильное именование

### 3.1.1. Имена

С++ имеет слабое место, за всё время его использования не сложилось единого способа именовать функции, классы, переменные.
Стандартная библиотека шаблонов, для задания имени функции, использует snake_case, Qt использует lowerCamelCase, а многие не гнушаются писать в стиле C# и Java
используя UpperCamelCase. Наиболее логичным будет использовать стиль написания соответствующий API который чаще всего используется в коде.
Если большинство вызовов в коде соответствуют методам Qt, то и придерживаться стоит стиля Qt.

| Концепт  |	Описание |	Пример |
|----------|----------|--------|
|class    |	Имена классов начинаются с большой буквы  | Database, JoystickController, DatabaseValidator|
|function | имена функций соответствуют стандарту Qt   | getFirstValue(), data.isEmpty(), hasNextCalculation()|
|acronym  | акронимы имеют только первую большую букву | getUuid(), checkId(), loadFromFtp(), HttpReader, ManagerUi |

### 3.1.2. Правильно используйте префиксы в коде

[Венгерская нотация](https://ru.wikipedia.org/wiki/Венгерская_нотация) больше не одобряется мировым сообществом программистов, однако многие префиксы ведут к хорошим практикам. Список разрешённых префиксов :

| Префикс |	Описание | Пример |
|---------|----------|--------|
| GLOBAL_ | глобальные переменные   | GLOBAL_application, GLOBAL_app_mutex |
| s | статичекие члены класса | sClassCounter, sUniqueId |
| m  | члены класса            | mX, mY, mDatabase, mCurrentOperation |

Глобальные переменные имеют максимально вызывающий синтаксис, что побуждает вас
их не использовать, чтобы не наблюдать такие выражения постоянно.

Если статический член класса представляет из себя константу, то правило 3.7 имеет приоритет.

### 3.1.3. Неймспейсы, как их правильно именовать

### 3.1.4. Члены класса

Используйте префикс m для членов класса. m - означает member.

Такое именование имеет свои плюсы и не является венгерской нотацией, так как это новый виток эволюции имён.

* помогает быстро через autocomplete искать члены класса. Способ именования используемый в [google-styleguide](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Initialization) ( ставить подчёркивание после поля класса member_), не позволяет сделать это.
* убирает коллизию имён, когда нужна функция getter для класса. mParent, parent()
* новый уровень когнитивной сложности - по префиксу понятно, что переменная принадлежит классу.

### 3.1.5. Почему указатель у типа данных?

Почему не `int * foo() {}`? Оставим такое выражение для умножения. Остаётся два варианта. Необходимо ставить
звёздочку у типа данных.

| Звёздочка слева кажется более согласованной |	Есть сомнения, где ставить звёздочку | Комментарий |
|---------------------------------------------|--------------------------------------|----------------|
| Dolphin* dolphin = new Dolphin(); |	Dolphin *dolphin = new Dolphin(); | переменная это указатель, всё хорошо |
| dynamic_cast<Dolphin*>(animal); |	dynamic_cast<Dolphin *>(animal); | тут кажется не нужен пробел? |
| Dolphin* getObj() {} | Dolphin *getObj() {} | что же нам делать... |

Есть проблема в таком синтаксисе, это объявление двух указателей `int* i, *j;`
Тут звёздочка прилипает к имени переменной. Но данный стандарт разрешает создание переменных только через
```cpp
int* i;
int* j;
```

TODO пример всех вариантов использования указателя

### 3.1.6. Используйте списки инициализации и выравнивайте их правильно

Списки инициализации должны содержать не только обязательные для инициализации поля, но так же и все поля которые могут конструироваться
по умолчанию (например QStringList, QVector и тд). Тоже самое справедливо и для всей иерархии наследования и даже интерфейсов.
Это позволет позднее при смене интерфейсов найти ошибки, когда вы могли бы забыть инициализировать некоторое поле класса.

TODO Написать про быстрый способ перестановки полей класса в списках инициализации
```cpp
class Data {
public:
  Data(const QString& path);
};

class BaseWorker {
};

class Worker : BaseWorker {
public:
  Worker(int x, int y, int z);  
private:
  QStringList mResult;
  int mX;
  int mY;
  int mZ;
  Data mData;
  QStringList mSequence;
};

Worker::Worker(int x, int y, int z) 
: BaseWorker()
, mResult()
, mX(x)
, mY(y)
, mZ(z)
, mData("./somefile.txt")
, mSequence() {
  processData();
  showResult();
}
```
### 3.1.8. Группируйте заголовочные файлы

Хорошо
```cpp
// qt
#include <QList>
#include <QTextStream>

// stl
#include <set>
#include <algorithm>

// tmp
#include <QDebug>

// common
#include <common/headers/io.h>

// arch
#include <arch/module/src/Module.h>

// map
#include <map/MapWindow/src/MapWindow.h>

// module
#include <efo/EfoDataLoader/src/EfoDataLoader.h>
#include <ShellMenuBar/ShellMenuBar/src/ShellMenuBar.h>
#include <ShellMenuBar/ShellMenuBar/src/ShellMenuAction.h>

// self
#include "MyClass.h" 
```

Плохо
```cpp
#include <ShellMenuBar/ShellMenuBar/src/ShellMenuAction.h>
#include <QList>
#include <set>
#include <efo/EfoDataLoader/src/EfoDataLoader.h>
#include <algorithm>
#include <common/headers/io.h>
#include <map/MapWindow/src/MapWindow.h>
#include <arch/module/src/Module.h>
#include <QTextStream>
#include <ShellMenuBar/ShellMenuBar/src/ShellMenuBar.h>
#include "MyClass.h" 
#include <QDebug>
```
Для файлов из собственного проекта стоит использовать слово self. Если файлы сгруппированы в папке, то использовать имя папки (gis, map).
Для заголовочных файлов с жёсткой линковкой можно использовать имя библиотеки (Demangler, Profiler)
или тот или иной способ группировки.

### 3.1.9. Форматирование функций switch/if который занимаются диспетчеризацией

```cpp
Object* Class::createObject(Type::Enum type) {
  switch(type) {
  case Type::Plane: return new PlaneObject(); break;
  case Type::Car:   return new CarObject();   break;
  case Type::Ship:  return new ShipObject();  break;
  }
  Q_ASSERT(false);
  return nullptr;
}
```

Указывайте все элементы перечисления, или указывайте default ветку

## 3.3. Не используйте дерективу using namespace

Дополнительно: 

[stackoverflow](http://stackoverflow.com/questions/8681714/correct-way-to-define-c-namespace-methods-in-cpp-file)

## 3.4. Не вызывайте виртуальные функции в конструкторах и деструкторах

Никогда не вызывайте вирутальный функции из конструктора! Это можно делать только если вы полностью понимаете как будет происходить диспетчеризация метода. Тоже самое относится и к деструкторам !

```cpp
class Resource {
private:
  Q_DISABLE_COPY(Resource)
public:
  virtual void open() = 0;
  virtual void close() = 0;
};

class ImageResource : public Resource {
private:
  Q_DISABLE_COPY(ImageResource)
public:
  ImageResource();
  ~ImageResource();
  virtual void open();
  virtual void close();
};

ImageResource::ImageResource()
: Resource() {
  ImageResource::open();
}

ImageResource::~ImageResource() {
  ImageResource::close();
}

virtual void ImageResource::open() {
  // some code
}

virtual void ImageResource::close() {
  // some code
}
```
Плохо
```cpp
class Resource {
private:
  Q_DISABLE_COPY(Resource)
public:
  Resource();
  ~Resource();
  virtual void open() = 0;
  virtual void close() = 0;
};

Resource::Resource() {
  open();
}

Resource::~Resource() {
  close();
}

class ImageResource : public Resource {
private:
  Q_DISABLE_COPY(ImageResource)
public:
  virtual void open();
  virtual void close();
};

virtual void ImageResource::open() {
  // some code
}

virtual void ImageResource::close() {
  // some code
}
```

Дополнительно: 

[mayers](http://www.artima.com/cppsource/nevercall.html),

[stackoverflow](http://stackoverflow.com/questions/12092933/calling-virtual-function-from-destructor)

## 3.5. Не только создавайте, но и добавляйте префикс проекта в Guard'ы

Все заголовочные файлы должны быть быть под зашитой. Если вы создаёте файлы вручную, то должны уделить особое внимание этому пункту.
Чтобы избежать коллизий применяется дополнитеьная схема именования. Кроме имени файла ещё указывается имя проекта.
Допустим вы создаёте класс LoadDialog через QtCreator, который находится в проекте EfoPacket, тогда правильная схема именования указана ниже.

Хорошо
```cpp
#ifndef EFO_PACKET_LOAD_DIALOG_H
#define EFO_PACKET_LOAD_DIALOG_H

class LoadDialog
{
public:
    LoadDialog();
};

#endif // EFO_PACKET_LOAD_DIALOG_H
```

Плохо
```cpp

#ifndef LOAD_DIALOG_H
#define LOAD_DIALOG_H

class LoadDialog
{
public:
    LoadDialog();
};

#endif // LOAD_DIALOG_H
```
Не используйте pragma, не переносимо.

Дополнительно: 

[wikipedia](https://ru.wikipedia.org/wiki/Include_guard)

[googlestyleguide](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#The__define_Guard)

## 3.6. Используйте именованные константы и перечисления для задания магических чисел и свойств класса
Хорошо
```cpp

class WorkInstance {
public:
  enum Mode { None, Prepare, Action };
  void calculate();
private:
  static int CALCULATION_LIMIT;
  static QString MODULE_PATH;
};

int WorkInstance::CALCULATION_LIMIT = 37;
QString WorkInstance::WORK_PATH = "./local/trash";

void WorkInstance:calculate() {
  ...
  if (currentMode == Prepare) return;
  while (calculationCout < CALCULATION_LIMIT) {
    ...
  }
}
```

Плохо
```cpp
#define CALCULATION_LIMIT 37
#define MODULE_PATH "./local/trash" 

class WorkInstance {
public:
  void calculate();
};

void WorkInstance:calculate() {
  ...
  if (currentMode == 1) return; // не использовать магические числа!
  while (calculationCout < CALCULATION_LIMIT) { // уже лучше, но ещё лучше без макросов
    ...
  }
}
```

## 3.7. Не игнорируйте предупреждение -Wreorder ('something' will be initialized after).

На первый взгляд безобидная ошибка приведёт к неопределённому поведению и ваши переменные будут инициализированы мусором.

```cpp
#include <iostream>
using namespace std;

class Cat {
public:    
  Cat(int val)
  : mVal(val), 
    mDef(mVal) {}

  void print() {
    cout << mVal << " - "    << mDef << endl;
  }
private:    
  int mDef; // (1)
  int mVal; // (2)
};

int main() {
  Cat c(17);
  c.print();
  return 0;
}
```

Если вы думаете, что будет напечатано "17 - 17" вы неправы. Наиболее вероятные исходы :

```
"17 - 0" 
"17 - 237827932" 
"17 - 488904323" 
...
```

Связано это с тем, что переменная mDef будет инициализирована раньше переменной mVal.

Дополнительно: 

[Gotcha 8](https://www.amazon.com/Gotchas-Avoiding-Common-Problems-Coding/dp/0321125185)

[stackoverflow](http://stackoverflow.com/questions/1828037/whats-the-point-of-g-wreorder)

## 3.8. Если необходимо вставить бинарные данные, а не исходный код используйте расширение .inc вместо .h

```cpp
const char* someBigData = #include "someBigData.inc";
```

Файл с данными:
```
  { 0, 25, 82932, 11, 234, 0, 2, 4, 230 .......... 3290, 66, 3321 }
```

Дополнительно: 

[googlestyleguide](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Self_contained_Headers)

## 3.9. Используйте опережающие объявления для внутренних классов

```cpp
#include <iostream>

struct Cat {
  void action();
  struct Paw; // forward declaration of a inner class
};

struct Cat::Paw {
  void attack();
};

void Cat::Paw::attack() { 
  std::cout << "attacked!" << std::endl; 
}

void Cat::action() { 
  Paw p;
  p.attack();
}

int main() {
  Cat c;
  c.action();
  return 0;
}
```

## 3.10. Не размножайте пустые деструкторы

Есть всего несколько причин в которых вам может понадобится деструктор, во всех остальных случаях он не нужен.
Если ни одна причина не подходит, не пишите его!

* Ваш класс это абстрактный интерфейс. Тогда деструктор нужен только в самом базовом классе. При этом деструктор должен быть вирутальным! TODO : Написать пример, и проблему.

* Вам действительно нужен деструктор для удаления данных, но в таком случае вы должен следовать Rule of Three. Если вы не хотите следовать правилу,
то добавьте в класс макрос Q_DISABLE_COPY. 

TODO: Пример и проблема.

## 3.11. Используйте полиморфизм возвращаемых значений

```cpp
#include <iostream>

class Instance {};

class CatInstance : public Instance {
public:    
  void cat() {
    std::cout << "Cat Object" << std::endl;
  }
};

class DogInstance : public Instance {
public:    
  void dog() {
    std::cout << "Dog Object" << std::endl;
  }    
};

// ==================================================

class BaseFactory {
public:
  virtual Instance* getInstance() = 0;
};

class CatFactory : public BaseFactory {
public:    
  virtual CatInstance* getInstance() {
    std::cout << "cat instance call" << std::endl;
    return new CatInstance();
  }
};

class DogFactory : public BaseFactory {
public:    
  virtual DogInstance* getInstance() {
    std::cout << "dog instance call" << std::endl;
    return new DogInstance();
  }
};

int main() {
  DogFactory* d = new DogFactory();
  CatFactory* c = new CatFactory();
  BaseFactory* ptr = d;

  d->getInstance()->dog();
  c->getInstance()->cat();
  ptr->getInstance();

  return 0;
}
```

standart output:
```
dog instance call
Dog Object
cat instance call
Cat Object
dog instance call
```

## 3.12. Если обходите коллекцию в обратном порядке рассмотрите unsigned тип

TODO: рассмотреть проблему, оператор "goes to"

Дополнительная информация: 

[stackoverflow](http://stackoverflow.com/questions/4205720/iterating-over-a-vector-in-reverse-direction)

## 3.13. Не сравнивайте float/double
Реализация от гугл, добавить в Guidelines.h

Дополнительно: 

[stackoverflow](http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison)

## 3.14. Изучить и не нарушать ODR (One definition rule)

Дополнительно: 

[wikipedia](https://en.wikipedia.org/wiki/One_Definition_Rule)

## 3.15. Не использовать приведение типа в стиле Си

Такие приведения типа очень подверженны ошибкам и их очень сложно искать в коде для анализа или автозамены.

Хорошо
```cpp
double d = 27.3;
int i = static_cast<int>(d);
Data* ptr = new Data();
void* raw = static_cast<void*>(ptr)
```

Плохо
```cpp
double d = 27.3;
int i = (int)d;
void* raw = (void*)ptr;
```

## 3.16. Не использовать многострочные комментарии в стиле Си

http://en.cppreference.com/w/cpp/comment
Только однострочные комментарии
TODO: описать проблему с многострочными

## 3.17. Записывайте условия в математическом стиле
[min, max] 	min <= count && count <= max 

## 3.18. Выделяйте предикатные функции

TODO : написать примеры

is, has, can

для локальных переменных

```cpp
QMap<int, int>::Iterator found = mMap.find(key);
```

## 3.19. Всегда пишите break

TODO сделать нормальный пример (когда была функция с return, а потом стала функцией которая пишет в переменную)

```cpp
enum Type { Unknown, Vector, Raster };

QString nameForType(Type type) {
  switch (type) {
  case Unknown: return "Неизвестный"; break;
  case Vector: return "Векторный"; break;
  case Raster: return "Растровый"; break;
  }
}
```

## 3.20. Разбивайте template функции, но не создавайте отдельный файл (inl, tpp, ...)

Любая inline функция или шаблон автоматически нарушают ODR.
Ошибки такого нарушения крайне редки, только если части библиотек не пересобираются целиком.
Шанс ошибок можно повысить если для шаблонов использовать inl и tpp файлы, поэтому их не рекомендуется использовать.

Дополнительно: 

[habrahabr](https://habrahabr.ru/company/abbyy/blog/108166/)

Хорошо
```cpp
namespace nsTank {
  template<typename Fuel>
  class Tank {
  public:
    int calculateVolume();
  private:
    Fuel mFuel;
  };

  template<typename Fuel>
  int Tank::calculateVolume() {
    int result = someProcessing(mFuel);      
    return result;
  }
}
```

Хорошо
```cpp
namespace nsTank {
  template<typename Fuel>
  class Tank {
  public:
    int calculateVolume();
  private:
    Fuel mFuel;
  };
}

template<typename Fuel>
int nsTank::Tank::calculateVolume() {
  int result = someProcessing(mFuel);      
  return result;
}
```

Плохо
```cpp
namespace nsTank {
  template<typename Fuel>
  class Tank {
  public:
    int calculateVolume();
  private:
    Fuel mFuel;
  };
}
#include "Tank.tpp" // инклудим реализацию шаблона
```

Плохо
```cpp
namespace nsTank {
  template<typename Fuel>
  class Tank {
  public:
    int calculateVolume() {
      int result = someProcessing(mFuel);      
      return result;
    }
  private:
    Fuel mFuel;
  };
}
```

## 3.21. Оформление класса

```cpp
class Cat : public Animal, // (1)
            public Dockable {
public:
  class BodyNode;
  
public:
  using Ptr = std::shared_ptr<Cat>;
  using IdCallback = int (*)(Animal*);
  
public:
  static std::vector<Animal::Ptr> spawnCats(Criteria c);
  
public: // (2)
  Cat();
  Cat(const Cat& that);
  operator int();
  Cat& operator=(Cat& that);  
  ~Cat();    
  
public: // (3)  
  Cat operator+ (const Cat& that);
  Cat operator* (const Cat& that);
    
public:  // (4)
  void walk();
  void sleep();

public: // (5)
  virtual void dockTo(Object* object);
  
private: // (6)  
  virtual void setDockMode(DockMode mode);
  
private: // (7)  
  void calculateSomeStuff();
  
private: // (8)
  std::list<BodyNode> mNodes;
  
};    

struct Cat::BodyNode {
  Wrap wrap;
  Connection connection;
};

```

## 3.22. Инициализация класса должна использовать статические функции

Хорошо:

```cpp
// header
class Window {
public:
  static Program createProgram();
  
public:
  Window();
  
public:
  void initialize();  
  
private:  
  Program mProgram;
};

// source
Window::Window() 
: mProgram(PROGRAM_DEFAULT_VALUE) {
  //
}

void Window::initialize() {
  mProgram = createProgram();
}

Program Window::createProgram() {
  Program p(a, lot, of, arguments);
  //
  // много кода работы с `p`
  //
  //  |--- данный код был перенесён из другой функции
  //  |    но забыли переименовать `mProgram` в `p`
  //  v    Ошибка компиляции!
  bindSomeData(mProgramm, "data1");
  bindSomeData(mProgramm, "data2");
  //
  // много кода работы с `p`
  //  
  return p;
}

```

Плохо: 

```cpp
// header
class Window {
public:
  Window();
  
public:
  void initialize();
  Program createProgram();
  
private:  
  Program mProgram;
};

// source
Window::Window() 
: mProgram(PROGRAM_DEFAULT_VALUE) {
  //
}

void Window::initialize() {
  mProgram = createProgram();
}

Program Window::createProgram() {
  Program p(a, lot, of, arguments);
  //
  // много кода работы с `p`
  //
  //  |--- данный код был перенесён из другой функции
  //  |    но забыли переименовать `mProgram` в `p`
  //  v    Всё работает! Используются настройки по умолчанию
  bindSomeData(mProgramm, "data1");
  bindSomeData(mProgramm, "data2");
  //
  // много кода работы с `p`
  //  
  return p;
}

```

## 3.23. Объявляйте заголовочный файл класса в самом начале

Позволяет уменьшить связанность нашего заголовочного файла

Хорошо:
```cpp
// self
#include "Cat.h"
// other
#include <other_header_files>
```

Плохо:
```cpp
// other
#include <other_header_files>
// self
#include "Cat.h" // может зависеть от other header files

```

# 4. Проектные файлы Qt (перенести в проект)

## 4.1. Используйте перенос строк

## 4.2. Старайтесь не использовать CONFIG += ordered

CONFIG += ordered полностью блокирует возможность параллельной компиляции проектов, что приводит к росту времени компиляции всего комплекса.
Необходимо явно указывать зависимости.


Плохо
```
TEMPLATE = subdirs

CONFIG += ordered \

SUBDIRS += \
  GisMap \
  TestGis \
  GisWidget \
  TestGisWidget
  ```

TODO : польза перестановки строк когда на конце "\"
https://blog.rburchell.com/2013/10/every-time-you-configordered-kitten-dies.html

## 4.3. Создавайте логические секции с помощью дополнительных символов

TEMPLATE = subdirs

CONFIG += ordered \

SUBDIRS += \

## 4.4. Именуйте файлы ресурсов Qt правильно

У файлов ресурсов Qt (расширение *.qrc) есть проблемы. Если два ресурса названы одинаково, qmake генерирует два одинаковых файла и происходит коллизия имён.
Следовательно каждый файл ресурсов должен иметь префикс вашего проекта.

# 5. Вывод ошибок и диагностических сообщений

# 6. Контроль версий

Как правильно писать коммиты можно прочитать в этой статье
Основные принципы: 

| Пишите коммит в формате Issue: Message (time) когда это возможно |	svn ci -m "Issue 123: Изменил отрисовку карты (20m)" |
| Пишите коммит с большой буквы 	| svn ci -m "Улучил скорость работы карты" |
| Не ставьте точку в конце 	| svn ci -m "Хороший коммит" |
| Не отправляйте пустой тело коммита |	svn ci -m "Написал что я сделал и почему 	|

Дополнительно: 

[git-commit](http://chris.beams.io/posts/git-commit/)
