#!/bin/bash

# Переведём лог atop из бинарного формата в ASCII (при необходимости)
atop -Mr atop_20200508 >> atop.log

# Выведем в отдельный файл значения Load Average (за 1 минуту) из лога atop
cat atop_ascii | grep "2020/05/08" -A 9 | grep avg | awk {'print $4'} >> avg1.list

# Выведем в отдельный файл свободную память (заменив мегабайты на 1 гигабайт) из лога atop
cat atop_ascii | grep MEM | grep free | awk {'print $7'} | sed 's/^[0-9]*.[0-9]*M$/1.0G/' | sed 's/G//' >> ram.list
