#!/bin/bash

# Переведём лог atop из бинарного формата в ASCII (при необходимости)
atop -Mr atop_20200508 >> atop.log

# Разархивируем access.log за нужное число (при необходимости)
gunzip -c access.log-20200508.gz > access.log
