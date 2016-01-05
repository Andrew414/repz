./kill.sh
rm srepz
NGXCFGFOLDER=$(pwd)
sudo nginx -c $(echo $NGXCFGFOLDER"/nginx.cfg")
sudo nginx -s reopen
gcc $(ls *.c) -lfcgi -o srepz
spawn-fcgi -p 8000 -n srepz
