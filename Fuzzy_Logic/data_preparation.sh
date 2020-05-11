#!/bin/bash

# Переведём лог atop из бинарного формата в ASCII (при необходимости)
atop -Mr atop_20200508 >> atop.log

# Разархивируем access.log за нужное число (при необходимости)
gunzip -c access.log-20200508.gz > access.log

# Выведем количество обращений к сайту в секунду в отдельный файл
cat access.log | grep "08/May/2020" | awk {'print $4'} | cut -d '[' -f 2 | uniq -c \
| sed "s/^ *//" | cut -d ' ' -f 1  > requests_per_seconds.list

# Выведем в отдельный файл значения Load Average ( за 1 минуту) из лога atop
cat atop_ascii | grep "2020/05/08" -A 9 | grep avg | awk {'print $4'} >> avg1.list
