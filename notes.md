#Item 2

это можно даже сформировать в правило
если есть последовательнсоть
a b c d e f
и тебе нужно вставить между ними сепаратор
 a  - b - c - d - e - f
получается у тебя
N элементов, и N-1 сепараторов
проверять вставку сепаратора необходимо вначале
[a] [ - b] [- c] [- d] [ - e] [ - f]
получаются такие группы
это сэкономит тебе кучу времени CPU
нежели если бы ты каждый шаг пытался понять, нужно выкинуть запятую или нет, как тут:
[a -] [b -] [c -] [d -] [e -] [f]

#Item 2 - Напишите библиотеку реализующую кросс платформенность

Необходимо реализовать int main(argc, argv) {} в Android, iOS, Windows, Unix через Native Api