/*Конечный автомат с двумя состояниями. Работает в фоне, уведомляет о разрыве сети.*/
/*Принцип работы: если сети нет, запускаем программу с пингом сайта или ip, получаем  однократный звуковой сигнал,о том
что сети нет. Когда сеть будет восстановлена, получаем однократный звуковой сигнал другой тональности
и завершаем программу.
Автор: Ivan Gavryushin (aka dcc0, MoL0T, Black_Ru, AnonymUser, iv777). MSK. Butovo. 2009-2025
Email: ivangavr777@gmail.com, dcc0@mail.ru, mol0t@list.ru. 
Спасибо Тимуру Гатину за идею.
*/
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <time.h>

int main(int argc, char * argv[]) {
   /*Переменная i для цикла, в котором находим количество пробелов*/
  int i = 0;
  /*Переменные основного кода*/
  int amount_of_spaces = 0;
  /*Начальное состояние автомата*/
  int initial_state = 0;
  /*Пинг*/
  char ip[100] = "ping -c 1 ";
  /*Переменная для бесконечного выполнения*/
  char * inifinite_run;
  /*В этой переменной будет ping и ресурс*/
  char ip_test[100];
  char * resource;
  int max_len;
  /*Интервал проверки сайта/ip*/
  int sleep_interval;

  /*Проверим минимальное количество аргументов.*/
  if (argc < 2) {
    printf("Введите адрес  вторым параметром\n\r");
    printf("Третий параметр - 1 - бесконечное выполнение\n\r");
    printf("test_ip.comb  -h - справка\n\r");
    /*Интервал проверки сайта или ip. 5 секунд по умолчанию*/
    sleep_interval  = 5;
    return 0;
  }

/*Проверим интервал*/
  if (argc > 2) {
	sleep_interval = atoi(argv[3]);
	}

  /*Вывод справки*/
  if ( strncmp("-h", argv[1], 8) == 0) {
    printf("Cправка\n\r");
    printf("Использование: \n\r  ip_test.comb [ip, или адрес сайта]\n\r");
    printf("Если сайт или ip доступен, программа уведомит звуком и завершится\n\r");
    printf("Если не доступен, уведомит звуком и будет работать в фоне, пока сайт/ip не станет доступен\n\r");
    printf("ip_test.comb [ip или адрес сайта] [1] - задаст бесконечную проверку сайта в фоне \n\r");
    printf("ip_test.comb [ip или адрес сайта] [1]  [10]-  четвёртый аргумент задаст интервал для непрерывной проверки \n\r");
    return 0;
  }

  /*Аргументы*/
  /*Бесконечное выполнение*/
  inifinite_run = argv[2];
  /*Ресурс, который проверяем*/
  resource = argv[1];
  max_len = sizeof ip_test;

 /*Проверим ввод. Найдем количество пробелов. Проверим на символы | &*/
  for (i = 0; i != max_len; i++) {
    if (argv[1][i] == ' ')
      amount_of_spaces++;
    if (argv[1][i] == '&') {
      printf("Недопустимый символ \n\r");
      return 0;
    }
     if (argv[1][i] == '|') {
      printf("Недопустимый символ \n\r");
      return 0;
    }

 }

  /*Если пробелов больше 2, то завершим программу*/
  if (amount_of_spaces > 3) {
    printf("В строке есть лишние пробелы!");
    return 0;
  }

  /*Склеим строку. Здесь название команды ping и имя ресурса или ip*/
  snprintf(ip_test, max_len, "%s%s", ip, resource);

  /*Проверим доступность ресурса (первый запуск). Переменная initial_state хранит начальное состояние*/
  start(ip_test);
  /*Ожидание события*/
  wait_event(initial_state, ip_test, inifinite_run, sleep_interval);
}

/*ФУНКЦИЯ: Первый запуск*/
void start(char * ip_test) {
  if (test(ip_test) == 0)
    system("beep -f 1200 -l 2000");
}

/*ФУНКЦИЯ: Определение состояния*/
int test(char * ip_test) {
  if (system(ip_test) == 0) {
    return 1;
  } else {
    return 0;
  }
}

/*ФУНКЦИЯ: результат и оповещение*/
void wait_event(int initial_state, char * ip_test, char * inifinite_run, int sleep_interval) {
/*Добавим дату. Структура с датой*/
time_t mytime = time(NULL);
struct tm *now = localtime(&mytime);
char str_month[20];
char str_day[20];
/*Форматирование даты: номера месяца и номера дня*/
strftime(str_month, sizeof(str_month), "%m", now);
strftime(str_day, sizeof(str_day), "%d", now);
/*Переменные месяца и дня для конвертации в целые*/
int s_month;
int s_day;

  while (1) {
    sleep(sleep_interval);
    test(ip_test);
    /*Если начальное состояние (b) не равно результату проверки ресурса - (test(ip)), - то
    подадим звуковой сигнал и изменим начальное состояние.*/
    if (initial_state != test(ip_test)) {
      initial_state = test(ip_test);
      if (test(ip_test) == 1) {
		/*Конвертируем номер дня и месяца в целые*/
		s_day=atoi(str_day);
		s_month=atoi(str_month);
		/*Проверим не январь ли нынче?! :)*/
		  if(s_day > 1 && s_day < 20 && s_month == 1) {
	     /*Если январь до 20, то играем эту мелодию*/
        system("beep -f 523 -l 400;beep -f 880 -l 400;beep -f 880 -l 400;beep -f 783 -l 400;beep -f 880 -l 400;beep -f 698 -l 400;beep -f 523 -l 400;beep -f 523 -l 500;beep -f 523 -l 400;beep -f 880 -l 400;beep -f 880 -l 400;beep -f 932 -l 400;beep -f 783 -l 600;beep -f 1046 -l 600;beep -f 1046 -l 500;beep -f 587 -l 400;beep -f 587 -l 400;beep -f 932 -l 400;beep -f 932 -l 400;beep -f 880 -l 400;beep -f 783 -l 400;beep -f 698 -l 400;beep -f 698 -l 400;beep -f 880 -l 400;beep -f 880 -l 400;beep -f 783 -l 400;beep -f 880 -l 600;beep -f 698 -l 500;");
	   } else {
	    system("beep -f 900 -l 500; beep -f 700 -l 1000; beep -f 800 -l 500; beep -f 800 -l 500; beep -f 900 -l 1000;");
		}
        printf("CETb ECTb!");
        /*Проверим не задан ли второй аргумент. Если не задан, то завершим программу*/
        if (inifinite_run == 0)
          break;
      } else {
        system("beep -f 1200 -l 2000");
      }
    }
  }
}
