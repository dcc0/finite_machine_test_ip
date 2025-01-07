#!/bin/bash
#Скрипт при помощи curl проверяет доступность сайта 
#и уведомляет звуком. By Ivan Gavryushin aka dcc0, MoL0T
#ivangavr777@gmail.com. MSK. Butovo. 2025

printf "Использование: test_web.sh [https://localhost.ru]\r\n"
printf "Для бесконечного выполнения: test_web.sh [https://localhost.ru] [1]\r\n"
printf "Третий параметр задаёт интервал test_web.sh [https://localhost.ru] [1] [30]\r\n"
#Тест. Функция

function test_web  {
TEST_WEB=$(curl -o /dev/null -s -w "%{http_code}\n" "$1")
	case $TEST_WEB in
	"200")
return 0;
;;
	"000")
return 1;
;;
esac
}

#Уведомление звуком. Функция
function notify {
	if [  "$return_val" -eq  "0" ];
	then
	beep -f 600 -l 500
	beep -f 400 -l 500 
	beep -f 600 -l 500
	else
	beep -f 300 -l 500
	fi
}

#Первый запуск
test_web "$1"
return_val=$?
if [[ $return_val =  "0" ]]
then
TRIGGER="0"
fi
if [[ $return_val = "1" ]]
then
TRIGGER="1"
fi

#Уведомляем при старте
notify $return_val;
	
#Если второй параметр не задан, то завершим
#Для бесконечного выполнения задать 1
if [[ -z "$2" ]]
then
exit
fi

#Проверим третий аргумент (интервал)
if [[ -z "$3" ]]
then
$3="10";
fi

#Слушаем в цикле
while :
do
sleep "$3"
test_web "$1"
return_val=$?
if [ "$TRIGGER" -ne "$return_val" ]
then
TRIGGER=$return_val
notify $return_val
fi
done
