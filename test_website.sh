#!/bin/bash
#Скрипт при помощи curl проверяет доступность сайта 
#и уведомляет звуком. By Ivan Gavryushin aka dcc0, MoL0T
#ivangavr777@gmail.com. MSK. Butovo. 2025

#Тест. Функция
function test_web  {
TEST_WEB=$(curl -o /dev/null -s -w "%{http_code}\n" "$1");
	case $TEST_WEB in
	"200")
return 1;
;;
	"000")
return 0;
;;
esac
}

#Уведомление звуком. Функция
function notify {
	if [  "$return_val" -eq  "1" ];
	then
	beep -f 600 -l 500;
	beep -f 400 -l 500; 
	beep -f 600 -l 500
	else
	beep -f 300 -l 500;
	fi
}

#Первый запуск
test_web "$1";
return_val=$?;
if [[ $return_val =  "1" ]]
then
TRIGGER="1";
fi
if [[ $return_val = "0" ]]
then
TRIGGER="0";
fi

#Уведомляем при старте
notify $return_val;

#Слушаем в цикле
while :
do
sleep 120
test_web "$1";
return_val=$?;
if [ "$TRIGGER" -ne "$return_val" ]
then
TRIGGER=$return_val;
notify $return_val;
fi
done
