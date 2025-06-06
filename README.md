## 1. Содержание репозитория

| путь                               | что находится                                                                                                                                                                                                                                                                                                                                                                       |
| ---------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `src/`                             | **C++-исходники** всех алгоритмов и утилит:<br>  • `StringGenerator.h` — генерация тестовых массивов<br>  • `StringSortTester.h` — измеритель времени + счётчик символьных сравнений<br>  • `StringAlgos.h` — 4 специализированных сортировки (StringQS, StringMS, MSD, MSD+QS) + обёртки для std-алгоритмов<br>  • `main.cpp` — единая тест-программа, формирующая `all_algos.csv` |
| `set9.ipynb`                   | Jupyter-ноутбук с пошаговой визуализацией результатов и комментариями                                                                                                                                                                                                                                                                                                               |
| `cmake-build-debug/ baseline.csv`  | базовый замер только `std::sort` / `std::stable_sort`                                                                                                                                                                                                                                                                                                                               |
| `cmake-build-debug/ all_algos.csv` | полный замер **шести** алгоритмов (std + 4 спец.)                                                                                                                                                                                                                                                                                                                                   |

---

## 2. Постановка задачи

Нужно сравнить работу обычных и модифицированных алгоритмов сортировки строк
на массивах от 100 до 3000 строк (шаг 100) для трёх типов входов:

* **random** — полностью случайные строки
* **reverse** — отсортированы в обратном лексикографическом порядке
* **almost** — отсортированы, затем ≤ 5 % случайных пар переставлены

Каждая строка длиной 10–200 символов, алфавит — 74 знака
(латиница A-Z / a-z, цифры 0-9, спецсимволы `!@#%:;^&*()-.`).

### Измеряемые метрики

* среднее **время выполнения** (мс) для 7 запусков
* среднее число **посимвольных сравнений** `char_cmp`
  (другие операции не учитываются)

---

## 3. Реализованные алгоритмы

| алгоритм           | файл                 | краткое описание                                    |
| ------------------ | -------------------- | --------------------------------------------------- |
| `std::sort`        | `main.cpp` (обёртка) | introsort / быстрая сортировка STL                  |
| `std::stable_sort` | `main.cpp`           | mergesort STL                                       |
| **StringQS**       | `StringAlgos.h`      | тернарный QuickSort (multi-key)                     |
| **StringMS**       | `StringAlgos.h`      | MergeSort + LCP-кэш                                 |
| **MSD**            | `StringAlgos.h`      | MSD Radix без переключения                          |
| **MSD+QS**         | `StringAlgos.h`      | MSD Radix с переходом на StringQS, если размер < 74 |

Все функции принимают `vector<string>&`, используют глобальный счётчик `gCmp` для регистрации символ‑к‑символу сравнений.

---

## 4. Просмотр графиков

Откройте `analysis.ipynb` и выполните все ячейки.
Будут построены 6 графиков (время и сравнения для random / reverse / almost)
с подробными текстовыми пояснениями.

---

## 5. Результаты (кратко)

* **MSD** — линейное время, `char_cmp ≈ 0`, лучший на всех типах входа.
* **MSD+QS** — совпадает с MSD, но на маленьких массивах чуть быстрее.
* **StringQS** — выигрывает по сравнениям на random, проигрывает на reverse / almost.
* **StringMS** — меньше сравнений, чем `std::stable_sort`, но медленнее из‑за LCP‑кэша.
* `std::sort` остаётся «универсальным» серединным вариантом.

---

## 6. Codeforces ID

| задача | ID            |
| ------ | ------------- |
| A1m    | **321242004** |
| A1q    | **321242223** |
| A1r    | **321242561** |
| A1rq   | **321242736** |

---
