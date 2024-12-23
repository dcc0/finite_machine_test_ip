/*Конечный автомат с двумя состояниями. Работает в фоне, уведомляет о разрыве сети.*/
/*Если сети нет, запускаем программу с пингом сайта или ip, получаем  однократный звуковой сигнал,о том
что сети нет. Когда сеть будет восстановлена, получаем звуковой сигнал (мелодию) другой тональности
и завершаем программу*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int test(char * ip) {
if(system(ip)==0) {
return 1;
}
else
{
return 0;
}}
void wait(int initial_state, char * ip) {
while (1) {
sleep (5);
test(ip);
/*Если начальное состояние (b) не равно результату проверки ресурса - (test(ip)), - то
подадим звуковой сигнал и изменим начальное состояние.*/
if (initial_state !=test(ip)) {
initial_state =test(ip);
if (test(ip) == 1) {
system("beep -f 900 -l 500; beep -f 700 -l 1000; beep -f 800 -l 500; beep -f 800 -l 500; beep -f 900 -l 1000;");
printf("CETb ECTb!");
 /*Чтобы сделать  "бесконечную" работу, убрать break.*/
break;
}
else
{
system("beep -f 1200 -l 2000");
}}}}
/*Первый запуск*/
void start (char * ip) {
if (test(ip)==0)
system("beep -f 1200 -l 2000");
}
int main (int argc, char *argv[]) {
int initial_state = 0;
char ip[100]="ping -c 1 ";
if (argc < 2) {
printf("Введите адрес  вторым параметром ");
return 0;
}
/*Проверим доступность ресурса. Переменная initial_state хранит начальное состояние*/
sprintf(ip, "%s%s", ip, argv[1]);
start (ip);
wait (initial_state, ip);
}
