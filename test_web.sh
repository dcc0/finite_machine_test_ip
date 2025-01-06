```bash
EST_WEB=`curl -o /dev/null -s -w "%{http_code}\n" $1`
case $TEST_WEB in
        "200")
beep -f 600 -l 500; 
beep -f 500 -l 500; 
beep -f 600 -l 500; 
;;

        "000")
beep -f 200 -l 500; 
;;
esac
```
